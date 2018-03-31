#pragma once
#include <PAW_Color.h>
#include <PAW_Primitive.h>
#include <PAW_Figure.h>
#include <vector>


void display_background(PAW_Color cols)
{
	for(uint32_t i = 0; i <= 240; i++)
	{
		for(uint32_t j = 0; j <= 320; j++)
		{
			BSP_LCD_DrawPixel(i, j, cols.col);
		}
	}
}

class PAW_Scene
{
public:
	float size_x;
	float size_y;
	PAW_Color background;

	std::vector<PAW_Figure> figs;
	//uint8_t ilosc_figur;
	//uint8_t max_ilosc_figur;

	PAW_Scene(PAW_Color background):
		size_x(240),
		size_y(320),
		background(background)
		//ilosc_figur(0),
		//max_ilosc_figur(8)
	{
		figs.clear();
	};

	void display(void)
	{
		display_background(background);
		for (unsigned int i = 0; i < figs.size(); i++)
		{
			figs[i].show(background);
		}
	};

	void push(PAW_Figure fig)
	{
		figs.push_back(fig);
	};

	void translate(PAW_Vector T)
	{
		for (unsigned int i = 0; i < figs.size(); i++)
		{
			figs[i].translate(T);
		}
	}

	void rotate(PAW_Vector rotate_point, int16_t degrees)
	{
		for (unsigned int i = 0; i < figs.size(); i++)
		{
			figs[i].rotate(rotate_point, degrees);
		}
	}
};
