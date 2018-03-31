#ifndef PAW_MATRIX_H
#define PAW_MATRIX_H

#include "PAW_Vector.h"
#include <cstdlib>
#include <cmath>
#include <random>
#include <iostream>
#include <ctime>
#include <type_traits>
#include <typeinfo>

/********************/
/*                  */
/*   CLASS MATRIX   */
/*                  */
/********************/

class PAW_Matrix
{
	friend class PAW_Matrix_specification;
	friend class PAW_Vector_specification;
	friend std::ostream& operator<<(std::ostream& out, const PAW_Matrix& m);

public:
	const float precision = default_precision;
	float* data;

	template <typename cm_float>
	struct accessor
	{
		using cm_float_ref_t = typename std::conditional<std::is_const<cm_float>::value, cm_float, cm_float&>::type;
		cm_float* data;
		char index1;

		cm_float_ref_t operator[](char index2) const
		{
			size_t x, y;
			if((*this).data == nullptr)
				std::cerr<<"'data' field of the queried object must be non-null"<<std::endl;
				//throw exception(exception::exception_type::is_null, "'data' field of the queried object must be non-null", 0);
			else if(index1 == 'x')
				x = 0;
			else if(index1 == 'y')
				x = 1;
			else if(index1 == 'z')
				x = 2;
			else if(index1 == 'u')
				x = 3;
			else
				std::cerr<<"Invalid index"<<std::endl;
				//throw exception(exception::exception_type::index_error, "Invalid index", index1);

			if(index2 == 'x')
				y = 0;
			else if(index2 == 'y')
				y = 1;
			else if(index2 == 'z')
				y = 2;
			else if(index2 == 'u')
				y = 3;
			else
				std::cerr<<"Invalid index"<<std::endl;
				//throw exception(exception::exception_type::index_error, "Invalid index", index2);

			return data[4 * x + y];
		}

		PAW_Vector column(void)
		{
			PAW_Vector v;
			size_t x;
			if(index1 == 'x')
				x = 0;
			else if(index1 == 'y')
				x = 1;
			else if(index1 == 'z')
				x = 2;
			else if(index1 == 'u')
				x = 3;
			else
				throw exception(exception::exception_type::index_error, "Invalid index", index1);

			v['x'] = data[x + 4 * 0];
			v['y'] = data[x + 4 * 1];
			v['z'] = data[x + 4 * 2];
			v['u'] = data[x + 4 * 3];

			return v;
		}

		PAW_Vector row(void)
		{
			PAW_Vector v;
			size_t x;
			if(index1 == 'x')
				x = 0;
			else if(index1 == 'y')
				x = 1;
			else if(index1 == 'z')
				x = 2;
			else if(index1 == 'u')
				x = 3;
			else
				throw exception(exception::exception_type::index_error, "Invalid index", index1);

			v['x'] = data[3 * x + 0];
			v['y'] = data[3 * x + 1];
			v['z'] = data[3 * x + 2];
      v['u'] = data[4 * x + 3];
			return v;
		}
	};

public:
	PAW_Matrix(void)
	    : data(new float[16])
	{
		for(size_t i = 0; i < 16; i++)
			data[i] = 0.0;
	}

	PAW_Matrix(float xx, float xy, float xz, float xu, float yx, float yy, float yz, float yu, float zx, float zy, float zz, float zu, float ux, float uy, float uz, float uu)
	    : data(new float[16])
	{
		data[0] = xx;
		data[1] = xy;
		data[2] = xz;
		data[3] = xu;
		data[4] = yx;
		data[5] = yy;
		data[6] = yz;
		data[7] = yu;
		data[8] = zx;
		data[9] = zy;
		data[10] = zz;
		data[11] = zu;
		data[12] = ux;
		data[13] = uy;
		data[14] = uz;
		data[15] = uu;
	}

	PAW_Matrix(const PAW_Matrix& copy)
	    : data(new float[16])
	{
		for(size_t i = 0; i < 16; i++)
			data[i] = copy.data[i];
	}

	PAW_Matrix(PAW_Matrix&& move)
	    : data(move.data)
	{
		move.data = nullptr;
	}

