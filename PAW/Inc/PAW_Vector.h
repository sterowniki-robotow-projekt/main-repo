#ifndef PAW_VECTOR_H
#define PAW_VECTOR_H

#include <cstdlib>
#include <cmath>
#include <random>
#include <iostream>
#include <ctime>

char index_tab[4] = {'x', 'y', 'z', 'u'};

static const float _inf = (1.0 / 0.0);
static const float _m_inf = (-1.0 / 0.0);

constexpr float default_precision = 0.0000005;
constexpr size_t tests_number = 1000;

inline float min(float x, float y)
{
	if(x <= y)
		return x;
	else
		return y;
}

inline float max(float x, float y)
{
	if(x >= y)
		return x;
	else
		return y;
}

float relative_error_float(float x, float y, float precision)
{
	if((abs(x) < precision) && (abs(y) < precision))
		return 0;
	else if(((abs(x) < precision) && (abs(y) >= precision)) || ((abs(y) < precision) && (abs(x) >= precision)))
		return 1 / precision;
	else
		return (abs(x - y) / min(abs(x), abs(y)));
}

inline bool is_scalar_finite(float m)
{
	bool success = true;
	success &= (m == m);//czy jest nan?
	success &= !(_inf == m);//czy jest inf?
	success &= !(-_inf == m);
	return success;
}

inline bool is_scalar_nan(float m)
{
		return !(m == m);
}

inline float hypot(float x, float y, float precision = default_precision)
{
	if(x == _inf || y == _inf)
		return _inf;
	else if(is_scalar_nan(x) && is_scalar_nan(y))
		return 0;
	else if(is_scalar_nan(x))
		return y;
	else if(is_scalar_nan(y))
		return x;
	else
	{
		float t;
		x = abs(x);
		y = abs(y);
		if(x <= y)
		{
			t = x;
			x = y;
		}
		else
			t = y;

		t /= x;
		float result = x * sqrt(1 + (t * t));
		////assert(!((x != _inf) && (y != _inf)) || ((result != _inf) && (result != (_inf/_inf))), "hypot is infinite or zero"); //sprawdza, czy dla danych nie bedących infem wynik nie jest infem lub nanem
		return result;
	}
}

float my_random(void)
{
	srand(time(NULL));
	return (((rand()/(RAND_MAX/2))-1)*255);

}

/* exceptions */

struct exception
{
	enum class exception_type : char
	{
		index_error,
		is_null,
		singular_matrix
	};
	exception_type type;
	const char* message;
	union
	{
		char index;
	};

	exception(exception::exception_type t, const char* text);
	exception(exception::exception_type t, const char* text, char id);
};

exception::exception(exception::exception_type t, const char* text)
{
	type = t;
	message = text;
}

exception::exception(exception::exception_type t, const char* text, char id)
{
	type = t;
	text = message;
	index = id;
}

inline std::ostream& operator<<(std::ostream& out, const exception& error)
{
	out << error.message << " ";
	switch(error.type)
	{
	case exception::exception_type::index_error:
		out << "'" << error.index << "' (" << ((int)error.index) << ")";
		break;
	case exception::exception_type::is_null:
		break;
	case exception::exception_type::singular_matrix:
		break;
	}
	return out;
}


inline int int_rand(void)
{
	static int a = 99;
	a = (1337 * a + 103) % 2048;
	return a;
}


/****************/
/*              */
/* CLASS VECTOR */
/*              */
/****************/

class PAW_Vector
{
	friend class PAW_Vector_specification;
	friend class PAW_Matrix_specification;

	friend std::ostream& operator<<(std::ostream& out, const PAW_Vector& vector);

public:
	float* data;

	PAW_Vector(void)
	    : data(new float[4])
	{
		for(size_t i = 0; i < 4; i++)
			data[i] = 0.0;
	}

