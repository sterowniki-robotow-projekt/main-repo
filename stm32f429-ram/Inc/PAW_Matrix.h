#pragma once
#include "PAW_Vector.h"

class PAW_Matrix : public PAW_Vector
{
private:
	size_t size2;
	PAW_Vector * data2;

public:
	PAW_Matrix(const size_t n_size);
	PAW_Matrix(const size_t n_size, const float diagonal_value);
	PAW_Matrix(const PAW_Matrix &n_matrix);
	~PAW_Matrix();
	float g_data(const size_t row, const size_t column) const;
	void s_data(const size_t row, const size_t column, const float value);
	size_t g_size() const;
	void randomize();
	void diagonal(const PAW_Vector &n_diagonal);

	PAW_Matrix operator +(const PAW_Matrix &second) const;
	PAW_Matrix operator -(const PAW_Matrix &second) const;
	PAW_Matrix operator -() const;
	PAW_Matrix operator *(const float second) const;
	PAW_Matrix operator /(const float second) const;
	PAW_Vector operator*(const PAW_Vector &second) const;
	PAW_Matrix operator*(const PAW_Matrix &second) const;
	PAW_Matrix inv() const;

	PAW_Matrix & operator = (const PAW_Matrix &second);
	PAW_Matrix & operator += (const PAW_Matrix &second);
	PAW_Matrix & operator -= (const PAW_Matrix &second);
	PAW_Matrix & operator *= (const float second);
	PAW_Matrix & operator /= (const float second);

	bool operator == (const PAW_Matrix &second) const;
	bool operator != (const PAW_Matrix &second) const;

	PAW_Vector operator [] (const size_t index) const;
	PAW_Vector &operator [] (const size_t index);

	void to_rotation_matrix(const size_t i, const size_t j, const float deg);
	PAW_Matrix givens(const size_t i, const size_t j, const float precision) const;
};

PAW_Matrix operator *(const float first, const PAW_Matrix &second);
std::ostream &operator <<(std::ostream & out, const PAW_Matrix &temp);
PAW_Matrix relative_error(const PAW_Matrix & a, const PAW_Matrix &b, const float precision = default_precision);
