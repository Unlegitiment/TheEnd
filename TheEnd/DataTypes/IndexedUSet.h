#pragma once
#include <unordered_set>
#include <vector>
#include "../SHVNative/types.h"
template<typename __Key, typename __Hash> class IndexedUSet {
private:
	std::unordered_set<__Key, __Hash> m_Set;
	std::vector<__Key> m_Vector = std::vector<__Key>(m_Set.begin(), m_Set.end()); // bro display the type information you right bastard.s

public:
	typedef __Key KeyType;
	typedef __Hash HashType;
	__Key& operator[](int index);
	void Add(__Key data);
	void Remove(__Key data);
	std::vector<__Key>& GetVector() {
		return this->m_Vector;
	}
	std::unordered_set<__Key, __Hash>& GetSet() {
		return this->m_Set;
	}
};

template<typename __Key, typename __Hash>
inline __Key& IndexedUSet<__Key, __Hash>::operator[](int index) {
	return this->GetVector()[index];
}

template<typename __Key, typename __Hash>
inline void IndexedUSet<__Key, __Hash>::Add(__Key data) {
	this->m_Set.insert(data);
	this->m_Vector.push_back(data);
}

template<typename __Key, typename __Hash>
inline void IndexedUSet<__Key, __Hash>::Remove(__Key data) {
	this->m_Set.erase(data);
	auto it = std::find(this->m_Vector.begin(), this->m_Vector.end(), data);
	if (it != this->m_Vector.end()) {
		this->m_Vector.erase(it);
	} else {
		scriptLogI("Couldn't find it in m_Vector.");
	}
}
