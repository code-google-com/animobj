#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

#include <math.h>

class CPoint3D;

class CVector3D
{
public:
	double m_X;
	double m_Y;
	double m_Z;

	CVector3D() 
	{
		m_X = 0.0f;
		m_Y = 0.0f;
		m_Z = 0.0f;
	}

	CVector3D(double x, double y, double z) { m_X = x; m_Y = y; m_Z = z; };
	CVector3D(const CVector3D& other);
	CVector3D(const CVector3D& begin, const CVector3D& end);
	virtual ~CVector3D() {};

public:
	CVector3D& Normalize();
	CVector3D Cross(const CVector3D& v) const { return CVector3D(m_Y*v.m_Z - m_Z*v.m_Y, m_Z*v.m_X - m_X*v.m_Z, m_X*v.m_Y - m_Y*v.m_X); };
	double Dot(const CVector3D& v) const { return m_X * v.m_X + m_Y * v.m_Y + m_Z * v.m_Z; };
	double Length() const { return sqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z); };

	CVector3D& operator=(const CVector3D& other);
	CVector3D& operator-=(const CVector3D& other);
	CVector3D& operator+=(const CVector3D& other);
	CVector3D& operator*=(double val);
	CVector3D operator-(const CVector3D& other) const;
	CVector3D operator+(const CVector3D& other) const;
	CVector3D operator/(double val) const;
	CVector3D operator*(double val) const;

	friend CVector3D operator*(double val, const CVector3D& other);
	friend CVector3D operator-(const CVector3D& other);

};

#endif // __VECTOR3D_H__