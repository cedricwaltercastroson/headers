/**
 * \kernelgroup{SceIofilemgr}
 * \usage{psp2kern/kernel/iofilemgr/stat.h,SceIofilemgrForDriver_stub}
 */

#ifndef _PSP2_IO_STAT_H_
#define _PSP2_IO_STAT_H_

#pragma message "psp2kern/io/stat.h is deprecated. Please include psp2kern/kernel/iofilemgr.h."

#include <psp2kern/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The following definitions are retained for backward compatibility */

/** Access modes for st_mode in ::SceIoStat. */
typedef enum SceIoAccessMode {
	SCE_S_IXUSR		= 0x0001,  //!< User execute permission
	SCE_S_IWUSR		= 0x0002,  //!< User write permission
	SCE_S_IRUSR		= 0x0004,  //!< User read permission
	SCE_S_IRWXU		= 0x0007,  //!< User access rights mask

	SCE_S_IXGRP		= 0x0008,  //!< Group execute permission
	SCE_S_IWGRP		= 0x0010,  //!< Group write permission
	SCE_S_IRGRP		= 0x0020,  //!< Group read permission
	SCE_S_IRWXG		= 0x0038,  //!< Group access rights mask

	SCE_S_IXOTH		= 0x0040,  //!< Others execute permission
	SCE_S_IWOTH		= 0x0080,  //!< Others write permission
	SCE_S_IROTH		= 0x0100,  //!< Others read permission
	SCE_S_IRWXO		= 0x01C0,  //!< Others access rights mask

	SCE_S_ISVTX		= 0x0200,  //!< Sticky
	SCE_S_ISGID		= 0x0400,  //!< Set GID
	SCE_S_ISUID		= 0x0800,  //!< Set UID

	SCE_S_IFDIR		= 0x1000,  //!< Directory
	SCE_S_IFREG		= 0x2000,  //!< Regular file
	SCE_S_IFLNK		= 0x4000,  //!< Symbolic link
	SCE_S_IFMT		= 0xF000,  //!< Format bits mask
} SceIoAccessMode;

// File mode checking macros
#define SCE_S_ISLNK(m)	(((m) & SCE_S_IFMT) == SCE_S_IFLNK)
#define SCE_S_ISREG(m)	(((m) & SCE_S_IFMT) == SCE_S_IFREG)
#define SCE_S_ISDIR(m)	(((m) & SCE_S_IFMT) == SCE_S_IFDIR)

/** File modes, used for the st_attr parameter in SceIoStat (confirm?). */
typedef enum SceIoFileMode {
	SCE_SO_IXOTH            = 0x0001,               //!< Hidden execute permission
	SCE_SO_IWOTH            = 0x0002,               //!< Hidden write permission
	SCE_SO_IROTH            = 0x0004,               //!< Hidden read permission
	SCE_SO_IFLNK            = 0x0008,               //!< Symbolic link
	SCE_SO_IFDIR            = 0x0010,               //!< Directory
	SCE_SO_IFREG            = 0x0020,               //!< Regular file
	SCE_SO_IFMT             = 0x0038,               //!< Format mask
} SceIoFileMode;

// File mode checking macros
#define SCE_SO_ISLNK(m)	(((m) & SCE_SO_IFMT) == SCE_SO_IFLNK)
#define SCE_SO_ISREG(m)	(((m) & SCE_SO_IFMT) == SCE_SO_IFREG)
#define SCE_SO_ISDIR(m)	(((m) & SCE_SO_IFMT) == SCE_SO_IFDIR)

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_STAT_H_ */

