#ifndef AnimOBJNODE_H
#define AnimOBJNODE_H

#include <maya/MTime.h>
#include <maya/MFnMesh.h>
#include <maya/MPoint.h>
#include <maya/MFloatPoint.h>
#include <maya/MFloatPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MPxNode.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MFnMeshData.h>
#include <maya/MIOStream.h>
#include "WavefrontOBJ.h"

#ifndef McheckErr
#define McheckErr(stat,msg)			\
	if ( MS::kSuccess != stat ) {	\
		cerr << msg;				\
		return MS::kFailure;		\
	}
#endif

extern string g_Filepath; // ex) c:\\temp\\my_objs
extern string g_FilenameWithoutExtAndSeq; // file name without extension and sequence number
extern string g_FileExt; // ex) .obj

class AnimOBJNode : public MPxNode
{
public:
	AnimOBJNode();
	virtual 		~AnimOBJNode() {};
	virtual MStatus compute(const MPlug& plug, MDataBlock& data);
	static  void*	creator();
	static  MStatus initialize();

	static MObject	time;
	static MObject	outputMesh;
	static MTypeId	id;

private:
	
	CWavefrontOBJ m_OBJMesh;

protected:
	MObject createMesh(const MTime& time, MObject& outData, MStatus& stat);
};

#endif // AnimOBJNODE_H