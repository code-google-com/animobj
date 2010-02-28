#include <iostream>
#include <fstream>

#include "WavefrontOBJ.h"
#include "StringTokenizer.h"
#include "MeshFace.h"

CWavefrontOBJ::CWavefrontOBJ(void)
{
}

CWavefrontOBJ::~CWavefrontOBJ(void)
{
}

bool CWavefrontOBJ::Load(string filepath)
{
	ifstream inFile(filepath.c_str());
	string sLine;
	vector<string> sTokens;

	if ( !inFile.is_open() )
		return false;

	Clear();

	while (!inFile.eof() )
	{
		getline(inFile, sLine);
		sTokens.clear(); 
		int numFound = StringTokenizer(sLine, string(" "), sTokens, true);

		if ( numFound == 0 )
			continue;

		vector <string>::iterator iter;
		string sToken; 

		iter = sTokens.begin();
		sToken = *(iter);
		
		if ( sToken == "#" ) // comment
			continue;
		else if ( sToken == "v" ) // vertex
		{
			CVector3D vertex;
			
			// x
			++iter;
			sToken = (*iter);			
			vertex.m_X = (float)atof(sToken.c_str());

			// y
			++iter;
			sToken = (*iter);			
			vertex.m_Y = (float)atof(sToken.c_str());

			// z
			++iter;
			sToken = (*iter);			
			vertex.m_Z = (float)atof(sToken.c_str());

			m_VertexList.push_back(vertex);
		}
		else if ( sToken == "vn" ) // vertex normal
		{
			CVector3D nv;
			
			// x
			++iter;
			sToken = (*iter);			
			nv.m_X = (float)atof(sToken.c_str());

			// y
			++iter;
			sToken = (*iter);			
			nv.m_Y = (float)atof(sToken.c_str());

			// z
			++iter;
			sToken = (*iter);			
			nv.m_Z = (float)atof(sToken.c_str());

			m_NormalVecList.push_back(nv);

		}
		else if ( sToken == "f" ) // face
		{
			CMeshFace face;
			vector<string> sTokens2;

			for ( iter = sTokens.begin() + 1; iter != sTokens.end(); iter++ )
			{
				sToken = (*iter);
				sTokens2.clear();
				numFound = StringTokenizer(sToken, string("/"), sTokens2, true);

				if ( numFound > 0 )
				{
					face.AddVertexIndex(atoi(sTokens2[0].c_str()));

					if ( numFound == 3 )
						face.AddNormalVecIndex(atoi(sTokens2[2].c_str()));
				}
				else
					face.AddVertexIndex(atoi(sToken.c_str()));
			}

			AddFace(face);
		}		
	}

	inFile.close();

    return true;
}
