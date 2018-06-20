#pragma once
#include "PAW_Color.h"
#include "PAW_Primitive.h"
#include "PAW_Circle.h"
#include "PAW_Line.h"
#include "PAW_Point.h"

#include <vector>

class PAW_Figure
{
private:
	std::vector <PAW_Primitive *> form;
	static constexpr float left = -120.0f;
	static constexpr float right = 120.0f;
	static constexpr float top = 120.0f;
	static constexpr float bottom = -120.0f;
	static constexpr float near = 120.0f;
	static constexpr float far = -120.0f;

	PAW_Matrix generate_projection_matrix() const;
	void rotate_helper(PAW_Primitive * primi,  const PAW_Matrix projection_matrix);
	void projection_helper(PAW_Primitive * primi,  const PAW_Matrix projection_matrix);
	void scale_helper(PAW_Primitive * primi,  const float scale);

public:
	PAW_Figure();
	PAW_Figure(const std::vector <PAW_Primitive *> & n_form);
	~PAW_Figure();
	void push(const PAW_Line n_line);
	void push(const PAW_Circle n_circle);
	void push(const PAW_Point n_point);
	void show(const PAW_Color &background) const;
	void translate(const PAW_Vector n_translation);
	void rotate(const PAW_Vector rotate_point, const int16_t degrees);
	std::vector <PAW_Primitive*> g_form() const;
	std::vector <PAW_Primitive*> &g_form();

	void project3D_to_2D();
	void rotate3D(const float x_degrees, const float y_degrees, const float z_degrees);
	void scale3D(const float scale);
	void toCube(const float a_length, const PAW_Color a_color);
	void toPyramid(const float a_length, const PAW_Color a_color);
	void toCross(const float a_length, const PAW_Color a_color);
	void toExperimental(const float a_length, const PAW_Color a_color);

	void paint(const PAW_Line&, const PAW_Line&, const PAW_Color& );
};


