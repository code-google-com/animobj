#pragma once

#include <list>
#include "Vector3D.h"

class CMeshFace;

using namespace std;

class CMesh
{
public:
	CMesh(void);
	CMesh(const CMesh& other);
	virtual ~CMesh(void);

protected:
	list<CVector3D> m_VertexList;
	list<CVector3D> m_NormalVecList;
	list<CMeshFace> m_FaceList;

public:
	virtual bool Load(string filepath) = 0;
	const list<CVector3D>& GetVertexList() const { return m_VertexList; }
	const list<CVector3D>& GetNormalVecList() const { return m_NormalVecList; }
	const list<CMeshFace>& GetFaceList() const { return m_FaceList; }

	int CountVertices() const { return (int)m_VertexList.size(); }
	int CountNormals() const { return (int)m_NormalVecList.size(); }
	int CountFaces() const { return (int)m_FaceList.size(); }

	void AddFace(const CMeshFace& face);
	void Clear();	

	CMesh& operator=(const CMesh& other);
};
