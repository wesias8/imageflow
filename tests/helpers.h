#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include "string.h"
#include <stdbool.h>
#include "curl/curl.h"
#include "curl/easy.h"
#include <stdlib.h>
#include "imageflow.h"
#include "imageflow_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#include "io.h"
#pragma warning(error : 4005)

#ifndef _UNISTD_H
#define _UNISTD_H 1

/* This file intended to serve as a drop-in replacement for
*  unistd.h on Windows
*  Please add functionality as neeeded
*/

#include <stdlib.h>
#include <io.h>
#include <process.h> /* for getpid() and the exec..() family */
#include <direct.h> /* for _getcwd() and _chdir() */

#define srandom srand
#define random rand

/* Values for the second argument to access.
These may be OR'd together.  */
#define R_OK 4 /* Test for read permission.  */
#define W_OK 2 /* Test for write permission.  */
//#define   X_OK    1       /* execute permission - unsupported in windows*/
#define F_OK 0 /* Test for existence.  */

#define access _access
#define dup2 _dup2
#define execve _execve
#define ftruncate _chsize
#define unlink _unlink
#define fileno _fileno
#define getcwd _getcwd
#define chdir _chdir
#define isatty _isatty
#define lseek _lseek
/* read, write, and close are NOT being #defined here, because while there are file handle specific versions for
 * Windows, they probably don't work for sockets. You need to look at your app and consider whether to call e.g.
 * closesocket(). */

#define ssize_t int

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define S_IRWXU = (400 | 200 | 100)
#endif
#else
#include "unistd.h"
#endif

FLOW_EXPORT uint8_t* get_bytes_cached(flow_context* c, size_t* bytes_count_out, const char* url);
FLOW_EXPORT void fetch_image(const char* url, char* dest_path);
FLOW_EXPORT uint8_t* read_all_bytes(flow_context* c, size_t* buffer_size, const char* path);
FLOW_EXPORT bool write_all_byte(const char* path, char* buffer, size_t size);
FLOW_EXPORT void copy_file(FILE* from, FILE* to);

FLOW_EXPORT unsigned long djb2(unsigned const char* str);
FLOW_EXPORT size_t nonzero_count(uint8_t* array, size_t length);

FLOW_EXPORT struct flow_bitmap_bgra* BitmapBgra_create_test_image(flow_context* c);
FLOW_EXPORT double flow_bitmap_float_compare(flow_context* c, flow_bitmap_float* a, flow_bitmap_float* b,
                                             float* out_max_delta);

FLOW_EXPORT struct flow_io* get_io_for_cached_url(flow_context* c, const char* url, void* owner);

FLOW_EXPORT bool has_err(flow_context* c, const char* file, int line, const char* func);

#define ERR(c) REQUIRE_FALSE(has_err(c, __FILE__, __LINE__, __func__))

#ifdef __cplusplus
}
#endif