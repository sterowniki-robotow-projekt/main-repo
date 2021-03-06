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

void PAW_Figure::rotate_helper(PAW_Primitive * primi, const PAW_Matrix projection_matrix)
{
	primi->rotate_helper(projection_matrix);
}
void PAW_Figure::projection_helper(PAW_Primitive * primi, const PAW_Matrix projection_matrix)
{
	primi->projection_helper(projection_matrix);
}

void PAW_Figure::scale_helper(PAW_Primitive * primi, const float scale)
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
}

void PAW_Figure::rotate3D(const float x_degrees, const float y_degrees, const float z_degrees)
{
	PAW_Matrix Rx(4), Ry(4), Rz(4), R(4);
	Rx.to_rotation_matrix(y, z, x_degrees);
	Ry.to_rotation_matrix(z, x, y_degrees);
	Rz.to_rotation_matrix(y, x, z_degrees);

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
		scale_helper(form[i], scale);
	}
}


void PAW_Figure::toPyramid(const float a_length, const PAW_Color a_color)
{
	for(size_t i =0 ; i< form.size(); ++i)
	{
		delete form[i];
	}
	form.clear();

	const float length = 0.5f * a_length;
	PAW_Vector P1(-length, -length, -length, 1.0f);
	PAW_Vector P2(-length,-length, length, 1.0f);
	PAW_Vector P3(length, -length, -length, 1.0f);
	PAW_Vector P4(length, -length, length, 1.0f);
	PAW_Vector P5(0, length, 0, 1.0f);

	PAW_Vector S1(-50.0f,-20.0f,-10.0f,1.0f);
	PAW_Vector S2(20.0f,10.0f,50.0f,1.0f);
	PAW_Vector S3(0,0,0,1.0f);

	PAW_Line SL1(S3,S1,a_color);
	PAW_Line SL2(S2,S1,a_color);

	PAW_Line L1(P1, P2, a_color);
	PAW_Line L2(P2, P4, a_color);
	PAW_Line L3(P4, P3, a_color);
	PAW_Line L4(P3, P1, a_color);

	PAW_Line L5(P5, P1, a_color);
	PAW_Line L6(P5, P2, a_color);
	PAW_Line L7(P5, P3, a_color);
	PAW_Line L8(P5, P4, a_color);

	PAW_Color red(255,232,23,23);
	PAW_Color blue(255,23,127,232);

	paint(L7,L8,red);


	push(L1);
	push(L2);
	push(L3);
	push(L4);

	push(L5);
	push(L6);
	push(L7);
	push(L8);

	//push(PAW_Circle(P1, 5.0f, true, PAW_Color(255, 255, 255, 0))); //zolty
	//push(PAW_Circle(P2, 5.0f, true, PAW_Color(255, 255, 0, 0))); //czerwony
	//push(PAW_Circle(P3, 5.0f, true, PAW_Color(255, 0, 255, 0))); //zielony
	//push(PAW_Circle(P4, 5.0f, true, PAW_Color(255, 0, 0, 255))); //niebieski
	//push(PAW_Circle(P5, 5.0f, true, PAW_Color(255, 224, 95, 92))); //rozowy
	//push(PAW_Circle(P6, 5.0f, true, PAW_Color(255, 69, 71, 124))); //fioletowy
	//push(PAW_Circle(P7, 5.0f, true, PAW_Color(255, 77, 255, 255))); //cyan
	//push(PAW_Circle(P8, 5.0f, true, PAW_Color(255, 255, 128, 0))); //pomaranczowy
}

