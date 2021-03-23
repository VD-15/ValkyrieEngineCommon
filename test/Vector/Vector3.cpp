#include "TestValues.hpp"

using namespace vlk;

class Vector3Generator : public Catch::Generators::IGenerator<Vector3>
{
	Vector3 v;
	VectorBase<3, Int> index;
	public:
	Vector3Generator()
	{ }

	static Catch::Generators::GeneratorWrapper<Vector3> GetWrapper()
	{
		return Catch::Generators::GeneratorWrapper<Vector3>(
				std::unique_ptr<IGenerator<Vector3>>(new Vector3Generator()));
	}

	const Vector3& get() const override
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
				index[1] = 0;
				index[2]++;

				if (index[2] > testValues.size())
				{
					return false;
				}
			}
		}

		v[0] = *(testValues.begin() + index[0]);
		v[1] = *(testValues.begin() + index[1]);
		v[2] = *(testValues.begin() + index[2]);

		return true;
	}
};

TEST_CASE("Vector3 default constructor")
{
	Vector3 v;
	REQUIRE(v.X() == 0.0f);
	REQUIRE(v.Y() == 0.0f);
	REQUIRE(v.Z() == 0.0f);
}

TEST_CASE("Vector3 triple float constructor")
{
	auto s = GENERATE(values(testValues));
	auto t = GENERATE(values(testValues));
	auto r = GENERATE(values(testValues));

	Vector3 v(s, t, r);
	REQUIRE(v.X() == s);
	REQUIRE(v.Y() == t);
	REQUIRE(v.Z() == r);
}

TEST_CASE("Vector3 Vector2/depth constructor")
{
	auto s = GENERATE(values(testValues));
	auto t = GENERATE(values(testValues));
	auto r = GENERATE(values(testValues));

	Vector2 v(s, t);

	Vector3 u(v, r);

	REQUIRE(u.X() == s);
	REQUIRE(u.Y() == t);
	REQUIRE(u.Z() == r);
}

TEST_CASE("Vector3 copy constructor")
{
	auto s = GENERATE(values(testValues));
	auto t = GENERATE(values(testValues));
	auto r = GENERATE(values(testValues));

	Vector3 v(s, t, r);
	Vector3 u(v);

	REQUIRE(u.X() == s);
	REQUIRE(u.Y() == t);
	REQUIRE(u.Z() == r);
}

TEST_CASE("Vector3 move constructor")
{
	auto s = GENERATE(values(testValues));
	auto t = GENERATE(values(testValues));
	auto r = GENERATE(values(testValues));

	Vector3 v(std::move(Vector3(s, t, r)));

	REQUIRE(v.X() == s);
	REQUIRE(v.Y() == t);
	REQUIRE(v.Z() == r);
}

TEST_CASE("Vector3 copy assignment operator")
{
	auto s = GENERATE(values(testValues));
	auto t = GENERATE(values(testValues));
	auto r = GENERATE(values(testValues));

	Vector3 v(s, t, r);
	Vector3 u = v;

	REQUIRE(u.X() == s);
	REQUIRE(u.Y() == t);
	REQUIRE(u.Z() == r);
}

TEST_CASE("Vector3 move assignment operator")
{
	auto s = GENERATE(values(testValues));
	auto t = GENERATE(values(testValues));
	auto r = GENERATE(values(testValues));

	Vector3 v = std::move(Vector3(s, t, r));

	REQUIRE(v.X() == s);
	REQUIRE(v.Y() == t);
	REQUIRE(v.Z() == r);
}

TEST_CASE("Vector3 Vector2 cast operator")
{
	auto s = GENERATE(values(testValues));
	auto t = GENERATE(values(testValues));
	auto r = GENERATE(values(testValues));

	Vector3 v(s, t, r);
	Vector2 u(static_cast<Vector2>(v));

	REQUIRE(u.X() == s);
	REQUIRE(u.Y() == t);
}

TEST_CASE("Vector3 negate operator")
{
	const Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));

	Vector3 u(-v);

	REQUIRE(-v.X() == u.X());
	REQUIRE(-v.Y() == u.Y());
	REQUIRE(-v.Z() == u.Z());
}

