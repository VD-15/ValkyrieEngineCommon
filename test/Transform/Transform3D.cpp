#include "TestValues.hpp"
#include "ValkyrieEngineCommon/VMath.hpp"
#include <stdexcept>

using namespace vlk;

TEST_CASE("Transform3D constructors")
{
	Transform3D s;

	SECTION("Transform3D default constructor")
	{
		REQUIRE(s.translation == Vector3());
		REQUIRE(s.rotation == Quaternion());
		REQUIRE(s.scale == Vector3(1.f, 1.f, 1.f));
		REQUIRE(s.GetMatrix() == Matrix4());
		REQUIRE(s.GetParent() == nullptr);
	}

	s.translation = Vector3(17.f, -32.f, 14.f);
	s.scale = Vector3(34.f, 56.f, -12.f);
	s.rotation = Quaternion::AngleAxis(1.4536f, Vector3::Normalized(Vector3(3.f, 7.f, -5.f)));

	SECTION("Transform3D equality operator")
	{
		REQUIRE(s == s);
		REQUIRE(!(s != s));

		Transform3D t(s);
		t.translation = Vector3();

		REQUIRE(t != s);
		REQUIRE(!(t == s));
	}

	SECTION("Transform3D copy constructor")
	{
		Transform3D t(s);

		REQUIRE(t.translation == s.translation);
		REQUIRE(t.rotation == s.rotation);
		REQUIRE(t.scale == s.scale);
		REQUIRE(t == s);
	}

	SECTION("Transform3D move constructor")
	{
		Transform3D t(std::move(Transform3D(s)));

		REQUIRE(t.translation == s.translation);
		REQUIRE(t.rotation == s.rotation);
		REQUIRE(t.scale == s.scale);
		REQUIRE(t == s);
	}

	SECTION("Transform3D copy assignment operator")
	{
		Transform3D t;
		t = s;
		
		REQUIRE(t.translation == s.translation);
		REQUIRE(t.rotation == s.rotation);
		REQUIRE(t.scale == s.scale);
		REQUIRE(t == s);
	}

	SECTION("Transform3D move assignment operator")
	{
		Transform3D t;
		t = std::move(Transform3D(s));
		
		REQUIRE(t.translation == s.translation);
		REQUIRE(t.rotation == s.rotation);
		REQUIRE(t.scale == s.scale);
		REQUIRE(t == s);
	}
}

TEST_CASE("Transform3D parent hierarchy")
{
	Transform3D s;
	REQUIRE_THROWS_AS(s.SetParent(&s), std::runtime_error);
	REQUIRE(s.GetParent() == nullptr);

	Transform3D t;

	t.SetParent(&s);
	REQUIRE(t.GetParent() == &s);
	REQUIRE_THROWS_AS(s.SetParent(&t), std::runtime_error);
	REQUIRE(s.GetParent() == nullptr);

	Transform3D q;
	s.SetParent(&q);
	REQUIRE_THROWS_AS(q.SetParent(&s), std::runtime_error);
	REQUIRE(q.GetParent() == nullptr);
}

TEST_CASE("Transform3D local translate")
{
	Transform3D t;
	t.translation = Vector3(5.0f, 2.0f, -2.f);
	Vector4 v(-1.0f, 2.0f, -5.f, 1.f);
	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(4.f));
	REQUIRE(v.Y() == Approx(4.f));
	REQUIRE(v.Z() == Approx(-7.f));
	REQUIRE(v.W() == Approx(1.f));
}

TEST_CASE("Transform3D local rotate")
{
	Transform3D t;
	t.rotation = Quaternion::AngleAxis(vlk::HalfPi, Vector3::Up());

	Vector4 v(0.f, 0.f, 0.f, 1.f);
	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(0.f));
	REQUIRE(v.Y() == Approx(0.f));
	REQUIRE(v.Z() == Approx(0.f));
	REQUIRE(v.W() == Approx(1.f));

	t.translation = Vector3(5.0f, 2.0f, -1.f);
	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(5.f));
	REQUIRE(v.Y() == Approx(2.f));
	REQUIRE(v.Z() == Approx(-1.f));
	REQUIRE(v.W() == Approx(1.f));

	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(4.f));
	REQUIRE(v.Y() == Approx(4.f));
	REQUIRE(v.Z() == Approx(-6.f));
	REQUIRE(v.W() == Approx(1.f));
}

TEST_CASE("Transform3D local scale")
{
	Transform3D t;
	t.scale = Vector3(2.f, 3.f, 4.f);

	Vector4 v(0.f, 0.f, 0.f, 1.f);

	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(0.f));
	REQUIRE(v.Y() == Approx(0.f));
	REQUIRE(v.Z() == Approx(0.f));
	REQUIRE(v.W() == Approx(1.f));

	v = t.GetMatrix() * Vector4(1.f, 1.f, 1.f, 1.f);

	REQUIRE(v.X() == Approx(2.f));
	REQUIRE(v.Y() == Approx(3.f));
	REQUIRE(v.Z() == Approx(4.f));
	REQUIRE(v.W() == Approx(1.f));

	t.translation = Vector3(-2.f, -1.f, 3.f);

	v = t.GetMatrix() * Vector4(1.f, 1.f, 1.f, 1.f);

	REQUIRE(v.X() == Approx(0.f));
	REQUIRE(v.Y() == Approx(2.f));
	REQUIRE(v.Z() == Approx(7.f));
	REQUIRE(v.W() == Approx(1.f));
}

//TODO:

/*
TEST_CASE("Transform3D conjugate transform local")
{
	Transform3D t;
	t.translation = Vector3(5.0f, 2.0f, 2.f);
	t.rotation = Quaternion::AngleAxis(vlk::HalfPi, Vector3(0.f, 0.f, 1.f));
	t.scale = Vector3(0.5f, 2.0f, 1.f);
	Vector4 v(1.0f, 3.0f, 2.0f, 1.f);

	v = t.GetMatrix() * v;
	REQUIRE(v.X() == Approx(-1.0));
	REQUIRE(v.Y() == Approx(2.5));
	REQUIRE(v.Z() == Approx());
}

TEST_CASE("Transform3D global")
{
	Transform3D t;
	t.translation = Vector3(2.0f, 2.0f);
	t.rotation = vlk::HalfPi;
	t.scale = Vector3(2.f, 3.f);

	Transform3D r;
	r.translation = Vector3(-1.0f, 4.0f);
	r.rotation = -vlk::Pi;
	r.scale = Vector3(0.5f, 0.5f);

	r.SetParent(&t);

	SECTION("Transform3D global translate")
	{
		Vector3 v(r.GetWorldTranslation());
		REQUIRE(v.X() == Approx(-10.f));
		REQUIRE(v.Y() == Approx(0.f).margin(0.0001));
	}

	SECTION("Transform3D global rotation")
	{
		REQUIRE(r.GetWorldRotation() == Approx(-vlk::HalfPi));
	}

	SECTION("Transform3D global scale")
	{
		Vector3 v(r.GetWorldScale());
		REQUIRE(v.X() == Approx(1.5f));
		REQUIRE(v.Y() == Approx(-1.f));
	}

	REQUIRE(t.GetWorldMatrix() == t.GetMatrix());
	REQUIRE(r.GetWorldMatrix() == t.GetMatrix() * r.GetMatrix());
}*/
