#ifndef __IDSHORTCUTHELPER_H_DEFINED__
#define __IDSHORTCUTHELPER_H_DEFINED__

#include "IDFile.h"
#include "PMString.h"

class IDSCHelper 
{
public:
	static IDFile GetShortcutFilePath();
	static void OutputShortcutFile();

private:
	static PMString m_ShortcutFilePath;

};
#endif