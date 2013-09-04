
#ifndef __IIDSHORTCUTSDATAMODEL_H_DEFINED__
#define __IIDSHORTCUTSDATAMODEL_H_DEFINED__

#include "IPMUnknown.h"
#include "IDShortcutsID.h"
#include "IDSCTreeNode.h"

class IIDSCDataModel : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIDSHORTCUTSDATAMODEL };

	virtual UID GetRootUID() const = 0;
	virtual UID GetParentUID(UID uid) const = 0;

	virtual int32 GetChildCount(UID uid) const = 0; 
	virtual UID GetNthChildUID(UID uid, int32 nth) const = 0; 


};

#endif // __IIDSHORTCUTSDATAMODEL_H_DEFINED__

