#include "Vector3D.h"

CVector3D::CVector3D(const CVector3D& other) 
{ 
	m_X = other.m_X; 
	m_Y = other.m_Y; 
	m_Z = other.m_Z; 
}

CVector3D::CVector3D(const CVector3D& begin, const CVector3D& end)
{
	m_X = end.m_X - begin.m_X; 
	m_Y = end.m_Y - begin.m_Y; 
	m_Z = end.m_Z - begin.m_Z; 
}

CVector3D& CVector3D::Normalize()
{
	double d = sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);

	if ( d == 0 )
		return *this;

	m_X = m_X / d;
	m_Y = m_Y / d;
	m_Z = m_Z / d;

	return *this;
}

CVector3D CVector3D::operator-(const CVector3D& other) const
{ 
	return CVector3D(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z); 
}

CVector3D CVector3D::operator+(const CVector3D& other) const
{ 
	return CVector3D(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z); 
}

CVector3D CVector3D::operator/(double val) const
{ 
	if ( val != 0.0f )
		return CVector3D(m_X / val, m_Y / val, m_Z / val); 
	else
		return CVector3D(0.0f, 0.0f, 0.0f);
}

CVector3D& CVector3D::operator=(const CVector3D& other) 
{ 
	m_X = other.m_X; 
	m_Y = other.m_Y; 
	m_Z = other.m_Z; 
	
	return *this; 
}

CVector3D& CVector3D::operator-=(const CVector3D& other) 
{ 
	m_X -= other.m_X; 
	m_Y -= other.m_Y; 
	m_Z -= other.m_Z; 
	
	return *this; 
}

CVector3D& CVector3D::operator+=(const CVector3D& other) 
{ 
	m_X += other.m_X; 
	m_Y += other.m_Y; 
	m_Z += other.m_Z; 
	
	return *this; 
}

CVector3D& CVector3D::operator*=(double val)
{
	m_X *= val; 
	m_Y *= val; 
	m_Z *= val; 
	
	return *this; 
}

CVector3D CVector3D::operator*(double val) const
{
	CVector3D vec(*this);

	vec.m_X *= val;
	vec.m_Y *= val;
	vec.m_Z *= val;

	return vec;
}

CVector3D operator*(double val, const CVector3D& other)
{
	return other * val;
}


CVector3D operator-(const CVector3D& other)
{
	CVector3D vec(other);

	vec.m_X = -vec.m_X;
	vec.m_Y = -vec.m_Y;
	vec.m_Z = -vec.m_Z;

	return vec;
}
