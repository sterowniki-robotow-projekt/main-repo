#include "PAW_Vector.h"

PAW_Vector::PAW_Vector():size(4), data(new float[4])
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i] = 0.0f;
	}
}

PAW_Vector::PAW_Vector(const size_t n_size) : size(n_size), data(new float[size])
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i] = 0.0f;
	}
}
PAW_Vector::PAW_Vector(const float x, const float y):size(2), data(new float[size])
{
	data[0] = x;
	data[1] = y;
}
PAW_Vector::PAW_Vector(const float x, const float y, const float z):size(3), data(new float[size])
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

PAW_Vector::PAW_Vector(const float x, const float y, const float z, const float u):size(4), data(new float[size])
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = u;
}

PAW_Vector::PAW_Vector(const PAW_Vector &n_vector): size(n_vector.g_size()), data(new float[size])
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i] = n_vector.g_data(i);
	}
}

PAW_Vector::~PAW_Vector()
{
	delete[] data;
}

size_t PAW_Vector::g_size() const
{
	return size;
}

float PAW_Vector::g_data(const size_t index) const
{
	if (index < size)
	{
		return data[index];
	}
	else
	{
		return 0.0f;
	}
}

void PAW_Vector::s_data(const size_t index, const float value)
{
	if (index < size)
	{
		data[index] = value;
	}
}

void PAW_Vector::randomize()
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i] = rand_float(0.0f, 255.0f);
	}
}

float & PAW_Vector::operator[](const size_t index)
{
	if (data == nullptr)
	{
		std::cerr << "Vector is not allocated" << std::endl;
	}
	else if (index >= 0 && index < size)
	{
		return data[index];
	}
	else
	{
		std::cerr << "Invalid index" << std::endl;
	}
}

float PAW_Vector::operator[](const size_t index) const
{
	if (data == nullptr)
	{
		std::cerr << "Vector is not allocated" << std::endl;
	}
	else if (index >= 0 && index < size)
	{
		return data[index];
	}
	else
	{
		std::cerr << "Invalid index" << std::endl;
	}

	return -1.0f;
}

bool PAW_Vector::operator==(const PAW_Vector & second) const
{
	if (size != second.g_size())
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (data[i] != second.g_data(i))
			{
				return false;
			}
		}
	}

	return true;
}

bool PAW_Vector::operator!=(const PAW_Vector & second) const
{
	if (size != second.g_size())
	{
		return true;
	}
	else
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (data[i] != second.g_data(i))
			{
				return true;
			}
		}
	}
	return false;
}

PAW_Vector PAW_Vector::operator+(const PAW_Vector & second) const
{
	if (size != second.g_size())
	{
		return PAW_Vector(0);
	}
	else
	{
		PAW_Vector r_value(size);

		for (size_t i = 0; i < size; ++i)
		{
			r_value.s_data(i, data[i] + second.g_data(i));
		}

		return r_value;
	}
}

PAW_Vector PAW_Vector::operator-(const PAW_Vector & second) const
{
	if (size != second.g_size())
	{
		return PAW_Vector(0);
	}
	else
	{
		PAW_Vector r_value(size);

		for (size_t i = 0; i < size; ++i)
		{
			r_value.s_data(i, data[i] - second.g_data(i));
		}

		return r_value;
	}
}

PAW_Vector PAW_Vector::operator-() const
{
	PAW_Vector r_value(size);

	for (size_t i = 0; i < size; ++i)
	{
		r_value.s_data(i, data[i] * -1.0f);
	}

	return r_value;
}

PAW_Vector PAW_Vector::operator*(const float second) const
{
	PAW_Vector r_value(size);

	for (size_t i = 0; i < size; ++i)
	{
		r_value.s_data(i, data[i] * second);
	}

	return r_value;
}

PAW_Vector PAW_Vector::operator/(const float second) const
{
	PAW_Vector r_value(size);

	for (size_t i = 0; i < size; ++i)
	{
		r_value.s_data(i, data[i] / second);
	}

	return r_value;
}

PAW_Vector & PAW_Vector::operator=(const PAW_Vector & second)
{
	delete[] data;
	size = second.g_size();
	data = new float[size];

	for (size_t i = 0; i < size; ++i)
	{
		data[i] = second.g_data(i);
	}
	
	return *this;
}

PAW_Vector & PAW_Vector::operator+=(const PAW_Vector & second)
{
	if (size == second.g_size())
	{
		for (size_t i = 0; i < size; ++i)
		{
			data[i] += second.g_data(i);
		}
	}

	return *this;
}

PAW_Vector & PAW_Vector::operator-=(const PAW_Vector & second)
{
	if (size == second.g_size())
	{
		for (size_t i = 0; i < size; ++i)
		{
			data[i] -= second.g_data(i);
		}
	}

	return *this;
}

PAW_Vector & PAW_Vector::operator*=(const float second)
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i] *= second;
	}

	return *this;
}

PAW_Vector & PAW_Vector::operator /= (const float second)
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i] /= second;
	}

	return *this;
}

bool PAW_Vector::is_small(const float precision) const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (abs(data[i]) >= precision)
		{
			return false;
		}
	}

	return true;
}

bool PAW_Vector::is_finite() const
{
	for (size_t i = 0; i < size; ++i)
	{
		if (!is_float_finite(data[i]))
		{
			return false;
		}
	}
	return true;
}

float PAW_Vector::length() const
{
	float r_value = 0.0f;

	for (size_t i = 0; i < size; ++i)
	{
		r_value += pow(data[i], 2);
	}

	return sqrt(r_value);
}

PAW_Vector PAW_Vector::vertor(const float precision) const
{
	if (is_small(precision))
	{
		return PAW_Vector(4);
	}
	else
	{
		return *this / this->length();
	}
}

size_t PAW_Vector::r_size() const
{
	return size;
}

PAW_Vector relative_error(const PAW_Vector & a, const PAW_Vector & b, const float precision)
{
	if (a.g_size() != b.g_size())
	{
		return PAW_Vector(0);
	}
	else
	{
		PAW_Vector r_value(a.g_size());

		for (size_t i = 0; i < r_value.g_size(); ++i)
		{
			r_value.s_data(i, relative_error_float(a.g_data(i), b.g_data(i), precision));
		}

		return r_value;
	}
}

void swap(PAW_Vector & a, PAW_Vector & b)
{
	PAW_Vector temp = a;
	a = b;
	b = temp;
}

PAW_Vector operator*(const float first, const PAW_Vector & second)
{
	return second * first;
}

std::ostream & operator<<(std::ostream & out, const PAW_Vector & temp)
{
	if (temp.g_size() > 0)
	{
		out << "[";
		for (size_t i = 0; i < temp.g_size(); ++i)
		{
			if (i != temp.g_size() - 1)
			{
				out << temp.g_data(i) << ", ";
			}
			else
			{
				out << temp.g_data(i) << "]\n";
			}
		}
	}
	return out;
}
