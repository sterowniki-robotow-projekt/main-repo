#include "PAW_Color.h"

PAW_Color::PAW_Color()
{
	//set 255 alpha, 0 rgb
	channels[0] = 0xFF;
	for (uint8_t i = 1; i < 4; ++i)
	{
		channels[i] = 0x00;
	}

	for (uint8_t i = 0; i < 4; ++i)
	{
		color <<= 8;
		color += channels[i];
	}
}

PAW_Color::PAW_Color(const uint8_t alpha, const uint8_t red, const uint8_t green, const uint8_t blue)
{
	//set alpha, red, green, blue channels and combine channels to color
	channels[0] = alpha;
	channels[1] = red;
	channels[2] = green;
	channels[3] = blue;

	for (uint8_t i = 0; i < 4; ++i)
	{
		color <<= 8;
		color += channels[i];
	}
}


PAW_Color::~PAW_Color()
{
}

uint8_t PAW_Color::g_channel(const uint8_t index) const
{
	if (index < 4)
	{
		return channels[index];
	}
	else
	{
		return 0x00;
	}
}

uint32_t PAW_Color::g_value() const
{
	return color;
}

void PAW_Color::mix_color(const PAW_Color color2, const float importance2)
{
	const float importance = 1.0f - importance2;
	color = 0;

	for (uint8_t i = 0; i < 4; ++i)
	{
		channels[i] = static_cast<uint8_t>(channels[i] * importance + color2.g_channel(i) * importance2);
		color <<= 8;
		color += channels[i];
	}
}
