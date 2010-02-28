#include "MeshFace.h"

CMeshFace::CMeshFace(CMesh* pMesh /*= NULL*/)
{
	m_pParMesh = pMesh;
}

CMeshFace::~CMeshFace(void)
{
}

CMeshFace::CMeshFace(const CMeshFace& other)
{
	m_pParMesh = other.m_pParMesh;
	m_VertexIndexList = other.m_VertexIndexList;
	m_NormalVecIndexList = other.m_NormalVecIndexList;
}

void CMeshFace::AddVertexIndex(int index)
{
	m_VertexIndexList.push_back(index);
}

void CMeshFace::AddNormalVecIndex(int index)
{
	m_NormalVecIndexList.push_back(index);
}

CMeshFace& CMeshFace::operator=(const CMeshFace& other)
{
	m_pParMesh = other.m_pParMesh;
	m_VertexIndexList = other.m_VertexIndexList;
	m_NormalVecIndexList = other.m_NormalVecIndexList;

	return (*this);
}