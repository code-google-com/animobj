#include "Mesh.h"
#include "MeshFace.h"

#include <limits>


CMesh::CMesh(void)
{
}

CMesh::CMesh(const CMesh& other)
{
	m_VertexList = other.m_VertexList;
	m_NormalVecList = other.m_NormalVecList;
	m_FaceList = other.m_FaceList;
}

CMesh::~CMesh(void)
{
	
}

void CMesh::AddFace(const CMeshFace& face)
{
	m_FaceList.push_back(face);
}

void CMesh::Clear()
{
	m_VertexList.clear();
	m_NormalVecList.clear();
	m_FaceList.clear();
}

CMesh& CMesh::operator=(const CMesh& other)
{
	if ( this == &other )
		return (*this);

	m_VertexList = other.m_VertexList;
	m_NormalVecList = other.m_NormalVecList;
	m_FaceList = other.m_FaceList;

	return (*this);
}