#include<stdexcept>
#include <vector>

class DSU {
	int* _parent;
	int _size;
	int* _rank;
public:
	DSU(int size);
	void unite(int x1, int x2);
	int find(int x);
	int find_op(int x);
	~DSU();
};

DSU::DSU(int size):_size(size) {
	_parent = new int[_size];
	_rank = new int[_size];
	for (int i = 0;i < _size;i++) {
		_parent[i] = i;
		_rank[i] = 0;
	}
}

DSU::~DSU() {
	delete[]_parent;
	delete[]_rank;
}

int DSU::find(int x) {
	if (x < 0 || x >= _size) {
		throw std::out_of_range("Index out of bounds");
	}
	if (_parent[x] == x)
	{
		return x;
	}
	else {
		return find(_parent[x]);
	}
}

void DSU::unite(int x1, int x2) {
	if (x1 < 0 || x1 >= _size || x2 < 0 || x2 >= _size) {
		throw std::out_of_range("Index out of bounds");
	}
	int p1 = find(x1);
	int p2 = find(x2);

	if (p1 == p2) return;

	if (_rank[p1] < _rank[p2]) {
		_parent[p1] = p2;
	}
	else if (_rank[p1] > _rank[p2]) {
		_parent[p2] = p1;
	}
	else {
		_parent[p2] = p1;
		_rank[p1]++;
	}
}

//сжатие путей
int DSU::find_op(int x) {
	if (x < 0 || x >= _size) {
		throw std::out_of_range("Index out of bounds");
	}
	if (_parent[x] != x) {
		_parent[x] = find_op(_parent[x]);
	}
	return _parent[x];
}

class IslandCounter {
    const std::vector<std::vector<int>>& _grid;
    int _rows;
    int _cols;

public:
    bool isInBounds(int row, int col) const {
        return row >= 0 && row < _rows && col >= 0 && col < _cols;
    }

    int convertToFlatIndex(int row, int col) const {
        return row * _cols + col;
    }
    IslandCounter(const std::vector<std::vector<int>>& grid)
        : _grid(grid), _rows(grid.size())
    {
        if (grid.empty()) {
            _cols = 0;
        }
        else {
            _cols = grid[0].size();
        }
    }

    int calculateIslands() {
        if (_rows == 0 || _cols == 0) {
            return 0;
        }

        DSU disjointSet(_rows * _cols);

        // Проверяем только левого и верхнего соседа
        const int neighborOffsets[2][2] = { {1, 0}, {0, 1} };  

        // Фаза 1: Объединение компонент
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                if (_grid[i][j] == 1) {
                    int currentFlatIdx = convertToFlatIndex(i, j);

                    for (int k = 0; k < 2; ++k) {
                        int neighborRow = i + neighborOffsets[k][0];
                        int neighborCol = j + neighborOffsets[k][1];

                        // Проверяем нижнюю и правую границы
                        if (neighborRow < _rows && neighborCol < _cols &&
                            _grid[neighborRow][neighborCol] == 1) {
                            int neighborFlatIdx = convertToFlatIndex(neighborRow, neighborCol);
                            disjointSet.unite(currentFlatIdx, neighborFlatIdx);
                        }
                    }
                }
            }
        }

        // Фаза 2: Подсчет уникальных компонент
        int totalIslands = 0;
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                if (_grid[i][j] == 1) {
                    int cellIndex = convertToFlatIndex(i, j);
                    int rootRepresentative = disjointSet.find_op(cellIndex);

                    if (rootRepresentative == cellIndex)
                    {
                        totalIslands ++;
                    }
                }
            }
        }

        return totalIslands;
    }
};

