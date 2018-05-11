#pragma once
#include "PAW_Figure.h"
#include "main.h"

class PAW_Scene
{
private:
	float size_x, size_y;
	PAW_Color background;
	std::vector <PAW_Figure> figs;

public:
	PAW_Scene(const PAW_Color n_background);
	~PAW_Scene();
	void display() const;
	void push(const PAW_Figure n_fig);
	void translate(const PAW_Vector n_translation);
	void rotate(const PAW_Vector rotate_point, const int16_t degrees);
	PAW_Color g_background() const;
	std::vector <PAW_Figure> g_figs() const;
	PAW_Color &g_background();
	std::vector<PAW_Figure> &g_figs();
	PAW_Figure &g_figs(const size_t index);
};

void display_background(const PAW_Color background);
