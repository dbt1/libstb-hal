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
 * private video functions, only to be used in libstb-hal
 */

#ifndef __video_priv__
#define __video_priv__

#include "video_hal.h"
#include <hardware/vid/vid_inf.h>
#define video_format_t          vidDispSize_t
#include <cs_types.h>
#include "dmx_hal.h"

#define STB_HAL_VIDEO_HAS_GETSCREENIMAGE 1

typedef enum {
	VIDEO_STOPPED, /* Video is stopped */
	VIDEO_PLAYING, /* Video is currently playing */
	VIDEO_FREEZED  /* Video is freezed */
} video_play_state_t;

class VDec
{
public:
	/* video device */
	int fd;
	/* apparently we cannot query the driver's state
	   => remember it */
	video_play_state_t playstate;
	vidDispMode_t croppingMode;
	vidOutFmt_t outputformat;
	bool pic_shown;
	int scartvoltage;
	int z[2]; /* zoomvalue for 4:3 (0) and 16:9 (1) in percent */
	int *zoomvalue;
	void *blank_data[2]; /* we store two blank MPEGs (PAL/NTSC) in there */
	int blank_size[2];

	void routeVideo(int standby);
	int video_standby;

	/* constructor & destructor */
	VDec(void);
	~VDec(void);

	/* aspect ratio */
	int getAspectRatio(void);
	int setAspectRatio(int aspect, int mode);

	/* cropping mode */
	int setCroppingMode(vidDispMode_t x = VID_DISPMODE_NORM);

	/* blank on freeze */
	int getBlank(void);
	int setBlank(void);

	/* change video play state. Parameters are all unused. */
	int Start(void);
	int Stop(bool blank = true);

	/* set video_system */
	int SetVideoSystem(int video_system, bool remember = true);
	bool ShowPicture(const char * fname);
	void StopPicture();
	void Standby(unsigned int bOn);
	void Pig(int x, int y, int w, int h);
	int setZoom(int);
	void VideoParamWatchdog(void);
	void SetVideoMode(analog_mode_t mode);
	void FastForwardMode(int mode = 0);
	bool GetScreenImage(unsigned char * &data, int &xres, int &yres, bool get_video = true, bool get_osd = false, bool scale_to_video = false);
};

#endif
