#include <algorithm>
#include <iterator>

#include "conway.h"

namespace conway {
	template<size_t dim>
	void Conway<dim>::Next() {
		UpdateToAdd();
		UpdateToRemove();
		UpdateCells();

		std::set<Cell*> temp;
		std::set_difference(alive_.begin(), alive_.end(), to_remove_.begin(), to_remove_.end(), std::inserter(temp, temp.begin()));
		temp.insert(to_add_.begin(), to_add_.end());
		alive_.swap(temp);

		to_add_.clear();
		to_remove_.clear();
	}

	template<size_t dim>
	vector<Cell*> Conway<dim>::GetAlive() {
		return vector<Cell*>(alive_.begin(), alive_.end());
	}

	template<size_t dim>
	Cell* Conway<dim>::Get(const vector<size_t>& coords) {
		return grid_.Get(coords);
	}

	template<size_t dim>
	void Conway<dim>::Set(const vector<size_t>& coords, bool alive) {
		grid_.Set(coords, alive);

		if (alive) {
			alive_.insert(grid_.Get(coords));
		} else {
			alive_.erase(grid_.Get(coords));
		}
	}

	template<size_t dim>
	void Conway<dim>::UpdateToAdd() {
		for (Cell* c : alive_) {
			for (Cell* n : grid_.Neighbors(*c)) {
				if (alive_.find(n) == alive_.end()) {
					if (grid_.AliveNeighbors(*n) >= threshold_spawn_lower && grid_.AliveNeighbors(*n) <= threshold_spawn_upper) {
						to_add_.insert(n);
					}
				}
			}
		}
	}

	template<size_t dim>
	void Conway<dim>::UpdateToRemove() {
		for (Cell* c : alive_) {
			if (grid_.AliveNeighbors(*c) < threshold_survive_lower || grid_.AliveNeighbors(*c) > threshold_survive_upper) {
				to_remove_.insert(c);
			}
		}
	}

	template<size_t dim>
	void Conway<dim>::UpdateCells() {
		for (Cell* c : to_add_) {
			c->alive = true;
		}

		for (Cell* c : to_remove_) {
			c->alive = false;
		}
	}

	// template class fix
	template class Conway<2>;
	template class Conway<3>;
	template class Conway<4>;
}