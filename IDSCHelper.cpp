#include "VCPlugInHeaders.h"
#include "IDocTempFolder.h"
#include "IDFile.h"
#include "FileUtils.h"
#include "IWorkspace.h"

#include "IDSCHelper.h"

PMString IDSCHelper::m_ShortcutFilePath = kNullString;

const PMString IDSC_File_Name("idsc.idsc");

IDFile IDSCHelper::GetShortcutFilePath()
{
	InterfacePtr<IDocTempFolder> docTempFolder(
		GetExecutionContextSession()->QueryWorkspace(), UseDefaultIID());
	if(nil != docTempFolder)
	{
		IDFile folder;
		docTempFolder->GetFolder(folder);
		FileUtils::AppendPath(&folder, IDSC_File_Name);
		return folder;
	}
	return IDFile();
}


void IDSCHelper::OutputShortcutFile()
{
	IDFile shortcutFile = GetShortcutFilePath();
}