	~PAW_Matrix(void)
	{
		if(data)
			delete[] data;
	}

	static PAW_Matrix zero(void)
	{
		return PAW_Matrix();
	}

	static PAW_Matrix unit(void)
	{
		return PAW_Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}

	static PAW_Matrix random(void)
	{
		srand(time(NULL));
		int m = rand();
		if(m % 2 == 0)
		{
			return PAW_Matrix(my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random(), my_random());
		}
		else
		{
			int k = rand() % 4;
			int l = rand() % 4;
			PAW_Matrix m;
			for(auto const i : index_tab)
			{
				for(auto const j : index_tab)
				{
					if(i == l && j == k)
						m[i][j] = (1.0 / 0.0);
					else
						m[i][j] = my_random();
				}
			}
			return m;
		}
	}

	static PAW_Matrix diagonal(const PAW_Vector& vector)
	{
		return PAW_Matrix(vector['x'], 0, 0, 0, 0, vector['y'], 0, 0, 0, 0, vector['z'], 0, 0, 0, 0, vector['u']);
	}

	accessor<float> operator[](char index)
	{
		if((*this).data == nullptr)
			std::cerr<<"'data' field of the queried object must be non-null"<<std::endl;
			//throw exception(exception::exception_type::is_null, "'data' field of the queried object must be non-null", 0);
		return accessor<float>{.data = data, .index1 = index};
	}

	accessor<const float> operator[](char index) const
	{
		if((*this).data == nullptr)
			std::cerr<<"'data' field of the queried object must be non-null"<<std::endl;
			//throw exception(exception::exception_type::is_null, "'data' field of the queried object must be non-null", 0);
		return accessor<const float>{.data = data, .index1 = index};
	}

	PAW_Matrix operator+(const PAW_Matrix& that) const
	{
    PAW_Matrix temp;
    for(auto const i: index_tab)
    for(auto const j: index_tab)
    {
      temp[i][j] = (*this)[i][j] + that[i][j];
    }
    return temp;
	}

	PAW_Matrix operator-(const PAW_Matrix& that) const
	{
    PAW_Matrix temp;
    for(auto const i: index_tab)
    for(auto const j: index_tab)
    {
      temp[i][j] = (*this)[i][j] - that[i][j];
    }
    return temp;	}

	PAW_Matrix operator-(void) const
	{
    PAW_Matrix temp;
    for(auto const i: index_tab)
    for(auto const j: index_tab)
    {
      temp[i][j] = (-1) * (*this)[i][j];
    }
    return temp;	}

	PAW_Matrix operator*(float that) const
	{
      PAW_Matrix temp;
      for(auto const i: index_tab)
      for(auto const j: index_tab)
      {
        temp[i][j] = (*this)[i][j] * that;
      }
      return temp;
		}

	PAW_Matrix operator/(float that) const
	{
      PAW_Matrix temp;
      for(auto const i: index_tab)
      for(auto const j: index_tab)
      {
        temp[i][j] = (*this)[i][j] / that;
      }
      return temp;
	}

	PAW_Vector operator*(const PAW_Vector& that) const
	{
    PAW_Vector temp;
    for(auto const i: index_tab)
    for(auto const j: index_tab)
    {
      temp[i] += (*this)[i][j] * that[j];
    }
    return temp;
	}

	// MULTIPLICATION
	PAW_Matrix operator*(const PAW_Matrix& that) const
	{
		PAW_Matrix result;

		for(auto const i : index_tab)
		{
			for(auto const j : index_tab)
			{
				float temp = 0;
				for(auto const k : index_tab)
				{
					temp += (*this)[i][k] * that[k][j];
				}
				result[i][j] = temp;
			}
		}
		return result;
	}

	// ASSIGNMENT
	PAW_Matrix& operator=(const PAW_Matrix& that)
	{
		for(auto const i : index_tab)
			for(auto const j : index_tab)
				(*this)[i][j] = that[i][j];

		return *this;
	}

