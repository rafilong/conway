#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/conway/conway.h"

using namespace conway;

TEST_CASE("Default constructor (1d)") {
	Grid<1> grid(10);
	REQUIRE(!grid.Get({ 0 })->alive);
}

TEST_CASE("Default constructor (2d)") {
	Grid<2> grid(10);
	REQUIRE(!grid.Get({ 0, 0 })->alive);
}

TEST_CASE("Setter (1d)") {
	Grid<1> grid(10);
	grid.Set({ 0 }, true);
	REQUIRE(grid.Get({ 0 })->alive);
}

TEST_CASE("Get neighbors (2d)") {
	Grid<2> grid(10);
	REQUIRE(grid.Neighbors(Cell({ 0, 0 })).size() == 4);
	REQUIRE(grid.Neighbors(Cell({ 1, 1 })).size() == 9);
}

TEST_CASE("Get neighbors (4d)") {
	Grid<4> grid(10);
	REQUIRE(grid.Neighbors(Cell({ 1, 1 })).size() == 80);
}

TEST_CASE("Get alive neighbors (2d)") {
	Grid<2> grid(10);
	grid.Set({ 0, 1 }, true);
	REQUIRE(grid.AliveNeighbors(Cell({ 0, 0 })) == 1);
}
