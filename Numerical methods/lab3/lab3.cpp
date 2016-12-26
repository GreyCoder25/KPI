#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int NUM_EQUATIONS = 4;

void divideRowByTheNumber(double v[], int size, double num) {
	
	for (int i = 0; i < size; ++i)
		v[i] /= num;
}

void addTwoRowsWithMult(double v1[] , double v2[], int size, double num) {
	
	for (int i = 0; i < size; ++i)
		v1[i] += v2[i] * num;
	
}

void printMatrix(double A[NUM_EQUATIONS][NUM_EQUATIONS + 1], int num_rows, int num_columns) {
	
	cout << setprecision(7) << setiosflags(ios::left);
	
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_columns; ++j)
			cout << setw(8) << A[i][j];
		cout << endl; 
	}
	cout << endl;
}

void gaussJordanElimination(double A[NUM_EQUATIONS][NUM_EQUATIONS + 1], int num_rows, int num_columns) {
	
	/* Solves system of linear equations
	 * using Gauss-Jordan elimination method
	 * 
	 * parameters:
	 * 	A - matrix of linear-equations system
	 * 	B - column vector of free members
	 */
	 
	 for (int i = 0; i < num_rows; ++i) {
		 divideRowByTheNumber(A[i], num_columns, A[i][i]);
		 for (int j = 0; j < num_rows; ++j) {
			if (i != j) 
				addTwoRowsWithMult(A[j], A[i], num_columns, -A[j][i]);
		 } 
	 }
}

double calculate_q(double a[NUM_EQUATIONS][NUM_EQUATIONS], int size) {
	
	double q = 0;
	for (int i = 0; i < size; ++i) {
		double temp_q = 0;
		for (int j = 0; j < size; ++j)
			temp_q += abs(a[i][j]);

		if (temp_q > q)
			q = temp_q;
	}

	return q;
}

double calculate_norm(double v[], int size) {
	
	double res = 0;
	for (int i = 0; i < size; ++i)
		res += v[i] * v[i];
	
	return sqrt(res);
}

double* vect_diff(double v1[], double v2[], int size) {
	
	double* diff = new double[size];
	for (int i = 0; i < size; ++i)
		diff[i] = v1[i] - v2[i];
	
	return diff;
}

void vect_copy(double v1[], double v2[], int size) {
	
	for (int i = 0; i < size; ++i)
		v1[i] = v2[i];
	
}

void solution_print(double v[], int size) {
	
	for (int i = 0; i < size; ++i)
		cout << 'x' << i << " = " << setw(12) << v[i] << endl;
	cout << endl;
	
}

double* gaussSeidelMethod(double A[NUM_EQUATIONS][NUM_EQUATIONS + 1], int num_rows, int num_columns, double eps) {
	
	double* x = new double[num_rows];
	
	double beta[num_rows];
	for (int i = 0; i < num_rows; ++i)
		beta[i] = A[i][num_columns - 1] / A[i][i];
		
	double alpha[NUM_EQUATIONS][NUM_EQUATIONS];
	for (int i = 0; i < num_rows; ++i)
		for (int j = 0; j < num_rows; ++j)
			if (i != j)
				alpha[i][j] = -A[i][j] / A[i][i];
			else
				alpha[i][j] = 0;
	
				
	double q = calculate_q(alpha, num_rows);
				
	vect_copy(x, beta, num_rows);
		
	double x_prev[num_rows];
	int num_iter = 0;
	do {
		vect_copy(x_prev, x, num_rows);
		for (int i = 0; i < num_rows; ++i) {
			double x_new = beta[i];
			for (int j = 0; j < num_rows; ++j)
				x_new += alpha[i][j] * x[j];
			x[i] = x_new;
			++num_iter;
		}
		
	} while (calculate_norm(vect_diff(x, x_prev, num_rows), num_rows) > eps * (1 - q) / q);
	cout << "num_iter = " << num_iter << endl;
		
	return x;	
}

int main() {
	
	
	double A[NUM_EQUATIONS][NUM_EQUATIONS + 1] = { {13, 12, 3, 16, 242}, //matrix A in equality A * X = B
												   {0, 28, 17, 10, 279},
											       {9,  1, 14,  3, 111},
											       {10, 14, 3,  0, 143} };
	
	printMatrix(A, NUM_EQUATIONS, NUM_EQUATIONS + 1);
	gaussJordanElimination(A, NUM_EQUATIONS, NUM_EQUATIONS + 1);
	printMatrix(A, NUM_EQUATIONS, NUM_EQUATIONS + 1);
	
	double A_p[NUM_EQUATIONS][NUM_EQUATIONS + 1] = { {23, -2, -11,   6, 106}, // matrix A prepared for iterations
													 { 0, 28,  17,  10, 279},
													 { 9,  1,  14,   3, 111},
													 {-3,  2,   0, -16, -99} };
													 
	printMatrix(A_p, NUM_EQUATIONS, NUM_EQUATIONS + 1);
	solution_print(gaussSeidelMethod(A_p, NUM_EQUATIONS, NUM_EQUATIONS + 1, 0.1), NUM_EQUATIONS);							 
	
}
