#define PI 3.141592653589793
#define TRIG_ITERATIONS 20
#define SQRT_ITERATIONS 25

double rad(double deg);
double deg(double rad);
double sqrt(double x);
double factorial(int x);
double sin(double x);
double cos(double x);
double arcsin(double x);
double arccos(double x);
double cos_side(double side1, double side2, double opposite_angle);
double cos_angle(double side1, double side2, double opposite_side);
double sin_side(double side, double opposite_angle, double angle);
double sin_angle(double opposite_angle, double side, double opposite_side);
void three_sides(double a, double b, double c, double *alpha, double *beta, double *gamma);
