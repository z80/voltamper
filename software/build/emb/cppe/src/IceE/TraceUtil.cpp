// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/TraceUtil.h>
#include <IceE/StringUtil.h>
#include <IceE/ReplyStatus.h>
#include <IceE/TraceLevels.h>
#include <IceE/Logger.h>
#include <IceE/BasicStream.h>
#include <IceE/Protocol.h>
#include <IceE/SafeStdio.h>
#include <IceE/OperationMode.h>
#include <IceE/Identity.h>
#include <IceE/Instance.h>

using namespace std;
using namespace Ice;
using namespace IceInternal;

static void
printIdentityFacetOperation(string& s, BasicStream& stream)
{
    Identity identity;
    identity.__read(&stream);
    s += "\nidentity = ";
    s += stream.instance()->identityToString(identity);

    vector<string> facet;
    stream.read(facet);
    s += "\nfacet = ";
    if(!facet.empty())
    {
        s += IceUtilInternal::escapeString(facet[0], "");
    }

    string operation;
    stream.read(operation);
    s += "\noperation = ";
    s += operation;
}

static string
getMessageTypeAsString(Byte type)
{
    switch(type)
    {
        case requestMsg:
            return "request";
        case requestBatchMsg:
            return "batch request";
        case replyMsg:
            return "reply";
        case closeConnectionMsg:
            return "close connection";
        case validateConnectionMsg:
            return "validate connection";
        default:
            return "unknown";
    }
}

static void
printRequestHeader(string& s, BasicStream& stream)
{
    printIdentityFacetOperation(s, stream);

    Byte mode;
    stream.read(mode);
    s += Ice::printfToString("\nmode = %d ", static_cast<int>(mode));
    switch(mode)
    {
        case Normal:
        {
            s += "(normal)";
            break;
        }

        case Nonmutating:
        {
            s += "(nonmutating)";
            break;
        }

        case Idempotent:
        {
            s += "(idempotent)";
            break;
        }

        default:
        {
            s += "(unknown)";
            break;
        }
    }

    Int sz;
    stream.readSize(sz);
    s += "\ncontext = ";
    while(sz--)
    {
        pair<string, string> pair;
        stream.read(pair.first);
        stream.read(pair.second);
        s += pair.first;
        s += "/";
        s += pair.second;
        if(sz)
        {
            s += ", ";
        }
    }
}

static Byte
printHeader(string& s, BasicStream& stream)
{
    Byte magicNumber;
    stream.read(magicNumber);        // Don't bother printing the magic number
    stream.read(magicNumber);
    stream.read(magicNumber);
    stream.read(magicNumber);

    Byte pMajor;
    Byte pMinor;
    stream.read(pMajor);
    stream.read(pMinor);
    //Ice::printfToString("\nprotocol version = %d.%d", static_cast<unsigned>(pMajor),
    //static_cast<unsigned>(pMinor);

    Byte eMajor;
    Byte eMinor;
    stream.read(eMajor);
    stream.read(eMinor);
    //Ice::printfToString("\nencoding version = %d.%d", static_cast<unsigned>(eMajor),
    //static_cast<unsigned>(eMinor);

    Byte type;
    stream.read(type);
    string typeStr = getMessageTypeAsString(type);
    s += Ice::printfToString("\nmessage type = %d (%s)", static_cast<int>(type), typeStr.c_str());

    Byte compress;
    stream.read(compress);
    s += Ice::printfToString("\ncompression status = %d ", static_cast<int>(compress));

    switch(compress)
    {
        case 0:
        {
            s += "(not compressed; do not compress response, if any)";
            break;
        }

        case 1:
        {
            s += "(not compressed; compress response, if any)";
            break;
        }

        case 2:
        {
            s += "(compressed; compress response, if any)";
            break;
        }

        default:
        {
            s += "(unknown)";
            break;
        }
    }

    Int size;
    stream.read(size);
    s += Ice::printfToString("\nmessage size = %d", size);

    return type;
}

static void
printRequest(string& s, BasicStream& stream)
{
    Int requestId;
    stream.read(requestId);
    s += Ice::printfToString("\nrequest id = %d", requestId);
    if(requestId == 0)
    {
        s += " (oneway)";
    }

    printRequestHeader(s, stream);
}

