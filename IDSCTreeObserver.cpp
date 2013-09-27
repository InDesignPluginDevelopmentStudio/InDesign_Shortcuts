
#include "VCPlugInHeaders.h"

// Interface includes
#include "ISubject.h"
#include "ITreeViewMgr.h"

// General includes
#include "CObserver.h"
#include "K2Vector.tpp" // For NodeIDList to compile

#include "IIDSCDataModel.h"

class IDSCTreeObserver : public CObserver
{
public:
	/**
	Constructor for WLBListBoxObserver class.
	@param interface ptr from boss object on which this interface is aggregated.
	*/
	IDSCTreeObserver(IPMUnknown* boss);

	/**
	Destructor 
	*/	
	~IDSCTreeObserver();

	/**
	AutoAttach is only called for registered observers
	of widgets.  This method is called by the application
	core when the widget is shown.
	*/	
	virtual void AutoAttach();

	/**
	AutoDetach is only called for registered observers
	of widgets. Called when widget hidden.
	*/	
	virtual void AutoDetach();

	/**
	Update is called for all registered observers, and is
	the method through which changes are broadcast. 
	@param theChange [IN] this is specified by the agent of change; it can be the class ID of the agent,
	or it may be some specialised message ID.
	@param theSubject [IN] provides a reference to the object which has changed; in this case, the button
	widget boss object that is being observed.
	@param protocol [IN] the protocol along which the change occurred.
	@param changedBy [IN] this can be used to provide additional information about the change or a reference
	to the boss object that caused the change.
	*/	
	virtual void Update(
		const ClassID& theChange, 
		ISubject* theSubject, 
		const PMIID &protocol, 
		void* changedBy);

	virtual void LazyUpdate( 
		ISubject *  theSubject,  
		const PMIID &  protocol,  
		const LazyNotificationData *  data); 

protected:

	/**	Handles a change in the selection when the end user 
	either clicks on a node or clicks off it
	*/
	void handleSelectionChanged();

	/**	Sets the path on the preview widget and invalidates it
	@param path [IN] specifies the path to the asset in 
	the local file system
	*/
	void doPreview(const PMString& path);

	/**	Populates the tree model. 
	*/
	void initTree();

};

/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE( IDSCTreeObserver, kIDShortcutsTreeObserverImpl)


/* Constructor
*/
IDSCTreeObserver::IDSCTreeObserver(IPMUnknown* boss)
: CObserver(boss)
{
}


/* Destructor
*/
IDSCTreeObserver::~IDSCTreeObserver()
{
}


/* AutoAttach
*/
void IDSCTreeObserver::AutoAttach()
{
	// Show/refresh tree when widget made visible
	initTree();
	InterfacePtr<ISubject> subj(this, UseDefaultIID()); 
	ASSERT(subj);
	subj->AttachObserver(this, IID_ITREEVIEWCONTROLLER);
	
}


/* AutoDetach
*/
void IDSCTreeObserver::AutoDetach()
{
	InterfacePtr<ISubject> subj(this, UseDefaultIID()); 
	ASSERT(subj);
	subj->DetachObserver(this, IID_ITREEVIEWCONTROLLER);

}


/* Update
*/
void IDSCTreeObserver::Update(
								const ClassID& theChange, 
								ISubject* theSubject, 
								const PMIID &protocol, 
								void* changedBy)
{
	switch(theChange.Get())
	{
	case kListSelectionChangedMessage:
		{
			this->handleSelectionChanged();
			break;
		}
	
	}
}

void IDSCTreeObserver::LazyUpdate(ISubject *  theSubject,  
						const PMIID &  protocol,  
						const LazyNotificationData *  data)
{

}


/* initTree
*/
void IDSCTreeObserver::initTree()
{
	do
	{
		InterfacePtr<ITreeViewMgr> treeViewMgr(this, UseDefaultIID());
		ASSERT(treeViewMgr);
		if(treeViewMgr == nil)
		{
			break;
		}
	
		treeViewMgr->ClearTree();
		treeViewMgr->ChangeRoot(kTrue);
	} while(kFalse);
}


/* handleSelectionChanged
*/
void IDSCTreeObserver::handleSelectionChanged()
{
	
}


/* doPreview
*/
void IDSCTreeObserver::doPreview(const PMString& path)
{
	
}

//	end, File: IDSCTreeObserver.cpp
