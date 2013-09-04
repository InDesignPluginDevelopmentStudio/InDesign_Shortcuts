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
	virtual UID GetRootUID() const;
	virtual UID GetParentUID(UID uid) const;
	virtual int32 GetChildCount(const PMString& path) const ; 
	virtual UID GetNthChildUID(UID uid, int32 nth) const; 

	virtual PMString GetRootPath() const;
	virtual IDSCTreeNode* GetNode(const PMString& path) const;
	virtual PMString GetParentPath(const PMString& path) const;
	virtual int32 GetChildIndexFor(const PMString& par, const PMString& kid); 
	virtual void Rebuild(const PMString& rootPath);

protected:
	bool compareByUID(const IDSCTreeNode& lh, const IDSCTreeNode& rh);

	bool16 validPath(const PMString& p);
	void deleteTree() ;

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
}

IDSCDataModel::~IDSCDataModel()
{
	deleteTree();
}

void IDSCDataModel::deleteTree() 
{
	// We've flattened the tree in our hashtable anyway so 
	// use this to delete the nodes.
	std::map<PMString, IDSCTreeNode* >::iterator iter;
	for(iter = _nodeMap.begin(); iter != _nodeMap.end(); iter++)
	{
		IDSCTreeNode* node = iter->second;
		ASSERT(node);
		delete node;
	}
	_nodeMap.clear();
	_pRootNode = nil;
}

UID IDSCDataModel::GetRootUID() const
{
	if(nil == _pRootNode)
		_pRootNode = new IDSCTreeNode();

	if(nil != _pRootNode)
		return _pRootNode->GetUID();

	return kInvalidUID;
}

bool IDSCDataModel::compareByUID(const IDSCTreeNode& lh, const IDSCTreeNode& rh)
{
	return (lh.GetUID() < rh.GetUID());
}

UID IDSCDataModel::GetParentUID(UID uid) const
{
	if(uid == GetRootUID())
		return kInvalidUID;
	
	NodeMap::const_iterator iter = _nodeMap.find(uid);
	if(iter == _nodeMap.end())
		return kInvalidUID;

	return iter->second->GetParentUID();
}

void IDSCDataModel::Rebuild(const PMString& path)
{
	if(_pRootNode != nil) {
		deleteTree();
	}
	if(path.empty() == kFalse) {
		_pRootNode =  new IDSCTreeNode();
		_pRootNode->SetData(path);
		_nodeMap.insert( std::pair<PMString, IDSCTreeNode* >(path, _pRootNode));
		this->cacheChildren(path);
	}

}

PMString  IDSCDataModel::GetParentPath(const PMString& path) const
{
	// We assume that the parent is cached, because we
	// found its kids
	std::map<PMString, IDSCTreeNode* >::const_iterator result = _nodeMap.find(path);
	if(result != _nodeMap.end())
	{
		IDSCTreeNode* node = result->second;
		ASSERT(node);
		ASSERT(_pRootNode);
		// Use the comparison we've defined on the node class
		if((*node) == (*_pRootNode))
		{
			return PMString();
		}
		return node->GetParent()->GetData();
	}
	return PMString();
}

int32 IDSCDataModel::GetChildCount(const PMString& path) const
{
	NodeMap::const_iterator result = _nodeMap.find(path);
	if(result != _nodeMap.end()) {
		int32 possChildCount = result->second->ChildCount();
		return possChildCount;
	}

	return 0;
}

UID IDSCDataModel::GetNthChildUID(
	UID uid, int32 nth) const
{
	NodeMap::const_iterator result = _nodeMap.find(path);
	if(result != _nodeMap.end()) {
		IDSCTreeNode* pNode = result->second->GetNthChild(nth);
		if (nil != pNode)
			return pNode->GetUID();
	}
	return kInvalidUID;
}

int32  IDSCDataModel::GetChildIndexFor(
	const PMString& par, const PMString& kid) //const
{
	// Can we be called here without the kids being already cached?
	int32 retval=(-1);
	std::map<PMString, IDSCTreeNode* >::const_iterator result = _nodeMap.find(par);
	if(result != _nodeMap.end()) {
		IDSCTreeNode* node = result->second;
		if(node->ChildCount() == 0) {
			// Try to cache the kids, we may not have done so
			this->cacheChildren(par);
		}
		for(int32 i=0; i < node->ChildCount(); i++){
			PMString kidPath = node->GetNthChild(i).GetData();
			if(kid == kidPath) {
				retval=i;
				break;
			}
		}
	}
	
	return retval;
}


PMString IDSCDataModel::GetRootPath() const
{
	if(_pRootNode != nil)
	{
		return _pRootNode->GetData();
	}
	return PMString();
}

IDSCTreeNode* IDSCDataModel::GetNode(const PMString& path) const
{
	IDSCTreeNode* retval = nil;

	std::map<PMString, IDSCTreeNode* >::const_iterator result = _nodeMap.find(path);
	if(result != _nodeMap.end()) {
		retval = result->second;
	}
	return retval;
}

bool16 IDSCDataModel::validPath(const PMString& p)
{
	const PMString thisDir(".");
	const PMString parentDir("..");
	return p != thisDir && p != parentDir;
}

