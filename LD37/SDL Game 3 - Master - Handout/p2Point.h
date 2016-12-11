// ----------------------------------------------------
// Point class    -----------
// ----------------------------------------------------

#ifndef __P2POINT_H__
#define __P2POINT_H__

template<class TYPE>
class p2Point
{
public:

	TYPE x, y;

	p2Point()
	{}

	p2Point(const p2Point& p)
	{
		x = p.x;
		y = p.y;
	}

	// Math ------------------------------------------------
	p2Point operator -(const p2Point &v) const
	{
		p2Vector2 r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	p2Point operator + (const p2Point &v) const
	{
		p2Vector2 r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	const p2Point& operator -=(const p2Point &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const p2Point& operator +=(const p2Point &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}

	bool operator ==(const p2Point& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const p2Point& v) const
	{
		return (x != v.x || y != v.y);
	}

	// Utils ------------------------------------------------
	bool IsZero() const
	{
		
		return (x == 0 && y == 0);
	}

	p2Point& SetToZero()
	{
		x = y = 0;
		return(*this);
	}

	p2Point& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	// Distances ---------------------------------------------
	TYPE DistanceTo(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (TYPE)sqrt((fx*fx) + (fy*fy));
	}

	float Length()
	{
		return (float)sqrt((x*x) + (y*y));
	}

	p2Point& Scale(float e)
	{
		x = (TYPE)x * e;
		y = (TYPE)y * e;

		return(*this);
	}

	p2Point& Divide(float e)
	{
		float xx = x / e;
		float yy = y / e;
		
		//escala para que no de fallos
		x = (int)(xx * 1.5f);
		y = (int)(yy * 1.5f);

		return(*this);
	}

	p2Point& Normalize()
	{

		
		float lon = Length();

		if (lon != 0)
		{
			return Divide(lon);
		}
		else
			return SetToZero();


	}
};

#endif // __P2POINT_H__