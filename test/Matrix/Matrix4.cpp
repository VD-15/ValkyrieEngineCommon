#include "TestValues.hpp"
#include "ValkyrieEngineCommon/VMath.hpp"

using namespace vlk;

TEST_CASE("Matrix4 default constructor")
{
	Matrix4 m;

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (x == y) REQUIRE(m[x][y] == 1.0f);
			else REQUIRE(m[x][y] == 0.0f);
		}
	}
}

TEST_CASE("Matrix4 nine float constructor")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[0][3] == 2.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[1][3] == 6.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
	REQUIRE(m[2][3] == 1.0f);
	REQUIRE(m[3][0] == -2.0f);
	REQUIRE(m[3][1] == 0.0f);
	REQUIRE(m[3][2] == 4.0f);
	REQUIRE(m[3][3] == -7.0f);
}
TEST_CASE("Matrix4 array constructor")
{
	Matrix4 m(
		VectorBase<4, Float>({ 0.0f, 9.0f, 3.0f, 2.0f }),
		VectorBase<4, Float>({ 1.0f, 8.0f, 4.0f, 6.0f }),
		VectorBase<4, Float>({ 2.0f, 7.0f, 5.0f, 1.0f }),
		VectorBase<4, Float>({-2.0f, 0.0f, 4.0f,-7.0f }));

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[0][3] == 2.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[1][3] == 6.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
	REQUIRE(m[2][3] == 1.0f);
	REQUIRE(m[3][0] == -2.0f);
	REQUIRE(m[3][1] == 0.0f);
	REQUIRE(m[3][2] == 4.0f);
	REQUIRE(m[3][3] == -7.0f);
}

TEST_CASE("Matrix4 copy constructor")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	Matrix4 n(m);

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[0][3] == 2.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[1][3] == 6.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
	REQUIRE(m[2][3] == 1.0f);
	REQUIRE(m[3][0] == -2.0f);
	REQUIRE(m[3][1] == 0.0f);
	REQUIRE(m[3][2] == 4.0f);
	REQUIRE(m[3][3] == -7.0f);
}

TEST_CASE("Matrix4 move constructor")
{
	Matrix4 m(Matrix4(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f));

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[0][3] == 2.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[1][3] == 6.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
	REQUIRE(m[2][3] == 1.0f);
	REQUIRE(m[3][0] == -2.0f);
	REQUIRE(m[3][1] == 0.0f);
	REQUIRE(m[3][2] == 4.0f);
	REQUIRE(m[3][3] == -7.0f);
}

TEST_CASE("Matrix4 copy assignment operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	Matrix4 n = m;

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[0][3] == 2.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[1][3] == 6.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
	REQUIRE(m[2][3] == 1.0f);
	REQUIRE(m[3][0] == -2.0f);
	REQUIRE(m[3][1] == 0.0f);
	REQUIRE(m[3][2] == 4.0f);
	REQUIRE(m[3][3] == -7.0f);
}

TEST_CASE("Matrix4 move assignment operator")
{
	Matrix4 m;
	m = std::move(Matrix4(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f));

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[0][3] == 2.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[1][3] == 6.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
	REQUIRE(m[2][3] == 1.0f);
	REQUIRE(m[3][0] == -2.0f);
	REQUIRE(m[3][1] == 0.0f);
	REQUIRE(m[3][2] == 4.0f);
	REQUIRE(m[3][3] == -7.0f);
}

TEST_CASE("Matrix4 three Vector4 constructor")
{
	Matrix4 m({
		Vector4(0.0f, 9.0f, 3.0f, 2.0f),
		Vector4(1.0f, 8.0f, 4.0f, 6.0f),
		Vector4(2.0f, 7.0f, 5.0f, 1.0f),
		Vector4(-2.0f, 0.0f, 4.0f, -7.0f)});

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[0][3] == 2.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[1][3] == 6.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
	REQUIRE(m[2][3] == 1.0f);
	REQUIRE(m[3][0] == -2.0f);
	REQUIRE(m[3][1] == 0.0f);
	REQUIRE(m[3][2] == 4.0f);
	REQUIRE(m[3][3] == -7.0f);
}

