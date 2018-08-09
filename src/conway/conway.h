#pragma once

#include <set>

#include "grid.h"

namespace conway {
	using std::set;

	template <size_t dim>
	class Conway {
	private:
		Grid<dim> grid_;
		size_t size_;

		/* The threshold below which cells die. */
		size_t threshold_survive_lower = 2;
		/* The threshold above which cells die. */
		size_t threshold_survive_upper = 3;
		/* The threshold above which cells spawn. */
		size_t threshold_spawn_lower = 3;
		/* The threshold below which cells spawn. */
		size_t threshold_spawn_upper = 3;

		/* Cells that are currently alive. */
		set<Cell*> alive_;
		/* Cells to be added on completion of cycle (TODO: try to make local variable) */
		set<Cell*> to_add_;
		/* Cells to be removed on completion of cycle (TODO: try to make local variable) */
		set<Cell*> to_remove_;

		/* Updates to_add_ variable (TODO: add return, remove side effects) */
		void UpdateToAdd();
		/* Updates to_remove_ variable (TODO: add return, remove side effects) */
		void UpdateToRemove();
		/* Updates cells in to_add_ and to_remove_ (TODO: add return, remove side effects) */
		void UpdateCells();
	public:
		Conway() : Conway(100) { }
		Conway(size_t size) : grid_(vector<size_t>(), size), size_(size) { }

		/**
		 * Moves the simulation forward one generation.
		 */
		void Next();

		/**
		 * Returns a vector of living cells.
		 */
		vector<Cell*> GetAlive();

		/**
		 * Returns a pointer to the cell at that coordinate.
		 */
		Cell* Get(const vector<size_t>& coords);

		/**
		 * Sets the status of the cell at that coordinate.
		 */
		void Set(const vector<size_t>& coords, bool alive);
	};
}