	// MOVE ASSIGNMENT
	PAW_Matrix& operator=(PAW_Matrix&& that)
	{
		this->~PAW_Matrix();
		(*this).data = that.data;
		that.data = nullptr;
		return *this;
	}

	// ADDITION ASSIGNMENT
	PAW_Matrix& operator+=(const PAW_Matrix& that)
	{
		for(auto const i : index_tab)
			for(auto const j : index_tab)
				(*this)[i][j] += that[i][j];

		return (*this);
	}

	// SUBTRACTION ASSIGNMENT
	PAW_Matrix& operator-=(const PAW_Matrix& that)
	{
		for(auto const i : index_tab)
			for(auto const j : index_tab)
				(*this)[i][j] -= that[i][j];

		return (*this);
	}

	// MULTIPLICATION ASSIGNMENT
	PAW_Matrix& operator*=(float that)
	{
		for(auto const i : index_tab)
			for(auto j : index_tab)
				(*this)[i][j] *= that;

		return (*this);
	}

	// DIVIDE ASSIGNMENT
	PAW_Matrix& operator/=(float that)
	{
		for(auto const i : index_tab)
			for(auto const j : index_tab)
				(*this)[i][j] /= that;

		return (*this);
	}

	// OPERATOR EQUALITY
	bool operator==(const PAW_Matrix& that) const
	{
		bool success = true;

		for(size_t i = 0; i < 16; i++)
			success &= ((*this).data[i] == that.data[i]);

		return success;
	}

	// OPERATOR INEQUALITY
	bool operator!=(const PAW_Matrix& that) const
	{
		bool success = true;

		for(size_t i = 0; i < 16; i++)
			success &= (*this).data[i] == that.data[i];

		return !success;
	}

	PAW_Matrix givens(const char i, const char j) const
	{

		PAW_Matrix result = unit();

		if(abs((*this)[i][j]) < precision )
			return result;
		else
		{
			const float r = hypot((*this)[i][i], (*this)[j][i]);
			const float c = (*this)[i][i] / r;
			const float s = (*this)[j][i] / r;

			result[i][i] = c;
			result[i][j] = s;
			result[j][i] = -s;
			result[j][j] = c;

			return result;
		}
	}

	PAW_Matrix make_rotation(const char i, const char j, const float deg)
	{
		PAW_Matrix result = unit();
		float radians = deg*3.141592/360;
		//if(abs((*this)[i][j]) < precision )
		//	return result;
		//else
		//{
			result[i][i] = cos(radians);
			result[i][j] = sin(radians);
			result[j][i] = -sin(radians);
			result[j][j] = cos(radians);

			return result;
		//}
	}

	static inline PAW_Matrix relative_error(const PAW_Matrix& a, const PAW_Matrix& b, float precision = default_precision)
	{
		PAW_Matrix result;
		for(auto const i : index_tab)
			for(auto const j : index_tab)
			{
				result[i][j] =  relative_error_float(a[i][j], b[i][j], precision);
			}
			return result;
	}

};

// MULTIPLICATION SCALAR
PAW_Matrix operator*(float scalar, const PAW_Matrix& matrix)
{
	return matrix * scalar;
}

//PAW_Vector operator * (const PAW_Vector& vector, const PAW_Matrix& matrix);
PAW_Vector& operator*=(PAW_Vector& vector, const PAW_Matrix& matrix);

inline std::ostream& operator<<(std::ostream& out, const PAW_Matrix& m)
{
	if(m.data == nullptr)
		out << "{{ <null> }}";
	else
	{
		out << " {{ " << m['x']['x'] << " " << m['x']['y'] << " " << m['x']['z'] << " " << m['x']['u'] << " },\n";
		out << "  { " << m['y']['x'] << " " << m['y']['y'] << " " << m['y']['z'] << " " << m['y']['u'] <<" },\n";
		out << "  { " << m['z']['x'] << " " << m['z']['y'] << " " << m['z']['z'] << " " << m['z']['u'] <<" },\n ";
		out << "  { " << m['u']['x'] << " " << m['u']['y'] << " " << m['u']['z'] << " " << m['u']['u'] <<" }}";
	}
	return out;
}

#endif