TEST_CASE("Matrix4 equality operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);
	
	Matrix4 n(
		5.0f, 4.0f, 3.0f, 7.0f,
		7.0f, 8.0f, 9.0f, 1.0f,
		2.0f, 1.0f, 0.0f, 0.0f,
		4.0f, 4.0f, 1.0f, 5.0f);

	REQUIRE(m == m);
	REQUIRE(n == n);
	REQUIRE(!(m == n));
	REQUIRE(!(n == m));
}

TEST_CASE("Matrix4 inequality operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);
	
	Matrix4 n(
		5.0f, 4.0f, 3.0f, 7.0f,
		7.0f, 8.0f, 9.0f, 1.0f,
		2.0f, 1.0f, 0.0f, 0.0f,
		4.0f, 4.0f, 1.0f, 5.0f);

	REQUIRE(m != n);
	REQUIRE(n != m);
	REQUIRE(!(m != m));
	REQUIRE(!(n != n));
}

TEST_CASE("Matrix4 scalar addition operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	m = m + 3.0f;

	REQUIRE(m[0][0] == 0.0f + 3.0f);
	REQUIRE(m[0][1] == 9.0f + 3.0f);
	REQUIRE(m[0][2] == 3.0f + 3.0f);
	REQUIRE(m[0][3] == 2.0f + 3.0f);
	REQUIRE(m[1][0] == 1.0f + 3.0f);
	REQUIRE(m[1][1] == 8.0f + 3.0f);
	REQUIRE(m[1][2] == 4.0f + 3.0f);
	REQUIRE(m[1][3] == 6.0f + 3.0f);
	REQUIRE(m[2][0] == 2.0f + 3.0f);
	REQUIRE(m[2][1] == 7.0f + 3.0f);
	REQUIRE(m[2][2] == 5.0f + 3.0f);
	REQUIRE(m[2][3] == 1.0f + 3.0f);
	REQUIRE(m[3][0] == -2.0f + 3.0f);
	REQUIRE(m[3][1] == 0.0f + 3.0f);
	REQUIRE(m[3][2] == 4.0f + 3.0f);
	REQUIRE(m[3][3] == -7.0f + 3.0f);
}

TEST_CASE("Matrix4 scalar subtraction operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	m = m - 3.0f;

	REQUIRE(m[0][0] == 0.0f - 3.0f);
	REQUIRE(m[0][1] == 9.0f - 3.0f);
	REQUIRE(m[0][2] == 3.0f - 3.0f);
	REQUIRE(m[0][3] == 2.0f - 3.0f);
	REQUIRE(m[1][0] == 1.0f - 3.0f);
	REQUIRE(m[1][1] == 8.0f - 3.0f);
	REQUIRE(m[1][2] == 4.0f - 3.0f);
	REQUIRE(m[1][3] == 6.0f - 3.0f);
	REQUIRE(m[2][0] == 2.0f - 3.0f);
	REQUIRE(m[2][1] == 7.0f - 3.0f);
	REQUIRE(m[2][2] == 5.0f - 3.0f);
	REQUIRE(m[2][3] == 1.0f - 3.0f);
	REQUIRE(m[3][0] == -2.0f - 3.0f);
	REQUIRE(m[3][1] == 0.0f - 3.0f);
	REQUIRE(m[3][2] == 4.0f - 3.0f);
	REQUIRE(m[3][3] == -7.0f - 3.0f);
}

TEST_CASE("Matrix4 scalar multiplication operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	m = m * 2.0f;

	REQUIRE(m[0][0] == 0.0f * 2.0f);
	REQUIRE(m[0][1] == 9.0f * 2.0f);
	REQUIRE(m[0][2] == 3.0f * 2.0f);
	REQUIRE(m[0][3] == 2.0f * 2.0f);
	REQUIRE(m[1][0] == 1.0f * 2.0f);
	REQUIRE(m[1][1] == 8.0f * 2.0f);
	REQUIRE(m[1][2] == 4.0f * 2.0f);
	REQUIRE(m[1][3] == 6.0f * 2.0f);
	REQUIRE(m[2][0] == 2.0f * 2.0f);
	REQUIRE(m[2][1] == 7.0f * 2.0f);
	REQUIRE(m[2][2] == 5.0f * 2.0f);
	REQUIRE(m[2][3] == 1.0f * 2.0f);
	REQUIRE(m[3][0] == -2.0f * 2.0f);
	REQUIRE(m[3][1] == 0.0f * 2.0f);
	REQUIRE(m[3][2] == 4.0f * 2.0f);
	REQUIRE(m[3][3] == -7.0f * 2.0f);
}

