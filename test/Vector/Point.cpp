#include "ValkyrieEngineCommon/Vector.hpp"
#include "catch2/catch.hpp"

using namespace vlk;

TEST_CASE("Default constructor")
{
	Point<Int> p;
	REQUIRE(p.X() == 0);
	REQUIRE(p.Y() == 0);
}

TEST_CASE("Value constructor")
{
	Point<Int> p(5, -17);
	REQUIRE(p.X() == 5);
	REQUIRE(p.Y() == -17);
}

TEST_CASE("VectorBase<2, Val> constructor")
{
	VectorBase<2, Int> data({-4, 33});
	Point<Int> p(data);
	REQUIRE(p.X() == -4);
	REQUIRE(p.Y() == 33);
}

TEST_CASE("Copy constructor")
{
	Point<Int> q(66, -3);
	Point<Int> p(q);
	REQUIRE(p.X() == 66);
	REQUIRE(p.Y() == -3);
}

TEST_CASE("Copy operator")
{
	Point<Int> q(54637, 542689);
	Point<Int> p = q;
	REQUIRE(p.X() == 54637);
	REQUIRE(p.Y() == 542689);
}

TEST_CASE("Move constructor")
{
	Point<Int> p(std::move(Point<Int>(213890, -13284)));
	REQUIRE(p.X() == 213890);
	REQUIRE(p.Y() == -13284);
}

TEST_CASE("Move operator")
{
	Point<Int> p = std::move(Point<Int>(72354, -457890));
	REQUIRE(p.X() == 72354);
	REQUIRE(p.Y() == -457890);
}

TEST_CASE("Index operator")
{
	Point<Int> p(-456784, -9063456);
	REQUIRE(p.X() == p[0]);
	REQUIRE(p.Y() == p[1]);
}

TEST_CASE("Const index operator")
{
	const Point<Int> p(-3657, 689423456);
	REQUIRE(p.X() == p[0]);
	REQUIRE(p.Y() == p[1]);
}

TEST_CASE("Get data")
{
	Point<Int> p(46857, -5645489);
	REQUIRE(p.Data()[0] == 46857);
	REQUIRE(p.Data()[1] == -5645489);
}

TEST_CASE("Const get data")
{
	const Point<Int> p(46857, -5645489);
	REQUIRE(p.Data()[0] == 46857);
	REQUIRE(p.Data()[1] == -5645489);
}

TEST_CASE("Negate operator")
{
	Point<Int> p(-888, -334);
	Point<Int> q(-p);
	REQUIRE(p[0] == -(q[0]));
	REQUIRE(p[1] == -(q[1]));
}

TEST_CASE("Equality operator")
{
	Point<Int> p(-64, -64);
	Point<Int> q(-64, -64);
	REQUIRE(p == q);
}

TEST_CASE("Inequality operator")
{
	Point<Int> p(-63, -64);
	Point<Int> q(66, 54);
	REQUIRE(p != q);
}

TEST_CASE("Addition operator")
{
	Point<Int> p(Point<Int>(-3, 6) + Point<Int>(3, -6));
	REQUIRE(p[0] == 0);
	REQUIRE(p[1] == 0);
}

TEST_CASE("Addition increment operator")
{
	Point<Int> p(-4, 3);
	p += Point<Int>(4, -3);
	REQUIRE(p[0] == 0);
	REQUIRE(p[1] == 0);
}

TEST_CASE("Subtraction operator")
{
	Point<Int> p(Point<Int>(-3, 6) - Point<Int>(-3, 6));
	REQUIRE(p[0] == 0);
	REQUIRE(p[1] == 0);
}

TEST_CASE("Subtraction increment operator")
{
	Point<Int> p(-4, 3);
	p -= Point<Int>(-4, 3);
	REQUIRE(p[0] == 0);
	REQUIRE(p[1] == 0);
}

TEST_CASE("Scalar multiplication operator")
{
	Point<Int> q(6, 3);
	Point<Int> p(q * 2);
	REQUIRE(p[0] == 12);
	REQUIRE(p[1] == 6);
}

TEST_CASE("Scalar multiplication increment operator")
{
	Point<Int> p(6, 3);
	p *= 2;
	REQUIRE(p[0] == 12);
	REQUIRE(p[1] == 6);
}

TEST_CASE("Scalar division operator")
{
	Point<Int> q(6, 3);
	Point<Int> p(q / 3);
	REQUIRE(p[0] == 2);
	REQUIRE(p[1] == 1);
}


TEST_CASE("Scalar division increment operator")
{
	Point<Int> p(6, 3);
	p /= 3;
	REQUIRE(p[0] == 2);
	REQUIRE(p[1] == 1);
}
