/**
 * \kernelgroup{SceIofilemgr}
 * \usage{psp2kern/kernel/iofilemgr.h,SceIofilemgrForDriver_stub}
 */

#ifndef _PSP2_IO_FCNTL_H_
#define _PSP2_IO_FCNTL_H_

#pragma message "psp2kern/io/fcntl.h is deprecated. Please include psp2kern/kernel/iofilemgr.h."

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

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_FCNTL_H_ */