void PAW_Figure::toCross(const float a_length, const PAW_Color a_color)
{
	for(size_t i =0 ; i< form.size(); ++i)
	{
		delete form[i];
	}
	form.clear();

	const float length = 0.5f * a_length;

	PAW_Vector P1(-0.5f*length, -length, -0.5f*length, 1.0f);
	PAW_Vector P2(-0.5f*length,-length, 0.5f*length, 1.0f);
	PAW_Vector P3(0.5f*length, -length, -0.5f*length, 1.0f);
	PAW_Vector P4(0.5f*length, -length, 0.5f*length, 1.0f);

	PAW_Vector P5(-0.5f*length, -0.5f*length, -0.5f*length, 1.0f);
	PAW_Vector P6(-0.5f*length,-0.5f*length, 0.5f*length, 1.0f);
	PAW_Vector P7(0.5f*length, -0.5f*length, -0.5f*length, 1.0f);
	PAW_Vector P8(0.5f*length, -0.5f*length, 0.5f*length, 1.0f);

	PAW_Vector P9(-length, -0.5f*length, 0.5f*length, 1.0f);
	PAW_Vector P10(length, -0.5f*length, 0.5f*length, 1.0f);

	PAW_Vector P11(-length, 0, 0.5f*length, 1.0f);
	PAW_Vector P12(length, 0, 0.5f*length, 1.0f);

	PAW_Vector P14(-length, -0.5f*length, -0.5f*length, 1.0f);
	PAW_Vector P13(length, -0.5f*length, -0.5f*length, 1.0f);

	PAW_Vector P15(-length, 0, -0.5f*length, 1.0f);
	PAW_Vector P16(length, 0, -0.5f*length, 1.0f);

	PAW_Vector P17(-0.5f*length, 0.0f*length, -0.5f*length, 1.0f);
	PAW_Vector P18(0.5f*length, 0.0f*length, -0.5f*length, 1.0f);

	PAW_Vector P19(-0.5f*length,-0.0f*length, 0.5f*length, 1.0f);
	PAW_Vector P20(0.5f*length, -0.0f*length, 0.5f*length, 1.0f);

	PAW_Vector P23(-0.5f*length, 0.5f*length, -0.5f*length, 1.0f);
	PAW_Vector P24(0.5f*length, 0.5f*length, -0.5f*length, 1.0f);

	PAW_Vector P21(-0.5f*length,0.5f*length, 0.5f*length, 1.0f);
	PAW_Vector P22(0.5f*length, 0.5f*length, 0.5f*length, 1.0f);


	push(PAW_Line(P1, P3, a_color));
	push(PAW_Line(P2, P4, a_color));
	push(PAW_Line(P3, P4, a_color));
	push(PAW_Line(P2, P1, a_color));
	push(PAW_Line(P1, P5, a_color));
	push(PAW_Line(P2, P6, a_color));
	push(PAW_Line(P3, P7, a_color));
	push(PAW_Line(P4, P8, a_color));
	push(PAW_Line(P6, P9, a_color));
	push(PAW_Line(P8, P10, a_color));
	push(PAW_Line(P11, P9, a_color));
	push(PAW_Line(P12, P10, a_color));
	push(PAW_Line(P14, P5, a_color));
	push(PAW_Line(P13, P7, a_color));
	push(PAW_Line(P14, P15, a_color));
	push(PAW_Line(P13, P16, a_color));
	push(PAW_Line(P15, P11, a_color));
	push(PAW_Line(P16, P12, a_color));
	push(PAW_Line(P9, P14, a_color));
	push(PAW_Line(P13, P10, a_color));
	push(PAW_Line(P15, P17, a_color));
	push(PAW_Line(P16, P18, a_color));
	push(PAW_Line(P11, P19, a_color));
	push(PAW_Line(P12, P20, a_color));
	push(PAW_Line(P17, P23, a_color));
	push(PAW_Line(P18, P24, a_color));
	push(PAW_Line(P19, P21, a_color));
	push(PAW_Line(P22, P20, a_color));
	push(PAW_Line(P23, P21, a_color));
	push(PAW_Line(P24, P22, a_color));
	push(PAW_Line(P22, P21, a_color));
	push(PAW_Line(P23, P24, a_color));

}


void PAW_Figure::toCube(const float a_length, const PAW_Color a_color)
{
	for(size_t i =0 ; i< form.size(); ++i)
	{
		delete form[i];
	}
	form.clear();



	const float length = 0.5f * a_length;

	PAW_Vector P1(-length, -length, length, 1.0f);
	PAW_Vector P2(length, -length, length, 1.0f);
	PAW_Vector P3(-length, length, length, 1.0f);
	PAW_Vector P4(length, length, length, 1.0f);
	PAW_Vector P5(-length, -length, -length, 1.0f);
	PAW_Vector P6(length, -length, -length, 1.0f);
	PAW_Vector P7(-length, length, -length, 1.0f);
	PAW_Vector P8(length, length, -length, 1.0f);


	PAW_Line L1(P1, P2, a_color);
	PAW_Line L2(P2, P4, a_color);
	PAW_Line L3(P3, P4, a_color);
	PAW_Line L4(P3, P1, a_color);
	PAW_Line L5(P1, P5, a_color);
	PAW_Line L6(P5, P7, a_color);
	PAW_Line L7(P7, P3, a_color);
	PAW_Line L8(P7, P8, a_color);
	PAW_Line L9(P5, P6, a_color);
	PAW_Line L10(P6, P8, a_color);
	PAW_Line L11(P8, P4, a_color);
	PAW_Line L12(P6, P2, a_color);

	PAW_Color green(255,85,255,51);
	PAW_Color purple(255,200,43,199);

	paint(L1,L3,green);
	paint(L10,L6,purple);

	push(L1);
	push(L2);
	push(L3);
	push(L4);
	push(L5);
	push(L6);
	push(L7);
	push(L8);
	push(L9);
	push(L10);
	push(L11);
	push(L12);







	//push(PAW_Circle(P1, 5.0f, true, PAW_Color(255, 255, 255, 0))); //zolty
	//push(PAW_Circle(P2, 5.0f, true, PAW_Color(255, 255, 0, 0))); //czerwony
	//push(PAW_Circle(P3, 5.0f, true, PAW_Color(255, 0, 255, 0))); //zielony
	//push(PAW_Circle(P4, 5.0f, true, PAW_Color(255, 0, 0, 255))); //niebieski
	//push(PAW_Circle(P5, 5.0f, true, PAW_Color(255, 224, 95, 92))); //rozowy
	//push(PAW_Circle(P6, 5.0f, true, PAW_Color(255, 69, 71, 124))); //fioletowy
	//push(PAW_Circle(P7, 5.0f, true, PAW_Color(255, 77, 255, 255))); //cyan
	//push(PAW_Circle(P8, 5.0f, true, PAW_Color(255, 255, 128, 0))); //pomaranczowy
}


