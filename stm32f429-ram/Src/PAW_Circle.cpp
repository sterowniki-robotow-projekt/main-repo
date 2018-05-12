#include "PAW_Circle.h"

PAW_Circle::PAW_Circle(const PAW_Vector n_center, const float n_radius, bool n_filled, const PAW_Color n_color) :
		PAW_Primitive(n_filled, n_color), center(n_center), radius(n_radius)
{
}

PAW_Circle::~PAW_Circle()
{
}

void PAW_Circle::rotate(const PAW_Vector rotate_point, const int16_t degrees)
{
	PAW_Matrix rotation_matrix(rotate_point.g_size());
	rotation_matrix.to_rotation_matrix(x, y, degrees);

	center = rotation_matrix * (center - rotate_point) + rotate_point;
}

void PAW_Circle::translate(const PAW_Vector translation)
{
	center += translation;
}

void PAW_Circle::show(const PAW_Color &background) const
{
	if (!is_filled)
	{
		PAW_Vector p(0.0f, -radius, 0.0f, 0.0f);
		for (float i = 0; i < 360; ++i)
		{
			PAW_Matrix rotation_matrix(4);
			rotation_matrix.to_rotation_matrix(y, x, i);
			PAW_Vector temp = rotation_matrix * p;

			BSP_LCD_DrawPixel(temp[x] + center[x], temp[y] + center[y], color.g_value());
		}
	}
	else
	{
		PAW_Vector p(0.0f, radius, 0.0f, 0.0f);
		for (float i = 0; i < 360; i += 2)
		{
			PAW_Matrix rotation_matrix(4);
			rotation_matrix.to_rotation_matrix(y, x, i);
			PAW_Vector temp = rotation_matrix * p;

			PAW_Vector first(temp[x] + center[x], temp[y] + center[y], 0.0f, 1.0f);
			PAW_Vector second(center[x], center[y], 0.0f, 1.0f);
			PAW_Line line(first, second, color);
			line.show(background);
		}
	}
}

uint32_t PAW_Circle::send_to_ram(const uint16_t x, const uint16_t y) const
{
	return uint32_t();
}

PAW_Vector PAW_Circle::g_center() const
{
	return center;
}

float PAW_Circle::g_radius() const
{
	return radius;
}

PAW_Vector &PAW_Circle::g_center()
{
	return center;
}

float &PAW_Circle::g_radius()
{
	return radius;
}

void PAW_Circle::rotate_helper(const PAW_Matrix rotation_matrix)
{
	center[y] *= -1;
	center[z] *= -1;
	center = rotation_matrix * center;
	center[y] *= -1;
	center[z] *= -1;
}
void PAW_Circle::projection_helper(const PAW_Matrix projection_matrix)
{
	center[y] *= -1;
	center[z] *= -1;
	center = projection_matrix * center;
}
void PAW_Circle::scale_helper(const float scale)
{
	center *=scale;
	radius *=scale;
}
