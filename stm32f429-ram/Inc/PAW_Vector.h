#pragma once
#include <iostream>
#include "PAW_Math.h"

enum
{
	x = 0, y, z, w
};

class PAW_Vector
{
private:
	size_t size;
	float *data;

public:
	PAW_Vector();
	PAW_Vector(const size_t n_size);
	PAW_Vector(const float x, const float y);
	PAW_Vector(const float x, const float y, const float z);
	PAW_Vector(const float x, const float y, const float z,const float u);
	PAW_Vector(const PAW_Vector &n_vector);
	~PAW_Vector();
	size_t g_size() const;
	float g_data(const size_t index) const;
	void s_data(const size_t index, const float value);

	void randomize();

	float &operator[](const size_t index);
	float operator[](const size_t index) const;
	
	bool operator == (const PAW_Vector &second) const;
	bool operator != (const PAW_Vector &second) const;
	PAW_Vector operator + (const PAW_Vector &second) const;
	PAW_Vector operator - (const PAW_Vector &second) const;
	PAW_Vector operator - () const;
	PAW_Vector operator * (const float second) const;
	PAW_Vector operator / (const float second) const;
	PAW_Vector &operator = (const PAW_Vector &second);
	PAW_Vector &operator += (const PAW_Vector &second);
	PAW_Vector &operator -= (const PAW_Vector &second);
	PAW_Vector &operator *= (const float second);
	PAW_Vector &operator /= (const float second);

	bool is_small(const float precision = default_precision) const;
	bool is_finite() const;
	float length() const;
	PAW_Vector vertor(const float precision = default_precision) const;
	size_t r_size() const;
};

PAW_Vector relative_error(const PAW_Vector &a, const PAW_Vector &b, float precision = default_precision);
void swap(PAW_Vector &a, PAW_Vector &b);
PAW_Vector operator *(const float first, const PAW_Vector &second);
std::ostream &operator << (std::ostream &out, const PAW_Vector &temp);
