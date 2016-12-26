#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const double interval_start = 0;
const double interval_end = 12;
const int NUM_INTERVALS = 50;

double func(const double x) {
	return x - 1.5 * x * x * x * sin(x);
}

void x_fill(vector<double> &x, const double a, const double b) {
	
	const double step = (b - a) / (x.size() - 1);
	const int x_size = x.size();
	
	double temp = a;
	for (int i = 0; i < x_size; ++i) {
		x[i] = temp;
		temp += step;
	}
	
}

void f_fill(vector<double> &f, const vector<double> &x) {
	
	const int x_size = x.size();
	for (int i  = 0; i < x_size; ++i)
		f[i] = func(x[i]);
		
}

void d_fill(vector<double> &d, const vector<double> &c, const double h) {
	
	const int d_size = d.size();
	for (int i = 1; i < d_size; ++i)
		d[i] = (c[i] - c[i - 1]) / h;
}

void b_fill(vector<double> &b, const vector<double> &c, const vector<double> &d, const vector<double> &f, const double h) {
	
	const int b_size = b.size();
	for (int i = 1; i < b_size; ++i) {
		b[i] = (h / 2) * c[i] - (h * h * d[i]) / 6 + (f[i] - f[i - 1]) / h;
	}
	
}

void matrix_zero_init(double A[NUM_INTERVALS - 1][NUM_INTERVALS], const int num_rows, const int num_columns) {
	
	for (int i = 0; i < num_rows; ++i)
		for (int j = 0; j < num_columns; ++j)
			A[i][j] = 0;
}

void A_fill(double A[NUM_INTERVALS - 1][NUM_INTERVALS], const int num_rows, const int num_columns, 
			const double h, const vector<double> &f) {
	
	const int n = num_columns - 1;
	int j = 1;
	A[0][0] = 4*h; A[0][1] = h; A[0][n] = 6*( (f[2] - f[1]) / h - (f[1] - f[0]) / h );
	for (int i = 1; i < num_rows - 1; ++i) {
		A[i][j-1] = h;
		A[i][j] = 4*h;
		A[i][j+1] = h;
		A[i][n] = 6*( (f[j+2] - f[j+1]) / h - (f[j+1] - f[j]) / h );
		
		++j;
	}
	A[num_rows - 1][n - 2] = h; A[num_rows - 1][n - 1] = 4*h;
	A[num_rows - 1][n] = 6*( (f[j+2] - f[j+1]) / h - (f[j+1] - f[j]) / h );	
}

vector<double> sweep_method(double A[NUM_INTERVALS - 1][NUM_INTERVALS], const int num_rows, const int num_columns) {
	
	vector<double> alpha(num_rows + 1);
	vector<double> beta(num_rows + 1);
	vector<double> x(num_rows + 1);
	
	double A_i = 0, B_i = A[0][1], C_i = A[0][0], F_i = A[0][num_columns - 1];
	
	alpha[1] = -B_i / C_i;				
	beta[1] = F_i / C_i; 				
	
	for (int i = 1; i <= num_rows - 1; ++i) {
		
		alpha[i+1] = -B_i / (A_i * alpha[i] + C_i);
		beta[i+1] = (F_i - A_i * beta[i]) / (A_i * alpha[i] + C_i);	
		
		if (i < num_rows - 1) {
			A_i = A[i][i-1];
			B_i = A[i][i+1];
			C_i = A[i][i];
			F_i = A[i][num_columns - 1];
		}
		else {
			A_i = A[num_rows - 1][num_columns - 3];
			B_i = A[num_rows - 2][num_columns - 2];
			C_i = A[num_rows - 1][num_columns - 2];
			F_i = A[num_rows - 1][num_columns - 1];
		}
	}
	x[num_rows] = (F_i - A_i * beta[num_rows]) / (A_i * alpha[num_rows] + C_i);
	for (int i = num_rows - 1; i >= 1; --i)
		x[i] = alpha[i + 1] * x[i + 1] + beta[i + 1];
	
	return x;
}

double s(const double arg, const int i, const vector<double> &x, const vector<double> &f, const vector<double> &b,
																	 const vector<double> &c, const vector<double> &d) {
	
	return f[i] + b[i]*(arg - x[i]) + (c[i] / 2)*(arg - x[i])*(arg - x[i]) + (d[i] / 6)*(arg - x[i])*(arg - x[i])*(arg - x[i]); 
	
}

void print(const vector<double> &v) {
	
	const int len = v.size();
	for (int i = 0 ; i < len; ++i)
		cout << v[i] << ' ';
	cout << "\n\n";
	
}

void print_matrix(double A[NUM_INTERVALS - 1][NUM_INTERVALS], const int num_rows, const int num_columns) {
	
	cout << setprecision(5) << setiosflags(ios::left);
	
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_columns; ++j)
			cout << setw(8) << A[i][j];
		cout << endl; 
	}
	cout << endl;
}

int main() {
	
	double A[NUM_INTERVALS - 1][NUM_INTERVALS];
	double h = (interval_end - interval_start) / NUM_INTERVALS;
	
	vector<double> x(NUM_INTERVALS + 1);
	vector<double> f(NUM_INTERVALS + 1);	
	vector<double> b(NUM_INTERVALS + 1);
	vector<double> c(NUM_INTERVALS + 1);
	vector<double> d(NUM_INTERVALS + 1);
	
	x_fill(x, interval_start, interval_end);
	f_fill(f, x);
	//print(f);
	matrix_zero_init(A, NUM_INTERVALS - 1, NUM_INTERVALS);
	A_fill(A, NUM_INTERVALS - 1, NUM_INTERVALS, h, f);
	//print_matrix(A, NUM_INTERVALS - 1, NUM_INTERVALS);
	
	c = sweep_method(A, NUM_INTERVALS - 1, NUM_INTERVALS);
	c.push_back(0);
	//print(c);
	d_fill(d, c, h);
	b_fill(b, c, d, f, h);
	
	const double GRAPH_BUILDING_STEP = 0.01;
	
	ofstream func_vals_file("f_vals.txt");
	for (double i = interval_start; i <= interval_end; i += GRAPH_BUILDING_STEP)
		func_vals_file << i << "\t" << func(i) << endl;

	func_vals_file.close();
	
	ofstream spline_approx_vals_file("spline_approx_vals.txt");
	for (size_t i = 1; i <= x.size() - 1; ++i)
		for (double j = x[i - 1]; j < x[i]; j += GRAPH_BUILDING_STEP)
			spline_approx_vals_file << j << "\t" << s(j, i, x, f, b, c, d) << endl;
			
	spline_approx_vals_file.close();
}
