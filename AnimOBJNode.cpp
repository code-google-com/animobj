#include <maya/MPxCommand.h>

#include "AnimOBJNode.h"
#include "StringTokenizer.h"
#include <sstream>


/*
// Unfortunately, Maya plugin didn't work with Boost either static or dynamic(dll) links. 
// If you want to try, uncomment below block. 
#define BOOST_LIB_DIAGNOSTIC
#include <boost/filesystem/path.hpp>

namespace boostfs = boost::filesystem;
using boost::filesystem::path;
*/

MObject AnimOBJNode::time;
MObject AnimOBJNode::outputMesh;
MTypeId AnimOBJNode::id(0x80001);

string g_Filepath; // ex) c:\\temp\\my_objs
string g_FilenameWithoutExtAndSeq; // file name without extension and sequence number. 
								   // If the real file name is 'my_anim_01.obj', then this is 'my_anim'. 
string g_FileExt; // ex) '.obj'. Note, it includes dot. 

AnimOBJNode::AnimOBJNode()
{
	g_Filepath.clear();
	g_FilenameWithoutExtAndSeq.clear();
}

void* AnimOBJNode::creator()
{
	return new AnimOBJNode;
}

MStatus AnimOBJNode::initialize()
{
	MFnUnitAttribute unitAttr;
	MFnTypedAttribute typedAttr;

	MStatus returnStatus;

	AnimOBJNode::time = unitAttr.create( "time", "tm",
										  MFnUnitAttribute::kTime,
										  0.0, &returnStatus );
	McheckErr(returnStatus, "ERROR creating AnimOBJNode time attribute\n");


	AnimOBJNode::outputMesh = typedAttr.create( "outputMesh", "out",
												 MFnData::kMesh,
												 &returnStatus ); 
	McheckErr(returnStatus, "ERROR creating AnimOBJNode output attribute\n");
	typedAttr.setStorable(false);

	returnStatus = addAttribute(AnimOBJNode::time);
	McheckErr(returnStatus, "ERROR adding time attribute\n");

	returnStatus = addAttribute(AnimOBJNode::outputMesh);
	McheckErr(returnStatus, "ERROR adding outputMesh attribute\n");

	returnStatus = attributeAffects(AnimOBJNode::time,
								    AnimOBJNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects\n");

	return MS::kSuccess;
}

MObject AnimOBJNode::createMesh(const MTime& time, MObject& outData, MStatus& stat)
{
	int frame;
	MFnMesh meshFS;

	frame = (int)time.as( MTime::kFilm );

	// generate file path based on the user's file selection and frame number
	std::stringstream int2Str;
	int2Str << frame;

	string filepath = g_Filepath + g_FilenameWithoutExtAndSeq + "_" + int2Str.str() + g_FileExt;

	string msg = "Loading " + filepath;
	MPxCommand::setResult(msg.c_str());

	// load OBJ
	if ( !m_OBJMesh.Load(filepath) )
		return MObject::kNullObj;

	MFloatPointArray points;
	MIntArray faceCounts;
	MIntArray faceConnects;

	std::list<CVector3D>::const_iterator iterVer;

	for ( iterVer = m_OBJMesh.GetVertexList().begin(); iterVer != m_OBJMesh.GetVertexList().end(); iterVer++ )
	{
		MFloatPoint pnt((float)(*iterVer).m_X, (float)(*iterVer).m_Y, (float)(*iterVer).m_Z);
		points.append(pnt);
	}

	std::list<CMeshFace>::const_iterator iterFace;

	for ( iterFace = m_OBJMesh.GetFaceList().begin(); iterFace != m_OBJMesh.GetFaceList().end(); iterFace++ )
	{
		int cnt = (*iterFace).CountVertices();
		faceCounts.append(cnt);
	} 
 
	for ( iterFace = m_OBJMesh.GetFaceList().begin(); iterFace != m_OBJMesh.GetFaceList().end(); iterFace++ )
	{
		const std::list<int>& vertIndexList = (*iterFace).GetVertexIndexList();

		std::list<int>::const_iterator iterVrtIndex;

		for ( iterVrtIndex = vertIndexList.begin(); iterVrtIndex != vertIndexList.end(); iterVrtIndex++ )
		{
			int index = (*iterVrtIndex)-1;
			faceConnects.append(index);
		}
	}

	MObject newMesh = meshFS.create(points.length(), faceCounts.length(), points, faceCounts, faceConnects, outData, &stat);
	return newMesh;
}

MStatus AnimOBJNode::compute(const MPlug& plug, MDataBlock& data)
{	
	MStatus returnStatus;

	if (plug == outputMesh) {
		/* Get time */
		MDataHandle timeData = data.inputValue( time, &returnStatus ); 
		McheckErr(returnStatus, "Error getting time data handle\n");
		MTime time = timeData.asTime();

		/* Get output object */

		MDataHandle outputHandle = data.outputValue(outputMesh, &returnStatus);
		McheckErr(returnStatus, "ERROR getting polygon data handle\n");

		MFnMeshData dataCreator;
		MObject newOutputData = dataCreator.create(&returnStatus);
		McheckErr(returnStatus, "ERROR creating outputData");

		MStatus stat;
		string sStat;

		if ( g_Filepath == "" )
		{
			TCHAR lpstrFile[MAX_PATH]="";  // MAX_PATH = 260

			OPENFILENAME OFN = 
						{ 
							sizeof(OPENFILENAME), 
							NULL, NULL,
							"Obj Files (*.obj)\0*.obj\0All(*.*)\0*.*\0\0",
							NULL, 0, 1, 
							lpstrFile, MAX_PATH, 
							NULL, 0,
							NULL, "Load *.obj File Dialog", 
							OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, 0, 
							0, "obj", 0, 
							NULL, NULL 
						};

			if ( !GetOpenFileName(&OFN) )
			{
				return MS::kFailure;
			}

			/*
			// Unfortunately, Maya plugin didn't work with Boost either static or dynamic(dll) links. 
			// If you want to try, uncomment below block. 
			
			boostfs::path filepath(lpstrFile);

			g_FileExt = filepath.extension();
			g_Filepath = filepath.parent_path().string();
			g_FilenameWithoutExtAndSeq = filepath.stem();*/

			string inputPath(lpstrFile);
			g_FileExt = inputPath.substr(inputPath.find_last_of('.'));
			g_Filepath = inputPath.substr(0, inputPath.find_last_of('\\')+1);
			g_FilenameWithoutExtAndSeq = inputPath.substr(inputPath.find_last_of('\\')+1, inputPath.find_last_of('_')-inputPath.find_last_of('\\')-1);
		}

		if ( createMesh(time, newOutputData, returnStatus) == MObject::kNullObj )
		{
			return MS::kFailure;
		}

		outputHandle.set(newOutputData);
		data.setClean(plug);
	} else
		return MS::kUnknownParameter;

	return MS::kSuccess;
}