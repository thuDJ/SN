#include "SNcal.h"
#include <math.h>
#define PI acos(-1)

void SNCalc::Geoinit(double x_inp, double y_inp) {
	x_length = x_inp;
	y_length = y_inp;
}

void SNCalc::Matinit(double del_t_inp, double del_s0_inp, double del_s1_inp, double del_s2_inp) {
	sig_t = del_t_inp;
	sig_s0 = del_s0_inp;
	sig_s1 = del_s1_inp;
	sig_s2 = del_s2_inp;
}

void SNCalc::Sourceinit(double den_inp, double x1_inp, double x2_inp, double y1_inp, double y2_inp) {
	source_den = den_inp;
	x1_source = x1_inp;
	x2_source = x2_inp;
	y1_source = y1_inp;
	y2_source = y2_inp;
}

bool SNCalc::InSource(double x, double y) {
	return x > x1_source && x < x2_source && y > y1_source && y < y2_source;
}

void SNCalc::Calc(int xN, int yN, double err) {
	if (N == 4) {
		Calc_N(xN, yN, err, comb_4);
	}
	else if (N == 8) {
		Calc_N(xN, yN, err, comb_8);
	}
	else if (N == 12) {
		Calc_N(xN, yN, err, comb_12);
	}
}

void SNCalc::Calc_N(int xN, int yN, double err, int comb_N[][2] ) {

	double* miu_set = miu_4;
	double* wgt_set = wgt_4;
	// int** comb_N = comb_12;
	// todo: comb_12
	int N_miu = N * (N + 2) / 8;  //单个象限内的角度离散数目
	if (N == 4) {
		miu_set = miu_4;
		wgt_set = wgt_4;
	}
	else if (N == 8) {
		miu_set = miu_8;
		wgt_set = wgt_8;
	}
	else if (N == 12) {
		miu_set = miu_12;
		wgt_set = wgt_12;
	}

	double** flux_t = new double* [xN];  //total flux
	double*** flux = new double** [xN];  //angle flux
	double*** flux_halfx = new double** [xN+1]; //x-axis half flux
	double*** flux_halfy = new double** [xN+1]; //y-axis half flux
	for (int i = 0; i < xN; i++) {
		flux[i] = new double* [yN];
		flux_t[i] = new double[yN];
		for (int j = 0; j < yN; j++) {
			flux[i][j] = new double[N_miu];
			flux_t[i][j] = 0;
			for (int k = 0; k < N_miu; k++) {
				flux[i][j][k] = 1; // 初始时刻：通量均匀分布
			}
		}
	}
	for (int i = 0; i < xN + 1; i++) {
		flux_halfx[i] = new double* [yN+1];
		flux_halfy[i] = new double* [yN+1];
		for (int j = 0; j < yN + 1; j++) {
			flux_halfx[i][j] = new double[N_miu];
			flux_halfy[i][j] = new double[N_miu];
			for (int k = 0; k < N_miu; k++) {
				flux_halfx[i][j][k] = 0; // 真空边界，初始值均为零
				flux_halfy[i][j][k] = 0; // 真空边界，初始值均为零
			}
		}
	}


	// 初始化边界条件
	double iter_miu;
	double iter_ita;
	double iter_wgt;
	int iter_x;
	int iter_y;
	double pos_x;
	double pos_y;

	double E, F, Q, Q_scatter, Q_source;
	double S = x_length * y_length / xN / yN;

	//第一卦限,从左下角开始
	for (int i = 0; i < N_miu; i++) {
		iter_miu = miu_set[comb_N[i][0]];
		iter_ita = miu_set[comb_N[i][1]];
		iter_wgt = wgt_set[comb_N[i][0]];
		for (iter_x = 0; iter_x < xN; iter_x++) {
			pos_x = x_length / xN * iter_x;
			for (iter_y = 0; iter_y < yN; iter_y++) {
				pos_y = y_length / yN * iter_y;
				E = 2 * iter_miu * x_length / xN;
				F = 2 * iter_ita * y_length / yN;
				Q_source = InSource(pos_x, pos_y) ? S * source_den/2/PI : 0;
				Q_scatter = flux_t[iter_x][iter_y]* sig_s0/2/PI;

				// todo : find out 

				Q = Q_source + Q_scatter;
				flux[iter_x][iter_y][i] = (E * flux_halfx[iter_x][iter_y][i] + F * flux_halfy[iter_x][iter_y][i] + Q) / (E + F + sig_t);
				flux_halfx[iter_x + 1][iter_y][i] = 2 * flux[iter_x][iter_y][i] - flux_halfx[iter_x][iter_y][i];
				flux_halfy[iter_x][iter_y + 1][i] = 2 * flux[iter_x][iter_y][i] - flux_halfx[iter_x][iter_y][i];
			}
		}
	}
	//第二卦限，从右下角开始

	//第三卦限，从右上角开始

	//第四卦限，从左上角开始


	for (iter_x = 0; iter_x < xN; iter_x++) {
		for (iter_y = 0; iter_y < yN; iter_y++) {
			flux_t[iter_x][iter_y] = 0;
			for (int i = 0; i < N_miu; i++) {
				flux_t[iter_x][iter_y] = flux_t[iter_x][iter_y] + flux[iter_x][iter_y][i] / comb_N[i][0] / 4;
			}
			cout << flux_t[iter_x][iter_y] << ' ';
		}
		cout << endl;
	}


}

