//========================================================================================
//  
//  $File: $
//  
//  Owner: james.dd.sun
//  
//  $Author: $
//  
//  $DateTime: $
//  
//  $Revision:  $
//  
//  $Change: $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ITreeViewHierarchyAdapter.h"
#include "IWorkspace.h"
#include "ISession.h"
#include "IIDSCDataModel.h"
// General includes:
#include "CPMUnknown.h"
#include "CAlert.h"
#include <UIDNodeID.h>

// Project includes:
#include "IDShortcutsID.h"
#include "IDSCTreeNode.h"


class IDSCTreeHierAdapter : 
	public CPMUnknown<ITreeViewHierarchyAdapter>
{
public:
	IDSCTreeHierAdapter(IPMUnknown* boss);
	virtual ~IDSCTreeHierAdapter();
	virtual NodeID_rv GetRootNode() const;
	virtual NodeID_rv GetParentNode(const NodeID& node) const;
	virtual int32 GetNumChildren(const NodeID& node) const;
	virtual NodeID_rv GetNthChild(
		const NodeID& node, const int32& nth) const;

	virtual int32 GetChildIndex(
		const NodeID& parent, const NodeID& child) const;

	virtual NodeID_rv GetGenericNodeID() const;

};	

CREATE_PMINTERFACE(IDSCTreeHierAdapter,kIDShortcutsTVHierarchyAdapterImpl)

IDSCTreeHierAdapter::IDSCTreeHierAdapter(IPMUnknown* boss) : 
	CPMUnknown<ITreeViewHierarchyAdapter>(boss)
{
}

IDSCTreeHierAdapter::~IDSCTreeHierAdapter()
{
}

NodeID_rv IDSCTreeHierAdapter::GetRootNode() const
{
	do {
	InterfacePtr<IWorkspace> workSpace(GetExecutionContextSession()->QueryWorkspace());
	ASSERT( workSpace);	
	if(nil == workSpace)
		break;

	InterfacePtr<IIDSCDataModel> idSCData(workSpace, UseDefaultIID());
	if(nil == idSCData)
		break;

	UID rootUID = idSCData->GetRootUID();
	return UIDNodeID::Create(rootUID);

	}while(kFalse);

	return kInvalidNodeID;
}


/* GetParentNode
*/
NodeID_rv IDSCTreeHierAdapter::GetParentNode(const NodeID& node) const
{
	// The root has no parent: this will be a general result	
	do
	{
		TreeNodePtr<UIDNodeID> nodeID(node);
		ASSERT(nodeID);
		if (nodeID == nil)
			break; 

		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(workspace);
		if(nil == workspace)
			break;

		InterfacePtr<IIDSCDataModel> model(workspace, UseDefaultIID());
		ASSERT(model);
		UID uid = nodeID->GetUID();
		if(nil == model || uid == model->GetRootUID())
			break;

		UID parentUID = model->GetParentUID(uid);
		return UIDNodeID::Create(parentUID);

	} while(kFalse);

	return kInvalidNodeID;	
}


/*
*/
int32 IDSCTreeHierAdapter::GetNumChildren(const NodeID& node) const
{
	int32 retval=0;
	do
	{
		TreeNodePtr<UIDNodeID> nodeID(node);
		if (nodeID == nil)
			break;

		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(workspace);
		if(nil == workspace)
			break;

		InterfacePtr<IIDSCDataModel> model(workspace, UseDefaultIID());
		ASSERT(model);
		UID uid = nodeID->GetUID();
		if(nil == model)
			break;

		retval = model->GetChildCount(nodeID->GetUID());
	} while(kFalse);
	
	return retval;
}

/* GetNthChild
*/
NodeID_rv IDSCTreeHierAdapter::GetNthChild(
	const NodeID& node, const int32& nth) const
{
	do
	{
		TreeNodePtr<UIDNodeID> nodeID(node);
		if (nodeID == nil)
			break;
		
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		ASSERT(workspace);
		if(nil == workspace)
			break;

		InterfacePtr<IIDSCDataModel> model(workspace, UseDefaultIID());
		ASSERT(model);
		if(nil == model)
			break;

		UID childUid = model->GetNthChildUID(nodeID->GetUID(), nth);	
		return UIDNodeID::Create(childUid);
		
	} while(kFalse);
	return kInvalidNodeID;
}


/* GetChildIndex
*/
int32 IDSCTreeHierAdapter::GetChildIndex(
	const NodeID& parent, const NodeID& child) const
{
	do
	{
		TreeNodePtr<UIDNodeID> parentFileNodeID(parent);
		ASSERT(parentFileNodeID);
		if(parentFileNodeID==nil)
		{
			break;
		}
		TreeNodePtr<UIDNodeID> childFileNodeID(child);
		ASSERT(childFileNodeID);
		if(childFileNodeID==nil)
		{
			break;
		}
		InterfacePtr<IIDSCDataModel> model(this, UseDefaultIID());
		ASSERT(model);				
		return model->GetChildIndexFor(parentFileNodeID->GetUID(), childFileNodeID->GetUID());			
	} while(kFalse);

	return (-1);
}


/* GetGenericNodeID
*/
NodeID_rv IDSCTreeHierAdapter::GetGenericNodeID() const
{
	return UIDNodeID::Create(kInvalidUID);
}

//	end, File: IDSCTreeHierAdapter.cpp
