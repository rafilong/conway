#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../conway/conway.h"

using namespace conway;

TEST_CASE("Default constructor") {
	Conway<2> conway;
	REQUIRE(conway.GetAlive().size() == 0);
}

TEST_CASE("Set") {
	Conway<2> conway;
	conway.Set({ 0, 0 }, true);
	REQUIRE(conway.GetAlive().size() == 1);
}

TEST_CASE("Get") {
	Conway<2> conway;
	REQUIRE(!conway.Get({ 0, 0 })->alive);
}

TEST_CASE("Next") {
	Conway<2> conway;
	conway.Set({ 0, 0 }, true);
	conway.Next();
	REQUIRE(conway.GetAlive().size() == 0);
}
