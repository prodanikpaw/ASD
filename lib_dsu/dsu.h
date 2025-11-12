#include<stdexcept>

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

int DSU::find_op(int x) {
	if (x < 0 || x >= _size) {
		throw std::out_of_range("Index out of bounds");
	}
	if (_parent[x] != x) {
		_parent[x] = find_op(_parent[x]);
	}
	return _parent[x];
}

