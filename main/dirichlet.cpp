#include "dirichlet.h"
#include <cmath>

double function(const double x, const double y)
{ // правая часть уравнения

	return 0;
}

double conditions(const double x, const double y)
{ //краевые условия

	if (x == 0)
		return 0;
	if (x == 1)
		return sin(y);
	if (y == 0)
		return 0;
	if (y == 1)
		return sin(x);
	else
		return 0;
	return 0;
}

double step(const size_t size)
{ //шаг для сетки

	return 1.0 / (size + 1.0);
}

Matrix first_approx_f(const size_t size, const double h)
{ //первое приближение для f

	Matrix F(size, size);
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
		{
			F(i, j) = function((i + 1) * h, (j + 1) * h);
		}
	}

	return F;
}

Matrix first_approx_u(const size_t size, const double h)
{ //первое приближение для u

	Matrix u(size + 2, size + 2);

	for (size_t i = 1; i < size + 1; ++i)
	{
		u(i, 0) = conditions(i * h, 0);
		u(i, size + 1) = conditions(i * h, (size + 1) * h);
	}
	for (size_t j = 0; j < size + 2; ++j)
	{
		u(0, j) = conditions(0, j * h);
		u(size + 1, j) = conditions((size + 1) * h, j * h);
	}

	return u;
}

Matrix solve(const size_t size, const double eps)
{

	double h = step(size);

	Matrix F = first_approx_f(size, h);
	Matrix u = first_approx_u(size, h);

	double max;
	do
	{

		max = 0;
		for (size_t i = 1; i < size + 1; ++i)
			for (size_t j = 1; j < size + 1; ++j)
			{
				double u0 = u(i, j);
				double temp = 0.25 * (u(i - 1, j) + u(i + 1, j) + u(i, j - 1) + u(i, j + 1) - h * h * F(i - 1, j - 1));
				u(i, j) = temp;
				double d = std::fabs(temp - u0);

				if (d > max)
				{
					max = d;
				}
			}
	} while (max > eps);

	return u;
}

Matrix solve_omp(const size_t size, const double eps)
{

	double h = step(size);
	Matrix u_mat = first_approx_u(size, h);
	Matrix f_mat = first_approx_f(size, h);
	double max, u0, d;
	size_t j = 0;
	size_t i = 0;
	std::vector<double> mx(size + 1);
	do
	{

		for (size_t k = 1; k < size + 1; k++)
		{
			mx[k] = 0;
#pragma omp parallel for shared(u_mat, k, mx) private(i, j, u0, d)
			for (i = 1; i < k + 1; i++)
			{
				j = k + 1 - i;
				u0 = u_mat(i, j);
				u_mat(i, j) = 0.25 * (u_mat(i - 1, j) + u_mat(i + 1, j) + u_mat(i, j - 1) + u_mat(i, j + 1) - h * h * f_mat(i - 1, j - 1));
				d = std::fabs(u_mat(i, j) - u0);
				if (d > mx[i])
					mx[i] = d;
			}
		}
		for (size_t k = size - 1; k > 0; k--)
		{
#pragma omp parallel for shared(u_mat, k, mx) private(i, j, u0, d)
			for (i = size - k + 1; i < size + 1; i++)
			{
				j = 2 * size - k - i + 1;
				u0 = u_mat(i, j);
				u_mat(i, j) = 0.25 * (u_mat(i - 1, j) + u_mat(i + 1, j) + u_mat(i, j - 1) + u_mat(i, j + 1) - h * h * f_mat(i - 1, j - 1));
				d = std::fabs(u_mat(i, j) - u0);
				if (d > mx[i])
					mx[i] = d;
			}
		}
		max = 0;
		for (size_t i = 1; i < size + 1; i++)
		{
			if (mx[i] > max)
				max = mx[i];
		}
	} while (max > eps);
	return u_mat;
}

Matrix solve_mpi(const size_t size, const double eps, const size_t ProcRank, const size_t ProcNum)
{
	return 0;

}