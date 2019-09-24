#pragma once


template <class T>
class Vector2d_T
{
public:

	Vector2d_T<T>() = default;

	Vector2d_T<T>(const Vector2d_T<T>&) = default;

	Vector2d_T<T>(Vector2d_T<T>&&) = default;
	
	Vector2d_T<T>& operator = (Vector2d_T<T>&& v) = default;

	Vector2d_T<T>(T X, T Y) : x(X), y(Y){}

	~Vector2d_T<T>() = default;

	template <class T2>
	explicit operator Vector2d_T<T2>() const
	{
		return { static_cast<T2>(x), static_cast<T2>(y) };
	}

	Vector2d_T<T>& operator = (const Vector2d_T<T>& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	Vector2d_T<T>& operator *= (const Vector2d_T<T>& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vector2d_T<T> operator * (const Vector2d_T<T>& v) const
	{
		return { x * v.x, y * v.y };
	}

	Vector2d_T<T>& operator /= (T divider)
	{
		if(divider != 0)
		{
			x /= divider;
			y /= divider;
		}
		return *this;
	}

	Vector2d_T<T> operator / (T divider) const
	{
		if(divider == 0)
			divider = 1;
		return { x / divider, y / divider };
	}

	Vector2d_T<T>& operator += (const Vector2d_T<T>& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2d_T<T> operator + (const Vector2d_T<T>& v) const
	{
		return { x + v.x, y + v.y };
	}

	
	Vector2d_T<T>& operator -= (const Vector2d_T<T>& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2d_T<T> operator - (const Vector2d_T<T>& v) const
	{
		return { x - v.x, y - v.y };
	}

	bool operator == (const Vector2d_T<T>& v) const
	{
		return x == v.x && y == v.y;
	}

	bool operator != (const Vector2d_T<T>& v) const
	{
		return x != v.x || y != v.y;
	}
	
	T x = 0, y = 0;
};


using Vector2d = Vector2d_T<float>;

using Vector2di = Vector2d_T<int_t>;


