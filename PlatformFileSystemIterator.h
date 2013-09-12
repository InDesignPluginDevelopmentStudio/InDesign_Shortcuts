//========================================================================================
//  
//  $File: //depot/indesign_3.x/dragonfly/source/sdksamples/paneltreeview/PlatformFileSystemIterator.h $
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
//  
//  Purpose:
//  
//========================================================================================

#ifndef __PlatformFileSystemIterator_H_DEFINED__
#define __PlatformFileSystemIterator_H_DEFINED__



#ifdef WINDOWS
#include "WinFileSystemIterator.h"
#define PlatformFileSystemIterator WinFileSystemIterator
#endif
#ifdef MACINTOSH
#include "MacFileSystemIterator.h"
#define PlatformFileSystemIterator MacFileSystemIterator
#endif


#endif

