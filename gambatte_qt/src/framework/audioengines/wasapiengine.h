/***************************************************************************
 *   Copyright (C) 2009 by Sindre Aam�s                                    *
 *   aamas@stud.ntnu.no                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2 as     *
 *   published by the Free Software Foundation.                            *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License version 2 for more details.                *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   version 2 along with this program; if not, write to the               *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef WASAPIENGINE_H
#define WASAPIENGINE_H

#include "../audioengine.h"
#include <BaseTsd.h>
#include <memory>

class QComboBox;
class QCheckBox;
class IAudioClient;
class IAudioRenderClient;
class IAudioClock;

class WasapiEngine: public AudioEngine {
	const std::auto_ptr<QWidget> confWidget;
	QComboBox *const deviceSelector;
	QCheckBox *const exclusiveBox;
	IAudioClient *pAudioClient;
	IAudioRenderClient *pRenderClient;
	IAudioClock *pAudioClock;
	unsigned pos_;
	unsigned posFrames;
	unsigned deviceIndex;
	UINT32 bufferFrameCount;
	RateEst est;
	bool started;
	bool exclusive;

	int doInit(int rate, unsigned latency);
	int waitForSpace(UINT32 &numFramesPadding, unsigned space);
	int write(void *buffer, unsigned frames, UINT32 numFramesPadding);

public:
	static bool isUsable();
	WasapiEngine();
	~WasapiEngine();
	void uninit();
	int write(void *buffer, unsigned frames);
	int write(void *buffer, unsigned samples, BufferState &preBufState_out, RateEst::Result &rate_out);
	const RateEst::Result rateEstimate() const { return est.result(); }
	const BufferState bufferState() const;
	void pause();
	QWidget* settingsWidget() { return confWidget.get(); }
	void acceptSettings();
	void rejectSettings();
};

#endif /* WASAPIENGINE_H */
