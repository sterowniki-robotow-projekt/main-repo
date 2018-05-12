#include "PAW_Matrix.h"

PAW_Matrix::PAW_Matrix(const size_t n_size): size2(n_size), data2(new PAW_Vector[size2])
{

}

PAW_Matrix::PAW_Matrix(const size_t n_size, const float diagonal_value): size2(n_size), data2(new PAW_Vector[size2])
{
	for (size_t i = 0; i < size2; ++i)
	{
		for (size_t j = 0; j < size2; ++j)
		{
			if (i == j)
			{
				data2[i].s_data(j, diagonal_value);
			}
		}
	}
}

PAW_Matrix::PAW_Matrix(const PAW_Matrix & n_matrix) : size2(n_matrix.g_size()), data2(new PAW_Vector[size2])
{
	for (size_t i = 0; i < size2; ++i)
	{
		for (size_t j = 0; j < size2; ++j)
		{
			data2[i].s_data(j, n_matrix.g_data(i, j));
		}
	}
}

PAW_Matrix::~PAW_Matrix()
{
	delete[] data2;
}

float PAW_Matrix::g_data(const size_t row, const size_t column) const
{
	return data2[row].g_data(column);
}

void PAW_Matrix::s_data(const size_t row, const size_t column, const float value)
{
	data2[row].s_data(column, value);
}

size_t PAW_Matrix::g_size() const
{
	return size2;
}

void PAW_Matrix::randomize()
{
	for (size_t i = 0; i < size2; ++i)
	{
		for (size_t j = 0; j < size2; ++j)
		{
			data2[i].s_data(j, rand_float(0.0f, 255.0f));
		}
	}
}

void PAW_Matrix::diagonal(const PAW_Vector & n_diagonal)
{
	for (size_t i = 0; i < size2; ++i)
	{
		for (size_t j = 0; j < size2; ++j)
		{
			if (i == j)
			{
				data2[i].s_data(j, n_diagonal.g_data(i));
			}
		}
	}
}

PAW_Matrix PAW_Matrix::operator+(const PAW_Matrix & second) const
{
	if (size2 != second.g_size())
	{
		return PAW_Matrix(0);
	}
	else
	{
		PAW_Matrix r_value(size2);

		for (size_t i = 0; i < size2; ++i)
		{
			for (size_t j = 0; j < size2; ++j)
			{
				r_value.s_data(i, j, data2[i].g_data(j) + second.g_data(i, j));
			}
		}
		return r_value;
	}
}

PAW_Matrix PAW_Matrix::operator-(const PAW_Matrix & second) const
{
	if (size2 != second.g_size())
	{
		return PAW_Matrix(0);
	}
	else
	{
		PAW_Matrix r_value(size2);

		for (size_t i = 0; i < size2; ++i)
		{
			for (size_t j = 0; j < size2; ++j)
			{
				r_value.s_data(i, j, data2[i].g_data(j) - second.g_data(i, j));
			}
		}
		return r_value;
	}
}

PAW_Matrix PAW_Matrix::operator-() const
{
	PAW_Matrix r_value(size2);

	for (size_t i = 0; i < size2; ++i)
	{
		for (size_t j = 0; j < size2; ++j)
		{
			r_value.s_data(i, j, data2[i].g_data(j) *-1.0f);
		}
	}

	return r_value;
}

PAW_Matrix PAW_Matrix::operator*(const float second) const
{
	PAW_Matrix r_value(size2);

	for (size_t i = 0; i < size2; ++i)
	{
		for (size_t j = 0; j < size2; ++j)
		{
			r_value.s_data(i, j, data2[i].g_data(j) * second);
		}
	}
	return r_value;
}

PAW_Matrix PAW_Matrix::operator/(const float second) const
{
	PAW_Matrix r_value(size2);

	for (size_t i = 0; i < size2; ++i)
	{
		for (size_t j = 0; j < size2; ++j)
		{
			r_value.s_data(i, j, data2[i].g_data(j) / second);
		}
	}
	return r_value;
}

PAW_Vector PAW_Matrix::operator*(const PAW_Vector & second) const
{
	if (size2 != second.g_size())
	{
		return PAW_Vector(0);
	}
	else
	{
		PAW_Vector r_value(size2);

		for (size_t i = 0; i < size2; ++i)
		{
			for (size_t j = 0; j < size2; ++j)
			{
				r_value.s_data(i, r_value.g_data(i) + data2[i].g_data(j) * second.g_data(j));
			}
		}
		return r_value;
	}
}

PAW_Matrix PAW_Matrix::operator*(const PAW_Matrix & second) const
{
	if (size2 != second.g_size())
	{
		return PAW_Matrix(0);
	}
	else
	{
		PAW_Matrix r_value(size2);

		for (size_t i = 0; i < size2; ++i)
		{
			for (size_t j = 0; j < size2; ++j)
			{
				float temp = 0.0f;
				for (size_t a = 0; a < size2; ++a)
				{
					temp += data2[i].g_data(a) * second.g_data(a, j);
				}
				r_value.s_data(i, j, temp);
			}
		}
		return r_value;
	}
}

PAW_Matrix PAW_Matrix::inv() const
{
	double inv[16], det, m[16];

	for (size_t i = 0, j = 0; i < 16; ++i)
	{
		if ((i + 1) % 5 == 0)
		{
			++j;
		}
		m[i] = data2[j][i % 4];

	}

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;
	/*
	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;
		*/

	PAW_Matrix r_value(4);

	for (size_t i = 0, j=0; i < 16; ++i)
	{
		if ((i + 1) % 5 == 0)
		{
			++j;
		}
		r_value[j][i % 4] = inv[i] * det;
	}
	return r_value;
}


