/**
 * \kernelgroup{SceIofilemgr}
 * \usage{psp2kern/kernel/iofilemgr.h,SceIofilemgrForDriver_stub}
 */

#ifndef _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_H_
#define _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_H_

#include <psp2common/kernel/iofilemgr.h>
#include <psp2kern/kernel/iofilemgr/async.h>
#include <psp2kern/kernel/iofilemgr/stat.h>
#include <psp2kern/kernel/iofilemgr/dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Remove directory entry
 *
 * @param filename - Path to the file to remove
 * @return < 0 on error
 */
int ksceIoRemove(const char *filename);

/**
 * Make a directory file
 *
 * @param dirname - The path to the directory
 * @param mode - Access mode bits.
 * @return Returns the value 0 if it's successful, otherwise <0
 */
int ksceIoMkdir(const char *dirname, SceIoMode mode);

/**
 * Remove a directory file
 *
 * @param dirname - Removes a directory file pointed by the string path
 * @return Returns the value 0 if it's successful, otherwise <0
 */
int ksceIoRmdir(const char *dirname);

/**
 * Change the name of a file
 *
 * @param oldname - The old filename
 * @param newname - The new filename
 * @return < 0 on error.
 */
int ksceIoRename(const char *oldname, const char *newname);

/**
  * Send a devctl command to a device.
  *
  * @par Example: Sending a simple command to a device
  * @code
  * SceIoDevInfo info;
  * ksceIoDevctl("ux0:", 0x3001, NULL, 0, &info, sizeof(SceIoDevInfo));
  * @endcode
  *
  * @param devname - String for the device to send the devctl to (e.g. "ux0:")
  * @param cmd - The command to send to the device
  * @param arg - A data block to send to the device, if NULL sends no data
  * @param arglen - Length of indata, if 0 sends no data
  * @param bufp - A data block to receive the result of a command, if NULL receives no data
  * @param buflen - Length of outdata, if 0 receives no data
  * @return 0 on success, < 0 on error
  */
int ksceIoDevctl(
	const char *devname,
	int cmd,
	const void *arg,
	SceSize arglen,
	void *bufp,
	SceSize buflen);

/**
  * Synchronize the file data on the device.
  *
  * @param devname - The device to synchronize (e.g. msfat0:)
  * @param flag - device specific flags
  */
int ksceIoSync(const char *devname, int flag);

/**
 * Open or create a file for reading or writing
 *
 * @par Example1: Open a file for reading
 * @code
 * if((fd = ksceIoOpen("device:/path/to/file", SCE_O_RDONLY, 0777) < 0) {
 * // error code in fd, for example no open filehandle left (0x80010018)
 * }
 * @endcode
 * @par Example2: Open a file for writing, creating it if it doesn't exist
 * @code
 * if((fd = ksceIoOpen("device:/path/to/file", SCE_O_WRONLY|SCE_O_CREAT, 0777) < 0) {
 * // error code in fd, for example no open filehandle left (0x80010018)
 * }
 * @endcode
 *
 * @param filename - Pointer to a string holding the name of the file to open
 * @param flag - Libc styled flags that are or'ed together
 * @param mode - File access mode (One or more ::SceIoMode).
 * @return A non-negative integer is a valid fd, anything else an error
 */
SceUID ksceIoOpen(const char *filename, int flag, SceIoMode mode);

/**
 * Delete a descriptor
 *
 * @code
 * ksceIoClose(fd);
 * @endcode
 *
 * @param fd - File descriptor to close
 * @return < 0 on error
 */
int ksceIoClose(SceUID fd);

/**
  * Perform an ioctl on a device.
  *
  * @param fd - Opened file descriptor to ioctl to
  * @param cmd - The command to send to the device
  * @param argp - A data block to send to the device, if NULL sends no data
  * @param arglen - Length of indata, if 0 sends no data
  * @param bufp - A data block to receive the result of a command, if NULL receives no data
  * @param buflen - Length of outdata, if 0 receives no data
  * @return 0 on success, < 0 on error
  */