void PAW_Figure::toExperimental(const float a_length, const PAW_Color a_color)
{
	for(size_t i =0 ; i< form.size(); ++i)
	{
		delete form[i];
	}
	form.clear();



	const float length = 0.5f * a_length;

	PAW_Vector P1(-length, -length, length, 1.0f);
	PAW_Vector P2(length, -length, length, 1.0f);
	PAW_Vector P3(-length, length, length, 1.0f);
	PAW_Vector P4(length, length, length, 1.0f);
	PAW_Vector P5(-length, -length, -length, 1.0f);
	PAW_Vector P6(length, -length, -length, 1.0f);
	PAW_Vector P7(-length, length, -length, 1.0f);
	PAW_Vector P8(length, length, -length, 1.0f);


	PAW_Line L1(P1, P2, a_color);
	PAW_Line L2(P2, P4, a_color);
	PAW_Line L3(P3, P4, a_color);
	PAW_Line L4(P3, P1, a_color);
	PAW_Line L5(P1, P5, a_color);
	PAW_Line L6(P5, P7, a_color);
	PAW_Line L7(P7, P3, a_color);
	PAW_Line L8(P7, P8, a_color);
	PAW_Line L9(P5, P6, a_color);
	PAW_Line L10(P6, P8, a_color);
	PAW_Line L11(P8, P4, a_color);
	PAW_Line L12(P6, P2, a_color);

	PAW_Color green(255,85,255,51);
	PAW_Color purple(255,200,43,199);
	PAW_Color yellow(255,199,255,0);

	paint(L1,L3,green);
	paint(L10,L6,purple);
	paint(L11,L12,yellow);

	push(L1);
	push(L2);
	push(L3);
	push(L4);
	push(L5);
	push(L6);
	push(L7);
	push(L8);
	push(L9);
	push(L10);
	push(L11);
	push(L12);


}






void PAW_Figure::paint(const PAW_Line& line1, const PAW_Line& line2, const PAW_Color& clr){

	PAW_Vector* vec_ptr1 = NULL;
	PAW_Vector* vec_ptr2 = NULL;

	// d to beda roznice, delty itd.
	float dx1, dx2, dy1, dy2, dz1, dz2;
	// c to kursory albo iteratory
	float cx1, cy1, cz1, cx2, cy2, cz2;

	//m to milestone'y, punkty zaczepne dla linii tworzacych sciane
	float mx1,mx2,my1,my2,mz1,mz2;

	// pomocnicze
	int loopint = 0;

	cx1 = line1.g_begin()[x];
	cy1 = line1.g_begin()[y];
	cz1 = line1.g_begin()[z];

	cx2 = line2.g_begin()[x];
	cy2 = line2.g_begin()[y];
	cz2 = line2.g_begin()[z];


	//DISTANCES ON LINE 1
	 dx1 = line1.g_end()[x] - line1.g_begin()[x];
	 dy1 = line1.g_end()[y] - line1.g_begin()[y];
	 dz1 = line1.g_end()[z] - line1.g_begin()[z];


	//DISTANCES ON LINE 2
	 dx2 = line2.g_end()[x] - line2.g_begin()[x];
	 dy2 = line2.g_end()[y] - line2.g_begin()[y];
	 dz2 = line2.g_end()[z] - line2.g_begin()[z];

	// dlugosci wektorow
	float length1 = sqrt(dx1*dx1 + dy1*dy1 + dz1*dz1);
	float length2 = sqrt(dx2*dx2 + dy2*dy2 + dz2*dz2);

	int density = 2; // jak gesta sciana? 2 oznacza linie co 0.5f

	loopint = static_cast<int>(length1);

	 // MILESTONE'Y DLA KAZDEGO KURSORA
	 mx1 = dx1/(density*loopint);
	 my1 = dy1/(density*loopint);
	 mz1 = dz1/(density*loopint);
	 mx2 = dx2/(density*loopint);
	 my2 = dy2/(density*loopint);
	 mz2 = dz2/(density*loopint);


	 // jesli rozne dlugosci - nic sie nie dzieje
	if ((length1 == length2)&&(length1 != 0.0f)) {
		for(int i = 0; i < density*loopint; i++) {

			vec_ptr1 = new PAW_Vector(cx1,cy1,cz1,1.0f);
			vec_ptr2 = new PAW_Vector(cx2,cy2,cz2,1.0f);

			push(PAW_Line(*vec_ptr1,*vec_ptr2,clr));

			//przesuniecie kursorow
			cx1 += mx1;
			cy1 += my1;
			cz1 += mz1;
			cx2 += mx2;
			cy2 += my2;
			cz2 += mz2;

			delete vec_ptr1;
			delete vec_ptr2;
		}
	}
}