PAW_Matrix & PAW_Matrix::operator=(const PAW_Matrix & second)
{
	delete[] data2;
	size2 = second.g_size();
	data2 = new PAW_Vector[size2];

	for (size_t i = 0; i < size2; ++i)
	{
		for (size_t j = 0; j < size2; ++j)
		{
			data2[i].s_data(j, second.g_data(i, j));
		}
	}

	return *this;
}

PAW_Matrix & PAW_Matrix::operator+=(const PAW_Matrix & second)
{
	if (size2 == second.g_size())
	{
		for (size_t i = 0; i < size2; ++i)
		{
			for (size_t j = 0; j < size2; ++j)
			{
				data2[i].s_data(j,data2[i].g_data(j) + second.g_data(i, j));
			}
		}
	}

	return *this;
}

PAW_Matrix & PAW_Matrix::operator-=(const PAW_Matrix & second)
{
	if (size2 == second.g_size())
	{
		for (size_t i = 0; i < size2; ++i)
		{
			for (size_t j = 0; j < size2; ++j)
			{
				data2[i].s_data(j, data2[i].g_data(j) - second.g_data(i, j));
			}
		}
	}

	return *this;
}

PAW_Matrix & PAW_Matrix::operator*=(const float second)
{
		for (size_t i = 0; i < size2; ++i)
		{
			for (size_t j = 0; j < size2; ++j)
			{
				data2[i].s_data(j, data2[i].g_data(j) * second);
			}
		}

	return *this;
}

PAW_Matrix & PAW_Matrix::operator/=(const float second)
{
	for (size_t i = 0; i < size2; ++i)
	{
		for (size_t j = 0; j < size2; ++j)
		{
			data2[i].s_data(j, data2[i].g_data(j) / second);
		}
	}

	return *this;
}

bool PAW_Matrix::operator==(const PAW_Matrix & second) const
{
	if (size2 != second.g_size())
	{
		return false;
	}
	{
		for (size_t i = 0; i < size2; ++i)
		{
			for (size_t j = 0; j < size2; ++j)
			{
				if (data2[i].g_data(j) != second.g_data(i, j))
				{
					return false;
				}
			}
		}

		return true;
	}
}

bool PAW_Matrix::operator!=(const PAW_Matrix & second) const
{
	if (size2 != second.g_size())
	{
		return true;
	}
	else
	{
		for (size_t i = 0; i < size2; ++i)
		{
			for (size_t j = 0; j < size2; ++j)
			{
				if (data2[i].g_data(j) != second.g_data(i, j))
				{
					return true;
				}
			}
		}

		return false;
	}
}

PAW_Vector PAW_Matrix::operator[](const size_t index) const
{
	return data2[index];
}

PAW_Vector & PAW_Matrix::operator[](const size_t index)
{
	return data2[index];
}

PAW_Matrix PAW_Matrix::givens(const size_t i, const size_t j, const float precision) const
{
	PAW_Matrix r_value(4,1.0f);

	if(abs(data2[i].g_data(j))<precision)
	{
		return r_value;
	}
	else
	{
		const float r = hypot(data2[i].g_data(i),data2[j].g_data(j));
		const float c = data2[i].g_data(i)/r;
		const float s = data2[j].g_data(j)/r;

		r_value.s_data(i,i,c);
		r_value.s_data(i,j,s);
		r_value.s_data(j,i,-s);
		r_value.s_data(j,j,c);

		return r_value;
	}
}

void PAW_Matrix::to_rotation_matrix(const size_t i, const size_t j, const float deg)
{
	if (i >= 0 && i < size2 && j >= 0 && j < size2)
	{
		float rad = 3.1415f * deg / 180.0f;
		PAW_Matrix r_value(size2, 1.0f);

		r_value.s_data(i, i, cos(rad));
		r_value.s_data(i, j, sin(rad));
		r_value.s_data(j, i, -sin(rad));
		r_value.s_data(j, j, cos(rad));

		for (size_t k = 0; k < size2; ++k)
		{
			for (size_t l = 0; l < size2; ++l)
			{
				data2[k].s_data(l, r_value.g_data(k, l));
			}
		}
	}
}

PAW_Matrix operator*(const float first, const PAW_Matrix & second)
{
	return second * first;
}

std::ostream & operator<<(std::ostream & out, const PAW_Matrix & temp)
{
	if (temp.g_size() > 0)
	{
		for (size_t i = 0; i < temp.g_size(); ++i)
		{
			std::cout << "{ ";
			for (size_t j = 0; j < temp.g_size(); ++j)
			{
				if (j != temp.g_size() - 1)
				{
					std::cout << temp.g_data(i, j) << "| ";
				}
				else
				{
					std::cout << temp.g_data(i, j);
				}
			}
			std::cout << "}\n";
		}
	}
	return out;
}

PAW_Matrix relative_error(const PAW_Matrix & a, const PAW_Matrix & b, const float precision)
{
	if (a.g_size() != b.g_size())
	{
		return PAW_Matrix(1);
	}
	else
	{
		PAW_Matrix r_value(a.g_size());

		for (size_t i = 0; i < r_value.g_size(); ++i)
		{
			for (size_t j = 0; j < r_value.g_size(); ++j)
			{
				r_value.s_data(i, j, relative_error_float(a.g_data(i, j), b.g_data(i, j), precision));
			}
		}
		return r_value;
	}
}
