#pragma once
#include "PAW_Primitive.h"

class PAW_Point : public PAW_Primitive
{
private:
	PAW_Vector position;

public:
	PAW_Point(const PAW_Vector n_pos,const PAW_Color n_color);
	virtual	~PAW_Point();
	virtual void rotate(const PAW_Vector rotate_point,const int16_t degrees) final;
	virtual void translate(const PAW_Vector translation) final;
	virtual void show(const PAW_Color &background) const final;
	virtual uint32_t send_to_ram(const uint16_t x,const  uint16_t y) const final;
	PAW_Vector g_position() const;
	PAW_Vector &g_position();

	virtual void rotate_helper(const PAW_Matrix rotation_matrix) final;
		virtual void projection_helper(const PAW_Matrix projection_matrix) final;
		virtual void scale_helper(const float scale) final;
};

