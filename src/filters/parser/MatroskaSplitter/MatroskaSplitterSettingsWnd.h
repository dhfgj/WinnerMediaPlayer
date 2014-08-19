/*
 * (C) 2006-2014 see Authors.txt
 *
 * This file is part of WinnerMediaPlayer.
 *
 * WinnerMediaPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * WinnerMediaPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "../../filters/InternalPropertyPage.h"
#include "IMatroskaSplitter.h"
#include "resource.h"

class __declspec(uuid("1996C0A9-1F4C-4538-A6FF-ED0F591BE5D6"))
	CMatroskaSplitterSettingsWnd : public CInternalPropertyPageWnd
{
private :
	CComQIPtr<IMatroskaSplitterFilter> m_pMSF;

	CButton m_cbLoadEmbeddedFonts;

public:
	CMatroskaSplitterSettingsWnd(void);

	bool OnConnect(const CInterfaceList<IUnknown, &IID_IUnknown>& pUnks);
	void OnDisconnect();
	bool OnActivate();
	void OnDeactivate();
	bool OnApply();

	static LPCTSTR GetWindowTitle() { return MAKEINTRESOURCE(IDS_FILTER_SETTINGS_CAPTION); }
	static CSize GetWindowSize() { return CSize(300, 250); }

	DECLARE_MESSAGE_MAP()
};
