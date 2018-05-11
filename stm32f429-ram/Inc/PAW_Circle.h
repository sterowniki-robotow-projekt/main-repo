#pragma once
#include "PAW_Primitive.h"
#include "PAW_Line.h"

class PAW_Circle: public PAW_Primitive
{
private:
	PAW_Vector center;
	float radius;

public:
	PAW_Circle(const PAW_Vector n_center, const float n_radius, bool n_filled, const PAW_Color n_color);
	virtual ~PAW_Circle();
	virtual void rotate(const PAW_Vector rotate_point, const int16_t degrees) final;
	virtual void translate(const PAW_Vector translation) final;
	virtual void show(const PAW_Color &background) const final;
	virtual uint32_t send_to_ram(const uint16_t x, const uint16_t y) const final;
	PAW_Vector g_center() const;
	float g_radius() const;
	PAW_Vector &g_center();
	float &g_radius();
	virtual void rotate_helper(const PAW_Matrix rotation_matrix) final;
	virtual void projection_helper(const PAW_Matrix projection_matrix) final;
	virtual void scale_helper(const float scale) final;

};
