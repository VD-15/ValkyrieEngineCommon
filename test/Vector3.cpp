#include <memory>
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "ValkyrieEngineCommon/Vector.hpp"
#include <random>

using namespace vlk;

class RandomVector3Generator : public Catch::Generators::IGenerator<Vector3>
{
	static std::mt19937 rng;
	std::uniform_real_distribution<float> dist;
	Vector3 v;
	public:
	RandomVector3Generator() :
		dist(-128.0f, 127.0f)
	{
		next();
	}

	static Catch::Generators::GeneratorWrapper<Vector3> GetWrapper()
	{
		return Catch::Generators::GeneratorWrapper<Vector3>(
				std::unique_ptr<IGenerator<Vector3>>(new RandomVector3Generator()));
	}

	const Vector3& get() const override
	{
		return v;
	}

	bool next() override
	{
		v.x = dist(rng);
		v.y = dist(rng);
		v.z = dist(rng);
		return true;
	}
};

std::mt19937 RandomVector3Generator::rng;

TEST_CASE("Vector3 default constructor")
{
	Vector3 v;
	REQUIRE(v.x == 0.0f);
	REQUIRE(v.y == 0.0f);
	REQUIRE(v.z == 0.0f);
}

TEST_CASE("Vector3 single float constructor")
{
	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector3 v(i);
	REQUIRE(v.x == i);
	REQUIRE(v.y == i);
	REQUIRE(v.z == i);
}

TEST_CASE("Vector3 triple float constructor")
{
	auto s = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto t = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto r = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector3 v(s, t, r);
	REQUIRE(v.x == s);
	REQUIRE(v.y == t);
	REQUIRE(v.z == r);
}

TEST_CASE("Vector3 Vector2/depth constructor")
{
	auto s = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto t = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto r = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector2 v(s, t);

	Vector3 u(v, r);

	REQUIRE(u.x == s);
	REQUIRE(u.y == t);
	REQUIRE(u.z == r);
}

TEST_CASE("Vector3 copy constructor")
{
	auto s = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto t = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto r = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector3 v(s, t, r);
	Vector3 u(v);

	REQUIRE(u.x == s);
	REQUIRE(u.y == t);
	REQUIRE(u.z == r);
}

TEST_CASE("Vector3 move constructor")
{
	auto s = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto t = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto r = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector3 v(std::move(Vector3(s, t, r)));

	REQUIRE(v.x == s);
	REQUIRE(v.y == t);
	REQUIRE(v.z == r);
}

TEST_CASE("Vector3 copy assignment operator")
{
	auto s = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto t = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto r = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector3 v(s, t, r);
	Vector3 u = v;

	REQUIRE(u.x == s);
	REQUIRE(u.y == t);
	REQUIRE(u.z == r);
}

TEST_CASE("Vector3 move assignment operator")
{
	auto s = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto t = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto r = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector3 v = std::move(Vector3(s, t, r));

	REQUIRE(v.x == s);
	REQUIRE(v.y == t);
	REQUIRE(v.z == r);
}

TEST_CASE("Vector3 Vector2 cast operator")
{
	auto s = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto t = GENERATE(take(10, random(-128.0f, 127.0f)));
	auto r = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector3 v(s, t, r);
	Vector2 u(static_cast<Vector2>(v));

	REQUIRE(u.x == s);
	REQUIRE(u.y == t);
}

TEST_CASE("Vector3 negate operator")
{
	const Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));

	Vector3 u(-v);

	REQUIRE(-v.x == u.x);
	REQUIRE(-v.y == u.y);
	REQUIRE(-v.z == u.z);
}

TEST_CASE("Vector3 equality operator")
{
	const Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));

	INFO(u.x);
	INFO(u.y);
	INFO(u.z);

	REQUIRE(!(v == u));
	REQUIRE(!(u == v));
	REQUIRE(u == u);
	REQUIRE(v == v);
}
TEST_CASE("Vector3 inequality operator")
{
	const Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));

	REQUIRE(v != u);
	REQUIRE(u != v);
	REQUIRE(!(v != v));
	REQUIRE(!(u != u));
}

TEST_CASE("Vector3 addition operator")
{
	const Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));

	Vector3 w(v + u);

	REQUIRE(w.x == v.x + u.x);
	REQUIRE(w.y == v.y + u.y);
	REQUIRE(w.z == v.z + u.z);
}

TEST_CASE("Vector3 subtraction operator")
{
	const Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));

	Vector3 w(v - u);

	REQUIRE(w.x == v.x - u.x);
	REQUIRE(w.y == v.y - u.y);
	REQUIRE(w.z == v.z - u.z);
}

TEST_CASE("Vector3 scale up operator")
{
	const Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector3 w(v * i);

	REQUIRE(w.x == v.x * i);
	REQUIRE(w.y == v.y * i);
	REQUIRE(w.z == v.z * i);
}