	PAW_Vector(float x, float y, float z, float u)
	    : data(new float[4])
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = u;
	}

	PAW_Vector(const PAW_Vector& copy)
	    : data(new float[4])
	{
		for(size_t i = 0; i < 4; i++)
			data[i] = copy.data[i];
	}

	~PAW_Vector(void)
	{
		if(data)
			delete[] data;
	}

	static PAW_Vector zero(void)
	{
		return PAW_Vector();
	}

	static PAW_Vector random(void)
	{
		return PAW_Vector(my_random(), my_random(), my_random(), my_random());
	}

	float& operator[](char index)
	{
		if((*this).data == nullptr)
			std::cerr<<"'data' field of the queried object must be non-null"<<std::endl;
			//throw exception(exception::exception_type::is_null, "'data' field of the queried object must be non-null", 0);
		else if(index == 'x')
			return data[0];
		else if(index == 'y')
			return data[1];
		else if(index == 'z')
			return data[2];
		else if(index == 'u')
			return data[3];
		else
			std::cerr<<"Invalid index"<<std::endl;
			//throw exception(exception::exception_type::index_error, "Invalid index", index);

	}

	float operator[](char index) const
	{
		if((*this).data == nullptr)
			std::cerr<<"'data' field of the queried object must be non-null"<<std::endl;
			//throw exception(exception::exception_type::is_null, "'data' field of the queried object must be non-null", 0);
		else if(index == 'x')
			return data[0];
		else if(index == 'y')
			return data[1];
		else if(index == 'z')
			return data[2];
		else if(index == 'u')
			return data[3];
		else
			std::cerr<<"Invalid index"<<std::endl;
			//throw exception(exception::exception_type::index_error, "Invalid index", index);
		return -1;
	}

	// OPERATOR EQUALITY
	bool operator==(const PAW_Vector& that) const
	{
		bool success = true;

		for(size_t i = 0; i < 4; i++)
			success &= ((*this).data[i] == that.data[i]);

		return success;
	}

	// OPERATOR INEQUALITY
	bool operator!=(const PAW_Vector& that) const
	{
		bool success = true;

		for(size_t i = 0; i < 4; i++)
			success &= (*this).data[i] == that.data[i];

		return !success;
	}

	// ADDITION
	PAW_Vector operator+(const PAW_Vector& that) const
	{
		return PAW_Vector((*this)['x'] + that['x'], (*this)['y'] + that['y'], (*this)['z'] + that['z'], 1);
	}

	// SUBTRACTION VECTOR VECTOR
	PAW_Vector operator-(const PAW_Vector& that) const
	{
		return PAW_Vector((*this)['x'] - that['x'], (*this)['y'] - that['y'], (*this)['z'] - that['z'], 1);
	}

	// AVERSE VECTOR
	PAW_Vector operator-(void) const
	{
		return PAW_Vector(-((*this)['x']), -((*this)['y']), -((*this)['z']), ((*this)['u']));
	}

	// MULTIPLICATION SCALAR
	PAW_Vector operator*(float that) const
	{
		return PAW_Vector((*this)['x'] * that, (*this)['y'] * that, (*this)['z'] * that, (*this)['u'] * that);
	}

	// DIVIDED BY SCALAR
	PAW_Vector operator/(float that) const
	{
		return PAW_Vector((*this)['x'] / that, (*this)['y'] / that, (*this)['z'] / that, (*this)['u'] / that);
	}

	// DOT PRODUCT
	float operator*(const PAW_Vector& that) const
	{
		return (((*this)['x'] * that['x']) + ((*this)['y'] * that['y']) + ((*this)['z'] * that['z']) + ((*this)['u'] * that['u']));
	}

	// ASSIGNMENT
	PAW_Vector& operator=(const PAW_Vector& that)
	{
		//for(auto const i : {'x', 'y', 'z', 'u'})
		for(auto const i : index_tab)
			(*this)[i] = that[i];

		return *this;
	}

	// MOVE ASSIGNMENT
	PAW_Vector& operator=(PAW_Vector&& that)
	{
		this->~PAW_Vector();
		(*this).data = that.data;
		that.data = nullptr;
		return *this;
	}

	// ADDITION ASSIGNMENT
	PAW_Vector& operator+=(const PAW_Vector& that)
	{
		for(auto const i : index_tab)
			(*this)[i] += that[i];

		return (*this);
	}

	// SUBTRACTION ASSIGNMENT
	PAW_Vector& operator-=(const PAW_Vector& that)
	{
		for(auto const i : index_tab)
			(*this)[i] -= that[i];

		return (*this);
	}

	// MULTIPLICATION ASSIGNMENT
	PAW_Vector& operator*=(float that)
	{
		for(auto const i : index_tab)
			(*this)[i] *= that;

		return (*this);
	}

	// DIVIDE ASSIGNMENT
	PAW_Vector& operator/=(float that)
	{
		for(auto const i : index_tab)
			(*this)[i] /= that;

		return (*this);
	}

	// RELATIVE ERROR
	static PAW_Vector relative_error(const PAW_Vector& v, const PAW_Vector& w, float precision = default_precision)
	{
		return PAW_Vector(relative_error_float(v['x'], w['x'], precision),  relative_error_float(v['y'], w['y'], precision),  relative_error_float(v['z'], w['z'], precision),  relative_error_float(v['u'], w['u'], precision));
	}

	//IS SMALL
	bool is_small(float precision = default_precision) const
	{
		return (abs((*this)['x']) < precision) && (abs((*this)['y']) < precision) && (abs((*this)['z']) < precision) && (abs((*this)['u']) < precision);
	}

	float len(void) const
	{
		return sqrt(((*this)['x'] * (*this)['x']) + ((*this)['y'] * (*this)['y']) + ((*this)['z'] * (*this)['z']) + ((*this)['u'] * (*this)['u']));
	}

	PAW_Vector vertor(float precision = default_precision) const
	{
		if(this->is_small(precision))
			return PAW_Vector(0, 0, 0, 0);

		float size = this->len();
		return ((*this) * (1 / size));
	}

	static void swap(PAW_Vector& a, PAW_Vector& b)
	{
		PAW_Vector temp = a;
		a = b;
		b = temp;
	}

	bool is_finite() const
	{
		PAW_Vector x = *this;
		bool success = true;

		for(auto const i : index_tab)
		{
			success &= is_scalar_finite(x[i]);
		}
		return success;
	}

};

// MULTIPLICATION SCALAR
PAW_Vector operator*(float scalar, const PAW_Vector& vector)
{
	return vector * scalar;
}

// OPERATOR OUT
inline std::ostream& operator<<(std::ostream& out, const PAW_Vector& vector)
{
	if(vector.data == nullptr)
		out << "[ <null> ]";
	else
		out << "[" << vector['x'] << ", " << vector['y'] << ", " << vector['z'] << ", " << vector['u'] << "]";
	return out;
}

#endif
