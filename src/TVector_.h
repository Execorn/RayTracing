#pragma once

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

// ----------------------------------------------------------------

template <size_t dimension, typename Type>
class Vector_ {

private:
	Type data_[dimension];

public:
	Vector_() {
		for (size_t idx = 0; idx < dimension; ++idx) this->data_[idx] = Type();
	}

	Type& operator[] (const size_t idx) {
		assert(idx < dimension);
		return this->data_[idx];
	}

	const Type& operator[] (const size_t idx) const {
		assert(idx < dimension);
		return this->data_[idx];
	}
};

// ----------------------------------------------------------------

typedef Vector_<2, float> Vector2f_;
typedef Vector_<2, int>   Vector2i_;
typedef Vector_<3, float> Vector3f_;

typedef Vector_<3, int  > Vector3i_;
typedef Vector_<4, float> Vector4f_;

// ----------------------------------------------------------------
//TODO: remove the same code in operator[] implementations if possible
template <typename Type>
class Vector_<2, Type> {

public:
	Vector_():
		x_(Type()), y_(Type()) {}
	Vector_(Type x, Type y):
		x_(x), y_(y) {}

	template <class U>
	Vector_<2, Type> (const Vector_<2, U> &v);

	const Type& operator[] (const size_t idx) const {
		assert(idx < 2);
		return idx <= 0 ? this->x_ : this->y_;
	}
	Type& operator[] (const size_t idx) {
		assert(idx < 2);
		return idx <= 0 ? this->x_ : this->y_;
	}

	Type x_, y_;
};

// ----------------------------------------------------------------

template <typename Type>
class Vector_<3, Type> {

public:
	Vector_():
		x_(Type()), y_(Type()), z_(Type()) {}
	Vector_(Type x, Type y, Type z):
		x_(x), y_(y), z_(z) {}

	const Type& operator[] (const size_t idx) const {
		assert(idx < 3);
		if (idx <= 0) return this->x_;
		return idx == 1 ? this->y_ : this->z_;
	}

	Type& operator[] (const size_t idx) {
		assert(idx < 3);
		if (idx <= 0) return this->x_;
		return idx == 1 ? this->y_ : this->z_;
	}

	Vector_<3, Type> operator *(const Type v) const {
        return {x_ * v, y_ * v, z_ * v};
    }

    float operator *(const Vector_<3, Type>& v) const {
        return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
    }

	void operator +=(const Vector_<3, Type>& v) {
        this->x_ += v.x_;
		this->y_ += v.y_;
		this->z_ += v.z_;
    }

    Vector_<3, Type> operator +(const Vector_<3, Type>& v) const {
		Vector_<3, Type> result = *this;
		result += v;

        return result;
    }

	void operator -=(const Vector_<3, Type>& v) {
        this->x_ -= v.x_;
		this->y_ -= v.y_;
		this->z_ -= v.z_;
    }

    Vector_<3, Type> operator -(const Vector_<3, Type>& v) const {
        Vector_<3, Type> result = *this;
		result -= v;

        return result;
    }

    Vector_<3, Type> operator -()  const {
        return {-x_, -y_, -z_};
    }

	float len() {
		return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
	}

	Vector_<3, Type>& normalize() {
		*this = (*this) * (1.f / this->len());
		return *this;
	}

	Type x_, y_, z_;
};

// ----------------------------------------------------------------

template <typename Type>
class Vector_<4, Type> {

public:
	Vector_():
		x_(Type()), y_(Type(), z_(Type()), w_(Type())) {}
	Vector_(Type x, Type y, Type z, Type w):
		x_(x), y_(y), z_(z), w_(w) {}

	const Type& operator[] (const size_t idx) const {
		assert(idx < 4);
		if (idx == 0) return this->x_;
		return idx == 1 ? this->y_ : (idx == 2 ? this->z_ : this->w_);
	}
	Type& operator[] (const size_t idx) {
		assert(idx < 4);
		if (idx == 0) return this->x_;
		return idx == 1 ? this->y_ : (idx == 2 ? this->z_ : this->w_);
	}

	Type x_, y_, z_, w_;
};

// ----------------------------------------------------------------
// ! LHS - left-hand side, RHS - right-hand side

template<size_t dimension, typename Type>
Vector_<dimension, Type> operator*(Vector_<dimension, Type> lhs, const Vector_<dimension, Type>& rhs) {
	Type result = Type();
    for (size_t idx = 0; idx < dimension; ++idx) {
		result += lhs[idx] * rhs[idx];
	}
    return result;
}

// ----------------------------------------------------------------

template<size_t dimension, typename Type>
Vector_<dimension, Type> operator+=(Vector_<dimension, Type> lhs, const Vector_<dimension, Type>& rhs) {
    for (size_t idx = 0; idx < dimension; ++idx) {
		lhs[idx] += rhs[idx];
	}
    return lhs;
}

// ----------------------------------------------------------------

template<size_t dimension, typename Type>
Vector_<dimension, Type> operator+(Vector_<dimension, Type> lhs, const Vector_<dimension, Type>& rhs) {
    Vector_<dimension, Type> result = lhs;
	result += rhs;
	return result;
}

// ----------------------------------------------------------------

template<size_t dimension, typename Type>
Vector_<dimension, Type> operator-=(Vector_<dimension, Type> lhs, const Vector_<dimension, Type>& rhs) {
    for (size_t idx = 0; idx < dimension; ++idx) {
		lhs[idx] -= rhs[idx];
	}
    return lhs;
}

// ----------------------------------------------------------------

template<size_t dimension, typename Type>
Vector_<dimension, Type> operator-(Vector_<dimension, Type> lhs, const Vector_<dimension, Type>& rhs) {
    Vector_<dimension, Type> result = lhs;
	result -= rhs;
	return result;
}

// ----------------------------------------------------------------

template<size_t dimension, typename Type, typename U>
Vector_<dimension, Type> operator*(const Vector_<dimension, Type> &lhs, const U& rhs) {
    Vector_<dimension, Type> result;
	for (size_t idx = 0; idx < dimension; ++idx) {
		result[idx] = lhs[idx] * rhs;
	}
    return result;
}

// ----------------------------------------------------------------

template<size_t dimension,typename Type>
Vector_<dimension, Type> operator-(const Vector_<dimension, Type> &lhs) {
    return lhs * Type(-1);
}

// ----------------------------------------------------------------
// ! https://en.wikipedia.org/wiki/Cross_product#Coordinate_notation

template <typename Type>
Vector_<3, Type> cross(Vector_<3, Type> v1, Vector_<3, Type> v2) {
    return Vector_<3, Type> (v1.y_ * v2.z_ - v1.z_ * v2.y_,
							 v1.z_ * v2.x_ - v1.x_ * v2.z_,
							 v1.x_ * v2.y_ - v1.y_ * v2.x_);
}

// ----------------------------------------------------------------

template <size_t dimension, typename Type>
std::ostream& operator<<(std::ostream& out, const Vector_<dimension, Type>& vector) {
    for (size_t idx = 0; idx < dimension; ++idx) {
        out << vector[idx] << " ";
    }
    return out;
}

// ----------------------------------------------------------------
