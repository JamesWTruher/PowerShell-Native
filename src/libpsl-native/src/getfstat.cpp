// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

//! @brief returns the stat of a file

#include "getstat.h"

#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

//! @brief GetFStat returns the stat of a file. This simply delegates to the
//! stat() system call and maps errno to the expected values for GetLastError.
//!
//! GetFStat
//!
//! @param[in] fildes
//! @parblock
//! A pointer to the buffer that contains the file descriptor
//!
//! an integer
//! @endparblock
//!
//! @param[in] stat
//! @parblock
//! A pointer to the buffer in which to place the stat information
//! @endparblock
//!
//! @retval 0 if successful
//! @retval -1 if failed
//!

// DO NOT use in managed code
// use externally defined structs in managed code has proven to be buggy
// (memory corruption issues due to layout difference between platforms)
// see https://github.com/dotnet/corefx/issues/29700#issuecomment-389313075
int32_t GetFStat(int fd, struct stat* buf)
{
    errno = 0;

    return fstat(fd, buf);
}

