//========================================================================================
//  
//  $File: //depot/indesign_8.0/gm/source/sdksamples/paneltreeview/MacFileSystemIterator.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: alokumar $
//  
//  $DateTime: 2012/02/15 11:23:10 $
//  
//  $Revision: #1 $
//  
//  $Change: 817912 $
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
#ifdef MACINTOSH
#include "MacFileSystemIterator.h"
#include "K2Vector.tpp"
#include "FileUtils.h"
#include "MacFileUtils.h"

// See http://developer.apple.com/techpubs/macosx/Carbon/Files/FileManager/File_Manager/index.html
// and http://developer.apple.com/techpubs/macosx/Carbon/Files/FileManager/File_Manager/Functions/Searching_a__log_Iterator.html

// For the bitmaps:
// http://developer.apple.com/techpubs/macosx/Carbon/Files/FileManager/File_Manager/Enumerations/Catalog_Info_ap_Constants.html

MacFileSystemIterator::MacFileSystemIterator()
{
}

MacFileSystemIterator::~MacFileSystemIterator()
{
}

/*
*/
void MacFileSystemIterator::SetStartingPath(const IDFile& fileSpec)
{
	FileUtils::IDFileToFSRef(fileSpec, fStartingFileRef);
}

/*
*/
bool16 MacFileSystemIterator :: FindFirstFile(IDFile& resultFile, PMString filter)
{
	do {	
		FSRef folderRef = fStartingFileRef;
	  	
		OSErr startIterErr = FSOpenIterator (
		    	&folderRef,
		  	kFSIterateFlat,
		  	 &fFSIterator
		);
		if(startIterErr != noErr) {
			break;
		}
		return this->FindNextFile(resultFile);
 	} while(kFalse);
	return kFalse;
}
	
/*
*/
bool16 MacFileSystemIterator :: FindNextFile(IDFile& resultFile)
{
	bool16 itemsLeftToIterate = kFalse;
	do {
		FSCatalogInfoBitmap     whichInfo =	 kFSCatInfoNodeFlags |   kFSCatInfoFinderInfo; 
		const int kFolderItemsPerBulkCall = 1;
		FSCatalogInfo*  foundCatInfos = new FSCatalogInfo [kFolderItemsPerBulkCall];		
		FSRef*		  foundFSRefs = new FSRef [kFolderItemsPerBulkCall];			
		HFSUniStr255*   foundNames = new HFSUniStr255[kFolderItemsPerBulkCall];			
		//FSSpec*		  fileSpecs = new FSSpec[kFolderItemsPerBulkCall];			
	
  		 ItemCount   foundItems;      
		OSErr err = FSGetCatalogInfoBulk(fFSIterator, 
								kFolderItemsPerBulkCall,
								&foundItems, nil,
								kFSCatInfoGettableInfo,
								foundCatInfos, 
								foundFSRefs, 
								NULL, 
								foundNames);
		if (err == errFSNoMoreItems) {
			err = noErr;
			itemsLeftToIterate = kFalse;
		} else if(err == noErr) {
			itemsLeftToIterate = kTrue;
		}
		
		if(err == noErr &&  foundItems > 0) {
			ASSERT(foundItems == kFolderItemsPerBulkCall);
			MacFileUtils::FSRefToAFile(foundFSRefs[0], resultFile);
		}
		
		delete [] foundCatInfos;
		delete [] foundFSRefs;
		delete [] foundNames;
		//delete [] fileSpecs;
	} while(kFalse);
	
	// Release resources used by this iterator when we're at end
	if(!itemsLeftToIterate) {
		FSCloseIterator(fFSIterator);
	}
	return itemsLeftToIterate;


}

 bool16 MacFileSystemIterator ::  IsDirectory(const IDFile& fileSpec)
 {
	return fileSpec.GetAttribute(IDFile::kDirectory);
 }
 
 /*
 Written to allow a little more visibility into what the platform iterator methods are really doing
 	and provide for a bit more testing confidence.
 */
void MacFileSystemIterator :: GetImmediateChildren(const IDFile& parentSysFile, 
										K2Vector<IDFile>& outFileSpecs,
										const int32 maxFolderItemsPerBulkCall )
{
	do {
		outFileSpecs.clear();
		FSRef folderRef;
		OSErr specToRefErr = MacFileUtils::AFileToFSRef(parentSysFile, folderRef);
	     	ASSERT(specToRefErr == noErr);
		if(specToRefErr != noErr) {
			break;
		}
		FSIterator fsIterator;
		OSErr startIterErr = FSOpenIterator (
		    	&folderRef,
		  	kFSIterateFlat,
		  	 &fsIterator
		);
		if(startIterErr != noErr) {
			break;
		}
		FSCatalogInfoBitmap     whichInfo =	 kFSCatInfoNodeFlags |   kFSCatInfoFinderInfo; 
		FSCatalogInfo*  foundCatInfos = new FSCatalogInfo [maxFolderItemsPerBulkCall];		
		FSRef*		  foundFSRefs = new FSRef [maxFolderItemsPerBulkCall];			
		HFSUniStr255*   foundNames = new HFSUniStr255[maxFolderItemsPerBulkCall];			
	
  		 ItemCount   foundItems;      
		OSErr err = FSGetCatalogInfoBulk(fsIterator, 
								maxFolderItemsPerBulkCall,
								&foundItems, nil,
								kFSCatInfoGettableInfo,
								foundCatInfos, 
								foundFSRefs, 
								NULL, 
								foundNames);
		if (err == errFSNoMoreItems) {
			err = noErr;
		} 
		
		if(err == noErr &&  foundItems > 0) {
			IDFile tmpFile;
			for(int32 i=0; i < foundItems; i++) {
				err = MacFileUtils::FSRefToAFile(foundFSRefs[i], tmpFile);
				if (err == noErr) {
					outFileSpecs.push_back(tmpFile);
				}
			}
		}
		
		delete [] foundCatInfos;
		delete [] foundFSRefs;
		delete [] foundNames;
		OSErr junk = FSCloseIterator(fsIterator);

	} while(kFalse);
}



#endif
