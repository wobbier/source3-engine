/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HCT_FILTER_DIALOG_UTILS_H
#define HCT_FILTER_DIALOG_UTILS_H

#include <ContentTools/Common/SceneExport/Error/hctSceneExportError.h> 

// This functions is used by filter Dialogs to display ToolTips
BOOL CreateToolTip(int toolID, HWND hDlg, HINSTANCE hInst, hkStringOld toolText);

// This function will print (incl. formatting) the LogEntry to the provided RichEdit control.
void hctPrintLogEntryToRichEditControl(const hctSceneExportError::LogEntry& entry, HWND richEditControl);

// This function will return the value in the specified dialog item as a float
float hctGetDlgItemFloat(__in HWND hDlg, __in int nIDDlgItem);

// This function will return the value in the specified dialog item as a int
int hctGetDlgItemInt(__in HWND hDlg, __in int nIDDlgItem);

// This function will return true if any characters were copied successfully, storing the result in a hkStringPtr
bool hctGetDlgItemHkStringPtr(__in HWND hDlg, __in int nIDDlgItem, hkStringPtr& text);

// This function will return true if any characters were copied successfully, storing the result in a hkStringPtr
bool hctGetWindowHkStringPtr(__in HWND hWnd, hkStringPtr& text);

#endif	// HCT_FILTER_DIALOG_UTILS_H

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20140907)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2014
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
