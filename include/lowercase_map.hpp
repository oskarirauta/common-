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

		class const_iterator {
		friend class lowercase_map;
		protected:
			std::map<std::string, T>::const_iterator c_it;
			const_iterator(const std::map<std::string, T>::const_iterator &it) {
				this -> c_it = it;
			}

		public:
			const_iterator() = default;
			const_iterator& operator++() { ++this -> c_it; return *this; }
			const_iterator operator++(int) const { auto tmp = *this; ++(*this); return tmp; }
			bool operator==(const const_iterator& rhs) const { return this -> c_it == rhs.c_it; }
			bool operator!=(const const_iterator& rhs) const { return this -> c_it != rhs.c_it; }
			const std::pair<const std::string, T>& operator*() const { return *(this -> c_it); }
			const std::pair<const std::string, T>* operator->() const { return this -> c_it.operator -> (); }
		}; // end of class common::lowercase_map<T>::const_iterator

		class iterator : public const_iterator {
		friend class lowercase_map;
		private:
			std::map<std::string, T>::iterator _it;
			iterator(const std::map<std::string, T>::iterator &it) {
				this -> _it = it;
			}

		public:
			iterator() = default;
			iterator& operator++() { ++this -> _it; return *this; }
			iterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }
			bool operator==(const iterator& rhs) { return this -> _it == rhs._it; }
			bool operator!=(const iterator& rhs) { return this -> _it != rhs._it; }
			const std::pair<const std::string, T>& operator*() { return *(this -> _it); }
			const std::pair<const std::string, T>* operator->() { return this -> _it.operator -> (); }
		}; // end of class common::lowercase_map<T>::iterator

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
		iterator find(const std::string& key);
		const_iterator find(const std::string& key) const;

		T& operator [](const std::string& key);
		T& operator [](std::string& key);
		bool operator ==(const lowercase_map<T>& other);
		bool operator !=(const lowercase_map<T>& other);
		bool operator <(const lowercase_map<T>&other);
		bool operator <=(const lowercase_map<T>&other);
		bool operator >(const lowercase_map<T>&other);
		bool operator >=(const lowercase_map<T>&other);
		bool operator <=>(const lowercase_map<T>&other);

		lowercase_map<T>& operator =(const std::initializer_list<std::pair<std::string, T>>& l);
		lowercase_map<T>& operator =(const lowercase_map<T>& other);
		lowercase_map<T>& operator =(const std::map<std::string, T>& map);
		lowercase_map<T>& operator =(const std::pair<std::string, T>& pair);

		lowercase_map<T>& operator *();
		const lowercase_map<T>& operator*() const;
		lowercase_map<T>* operator ->();
		const lowercase_map<T>* operator ->() const;

		lowercase_map() {}
		lowercase_map(const std::initializer_list<std::pair<std::string, T>>& l);
		lowercase_map(const lowercase_map<T>& other);
		lowercase_map(const std::map<std::string, T>& map);
		lowercase_map(const std::pair<std::string, T>& pair);

		T& at(const std::string& key);
		const T& at(const std::string& key) const;

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
		void clear();

	}; // end of class common::lowercase_map<T> introduction

	template <class T>
	lowercase_map<T>::iterator lowercase_map<T>::begin() {
		return lowercase_map<T>::iterator(this -> _m.begin());
	}

	template <class T>
	lowercase_map<T>::iterator lowercase_map<T>::end() {
		return lowercase_map<T>::iterator(this -> _m.end());
	}

	template <class T>
	lowercase_map<T>::const_iterator lowercase_map<T>::cbegin() const {
		return lowercase_map<T>::const_iterator(this -> _m.cbegin());
	}

	template <class T>
	lowercase_map<T>::const_iterator lowercase_map<T>::cend() const {
		return lowercase_map<T>::const_iterator(this -> _m.cend());
	}

	template <class T>
	lowercase_map<T>::const_iterator lowercase_map<T>::begin() const {
		return lowercase_map<T>::const_iterator(this -> _m.cbegin());
	}

	template <class T>
	lowercase_map<T>::const_iterator lowercase_map<T>::end() const {
		return lowercase_map<T>::const_iterator(this -> _m.cend());
	}

	template <class T>
	lowercase_map<T>::iterator lowercase_map<T>::find(const std::string& key) {
		auto it = this -> _m.find(key);
		return lowercase_map<T>::iterator(it);
	}

	template <class T>
	lowercase_map<T>::const_iterator lowercase_map<T>::find(const std::string& key) const {
		auto it = this -> _m.find(key);
		return lowercase_map<T>::const_iterator(it);
	}

	template <class T>
	T& lowercase_map<T>::operator [](const std::string& key) {
		return this -> _m[common::to_lower(std::as_const(key))];
	}

	template <class T>
	T& lowercase_map<T>::operator [](std::string& key) {
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
	lowercase_map<T>& lowercase_map<T>::operator =(const std::initializer_list<std::pair<std::string, T>>& l) {

		this -> _m.clear();
		for ( auto& [key, value] : l )
			this -> _m[common::to_lower(std::as_const(key))] = value;
	}

	template <class T>
	lowercase_map<T>& lowercase_map<T>::operator =(const lowercase_map<T>& other) {

		this -> _m.clear();
		for ( auto& [key, value] : other )
			this -> _m[common::to_lower(std::as_const(key))] = value;
	}

	template <class T>
	lowercase_map<T>& lowercase_map<T>::operator =(const std::map<std::string, T>& map) {

		this -> _m.clear();
		for ( auto& [key, value] : map )
			this -> _m[common::to_lower(std::as_const(key))] = value;
	}

	template <class T>
	lowercase_map<T>& lowercase_map<T>::operator =(const std::pair<std::string, T>& pair) {

		this -> _m.clear();
		this -> _m[common::to_lower(std::as_const(pair.first))] = pair.second;
	}

	template <class T>
	lowercase_map<T>& lowercase_map<T>::operator *() {
		return this;
	}

	template <class T>
	const lowercase_map<T>& lowercase_map<T>::operator*() const {
		return this;
	}

	template <class T>
	lowercase_map<T>* lowercase_map<T>::operator ->() {
		return *this;
	}

	template <class T>
	const lowercase_map<T>* lowercase_map<T>::operator ->() const {
		return *this;
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
	const T& lowercase_map<T>::at(const std::string& key) const {
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
		return this -> _m.erase(common::to_lower(std::as_const(key)));
	}

	template <class T>
	void lowercase_map<T>::clear() {
		this -> _m.clear();
	}

} // end of namespace