TEST_CASE("Matrix4 scalar division operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	m = m / 2.0f;

	REQUIRE(m[0][0] == 0.0f / 2.0f);
	REQUIRE(m[0][1] == 9.0f / 2.0f);
	REQUIRE(m[0][2] == 3.0f / 2.0f);
	REQUIRE(m[0][3] == 2.0f / 2.0f);
	REQUIRE(m[1][0] == 1.0f / 2.0f);
	REQUIRE(m[1][1] == 8.0f / 2.0f);
	REQUIRE(m[1][2] == 4.0f / 2.0f);
	REQUIRE(m[1][3] == 6.0f / 2.0f);
	REQUIRE(m[2][0] == 2.0f / 2.0f);
	REQUIRE(m[2][1] == 7.0f / 2.0f);
	REQUIRE(m[2][2] == 5.0f / 2.0f);
	REQUIRE(m[2][3] == 1.0f / 2.0f);
	REQUIRE(m[3][0] == -2.0f / 2.0f);
	REQUIRE(m[3][1] == 0.0f / 2.0f);
	REQUIRE(m[3][2] == 4.0f / 2.0f);
	REQUIRE(m[3][3] == -7.0f / 2.0f);
}

TEST_CASE("Matrix4 matrix addition operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	Matrix4 n(
		5.0f, 4.0f, 3.0f, 7.0f,
		7.0f, 8.0f, 9.0f, 1.0f,
		2.0f, 1.0f, 0.0f, 0.0f,
		4.0f, 4.0f, 1.0f, 5.0f);

	Matrix4 o(m + n);

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			REQUIRE(o[x][y] == m[x][y] + n[x][y]);
		}
	}
}

TEST_CASE("Matrix4 matrix subtraction operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	Matrix4 n(
		5.0f, 4.0f, 3.0f, 7.0f,
		7.0f, 8.0f, 9.0f, 1.0f,
		2.0f, 1.0f, 0.0f, 0.0f,
		4.0f, 4.0f, 1.0f, 5.0f);

	Matrix4 o(m - n);

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			REQUIRE(o[x][y] == m[x][y] - n[x][y]);
		}
	}
}

TEST_CASE("Matrix4 scalar addition assignment operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	m += 3.0f;

	REQUIRE(m[0][0] == 0.0f + 3.0f);
	REQUIRE(m[0][1] == 9.0f + 3.0f);
	REQUIRE(m[0][2] == 3.0f + 3.0f);
	REQUIRE(m[0][3] == 2.0f + 3.0f);
	REQUIRE(m[1][0] == 1.0f + 3.0f);
	REQUIRE(m[1][1] == 8.0f + 3.0f);
	REQUIRE(m[1][2] == 4.0f + 3.0f);
	REQUIRE(m[1][3] == 6.0f + 3.0f);
	REQUIRE(m[2][0] == 2.0f + 3.0f);
	REQUIRE(m[2][1] == 7.0f + 3.0f);
	REQUIRE(m[2][2] == 5.0f + 3.0f);
	REQUIRE(m[2][3] == 1.0f + 3.0f);
	REQUIRE(m[3][0] == -2.0f + 3.0f);
	REQUIRE(m[3][1] == 0.0f + 3.0f);
	REQUIRE(m[3][2] == 4.0f + 3.0f);
	REQUIRE(m[3][3] == -7.0f + 3.0f);
}

