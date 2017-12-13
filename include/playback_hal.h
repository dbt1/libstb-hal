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
 */

#ifndef __playback_hal__
#define __playback_hal__

#include <string>
#include <stdint.h>
#include <vector>

extern "C" {
#include <libavformat/avformat.h>
}

/*
 * This is actually the max number that could be returned by
 * FindAllPids() / FindAllSubs().
 * not yet implemented, most archs return max. 10 PIDs.
 */
#define MAX_PLAYBACK_PIDS 40

typedef enum {
	PLAYMODE_TS = 0,
	PLAYMODE_FILE,
} playmode_t;

class PBPrivate;
class cPlayback
{
public:
	bool Open(playmode_t PlayMode);
	void Close(void);
	bool Start(char *filename, unsigned short vpid, int vtype, unsigned short apid, int ac3, unsigned int duration);
	bool Start(std::string filename, std::string headers = "");
	bool Stop(void);
	bool SetAPid(unsigned short pid, int audio_flag);
	bool SetSpeed(int speed);
	bool GetSpeed(int &speed) const;
	bool GetPosition(int &position, int &duration);
	bool SetPosition(int position, bool absolute = false);
	void FindAllPids(uint16_t *pids, unsigned short *aud_flags, uint16_t *num, std::string *language);
	void FindAllPids(int *apids, unsigned int *ac3flags, uint32_t *numpida, std::string *language){FindAllPids((uint16_t*)apids, (unsigned short*)ac3flags, (uint16_t*) numpida, language);}
	void FindAllSubs(uint16_t *pids, unsigned short *supported, uint16_t *num, std::string *language);
	bool SelectSubtitles(int pid, std::string charset = "");
	void GetChapters(std::vector<int> &positions, std::vector<std::string> &titles);
	void RequestAbort();
	void GetTitles(std::vector<int> &playlists, std::vector<std::string> &titles, int &current);
	void SetTitle(int title);
	uint64_t GetReadCount(void);
	void FindAllTeletextsubtitlePids(int *, unsigned int *numpids, std::string *, int *, int *){*numpids = 0;}
	void FindAllSubtitlePids(int * /*pids*/, unsigned int *numpids, std::string * /*language*/){*numpids = 0;}
	int GetSubtitlePid(void){return 0;}
	bool SetTeletextPid(int /*pid*/){return true;}
	int GetAPid(){return 0;}
	void GetMetadata(std::vector<std::string> /*&keys*/, std::vector<std::string> /*&values*/){}
	void GetPts(uint64_t &/*pts*/){}
	bool SetSubtitlePid(int /*pid*/){return false;}
	AVFormatContext *GetAVFormatContext(){return NULL;}
	void ReleaseAVFormatContext(){}

	//
	cPlayback(int num = 0);
	~cPlayback();
private:
	PBPrivate *pd;
};

#endif