int ksceIoIoctl(
  SceUID fd,
  int cmd,
  const void *argp,
  SceSize arglen,
  void *bufp,
  SceSize buflen);

/**
 * Reposition read/write file descriptor offset
 *
 * @par Example:
 * @code
 * pos = ksceIoLseek(fd, -10, SCE_SEEK_END);
 * @endcode
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - One of ::SceIoSeekMode.
 *
 * @return The position in the file after the seek.
 */
SceOff ksceIoLseek(SceUID fd, SceOff offset, int whence);

/**
 * Read input
 *
 * @par Example:
 * @code
 * bytes_read = ksceIoRead(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to read from
 * @param buf - Pointer to the buffer where the read data will be placed
 * @param nbyte - Size of the read in bytes
 *
 * @return The number of bytes read
 */
SceSSize ksceIoRead(SceUID fd, void *buf, SceSize nbyte);

/**
 * Write output
 *
 * @par Example:
 * @code
 * bytes_written = ksceIoWrite(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to write to
 * @param buf - Pointer to the data to write
 * @param nbyte - Size of data to write
 *
 * @return The number of bytes written
 */
SceSSize ksceIoWrite(SceUID fd, const void *buf, SceSize nbyte);

/**
 * Read input at offset
 *
 * @par Example:
 * @code
 * bytes_read = ksceIoPread(fd, data, 100, 0x1000);
 * @endcode
 *
 * @param fd - Opened file descriptor to read from
 * @param buf - Pointer to the buffer where the read data will be placed
 * @param nbyte - Size of the read in bytes
 * @param offset - Offset to read
 *
 * @return < 0 on error.
 */
SceSSize ksceIoPread(SceUID fd, void *buf, SceSize nbyte, SceOff offset);

/**
 * Write output at offset
 *
 * @par Example:
 * @code
 * bytes_written = ksceIoPwrite(fd, data, 100, 0x1000);
 * @endcode
 *
 * @param fd - Opened file descriptor to write to
 * @param buf - Pointer to the data to write
 * @param nbyte - Size of data to write
 * @param offset - Offset to write
 *
 * @return The number of bytes written
 */
SceSSize ksceIoPwrite(SceUID fd, const void *buf, SceSize nbyte, SceOff offset);

/**
 * Synchronize the file data for one file
 *
 * @param fd - Opened file descriptor to sync
 * @param flag - device specific flags
 *
 * @return < 0 on error.
 */
int ksceIoSyncByFd(SceUID fd, int flag);

/*--------------------Async IO--------------------*/

/**
 * Remove directory entry (asynchronous)
 *
 * @param file - Path to the file to remove
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
int ksceIoRemoveAsync(const char *file, SceIoAsyncParam* asyncParam);

/**
 * Change the name of a file (asynchronous)
 *
 * @param oldname - The old filename
 * @param newname - The new filename
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoRenameAsync(const char *oldname, const char *newname, SceIoAsyncParam* asyncParam);

/**
 * Open or create a file for reading or writing (asynchronous)
 *
 * @param file - Pointer to a string holding the name of the file to open
 * @param flags - Libc styled flags that are or'ed together
 * @param mode - File access mode (One or more ::SceIoMode).
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoOpenAsync(const char *file, int flags, SceMode mode, SceIoAsyncParam* asyncParam);

/**
 * Delete a descriptor (asynchronous)
 *
 * @param fd - File descriptor to close
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoCloseAsync(SceUID fd, SceIoAsyncParam* asyncParam);

/**
 * Read input (asynchronous)
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoReadAsync(SceUID fd, void *data, SceSize size, SceIoAsyncParam* asyncParam);

/**
 * Read input at offset (asynchronous)
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 * @param offset - Offset to read
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoPreadAsync(SceUID fd, void *data, SceSize size, SceOff offset, SceIoAsyncParam* asyncParam);

/**
 * Write output (asynchronous)
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoWriteAsync(SceUID fd, const void *data, SceSize size, SceIoAsyncParam* asyncParam);

/**
 * Write output at offset (asynchronous)
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 * @param offset - Offset to write
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoPwriteAsync(SceUID fd, const void *data, SceSize size, SceOff offset, SceIoAsyncParam* asyncParam);

/**
 * Reposition read/write file descriptor offset (asynchronous)
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - One of ::SceIoSeekMode.
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoLseekAsync(SceUID fd, SceOff offset, int whence, SceIoAsyncParam* asyncParam);

/**
 * Synchronize device state with state of file or directory being opened
 *
 * @param fd - Opened file descriptor to sync
 * @param fd - Device-dependent flag
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoSyncByFdAsync(SceUID fd, int flag, SceIoAsyncParam* asyncParam);

/**
 * Synchronize device state with memory state
 *
 * @param fd - Device name
 * @param fd - Device-dependent flag
 * @param asyncParam - parameters related to async operation.
 *
 * @return A non-negative integer is a valid op handle, anything else an error
 */
