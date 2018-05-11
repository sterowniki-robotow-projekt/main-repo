#include "PAW_Primitive.h"

PAW_Primitive::PAW_Primitive(const bool n_filled, const PAW_Color n_color)
{
	is_filled = n_filled;
	color = n_color;
}

PAW_Primitive::~PAW_Primitive()
{
}

void PAW_Primitive::rotate(const PAW_Vector rotate_point, const int16_t degrees)
{

}

void PAW_Primitive::translate(const PAW_Vector translation)
{
}

void PAW_Primitive::show(const PAW_Color &background) const
{
}

void PAW_Primitive::rotate_helper(const PAW_Matrix rotation_matrix)
{

}
void PAW_Primitive::projection_helper(const PAW_Matrix projection_matrix)
{

}

void PAW_Primitive::scale_helper(const float scale)
{

}
uint32_t PAW_Primitive::send_to_ram(const uint16_t x, const uint16_t y) const
{
	return uint32_t();
}

void PAW_Primitive::s_color(const PAW_Color n_color)
{
	color = n_color;
}

PAW_Color PAW_Primitive::g_color() const
{
	return color;
}

bool PAW_Primitive::g_is_filled() const
{
	return is_filled;
}
