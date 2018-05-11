#pragma once
#include <iostream>

class PAW_Color
{
private:
	uint32_t color;
	uint8_t channels[4];

public:
	PAW_Color();
	PAW_Color(const uint8_t alpha,const uint8_t red,const uint8_t green, const uint8_t blue);
	~PAW_Color();
	uint8_t g_channel(const uint8_t index) const;
	uint32_t g_value() const;
	void mix_color(const PAW_Color color2, const float importance2);
};

