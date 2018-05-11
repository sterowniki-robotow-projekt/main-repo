#pragma once
#include "PAW_Primitive.h"

class PAW_Line : public PAW_Primitive
{
private:
	PAW_Vector begin, end;

public:
	PAW_Line(const PAW_Vector n_begin, const PAW_Vector n_end, const PAW_Color n_color);
	virtual	~PAW_Line();
	virtual void rotate(const PAW_Vector rotate_point, const int16_t degrees) final;
	virtual void translate(const PAW_Vector translation) final;
	virtual void show(const PAW_Color &background) const final;
	virtual uint32_t send_to_ram(const uint16_t x, const  uint16_t y) const final;
	PAW_Vector g_begin() const;
	PAW_Vector g_end() const;
	PAW_Vector & g_begin();
	PAW_Vector & g_end();

	virtual void rotate_helper(const PAW_Matrix rotation_matrix) final;
		virtual void projection_helper(const PAW_Matrix projection_matrix) final;
		virtual void scale_helper(const float scale) final;

};

