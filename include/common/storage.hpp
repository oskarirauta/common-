#pragma once

#include <ostream>
#include <istream>
#include <type_traits>

namespace common {

template<typename T>
class Storage {

	static_assert(std::is_arithmetic<T>::value, "Not an arithmetic type, Storage type must be numeric");

	private:

		T value;

		static T size_division(T v);

	public:

		Storage() {}
		Storage(T v) : value(v) {}

		operator T&() { return this -> value; }
		operator T() const { return this -> value; }

		Storage& operator =(const T& v) { this -> value = v; return *this; }

		Storage operator +(const T& v) { return Storage(this -> value + v); }
		Storage operator -(const T& v) { return Storage(this -> value - v); }
		Storage operator *(const T& v) { return Storage(this -> value * v); }
		Storage operator /(const T& v) { return Storage(this -> value / v); }
		Storage operator %(const T& v) { return Storage(this -> value % v); }

		Storage operator +(const Storage<T>& o) { return Storage(this -> value + o.value); }
		Storage operator -(const Storage<T>& o) { return Storage(this -> value - o.value); }
		Storage operator *(const Storage<T>& o) { return Storage(this -> value * o.value); }
		Storage operator /(const Storage<T>& o) { return Storage(this -> value / o.value); }
		Storage operator %(const Storage<T>& o) { return Storage(this -> value % o.value); }

		Storage& operator +=(const T& v) { this -> value += v; return *this; }
		Storage& operator -=(const T& v) { this -> value -= v; return *this; }
		Storage& operator *=(const T& v) { this -> value *= v; return *this; }
		Storage& operator /=(const T& v) { this -> value /= v; return *this; }
		Storage& operator %=(const T& v) { this -> value %= v; return *this; }

		Storage& operator +=(const Storage<T>& o) { this -> value += o.value; return *this; }
		Storage& operator -=(const Storage<T>& o) { this -> value -= o.value; return *this; }
		Storage& operator *=(const Storage<T>& o) { this -> value *= o.value; return *this; }
		Storage& operator /=(const Storage<T>& o) { this -> value /= o.value; return *this; }
		Storage& operator %=(const Storage<T>& o) { this -> value %= o.value; return *this; }


		T& operator ++() { return ++this -> value; }
		T& operator --() { return --this -> value; }
		T& operator ++(int v) { return this -> value++; }
		T& operator --(int v) { return this -> value--; }

		bool operator ==(const T& v) const { return this -> value == v; }
		bool operator !=(const T& v) const { return this -> value != v; }
		bool operator <(const T& v) const { return this -> value < v; }
		bool operator >(const T& v) const { return this -> value > v; }
		bool operator <=(const T& v) const { return this -> value <= v; }
		bool operator >=(const T& v) const { return this -> value >= v; }

		bool operator ==(const Storage<T>& o) const { return this -> value == o.value; }
		bool operator !=(const Storage<T>& o) const { return this -> value != o.value; }
		bool operator <(const Storage<T>& o) const { return this -> value < o.value; }
		bool operator >(const Storage<T>& o) const { return this -> value > o.value; }
		bool operator <=(const Storage<T>& o) const { return this -> value <= o.value; }
		bool operator >=(const Storage<T>& o) const { return this -> value >= o.value; }

		T& raw() { return this -> value; }
		T raw() const { return this -> value; }

		T kb() const { return this -> value; }
		T mb() const;
		T gb() const;

};

} // end of namespace

template<typename T>
T common::Storage<T>::size_division(T v) {

	if ((unsigned long long)v < 103 )
		return 0;

	v = v / 1024;
	unsigned long long _v = (unsigned long long)((v * 10) + 0.5);
	return _v * 0.1;
}

template<typename T>
T common::Storage<T>::mb() const {

	if ( this -> value == 0 )
		return 0;
	else return common::Storage<T>::size_division(this -> value);
}

template<typename T>
T common::Storage<T>::gb() const {

	T _mb = this -> mb();
	if ( _mb == 0 )
		return 0;
	else return common::Storage<T>::size_division(_mb);
}

template<typename T>
std::ostream& operator <<(std::ostream& os, const common::Storage<T>& s) {

	os << s.raw();
	return os;
}

template<typename T>
std::istream& operator >>(std::istream& is, common::Storage<T>& s) {

	is >> s.raw();
	return is;
}
