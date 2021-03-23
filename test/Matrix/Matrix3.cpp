#include "TestValues.hpp"
#include "ValkyrieEngineCommon/VMath.hpp"

using namespace vlk;

TEST_CASE("Matrix3 default constructor")
{
	Matrix3 m;

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (x == y) REQUIRE(m[x][y] == 1.0f);
			else REQUIRE(m[x][y] == 0.0f);
		}
	}
}

TEST_CASE("Matrix3 nine float constructor")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
}
TEST_CASE("Matrix3 array constructor")
{
	Matrix3 m(
		VectorBase<3, Float>({ 0.0f, 9.0f, 3.0f }),
		VectorBase<3, Float>({ 1.0f, 8.0f, 4.0f }),
		VectorBase<3, Float>({ 2.0f, 7.0f, 5.0f }));

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
}

TEST_CASE("Matrix3 copy constructor")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	Matrix3 n(m);

	REQUIRE(n[0][0] == 0.0f);
	REQUIRE(n[0][1] == 9.0f);
	REQUIRE(n[0][2] == 3.0f);
	REQUIRE(n[1][0] == 1.0f);
	REQUIRE(n[1][1] == 8.0f);
	REQUIRE(n[1][2] == 4.0f);
	REQUIRE(n[2][0] == 2.0f);
	REQUIRE(n[2][1] == 7.0f);
	REQUIRE(n[2][2] == 5.0f);
}

TEST_CASE("Matrix3 move constructor")
{
	Matrix3 m(Matrix3(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f));

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
}

TEST_CASE("Matrix3 copy assignment operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	Matrix3 n = m;

	REQUIRE(n[0][0] == 0.0f);
	REQUIRE(n[0][1] == 9.0f);
	REQUIRE(n[0][2] == 3.0f);
	REQUIRE(n[1][0] == 1.0f);
	REQUIRE(n[1][1] == 8.0f);
	REQUIRE(n[1][2] == 4.0f);
	REQUIRE(n[2][0] == 2.0f);
	REQUIRE(n[2][1] == 7.0f);
	REQUIRE(n[2][2] == 5.0f);
}

TEST_CASE("Matrix3 move assignment operator")
{
	Matrix3 m;
	m = std::move(Matrix3(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f));

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 9.0f);
	REQUIRE(m[0][2] == 3.0f);
	REQUIRE(m[1][0] == 1.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 4.0f);
	REQUIRE(m[2][0] == 2.0f);
	REQUIRE(m[2][1] == 7.0f);
	REQUIRE(m[2][2] == 5.0f);
}

TEST_CASE("Matrix3 three Vector3 constructor")
{
	Matrix3 m(
		Vector3(0.0f, 1.0f, 2.0f),
		Vector3(9.0f, 8.0f, 7.0f),
		Vector3(3.0f, 4.0f, 5.0f));

	REQUIRE(m[0][0] == 0.0f);
	REQUIRE(m[0][1] == 1.0f);
	REQUIRE(m[0][2] == 2.0f);
	REQUIRE(m[1][0] == 9.0f);
	REQUIRE(m[1][1] == 8.0f);
	REQUIRE(m[1][2] == 7.0f);
	REQUIRE(m[2][0] == 3.0f);
	REQUIRE(m[2][1] == 4.0f);
	REQUIRE(m[2][2] == 5.0f);
}

TEST_CASE("Matrix3 scalar addition operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	m = m + 3.0f;

	REQUIRE(m[0][0] == Approx(3.0f));
	REQUIRE(m[0][1] == Approx(12.0f));
	REQUIRE(m[0][2] == Approx(6.0f));
	REQUIRE(m[1][0] == Approx(4.0f));
	REQUIRE(m[1][1] == Approx(11.0f));
	REQUIRE(m[1][2] == Approx(7.0f));
	REQUIRE(m[2][0] == Approx(5.0f));
	REQUIRE(m[2][1] == Approx(10.0f));
	REQUIRE(m[2][2] == Approx(8.0f));
}

TEST_CASE("Matrix3 scalar subtraction operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	m = m - 3.0f;

	REQUIRE(m[0][0] == Approx(-3.0f));
	REQUIRE(m[0][1] == Approx(6.0f));
	REQUIRE(m[0][2] == Approx(0.0f));
	REQUIRE(m[1][0] == Approx(-2.0f));
	REQUIRE(m[1][1] == Approx(5.0f));
	REQUIRE(m[1][2] == Approx(1.0f));
	REQUIRE(m[2][0] == Approx(-1.0f));
	REQUIRE(m[2][1] == Approx(4.0f));
	REQUIRE(m[2][2] == Approx(2.0f));
}

