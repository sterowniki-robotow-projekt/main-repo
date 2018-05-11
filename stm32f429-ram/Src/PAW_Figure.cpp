#include "PAW_Figure.h"

PAW_Figure::PAW_Figure()
{
}

PAW_Figure::PAW_Figure(const std::vector<PAW_Primitive*>& n_form)
{
	form = n_form;
}

PAW_Figure::~PAW_Figure()
{
}

PAW_Matrix PAW_Figure::generate_projection_matrix() const
{
	PAW_Matrix projection_matrix(4);
	projection_matrix[0][0] = 2 * near / (right - left);
	projection_matrix[0][2] = (right + left) / (right - left);
	projection_matrix[1][1] = 2 * near / (top - bottom);
	projection_matrix[1][2] = (top + bottom) / (top - bottom);
	projection_matrix[2][2] = -(far + near) / (far - near);
	projection_matrix[2][3] = -2 * far * near / (far - near);
	return projection_matrix;
}


void PAW_Figure::rotate_helper(PAW_Primitive * primi,  const PAW_Matrix projection_matrix)
{
	primi->rotate_helper(projection_matrix);
}
void PAW_Figure::projection_helper(PAW_Primitive * primi,  const PAW_Matrix projection_matrix)
{
	primi->projection_helper(projection_matrix);
}

void PAW_Figure::scale_helper(PAW_Primitive * primi,  const float scale)
{
	primi->scale_helper(scale);
}

void PAW_Figure::push(const PAW_Line n_line)
{
	form.push_back(new PAW_Line(n_line.g_begin(), n_line.g_end(), n_line.g_color()));
}

void PAW_Figure::push(const PAW_Circle n_circle)
{
	form.push_back(new PAW_Circle(n_circle.g_center(), n_circle.g_radius(), n_circle.g_is_filled(), n_circle.g_color()));
}

void PAW_Figure::push(const PAW_Point n_point)
{
	form.push_back(new PAW_Point(n_point.g_position(), n_point.g_color()));
}

void PAW_Figure::show(const PAW_Color &background) const
{
	for (size_t i = 0; i < form.size(); ++i)
	{
		form[i]->show(background);
	}
}

void PAW_Figure::translate(const PAW_Vector n_translation)
{
	for (size_t i = 0; i < form.size(); ++i)
	{
		form[i]->translate(n_translation);
	}
}

void PAW_Figure::rotate(const PAW_Vector rotate_point, const int16_t degrees)
{
	for (size_t i = 0; i < form.size(); ++i)
	{
		form[i]->rotate(rotate_point, degrees);
	}
}

std::vector<PAW_Primitive*> PAW_Figure::g_form() const
{
	return form;
}

std::vector<PAW_Primitive*> &PAW_Figure::g_form()
{
	return form;
}

void PAW_Figure::project3D_to_2D()
{
	PAW_Matrix P(4);
	P = generate_projection_matrix();

	for (size_t i = 0; i < form.size(); ++i)
	{
		projection_helper(form[i], P);
	}

	translate(PAW_Vector(540.0f, 290.0f, 0.0f, 0.0f));

}

void PAW_Figure::rotate3D(const float x_degrees, const float y_degrees, const float z_degrees)
{
	PAW_Matrix Rx(4), Ry(4), Rz(4), R(4);
	Rx.to_rotation_matrix(y, z, 2 * x_degrees);
	Ry.to_rotation_matrix(z, x, 2 * y_degrees);
	Rz.to_rotation_matrix(y, x, 2 * z_degrees);

	R = Rz * Ry * Rx;
	for (size_t i = 0; i < form.size(); ++i)
	{
		rotate_helper(form[i], R);
	}
}

void PAW_Figure::scale3D(const float scale)
{
	for (size_t i = 0; i < form.size(); ++i)
		{
			scale_helper(form[i], 0.5f);
		}
}
