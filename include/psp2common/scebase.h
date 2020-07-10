/**
 * \usergroup{SceBase}
 * \usage{psp2common/scebase.h}
 */

#ifndef _DOLCESDK_PSP2COMMON_SCEBASE_H_
#define _DOLCESDK_PSP2COMMON_SCEBASE_H_

#define SCE_PSP2_SDK_VERSION 0x03570011

#ifndef SCE_OK
#define SCE_OK 0
#endif

#define _SCE_MACRO_BEGIN       do {
#define _SCE_MACRO_END         } while (0)

#define _SCE_ALIGN_BEG(x)
#define _SCE_ALIGN_END(x)      __attribute__((__aligned__(x)))

#define _SCE_EXPECT(expr, val) __builtin_expect((expr), (val))

#define _SCE_BREAK()           _SCE_MACRO_BEGIN { __asm__ volatile ("bkpt 0x0000"); } _SCE_MACRO_END
#define _SCE_STOP()            _SCE_MACRO_BEGIN { __asm__ volatile ("bkpt 0x0002"); } _SCE_MACRO_END
#define _SCE_NORETURN_STOP()   _SCE_MACRO_BEGIN { __asm__ volatile ("bkpt 0x0001"); } _SCE_MACRO_END

#define _SCE_UNLIKELY(expr)    _SCE_EXPECT(expr, 0)
#define _SCE_LIKELY(expr)      _SCE_EXPECT(expr, 1)

#endif // _DOLCESDK_PSP2COMMON_SCEBASE_H_
