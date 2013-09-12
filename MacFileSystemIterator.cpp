//========================================================================================
//  
//  $File: //depot/indesign_3.x/dragonfly/source/sdksamples/paneltreeview/MacFileSystemIterator.cpp $
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

#include "VCPluginHeaders.h"
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
void MacFileSystemIterator::SetStartingPath(const UniFile&  fileSpec)
{
#ifdef INDESIGNCS5_5
	FileUtils::IDFileToFSSpec(fileSpec, fStartingFile);
#else
	FileUtils::IDFileToFSRef(fileSpec, fStartingFile);
#endif
}

/*
*/
bool16 MacFileSystemIterator :: FindFirstFile(UniFile&  resultFile)
{
	do {	
		FSRef folderRef;
#ifdef INDESIGNCS5_5
	  	OSErr specToRefErr = FSpMakeFSRef( &fStartingFile, &folderRef );
	     	ASSERT(specToRefErr == noErr);
		if(specToRefErr != noErr) {
			break;
		}
#else
		folderRef = fStartingFile;
#endif
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
bool16 MacFileSystemIterator :: FindNextFile(UniFile&  resultFile)
{
	bool16 itemsLeftToIterate = kFalse;
	do {
		FSCatalogInfoBitmap     whichInfo =	 kFSCatInfoNodeFlags |   kFSCatInfoFinderInfo; 
		const int kFolderItemsPerBulkCall = 1;
		FSCatalogInfo*  foundCatInfos = new FSCatalogInfo [kFolderItemsPerBulkCall];		
		FSRef*		  foundFSRefs = new FSRef [kFolderItemsPerBulkCall];			
		HFSUniStr255*   foundNames = new HFSUniStr255[kFolderItemsPerBulkCall];			
		FSSpec*		  fileSpecs = new FSSpec[kFolderItemsPerBulkCall];			
	
  		 ItemCount   foundItems;      
		OSErr err = FSGetCatalogInfoBulk(fFSIterator, 
								kFolderItemsPerBulkCall,
								&foundItems, nil,
								kFSCatInfoGettableInfo,
								foundCatInfos, 
								foundFSRefs, 
								fileSpecs, 
								foundNames);
		if (err == errFSNoMoreItems) {
			err = noErr;
			itemsLeftToIterate = kFalse;
		} else if(err == noErr) {
			itemsLeftToIterate = kTrue;
		}
		
		if(err == noErr &&  foundItems > 0) {
			ASSERT(foundItems == kFolderItemsPerBulkCall);

			FileUtils::FSSpecToIDFile(fileSpecs[0], resultFile);

		}
		
		delete [] foundCatInfos;
		delete [] foundFSRefs;
		delete [] foundNames;
		delete [] fileSpecs;
	} while(kFalse);
	
	// Release resources used by this iterator when we're at end
	if(!itemsLeftToIterate) {
		FSCloseIterator(fFSIterator);
	}
	return itemsLeftToIterate;


}

 bool16 MacFileSystemIterator ::  IsDirectory(const UniFile&  fileSpec)
 {
	 return fileSpec.GetAttribute(IDFile::kDirectory);
 }
 
 /*
 Written to allow a little more visibility into what the platform iterator methods are really doing
 	and provide for a bit more testing confidence.
 */
void MacFileSystemIterator :: GetImmediateChildren(const UniFile&  parentSysFile, 
										K2Vector<UniFile>& outFileSpecs,
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
		FSSpec*		  fileSpecs = new FSSpec[maxFolderItemsPerBulkCall];			
	
  		 ItemCount   foundItems;      
		OSErr err = FSGetCatalogInfoBulk(fsIterator, 
								maxFolderItemsPerBulkCall,
								&foundItems, nil,
								kFSCatInfoGettableInfo,
								foundCatInfos, 
								foundFSRefs, 
								fileSpecs, 
								foundNames);
		if (err == errFSNoMoreItems) {
			err = noErr;
		} 
		
		if(err == noErr &&  foundItems > 0) {

			IDFile tmpFile;
			for(int32 i=0; i < foundItems; i++) {
				err = FileUtils::FSSpecToIDFile(fileSpecs[i], tmpFile);
				if(err == noErr)
					outFileSpecs.push_back(tmpFile);
			}

		}
		
		delete [] foundCatInfos;
		delete [] foundFSRefs;
		delete [] foundNames;
		delete [] fileSpecs;
		OSErr junk = FSCloseIterator(fsIterator);

	} while(kFalse);
}



#endif
