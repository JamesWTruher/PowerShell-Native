// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

//! @brief Tests IsDirectory

#include <gtest/gtest.h>
#include <errno.h>
#include <unistd.h>
#include "isdirectory.h"
#include "getcommonlstat.h"

TEST(GetCommonLStat, RootIsDirectory)
{
    CommonStat cs;
    GetCommonLStat("/", &cs);
    bool isDir = IsDirectory("/");
    bool fromCommonLStat = (bool)cs.IsDirectory;
    EXPECT_EQ(isDir, fromCommonLStat);
}

TEST(GetCommonLStat, BinLsIsNotDirectory)
{
    CommonStat cs;
    GetCommonLStat("/bin/ls", &cs);
    bool isDir = IsDirectory("/bin/ls");
    bool fromCommonLStat = (bool)cs.IsDirectory;
    EXPECT_EQ(isDir, fromCommonLStat);
}


TEST(GetCommonLStat, ReturnsFalseForFakeDirectory)
{
    CommonStat cs;
    int badDir = GetCommonLStat("/A/Really/Bad/Directory",&cs);
    EXPECT_EQ(badDir, -1);
}

TEST(GetCommonLStat, GetOwnerIdOfRoot)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %u /", "r");
#else
     p = popen("/usr/bin/stat -c %u /", "r");
#endif
    int uid = -1;
    int result = fscanf(p, "%d", &uid);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(uid, cs.UserId);
}

TEST(GetCommonLStat, GetGroupId)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %g /", "r");
#else
     p = popen("/usr/bin/stat -c %g /", "r");
#endif
    int gid = -1;
    int result = fscanf(p, "%d", &gid);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(gid, cs.UserId);
}

TEST(GetCommonLStat, GetInodeNumber)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %i /", "r");
#else
     p = popen("/usr/bin/stat -c %i /", "r");
#endif
    long inode = -1;
    int result = fscanf(p, "%ld", &inode);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(inode, cs.Inode);
}

TEST(GetCommonLStat, GetSize)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %z /", "r");
#else
     p = popen("/usr/bin/stat -c %s /", "r");
#endif
    long size = -1;
    int result = fscanf(p, "%ld", &size);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(size, cs.Size);
}

TEST(GetCommonLStat, GetBlockSize)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %k /", "r");
#else
     p = popen("/usr/bin/stat -c %o /", "r");
#endif
    long bSize = -1;
    int result = fscanf(p, "%ld", &bSize);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(bSize, cs.BlockSize);
}

TEST(GetCommonLStat, GetBlockCount)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %b /", "r");
#else
     p = popen("/usr/bin/stat -c %b /", "r");
#endif
    int bSize = -1;
    int result = fscanf(p, "%d", &bSize);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(bSize, cs.NumberOfBlocks);
}

TEST(GetCommonLStat, GetLinkCount)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %l /", "r");
#else
     p = popen("/usr/bin/stat -c %h /", "r");
#endif
    int linkcount = -1;
    int result = fscanf(p, "%d", &linkcount);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(linkcount, cs.HardlinkCount);
}

TEST(GetCommonLStat, GetDeviceId)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %d /", "r");
#else
     p = popen("/usr/bin/stat -c %d /", "r");
#endif
    int deviceId = -1;
    int result = fscanf(p, "%d", &deviceId);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(deviceId, cs.DeviceId);
}

TEST(GetCommonLStat, GetATime)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %a /", "r");
#else
     p = popen("/usr/bin/stat -c %X /", "r");
#endif
    long aTime = -1;
    int result = fscanf(p, "%ld", &aTime);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(aTime, cs.AccessTime);
}

TEST(GetCommonLStat, GetMTime)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %m /", "r");
#else
     p = popen("/usr/bin/stat -c %Y /", "r");
#endif
    long mTime = -1;
    int result = fscanf(p, "%ld", &mTime);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(mTime, cs.ModifiedTime);
}

TEST(GetCommonLStat, GetCTime)
{
    FILE *p;
    CommonStat cs;
#if defined (__APPLE__)
     p = popen("/usr/bin/stat -f %c /", "r");
#else
     p = popen("/usr/bin/stat -c %Z /", "r");
#endif
    long cTime = -1;
    int result = fscanf(p, "%ld", &cTime);
    pclose(p);
    GetCommonLStat("/", &cs);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(cTime, cs.CreationTime);
}