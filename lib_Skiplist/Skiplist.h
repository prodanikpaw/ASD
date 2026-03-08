#include <iostream>
#include "List"

template<typename TKey, typename TValue>
struct Node {
	std::pair<TKey, TValue>;
	Node** next;
};


template<typename TKey, typename TValue>
class SkipList {

private:
	List <Node*> heads;
	size_t lvl;
	size_t max_lvl;
	size_t generate_level() {
		while (rand() % 100 < 50) {
			lvl++;
		}
	}
public:
	SkipList() {};

	TValue find(const TKey& key) const override;
	void insert(const TKey& key, const TValue& val) override;
	bool is_empty() const noexcept override;
	int size() const noexcept;

};

template<typename TKey, typename TValue>
SkipList<TKey, TValue> ::SkipList() :heads(nullptr), lvl(0), max_lvl(0) {}

template<typename TKey, typename TValue>
inline TValue SkipList<TKey, TValue>::find(const TKey& key) const
{
	Node* current = new Node;
	
	return TValue();
}

template<typename TKey, typename TValue>
inline void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& val)
{
	Node* new_node = new Node;
	if (is_empty()) {
		for (int i = 0;i < new_node;i++) {
			heads.push_front(new_node);
		}
	}
	else {

	}

}

template<typename TKey, typename TValue>
inline bool SkipList<TKey, TValue>::is_empty() const noexcept
{
	return false;
}

template<typename TKey, typename TValue>
inline int SkipList<TKey, TValue>::size() const noexcept
{
	return 0;
}
