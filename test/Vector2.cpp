#include <random>
#define CATCH_CONFIG_MAIN
#include "ValkyrieEngineCommon/Vector.hpp"
#include "catch2/catch.hpp"

using namespace vlk;

class RandomVector2Generator : public Catch::Generators::IGenerator<Vector2>
{
	static std::mt19937 rng;
	std::uniform_real_distribution<float> dist;
	Vector2 v;

	public:
	RandomVector2Generator() :
		dist(-128.0f, 127.0f)
	{
		next();
	}

	static Catch::Generators::GeneratorWrapper<Vector2> GetWrapper()
	{
		return Catch::Generators::GeneratorWrapper<Vector2>(
				std::unique_ptr<IGenerator<Vector2>>(new RandomVector2Generator()));
	}

	const Vector2& get() const override
	{
		return v;
	}

	bool next() override
	{
		v.x = dist(rng);
		v.y = dist(rng);
		return true;
	}
};

std::mt19937 RandomVector2Generator::rng;

TEST_CASE("Vector2 default constructor")
{
	Vector2 v;
	REQUIRE(v.x == 0.0f);
	REQUIRE(v.y == 0.0f);
}

TEST_CASE("Vector2 single float constructor")
{
	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));
	Vector2 v(i);
	REQUIRE(v.x == i);
	REQUIRE(v.y == i);
}

TEST_CASE("Vector2 dual float constructor")
{
	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto j = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector2 v(i, j);
	REQUIRE(v.x == i);
	REQUIRE(v.y == j);
}

TEST_CASE("Vector2 copy constructor")
{
	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto j = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector2 v(i, j);
	Vector2 u(v);
	REQUIRE(u.x == i);
	REQUIRE(u.y == j);
}

TEST_CASE("Vector2 move constructor")
{
	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto j = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector2 v(std::move(Vector2(i, j)));
	REQUIRE(v.x == i);
	REQUIRE(v.y == j);
}

TEST_CASE("Vector2 copy assignment operator")
{
	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto j = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector2 v(6.0f, -7.0f);
	Vector2 u(i, j);
	v = u;
	REQUIRE(v.x == i);
	REQUIRE(u.x == i);
	REQUIRE(v.y == j);
	REQUIRE(u.y == j);
}

TEST_CASE("Vector2 move assignment operator")
{
	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto j = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector2 v(10.0f, 20.0f);
	v = std::move(Vector2(i, j));

	REQUIRE(v.x == i);
	REQUIRE(v.y == j);
}

TEST_CASE("Vector2 negate operator")
{
	Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	Vector2 u(-v);

	REQUIRE(u.x == -v.x);
	REQUIRE(u.y == -v.y);
}

TEST_CASE("Vector2 equality operator")
{
	Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	Vector2 u = GENERATE(take(10, RandomVector2Generator::GetWrapper()));

	REQUIRE(!(u == v));
	REQUIRE(!(v == u));
	REQUIRE(u == u);
	REQUIRE(v == v);
}

TEST_CASE("Vector2 inequality operator")
{
	Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	Vector2 u = GENERATE(take(10, RandomVector2Generator::GetWrapper()));

	REQUIRE(v != u);
	REQUIRE(u != v);
	REQUIRE(!(v != v));
	REQUIRE(!(u != u));
}

TEST_CASE("Vector2 addition operator")
{	
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	Vector2 t(v + u);

	REQUIRE(t.x == (v.x + u.x));
	REQUIRE(t.y == (v.y + u.y));
}

TEST_CASE("Vector2 subtraction operator")
{	
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	Vector2 t(v - u);

	REQUIRE(t.x == (v.x - u.x));
	REQUIRE(t.y == (v.y - u.y));
}

TEST_CASE("Vector2 scale up operator")
{	
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	auto k = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector2 t(v * k);

	REQUIRE(t.x == (v.x * k));
	REQUIRE(t.y == (v.y * k));
}

TEST_CASE("Vector2 scale down operator")
{	
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	auto k = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector2 t(v / k);

	REQUIRE(t.x == (v.x / k));
	REQUIRE(t.y == (v.y / k));
}

