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
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Suite 500 Boston, MA 02110-1335 USA
 *
 * cVideo dummy implementation
 */

#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "video_hal.h"
#include "dmx_hal.h"
#include "avdec.h"
#include "lt_debug.h"
#define lt_debug(args...) _lt_debug(TRIPLE_DEBUG_VIDEO, this, args)
#define lt_info(args...) _lt_info(TRIPLE_DEBUG_VIDEO, this, args)
#define lt_info_c(args...) _lt_info(TRIPLE_DEBUG_VIDEO, NULL, args)

cVideo *videoDecoder = NULL;
int system_rev = 0;

extern cDemux *videoDemux;
extern AVDec *avdec;

cVideo::cVideo(int, void *, void *, unsigned int)
{
	lt_debug("%s\n", __func__);
}

cVideo::~cVideo(void)
{
}

int cVideo::setAspectRatio(int vformat, int cropping)
{
	lt_info("%s(%d, %d)\n", __func__, vformat, cropping);
	return avdec->set_aspect(vformat, cropping);
}

int cVideo::getAspectRatio(void)
{
	int ret = 0;
	return ret;
}

int cVideo::setCroppingMode(void)
{
	return 0;
}

int cVideo::Start(void *, unsigned short, unsigned short, void *)
{
	lt_debug("%s >\n", __func__);
	avdec->start_video();
	return 0;
}

int cVideo::Stop(bool)
{
	lt_debug("%s >\n", __func__);
	avdec->stop_video();
	return 0;
}

int cVideo::setBlank(int)
{
	return 1;
}

/* this is a dummy */
int cVideo::SetVideoSystem(int system, bool)
{
	int h;
	switch(system)
	{
		case VIDEO_STD_NTSC:
		case VIDEO_STD_480P:
			h = 480;
			break;
		case VIDEO_STD_1080I60:
		case VIDEO_STD_1080I50:
		case VIDEO_STD_1080P30:
		case VIDEO_STD_1080P24:
		case VIDEO_STD_1080P25:
		case VIDEO_STD_1080P50:
			h = 1080;
			break;
		case VIDEO_STD_720P50:
		case VIDEO_STD_720P60:
			h = 720;
			break;
		case VIDEO_STD_AUTO:
			lt_info("%s: VIDEO_STD_AUTO not implemented\n", __func__);
			// fallthrough
		case VIDEO_STD_SECAM:
		case VIDEO_STD_PAL:
		case VIDEO_STD_576P:
			h = 576;
			break;
		default:
			lt_info("%s: unhandled value %d\n", __func__, system);
			return 0;
	}
	lt_debug("%s: pic height is %d\n", __func__, h);
	return 0;
}

int cVideo::getPlayState(void)
{
	return 1; //VIDEO_PLAYING;
}

void cVideo::SetVideoMode(analog_mode_t)
{
}

bool cVideo::ShowPicture(const char *fname)
{
	lt_info("%s(%s)\n", __func__, fname);
	if (access(fname, R_OK))
		return true;
}

void cVideo::StopPicture()
{
}

void cVideo::Standby(unsigned int)
{
}

int cVideo::getBlank(void)
{
	return 0;
}

void cVideo::Pig(int x, int y, int w, int h, int, int)
{
	avdec->pig(x, y, w, h);
}

void cVideo::getPictureInfo(int &width, int &height, int &rate)
{
	width = 1; //dec_w;
	height = 1; //dec_h;
	rate = 1; //dec_r;
}

void cVideo::SetSyncMode(AVSYNC_TYPE)
{
};

int cVideo::SetStreamType(VIDEO_FORMAT v)
{
	return avdec->set_videoformat(v);
}

bool cVideo::GetScreenImage(unsigned char * &data, int &xres, int &yres, bool get_video, bool get_osd, bool scale_to_video)
{
	lt_info("%s: data 0x%p xres %d yres %d vid %d osd %d scale %d\n",
		__func__, data, xres, yres, get_video, get_osd, scale_to_video);
	return false;
}

void cVideo::SetDemux(cDemux *)
{
	lt_debug("%s: not implemented yet\n", __func__);
}

