#include "figures.h"

void PAW_MakeStarFromFigure(PAW_Figure & figure, const PAW_Vector position, const float radius, const PAW_Color color)
{
	PAW_Vector gw1(0.0f, radius, 0.0f, 1.0f);
	PAW_Vector gw2(radius * sqrt(3) / 2.0f, radius / 2.0f, 0.0f, 1.0f);
	PAW_Vector gw3(-radius * sqrt(3) / 2.0f, radius / 2.0f, 0.0f, 1.0f);

	PAW_Line line1(position - gw1, position + gw1, color);
	PAW_Line line2(position - gw2, position + gw2, color);
	PAW_Line line3(position - gw3, position + gw3, color);
	figure.push(line1);
	figure.push(line2);
	figure.push(line3);
}

void PAW_MakeDonutFromFigure(PAW_Figure & figure, const PAW_Vector position, const float radius1, const float radius2, const PAW_Color color)
{
	PAW_Circle circle1(position, radius1, true, color);
	PAW_Circle circle2(position, radius2, true, color);
	figure.push(circle1);
	figure.push(circle2);
}

void PAW_MakeFeatherFromFigure(PAW_Figure & figure)
{
	PAW_Circle big_cir1(PAW_Vector(120.0f, 90.0f, 0.0f, 1.0f), 35.0f, true, PAW_Color(255, 0, 255, 0));
	PAW_Circle big_cir2(PAW_Vector(120.0f, 90.0f, 0.0f, 1.0f), 20.0f, true, PAW_Color(255, 0, 0, 255));

	PAW_Circle mid_cir1(PAW_Vector(120.0f, 90.0f + 50.0f, 0.0f, 1.0f), 30.0f, true, PAW_Color(255, 0, 255, 0));
	PAW_Circle mid_cir2(PAW_Vector(120.0f, 90.0f + 50.0f, 0.0f, 1.0f), 15.0f, true, PAW_Color(255, 0, 0, 255));

	PAW_Circle s_cir1(PAW_Vector(120.0f, 90.0f + 50.0f + 40.0f, 0.0f, 1.0f), 25.0f, true, PAW_Color(255, 0, 255, 0));
	PAW_Circle s_cir2(PAW_Vector(120.0f, 90.0f + 50.0f + 40.0f, 0.0f, 1.0f), 15.0f, true, PAW_Color(255, 0, 0, 255));
	PAW_Circle s_cir3(PAW_Vector(120.0f, 90.0f + 50.0f + 40.0f + 30.0f, 0.0f, 1.0f), 20.0f, true, PAW_Color(255, 0, 255, 0));
	PAW_Circle s_cir4(PAW_Vector(120.0f, 90.0f + 50.0f + 40.0f + 30.0f, 0.0f, 1.0f), 10.0f, true, PAW_Color(255, 0, 0, 255));
	PAW_Circle s_cir5(PAW_Vector(120.0f, 90.0f + 50.0f + 40.0f + 30.0f + 30.0f, 0.0f, 1.0f), 20, true, PAW_Color(255, 0, 255, 0));
	PAW_Circle s_cir6(PAW_Vector(120.0f, 90.0f + 50.0f + 40.0f + 30.0f + 30.0f, 0.0f, 1.0f), 10, true, PAW_Color(255, 0, 0, 255));

	figure.push(big_cir1);
	figure.push(big_cir2);
	figure.push(mid_cir1);
	figure.push(mid_cir2);
	figure.push(s_cir1);
	figure.push(s_cir2);
	figure.push(s_cir3);
	figure.push(s_cir4);
	figure.push(s_cir5);
	figure.push(s_cir6);
}
