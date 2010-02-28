#include <maya/MFnPlugin.h>
#include <maya/MPxCommand.h>
#include <maya/MGlobal.h>

#include "AnimOBJNode.h"
#include "AnimOBJ_LoadCommand.h"
#include <sstream>

MStatus initializePlugin(MObject obj)
{
	MStatus   status;
	MFnPlugin plugin(obj, "AnimOBJ", "0.1", "Any");

	status = plugin.registerNode("AnimOBJNode", AnimOBJNode::id,
						 AnimOBJNode::creator, AnimOBJNode::initialize);

	plugin.registerCommand( "AnimOBJ_LoadCommand", AnimOBJ_LoadCommand::creator );

	MGlobal::executeCommand( "source AnimOBJMain.mel" );
    MGlobal::executeCommand( "AnimOBJMain_initialize" );

	if (!status) {
		status.perror("registerNode");
		return status;
	}

	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus	  status;
	MFnPlugin plugin(obj);

	status = plugin.deregisterNode(AnimOBJNode::id);
	
	plugin.deregisterCommand( "AnimOBJ_LoadCommand" );
	
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}

	return status;
}




