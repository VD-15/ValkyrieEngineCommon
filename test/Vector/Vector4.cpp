
#include "TestValues.hpp"

using namespace vlk;


class Vector4Generator : public Catch::Generators::IGenerator<Vector4>
{
	Vector4 v;
	VectorBase<4, Int> index;
	public:
	Vector4Generator()
	{ }

	static Catch::Generators::GeneratorWrapper<Vector4> GetWrapper()
	{
		return Catch::Generators::GeneratorWrapper<Vector4>(
				std::unique_ptr<IGenerator<Vector4>>(new Vector4Generator()));
	}

	const Vector4& get() const override
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
					index[2] = 0;
					index[3]++;

					if (index[3] > testValues.size())
					{
						return false;
					}
				}
			}
		}

		v[0] = *(testValues.begin() + index[0]);
		v[1] = *(testValues.begin() + index[1]);
		v[2] = *(testValues.begin() + index[2]);
		v[3] = *(testValues.begin() + index[3]);

		return true;
	}
};

TEST_CASE("Vector4 default constructor")
{
	Vector4 v;
	REQUIRE(v.X() == 0.0f);
	REQUIRE(v.Y() == 0.0f);
	REQUIRE(v.Z() == 0.0f);
	REQUIRE(v.W() == 0.0f);
}

TEST_CASE("Vector4 four float constructor")
{
	auto s = GENERATE(values(reducedValues));
	auto t = GENERATE(values(reducedValues));
	auto r = GENERATE(values(reducedValues));
	auto q = GENERATE(values(reducedValues));

	Vector4 v(s, t, r, q);
	REQUIRE(v.X() == s);
	REQUIRE(v.Y() == t);
	REQUIRE(v.Z() == r);
	REQUIRE(v.W() == q);
}

TEST_CASE("Vector4 Vector2/depth constructor")
{
	auto s = GENERATE(values(reducedValues));
	auto t = GENERATE(values(reducedValues));
	auto r = GENERATE(values(reducedValues));
	auto q = GENERATE(values(reducedValues));

	Vector3 v(s, t, r);

	Vector4 u(v, q);

	REQUIRE(u.X() == s);
	REQUIRE(u.Y() == t);
	REQUIRE(u.Z() == r);
	REQUIRE(u.W() == q);
}

TEST_CASE("Vector4 copy constructor")
{
	auto s = GENERATE(values(reducedValues));
	auto t = GENERATE(values(reducedValues));
	auto r = GENERATE(values(reducedValues));
	auto q = GENERATE(values(reducedValues));

	Vector4 v(s, t, r, q);
	Vector4 u(v);

	REQUIRE(u.X() == s);
	REQUIRE(u.Y() == t);
	REQUIRE(u.Z() == r);
	REQUIRE(u.W() == q);
}

TEST_CASE("Vector4 move constructor")
{
	auto s = GENERATE(values(reducedValues));
	auto t = GENERATE(values(reducedValues));
	auto r = GENERATE(values(reducedValues));
	auto q = GENERATE(values(reducedValues));

	Vector4 v(std::move(Vector4(s, t, r, q)));

	REQUIRE(v.X() == s);
	REQUIRE(v.Y() == t);
	REQUIRE(v.Z() == r);
	REQUIRE(v.W() == q);
}

TEST_CASE("Vector4 copy assignment operator")
{
	auto s = GENERATE(values(reducedValues));
	auto t = GENERATE(values(reducedValues));
	auto r = GENERATE(values(reducedValues));
	auto q = GENERATE(values(reducedValues));

	Vector4 v(s, t, r, q);
	Vector4 u = v;

	REQUIRE(u.X() == s);
	REQUIRE(u.Y() == t);
	REQUIRE(u.Z() == r);
	REQUIRE(u.W() == q);
}

TEST_CASE("Vector4 move assignment operator")
{
	auto s = GENERATE(values(reducedValues));
	auto t = GENERATE(values(reducedValues));
	auto r = GENERATE(values(reducedValues));
	auto q = GENERATE(values(reducedValues));

	Vector4 v = std::move(Vector4(s, t, r, q));

	REQUIRE(v.X() == s);
	REQUIRE(v.Y() == t);
	REQUIRE(v.Z() == r);
	REQUIRE(v.W() == q);
}

TEST_CASE("Vector4 Vector3 cast operator")
{
	auto s = GENERATE(values(reducedValues));
	auto t = GENERATE(values(reducedValues));
	auto r = GENERATE(values(reducedValues));
	auto q = GENERATE(values(reducedValues));

	Vector4 v(s, t, r, q);
	Vector3 u(static_cast<Vector3>(v));

	REQUIRE(u.X() == s);
	REQUIRE(u.Y() == t);
	REQUIRE(u.Z() == r);
}

