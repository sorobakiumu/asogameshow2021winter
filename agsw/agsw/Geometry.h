#pragma once
#include <memory>

//2D座標・ベクトルを表す構造体
struct Vector2 {
	Vector2() :x(0), y(0) {}
	Vector2(float inx, float iny) :x(inx), y(iny) {}
	float x, y;
	///ベクトルの大きさを返します
	float Magnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
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

///内積を返す
float Dot(const Vector2& va, const Vector2& vb);

///外積を返す
float Cross(const Vector2& va, const Vector2& vb);

///内積演算子
float operator*(const Vector2& va, const Vector2& vb);

///外積演算子
float operator%(const Vector2& va, const Vector2& vb);

float GetRadian(std::pair<Vector2, Vector2> hillPos);

Vector2 RefLectVec(const Vector2& i, const Vector2& n);

class Boll {
public:
	Vector2 pos_;
	Vector2 vec_;

	Boll(Vector2 pos) {
		pos_ = pos;
		vec_ = {};
	}
	void updata();
	bool alive = true;
private:
};