SceUID ksceIoSyncAsync(const char* device, int flag, SceIoAsyncParam* asyncParam);

/**
  * This function is unimplemented.
  *
  * @return SCE_KERNEL_ERROR_UNSUP (0x80020004)
  */
int ksceIoIoctlAsync(
  SceUID fd,
  int cmd,
  const void *argp,
  SceSize arglen,
  void *bufp,
  SceSize buflen,
  SceIoAsyncParam* asyncParam);

/**
  * This function is unimplemented.
  *
  * @return SCE_KERNEL_ERROR_UNSUP (0x80020004)
  */
int ksceIoDevctlAsync(
  const char *devname,
  int cmd,
  const void *arg,
  SceSize arglen,
  void *bufp,
  SceSize buflen,
  SceIoAsyncParam* asyncParam);

/*--------------------IO Priority--------------------*/

/*Valid priority values range: 1 (highest) - 15 (lowest). Default priority value is 14*/

/**
 * Set IO operations priority for file descriptor for non-game application
 *
 * @param fd - File UID
 * @param priority - IO operations priority
 *
 * @return < 0 on error.
 */
int ksceIoSetPriorityForSystem(SceUID fd, int priority);

/**
 * Get IO operations priority for file descriptor for non-game application
 *
 * @param fd - File UID
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int ksceIoGetPriorityForSystem(SceUID fd);

/**
 * Set IO operations priority for caller process (will be default for all new IO operations)
 *
 * @param priority - New default IO operations priority
 *
 * @return < 0 on error.
 */
int ksceIoSetProcessDefaultPriorityForSystem(int priority);

/**
 * Get IO operations priority for process
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int ksceIoGetProcessDefaultPriorityForSystem(void);

/**
 * Set IO operations priority for caller thread for non-game
 * application (will be default for all new IO operations)
 *
 * @param priority - New default IO operations priority
 *
 * @return < 0 on error.
 */
int ksceIoSetThreadDefaultPriorityForSystem(int priority);

/**
 * Get IO operations priority for thread for non-game application
 *
 * @return A non-negative integer is a valid priority, anything else an error
 */
int ksceIoGetThreadDefaultPriorityForSystem(void);

/*--------------------Device mount functions--------------------*/

/**
  * Mounts a device
  *
  * @param[in]  id          Device to mount
  * @param[in]  path        Where to mount to
  * @param[in]  permission  Permission flags
  * @param      a4          Unknown, set to 0
  * @param      a5          Unknown, set to 0
  * @param      a6          Unknown, set to 0
  *
  * @return < 0 on error.
  */
int ksceIoMount(int id, const char *path, int permission, int a4, int a5, int a6);

/**
  * Unmounts a device
  *
  * @param[in]  id    Device to unmount
  * @param[in]  a2    Unknown, set to 0
  * @param[in]  a3    Unknown, set to 0
  * @param[in]  a4    Unknown, set to 0
  *
  * @return < 0 on error.
  */
int ksceIoUmount(int id, int a2, int a3, int a4);

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2KERN_KERNEL_IOFILEMGR_H_ */
