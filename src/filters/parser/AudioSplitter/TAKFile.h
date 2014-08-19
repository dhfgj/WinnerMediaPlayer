/*
 * (C) 2014 see Authors.txt
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

#include "AudioFile.h"

class CTAKFile : public CAudioFile
{
	__int64		m_samples;
	int			m_framelen;
	int			m_totalframes;

	CAPETag*	m_APETag;

	bool ParseTAKStreamInfo(BYTE* buf, int size);

public:
	CTAKFile();
	~CTAKFile();

	void SetProperties(IBaseFilter* pBF);

	HRESULT Open(CBaseSplitterFile* pFile);
	REFERENCE_TIME Seek(REFERENCE_TIME rt);
	int GetAudioFrame(Packet* packet, REFERENCE_TIME rtStart);
	CString GetName() const { return L"TAK"; };
};
