#include "TestValues.hpp"
#include "ValkyrieEngineCommon/Quaternion.hpp"
#include "ValkyrieEngineCommon/Matrix.hpp"
#include "ValkyrieEngineCommon/VMath.hpp"

using namespace vlk;

TEST_CASE("Quaternion default constructor")
{
	Quaternion q;

	REQUIRE(q[0] == 0.0f);
	REQUIRE(q[1] == 0.0f);
	REQUIRE(q[2] == 0.0f);
	REQUIRE(q[3] == 1.0f);
}

TEST_CASE("Quaternion value constructor")
{
	Quaternion q(1.0f, 2.0f, 5.0f, -2.0f);

	REQUIRE(q[0] == 1.0f);
	REQUIRE(q[1] == 2.0f);
	REQUIRE(q[2] == 5.0f);
	REQUIRE(q[3] == -2.0f);
}

TEST_CASE("Quaternion copy constructor")
{
	Quaternion q(1.0f, 2.0f, 5.0f, -2.0f);
	Quaternion p(q);

	REQUIRE(p[0] == 1.0f);
	REQUIRE(p[1] == 2.0f);
	REQUIRE(p[2] == 5.0f);
	REQUIRE(p[3] == -2.0f);
}

TEST_CASE("Quaternion move constructor")
{
	Quaternion p(std::move(Quaternion(1.0f, 2.0f, 5.0f, -2.0f)));

	REQUIRE(p[0] == 1.0f);
	REQUIRE(p[1] == 2.0f);
	REQUIRE(p[2] == 5.0f);
	REQUIRE(p[3] == -2.0f);
}

TEST_CASE("Quaternion copy assignment operator")
{
	Quaternion q(1.0f, 2.0f, 5.0f, -2.0f);
	Quaternion p;
	p = q;

	REQUIRE(p[0] == 1.0f);
	REQUIRE(p[1] == 2.0f);
	REQUIRE(p[2] == 5.0f);
	REQUIRE(p[3] == -2.0f);
}

TEST_CASE("Quaternion move assignment operator")
{
	Quaternion p;
	p = std::move(Quaternion(1.0f, 2.0f, 5.0f, -2.0f));

	REQUIRE(p[0] == 1.0f);
	REQUIRE(p[1] == 2.0f);
	REQUIRE(p[2] == 5.0f);
	REQUIRE(p[3] == -2.0f);
}

TEST_CASE("Quaternion equality operator")
{
	Quaternion q(1.0f, 2.0f, 5.0f, -2.0f);
	Quaternion p;

	REQUIRE(q == q);
	REQUIRE(p == p);
	REQUIRE(!(q == p));
	REQUIRE(!(p == q));
}

TEST_CASE("Quaternion inequality operator")
{
	Quaternion q(1.0f, 2.0f, 5.0f, -2.0f);
	Quaternion p;

	REQUIRE(q != p);
	REQUIRE(p != q);
	REQUIRE(!(p != p));
	REQUIRE(!(q != q));
}

TEST_CASE("Quaternion to matrix")
{
	Vector4 v(1.0f, 0.0f, 0.0f, 1.0f);
	Vector4 u(1.0f, 0.0f, 0.0f, 1.0f);

	//SECTION("Rotation Z")
	{
		Quaternion q(Quaternion::RotationZ(vlk::HalfPi));
		Quaternion p(Quaternion::RotationZ(ForceCXPR(vlk::HalfPi)));

		Matrix4 m(Matrix4::CreateRotation(q));
		Matrix4 n(Matrix4::CreateRotation(ForceCXPR(p)));

		v = m * v;
		u = n * u;

		REQUIRE(v[0] == Approx(0.0f).margin(0.0001));
		REQUIRE(v[1] == Approx(1.0f));
		REQUIRE(v[2] == Approx(0.0f).margin(0.0001));
		REQUIRE(v[3] == Approx(1.0f));

		REQUIRE(u[0] == Approx(0.0f).margin(0.0001));
		REQUIRE(u[1] == Approx(1.0f));
		REQUIRE(u[2] == Approx(0.0f).margin(0.0001));
		REQUIRE(u[3] == Approx(1.0f));
	}

	//SECTION("Rotation X")
	{
		Quaternion q(Quaternion::RotationX(vlk::HalfPi));
		Quaternion p(Quaternion::RotationX(ForceCXPR(vlk::HalfPi)));

		Matrix4 m(Matrix4::CreateRotation(q));
		Matrix4 n(Matrix4::CreateRotation(ForceCXPR(p)));

		v = m * v;
		u = n * u;

		REQUIRE(v[0] == Approx(0.0f).margin(0.0001));
		REQUIRE(v[1] == Approx(0.0f).margin(0.0001));
		REQUIRE(v[2] == Approx(1.0f));
		REQUIRE(v[3] == Approx(1.0f));

		REQUIRE(u[0] == Approx(0.0f).margin(0.0001));
		REQUIRE(u[1] == Approx(0.0f).margin(0.0001));
		REQUIRE(u[2] == Approx(1.0f));
		REQUIRE(u[3] == Approx(1.0f));
	}

	//SECTION("Rotation Y")
	{
		Quaternion q(Quaternion::RotationY(vlk::HalfPi));
		Quaternion p(Quaternion::RotationY(ForceCXPR(vlk::HalfPi)));

		Matrix4 m(Matrix4::CreateRotation(q));
		Matrix4 n(Matrix4::CreateRotation(ForceCXPR(p)));

		v = m * v;
		u = n * u;

		REQUIRE(v[0] == Approx(1.0f));
		REQUIRE(v[1] == Approx(0.0f).margin(0.0001));
		REQUIRE(v[2] == Approx(0.0f).margin(0.0001));
		REQUIRE(v[3] == Approx(1.0f));

		REQUIRE(u[0] == Approx(1.0f));
		REQUIRE(u[1] == Approx(0.0f).margin(0.0001));
		REQUIRE(u[2] == Approx(0.0f).margin(0.0001));
		REQUIRE(u[3] == Approx(1.0f));
	}
}

TEST_CASE("Quaternion Multiplication")
{
	Quaternion q(
		Quaternion::RotationY(-vlk::HalfPi) *
		Quaternion::RotationZ(-vlk::HalfPi) *
		Quaternion::RotationX(vlk::Pi) *
		Quaternion::RotationZ(vlk::HalfPi));
	Vector4 v(1.f, 0.f, 0.f, 1.f);

	v = Matrix4::CreateRotation(q) * v;

	REQUIRE(v[0] == Approx(0.f).margin(0.0001));
	REQUIRE(v[1] == Approx(0.f).margin(0.0001));
	REQUIRE(v[2] == Approx(-1.f).margin(0.0001));
	REQUIRE(v[3] == Approx(1.f));
}
