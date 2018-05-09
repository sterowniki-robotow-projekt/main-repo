#pragma once
#include <PAW_Color.h>

void swap(float& a, float& b)
{
	float temp = a;
	a = b;
	b = temp;
}

int integral_part(float x)
{
	return floor(x);
}

float fraction_part(float x)
{
	return x - floor(x);
}

float round(float x)
{
	return integral_part(x + 0.5);
}

class PAW_Primitive
{
public:
	virtual void rotate(PAW_Vector rotate_point, int16_t degrees) = 0;
	virtual void translate(PAW_Vector T) = 0;
	virtual void show(PAW_Color& background) = 0;
	virtual uint32_t send_to_ram(uint16_t x, uint16_t y) = 0;
	virtual void set_color(PAW_Color col)
	{
		this->col = col;
	};
	PAW_Primitive(bool filled, PAW_Color acol): is_filled(filled), col(acol) {};
	virtual ~PAW_Primitive(){};

	PAW_Color col;
	bool is_filled;
};


class PAW_Point final: public PAW_Primitive
{
public:
	PAW_Point(PAW_Vector apos, PAW_Color acol):pos(apos), PAW_Primitive(false, acol){};

	PAW_Vector pos;
	virtual uint32_t send_to_ram(uint16_t x, uint16_t y) final
	{};
	virtual void show(PAW_Color& background) final
	{
		BSP_LCD_DrawPixel(pos['x'], pos['y'], col.fullColor);
	};

	virtual void rotate(PAW_Vector rotate_point, int16_t degrees) final
	{
		(*this).pos -= rotate_point;
		PAW_Matrix R;
		R = R.make_rotation('x', 'y', degrees);
		(*this).pos =  R * (*this).pos;
		(*this).pos += rotate_point;
	}

	virtual void translate(PAW_Vector T) final
	{
		(*this).pos += T;
	}

	~PAW_Point(){};
};

class PAW_Line final: public PAW_Primitive
{
public:
	PAW_Vector start;
	PAW_Vector end;
	virtual uint32_t send_to_ram(uint16_t x, uint16_t y) final
	{};
	PAW_Line(PAW_Vector astart, PAW_Vector aend, PAW_Color acol):
		PAW_Primitive(false, acol)
	{
		start = PAW_Vector(astart);
		end = PAW_Vector(aend);
	};

	 virtual void show(PAW_Color& background)
	 {
		 const int x1 = start['x'];
		 const int y1 = start['y'];
		 const int x2 = end['x'];
		 const int y2 = end['y'];
	     // zmienne pomocnicze
	     int d, dx, dy, ai, bi, xi, yi;
	     int x = x1, y = y1;
	     // ustalenie kierunku rysowania
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
	     // ustalenie kierunku rysowania
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
	     // pierwszy piksel
	     BSP_LCD_DrawPixel(x, y, col.fullColor);
	     // oœ wiod¹ca OX
	     if (dx > dy)
	     {
	         ai = (dy - dx) * 2;
	         bi = dy * 2;
	         d = bi - dx;
	         // pêtla po kolejnych x
	         while (x != x2)
	         {
	             // test wspó³czynnika
	             if (d >= 0)
	             {
	                 x += xi;
	                 y += yi;
	                 d += ai;
	             }
	             else
	             {
	                 d += bi;
	                 x += xi;
	             }
	             BSP_LCD_DrawPixel(x, y, col.fullColor);
	         }
	     }
	     // oœ wiod¹ca OY
	     else
	     {
	         ai = ( dx - dy ) * 2;
	         bi = dx * 2;
	         d = bi - dy;
	         // pêtla po kolejnych y
	         while (y != y2)
	         {
	             // test wspó³czynnika
	             if (d >= 0)
	             {
	                 x += xi;
	                 y += yi;
	                 d += ai;
	             }
	             else
	             {
	                 d += bi;
	                 y += yi;
	             }
	             BSP_LCD_DrawPixel(x, y, col.fullColor);
	         }
	     }
	 }

	virtual void rotate(PAW_Vector rotate_point, int16_t degrees) final
	{
		start -= rotate_point;
		PAW_Matrix R;
		R = R.make_rotation('x', 'y', degrees);
		start =  R * start;
		start += rotate_point;

		end-= rotate_point;
		end =  R * end;
		end += rotate_point;
	}

	virtual void translate(PAW_Vector T) final
	{
		(*this).start += T;
		(*this).end += T;
	}

	~PAW_Line(){};
};

class PAW_Circle final: public PAW_Primitive
{
public:
	PAW_Circle(PAW_Vector c, float rad, bool filled, PAW_Color col):
		center(c),
		radius(rad),
		PAW_Primitive(filled, col)
	{};

	virtual uint32_t send_to_ram(uint16_t x, uint16_t y) final
	{};
	PAW_Vector center;
	float radius;

	virtual void show(PAW_Color& background) final
	{
		if(!is_filled)
		{
		PAW_Vector p(0, -radius, 0, 0);
		for(float i = 0; i < 360; i++)
		{
		float c = cos(i/180*3.1415);
		float s = sin(i/180*3.1415);
		PAW_Matrix R(c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		PAW_Vector temp = R * p;
		BSP_LCD_DrawPixel(temp['x'] + center['x'], temp['y'] + center['y'], col.fullColor);
		}
		}
		else
		{
		PAW_Vector p(0, radius, 0, 0);
		for(float i = 0; i < 360; i += 2)
		{
			float c = cos(i/180*3.1415);
			float s = sin(i/180*3.1415);
		PAW_Matrix R(c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		PAW_Vector temp = R * p;
		//BSP_LCD_DrawPixel(temp['x'] + center['x'], temp['y'] + center['y'], col.col);
		PAW_Line line(PAW_Vector(temp['x'] + center['x'], temp['y'] + center['y'], 0, 1), PAW_Vector(center['x'], center['y'], 0, 1),col);
		line.show(background);
		}
	}
	}

	virtual void rotate(PAW_Vector rotate_point, int16_t degrees) final
	{
		(*this).center -= rotate_point;
		PAW_Matrix R;
		R = R.make_rotation('x', 'y', degrees);
		(*this).center =  R * (*this).center;
		(*this).center += rotate_point;
	}

	virtual void translate(PAW_Vector T) final
	{
		(*this).center += T;
	}

	~PAW_Circle(){};
};

