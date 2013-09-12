#include "VCPlugInHeaders.h"

#include "IDSCTreeNode.h"

UID IDSCTreeNode::S_Node_UID = UID(1);


IDSCTreeNode::IDSCTreeNode():
	 TreeNodeBase<IDSCTreeNode>(),
	 _nodeType(E_None),
	 _shortcuts(kNullString)
{
}

//IDSCTreeNode::IDSCTreeNode(const PMString& name, 
//						EType type, 
//						UID parentUID, 
//						const PMString& shortcuts)
//{
//	this->SetUID(S_Node_UID++);
//	this->SetName(name);
//	this->SetType(type);
//	this->SetParent(parentUID);
//	this->SetShortcuts(shortcuts);
//}

void IDSCTreeNode::SetShortcuts(const PMString& shortcuts)
{
	this->_shortcuts = shortcuts;
}

PMString IDSCTreeNode::GetShortcuts() const
{
	return this->_shortcuts;
}

Bool16 IDSCTreeNode::HasShortcuts() const
{
	return !(GetShortcuts().IsEmpty());
}

/************************Begin Private Functions*******************************/


void IDSCTreeNode::DeepCopy(const IDSCTreeNode& node)
{
	this->SetUID(S_Node_UID++);
	this->SetName(node.GetName());
	this->SetParent(node.GetParent());
	this->SetShortcuts(node.GetShortcuts());
	this->SetType(node.GetType());
}
/************************End Private Functions*******************************/