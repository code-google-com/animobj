#pragma once

#include <list>
#include "Mesh.h"

class CMeshFace
{
public:
	CMeshFace(CMesh* pMesh = NULL);
	CMeshFace(const CMeshFace& other);
	virtual ~CMeshFace(void);

protected:
	// pointer to the parent mesh object
	CMesh* m_pParMesh; // = NULL

	std::list<int> m_VertexIndexList;
	std::list<int> m_NormalVecIndexList;

public:
	void AddVertexIndex(int index);
	void AddNormalVecIndex(int index);
	const std::list<int>& GetVertexIndexList() const { return m_VertexIndexList; }
	const std::list<int>& GetNormalVecIndexList() const { return m_NormalVecIndexList; }
	int CountVertices() const { return (int)m_VertexIndexList.size(); }


	CMeshFace& operator=(const CMeshFace& other);
};
