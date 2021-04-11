#include "TestValues.hpp"
#include "ValkyrieEngineCommon/VMath.hpp"
#include <stdexcept>

using namespace vlk;

TEST_CASE("Transform2D constructors")
{
	Transform2D s;

	SECTION("Transform2D default constructor")
	{
		REQUIRE(s.translation == Vector2());
		REQUIRE(s.rotation == 0.f);
		REQUIRE(s.scale == Vector2(1.f, 1.f));
		REQUIRE(s.GetMatrix() == Matrix3());
		REQUIRE(s.GetParent() == nullptr);
	}

	s.translation = Vector2(17.f, -32.f);
	s.scale = Vector2(34.f, 56.f);
	s.rotation = 46.f;

	SECTION("Transform2D equality operator")
	{
		REQUIRE(s == s);
		REQUIRE(!(s != s));

		Transform2D t(s);
		t.translation = Vector2();

		REQUIRE(t != s);
		REQUIRE(!(t == s));
	}

	SECTION("Transform2D copy constructor")
	{
		Transform2D t(s);

		REQUIRE(t.translation == s.translation);
		REQUIRE(t.rotation == s.rotation);
		REQUIRE(t.scale == s.scale);
		REQUIRE(t == s);
	}

	SECTION("Transform2D move constructor")
	{
		Transform2D tmp(s);
		Transform2D t(std::move(tmp));

		REQUIRE(t.translation == s.translation);
		REQUIRE(t.rotation == s.rotation);
		REQUIRE(t.scale == s.scale);
		REQUIRE(t == s);
	}

	SECTION("Transform2D copy assignment operator")
	{
		Transform2D t;
		t = s;
		
		REQUIRE(t.translation == s.translation);
		REQUIRE(t.rotation == s.rotation);
		REQUIRE(t.scale == s.scale);
		REQUIRE(t == s);
	}

	SECTION("Transform2D move assignment operator")
	{
		Transform2D tmp(s);
		Transform2D t = std::move(tmp);
		
		REQUIRE(t.translation == s.translation);
		REQUIRE(t.rotation == s.rotation);
		REQUIRE(t.scale == s.scale);
		REQUIRE(t == s);
	}
}

TEST_CASE("Transform2D parent hierarchy")
{
	Transform2D s;
	REQUIRE_THROWS_AS(s.SetParent(&s), std::runtime_error);
	REQUIRE(s.GetParent() == nullptr);

	Transform2D t;

	t.SetParent(&s);
	REQUIRE(t.GetParent() == &s);
	REQUIRE_THROWS_AS(s.SetParent(&t), std::runtime_error);
	REQUIRE(s.GetParent() == nullptr);

	Transform2D q;
	s.SetParent(&q);
	REQUIRE_THROWS_AS(q.SetParent(&s), std::runtime_error);
	REQUIRE(q.GetParent() == nullptr);
}

TEST_CASE("Transform2D local translate")
{
	Transform2D t;
	t.translation = Vector2(5.0f, 2.0f);
	Vector3 v(-1.0f, 2.0f, 1.f);
	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(4.f));
	REQUIRE(v.Y() == Approx(4.f));
	REQUIRE(v.Z() == Approx(1.f));
}

TEST_CASE("Transform2D local rotate")
{
	Transform2D t;
	t.rotation = vlk::HalfPi;

	Vector3 v(0.f, 0.f, 1.f);
	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(0.f));
	REQUIRE(v.Y() == Approx(0.f));
	REQUIRE(v.Z() == Approx(1.f));

	t.translation = Vector2(5.0f, 2.0f);
	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(5.f));
	REQUIRE(v.Y() == Approx(2.f));
	REQUIRE(v.Z() == Approx(1.f));

	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(3.f));
	REQUIRE(v.Y() == Approx(7.f));
	REQUIRE(v.Z() == Approx(1.f));
}

TEST_CASE("Transform2D local scale")
{
	Transform2D t;
	t.scale = Vector2(2.f, 3.f);

	Vector3 v(0.f, 0.f, 1.f);

	v = t.GetMatrix() * v;

	REQUIRE(v.X() == Approx(0.f));
	REQUIRE(v.Y() == Approx(0.f));
	REQUIRE(v.Z() == Approx(1.f));

	v = t.GetMatrix() * Vector3(1.f, 1.f, 1.f);

	REQUIRE(v.X() == Approx(2.f));
	REQUIRE(v.Y() == Approx(3.f));
	REQUIRE(v.Z() == Approx(1.f));

	t.translation = Vector2(-2.f, -1.f);

	v = t.GetMatrix() * Vector3(1.f, 1.f, 1.f);

	REQUIRE(v.X() == Approx(0.f));
	REQUIRE(v.Y() == Approx(2.f));
	REQUIRE(v.Z() == Approx(1.f));
}

TEST_CASE("Transform2D conjugate transform local")
{
	Transform2D t;
	t.translation = Vector2(5.0f, 2.0f);
	t.rotation = vlk::HalfPi;
	t.scale = Vector2(0.5f, 2.0f);
	Vector3 v(1.0f, 3.0f, 1.0f);

	v = t.GetMatrix() * v;
	REQUIRE(v.X() == Approx(-1.0));
	REQUIRE(v.Y() == Approx(2.5));
}

TEST_CASE("Transform2D global")
{
	Transform2D t;
	t.translation = Vector2(2.0f, 2.0f);
	t.rotation = vlk::HalfPi;
	t.scale = Vector2(2.f, 3.f);

	Transform2D r;
	r.translation = Vector2(-1.0f, 4.0f);
	r.rotation = -vlk::Pi;
	r.scale = Vector2(0.5f, 0.5f);

	r.SetParent(&t);

	SECTION("Transform2D global translate")
	{
		Vector2 v(r.GetWorldTranslation());
		REQUIRE(v.X() == Approx(-10.f));
		REQUIRE(v.Y() == Approx(0.f).margin(0.0001));
	}

	SECTION("Transform2D global rotation")
	{
		REQUIRE(r.GetWorldRotation() == Approx(-vlk::HalfPi));
	}

	SECTION("Transform2D global scale")
	{
		Vector2 v(r.GetWorldScale());
		REQUIRE(v.X() == Approx(1.5f));
		REQUIRE(v.Y() == Approx(-1.f));
	}

	REQUIRE(t.GetWorldMatrix() == t.GetMatrix());
	REQUIRE(r.GetWorldMatrix() == t.GetMatrix() * r.GetMatrix());
}
