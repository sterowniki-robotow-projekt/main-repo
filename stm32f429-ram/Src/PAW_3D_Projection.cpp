#include "PAW_3D_Projection.h"

PAW_Vector project_3D_to_2D(const PAW_Vector point_position)
{

		PAW_Vector r_value(4);
		PAW_Matrix P(4);
		P = projection_matrix(0.0f, 239.0f, 0.0f, 319.0f, 160.0f, 0.0f);
		PAW_Matrix Rx(4, 1.0f), Ry(4, 1.0f), Rz(4, 1.0f), Rx2(4, 1.0f);

		Rx.to_rotation_matrix(y, z, 0 * 0.0f); //x rot
		Ry.to_rotation_matrix(z, x, 2 * 0.0f); //y rot
		Rz.to_rotation_matrix(y, x, 2 * 90.0f); //z rot
		Rx2.to_rotation_matrix(y, z, 2 * 0.0f); //x rot

		PAW_Vector point_position2;
		point_position2 = point_position;
		point_position2[y] *= -1;
		point_position2[z] *= -1;
		r_value = Rz * point_position2;
		point_position2[y] *= -1;
		point_position2[z] *= -1;
		point_position2[y] *= -1;
		point_position2[z] *= -1;
		r_value = P * r_value;

		r_value += PAW_Vector(540.0f, 290.0f, 0.0f, 0.0f);

		r_value /= 2;
		std::cout << r_value;
		return r_value;

}

PAW_Matrix projection_matrix(const float left, const float right, const float top, const float bottom, const float near, const float far)
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
