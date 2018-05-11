#pragma once
#include "PAW_Matrix.h"
#include "PAW_Color.h"

#include "main.h"
#include "stm32f4xx_hal.h"

#include "stm32f4xx_hal_ltdc.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"
#include "stm32f429i_discovery.h"

class PAW_Primitive
{
protected:
	PAW_Color color;
	bool is_filled;

public:
	PAW_Primitive(const bool n_filled,const PAW_Color n_color);
	virtual	~PAW_Primitive();
	virtual void rotate(const PAW_Vector rotate_point,const int16_t degrees);
	virtual void translate(const PAW_Vector translation);
	virtual void show(const PAW_Color &background) const;
	virtual uint32_t send_to_ram(const uint16_t x,const  uint16_t y) const;
	virtual void rotate_helper(const PAW_Matrix rotation_matrix);
	virtual void projection_helper(const PAW_Matrix projection_matrix);
	virtual void scale_helper(const float scale);
	void s_color(const PAW_Color n_color);
	PAW_Color g_color() const;
	bool g_is_filled() const;
};