TEST_CASE("Matrix3 scalar multiplication operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	m = m * 2.0f;

	REQUIRE(m[0][0] == Approx(0.0f));
	REQUIRE(m[0][1] == Approx(18.0f));
	REQUIRE(m[0][2] == Approx(6.0f));
	REQUIRE(m[1][0] == Approx(2.0f));
	REQUIRE(m[1][1] == Approx(16.0f));
	REQUIRE(m[1][2] == Approx(8.0f));
	REQUIRE(m[2][0] == Approx(4.0f));
	REQUIRE(m[2][1] == Approx(14.0f));
	REQUIRE(m[2][2] == Approx(10.0f));
}

TEST_CASE("Matrix3 scalar division operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	m = m / 2.0f;

	REQUIRE(m[0][0] == Approx(0.0f));
	REQUIRE(m[0][1] == Approx(4.5f));
	REQUIRE(m[0][2] == Approx(1.5f));
	REQUIRE(m[1][0] == Approx(0.5f));
	REQUIRE(m[1][1] == Approx(4.0f));
	REQUIRE(m[1][2] == Approx(2.0f));
	REQUIRE(m[2][0] == Approx(1.0f));
	REQUIRE(m[2][1] == Approx(3.5f));
	REQUIRE(m[2][2] == Approx(2.5f));
}

TEST_CASE("Matrix3 matrix addition operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	Matrix3 n(
		5.0f, 4.0f, 3.0f,
		7.0f, 8.0f, 9.0f,
		2.0f, 1.0f, 0.0f);

	Matrix3 o(m + n);

	REQUIRE(o[0][0] == Approx(5.0f));
	REQUIRE(o[0][1] == Approx(16.0f));
	REQUIRE(o[0][2] == Approx(5.0f));
	REQUIRE(o[1][0] == Approx(5.0f));
	REQUIRE(o[1][1] == Approx(16.0f));
	REQUIRE(o[1][2] == Approx(5.0f));
	REQUIRE(o[2][0] == Approx(5.0f));
	REQUIRE(o[2][1] == Approx(16.0f));
	REQUIRE(o[2][2] == Approx(5.0f));
}

TEST_CASE("Matrix3 matrix subtraction operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	Matrix3 n(
		5.0f, 4.0f, 3.0f,
		7.0f, 8.0f, 9.0f,
		2.0f, 1.0f, 0.0f);

	Matrix3 o(m - n);

	REQUIRE(o[0][0] == Approx(-5.0f));
	REQUIRE(o[0][1] == Approx(2.0f));
	REQUIRE(o[0][2] == Approx(1.0f));
	REQUIRE(o[1][0] == Approx(-3.0f));
	REQUIRE(o[1][1] == Approx(0.0f));
	REQUIRE(o[1][2] == Approx(3.0f));
	REQUIRE(o[2][0] == Approx(-1.0f));
	REQUIRE(o[2][1] == Approx(-2.0f));
	REQUIRE(o[2][2] == Approx(5.0f));
}

TEST_CASE("Matrix3 scalar addition assignment operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	m += 3.0f;

	REQUIRE(m[0][0] == Approx(3.0f));
	REQUIRE(m[0][1] == Approx(12.0f));
	REQUIRE(m[0][2] == Approx(6.0f));
	REQUIRE(m[1][0] == Approx(4.0f));
	REQUIRE(m[1][1] == Approx(11.0f));
	REQUIRE(m[1][2] == Approx(7.0f));
	REQUIRE(m[2][0] == Approx(5.0f));
	REQUIRE(m[2][1] == Approx(10.0f));
	REQUIRE(m[2][2] == Approx(8.0f));
}

TEST_CASE("Matrix3 scalar subtraction assignment operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	m -= 3.0f;

	REQUIRE(m[0][0] == Approx(-3.0f));
	REQUIRE(m[0][1] == Approx(6.0f));
	REQUIRE(m[0][2] == Approx(0.0f));
	REQUIRE(m[1][0] == Approx(-2.0f));
	REQUIRE(m[1][1] == Approx(5.0f));
	REQUIRE(m[1][2] == Approx(1.0f));
	REQUIRE(m[2][0] == Approx(-1.0f));
	REQUIRE(m[2][1] == Approx(4.0f));
	REQUIRE(m[2][2] == Approx(2.0f));
}

