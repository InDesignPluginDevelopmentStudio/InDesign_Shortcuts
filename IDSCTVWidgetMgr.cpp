
#include "VCPlugInHeaders.h"
#include "IInterfaceFonts.h"
#include "SDKDef.h"
#include "CTreeViewWidgetMgr.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "ITreeViewHierarchyAdapter.h"
#include "UIDNodeID.h"
#include "ITextControlData.h"
#include "IWorkSpace.h"

#include "IDShortcutsID.h"
#include "IIDSCDataModel.h"
#include "IDSCTreeNode.h"


class IDSCTVWidgetMgr: public CTreeViewWidgetMgr
{
public:
	/**
		Constructor
		@param boss object on which this interface is being aggregated
	*/	
	IDSCTVWidgetMgr(IPMUnknown* boss);

	/**
		Destructor
	*/	
	virtual ~IDSCTVWidgetMgr() {}

	/** Create instance of the widget that represents given node in the tree.
		@param node [IN] specifies node of interest
		@return return reference to a newly instantiated object that is suitable for this node
	*/	
	virtual	IControlView* CreateWidgetForNode(
		const NodeID& node) const;
	/**
		Retrieve ID of a widget that has the right appearance for the node
		that you're trying to display. Here we use the same widget types for all the nodes,
		but vary the appearance by showing or hiding the expander widget depending on the number
		of children associated with a node.
		@param node [IN] specifies node of interest
		@return the ID of a widget that has the correct appearance for the given node type
	*/	
	virtual	WidgetID GetWidgetTypeForNode(const NodeID& node) const;

	/** Determine how to render the given node to the specified control.
		Figure out how you're going to render it based on properties of the node
		such as whether is has children or not (don't show expander if no children, for instance).
		@param node [IN] refers to the node that we're trying to render
		@param widget [IN] the control into which this node's appearance is going to be rendered
		@param message [IN] specifies ???
		@return kTrue if the node has been rendered successfully, kFalse otherwise
	*/	
	virtual	bool16 ApplyNodeIDToWidget(
		const NodeID& node, 
		IControlView* widget, 
		int32 message = 0) const;

	/** Given a particular node, how far should it be indented? This method
		returns a value in pixels that is used to Indent the displayed node 
		from the left edge of the tree-view control.
		@param node [IN] specifies node of interest
		@return an Indent for this particular node from the left edge of tree-view
	*/
	virtual PMReal GetIndentForNode(const NodeID& node) const;

private:
	void Indent(  const NodeID& node, IControlView* widget, 
		 IControlView* staticTextWidget ) const;
	
};	

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(IDSCTVWidgetMgr, kIDShortcutsTVWidgetMgrImpl)

/* Constructor
*/
IDSCTVWidgetMgr::IDSCTVWidgetMgr(IPMUnknown* boss) :
	CTreeViewWidgetMgr(boss)
{
	
}


/* CreateWidgetForNode
*/
IControlView* IDSCTVWidgetMgr::CreateWidgetForNode(
	const NodeID& node) const
{
	
	IControlView* retval= (IControlView*) ::CreateObject(
		::GetDataBase(this),
		RsrcSpec(LocaleSetting::GetLocale(), 
		kIDShortcutsPluginID, 
		kViewRsrcType, 
		kIDShortcutsTreeNodeWidgetRsrcID),
		IID_ICONTROLVIEW);
	return retval;
}



/* GetWidgetTypeForNode
*/
WidgetID IDSCTVWidgetMgr::GetWidgetTypeForNode(
	const NodeID& node) const
{
	return kIDShortcutsTreeNodeWidgetId;
}


