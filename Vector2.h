#pragma once

namespace csr
{
	struct Vector2
	{
		int x, y;

		Vector2()
		{
			x = 0;
			y = 0;
		}

		Vector2(int x, int y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2 operator +(const Vector2& v) const
		{
			return Vector2(x + v.x, y + v.y);
		}


		void operator +=(const Vector2& v)
		{
			*this = *this + v;
		}

		Vector2 operator -(const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y);
		}


		void operator -=(const Vector2& v)
		{
			*this = *this - v;
		}

		Vector2 operator *(const int& n) const
		{
			return Vector2(x * n, y * n);
		}

		void operator *=(const int& n)
		{
			*this = *this * n;
		}

		Vector2 operator /(const int& n) const
		{
			return Vector2(x / n, y / n);
		}

		void operator /=(const int& n)
		{
			*this = *this / n;
		}

		bool operator ==(const Vector2& v)
		{
			return x == v.x && y == v.y;
		}

		void Reverse()
		{
			*this *= -1;
		}
	};
}