static void
printBatchRequest(string& s, BasicStream& stream)
{
    int batchRequestNum;
    stream.read(batchRequestNum);
    s += Ice::printfToString("\nnumber of requests = %d", batchRequestNum);

    for(int i = 0; i < batchRequestNum; ++i)
    {
        s += Ice::printfToString("\nrequest #%d:", i);
        printRequestHeader(s, stream);
        stream.skipEncaps();
    }
}

static void
printReply(string& s, BasicStream& stream)
{
    Int requestId;
    stream.read(requestId);
    s += Ice::printfToString("\nrequest id = %d", requestId);

    Byte replyStatus;
    stream.read(replyStatus);
    s += Ice::printfToString("\nreply status = %d ", static_cast<int>(replyStatus));
    switch(replyStatus)
    {
    case replyOK:
    {
        s += "(ok)";
        break;
    }

    case replyUserException:
    {
        s += "(user exception)";
        break;
    }

    case replyObjectNotExist:
    case replyFacetNotExist:
    case replyOperationNotExist:
    {
        switch(replyStatus)
        {
        case replyObjectNotExist:
        {
            s += "(object not exist)";
            break;
        }

        case replyFacetNotExist:
        {
            s += "(facet not exist)";
            break;
        }

        case replyOperationNotExist:
        {
            s += "(operation not exist)";
            break;
        }

        default:
        {
            assert(false);
            break;
        }
        }

        printIdentityFacetOperation(s, stream);
        break;
    }

    case replyUnknownException:
    case replyUnknownLocalException:
    case replyUnknownUserException:
    {
        switch(replyStatus)
        {
        case replyUnknownException:
        {
            s += "(unknown exception)";
            break;
        }

        case replyUnknownLocalException:
        {
            s += "(unknown local exception)";
            break;
        }

        case replyUnknownUserException:
        {
            s += "(unknown user exception)";
            break;
        }

        default:
        {
            assert(false);
            break;
        }
        }
                
        string unknown;
        stream.read(unknown, false);
        s += "\nunknown = ";
        s += unknown;
        break;
    }

    default:
    {
        s += "(unknown)";
        break;
    }
    }
}

static Byte
printMessage(string& s, BasicStream& stream)
{
    Byte type = printHeader(s, stream);

    switch(type)
    {
    case closeConnectionMsg:
    case validateConnectionMsg:
    {
        // We're done.
        break;
    }
        
    case requestMsg:
    {
        printRequest(s, stream);
        break;
    }
        
    case requestBatchMsg:
    {
        printBatchRequest(s, stream);
        break;
    }
        
    case replyMsg:
    {
        printReply(s, stream);
        break;
    }
        
    default:
    {
        break;
    }    
    }

    return type;
}

void
IceInternal::traceSend(const BasicStream& str, const LoggerPtr& logger, const TraceLevelsPtr& tl)
{
    if(tl->protocol >= 1)
    {
        BasicStream& stream = const_cast<BasicStream&>(str);
        BasicStream::Container::iterator p = stream.i;
        stream.i = stream.b.begin();

        string s;
        Byte type = printMessage(s, stream);

        logger->trace(tl->protocolCat, "sending " + getMessageTypeAsString(type) + " " + s);
        stream.i = p;
    }
}

void
IceInternal::traceRecv(const BasicStream& str, const LoggerPtr& logger, const TraceLevelsPtr& tl)
{
    if(tl->protocol >= 1)
    {
        BasicStream& stream = const_cast<BasicStream&>(str);
        BasicStream::Container::iterator p = stream.i;
        stream.i = stream.b.begin();

        string s;
        Byte type = printMessage(s, stream);

        logger->trace(tl->protocolCat, "received " + getMessageTypeAsString(type) + " " + s);
        stream.i = p;
    }
}

void
IceInternal::trace(const char* heading, const BasicStream& str, const LoggerPtr& logger, const TraceLevelsPtr& tl)
{
    if(tl->protocol >= 1)
    {
        BasicStream& stream = const_cast<BasicStream&>(str);
        BasicStream::Container::iterator p = stream.i;
        stream.i = stream.b.begin();

        string s;
        s += heading;
        printMessage(s, stream);

        logger->trace(tl->protocolCat, s);
        stream.i = p;
    }
}