/* ApplyNodeIDToWidget
*/
bool16 IDSCTVWidgetMgr::ApplyNodeIDToWidget(
	const NodeID& node, IControlView* widget, int32 message) const
{
	CTreeViewWidgetMgr::ApplyNodeIDToWidget(node, widget);
	do
	{
		// If this node doesn't have any children, don't show expander Widget
		InterfacePtr<IPanelControlData> panelControlData(widget, UseDefaultIID());
		ASSERT(panelControlData);
		if(panelControlData==nil)
		{
			ASSERT_FAIL("null panelcontroldata");
			break;
		}

		// Set expander widget to hidden state if this node has no kids
		IControlView* expanderWidget = panelControlData->FindWidget(kTreeNodeExpanderWidgetID);
				ASSERT(expanderWidget);
		if(expanderWidget == nil)
			break;

		InterfacePtr<const ITreeViewHierarchyAdapter> adapter(this, UseDefaultIID());
		ASSERT(adapter);
		if(adapter == nil)
			break;
		if ( adapter->GetNumChildren(node) > 0 )
		{
			expanderWidget->Show();
			
		}
		else
		{
			expanderWidget->Hide();
			
		}


		

		TreeNodePtr<UIDNodeID> nodeID(node);
		ASSERT(nodeID);
		if(nodeID == nil)
		{
			break;
		}
		
		IControlView* displayStringView = 
			panelControlData->FindWidget( kIDShortcutsNodeNameWidgetID );
		ASSERT(displayStringView);
		if(displayStringView == nil)
		{
			break;
		}
		InterfacePtr<ITextControlData>
			textControlData( displayStringView, UseDefaultIID() );
		ASSERT(textControlData);
		if(textControlData== nil)
		{
			break;
		}
		
	InterfacePtr<IWorkspace> workSpace(GetExecutionContextSession()->QueryWorkspace());
	ASSERT( workSpace);	
	if(nil == workSpace)
		break;

		InterfacePtr<IIDSCDataModel> iModel( workSpace, UseDefaultIID() );
		if (iModel == nil)
		{
			break;
		}

		IDSCTreeNode* pNode = iModel->GetNode(nodeID->GetUID());
		if( !pNode )
			break;
		
		PMString stringToDisplay( pNode->GetShortcuts());
		
		
		if( nodeID->GetUID() == iModel->GetRootUID() )
		{
			// Reset variable root name for XPR-16836.
			//stringToDisplay = kVDVNodeNameVariableRoot;
			//stringToDisplay.Translate();
		}
		
		
		stringToDisplay.SetTranslatable( kFalse );
		textControlData->SetString(stringToDisplay);

		// Adjust indenting- this may be temporary
		this->Indent( node, widget, displayStringView );
	} while(kFalse);

	return kTrue;
}


/* GetIndentForNode
*/
PMReal IDSCTVWidgetMgr::GetIndentForNode(const NodeID& node) const
{

	return  18.0 ;
}


/* Indent
*/
void IDSCTVWidgetMgr::Indent(
	const NodeID& node, 
	IControlView* widget, 
	IControlView* staticTextWidget	
	 ) const
{
	ASSERT(widget);
	ASSERT(staticTextWidget);
	
	
	TreeNodePtr<UIDNodeID> nodeID(node);
	ASSERT(nodeID);
	if(nodeID == nil)
		return;

	InterfacePtr<IWorkspace> workSpace(GetExecutionContextSession()->QueryWorkspace());
	ASSERT( workSpace);	
	if(nil == workSpace)
		return;

	InterfacePtr<IIDSCDataModel> iModel(workSpace, UseDefaultIID() );
	if (iModel == nil)
		return;
	
	PMReal Indent = this->GetIndent(node);	

	if(nodeID->GetUID() != iModel->GetRootUID())
		Indent+=3.0;

	// adjust the size to fit the text 
	PMRect widgetFrame = widget->GetFrame();
	widgetFrame.Left() = Indent;
	widget->SetFrame( widgetFrame );

	// Call window changed to force FittedStaticText to resize
	staticTextWidget->WindowChanged();
	PMRect staticTextFrame = staticTextWidget->GetFrame();
		
	staticTextFrame.Right( widgetFrame.Right() );
	staticTextWidget->SetFrame( staticTextFrame );
	
}
//	end, File: IDSCTVWidgetMgr.cpp
