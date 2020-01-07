// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

//! @brief Tests IsDirectory

#include <gtest/gtest.h>
#include <errno.h>
#include <unistd.h>
#include "getcommonfstat.h"

TEST(GetCommonFStat, InodeIsInode)
{
    const std::string ftemplate = "/tmp/CommonStatModeF_XXXXXX";
    char fname[PATH_MAX];
    int fd;
    struct stat buffer;
    CommonStat cs;

    strcpy(fname, ftemplate.c_str());

    fd = mkstemp(fname);
    EXPECT_NE(fd, -1);

    fstat(fd, &buffer);
    GetCommonFStat(fd, &cs);

    close(fd);
    unlink(fname);

    EXPECT_EQ(buffer.st_ino, cs.Inode);

}

TEST(GetCommonFStat, ModeIsMode)
{
    const std::string ftemplate = "/tmp/CommonStatModeF_XXXXXX";
    char fname[PATH_MAX];
    int fd;
    struct stat buffer;
    CommonStat cs;

    strcpy(fname, ftemplate.c_str());

    fd = mkstemp(fname);
    EXPECT_NE(fd, -1);

    fstat(fd, &buffer);
    GetCommonFStat(fd, &cs);

    close(fd);
    unlink(fname);

    EXPECT_EQ(buffer.st_mode, cs.Mode);

}

TEST(GetCommonFStat, DirectoryIsDirectory)
{
    const std::string ftemplate = "/tmp/CommonStatModeF_XXXXXX";
    char fname[PATH_MAX];
    int fd;
    struct stat buffer;
    CommonStat cs;

    strcpy(fname, ftemplate.c_str());

    fd = mkstemp(fname);
    EXPECT_NE(fd, -1);

    fstat(fd, &buffer);
    GetCommonFStat(fd, &cs);

    close(fd);
    unlink(fname);

    EXPECT_EQ(S_ISDIR(buffer.st_mode), cs.IsDirectory);

}

TEST(GetCommonFStat, FileIsFile)
{
    const std::string ftemplate = "/tmp/CommonStatModeF_XXXXXX";
    char fname[PATH_MAX];
    int fd;
    struct stat buffer;
    CommonStat cs;

    strcpy(fname, ftemplate.c_str());

    fd = mkstemp(fname);
    EXPECT_NE(fd, -1);

    fstat(fd, &buffer);
    GetCommonFStat(fd, &cs);

    close(fd);
    unlink(fname);

    EXPECT_EQ(S_ISREG(buffer.st_mode), cs.IsFile);

}

