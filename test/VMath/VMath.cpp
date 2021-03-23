#include "ValkyrieEngineCommon/VMath.hpp"
#include "catch2/catch.hpp"
#include <initializer_list>
#include <limits>
#include <iostream>

using namespace vlk;

std::initializer_list<Float> edgeFloatValues = 
{
	std::numeric_limits<Float>::min(),
	std::numeric_limits<Float>::lowest(),
	std::numeric_limits<Float>::max(),
	std::numeric_limits<Float>::epsilon(),
};

TEST_CASE("Sign")
{
	REQUIRE(Sign(1.0) == 1.0);
	REQUIRE(Sign(0.0) == 0.0);
	REQUIRE(Sign(-1.0) == -1.0);
	REQUIRE(Sign(-2.0) == -1.0);
	REQUIRE(Sign(2.0) == 1.0);
}

TEST_CASE("Sin")
{
	auto f = GENERATE(range(-vlk::TwoPi, vlk::TwoPi, 0.001f));
	REQUIRE(vlk::Sin((Float)f) == Approx(vlk::Sin(ForceCXPR<Float>(f))).margin(0.0001f));
}

TEST_CASE("Cos")
{
	auto f = GENERATE(range(-vlk::TwoPi, vlk::TwoPi, 0.001f));
	REQUIRE(vlk::Cos((Float)f) == Approx(vlk::Cos(ForceCXPR<Float>(f))).margin(0.0001f));
}

//TODO: this is inaccurate with larger values
TEST_CASE("Tan")
{
	auto f = GENERATE(range(-vlk::TwoPi, vlk::TwoPi, 0.001f));
	INFO(f);
	Float t = vlk::Tan((Float)f);

	if (std::abs(t) <= 10.0)
	{
		//Use margin for small values because epsilon doesn't work near zero
		REQUIRE(vlk::Tan((Float)f) == Approx(vlk::Tan(ForceCXPR<Float>(f))).margin(0.0001f));
	}
	else
	{
		//allow relative 2% value deviation for larger values
		REQUIRE(vlk::Tan((Float)f) == Approx(vlk::Tan(ForceCXPR<Float>(f))).epsilon(0.02));
	}
}

TEST_CASE("ASin")
{
	auto f = GENERATE(range(-1.0f, 1.0f, 0.001f));
	REQUIRE(vlk::ASin((Float)f) == Approx(vlk::ASin(ForceCXPR<Float>(f))).margin(0.0001f));
}

TEST_CASE("ACos")
{
	auto f = GENERATE(range(-1.0f, 1.0f, 0.001f));
	REQUIRE(vlk::ACos((Float)f) == Approx(vlk::ACos(ForceCXPR<Float>(f))).margin(0.0001f));
}

TEST_CASE("ATan")
{
	auto f = GENERATE(range(-1.0f, 1.0f, 0.001f));
	REQUIRE(vlk::ATan((Float)f) == Approx(vlk::ATan(ForceCXPR<Float>(f))).margin(0.0001f));
}

TEST_CASE("ATan2")
{
	auto x = GENERATE(range(-10.0f, 10.0f, 0.1f));
	auto y = GENERATE(range(-10.0f, 10.0f, 0.1f));
	REQUIRE(vlk::ATan2((Float)x, (Float)y) ==
		Approx(vlk::ATan2(ForceCXPR<Float>(x), ForceCXPR<Float>(y))).margin(0.0001f));
}

TEST_CASE("Sqrt")
{
	auto f = GENERATE(range(0.0f, 10.0f, 0.01f));
	REQUIRE(vlk::Sqrt((Float)f) == Approx(vlk::Sqrt(ForceCXPR<Float>(f))).margin(0.0001f));
}

//TODO: This doesn't work peoperly with negative values
TEST_CASE("Pow")
{
	auto b = GENERATE(range(1.0f, 10.0f, 0.1f));
	auto e = GENERATE(range(1.0f, 10.0f, 0.1f));
	REQUIRE(vlk::Pow((Float)b, (Float)e) ==
		Approx(vlk::Pow(ForceCXPR<Float>(b), ForceCXPR<Float>(e))).margin(0.0001f));
}

//TODO: This gets inaccurate with small values of e
TEST_CASE("FMod")
{
	auto b = GENERATE(range(-10.0f, 10.0f, 0.1f));
	auto e = GENERATE(range(-10.0f, 10.0f, 0.1f));
	INFO(b);
	INFO(e);
	REQUIRE(vlk::FMod((Float)b, (Float)e) ==
		Approx(vlk::FMod(ForceCXPR<Float>(b), ForceCXPR<Float>(e))).margin(0.001f));
}

TEST_CASE("Ceil")
{
	auto f = GENERATE(range(-10.0f, 10.0f, 0.01f));
	REQUIRE(vlk::Ceil((Float)f) == vlk::Ceil(ForceCXPR<Float>(f)));
}

TEST_CASE("Floor")
{
	auto f = GENERATE(range(-10.0f, 10.0f, 0.01f));
	REQUIRE(vlk::Floor((Float)f) == vlk::Floor(ForceCXPR<Float>(f)));
}

TEST_CASE("Trunc")
{
	auto f = GENERATE(range(-10.0f, 10.0f, 0.01f));
	REQUIRE(vlk::Trunc((Float)f) == vlk::Trunc(ForceCXPR<Float>(f)));
}

TEST_CASE("Round")
{
	auto f = GENERATE(range(-10.0f, 10.0f, 0.01f));
	REQUIRE(vlk::Round((Float)f) == vlk::Round(ForceCXPR<Float>(f)));
}

TEST_CASE("Abs")
{
	auto f = GENERATE(range(-10.0f, 10.0f, 0.01f));
	REQUIRE(vlk::Abs((Float)f) == vlk::Abs(ForceCXPR<Float>(f)));
}
