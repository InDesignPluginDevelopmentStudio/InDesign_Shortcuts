//========================================================================================
//  
//  $File: //depot/indesign_3.x/dragonfly/source/sdksamples/paneltreeview/WinFileSystemIterator.cpp $
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

#ifdef WINDOWS 
#include "WinFileSystemIterator.h"
#include "FileUtils.h"

// General includes:
#include "K2Vector.tpp"

/* SetStartingPath
*/
void WinFileSystemIterator::SetStartingPath(const UniFile&  fileSpec)
{
	fSpec = fileSpec;
	PMString temp = FileUtils::SysFileToPMString(fileSpec);
	CharCounter len = temp.CharCount();
	for(CharCounter i = len-1; i>=0; i--)
	{
		if(temp.GetChar(i) == '\\')
		{
			temp.Remove(i, len-i);	
			break;
		}
	}
	
	fPath.SetTString(temp.GrabTString());
}


/* FindFirstFile
*/
bool16 WinFileSystemIterator::FindFirstFile(UniFile&  resultFile)
{
	fFilesFound=0;
	if (fhFindFile != INVALID_HANDLE_VALUE)
	{
		::FindClose(fhFindFile);
		fhFindFile = INVALID_HANDLE_VALUE;
	}

	WIN32_FIND_DATA findData;
	fhFindFile = ::FindFirstFile(fSpec.GrabTString(), &findData);
	
	if (fhFindFile != INVALID_HANDLE_VALUE)
	{
		PMString fileName;
		fileName.SetTString((LPTSTR)&findData.cFileName);
		PMString strPath=FileUtils::SysFileToPMString(fPath);
		strPath.Append(TEXT('\\'));
		strPath += fileName ;
		resultFile.SetString( strPath );
		fFilesFound++;
	}

	return fhFindFile != INVALID_HANDLE_VALUE;
}

	
/* FindNextFile
*/
bool16 WinFileSystemIterator::FindNextFile(UniFile&  resultFile)
{
	if (fFilesFound > eMaxFolderItemsPerSingleIteration)
	{
		return kFalse;
	}

	WIN32_FIND_DATA findData;
	bool16 foundNext = ::FindNextFile(fhFindFile, &findData);		
	if (foundNext)
	{
		PMString fileName;
		fileName.SetTString(findData.cFileName);
		PMString strPath=FileUtils::SysFileToPMString(fPath);
		strPath.Append(TEXT('\\'));
		strPath += fileName;
		resultFile.SetString(strPath);
		fFilesFound++;
	}

	if(!foundNext)
	{
		::FindClose (fhFindFile);
		fhFindFile = INVALID_HANDLE_VALUE;
	}
	return foundNext;
}


/* IsDirectory
*/
bool16 WinFileSystemIterator::IsDirectory(const UniFile&  fileSpec)
{
	if (::GetFileAttributes(fileSpec.GrabTString()) & FILE_ATTRIBUTE_DIRECTORY)
	{
		return kTrue;
	}

 	return kFalse;
}
 

/* GetImmediateChildren
*/
void WinFileSystemIterator::GetImmediateChildren(
	const UniFile&  parentSysFile, 
	K2Vector<UniFile>& outFileSpecs,
	const int32 maxFolderItemsPerBulkCall){
	const PMString dot(".");
	const PMString doubleDot("..");
	
	outFileSpecs.clear();

	do
	{

		WIN32_FIND_DATA findData;
		PMString filter=FileUtils::SysFileToPMString(parentSysFile);
		filter += "\\*.*";
		HANDLE hSearch = ::FindFirstFile(filter.GrabTString(), &findData); 
		if (hSearch == INVALID_HANDLE_VALUE)
		{ 
			break;
		} 
 
		bool16 hasNext =kTrue;
		int32 filesFound=0;
		while (hasNext && filesFound < maxFolderItemsPerBulkCall) 
		{ 
			
			UniFile resultFile;
			PMString fileName;
			fileName.SetTString(findData.cFileName);
			if(fileName != dot && fileName != doubleDot)
			{
				PMString strPath=FileUtils::SysFileToPMString(parentSysFile);
				strPath.Append(TEXT('\\'));
				strPath += fileName ;
				resultFile.SetString(strPath);
				outFileSpecs.push_back(resultFile);
				filesFound++;
			}
 
			hasNext = ::FindNextFile(hSearch, &findData);
		} 
 
		// Close the search handle. 
		::FindClose(hSearch);

	} while(kFalse);
}

#endif

//	end, File: WinFileSystemIterator.cpp