TEST_CASE("Vector3 equality operator")
{
	const Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));

	REQUIRE(u == u);
}
TEST_CASE("Vector3 inequality operator")
{
	const Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));

	REQUIRE(!(u != u));
}

TEST_CASE("Vector3 addition operator")
{
	const Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));

	Vector3 w(v + u);

	REQUIRE(w.X() == v.X() + u.X());
	REQUIRE(w.Y() == v.Y() + u.Y());
	REQUIRE(w.Z() == v.Z() + u.Z());
}

TEST_CASE("Vector3 subtraction operator")
{
	const Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));

	Vector3 w(v - u);

	REQUIRE(w.X() == v.X() - u.X());
	REQUIRE(w.Y() == v.Y() - u.Y());
	REQUIRE(w.Z() == v.Z() - u.Z());
}

TEST_CASE("Vector3 scale up operator")
{
	const Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	auto i = GENERATE(values(testValues));

	Vector3 w(v * i);

	REQUIRE(w.X() == v.X() * i);
	REQUIRE(w.Y() == v.Y() * i);
	REQUIRE(w.Z() == v.Z() * i);
}

TEST_CASE("Vector3 scale down operator")
{
	const Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	auto i = GENERATE(values(testValues));

	//Can't divide by zero
	if (i != 0.0f)
	{
		Vector3 w(v / i);

		REQUIRE(w.X() == v.X() / i);
		REQUIRE(w.Y() == v.Y() / i);
		REQUIRE(w.Z() == v.Z() / i);
	}
}

TEST_CASE("Vector3 addition assignment operator")
{
	const Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));
	Vector3 w(v);
	w += u;

	REQUIRE(w.X() == v.X() + u.X());
	REQUIRE(w.Y() == v.Y() + u.Y());
	REQUIRE(w.Z() == v.Z() + u.Z());
}

TEST_CASE("Vector3 subtraction assignment operator")
{
	const Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	const Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));
	Vector3 w(v);
	w -= u;

	REQUIRE(w.X() == v.X() - u.X());
	REQUIRE(w.Y() == v.Y() - u.Y());
	REQUIRE(w.Z() == v.Z() - u.Z());
}

TEST_CASE("Vector3 scale up assignment operator")
{
	const Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));
	Vector3 v(u);

	auto i = GENERATE(values(testValues));

	v *= i;

	REQUIRE(v.X() == u.X() * i);
	REQUIRE(v.Y() == u.Y() * i);
	REQUIRE(v.Z() == u.Z() * i);
}

TEST_CASE("Vector3 scale down assignment operator")
{
	const Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));
	Vector3 v(u);

	auto i = GENERATE(values(testValues));

	//Can't divide by zero
	if (i != 0.0f)
	{
		v /= i;

		REQUIRE(v.X() == u.X() / i);
		REQUIRE(v.Y() == u.Y() / i);
		REQUIRE(v.Z() == u.Z() / i);
	}
}

TEST_CASE("Vector3 length")
{
	Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	REQUIRE(Vector3::Length(v) == Approx(std::sqrt((v.X() * v.X()) + (v.Y() * v.Y()) + (v.Z() * v.Z()))));
	REQUIRE(Vector3::Length(v) == Approx(Vector3::Length(ForceCXPR(v))));
}

TEST_CASE("Vector3 square length")
{
	Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	REQUIRE(Vector3::SquareLength(v) == Approx((v.X() * v.X()) + (v.Y() * v.Y()) + (v.Z() * v.Z())));
	REQUIRE(Vector3::SquareLength(v) == Approx(Vector3::Length(v) * Vector3::Length(v)));
	REQUIRE(Vector3::SquareLength(v) == Approx(Vector3::SquareLength(ForceCXPR(v))));
}

TEST_CASE("Vector3 normalize")
{
	Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));

	if (Vector3::Length(v) != 0.0f)
	{
		v = Vector3::Normalized(v);

		REQUIRE(Vector3::Length(v) == Approx(1.0f));
		REQUIRE(Vector3::SquareLength(v) == Approx(1.0f));
	}
}