TEST_CASE("Matrix4 scalar subtraction assignment operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	m -= 3.0f;

	REQUIRE(m[0][0] == 0.0f - 3.0f);
	REQUIRE(m[0][1] == 9.0f - 3.0f);
	REQUIRE(m[0][2] == 3.0f - 3.0f);
	REQUIRE(m[0][3] == 2.0f - 3.0f);
	REQUIRE(m[1][0] == 1.0f - 3.0f);
	REQUIRE(m[1][1] == 8.0f - 3.0f);
	REQUIRE(m[1][2] == 4.0f - 3.0f);
	REQUIRE(m[1][3] == 6.0f - 3.0f);
	REQUIRE(m[2][0] == 2.0f - 3.0f);
	REQUIRE(m[2][1] == 7.0f - 3.0f);
	REQUIRE(m[2][2] == 5.0f - 3.0f);
	REQUIRE(m[2][3] == 1.0f - 3.0f);
	REQUIRE(m[3][0] == -2.0f - 3.0f);
	REQUIRE(m[3][1] == 0.0f - 3.0f);
	REQUIRE(m[3][2] == 4.0f - 3.0f);
	REQUIRE(m[3][3] == -7.0f - 3.0f);
}

TEST_CASE("Matrix4 scalar multiplication assignment operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	m *= 2.0f;

	REQUIRE(m[0][0] == 0.0f * 2.0f);
	REQUIRE(m[0][1] == 9.0f * 2.0f);
	REQUIRE(m[0][2] == 3.0f * 2.0f);
	REQUIRE(m[0][3] == 2.0f * 2.0f);
	REQUIRE(m[1][0] == 1.0f * 2.0f);
	REQUIRE(m[1][1] == 8.0f * 2.0f);
	REQUIRE(m[1][2] == 4.0f * 2.0f);
	REQUIRE(m[1][3] == 6.0f * 2.0f);
	REQUIRE(m[2][0] == 2.0f * 2.0f);
	REQUIRE(m[2][1] == 7.0f * 2.0f);
	REQUIRE(m[2][2] == 5.0f * 2.0f);
	REQUIRE(m[2][3] == 1.0f * 2.0f);
	REQUIRE(m[3][0] == -2.0f * 2.0f);
	REQUIRE(m[3][1] == 0.0f * 2.0f);
	REQUIRE(m[3][2] == 4.0f * 2.0f);
	REQUIRE(m[3][3] == -7.0f * 2.0f);
}

TEST_CASE("Matrix4 scalar division assignment operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	m /= 2.0f;

	REQUIRE(m[0][0] == 0.0f / 2.0f);
	REQUIRE(m[0][1] == 9.0f / 2.0f);
	REQUIRE(m[0][2] == 3.0f / 2.0f);
	REQUIRE(m[0][3] == 2.0f / 2.0f);
	REQUIRE(m[1][0] == 1.0f / 2.0f);
	REQUIRE(m[1][1] == 8.0f / 2.0f);
	REQUIRE(m[1][2] == 4.0f / 2.0f);
	REQUIRE(m[1][3] == 6.0f / 2.0f);
	REQUIRE(m[2][0] == 2.0f / 2.0f);
	REQUIRE(m[2][1] == 7.0f / 2.0f);
	REQUIRE(m[2][2] == 5.0f / 2.0f);
	REQUIRE(m[2][3] == 1.0f / 2.0f);
	REQUIRE(m[3][0] == -2.0f / 2.0f);
	REQUIRE(m[3][1] == 0.0f / 2.0f);
	REQUIRE(m[3][2] == 4.0f / 2.0f);
	REQUIRE(m[3][3] == -7.0f / 2.0f);
}

TEST_CASE("Matrix4 matrix addition assignment operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	Matrix4 n;
	n += m;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (x == y) REQUIRE(n[x][y] == Approx(m[x][y] + 1.0f));
			else REQUIRE(n[x][y] == Approx(m[x][y]));
		}
	}
}

TEST_CASE("Matrix4 matrix subtraction assignment operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	Matrix4 n;
	n -= m;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (x == y) REQUIRE(n[x][y] == Approx(1.0f - m[x][y]));
			else REQUIRE(n[x][y] == Approx(0.0f - m[x][y]));
		}
	}
}

TEST_CASE("Matrix4 vector multiplication")
{
	Vector4 v(2.0f, 1.0f, 3.0f, 1.0f);
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	Vector4 u(m * v);

	REQUIRE(u.X() == Approx(5.0f));
	REQUIRE(u.Y() == Approx(47.0f));
	REQUIRE(u.Z() == Approx(29.0f));
	REQUIRE(u.W() == Approx(6.0f));
}

