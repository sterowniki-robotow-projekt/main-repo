#include "PAW_Scene.h"

PAW_Scene::PAW_Scene(const PAW_Color n_background) : size_x(240), size_y(320), background(n_background)
{
	figs.clear();
}

PAW_Scene::~PAW_Scene()
{

}

void PAW_Scene::display() const
{
	display_background(background);
	for (size_t i = 0; i < figs.size(); ++i)
	{
		figs[i].show(background);
	}
}

void PAW_Scene::push(const PAW_Figure n_fig)
{
	figs.push_back(n_fig);
}

void PAW_Scene::translate(const PAW_Vector n_translation)
{
	for (size_t i = 0; i < figs.size(); ++i)
	{
		figs[i].translate(n_translation);
	}
}

void PAW_Scene::rotate(const PAW_Vector rotate_point, const int16_t degrees)
{
	for (size_t i = 0; i < figs.size(); ++i)
	{
		figs[i].rotate(rotate_point, degrees);
	}
}

PAW_Color PAW_Scene::g_background() const
{
	return background;
}

PAW_Color &PAW_Scene::g_background()
{
	return background;
}

std::vector<PAW_Figure> PAW_Scene::g_figs() const
{
	return figs;
}

std::vector<PAW_Figure>& PAW_Scene::g_figs()
{
	return figs;
}

PAW_Figure &PAW_Scene::g_figs(const size_t index)
{
	return figs[index];
}


void display_background(const PAW_Color background)
{
	for (uint32_t i = 0; i <= 240; ++i)
	{
		for (uint32_t j = 0; j <= 320; ++j)
		{
			BSP_LCD_DrawPixel(i, j, background.g_value());
		}
	}
}
