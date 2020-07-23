/**
 * \kernelgroup{SceIofilemgr}
 * \usage{psp2kern/kernel/iofilemgr.h,SceIofilemgrForDriver_stub}
 */

#ifndef _PSP2_IO_FCNTL_H_
#define _PSP2_IO_FCNTL_H_

#pragma GCC warning "psp2kern/io/fcntl.h is deprecated. Please include psp2kern/kernel/iofilemgr.h."

#include <psp2kern/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The following definitions are retained for backward compatibility */

/** Note: Not all of these ::ksceIoOpen flags are not compatible with the
   open() flags found in sys/unistd.h. */
#define SCE_O_DIROPEN SCE_FDIRO     //!< Internal use for ::sceIoDopen
#define SCE_O_RDLOCK  SCE_FRLOCK    //!< Read locked (non-shared)
#define SCE_O_WRLOCK  SCE_FWLOCK    //!< Write locked (non-shared)
#define SCE_O_SCAN    SCE_FSCAN     //!< Scan type
#define SCE_O_RCOM    SCE_FRCOM     //!< Remote command entry

#define SCE_DEV_TYPE_NULL    SCE_D_TYPE_NULL     //!< Dummy device
#define SCE_DEV_TYPE_CHAR    SCE_D_TYPE_CHAR     //!< Character device
#define SCE_DEV_TYPE_BLOCK   SCE_D_TYPE_BLOCK    //!< Block device
#define SCE_DEV_TYPE_FS      SCE_D_TYPE_FS       //!< File system device
#define SCE_DEV_TYPE_ALIAS   SCE_D_TYPE_ALIAS    //!< Alias name
#define SCE_DEV_TYPE_MOUNTPT SCE_D_TYPE_MOUNTPT  //!< Mount point

/**
 * Open or create a file for reading or writing (asynchronous)
 *
 * @param file - Pointer to a string holding the name of the file to open
 * @param flags - Libc styled flags that are or'ed together
 * @param mode - File access mode (One or more ::SceIoMode).
 * @return A non-negative integer is a valid fd, anything else an error
 */
SceUID ksceIoOpenAsync(const char *file, int flags, SceMode mode);

/**
 * Delete a descriptor (asynchronous)
 *
 * @param fd - File descriptor to close
 * @return < 0 on error
 */
int ksceIoCloseAsync(SceUID fd);

/**
 * Read input (asynchronous)
 *
 * @par Example:
 * @code
 * bytes_read = ksceIoRead(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 *
 * @return < 0 on error.
 */
int ksceIoReadAsync(SceUID fd, void *data, SceSize size);

/**
 * Write output (asynchronous)
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 *
 * @return < 0 on error.
 */
int ksceIoWriteAsync(SceUID fd, const void *data, SceSize size);

/**
 * Reposition read/write file descriptor offset (asynchronous)
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - One of ::SceIoSeekMode.
 *
 * @return < 0 on error. Actual value should be passed returned by the ::ksceIoWaitAsync call.
 */
int ksceIoLseekAsync(SceUID fd, SceOff offset, int whence);

/**
  * Cancel an asynchronous operation on a file descriptor.
  *
  * @param fd - The file descriptor to perform cancel on.
  *
  * @return < 0 on error.
  */
int ksceIoCancel(SceUID fd);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_FCNTL_H_ */

