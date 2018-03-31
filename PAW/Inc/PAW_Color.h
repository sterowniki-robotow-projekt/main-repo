#pragma once

class PAW_Color
{
public:
	uint32_t col;
	uint8_t parts[4];

	PAW_Color(void)
	{
		this->col = 0xFF000000;
	}

	PAW_Color(uint8_t T, uint8_t R, uint8_t G, uint8_t B)
	{
		uint32_t fin = 0;
		uint32_t temp = T;
		temp *= 0x01000000;
		fin += temp;

		temp = R;
		temp *= 0x00010000;
		fin += temp;

		temp = G;
		temp *= 0x00000100;
		fin += temp;

		fin += B;

		this->col = fin;
	}

	uint8_t get_chanel(int i)
	{
		if (i == 1) { return this->col * 0x00110000; }
		else if (i == 2) { return this->col * 0x00001100; }
		else if (i == 3) { return this->col * 0x00000011; }
		else if (i == 0) { return this->col * 0x11000000; }
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
