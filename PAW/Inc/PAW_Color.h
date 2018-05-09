#pragma once

class PAW_Color
{
public:
	uint32_t fullColor;
	uint8_t colorComponents[4];

	PAW_Color(void)
	{
		this->fullColor = 0xFF000000;
	}

	PAW_Color(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue)
	{
		uint32_t finalColor = 0;

		uint32_t temp = alpha;
		temp *= 0x01000000;
		finalColor += temp;

		temp = red;
		temp *= 0x00010000;
		finalColor += temp;

		temp = green;
		temp *= 0x00000100;
		finalColor += temp;

		finalColor += blue;

		this->fullColor = finalColor;
	}

	uint8_t get_chanel(int i)
	{
		if (i == 1) { return this->fullColor * 0x00110000; }
		else if (i == 2) { return this->fullColor * 0x00001100; }
		else if (i == 3) { return this->fullColor * 0x00000011; }
		else if (i == 0) { return this->fullColor * 0x11000000; }
		else return 0;
	}

	PAW_Color compose(PAW_Color c, float wage)
	{
		float w2 = 1.0 - wage;
		float temp[4];
		for(int i = 0; i < 4; i++)
			temp[i] = w2 * this->get_chanel(i) + wage * c.get_chanel(i);
		return PAW_Color(temp[0], temp[1], temp[2], temp[3]);
	}
};
