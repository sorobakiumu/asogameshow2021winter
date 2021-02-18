#include"Geometry.h"
#include<DxLib.h>
#include<cmath>

void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}

Vector2
Vector2::operator*(float scale) {
	return Vector2(x * scale, y * scale);
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x + vb.x, va.y + vb.y);
}

Vector2 operator-(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x - vb.x, va.y - vb.y);
}

Vector2 operator/(const Vector2& va, const float vb)
{
	if (vb == 0)
		return{ 0 ,0 };
	return Vector2(va.x / vb, va.y / vb);
}

float
Vector2::Magnitude()const {
	return hypot(x, y);
}

void
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}

Vector2
Vector2::Normalized() {
	float mag = Magnitude();
	return Vector2(x / mag, y / mag);
}

///���ς�Ԃ�
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x * vb.x + va.y * vb.y;
}

///�O�ς�Ԃ�
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x * vb.y - vb.x * va.y;
}

///���ω��Z�q
float
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///�O�ω��Z�q
float
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}

void
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}

float GetRadian(std::pair<Vector2, Vector2> hillPos)
{
	auto up = hillPos.first;
	auto down = hillPos.second;

	if (hillPos.second.y < hillPos.first.y) {
		up = hillPos.second;
		down = hillPos.first;
	}
	return atan2(up.y - down.y, up.x - down.x);
}
Vector2 RefLectVec(const Vector2& i, const Vector2& n)
{
	//���˃x�N�g���̎�
	//R=I-2*�iN�EI�jN
	//�����̂܂܃v���O�����ɂ���
	//�������A�I�y���[�^�[�I�[�o�[���[�h
	//�̊֌W��
	//
	Vector2 r = i - Vector2(n.x * (Dot(i, n) * 2), n.y * (Dot(i, n) * 2));
	return r;
}