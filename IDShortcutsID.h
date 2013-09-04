//========================================================================================
//  
//  $File: $
//  
//  Owner: James.dd.Sun
//  
//  $Author: $
//  
//  $DateTime: $
//  
//  $Revision: $
//  
//  $Change: $
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================


#ifndef __IDShortcutsID_h__
#define __IDShortcutsID_h__

#include "SDKDef.h"

// Company:
#define kIDShortcutsCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kIDShortcutsCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kIDShortcutsPluginName	"InDesignShortcutsList"			// Name of this plug-in.
#define kIDShortcutsPrefixNumber	0xe9400 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kIDShortcutsVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kIDShortcutsAuthor		"James.dd.Sun"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kIDShortcutsPrefixNumber above to modify the prefix.)
#define kIDShortcutsPrefix		RezLong(kIDShortcutsPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kIDShortcutsStringPrefix	SDK_DEF_STRINGIZE(kIDShortcutsPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kIDShortcutsMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kIDShortcutsMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kIDShortcutsPluginID, kIDShortcutsPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kIDShortcutsActionComponentBoss, kIDShortcutsPrefix + 0)
DECLARE_PMID(kClassIDSpace, kIDShortcutsPanelWidgetBoss, kIDShortcutsPrefix + 1)
DECLARE_PMID(kClassIDSpace, kIDShortcutsTreeViewWidgetBoss, kIDShortcutsPrefix + 3)
DECLARE_PMID(kClassIDSpace, kIDShortcutsTreeNodeWidgetBoss, kIDShortcutsPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kIDShortcutsBoss, kIDShortcutsPrefix + 25)


// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSDATAMODEL, kIDShortcutsPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_IIDSHORTCUTSINTERFACE, kIDShortcutsPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kIDShortcutsActionComponentImpl, kIDShortcutsPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kIDShortcutsTVWidgetMgrImpl, kIDShortcutsPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kIDShortcutsTreeObserverImpl, kIDShortcutsPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kIDShortcutsTVHierarchyAdapterImpl, kIDShortcutsPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kIDShortcutsDataModelImpl, kIDShortcutsPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kIDShortcutsImpl, kIDShortcutsPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kIDShortcutsAboutActionID, kIDShortcutsPrefix + 0)
DECLARE_PMID(kActionIDSpace, kIDShortcutsPanelWidgetActionID, kIDShortcutsPrefix + 1)
DECLARE_PMID(kActionIDSpace, kIDShortcutsSeparator1ActionID, kIDShortcutsPrefix + 2)
DECLARE_PMID(kActionIDSpace, kIDShortcutsPopupAboutThisActionID, kIDShortcutsPrefix + 3)//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kIDShortcutsActionID, kIDShortcutsPrefix + 25)


// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kIDShortcutsPanelWidgetID, kIDShortcutsPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kIDSCSearchEditBoxWidgetID, kIDShortcutsPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kIDShortcutsTreeViewWidgetID, kIDShortcutsPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kIDShortcutsTreeNodeWidgetId, kIDShortcutsPrefix + 5)
DECLARE_PMID(kWidgetIDSpace, kIDShortcutsNodePanelWidgetID, kIDShortcutsPrefix + 6)
DECLARE_PMID(kWidgetIDSpace, kIDShortcutsNodeNameWidgetID, kIDShortcutsPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kIDShortcutsWidgetID, kIDShortcutsPrefix + 25)


// "About Plug-ins" sub-menu:
#define kIDShortcutsAboutMenuKey			kIDShortcutsStringPrefix "kIDShortcutsAboutMenuKey"
#define kIDShortcutsAboutMenuPath		kSDKDefStandardAboutMenuPath kIDShortcutsCompanyKey

// "Plug-ins" sub-menu:
#define kIDShortcutsPluginsMenuKey 		kIDShortcutsStringPrefix "kIDShortcutsPluginsMenuKey"
#define kIDShortcutsPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kIDShortcutsCompanyKey kSDKDefDelimitMenuPath kIDShortcutsPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kIDShortcutsAboutBoxStringKey	kIDShortcutsStringPrefix "kIDShortcutsAboutBoxStringKey"
#define kIDShortcutsPanelTitleKey					kIDShortcutsStringPrefix	"kIDShortcutsPanelTitleKey"
#define kIDShortcutsStaticTextKey kIDShortcutsStringPrefix	"kIDShortcutsStaticTextKey"
#define kIDShortcutsInternalPopupMenuNameKey kIDShortcutsStringPrefix	"kIDShortcutsInternalPopupMenuNameKey"
#define kIDShortcutsTargetMenuPath kIDShortcutsInternalPopupMenuNameKey
#define kIDShortcutsSearchTextKey kIDShortcutsStringPrefix "kIDShortcutsSearchTextKey"

#define	kIDShortcutsSeparator1MenuItemPosition		10.0
#define kIDShortcutsAboutThisMenuItemPosition		11.0


// Initial data format version numbers
#define kIDShortcutsFirstMajorFormatNumber  RezLong(1)
#define kIDShortcutsFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kIDShortcutsCurrentMajorFormatNumber kIDShortcutsFirstMajorFormatNumber
#define kIDShortcutsCurrentMinorFormatNumber kIDShortcutsFirstMinorFormatNumber

#define kIDShortcutsListNodeItemRsrcID	 1000
#define kIDShortcutsTreeNodeWidgetRsrcID 1001
#endif // __IDShortcutsID_h__

//  Code generated by DollyXs code generator