TEST_CASE("Matrix3 scalar multiplication assignment operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	m *= 2.0f;

	REQUIRE(m[0][0] == Approx(0.0f));
	REQUIRE(m[0][1] == Approx(18.0f));
	REQUIRE(m[0][2] == Approx(6.0f));
	REQUIRE(m[1][0] == Approx(2.0f));
	REQUIRE(m[1][1] == Approx(16.0f));
	REQUIRE(m[1][2] == Approx(8.0f));
	REQUIRE(m[2][0] == Approx(4.0f));
	REQUIRE(m[2][1] == Approx(14.0f));
	REQUIRE(m[2][2] == Approx(10.0f));
}

TEST_CASE("Matrix3 scalar division assignment operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	m /= 2.0f;

	REQUIRE(m[0][0] == Approx(0.0f));
	REQUIRE(m[0][1] == Approx(4.5f));
	REQUIRE(m[0][2] == Approx(1.5f));
	REQUIRE(m[1][0] == Approx(0.5f));
	REQUIRE(m[1][1] == Approx(4.0f));
	REQUIRE(m[1][2] == Approx(2.0f));
	REQUIRE(m[2][0] == Approx(1.0f));
	REQUIRE(m[2][1] == Approx(3.5f));
	REQUIRE(m[2][2] == Approx(2.5f));
}

TEST_CASE("Matrix3 matrix addition assignment operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	Matrix3 n(
		5.0f, 4.0f, 3.0f,
		7.0f, 8.0f, 9.0f,
		2.0f, 1.0f, 0.0f);

	m += n;

	REQUIRE(m[0][0] == Approx(5.0f));
	REQUIRE(m[0][1] == Approx(16.0f));
	REQUIRE(m[0][2] == Approx(5.0f));
	REQUIRE(m[1][0] == Approx(5.0f));
	REQUIRE(m[1][1] == Approx(16.0f));
	REQUIRE(m[1][2] == Approx(5.0f));
	REQUIRE(m[2][0] == Approx(5.0f));
	REQUIRE(m[2][1] == Approx(16.0f));
	REQUIRE(m[2][2] == Approx(5.0f));
}

TEST_CASE("Matrix3 matrix subtraction assignment operator")
{
	Matrix3 m(
		0.0f, 1.0f, 2.0f,
		9.0f, 8.0f, 7.0f,
		3.0f, 4.0f, 5.0f);

	Matrix3 n(
		5.0f, 4.0f, 3.0f,
		7.0f, 8.0f, 9.0f,
		2.0f, 1.0f, 0.0f);

	m -= n;

	REQUIRE(m[0][0] == Approx(-5.0f));
	REQUIRE(m[0][1] == Approx(2.0f));
	REQUIRE(m[0][2] == Approx(1.0f));
	REQUIRE(m[1][0] == Approx(-3.0f));
	REQUIRE(m[1][1] == Approx(0.0f));
	REQUIRE(m[1][2] == Approx(3.0f));
	REQUIRE(m[2][0] == Approx(-1.0f));
	REQUIRE(m[2][1] == Approx(-2.0f));
	REQUIRE(m[2][2] == Approx(5.0f));
}

TEST_CASE("Matrix3 vector multiplication")
{
	Vector3 v(2.0f, 1.0f, 3.0f);
	Matrix3 m(
		1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f);

	Vector3 u(m * v);

	REQUIRE(u.X() == Approx(13.0f));
	REQUIRE(u.Y() == Approx(31.0f));
	REQUIRE(u.Z() == Approx(49.0f));
}

TEST_CASE("Matrix3 identity matrix multiplication")
{
	Matrix3 m = Matrix3() * Matrix3();

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
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

TEST_CASE("Matrix3 matrix multiplication")
{
	Matrix3 m(
		-4,  5, -3,
		 6,  1,  7,
		 8,  9,  3);

	Matrix3 n(
		-1,  4,  2,
		-2, -4,  5,
		 0,  6,  7);

	Matrix3 r(m * n);

	REQUIRE(r[0][0] == Approx(-6));
	REQUIRE(r[0][1] == Approx(-8));
	REQUIRE(r[0][2] == Approx(-26));
	REQUIRE(r[1][0] == Approx(-54));
	REQUIRE(r[1][1] == Approx( 62));
	REQUIRE(r[1][2] == Approx( 14));
	REQUIRE(r[2][0] == Approx(-4));
	REQUIRE(r[2][1] == Approx( 66));
	REQUIRE(r[2][2] == Approx( 82));
}

TEST_CASE("Matrix3 determinant")
{
	Matrix3 m(
		6.0f, 1.0f, 1.0f,
		4.0f, -2.0f, 5.0f,
		2.0f, 8.0f, 7.0f);

	REQUIRE(m.Determinant() == Approx(-306.0f));
}

TEST_CASE("Matrix3 transpose")
{
	Matrix3 m(
		6.0f, 1.0f, 1.0f,
		4.0f, -2.0f, 5.0f,
		2.0f, 8.0f, 7.0f);

	Matrix3 n(m.Transpose());

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			REQUIRE(m[x][y] == n[y][x]);
		}
	}
}

