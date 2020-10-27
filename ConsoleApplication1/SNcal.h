
#ifndef SNcal
#define SNcal
#include <iostream>

using namespace std;

class SNCalc 
{
public:
	SNCalc(int N_inp) {
		N = N_inp;
	}

	/// 数据成员
	int N;

	//Geo
	double x_length, y_length;

	//Mat
	double del_t, del_s0, del_s1, del_s2;


	/// 函数成员
	bool Geoinit(double x_inp, double y_inp);
	bool Matinit(double del_t_inp, double del_s0_inp, double del_s1_inp, double del_s2_inp);



	
};


#endif // !SNcal