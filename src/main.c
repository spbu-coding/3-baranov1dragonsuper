#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void solve_system_in_floats(float *x, float *y, float err){
	*y = (err + 0.0001f) / 0.0001f;
	*x = 2 - *y;
}

void solve_system_in_doubles(double *x, double *y, double err){
	*y = (err + 0.0001) / 0.0001;
	*x = 2 - *y;
}

void bad_solve_system_in_floats(float *x, float *y, float err){
	*y = (err + 20.0001f - 20.0f) / 0.0001f;
	*x = 2 - *y;
}

void bad_solve_system_in_doubles(double *x, double *y, double err){
	*y = (err + 20.0001 - 20.0) / 0.0001;
	*x = 2 - *y;
}

float calc_by_floats(float eps, int flag){
	int i = 1; float x, y, err = 0.0001f, dist = 1;
	if(flag) printf("Bad");
	else printf("Good");
	printf(" calculation in floats:\n");
	while ((dist > eps) && (i < 30)){
		if (flag) bad_solve_system_in_floats(&x,&y,err);
		else solve_system_in_floats(&x,&y,err);
		dist = powf(powf(x - 1, 2) + powf(y - 1, 2), 0.5f);
		err *= 0.5f;
		printf("floats step %d , distance = %f , error = %f\n", i++, dist, err);
	}
	printf("End of calculating in floats.\n");
	return (dist);
}

double calc_by_doubles(double eps, int flag){
	int i = 1; double x, y, err = 0.0001, dist = 1;
	if(flag) printf("Bad");
	else printf("Good");
	printf(" calculation in doubles:\n");
	while((dist > eps) && (i < 30)){
		if (flag) bad_solve_system_in_doubles(&x,&y,err);
		else solve_system_in_doubles(&x,&y,err);
		dist = sqrt(pow(x - 1, 2) + pow (y - 1, 2));
		err*= 0.5;
		printf("doubles step %d , distance = %lf , error = %lf\n", i++, dist, err);
	}
	printf("End of calculating in doubles.\n");
	return (dist);
}

void main(){
	float eps_f = powf(10,-6); double eps_d = pow(10,-6);
	float dist_f = calc_by_floats (eps_f, 0), dist_f2 = calc_by_floats(eps_f,1);
	double dist_d = calc_by_doubles (eps_d, 0), dist_d2 = calc_by_doubles (eps_d, 1);
	printf("Difference between bad calculation results (double - float): %lf. End of experiment.\n", dist_d2 - dist_f2);
}
