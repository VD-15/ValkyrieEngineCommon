#include "TestValues.hpp"
#include <initializer_list>

using namespace vlk;

std::initializer_list<float> testValues
{
	-1024.0f,
	-512.0f,
	-256.0f,
	-128.0f,
	-64.0f,
	-32.0f,
	-16.0f,
	-8.0f,
	-4.0f,
	-2.0f,
	-1.0f,
	-0.9f,
	-0.8f,
	-0.7f,
	-0.6f,
	-0.5f,
	-0.4f,
	-0.3f,
	-0.2f,
	-0.1f,
	0.0f,
	0.1f,
	0.2f,
	0.3f,
	0.4f,
	0.5f,
	0.6f,
	0.7f,
	0.8f,
	0.9f,
	1.0f,
	2.0f,
	4.0f,
	8.0f,
	16.0f,
	32.0f,
	64.0f,
	128.0f,
	256.0f,
	512.0f,
	1024.0f,
	std::numeric_limits<float>::lowest(),
	std::numeric_limits<float>::min(),
	std::numeric_limits<float>::max(),
	std::numeric_limits<float>::epsilon()
};

std::initializer_list<float> reducedValues
{
	-128.0f,
	-64.0f,
	-32.0f,
	-16.0f,
	-8.0f,
	-4.0f,
	-2.0f,
	-1.0f,
	1.0f,
	2.0f,
	4.0f,
	8.0f,
	16.0f,
	32.0f,
	64.0f,
	128.0f,
	std::numeric_limits<float>::lowest(),
	std::numeric_limits<float>::min(),
	std::numeric_limits<float>::max(),
	std::numeric_limits<float>::epsilon()
};


class Vector2Generator : public Catch::Generators::IGenerator<Vector2>
{
	Vector2 v;
	VectorBase<2, Size> index;
	public:

	Vector2Generator() = default;

	const Vector2& get() const override
	{
		return v;
	}

	bool next() override
	{
		index[0]++;
		if (index[0] > testValues.size())
		{
			index[0] = 0;
			index[1]++;

			if (index[1] > testValues.size())
			{
				return false;
			}
		}

		v[0] = *(testValues.begin() + index[0]);
		v[1] = *(testValues.begin() + index[1]);

		return true;
	}

	static Catch::Generators::GeneratorWrapper<Vector2> GetWrapper()
	{
		return Catch::Generators::GeneratorWrapper<Vector2>(
			std::unique_ptr<IGenerator<Vector2>>(new Vector2Generator()));
	}
};

TEST_CASE("Vector2 default constructor")
{
	Vector2 v;
	REQUIRE(v.X() == 0.0f);
	REQUIRE(v.Y() == 0.0f);
}

TEST_CASE("Vector2 dual float constructor")
{
	auto i = GENERATE(values(testValues));
	auto j = GENERATE(values(testValues));

	Vector2 v(i, j);
	REQUIRE(v.X() == i);
	REQUIRE(v.Y() == j);
}

TEST_CASE("Vector2 copy constructor")
{
	auto i = GENERATE(values(testValues));
	auto j = GENERATE(values(testValues));

	Vector2 v(i, j);
	Vector2 u(v);
	REQUIRE(u.X() == i);
	REQUIRE(u.Y() == j);
}

TEST_CASE("Vector2 move constructor")
{
	auto i = GENERATE(values(testValues));
	auto j = GENERATE(values(testValues));

	Vector2 tmp(i, j);
	Vector2 v(std::move(tmp));
	REQUIRE(v.X() == i);
	REQUIRE(v.Y() == j);
}

TEST_CASE("Vector2 copy assignment operator")
{
	auto i = GENERATE(values(testValues));
	auto j = GENERATE(values(testValues));

	Vector2 v(6.0f, -7.0f);
	Vector2 u(i, j);
	v = u;
	REQUIRE(v.X() == i);
	REQUIRE(u.X() == i);
	REQUIRE(v.Y() == j);
	REQUIRE(u.Y() == j);
}