TEST_CASE("Vector3 scale down operator")
{
	const Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));

	Vector3 w(v / i);

	REQUIRE(w.x == v.x / i);
	REQUIRE(w.y == v.y / i);
	REQUIRE(w.z == v.z / i);
}

TEST_CASE("Vector3 addition assignment operator")
{
	const Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 w(v);
	w += u;

	REQUIRE(w.x == v.x + u.x);
	REQUIRE(w.y == v.y + u.y);
	REQUIRE(w.z == v.z + u.z);
}

TEST_CASE("Vector3 subtraction assignment operator")
{
	const Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 w(v);
	w -= u;

	REQUIRE(w.x == v.x - u.x);
	REQUIRE(w.y == v.y - u.y);
	REQUIRE(w.z == v.z - u.z);
}

TEST_CASE("Vector3 scale up assignment operator")
{
	const Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 v(u);

	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));

	v *= i;

	REQUIRE(v.x == u.x * i);
	REQUIRE(v.y == u.y * i);
	REQUIRE(v.z == u.z * i);
}

TEST_CASE("Vector3 scale down assignment operator")
{
	const Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 v(u);

	auto i = GENERATE(take(10, random(-128.0f, 127.0f)));

	v /= i;

	REQUIRE(v.x == u.x / i);
	REQUIRE(v.y == u.y / i);
	REQUIRE(v.z == u.z / i);
}

TEST_CASE("Vector3 length")
{
	Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	REQUIRE(v.Length() == Approx(std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z))));
}

TEST_CASE("Vector3 square length")
{
	Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	REQUIRE(v.SquareLength() == Approx((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	REQUIRE(v.SquareLength() == Approx(v.Length() * v.Length()));
}

TEST_CASE("Vector3 normalize")
{
	Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	v.Normalize();

	REQUIRE(v.Length() == Approx(1.0f));
}

TEST_CASE("Vector3 distance to zero")
{
	Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));

	REQUIRE(Vector3::Distance(v, Vector3::Zero()) == Approx(v.Length()));
	REQUIRE(Vector3::Distance(Vector3::Zero(), v) == Approx(v.Length()));
}

TEST_CASE("Vector3 distance")
{
	Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));

	REQUIRE(Vector3::Distance(u, v) == Approx(Vector3::Distance(v, u)));

	float dx = v.x - u.x;
	float dy = v.y - u.y;
	float dz = v.z - u.z;

	REQUIRE(Vector3::Distance(v, u) == Approx(std::sqrt((dx * dx) + (dy * dy) + (dz * dz))));
}

TEST_CASE("Vector3 dot")
{
	Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));

	REQUIRE(Vector3::Dot(v, u) == Approx(Vector3::Dot(u, v)));
	REQUIRE(Vector3::Dot(v, u) == Approx((v.x * u.x) + (v.y * u.y) + (v.z * u.z)));
}

TEST_CASE("Vector3 normalized")
{
	Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 u(v);
	u.Normalize();

	REQUIRE(Vector3::Normalized(v).Length() == Approx(1.0f));
	REQUIRE(Vector3::Normalized(v).x == Approx(u.x));
	REQUIRE(Vector3::Normalized(v).y == Approx(u.y));
	REQUIRE(Vector3::Normalized(v).z == Approx(u.z));
}

TEST_CASE("Vector3 lerp")
{
	auto t = GENERATE(range(0.0f, 1.0f, 0.1f));

	Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 u = GENERATE(take(10, RandomVector3Generator::GetWrapper()));

	SECTION("Step lerp")
	{
		auto t = GENERATE(range(0.0f, 1.0f, 0.1f));
		Vector3 uv(Vector3::Lerp(u, v, t));
		Vector3 vu(Vector3::Lerp(v, u, 1.0f - t));

		//Need to be a bit more liberal here, so increase the margin of error.
		REQUIRE(uv.x == Approx(vu.x).margin(0.0001));
		REQUIRE(uv.y == Approx(vu.y).margin(0.0001));
		REQUIRE(uv.z == Approx(vu.z).margin(0.0001));
	}
}

TEST_CASE("Vector3 cross product")
{
	Vector3 v = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 w = GENERATE(take(10, RandomVector3Generator::GetWrapper()));
	Vector3 u(-v);

	//Cross product should be 0 when vectors are identical or opposite
	REQUIRE(Vector3::Cross(v, v).Length() == Approx(0.0f));
	REQUIRE(Vector3::Cross(v, u).Length() == Approx(0.0f));
	
	Float mags = v.Length() * w.Length();
	Float angle = std::acos(Vector3::Dot(v, w) / mags);
	
	REQUIRE(Vector3::Cross(v, w).Length() == Approx(mags * std::sin(angle)).margin(0.0001));

	// a*b  = |a||b|cos(t)
	//|axb| = |a||b|sin(t)
}
