/* ----------------------------------------------------------------------------
 * expWinSpawnClient.hpp --
 *
 *	Declares the SpawnClient classes.
 *
 * ----------------------------------------------------------------------------
 *
 * Written by: Don Libes, libes@cme.nist.gov, NIST, 12/3/90
 * 
 * Design and implementation of this program was paid for by U.S. tax
 * dollars.  Therefore it is public domain.  However, the author and NIST
 * would appreciate credit if this program or parts of it are used.
 * 
 * Copyright (c) 1997 Mitel Corporation
 *	work by Gordon Chaffee <chaffee@bmrc.berkeley.edu> for the WinNT port.
 *
 * Copyright (c) 2001-2002 Telindustrie, LLC
 *	work by David Gravereaux <davygrvy@pobox.com> for any Win32 OS.
 *
 * ----------------------------------------------------------------------------
 * URLs:    http://expect.nist.gov/
 *	    http://expect.sf.net/
 *	    http://bmrc.berkeley.edu/people/chaffee/expectnt.html
 * ----------------------------------------------------------------------------
 * RCS: @(#) $Id$
 * ----------------------------------------------------------------------------
 */

#include "expWinMessage.hpp"
#include "Mcl/include/CMcl.h"

class SpawnClientTransport
{
public:
    virtual void Write(Message *) = 0;
};

class SpawnMailboxClient : public SpawnClientTransport
{
public:
    SpawnMailboxClient(const char *name, CMclQueue<Message *> &_mQ);
    virtual void Write(Message *);
private:
    CMclMailbox *MasterToExpect;
    CMclMailbox *MasterFromExpect;
    CMclQueue<Message *> &mQ;
};

class ReadPipe : public CMclThreadHandler
{
public:
    ReadPipe(CMclQueue<Message *> &_mQ);
private:
    virtual unsigned ThreadHandlerProc(void);
    CMclQueue<Message *> &mQ;
    HANDLE hStdIn;
};

class SpawnStdioClient : public SpawnClientTransport
{
public:
    SpawnStdioClient(const char *name, CMclQueue<Message *> &_mQ);
    ~SpawnStdioClient();
    virtual void Write(Message *);
private:
    CMclQueue<Message *> &mQ;
    HANDLE hStdOut;
    HANDLE hStdErr;
    ReadPipe *reader;
    CMclThreadAutoPtr readThread;
};
