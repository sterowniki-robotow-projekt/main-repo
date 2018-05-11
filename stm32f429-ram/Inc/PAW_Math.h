#pragma once

#include <cmath>
#include <limits>
#include <cstdlib>

const float inf = std::numeric_limits<float>::infinity();
const float m_inf = inf * -1;

const float default_precision = 5e-7f;
const int test_number = 1000;

float min(const float a,const float b);
float max(const float a, const float b);

float relative_error_float(const float a, const float b, const float precision);

bool is_float_finite(const float a);
bool is_nan(const float a);
float m_hypot(const float a, const float b);
float rand_float(const float from, const float to);
int rand_int(const int from, const int to);

void swap(float &a, float &b);
int int_part(const float a);
float frac_part(const float a);
int round_float(const float a);