TEST_CASE("Vector2 move assignment operator")
{
	auto i = GENERATE(values(testValues));
	auto j = GENERATE(values(testValues));

	Vector2 tmp(i, j);
	Vector2 v(std::move(tmp));
	v = Vector2(i, j);

	REQUIRE(v.X() == i);
	REQUIRE(v.Y() == j);
}

TEST_CASE("Vector2 negate operator")
{
	Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	Vector2 u(-v);

	REQUIRE(u.X() == -v.X());
	REQUIRE(u.Y() == -v.Y());
}

TEST_CASE("Vector2 equality operator")
{
	Vector2 v(-3123.5634f, -435.24);
	Vector2 u(2468.468f, -45657.4486f);

	REQUIRE(!(u == v));
	REQUIRE(!(v == u));
	REQUIRE(u == u);
	REQUIRE(v == v);
}

TEST_CASE("Vector2 inequality operator")
{
	Vector2 v(-3123.5634f, -435.24);
	Vector2 u(2468.468f, -45657.4486f);

	REQUIRE(v != u);
	REQUIRE(u != v);
	REQUIRE(!(v != v));
	REQUIRE(!(u != u));
}

TEST_CASE("Vector2 addition operator")
{	
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, Vector2Generator::GetWrapper()));
	Vector2 t(v + u);

	REQUIRE(t.X() == (v.X() + u.X()));
	REQUIRE(t.Y() == (v.Y() + u.Y()));
}

TEST_CASE("Vector2 subtraction operator")
{	
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, Vector2Generator::GetWrapper()));
	Vector2 t(v - u);

	REQUIRE(t.X() == (v.X() - u.X()));
	REQUIRE(t.Y() == (v.Y() - u.Y()));
}

TEST_CASE("Vector2 scale up operator")
{	
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	auto k = GENERATE(values(testValues));

	Vector2 t(v * k);

	REQUIRE(t.X() == (v.X() * k));
	REQUIRE(t.Y() == (v.Y() * k));
}

TEST_CASE("Vector2 scale down operator")
{	
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	auto k = GENERATE(values(testValues));

	if (k != 0.0f)
	{
		Vector2 t(v / k);

		REQUIRE(t.X() == (v.X() / k));
		REQUIRE(t.Y() == (v.Y() / k));
	}

}

TEST_CASE("Vector2 addition assignment operator")
{	
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, Vector2Generator::GetWrapper()));
	Vector2 w(v);
	w += u;

	REQUIRE(w.X() == (v.X() + u.X()));
	REQUIRE(w.Y() == (v.Y() + u.Y()));
}

TEST_CASE("Vector2 subtraction assignment operator")
{	
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, Vector2Generator::GetWrapper()));
	Vector2 w(v);
	w -= u;

	REQUIRE(w.X() == (v.X() - u.X()));
	REQUIRE(w.Y() == (v.Y() - u.Y()));
}

TEST_CASE("Vector2 scale up assignment operator")
{	
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	auto k = GENERATE(values(testValues));
	Vector2 u(v);

	u *= k;

	REQUIRE(u.X() == (v.X() * k));
	REQUIRE(u.Y() == (v.Y() * k));
}

TEST_CASE("Vector2 scale down assignment operator")
{	
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	auto k = GENERATE(values(testValues));
	Vector2 u(v);

	if (k != 0.0)
	{
		u /= k;

		REQUIRE(u.X() == (v.X() / k));
		REQUIRE(u.Y() == (v.Y() / k));
	}
}

TEST_CASE("Vector2 length")
{
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	REQUIRE(Vector2::Length(v) == Approx(std::sqrt((v.X() * v.X()) + (v.Y() * v.Y()))));
	REQUIRE(Vector2::Length(v) == Approx(Vector2::Length(ForceCXPR(v))));
}

