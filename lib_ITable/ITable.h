/*#include<iostream>
template<typename TKey, typename TValue>
class ITable {
	~ITable() {};
public:
	virtual void insert(const TKey& key, const TValue& val) = 0;
	virtual void erase(const TKey& key) = 0;
	virtual void find(const TKey& key) = 0;
	virtual std::ostream& print(std::ostream& out)  const noexcept = 0;
	virtual bool is_empty()const noexcept = 0;
	virtual bool consist(const TKey&key)const noexcept = 0;

};
*/
template<typename TKey, typename TValue>
class ITable {
public:
    virtual ~ITable() {}

    virtual void insert(const TKey& key, const TValue& val) = 0;
    virtual void erase(const TKey& key) = 0;
    virtual TValue find(const TKey& key) const = 0;
    virtual std::ostream& print(std::ostream& out) const noexcept = 0;
    virtual bool is_empty() const noexcept = 0;
    virtual bool consist(const TKey& key) const noexcept = 0;
    virtual void replace(const TKey& key, const TValue& val) = 0;
};