#include "PAW_Interface.h"

PAW_Interface::PAW_Interface(const uint32_t n_adress_of_layer): adress_of_layer(n_adress_of_layer), temp_adress(0), buffer(new uint32_t[256])
{
}

PAW_Interface::~PAW_Interface()
{
	delete[] buffer;
}

void PAW_Interface::set_color_buffer(const uint16_t numb)
{
	for (uint16_t i = 0; i < 256; ++i)
	{
		buffer[i] = 0xFF000000 +0x00100000*numb + 0x00000001*i + 0x00000100*(255-i);
	}
}

void PAW_Interface::get_pixels_from_scene(const PAW_Scene n_scene, const uint16_t number_of_buffer)
{
	uint32_t result = 0;

	//if sucks watch out
	for(size_t i = 264; i>=0; --i)
	{
		buffer[i] = n_scene.g_background().g_value();
	}


	for (size_t xx = n_scene.g_figs().size(); xx>= 0; --xx)
	{
		for (size_t yy = n_scene.g_figs()[xx].g_form().size(); yy >= 0; --yy)
		{
			for (uint16_t i = 0; i < 16; ++i)
			{
				for (uint16_t j = 0; j < 16; ++j)
				{
					result = n_scene.g_figs()[xx].g_form()[yy]->send_to_ram(i, j);
					if (result - n_scene.g_background().g_value())
					{
						buffer[i * 16 + j] = result;
					}
				}
			}
		}
	}
}

void PAW_Interface::show_snap()
{
	for (uint16_t k = 0; k < 15; ++k)
	{
		set_color_buffer(k);
		for (uint16_t l = 0; l < 20; ++l)
		{
			save_buffer(l + k * 20);
			load_buffer(l + k * 20);
			for (uint16_t i = 0; i < 16; ++i)
			{
				for (uint16_t j = 0; j < 16; ++j)
				{
					BSP_LCD_DrawPixel(k * 16 + i, l * 16 + j, buffer[i * 16 + j]);
				}
			}
		}
	}
}
