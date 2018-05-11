#pragma once
#include "PAW_Scene.h"

#include "main.h"
#include "stm32f4xx_hal.h"

#include "stm32f4xx_hal_ltdc.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"
#include "stm32f429i_discovery.h"

class PAW_Interface
{
private:
	uint32_t adress_of_layer, temp_adress;
	uint32_t *buffer;

public:
	PAW_Interface(const uint32_t n_adress_of_layer);
	~PAW_Interface();
	void load_buffer(const uint8_t numb);
	void set_color_buffer(const uint16_t numb);
	void save_buffer(const uint8_t numb);
	void get_pixels_from_scene(const PAW_Scene n_scene, const uint16_t number_of_buffer);
	void show_snap();
};
