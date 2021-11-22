#pragma once
#include <iostream>
#include <string>
#include <vector>

template<class T>
class Vector {
private:
	std::vector<T> data;
public:

	void Add(T value)
	{
		data.push_back(value);
	}

	void Change(size_t index, T value)
	{
		if ((index > data.size()) || (index <= 0)) throw ("Invalid index");
		data[index - 1] = value;
	}

	size_t Size() const
	{
		return data.size();
	}

	T operator[] (const size_t index) const
	{
		if ((index > Size()) || (index < 0)) throw ("Invalid index");
		return data[index];
	}

	Vector<T> operator+(const Vector<T>& v)
	{
		if (v.Size() != data.size()) throw "Vectors aren't equal\n";
		Vector<T> sum(v);
		for (int i = 0; i < Size(); i++)
			sum.data[i] += data[i];
		return sum;
	}

	Vector<T> operator-(const Vector<T>& v)
	{
		if (v.Size() != data.size()) throw "Vectors aren't equal\n";
		Vector<T> sub(*this);
		for (int i = 0; i < Size(); i++)
			sub.data[i] = data[i] - v.data[i];
		return sub;
	}

	T operator* (const Vector<T>& v)
	{
		if (v.Size() != data.size()) throw "Vectors aren't equal\n";
		Vector<T> mul(v);
		T result = 0;
		for (int i = 0; i < Size(); i++)
			result += mul.data[i] * data[i];
		return result;
	}

	Vector<T> operator*(const T a)
	{
		Vector<T> mul1(*this), mul2(*this);
		for (int i = 0; i < Size(); i++)
		{
			mul1.data[i] = a * mul1.data[i];
			mul2.data[i] *= a;
			if (mul1.data[i] != mul2.data[i]) throw "Not commutative\n";
		}
		return mul1;
	}

	Vector<T> operator/ (const T a)
	{
		if (a == T(0)) throw ("Divide to 0!");
		Vector<T> div(*this);
		for (int i = 0; i < Size(); i++)
			div.data[i] /= a;
		return div;
	}

	template<class T>
	friend std::istream& operator>> (std::istream& is, Vector<T>& v);

	friend std::ostream& operator<< (std::ostream& os, const Vector<T>& v)
	{
		os << "Size:" << v.Size() << std::endl;
		for (int i = 0; i < v.Size(); i++)
			os << i + 1 << ": " << v[i] << std::endl;
		return os;
	}

	std::complex<float> operator* (const Vector<std::complex<float>>& v) const
	{
		if (v.Size() != data.size()) throw "Vectors aren't equal\n";
		std::complex<float> result = 0;
		for (size_t i = 0; i < Size(); i++)
			result += std::complex<float>(data[i].real() * v.data[i].real(), (-1) * data[i].imag() * v.data[i].imag());
		return result;
	}

	std::complex<double> operator* (const Vector<std::complex<double>>& v) const
	{
		if (v.Size() != data.size()) throw "Vectors aren't equal\n";
		std::complex<double> result = 0;
		for (size_t i = 0; i < Size(); i++)
			result += std::complex<double>(data[i].real() * v.data[i].real(), (-1) * data[i].imag() * v.data[i].imag());
		return result;
	}

};

template<class T>
std::istream& operator>> (std::istream& is, Vector<T>& v)
{
	std::cout << "\nSize: ";
	size_t size = 0;
	is >> size;
	T value = 0;
	for (int i = 0; i < size; i++)
	{
		is >> value;
		v.Add(value);
	}
	return is;
}

template<>
std::istream& operator>> (std::istream& is, Vector<std::complex<double>>& v)
{
	std::cout << "\nSize: ";
	size_t size = 0;
	is >> size;
	for (int i = 0; i < size; i++)
	{
		double real = 0;
		double imag = 0;
		std::cout << "\nReal part: ";
		is >> real;
		std::cout << "\nImag part: ";
		is >> imag;
		std::complex<double> value(real, imag);
		v.Add(value);
	}
	return is;
}

template<>
std::istream& operator>> (std::istream& is, Vector<std::complex<float>>& v)
{
	std::cout << "\nSize: ";
	size_t size = 0;
	is >> size;
	for (int i = 0; i < size; i++)
	{
		float real = 0;
		float imag = 0;
		std::cout << "\nReal part: ";
		is >> real;
		std::cout << "\nImag part: ";
		is >> imag;
		std::complex<float> value(real, imag);
		v.Add(value);
	}
	return is;
}