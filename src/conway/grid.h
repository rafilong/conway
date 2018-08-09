#pragma once

#include <vector>

namespace conway {
	using std::vector;

	/**
	 * Cell to be stored in grid.
	 * May add additional functionality later (age, etc).
	 */
	struct Cell {
		Cell(const vector<size_t>& coords) : alive(false), coords(coords) { }

		vector<size_t> coords;
		bool alive;
	};

	/**
	 * Class for n-dimension grid.
	 */
	template<size_t dim>
	class Grid {
	private:
		/**
		 * Vector of input size of sub-grids.
		 */
		vector<Grid<dim - 1>*> data_;
	public:
		Grid(const size_t size);
		Grid(const vector<size_t>& coords, const size_t size);
		~Grid();

		Cell* Get(const vector<size_t>& coords);
		void Set(const vector<size_t>& coords, bool alive);

		/**
		 * Returns the neighbors of given cell in the sub-grid.
		 */
		vector<Cell*> Neighbors(const Cell& cell);

		/**
		 * Returns the number of alive neighbors of given cell in the sub-grid.
		 */
		size_t AliveNeighbors(const Cell& cell);
	};

	/**
	 * Base case for n-dimension grid.
	 */
	template <>
	class Grid<0> {
	private:
		Cell* data_;
	public:
		Grid(const vector<size_t>& coords, const size_t size);
		~Grid();

		Cell* Get(const vector<size_t>& coords);
		void Set(const vector<size_t>& coords, bool alive);

		/**
		 * Returns the neighbors of given cell in the sub-grid.
		 */
		vector<Cell*> Neighbors(const Cell& cell);

		/**
		 * Returns the number of alive neighbors of given cell in the sub-grid.
		 */
		size_t AliveNeighbors(const Cell& cell);
	};
}
