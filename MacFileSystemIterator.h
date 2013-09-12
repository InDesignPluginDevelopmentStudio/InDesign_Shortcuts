//========================================================================================
//  
//  $File: //depot/indesign_3.x/dragonfly/source/sdksamples/paneltreeview/MacFileSystemIterator.h $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: Jsun $
//  
//  $DateTime: 2003/12/18 11:20:39 $
//  
//  $Revision: 2 $
//  
//  $Change: 237988 $
//  
//  Copyright 1997-2003 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __PnlTrvMacDirIterator_H_DEFINED__
#define __PnlTrvMacDirIterator_H_DEFINED__
#include "FileSystemIterator.h"

/** Macintosh specific class to iterate a folder's descendants.
@ingroup paneltreeview
 */
class MacFileSystemIterator : public FileSystemIterator {
public:
	MacFileSystemIterator();
	~MacFileSystemIterator();

	/**	Initialise the iterator with a starting folder

		@param fileSpec specifies the folder whose immediate dependents we're interested in
	 */
	virtual void SetStartingPath(const UniFile&  fileSpec);

	/**	Find the first file given the starting folder, if there is one.
		If the start file isn't a folder then this will return kFalse.

		@param resultFile [OUT] parameter
		@return bool16 kTrue if there is a first file, kFalse otherwise
	 */
	virtual bool16 FindFirstFile(UniFile&  resultFile);		

	/**	Find next file in iteration (doesn't descend into child folders).
		Will return kFalse if there is no next file given the current iteration state.

		@param resultFile [OUT] parameter
		@return bool16 kTrue if a file could be found, kFalse otherwise
	 */
	virtual bool16 FindNextFile(UniFile&  resultFile);
	
	/** Determine if specified file is a directory
		@return kTrue if directory, kFalse otherwise
	*/
	virtual bool16 IsDirectory(const UniFile&  fileSpec);
	

	/** Obtain list of files that are immediate descendants of the given parent
		Vector will be cleared and empty if no children exist.
		Otherwise on return it will contain the children of the specified folder.

		@param parentSysFile specifies the file whose immediate dependents we want
		@param outFileSpecs [OUT] holds the children of the specified folder
		@param maxFolderItemsPerBulkCall constrains the max number of items that might be returned. 

	*/		virtual void GetImmediateChildren(const UniFile&  parentSysFile, 
										K2Vector<UniFile>& outFileSpecs,
										const int32 maxFolderItemsPerBulkCall=256 );


protected:
	bool16 areEqual(const UniFile&  file1, const UniFile&  file2);
	
private:
#ifdef MACINTOSH 
  #ifdef INDESIGNCS5_5
	FSSpec fStartingFile;
  #else
    FSRef fStartingFile;
  #endif 
	FSIterator fFSIterator;
#endif // MACINTOSH
};


#endif