TEST_CASE("Vector4 negate operator")
{
	const Vector4 v = GENERATE(take(10, Vector4Generator::GetWrapper()));

	Vector4 u(-v);

	REQUIRE(-v.X() == u.X());
	REQUIRE(-v.Y() == u.Y());
	REQUIRE(-v.Z() == u.Z());
	REQUIRE(-v.W() == u.W());
}

TEST_CASE("Vector4 equality operator")
{
	const Vector4 u = GENERATE(take(10, Vector4Generator::GetWrapper()));

	REQUIRE(u == u);
}
TEST_CASE("Vector4 inequality operator")
{
	const Vector4 u = GENERATE(take(10, Vector4Generator::GetWrapper()));

	REQUIRE(!(u != u));
}

TEST_CASE("Vector4 addition operator")
{
	const Vector4 v = GENERATE(take(10, Vector4Generator::GetWrapper()));
	const Vector4 u = GENERATE(take(10, Vector4Generator::GetWrapper()));

	Vector4 w(v + u);

	REQUIRE(w.X() == v.X() + u.X());
	REQUIRE(w.Y() == v.Y() + u.Y());
	REQUIRE(w.Z() == v.Z() + u.Z());
	REQUIRE(w.W() == v.W() + u.W());
}

TEST_CASE("Vector4 subtraction operator")
{
	const Vector4 v = GENERATE(take(10, Vector4Generator::GetWrapper()));
	const Vector4 u = GENERATE(take(10, Vector4Generator::GetWrapper()));

	Vector4 w(v - u);

	REQUIRE(w.X() == v.X() - u.X());
	REQUIRE(w.Y() == v.Y() - u.Y());
	REQUIRE(w.Z() == v.Z() - u.Z());
	REQUIRE(w.W() == v.W() - u.W());
}

TEST_CASE("Vector4 scale up operator")
{
	const Vector4 v = GENERATE(take(10, Vector4Generator::GetWrapper()));
	auto i = GENERATE(values(testValues));

	Vector4 w(v * i);

	REQUIRE(w.X() == v.X() * i);
	REQUIRE(w.Y() == v.Y() * i);
	REQUIRE(w.Z() == v.Z() * i);
	REQUIRE(w.W() == v.W() * i);
}

TEST_CASE("Vector4 scale down operator")
{
	const Vector4 v = GENERATE(take(10, Vector4Generator::GetWrapper()));
	auto i = GENERATE(values(testValues));

	//Can't divide by zero
	if (i != 0.0f)
	{
		Vector4 w(v / i);

		REQUIRE(w.X() == v.X() / i);
		REQUIRE(w.Y() == v.Y() / i);
		REQUIRE(w.Z() == v.Z() / i);
		REQUIRE(w.W() == v.W() / i);
	}
}

TEST_CASE("Vector4 addition assignment operator")
{
	const Vector4 v = GENERATE(take(10, Vector4Generator::GetWrapper()));
	const Vector4 u = GENERATE(take(10, Vector4Generator::GetWrapper()));
	Vector4 w(v);
	w += u;

	REQUIRE(w.X() == v.X() + u.X());
	REQUIRE(w.Y() == v.Y() + u.Y());
	REQUIRE(w.Z() == v.Z() + u.Z());
	REQUIRE(w.W() == v.W() + u.W());
}

TEST_CASE("Vector4 subtraction assignment operator")
{
	const Vector4 v = GENERATE(take(10, Vector4Generator::GetWrapper()));
	const Vector4 u = GENERATE(take(10, Vector4Generator::GetWrapper()));
	Vector4 w(v);
	w -= u;

	REQUIRE(w.X() == v.X() - u.X());
	REQUIRE(w.Y() == v.Y() - u.Y());
	REQUIRE(w.Z() == v.Z() - u.Z());
	REQUIRE(w.W() == v.W() - u.W());
}

TEST_CASE("Vector4 scale up assignment operator")
{
	const Vector4 u = GENERATE(take(10, Vector4Generator::GetWrapper()));
	Vector4 v(u);

	auto i = GENERATE(values(testValues));

	v *= i;

	REQUIRE(v.X() == u.X() * i);
	REQUIRE(v.Y() == u.Y() * i);
	REQUIRE(v.Z() == u.Z() * i);
	REQUIRE(v.W() == u.W() * i);
}

TEST_CASE("Vector4 scale down assignment operator")
{
	const Vector4 u = GENERATE(take(10, Vector4Generator::GetWrapper()));
	Vector4 v(u);

	auto i = GENERATE(values(testValues));

	//Can't divide by zero
	if (i != 0.0f)
	{
		v /= i;

		REQUIRE(v.X() == u.X() / i);
		REQUIRE(v.Y() == u.Y() / i);
		REQUIRE(v.Z() == u.Z() / i);
		REQUIRE(v.W() == u.W() / i);
	}
}