TEST_CASE("Vector3 distance to zero")
{
	Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));

	REQUIRE(Vector3::Distance(v, Vector3::Zero()) == Approx(Vector3::Length(v)));
	REQUIRE(Vector3::Distance(Vector3::Zero(), v) == Approx(Vector3::Length(v)));
	REQUIRE(Vector3::Distance(ForceCXPR(v), ForceCXPR(Vector3::Zero())) ==
		Approx(Vector3::Length(v)));
	REQUIRE(Vector3::Distance(ForceCXPR(Vector3::Zero()), ForceCXPR(v)) ==
		Approx(Vector3::Length(v)));
}

TEST_CASE("Vector3 distance")
{
	Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));

	REQUIRE(Vector3::Distance(u, v) == Approx(Vector3::Distance(v, u)));
	REQUIRE(Vector3::Distance(ForceCXPR(v), ForceCXPR(u)) == 
		Approx(Vector3::Distance(ForceCXPR(u), ForceCXPR(v))));

	float dx = v.X() - u.X();
	float dy = v.Y() - u.Y();
	float dz = v.Z() - u.Z();

	REQUIRE(Vector3::Distance(v, u) == Approx(std::sqrt((dx * dx) + (dy * dy) + (dz * dz))));
	REQUIRE(Vector3::Distance(ForceCXPR(v), ForceCXPR(u)) ==
		Approx(Sqrt((dx * dx) + (dy * dy) + (dz * dz))));
}

TEST_CASE("Vector3 dot")
{
	Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));

	REQUIRE(Vector3::Dot(v, u) == Approx(Vector3::Dot(u, v)));
	REQUIRE(Vector3::Dot(ForceCXPR(v), ForceCXPR(u)) ==
		Approx(Vector3::Dot(ForceCXPR(u), ForceCXPR(v))));
	REQUIRE(Vector3::Dot(v, u) == Approx((v.X() * u.X()) + (v.Y() * u.Y()) + (v.Z() * u.Z())));
	REQUIRE(Vector3::Dot(ForceCXPR(v), ForceCXPR(u)) == Approx(Vector3::Dot(v, u)));
}

TEST_CASE("Vector3 lerp")
{
	auto t = GENERATE(range(0.0f, 1.0f, 0.1f));

	Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	Vector3 u = GENERATE(take(10, Vector3Generator::GetWrapper()));

	SECTION("Step lerp")
	{
		auto t = GENERATE(range(0.0f, 1.0f, 0.1f));
		Vector3 uv(Vector3::Lerp(u, v, t));
		Vector3 vu(Vector3::Lerp(v, u, 1.0f - t));

		//Need to be a bit more liberal here, so increase the margin of error.
		REQUIRE(uv.X() == Approx(vu.X()).margin(0.0001));
		REQUIRE(uv.Y() == Approx(vu.Y()).margin(0.0001));
		REQUIRE(uv.Z() == Approx(vu.Z()).margin(0.0001));
	}
}

TEST_CASE("Vector3 cross product")
{
	Vector3 v = GENERATE(take(10, Vector3Generator::GetWrapper()));
	Vector3 w = GENERATE(take(10, Vector3Generator::GetWrapper()));
	Vector3 u(-v);

	//Cross product should be 0 when vectors are identical or opposite
	REQUIRE(Vector3::Length(Vector3::Cross(v, v)) == Approx(0.0f));
	REQUIRE(Vector3::Length(Vector3::Cross(v, u)) == Approx(0.0f));
	
	Float mags = Vector3::Length(v) * Vector3::Length(w);

	if (mags != 0.0f)
	{
		Float cosA = Vector3::Dot(v, w) / mags;

		//Precision error makes |cosA| > 1.0 sometimes
		if (cosA == Approx(1.0f).epsilon(std::numeric_limits<float>::epsilon())) cosA = 1.0f;
		else if (cosA == Approx(-1.0f).epsilon(std::numeric_limits<float>::epsilon())) cosA = -1.0f;

		Float angle = std::acos(cosA);

		REQUIRE(Vector3::Length(Vector3::Cross(v, w)) == Approx(mags * std::sin(angle)).epsilon(0.01));
	}

	// a*b  = |a||b|cos(t)
	//|axb| = |a||b|sin(t)
}
