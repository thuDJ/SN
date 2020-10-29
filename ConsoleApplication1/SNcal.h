
#ifndef SNcal
#define SNcal
#include <iostream>
#include <vector>
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
	double sig_t, sig_s0, sig_s1, sig_s2;

	//Source
	double source_den;
	double x1_source, x2_source;
	double y1_source, y2_source;



	/// 函数成员
	void Geoinit(double x_inp, double y_inp);
	void Matinit(double del_t_inp, double del_s0_inp, double del_s1_inp, double del_s2_inp);
	void Sourceinit(double den_inp, double x1_inp, double x2_inp, double y1_inp, double y2_inp);
	void Calc(int xN = 200, int yN = 200, double err = 0.001);
	void Calc_N(int xN, int yN, double err, int comb[][2]);

	bool InSource(double x_inp, double y_inp);


private:
	double miu_4[2] = { 0.3500212,0.8688903 };
	double wgt_4[2] = {1/3., 1/3.};
	int comb_4[3][2] = { {2,1},{1,2},{1,1} };
	double miu_8[6] = { 0.1971380, 0.2133981, 0.5512958, 0.5773503, 0.8065570, 0.9603506 };
	double wgt_8[10] = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };
	int comb_8[10][2] = { {6,1}, {5,3 },{3,5},{1,6}, {5,2}, {4,4},{2,5},{3,2},{2,3},{1,1} };
	double miu_12[11] = { 0.1370611,  0.1497455, 0.3911744, 0.4213515, 0.4249785, 0.6040252, 0.6400755, 0.7827706, 0.8030727, 0.9080522, 0.9810344};
	double wgt_12[11] = { 1 / 21, 1 / 21, 1 / 21, 1 / 21, 1 / 21, 1 / 21, 1 / 21, 1 / 21, 1 / 21, 1 / 21, 1 / 21 };
	int comb_12[21][2] = { {11,1}, {10,3}, {8,6 }, {6,8}, {3,10}, {1,11},{10,2},{9,4},{7,7},{4,9},{2,10},{8,2},{7,5},{5,7},{2,8},{6,2},{4,4},{2,6},{3,2},{2,3},{1,1} };
};


#endif // !SNcal