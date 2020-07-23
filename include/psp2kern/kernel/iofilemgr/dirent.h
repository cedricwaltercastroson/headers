/**
 * \kernelgroup{SceIofilemgr}
 * \usage{psp2kern/kernel/iofilemgr/dirent.h,SceIofilemgrForDriver_stub}
 */

#ifndef _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_DIRENT_H_
#define _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_DIRENT_H_

#include <psp2kern/kernel/iofilemgr/async.h>
#include <psp2kern/kernel/iofilemgr/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Describes a single directory entry */
typedef struct SceIoDirent {
	SceIoStat d_stat;      //!< File status
	char      d_name[256]; //!< File name (not file path)
	void      *d_private;  //!< Reserved (set to 0)
	int       dummy;       //!< Padding
} SceIoDirent;

/**
  * Open a directory
  *
  * @par Example:
  * @code
  * int dfd;
  * dfd = ksceIoDopen("device:/");
  * if(dfd >= 0)
  * { Do something with the file descriptor }
  * @endcode
  * @param dirname - The directory to open for reading.
  * @return If >= 0 then a valid file descriptor, otherwise a Sony error code.
  */
SceUID ksceIoDopen(const char *dirname);

/**
  * Close an opened directory file descriptor
  *
  * @param fd - Already opened file descriptor (using ::ksceIoDopen)
  * @return < 0 on error
  */
int ksceIoDclose(SceUID fd);

/**
  * Reads an entry from an opened file descriptor.
  *
  * @param fd - Already opened file descriptor (using ::ksceIoDopen)
  * @param buf - Pointer to a ::SceIoDirent structure to hold the file information
  *
  * @return Read status
  * -   0 - No more directory entries left
  * - > 0 - More directory entries to go
  * - < 0 - Error
  */
int ksceIoDread(SceUID fd, SceIoDirent *buf);

/**
  * Open a directory (asynchronous)
  *
  * @param dirname - The directory to open for reading.
  * @param asyncParam - parameters related to async operation.
  *
  * @return If >= 0 then a valid op handle, otherwise a Sony error code.
  */
SceUID ksceIoDopenAsync(const char *dirname, SceIoAsyncParam* asyncParam);

/**
  * Reads an entry from an opened file descriptor (asynchronous)
  *
  * @param fd - Already opened file descriptor (using ::ksceIoDopen or ::ksceIoDopenAsync)
  * @param dir - Pointer to a ::SceIoDirent structure to hold the file information
  * @param asyncParam - parameters related to async operation.
  *
  * @return If >= 0 then a valid op handle, otherwise a Sony error code.
  */
SceUID ksceIoDreadAsync(SceUID fd, SceIoDirent *dir, SceIoAsyncParam* asyncParam);

/**
  * Close an opened directory file descriptor (asynchronous)
  *
  * @param fd - Already opened file descriptor (using ::ksceIoDopen or ::ksceIoDopenAsync)
  * @param asyncParam - parameters related to async operation.
  *
  * @return If >= 0 then a valid op handle, otherwise a Sony error code.
  */
SceUID ksceIoDcloseAsync(SceUID fd, SceIoAsyncParam* asyncParam);

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_DIRENT_H_ */
