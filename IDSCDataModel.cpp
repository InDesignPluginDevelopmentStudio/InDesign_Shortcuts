#include "VCPlugInHeaders.h"

// Interface includes

// Impl includes
#include <map>
#include <algorithm>
#include "SDKFileHelper.h"
// Project includes
#include "IIDSCDataModel.h"
#include "PlatformFileSystemIterator.h"


class IDSCDataModel : CPMUnknown<IIDSCDataModel>
{
public:
	IDSCDataModel(IPMUnknown* boss);
	virtual ~IDSCDataModel();
	virtual UID GetRootUID() const ;
	virtual UID GetParentUID(UID uid) const;
	virtual int32 GetChildCount(UID uid) const ; 
	virtual UID GetNthChildUID(UID uid, int32 nth) const; 
	virtual int32 GetChildIndexFor(UID parent, UID child) const; 

	virtual IDSCTreeNode* GetNode(UID uid) const;

protected:
	bool compareByUID(const IDSCTreeNode& lh, const IDSCTreeNode& rh);

	bool16 validPath(const PMString& p);

private:
	typedef std::map<UID, IDSCTreeNode*> NodeMap;
	
	NodeMap _nodeMap;
	PMString _shortcutSetName;
	IDSCTreeNode* _pRootNode;
};

CREATE_PMINTERFACE(IDSCDataModel, kIDSCDataModelImpl)


IDSCDataModel::IDSCDataModel(IPMUnknown* boss) : 
	CPMUnknown<IIDSCDataModel>(boss),
	_pRootNode(nil)
{
	_pRootNode = new IDSCTreeNode();
}

IDSCDataModel::~IDSCDataModel()
{
}

UID IDSCDataModel::GetRootUID()  const
{
	return (nil != _pRootNode) ? _pRootNode->GetUID() : kInvalidUID;
}

bool IDSCDataModel::compareByUID(const IDSCTreeNode& lh, const IDSCTreeNode& rh)
{
	return (lh.GetUID() < rh.GetUID());
}

UID IDSCDataModel::GetParentUID(UID uid)  const
{
	if(uid == GetRootUID())
		return kInvalidUID;
	
	NodeMap::const_iterator iter = _nodeMap.find(uid);
	if(iter == _nodeMap.end())
		return kInvalidUID;

	return iter->second->GetParentUID();
}

int32 IDSCDataModel::GetChildCount(UID uid) const  
{
	NodeMap::const_iterator result = _nodeMap.find(uid);
	if(result != _nodeMap.end()) {
		return result->second->ChildCount();
	}
	return 0;
}

UID IDSCDataModel::GetNthChildUID(
	UID uid, int32 nth) const
{
	NodeMap::const_iterator result = _nodeMap.find(uid);
	if(result != _nodeMap.end()) {
		IDSCTreeNode* pNode = result->second->GetNthChild(nth);
		if (nil != pNode)
			return pNode->GetUID();
	}
	return kInvalidUID;
}

int32  IDSCDataModel::GetChildIndexFor( UID parent, UID child ) const
{
	int32 retval=(-1);
	std::map<UID, IDSCTreeNode* >::const_iterator result = _nodeMap.find(parent);
	if(result != _nodeMap.end()) {
		IDSCTreeNode* node = result->second;
		for(int32 i = 0; i < node->ChildCount(); i++) {
			IDSCTreeNode* pChild = node->GetNthChild(i);
			if(nil != pChild && child == pChild->GetUID()) {
				retval = i;
				break;
			}
		}
	}
	
	return retval;
}



IDSCTreeNode* IDSCDataModel::GetNode(UID uid) const
{
	IDSCTreeNode* retval = nil;

	std::map<UID, IDSCTreeNode* >::const_iterator result = _nodeMap.find(uid);
	if(result != _nodeMap.end()) {
		retval = result->second;
	}
	return retval;
}
