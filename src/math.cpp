#include "math.hpp"

double rad(double deg)
{
    return deg * PI / 180;
}

double deg(double rad)
{
    return rad * 180 / PI;
}

double sqrt(double x)
{
    if (x == 0)
    {
        return 0;
    }
    double a, b, guess = x;
    for (int i = 0; i < SQRT_ITERATIONS; i++)
    {
        a = guess;
        a *= a;
        a -= x;
        b = 2;
        b *= guess;
        a /= b;
        guess -= a;
    }
    return guess;
}

double factorial(int x)
{
    double val = x;
    while (--x)
    {
        val *= x;
    }
    return val;
}

double sin(double x)
{
    if (x == 0.0)
    {
        return 0;
    }
    double x_sq = x;
    char sign = 1;
    double result = x;
    double a;
    x *= x;
    for (int n = 1; n < TRIG_ITERATIONS; n++)
    {
        x_sq *= x;
        sign *= -1;
        a = sign * x_sq;
        a /= factorial(2 * n + 1);
        result += a;
    }
    return result;
}

double cos(double x)
{
    if (x == 0.0)
    {
        return 1;
    }
    x *= x;
    double x_sq = 1;
    char sign = 1;
    double result = 1;
    double a;
    for (int n = 1; n < TRIG_ITERATIONS; n++)
    {
        x_sq *= x;
        sign *= -1;
        a = sign * x_sq;
        a /= factorial(2 * n);
        result += a;
    }
    return result;
}

double arcsin(double x)
{
    if (x == 0.0)
    {
        return 0;
    }
    double result = x;
    double mfour = 1;
    double fact1 = 1;
    double mult = x;
    double a, b;
    x *= x;
    for (int n = 1; n < TRIG_ITERATIONS; n++)
    {
        mfour *= 4;
        fact1 *= n;
        mult *= x;
        a = factorial(2 * n);
        a *= mult;
        b = mfour;
        b *= fact1;
        b *= fact1;
        b *= 2 * n + 1;
        a /= b;
        result += a;
    }
    return result;
}

double arccos(double x)
{
    if (x == 1.0)
    {
        return 0;
    }
    return PI / 2 - arcsin(x);
}

double cos_side(double side1, double side2, double opposite_angle)
{
    double x = side1;
    x *= side2;
    x *= -2 * cos(rad(opposite_angle));
    side1 *= side1;
    side2 *= side2;
    x += side1;
    x += side2;
    return sqrt(x);
}

double cos_angle(double side1, double side2, double opposite_side)
{
    double x = 2;
    x *= side1;
    x *= side2;
    side1 *= side1;
    side2 *= side2;
    opposite_side *= opposite_side;
    side1 += side2;
    side1 -= opposite_side;
    side1 /= x;
    return deg(arccos(side1));
}

double sin_side(double side, double opposite_angle, double angle)
{
    return sin(rad(angle))*side/sin(rad(opposite_angle));
}

double sin_angle(double opposite_angle, double side, double opposite_side)
{
    return deg(arcsin(opposite_side*sin(rad(opposite_angle))/side));
}

void three_sides(double a, double b, double c, double *alpha, double *beta, double *gamma)
{
    *alpha = cos_angle(b, c, a);
    *beta = cos_angle(a, c, b);
    *gamma = 180 - *alpha - *beta;
}
