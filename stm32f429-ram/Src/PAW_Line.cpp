#include "PAW_Line.h"

PAW_Line::PAW_Line(const PAW_Vector n_begin, const PAW_Vector n_end, const PAW_Color n_color) :
		PAW_Primitive(false, n_color), begin(n_begin), end(n_end){
}

PAW_Line::~PAW_Line()
{
}

void PAW_Line::rotate(const PAW_Vector rotate_point, const int16_t degrees)
{
	PAW_Matrix rotation_matrix(rotate_point.g_size());
	rotation_matrix.to_rotation_matrix(x, y, degrees);

	begin = rotation_matrix * (begin - rotate_point) + rotate_point;
	end = rotation_matrix * (end - rotate_point) + rotate_point;
}

void PAW_Line::translate(const PAW_Vector translation)
{
	begin += translation;
	end += translation;
}

void PAW_Line::show(const PAW_Color &background) const
{
	const int32_t x1 = static_cast<int32_t>(begin[x]);
	const int32_t y1 = static_cast<int32_t>(begin[y]);
	const int32_t x2 = static_cast<int32_t>(end[x]);
	const int32_t y2 = static_cast<int32_t>(end[y]);

	//zmienne pomocnicze
	int32_t d, dx, dy, ai, bi, xi, yi;
	d = dx = dy = ai = bi = xi = yi = 0;

	int32_t xx = x1, yy = y1;

	//ustalanie kierunku rysowania
	if (x1 < x2)
	{
		xi = 1;
		dx = x2 - x1;
	}
	else
	{
		xi = -1;
		dx = x1 - x2;
	}

	if (y1 < y2)
	{
		yi = 1;
		dy = y2 - y1;
	}
	else
	{
		yi = -1;
		dy = y1 - y2;
	}

	//pierwszy piksel
	BSP_LCD_DrawPixel(xx, yy, color.g_value());

	//oœ wiod¹ca OX
	if (dx > dy)
	{
		ai = 2 * (dy - dx);
		bi = 2 * dy;
		d = bi - dx;

		//pêtla po x
		while (xx != x2)
		{
			//test wspó³czynnika
			if (d >= 0)
			{
				xx += xi;
				yy += yi;
				d += ai;
			}
			else
			{
				d += bi;
				xx += xi;
			}
			BSP_LCD_DrawPixel(xx, yy, color.g_value());
		}
	}
	else
	{
		ai = 2 * (dx - dy);
		bi = 2 * dx;
		d = bi - dy;

		//pêtla po y
		while (yy != y2)
		{
			//test wspó³czynnika
			if (d >= 0)
			{
				xx += xi;
				yy += yi;
				d += ai;
			}
			else
			{
				d += bi;
				yy += yi;
			}
			BSP_LCD_DrawPixel(xx, yy, color.g_value());
		}
	}
}

uint32_t PAW_Line::send_to_ram(const uint16_t x, const uint16_t y) const
{
	return uint32_t();
}

PAW_Vector PAW_Line::g_begin() const
{
	return begin;
}

PAW_Vector PAW_Line::g_end() const
{
	return end;
}

void PAW_Line::rotate_helper(const PAW_Matrix rotation_matrix)
{
	begin[y] *= -1;
	begin[z] *= -1;
	begin = rotation_matrix * begin;
	begin[y] *= -1;
	begin[z] *= -1;

	end[y] *= -1;
	end[z] *= -1;
	end = rotation_matrix * end;
	end[y] *= -1;
	end[z] *= -1;
}
void PAW_Line::projection_helper(const PAW_Matrix projection_matrix)
{
	begin[y] *= -1;
	begin[z] *= -1;
	begin = projection_matrix * begin;

	end[y] *= -1;
	end[z] *= -1;
	end = projection_matrix * end;
}

void PAW_Line::scale_helper(const float scale)
{
	begin *=scale;
	end *=scale;
}
