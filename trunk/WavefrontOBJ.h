#pragma once

#include <string>

#include "Mesh.h"
#include "MeshFace.h"

using namespace std;

class CWavefrontOBJ : public CMesh
{
public:
	CWavefrontOBJ(void);
	virtual ~CWavefrontOBJ(void);

protected:
	string m_strFileName;
	string m_strFileFullPath;

public:
	virtual bool Load(string filepath); 
};
