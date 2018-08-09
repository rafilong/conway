#include "grid.h"

#include <cmath>

namespace conway {
	template<size_t dim>
	Grid<dim>::Grid(const size_t size) : Grid(vector<size_t>(), size) { }

	template<size_t dim>
	Grid<dim>::Grid(const vector<size_t>& coords, const size_t size) : data_(size) {
		for (size_t i = 0; i < size; i++) {
			vector<size_t> temp = coords;
			temp.push_back(i);
			data_[i] = new Grid<dim - 1>(temp, size);
		}
	}

	Grid<0>::Grid(const vector<size_t>& coords, const size_t size) {
		data_ = new Cell(coords);
	}

	template<size_t dim>
	Grid<dim>::~Grid() {
		for (Grid<dim - 1>* grid : data_) {
			delete grid;
		}
	}

	Grid<0>::~Grid() {
		delete data_;
	}

	template<size_t dim>
	Cell* Grid<dim>::Get(const vector<size_t>& coords) {
		return data_[coords[0]]->Get(vector<size_t>(coords.begin() + 1, coords.end()));
	}

	Cell* Grid<0>::Get(const vector<size_t>& coords) {
		return data_;
	}

	template<size_t dim>
	void Grid<dim>::Set(const vector<size_t>& coords, bool alive) {
		Get(coords)->alive = alive;
	}

	void Grid<0>::Set(const vector<size_t>& coords, bool alive) {
		data_->alive = alive;
	}

	template<size_t dim>
	vector<Cell*> Grid<dim>::Neighbors(const Cell& cell) {
		vector<Cell*> output;
		size_t coord = cell.coords[cell.coords.size() - dim];

		vector<Cell*> temp = data_[coord]->Neighbors(cell);
		output.insert(output.begin(), temp.begin(), temp.end());
		if (coord > 0) {
			temp = data_[coord - 1]->Neighbors(cell);
			output.insert(output.begin(), temp.begin(), temp.end());
		}
		if (coord < data_.size() - 1) {
			temp = data_[coord + 1]->Neighbors(cell);
			output.insert(output.begin(), temp.begin(), temp.end());
		}

		return output;
	}

	vector<Cell*> Grid<0>::Neighbors(const Cell& cell) {
		vector<Cell*> output;
		if (data_->coords == cell.coords) {
			return output;
		}

		for (size_t i = 0; i < cell.coords.size(); i++) {
			if (std::abs((long)(data_->coords[i] - cell.coords[i])) > 1) {
				return output;
			}
		}

		output.push_back(data_);
		return output;
	}

	template<size_t dim>
	size_t Grid<dim>::AliveNeighbors(const Cell& cell) {
		size_t count = 0;
		for (const Cell* c : Neighbors(cell)) {
			if (c->alive) {
				count++;
			}
		}
		return count;
	}

	// template class fix
	template class Grid<0>;
	template class Grid<1>;
	template class Grid<2>;
	template class Grid<3>;
	template class Grid<4>;
}