TEST_CASE("Matrix3 inverse operator")
{
	Matrix3 m(
		5.0f, 1.0f, 3.0f,
		9.0f, 5.0f, 8.0f,
		7.0f, 8.0f, 5.0f);

	//Matrix multiplication has already been tested, so we should be able to rely on it.
	//A matrix multiplied by its inverse should be equal to an identity matrix, so we test that here

	Matrix3 n = !m;

	REQUIRE(n[0][0] == Approx( 39.f / 73.f));
	REQUIRE(n[1][0] == Approx(-19.f / 73.f));
	REQUIRE(n[2][0] == Approx( 07.f / 73.f));
	REQUIRE(n[0][1] == Approx(-11.f / 73.f));
	REQUIRE(n[1][1] == Approx( -4.f / 73.f));
	REQUIRE(n[2][1] == Approx( 13.f / 73.f));
	REQUIRE(n[0][2] == Approx(-37.f / 73.f));
	REQUIRE(n[1][2] == Approx( 33.f / 73.f));
	REQUIRE(n[2][2] == Approx(-16.f / 73.f));

	
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

TEST_CASE("Matrix3 equality operator")
{
	Matrix3 m(
		5.0f, 1.0f, 3.0f,
		9.0f, 5.0f, 8.0f,
		7.0f, 8.0f, 5.0f);
	
	Matrix3 n(
		5.0f, 1.0f, 3.0f,
		9.0f, 5.0f, 8.0f,
		7.0f, 2.0f, 5.0f);

	REQUIRE(m == m);
	REQUIRE(n == n);
	REQUIRE(!(m == n));
	REQUIRE(!(n == m));
}

TEST_CASE("Matrix3 inequality operator")
{
	Matrix3 m(
		5.0f, 1.0f, 3.0f,
		9.0f, 5.0f, 8.0f,
		7.0f, 8.0f, 5.0f);
	
	Matrix3 n(
		5.0f, 1.0f, 3.0f,
		9.0f, 5.0f, 8.0f,
		7.0f, 2.0f, 5.0f);

	REQUIRE(m != n);
	REQUIRE(n != m);
	REQUIRE(!(m != m));
	REQUIRE(!(n != n));
}

TEST_CASE("Matrix3 translation")
{
	Vector3 v(0.0f, 0.0f, 1.0f);
	Matrix3 m(Matrix3::CreateTranslation(Vector2(10.f, 20.f)));

	v = m * v;

	REQUIRE(v.X() == Approx(10.0f));
	REQUIRE(v.Y() == Approx(20.0f));
	REQUIRE(v.Z() == Approx(1.0f));
}

TEST_CASE("Matrix3 rotation")
{
	Vector3 v(1.0f, 1.0f, 1.0f);
	Vector3 u = (*Matrix3::CreateRotation(ForceCXPR(1.5707963268f))) * v;
	v = Matrix3::CreateRotation(1.5707963268f) * v;

	REQUIRE(v.X() == Approx(-1.0f));
	REQUIRE(v.Y() == Approx(1.0f));
	REQUIRE(v.Z() == Approx(1.0f));
	REQUIRE(u.X() == Approx(-1.0f));
	REQUIRE(u.Y() == Approx(1.0f));
	REQUIRE(u.Z() == Approx(1.0f));
}

TEST_CASE("Matrix3 scale")
{
	Vector3 v(1.5f, 3.0f, 1.0f);

	v = Matrix3::CreateScale(Vector2(2.0f, 3.0f)) * v;

	REQUIRE(v.X() == Approx(3.0f));
	REQUIRE(v.Y() == Approx(9.0f));
	REQUIRE(v.Z() == Approx(1.0f));
}

TEST_CASE("Matrix3 reflection")
{
	Vector3 v(1.0f, 1.0f, 1.0f);

	v = Matrix3::CreateReflectionX() * v;

	REQUIRE(v.X() == Approx(-1.0f));
	REQUIRE(v.Y() == Approx(1.0f));
	REQUIRE(v.Z() == Approx(1.0f));

	v = Matrix3::CreateReflectionY() * v;

	REQUIRE(v.X() == Approx(-1.0f));
	REQUIRE(v.Y() == Approx(-1.0f));
	REQUIRE(v.Z() == Approx(1.0f));
}
