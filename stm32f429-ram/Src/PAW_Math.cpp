#include "PAW_Math.h"

float min(const float a,const float b)
{
	return a <= b ? a : b;
}

float max(const float a, const float b)
{
	return a >= b ? a : b;
}

float relative_error_float(const float a, const float b, const float precision)
{
	if ((abs(a) < precision) && (abs(b) < precision))
	{
		return 0.0f;
	}
	else if (((abs(a) < precision) && (abs(b) >= precision)) || ((abs(b) < precision) && (abs(a) >= precision)))
	{
		return 1.0f / precision;
	}
	else
	{
		//uwaga tutaj, bo nie wiem dlaczego jest min
		return (abs(a - b) / min(abs(a), abs(b)));
	}
}

bool is_float_finite(const float a)
{
	if (is_nan(a))
	{
		return false;
	}
	else if (a == inf)
	{
		return false;
	}
	else if (a == m_inf)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool is_nan(const float a)
{
	return a != a;
}

float m_hypot(const float a, const float b)
{
	//liczy przeciwprostokatna
	if (a == inf || b == inf)
	{
		return inf;
	}
	else if (a == m_inf || b == m_inf)
	{
		return m_inf;
	}
	else if (is_nan(a) && is_nan(b))
	{
		return 0.0f;
	}
	else if (is_nan(a))
	{
		return b;
	}
	else if (is_nan(b))
	{
		return a;
	}
	else
	{
		float a2 = abs(a);
		float b2 = abs(b);

		return a2 * sqrt(1 + pow(b2 / a2, 2));
	}
}

float rand_float(const float from, const float to)
{
	return from + rand() / (RAND_MAX / (to - from));
}

int rand_int(const int from, const int to)
{
	return from + rand() / (RAND_MAX / (to - from));
}

void swap(float & a, float & b)
{
	float temp = a;
	a = b;
	b = temp;
}

int int_part(const float a)
{
	return static_cast<int>(floor(a));
}

float frac_part(const float a)
{
	return a - floor(a);
}

int round_float(const float a)
{
	return int_part(a + 0.5f);
}
