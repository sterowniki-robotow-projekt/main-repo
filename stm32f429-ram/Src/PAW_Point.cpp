#include "PAW_Point.h"

PAW_Point::PAW_Point(const PAW_Vector n_position, const PAW_Color n_color) :
		PAW_Primitive(false, n_color), position(n_position)
{
}

PAW_Point::~PAW_Point()
{

}

void PAW_Point::rotate(const PAW_Vector rotate_point, const int16_t degrees)
{
	PAW_Matrix rotation_matrix(4);
	rotation_matrix.to_rotation_matrix(x, y, degrees);

	position = rotation_matrix * (position - rotate_point) + rotate_point;
}

void PAW_Point::translate(const PAW_Vector translation)
{
	position += translation;
}

void PAW_Point::show(const PAW_Color &background) const
{
	BSP_LCD_DrawPixel(position[x], position[y], color.g_value());
}

uint32_t PAW_Point::send_to_ram(const uint16_t x, const uint16_t y) const
{
	return uint32_t();
}

PAW_Vector PAW_Point::g_position() const
{
	return position;
}

PAW_Vector &PAW_Point::g_position()
{
	return position;
}

void PAW_Point::rotate_helper(const PAW_Matrix rotation_matrix)
{
	position[y] *= -1;
	position[z] *= -1;
	position = rotation_matrix * position;
	position[y] *= -1;
	position[z] *= -1;
}
void PAW_Point::projection_helper(const PAW_Matrix projection_matrix)
{
	position[y] *= -1;
	position[z] *= -1;
	position = projection_matrix * position;

}

void PAW_Point::scale_helper(const float scale)
{
	position *=scale;
}