TEST_CASE("Matrix4 identity matrix multiplication")
{
	Matrix4 m = Matrix4() * Matrix4();

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (x == y)
			{
				REQUIRE(m[x][y] == Approx(1.0f));
			}
			else
			{
				REQUIRE(m[x][y] == Approx(0.0f));
			}
		}
	}
}

TEST_CASE("Matrix4 matrix multiplication")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	Matrix4 n(
		5.0f, 4.0f, 3.0f, 7.0f,
		7.0f, 8.0f, 9.0f, 1.0f,
		2.0f, 1.0f, 0.0f, 0.0f,
		4.0f, 4.0f, 1.0f, 5.0f);

	Matrix4 r(m * n);

	Matrix4 q(
		  3.0f,   2.0f,  7.0f,  -9.0f,
		115.0f, 107.0f, 99.0f,  71.0f,
		 69.0f,  65.0f, 49.0f,  45.0f,
		 26.0f,  29.0f, 53.0f, -15.0f);

	REQUIRE(r == q);
}

TEST_CASE("Matrix4 determinant")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	REQUIRE(m.Determinant() == Approx(-540.0f));
}

TEST_CASE("Matrix4 transpose")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	Matrix4 n(m.Transpose());

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			REQUIRE(m[x][y] == n[y][x]);
		}
	}
}

TEST_CASE("Matrix4 inverse operator")
{
	Matrix4 m(
		0.0f, 1.0f, 2.0f, -2.0f,
		9.0f, 8.0f, 7.0f,  0.0f,
		3.0f, 4.0f, 5.0f,  4.0f,
		2.0f, 6.0f, 1.0f, -7.0f);

	//Matrix multiplication has already been tested, so we should be able to rely on it.
	//A matrix multiplied by its inverse should be equal to an identity matrix, so we test that here

	Matrix4 n = !m;

	REQUIRE(n[0][0] == Approx(  -13.0f / 135.0f));
	REQUIRE(n[0][1] == Approx(  -37.0f / 135.0f));
	REQUIRE(n[0][2] == Approx(   59.0f / 135.0f));
	REQUIRE(n[0][3] == Approx(   -1.0f /   5.0f));
	REQUIRE(n[1][0] == Approx(   13.0f /  60.0f));
	REQUIRE(n[1][1] == Approx(   -2.0f /  15.0f));
	REQUIRE(n[1][2] == Approx(    1.0f /  60.0f));
	REQUIRE(n[1][3] == Approx(   -1.0f /  20.0f));
	REQUIRE(n[2][0] == Approx( -131.0f / 540.0f));
	REQUIRE(n[2][1] == Approx(   34.0f / 135.0f));
	REQUIRE(n[2][2] == Approx(   13.0f / 540.0f));
	REQUIRE(n[2][3] == Approx(    3.0f /  20.0f));
	REQUIRE(n[3][0] == Approx(   -1.0f /   9.0f));
	REQUIRE(n[3][1] == Approx(    2.0f /   9.0f));
	REQUIRE(n[3][2] == Approx(   -1.0f /   9.0f));
	REQUIRE(n[3][3] == Approx(    0.0f         ));
	
	n = n * m;

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (x == y)
			{
				REQUIRE(n[x][y] == Approx(1.0f));
			}
			else
			{
				REQUIRE(n[x][y] == Approx(0.0f).margin(0.0001));
			}
		}
	}
}

TEST_CASE("Matrix4 translation")
{
	Vector4 v(0.0f, 0.0f, 0.0f, 1.0f);

	v = Matrix4::CreateTranslation(Vector3(10.0f, 20.0f, -30.0f)) * v;

	REQUIRE(v.X() == Approx(10.0f));
	REQUIRE(v.Y() == Approx(20.0f));
	REQUIRE(v.Z() == Approx(-30.0f));
	REQUIRE(v.W() == Approx(1.0f));
}

