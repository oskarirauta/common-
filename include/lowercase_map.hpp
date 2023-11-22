#pragma once

#include <utility>
#include <string>
#include <map>

#include "common.hpp"

namespace common {

template <class T>
class lowercase_map {
	private:
		std::map<std::string, T> _m;

	public:
		typedef std::map<std::string, T>::size_type size_type;

		class iterator {
			friend class lowercase_map;
			private:
				std::map<std::string, T>::iterator _it;
				iterator(const std::map<std::string, T>::iterator &it) {
					_it = it;
				}

			public:
				iterator& operator++() { ++_it; return *this; }
				iterator operator++(int) { iterator tmp(*this); operator++(); return tmp; }
				bool operator==(const iterator& rhs) { return _it == rhs._it; }
				bool operator!=(const iterator& rhs) { return _it != rhs._it; }
				std::pair<const std::string, T>& operator*() { return *_it; }
				std::pair<const std::string, T>* operator->() { return _it.operator->(); }
		};

	iterator begin();
	iterator end();
	iterator find(const std::string& key);

	T& operator [](const std::string& key);
	bool operator ==(const lowercase_map<T>& other);
	bool operator !=(const lowercase_map<T>& other);
	bool operator <(const lowercase_map<T>&other);
	bool operator <=(const lowercase_map<T>&other);
	bool operator >(const lowercase_map<T>&other);
	bool operator >=(const lowercase_map<T>&other);
	bool operator <=>(const lowercase_map<T>&other);

	lowercase_map() {}
	lowercase_map(const std::initializer_list<std::pair<std::string, T>>& l);
	lowercase_map(const lowercase_map<T>& other);
	lowercase_map(const std::map<std::string, T>& map);
	lowercase_map(const std::pair<std::string, T>& pair);

	T& at(const std::string& key);
	bool contains(const std::string& key) const;

	bool empty() const;
	lowercase_map<T>::size_type size() const;
	lowercase_map<T>::size_type max_size() const;

	void insert(const std::initializer_list<std::pair<std::string, T>>& l);
	void insert(const lowercase_map<T>& other);
	void insert(const std::pair<std::string, T>& pair);

	void append(const std::initializer_list<std::pair<std::string, T>>& l);
	void append(const lowercase_map<T>& other);
	void append(const std::pair<std::string, T>& pair);

	lowercase_map<T>::size_type erase(const std::string& key);
};

template <class T>
lowercase_map<T>::iterator lowercase_map<T>::begin() {
	return this -> _m.begin();
}

template <class T>
lowercase_map<T>::iterator lowercase_map<T>::end() {
	return this -> _m.end();
}

template <class T>
lowercase_map<T>::iterator lowercase_map<T>::find(const std::string& key) {
	auto it = this -> _m.find(key);
	return iterator(it);
}

template <class T>
T& lowercase_map<T>::operator [](const std::string& key) {
	return this -> _m[common::to_lower(std::as_const(key))];
}

template <class T>
bool lowercase_map<T>::operator ==(const lowercase_map<T>& other) {
	return this -> _m == other._m;
}

template <class T>
bool lowercase_map<T>::operator !=(const lowercase_map<T>& other) {
	return this -> _m != other._m;
}

template <class T>
bool lowercase_map<T>::operator <(const lowercase_map<T>&other) {
	return this -> _m < other._m;
}

template <class T>
bool lowercase_map<T>::operator <=(const lowercase_map<T>&other) {
	return this -> _m <= other._m;
}

template <class T>
bool lowercase_map<T>::operator >(const lowercase_map<T>&other) {
	return this -> _m > other._m;
}

template <class T>
bool lowercase_map<T>::operator >=(const lowercase_map<T>&other) {
	return this -> _m >= other._m;
}

template <class T>
bool lowercase_map<T>::operator <=>(const lowercase_map<T>&other) {
	return this -> _m <=> other._m;
}

template <class T>
lowercase_map<T>::lowercase_map(const std::initializer_list<std::pair<std::string, T>>& l) {

	for ( auto& [key, value] : l )
		this -> _m[common::to_lower(std::as_const(key))] = value;
}

template <class T>
lowercase_map<T>::lowercase_map(const lowercase_map<T>& other) {

	for ( auto& [key, value] : other )
		this -> _m[common::to_lower(std::as_const(key))] = value;
}

template <class T>
lowercase_map<T>::lowercase_map(const std::map<std::string, T>& map) {

	for ( auto& [key, value] : map )
		this -> _m[common::to_lower(std::as_const(key))] = value;
}

template <class T>
lowercase_map<T>::lowercase_map(const std::pair<std::string, T>& pair) {

	this -> _m[common::to_lower(std::as_const(pair.first))] = pair.second;
}

template <class T>
T& lowercase_map<T>::at(const std::string& key) {

	return this -> _m[common::to_lower(std::as_const(key))];
}

template <class T>
bool lowercase_map<T>::contains(const std::string& key) const {

	return this -> _m.contains(common::to_lower(std::as_const(key)));
}

template <class T>
bool lowercase_map<T>::empty() const {

	return this -> _m.empty();
}

template <class T>
lowercase_map<T>::size_type lowercase_map<T>::size() const {

	return this -> _m.size();
}

template <class T>
lowercase_map<T>::size_type lowercase_map<T>::max_size() const {

	return this -> _m.max_size();
}

template <class T>
void lowercase_map<T>::insert(const std::initializer_list<std::pair<std::string, T>>& l) {

	for ( auto& [key, value] : l )
		this -> _m[common::to_lower(std::as_const(key))] = value;
}

template <class T>
void lowercase_map<T>::insert(const lowercase_map<T>& other) {

	for ( auto& [key, value] : other )
		this -> _m[common::to_lower(std::as_const(key))] = value;
}

template <class T>
void lowercase_map<T>::insert(const std::pair<std::string, T>& pair) {

	this -> _m[common::to_lower(std::as_const(pair.first))] = pair.second;
}

template <class T>
void lowercase_map<T>::append(const std::initializer_list<std::pair<std::string, T>>& l) {

	this -> insert(l);
}

template <class T>
void lowercase_map<T>::append(const lowercase_map<T>& other) {

	this -> insert(other);
}

template <class T>
void lowercase_map<T>::append(const std::pair<std::string, T>& pair) {

	this -> insert(pair);
}

template <class T>
lowercase_map<T>::size_type lowercase_map<T>::erase(const std::string& key) {

	this -> _m.erase(common::to_lower(std::as_const(key)));
}

} // end of namespace
