#pragma once
#include <memory>

//2D���W�E�x�N�g����\���\����
struct Vector2 {
	Vector2() :x(0), y(0) {}
	Vector2(float inx, float iny) :x(inx), y(iny) {}
	float x, y;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector2 Normalized();

	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(float scale);
	Vector2 operator*(float scale);
	Vector2 operator-() {
		return Vector2(-x, -y);
	}
};

Vector2 operator+(const Vector2& va, const Vector2 vb);
Vector2 operator-(const Vector2& va, const Vector2 vb);
Vector2 operator/(const Vector2& va, const float vb);

///���ς�Ԃ�
float Dot(const Vector2& va, const Vector2& vb);

///�O�ς�Ԃ�
float Cross(const Vector2& va, const Vector2& vb);

///���ω��Z�q
float operator*(const Vector2& va, const Vector2& vb);

///�O�ω��Z�q
float operator%(const Vector2& va, const Vector2& vb);
//
//Vector2 RefLectVec(const Vector2& i, const Vector2& n)
//{
//	Vector2 r = i - Vector2(n.x * (Dot(i, n) * 2), n.y * (Dot(i, n) * 2));
//	return r;
//}
//
//float GetRadian(std::pair<Vector2, Vector2> hillPos)
//{
//	auto up = hillPos.first;
//	auto down = hillPos.second;
//
//	if (hillPos.second.y < hillPos.first.y) {
//		up = hillPos.second;
//		down = hillPos.first;
//	}
//	return atan2(up.y - down.y, up.x - down.x);
//}

struct Vector3 {
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float ix, float iy,float iz) :x(ix), y(iy), z(iz){}
	float x, y, z;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector3 Normalized();

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(float scale);
	Vector3 operator*(float scale);
	Vector3 operator-() {
		return Vector3(-x, -y, -z);
	}
};

Vector3 operator+(const Vector3& va, const Vector3 vb);
Vector3 operator-(const Vector3& va, const Vector3 vb);

///���ς�Ԃ�
float Dot(const Vector3& va, const Vector3& vb);
///���ω��Z�q
float operator*(const Vector3& va, const Vector3& vb);