TEST_CASE("Matrix4 rotation")
{
	Vector4 v(1.0f, 1.0f, -1.0f, 1.0f);
	Vector4 u(v);

	u = (*Matrix4::CreateRotationZ(ForceCXPR(vlk::HalfPi))) * u;
	v =   Matrix4::CreateRotationZ(          vlk::HalfPi)   * v;

	REQUIRE(v.X() == Approx(-1.0f));
	REQUIRE(v.Y() == Approx( 1.0f));
	REQUIRE(v.Z() == Approx(-1.0f));
	REQUIRE(v.W() == Approx( 1.0f));
	REQUIRE(u.X() == Approx(-1.0f));
	REQUIRE(u.Y() == Approx( 1.0f));
	REQUIRE(u.Z() == Approx(-1.0f));
	REQUIRE(u.W() == Approx( 1.0f));

	u = (*Matrix4::CreateRotationX(ForceCXPR(vlk::HalfPi))) * u;
	v =   Matrix4::CreateRotationX(          vlk::HalfPi)   * v;

	REQUIRE(v.X() == Approx(-1.0f));
	REQUIRE(v.Y() == Approx( 1.0f));
	REQUIRE(v.Z() == Approx( 1.0f));
	REQUIRE(v.W() == Approx( 1.0f));
	REQUIRE(u.X() == Approx(-1.0f));
	REQUIRE(u.Y() == Approx( 1.0f));
	REQUIRE(u.Z() == Approx( 1.0f));
	REQUIRE(u.W() == Approx( 1.0f));

	u = (*Matrix4::CreateRotationY(ForceCXPR(vlk::HalfPi))) * u;
	v =   Matrix4::CreateRotationY(          vlk::HalfPi)   * v;

	REQUIRE(v.X() == Approx( 1.0f));
	REQUIRE(v.Y() == Approx( 1.0f));
	REQUIRE(v.Z() == Approx( 1.0f));
	REQUIRE(v.W() == Approx( 1.0f));
	REQUIRE(u.X() == Approx( 1.0f));
	REQUIRE(u.Y() == Approx( 1.0f));
	REQUIRE(u.Z() == Approx( 1.0f));
	REQUIRE(u.W() == Approx( 1.0f));
}

TEST_CASE("Matrix4 scale")
{
	Vector4 v(1.5f, 3.0f, 0.3f, 1.0f);

	v = Matrix4::CreateScale(Vector3(2.0f, 3.0f, 10.0f)) * v;

	REQUIRE(v.X() == Approx(3.0f));
	REQUIRE(v.Y() == Approx(9.0f));
	REQUIRE(v.Z() == Approx(3.0f));
	REQUIRE(v.W() == Approx(1.0f));
}

TEST_CASE("Matrix4 reflection")
{
	Vector4 v(1.0f, 1.0f, 1.0f, 1.0f);

	v = Matrix4::CreateReflectionX() * v;

	REQUIRE(v.X() == Approx(-1.0f));
	REQUIRE(v.Y() == Approx(1.0f));
	REQUIRE(v.Z() == Approx(1.0f));
	REQUIRE(v.W() == Approx(1.0f));

	v = Matrix4::CreateReflectionY() * v;

	REQUIRE(v.X() == Approx(-1.0f));
	REQUIRE(v.Y() == Approx(-1.0f));
	REQUIRE(v.Z() == Approx(1.0f));
	REQUIRE(v.W() == Approx(1.0f));

	v = Matrix4::CreateReflectionZ() * v;

	REQUIRE(v.X() == Approx(-1.0f));
	REQUIRE(v.Y() == Approx(-1.0f));
	REQUIRE(v.Z() == Approx(-1.0f));
	REQUIRE(v.W() == Approx(1.0f));
}

TEST_CASE("Matrix4 angle-axis")
{
	Vector4 v(-1.f, -1.f, -1.f, 1.f);
	Matrix4 m(Matrix4::CreateRotation(vlk::Pi, Vector3::Normalized(Vector3(1.f, 1.f, 1.f))));
	Matrix4 n(Matrix4::CreateRotation(ForceCXPR(vlk::Pi), 
		ForceCXPR(Vector3::Normalized(Vector3(1.f, 1.f, 1.f)))));
	Vector4 u(m * v);
	
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			REQUIRE(m[x][y] == Approx(n[x][y]));
		}

	}

	REQUIRE(v[0] == Approx(-1.f));
	REQUIRE(v[1] == Approx(-1.f));
	REQUIRE(v[2] == Approx(-1.f));
	REQUIRE(v[3] == Approx( 1.f));
}
