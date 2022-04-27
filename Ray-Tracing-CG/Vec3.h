#pragma once

#include "cuda_runtime.h"

#include <iostream>
#include <cmath>

using namespace std;

class Vec3 {
public:
	float e[3];

	__host__ __device__ Vec3() : e{ 0, 0, 0 } {}
	__host__ __device__ Vec3(float a, float b, float c) : e{ a, b, c } {}

	__host__ __device__ float x() { return e[0]; }
	__host__ __device__ float y() { return e[1]; }
	__host__ __device__ float z() { return e[2]; }

	__host__ __device__ Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
	__host__ __device__ float operator[](int i) const { return e[i]; }

	__host__ __device__ Vec3& operator+=(const Vec3& v) {
		e[0] += v[0];
		e[1] += v[1];
		e[2] += v[2];
		return *this;
	}

	__host__ __device__ Vec3& operator*=(const float k) {
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
		return *this;
	}

	__host__ __device__ Vec3& operator/=(const float k) {
		return *this *= (1 / k);
	}

	__host__ __device__ float length() const {
		return sqrt(magnitude());
	}

	__host__ __device__ float magnitude() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
};

using Point = Vec3;
using Color = Vec3;


inline ostream& operator<<(ostream& out, const Vec3& v) {
	return out << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')' << endl;
}

__host__ __device__ inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

__host__ __device__ inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

__host__ __device__ inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

__host__ __device__ inline Vec3 operator*(float k, const Vec3& v) {
	return Vec3(k * v[0], k * v[1], k * v[2]);
}

__host__ __device__ inline Vec3 operator*(const Vec3& v, float k) {
	return k * v;
}

__host__ __device__ inline Vec3 operator/(const Vec3& v, float k) {
	return v * (1/k);
}


// Opérations mathématiques
__host__ __device__ inline float dot(const Vec3& u, const Vec3& v) {
	return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

__host__ __device__ inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u[1] * v[2] - u[2] * v[1],
				u[2] * v[0] - u[0] * v[2],
				u[0] * v[1] - u[1] * v[0]);
}

__host__ __device__ inline Vec3 unit(const Vec3& v) {
	return v / v.length();
}