TEST_CASE("Vector2 square length")
{
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	REQUIRE(Vector2::Length(v) == Approx(std::sqrt((v.X() * v.X()) + (v.Y() * v.Y()))));
	REQUIRE(Vector2::SquareLength(v) == Approx(Vector2::Length(v) * Vector2::Length(v)));
	REQUIRE(Vector2::SquareLength(v) == Approx(Vector2::SquareLength(ForceCXPR(v))));
}

TEST_CASE("Vector2 normalize")
{
	Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));

	if (Vector2::Length(v) != 0.0f)
	{
		v = Vector2::Normalized(v);
		REQUIRE(Vector2::Length(v) == Approx(1.0f));
		REQUIRE(Vector2::Length(ForceCXPR(v)) == Approx(1.0f));
	}
}

TEST_CASE("Vector2 distance to zero")
{	
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));

	REQUIRE(Vector2::Distance(v, Vector2::Zero()) == Approx(Vector2::Length(v)));
	REQUIRE(Vector2::Distance(Vector2::Zero(), v) == Approx(Vector2::Length(v)));

	REQUIRE((Float)Vector2::Distance(ForceCXPR(v), ForceCXPR(Vector2::Zero())) ==
		Approx(Vector2::Length(v)));
	REQUIRE(Vector2::Distance(ForceCXPR(Vector2::Zero()), ForceCXPR(v)) ==
		Approx(Vector2::Length(v)));
}

TEST_CASE("Vector2 distance")
{
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, Vector2Generator::GetWrapper()));

	REQUIRE(Vector2::Distance(v, u) == Approx(Vector2::Distance(u, v)));
	REQUIRE(Vector2::Distance(ForceCXPR(v), ForceCXPR(u)) == 
		Approx(Vector2::Distance(ForceCXPR(u), ForceCXPR(v))));

	float dx = v.X() - u.X();
	float dy = v.Y() - u.Y();

	REQUIRE(Vector2::Distance(v, u) == Approx(Sqrt((dx * dx) + (dy * dy))));
	REQUIRE(Vector2::Distance(ForceCXPR(v), ForceCXPR(u)) ==
		Approx(Sqrt((dx * dx) + (dy * dy))));
}

TEST_CASE("Vector2 dot")
{
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, Vector2Generator::GetWrapper()));

	REQUIRE(Vector2::Dot(v, u) == Approx(Vector2::Dot(u, v)));
	REQUIRE(Vector2::Dot(ForceCXPR(v), ForceCXPR(u)) ==
		Approx(Vector2::Dot(ForceCXPR(u), ForceCXPR(v))));
	REQUIRE(Vector2::Dot(v, u) == Approx((v.X() * u.X()) + (v.Y() * u.Y())));
	REQUIRE(Vector2::Dot(ForceCXPR(v), ForceCXPR(u)) ==
		Approx((v.X() * u.X()) + (v.Y() * u.Y())));
}

TEST_CASE("Vector2 lerp")
{
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));
	const Vector2 u = GENERATE(take(10, Vector2Generator::GetWrapper()));

	SECTION("Step lerp")
	{
		auto t = GENERATE(range(0.0f, 1.0f, 0.1f));
		Vector2 uv(Vector2::Lerp(u, v, t));
		Vector2 vu(Vector2::Lerp(v, u, 1.0f - t));

		//Need to be a bit more liberal here, so increase the margin of error.
		REQUIRE(uv.X() == Approx(vu.X()).margin(0.0001));
		REQUIRE(uv.Y() == Approx(vu.Y()).margin(0.0001));
	}
}

TEST_CASE("Vector2 perpendicular")
{
	const Vector2 v = GENERATE(take(10, Vector2Generator::GetWrapper()));

	INFO(v[0]);
	INFO(v[1]);

	const Vector2 u(Vector2::Perpendicular(v));

	//Can't divide by zero
	if (!(v[0] == 0.0f & v[1] == 0.0f))
	{
		//Angle between v and u should be ~pi/2
		REQUIRE(std::acos((Vector2::Dot(v, u)) / (Vector2::Length(u) * Vector2::Length(v))) ==
			Approx(1.5707963268));
	}
}
