#pragma once
#include <PAW_Color.h>
#include <PAW_Primitive.h>
#include <vector>

class PAW_Figure
{
public:
	std::vector<PAW_Primitive *> form;

	PAW_Figure(){};

	PAW_Figure(std::vector<PAW_Primitive *> & aform)
	{
		for(unsigned int i = 0; i < aform.size(); i++)
			form.push_back( aform[i] );
	};

	void push(PAW_Line line)
	{
		form.push_back(new PAW_Line(line.start, line.end, line.col));
	}

	void push(PAW_Circle circle)
	{
		form.push_back(new PAW_Circle(circle.center, circle.radius, circle.is_filled, circle.col));
	}

	void push(PAW_Point p)
	{
		form.push_back(new PAW_Point(p.pos, p.col));
	}

	void show(PAW_Color& background)
	{
		for (unsigned int i = 0; i < form.size(); i++)
		{
			form[i]->show(background);
		}
	}

	void translate(PAW_Vector T)
	{
		for (unsigned int i = 0; i < form.size(); i++)
		{
			form[i]->translate(T);
		}
	}

	void rotate(PAW_Vector rotate_point, int16_t degrees)
	{
		for (unsigned int i = 0; i < form.size(); i++)
		{
			form[i]->rotate(rotate_point, degrees);
		}
	}
};
