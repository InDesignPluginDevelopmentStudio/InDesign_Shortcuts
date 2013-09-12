#ifndef __IDSHORTCUTSTREENODE_H_DEFINED__
#define __IDSHORTCUTSTREENODE_H_DEFINED__

#include <OMTypes.h>
#include "TreeNodeBase.h"

class IDSCTreeNode : public TreeNodeBase<IDSCTreeNode>
{
public:
	enum EType{E_None = -1, E_Root, E_ProductArea, E_Menu};

	IDSCTreeNode();
//	IDSCTreeNode(const PMString& name, EType type, UID parentUID, const PMString& shortcuts = kNullString);

	void SetType(EType type) { _nodeType = type; }
	EType GetType() const { return _nodeType; }


	void SetShortcuts(const PMString& shortcuts);
	PMString GetShortcuts() const;

	Bool16 HasShortcuts() const;

private:
	void DeepCopy(const IDSCTreeNode& node);

/// members
	static UID S_Node_UID;
	EType _nodeType;

	PMString _shortcuts;

};
#endif