TEST_CASE("Vector2 addition assignment operator")
{	
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	Vector2 w(v);
	w += u;

	REQUIRE(w.x == (v.x + u.x));
	REQUIRE(w.y == (v.y + u.y));
}

TEST_CASE("Vector2 subtraction assignment operator")
{	
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	Vector2 w(v);
	w -= u;

	REQUIRE(w.x == (v.x - u.x));
	REQUIRE(w.y == (v.y - u.y));
}

TEST_CASE("Vector2 scale up assignment operator")
{	
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	auto k = GENERATE(take(10, random(-128.0f, 127.0f)));
	Vector2 u(v);

	u *= k;

	REQUIRE(u.x == (v.x * k));
	REQUIRE(u.y == (v.y * k));
}

TEST_CASE("Vector2 scale down assignment operator")
{	
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	auto k = GENERATE(take(10, random(-128.0f, 127.0f)));
	Vector2 u(v);

	u /= k;

	REQUIRE(u.x == (v.x / k));
	REQUIRE(u.y == (v.y / k));
}

TEST_CASE("Vector2 length")
{
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	REQUIRE(v.Length() == Approx(std::sqrt((v.x * v.x) + (v.y * v.y))));
}

TEST_CASE("Vector2 square length")
{
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	REQUIRE(v.Length() == Approx(std::sqrt((v.x * v.x) + (v.y * v.y))));
	REQUIRE(v.SquareLength() == Approx(v.Length() * v.Length()));
}

TEST_CASE("Vector2 normalize")
{
	Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	v.Normalize();

	REQUIRE(v.Length() == Approx(1.0f));
}

TEST_CASE("Vector2 distance to zero")
{	
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));

	REQUIRE(Vector2::Distance(v, Vector2::Zero()) == Approx(v.Length()));
	REQUIRE(Vector2::Distance(Vector2::Zero(), v) == Approx(v.Length()));
}

TEST_CASE("Vector2 distance")
{
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, RandomVector2Generator::GetWrapper()));

	REQUIRE(Vector2::Distance(v, u) == Approx(Vector2::Distance(u, v)));

	float dx = v.x - u.x;
	float dy = v.y - u.y;

	REQUIRE(Vector2::Distance(v, u) == Approx(std::sqrt((dx * dx) + (dy * dy))));
}

TEST_CASE("Vector2 dot")
{
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, RandomVector2Generator::GetWrapper()));

	REQUIRE(Vector2::Dot(v, u) == Approx(Vector2::Dot(u, v)));
	REQUIRE(Vector2::Dot(v, u) == Approx((v.x * u.x) + (v.y * u.y)));
}

TEST_CASE("Vector2 normalized")
{
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	Vector2 u(v);
	u.Normalize();

	REQUIRE(Vector2::Normalized(v).Length() == Approx(1.0));
	REQUIRE(Vector2::Normalized(v).x == Approx(u.x));
	REQUIRE(Vector2::Normalized(v).y == Approx(u.y));
}

TEST_CASE("Vector2 lerp")
{
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, RandomVector2Generator::GetWrapper()));

	SECTION("Step lerp")
	{
		auto t = GENERATE(range(0.0f, 1.0f, 0.1f));
		Vector2 uv(Vector2::Lerp(u, v, t));
		Vector2 vu(Vector2::Lerp(v, u, 1.0f - t));

		//Need to be a bit more liberal here, so increase the margin of error.
		REQUIRE(uv.x == Approx(vu.x).margin(0.0001));
		REQUIRE(uv.y == Approx(vu.y).margin(0.0001));
	}
}

TEST_CASE("Vector2 perpendicular")
{
	const Vector2 v = GENERATE(take(10, RandomVector2Generator::GetWrapper()));
	const Vector2 u(Vector2::Perpendicular(v));

	//Angle between v and u should be ~pi/2
	REQUIRE(std::acos((Vector2::Dot(v, u)) / (u.Length() * v.Length())) == Approx(1.5707963268));
}
