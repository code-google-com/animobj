#include <maya/MFnPlugin.h>

#include <maya/MPxCommand.h>
#include <maya/MGlobal.h>
#include "AnimOBJNode.h"

class AnimOBJ_LoadCommand : public MPxCommand
{
public:
	//creator function
	static void *creator();

	//command execution functions
	virtual MStatus doIt(const MArgList &args);
};

MStatus AnimOBJ_LoadCommand::doIt( const MArgList& args ) 
{
	MStatus stat;
	string sStat;

	g_Filepath = "";
	g_FilenameWithoutExtAndSeq = "";
	g_FileExt = "";

	if ( 1 )
	{
		stat = MGlobal::executeCommand("createNode transform -n AnimOBJ1;");
		McheckErr(stat, "ERROR createNode transform -n AnimOBJ1;");

		stat = MGlobal::executeCommand("createNode mesh -n AnimOBJShape1 -p AnimOBJ1;");
		McheckErr(stat, "ERROR createNode mesh -n AnimOBJShape1 -p AnimOBJ1;");

		stat = MGlobal::executeCommand("sets -add initialShadingGroup AnimOBJShape1;");
		McheckErr(stat, "ERROR sets -add initialShadingGroup AnimOBJShape1;");

		stat = MGlobal::executeCommand("createNode AnimOBJNode -n AnimOBJNode1;");
		McheckErr(stat, "ERROR createNode AnimOBJNode -n AnimOBJNode1;");
		
		stat = MGlobal::executeCommand("connectAttr time1.outTime AnimOBJNode1.time;");
		McheckErr(stat, "ERROR connectAttr time1.outTime AnimOBJNode1.time;");
		
		stat = MGlobal::executeCommand("connectAttr AnimOBJNode1.outputMesh AnimOBJShape1.inMesh;");
		McheckErr(stat, "ERROR connectAttr AnimOBJNode1.outputMesh AnimOBJShape1.inMesh;");
	}

	//sStat = str;

	/*if(stat==MS::kSuccess) 
		setResult(sStat.c_str());
	else 
		displayError("[ERROR] could not load AnimOBJ file");
	
	return stat;*/

	return MS::kSuccess;
}

void* AnimOBJ_LoadCommand::creator() {
	return new AnimOBJ_LoadCommand;
}