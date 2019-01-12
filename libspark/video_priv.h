/*
 * (C) 2010-2013 Stefan Seyfried
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * private video functions, to be used only inside libstb-hal
 */

#ifndef __video_priv__
#define __video_priv__

#include <video_hal.h>
#include <linux/dvb/video.h>

class VDec
{
public:
	/* all public, used inside libstb-hal only anyways... */
	int fd;			/* video device fd */
	unsigned int devnum;	/* unit number */
	/* apparently we cannot query the driver's state
	   => remember it */
	video_play_state_t playstate;
	int video_standby;
	bool stillpicture;

	/* constructor & destructor */
	VDec(unsigned int unit);
	~VDec(void);

	/* used directly by cVideo */
	int getAspectRatio(void);
	void getPictureInfo(int &width, int &height, int &rate);
	int Start(void);
	int Stop(bool blank = true);
	int SetStreamType(VIDEO_FORMAT type);
	void SetSyncMode(AVSYNC_TYPE mode);
	bool ShowPicture(const char * fname);
	void Standby(unsigned int bOn);

	/* used internally by dmx */
	int64_t GetPTS(void);
	/* used internally by playback */
	void openDevice(void);
	void closeDevice(void);
};

#endif
