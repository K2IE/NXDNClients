/*
 *   Copyright (C) 2009-2014,2016,2018,2020 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	KenwoodNetwork_H
#define	KenwoodNetwork_H

#include "CoreNetwork.h"
#include "StopWatch.h"
#include "UDPSocket.h"
#include "Timer.h"

#include <cstdint>
#include <string>

class CKenwoodNetwork : public ICoreNetwork {
public:
	CKenwoodNetwork(const std::string& address, bool debug);
	virtual ~CKenwoodNetwork();

	virtual bool open();

	virtual bool write(const unsigned char* data, unsigned int length);

	virtual unsigned int read(unsigned char* data);

	virtual void close();

    virtual void clock(unsigned int ms);

private:
	CUDPSocket     m_rtpSocket;
    CUDPSocket     m_rtcpSocket;
    CStopWatch     m_stopWatch;
    in_addr        m_address;
    unsigned short m_seqNo;
    unsigned long  m_timeStamp;
    unsigned int   m_ssrc;
    bool           m_debug;
    CTimer         m_timer;

    bool processIcomVoiceHeader(const unsigned char* data);
    bool processIcomVoiceData(const unsigned char* data);
    bool processKenwoodVoiceHeader(unsigned char* data);
    void processKenwoodVoiceData(unsigned char* data);
    bool writeRTPVoiceHeader(const unsigned char* data);
    bool writeRTPVoiceData(const unsigned char* data);
    bool writeRTPVoiceTrailer(const unsigned char* data);
    bool writeRTCPPing();
    bool writeRTCPData(unsigned char type, unsigned short src, unsigned short dst);
    unsigned int readRTP(unsigned char* data);
    unsigned int readRTCP(unsigned char* data);
};

#endif