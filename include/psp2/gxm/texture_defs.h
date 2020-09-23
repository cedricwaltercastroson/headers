/*
	The definitions below may be used to create texture control words directly.
	Please see the GPU User's Guide for more details.  Texture control words
	can be validated in libgxm using #sceGxmTextureValidate().
*/

#ifndef _DOLCESDK_PSP2_GXM_TEXTURE_DEFS_H_
#define _DOLCESDK_PSP2_GXM_TEXTURE_DEFS_H_

#define SCE_GXM_PDS_DOUTT0_TEXFEXT_SHIFT                            31
#define SCE_GXM_PDS_DOUTT0_TEXFEXT_MASK                             0x80000000U
#define SCE_GXM_PDS_DOUTT0_TEXFEXT_CLRMSK                           0x7FFFFFFFU

#define SCE_GXM_PDS_DOUTT0_GAMMA_NONE                               0x00000000U
#define SCE_GXM_PDS_DOUTT0_GAMMA_R                                  0x00000001U
#define SCE_GXM_PDS_DOUTT0_GAMMA_BGR                                0x00000001U
#define SCE_GXM_PDS_DOUTT0_GAMMA_GR                                 0x00000003U
#define SCE_GXM_PDS_DOUTT0_GAMMA_SHIFT                              27
#define SCE_GXM_PDS_DOUTT0_GAMMA_MASK                               0x18000000U
#define SCE_GXM_PDS_DOUTT0_GAMMA_CLRMSK                             0xE7FFFFFFU

#define SCE_GXM_PDS_DOUTT0_STRIDE_ALIGNSHIFT                        2
#define SCE_GXM_PDS_DOUTT0_STRIDEHI_STRIDE_SHIFT                    3
#define SCE_GXM_PDS_DOUTT0_STRIDEHI_SHIFT                           17
#define SCE_GXM_PDS_DOUTT0_STRIDEHI_MASK                            0x07FE0000U
#define SCE_GXM_PDS_DOUTT0_STRIDEHI_CLRMSK                          0xF801FFFFU

#define SCE_GXM_PDS_DOUTT0_STRIDELO_STRIDE_SHIFT                    0
#define SCE_GXM_PDS_DOUTT0_STRIDELO_SHIFT                           9
#define SCE_GXM_PDS_DOUTT0_STRIDELO_MASK                            0x00000E00U
#define SCE_GXM_PDS_DOUTT0_STRIDELO_CLRMSK                          0xFFFFF1FFU

#define SCE_GXM_PDS_DOUTT0_STRIDEEX_STRIDE_SHIFT                    13
#define SCE_GXM_PDS_DOUTT0_STRIDEEX_SHIFT                           1
#define SCE_GXM_PDS_DOUTT0_STRIDEEX_MASK                            0x00000006U
#define SCE_GXM_PDS_DOUTT0_STRIDEEX_CLRMSK                          0xFFFFFFF9U

#define SCE_GXM_PDS_DOUTT0_DADJUST_MIN                              0x00000000U
#define SCE_GXM_PDS_DOUTT0_DADJUST_ZERO                             0x0000001FU
#define SCE_GXM_PDS_DOUTT0_DADJUST_MAX                              0x0000003FU
#define SCE_GXM_PDS_DOUTT0_DADJUST_SHIFT                            21
#define SCE_GXM_PDS_DOUTT0_DADJUST_MASK                             0x07E00000U
#define SCE_GXM_PDS_DOUTT0_DADJUST_CLRMSK                           0xF81FFFFFU

#define SCE_GXM_PDS_DOUTT0_MIPMAPCLAMP_MIN                          0x00000000U
#define SCE_GXM_PDS_DOUTT0_MIPMAPCLAMP_MAX                          0x0000000CU
#define SCE_GXM_PDS_DOUTT0_MIPMAPCLAMP_NOTMIPMAP                    0x0000000FU
#define SCE_GXM_PDS_DOUTT0_MIPMAPCLAMP_SHIFT                        17
#define SCE_GXM_PDS_DOUTT0_MIPMAPCLAMP_MASK                         0x001E0000U
#define SCE_GXM_PDS_DOUTT0_MIPMAPCLAMP_CLRMSK                       0xFFE1FFFFU

#define SCE_GXM_PDS_DOUTT0_MINFILTER_SHIFT                          10
#define SCE_GXM_PDS_DOUTT0_MINFILTER_MASK                           0x00000400U
#define SCE_GXM_PDS_DOUTT0_MINFILTER_CLRMSK                         0xFFFFFBFFU

#define SCE_GXM_PDS_DOUTT0_MIPFILTER_SHIFT                          9
#define SCE_GXM_PDS_DOUTT0_MIPFILTER_MASK                           0x00000200U
#define SCE_GXM_PDS_DOUTT0_MIPFILTER_CLRMSK                         0xFFFFFDFFU

#define SCE_GXM_PDS_DOUTT0_MAGFILTER_SHIFT                          12
#define SCE_GXM_PDS_DOUTT0_MAGFILTER_MASK                           0x00001000U
#define SCE_GXM_PDS_DOUTT0_MAGFILTER_CLRMSK                         0xFFFFEFFFU

#define SCE_GXM_PDS_DOUTT0_UADDRMODE_REPEAT                         0x00000000U
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_MIRROR                         0x00000001U
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_CLAMP                          0x00000002U
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_MIRROR_CLAMP                   0x00000003U
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_REPEAT_IGNORE_BORDER           0x00000004U
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_CLAMP_FULL_BORDER              0x00000005U
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_CLAMP_IGNORE_BORDER            0x00000006U
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_CLAMP_HALF_BORDER              0x00000007U
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_SHIFT                          6
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_MASK                           0x000001C0U
#define SCE_GXM_PDS_DOUTT0_UADDRMODE_CLRMSK                         0xFFFFFE3FU

#define SCE_GXM_PDS_DOUTT0_VADDRMODE_REPEAT                         0x00000000U
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_MIRROR                         0x00000001U
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_CLAMP                          0x00000002U
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_MIRROR_CLAMP                   0x00000003U
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_REPEAT_IGNORE_BORDER           0x00000004U
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_CLAMP_FULL_BORDER              0x00000005U
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_CLAMP_IGNORE_BORDER            0x00000006U
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_CLAMP_HALF_BORDER              0x00000007U
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_SHIFT                          3
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_MASK                           0x00000038U
#define SCE_GXM_PDS_DOUTT0_VADDRMODE_CLRMSK                         0xFFFFFFC7U

#define SCE_GXM_PDS_DOUTT1_TEXTYPE_SWIZZLED                         0x00000000U
#define SCE_GXM_PDS_DOUTT1_TEXTYPE_CUBE                             0x00000002U
#define SCE_GXM_PDS_DOUTT1_TEXTYPE_LINEAR                           0x00000003U
#define SCE_GXM_PDS_DOUTT1_TEXTYPE_TILED                            0x00000004U
#define SCE_GXM_PDS_DOUTT1_TEXTYPE_SWIZZLED_ARBITRARY               0x00000005U
#define SCE_GXM_PDS_DOUTT1_TEXTYPE_LINEAR_STRIDED                   0x00000006U
#define SCE_GXM_PDS_DOUTT1_TEXTYPE_CUBE_ARBITRARY                   0x00000007U
#define SCE_GXM_PDS_DOUTT1_TEXTYPE_SHIFT                            29
#define SCE_GXM_PDS_DOUTT1_TEXTYPE_MASK                             0xE0000000U
#define SCE_GXM_PDS_DOUTT1_TEXTYPE_CLRMSK                           0x1FFFFFFFU

#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U8                             0x00000000U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_S8                             0x00000001U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U4U4U4U4                       0x00000002U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U8U3U3U2                       0x00000003U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U1U5U5U5                       0x00000004U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U5U6U5                         0x00000005U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_S5S5U6                         0x00000006U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U8U8                           0x00000007U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_S8S8                           0x00000008U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U16                            0x00000009U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_S16                            0x0000000AU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_F16                            0x0000000BU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U8U8U8U8                       0x0000000CU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_S8S8S8S8                       0x0000000DU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U2U10U10U10                    0x0000000EU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U16U16                         0x0000000FU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_S16S16                         0x00000010U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_F16F16                         0x00000011U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_F32                            0x00000012U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_F32M                           0x00000013U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_X8S8S8U8                       0x00000014U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_X8U24                          0x00000015U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U32                            0x00000017U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_S32                            0x00000018U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_SE5M9M9M9                      0x00000019U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_F11F11F10                      0x0000001AU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_F16F16F16F16                   0x0000001BU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U16U16U16U16                   0x0000001CU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_S16S16S16S16                   0x0000001DU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_F32F32                         0x0000001EU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U32U32                         0x0000001FU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_PVRT2BPP                       0x00000000U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_PVRT4BPP                       0x00000001U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_PVRTII2BPP                     0x00000002U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_PVRTII4BPP                     0x00000003U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_UBC1                           0x00000005U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_UBC2                           0x00000006U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_UBC3                           0x00000007U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_UBC4                           0x00000008U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_SBC4                           0x00000009U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_UBC5                           0x0000000AU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_SBC5                           0x0000000BU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_YUV420P2                       0x00000010U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_YUV420P3                       0x00000011U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_YUV422                         0x00000012U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_P4                             0x00000014U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_P8                             0x00000015U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U8U8U8                         0x00000018U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_S8S8S8                         0x00000019U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_U2F10F10F10                    0x0000001AU
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_SHIFT                          24
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_MASK                           0x1F000000U
#define SCE_GXM_PDS_DOUTT1_TEXFORMAT_CLRMSK                         0xE0FFFFFFU

#define SCE_GXM_PDS_DOUTT1_USIZE_MIN                                0x00000000U
#define SCE_GXM_PDS_DOUTT1_USIZE_MAX                                0x0000000CU
#define SCE_GXM_PDS_DOUTT1_USIZE_SHIFT                              16
#define SCE_GXM_PDS_DOUTT1_USIZE_MASK                               0x000F0000U
#define SCE_GXM_PDS_DOUTT1_USIZE_CLRMSK                             0xFFF0FFFFU

#define SCE_GXM_PDS_DOUTT1_VSIZE_MIN                                0x00000000U
#define SCE_GXM_PDS_DOUTT1_VSIZE_MAX                                0x0000000CU
#define SCE_GXM_PDS_DOUTT1_VSIZE_SHIFT                              0
#define SCE_GXM_PDS_DOUTT1_VSIZE_MASK                               0x0000000FU
#define SCE_GXM_PDS_DOUTT1_VSIZE_CLRMSK                             0xFFFFFFF0U

#define SCE_GXM_PDS_DOUTT1_WIDTH_SHIFT                              12
#define SCE_GXM_PDS_DOUTT1_WIDTH_MASK                               0x00FFF000U
#define SCE_GXM_PDS_DOUTT1_WIDTH_CLRMSK                             0xFF000FFFU

#define SCE_GXM_PDS_DOUTT1_HEIGHT_SHIFT                             0
#define SCE_GXM_PDS_DOUTT1_HEIGHT_MASK                              0x00000FFFU
#define SCE_GXM_PDS_DOUTT1_HEIGHT_CLRMSK                            0xFFFFF000U

#define SCE_GXM_PDS_DOUTT2_TEXADDR_ALIGNSHIFT                       2
#define SCE_GXM_PDS_DOUTT2_TEXADDR_SHIFT                            2
#define SCE_GXM_PDS_DOUTT2_TEXADDR_MASK                             0xFFFFFFFCU
#define SCE_GXM_PDS_DOUTT2_TEXADDR_CLRMSK                           0x00000003U

#define SCE_GXM_PDS_DOUTT2_LODMINHI_LOD_SHIFT                       2
#define SCE_GXM_PDS_DOUTT2_LODMINHI_SHIFT                           0
#define SCE_GXM_PDS_DOUTT2_LODMINHI_MASK                            0x00000003U
#define SCE_GXM_PDS_DOUTT2_LODMINHI_CLRMSK                          0xFFFFFFFCU

#define SCE_GXM_PDS_DOUTT3_NORM_SHIFT                               31
#define SCE_GXM_PDS_DOUTT3_NORM_MASK                                0x80000000U
#define SCE_GXM_PDS_DOUTT3_NORM_CLRMSK                              0x7FFFFFFFU

#define SCE_GXM_PDS_DOUTT3_SWIZ_ABGR                                0x00000000U
#define SCE_GXM_PDS_DOUTT3_SWIZ_ARGB                                0x00000001U
#define SCE_GXM_PDS_DOUTT3_SWIZ_RGBA                                0x00000002U
#define SCE_GXM_PDS_DOUTT3_SWIZ_BGRA                                0x00000003U
#define SCE_GXM_PDS_DOUTT3_SWIZ_1BGR                                0x00000004U
#define SCE_GXM_PDS_DOUTT3_SWIZ_1RGB                                0x00000005U
#define SCE_GXM_PDS_DOUTT3_SWIZ_RGB1                                0x00000006U
#define SCE_GXM_PDS_DOUTT3_SWIZ_BGR1                                0x00000007U
#define SCE_GXM_PDS_DOUTT3_SWIZ_BGR                                 0x00000000U
#define SCE_GXM_PDS_DOUTT3_SWIZ_RGB                                 0x00000001U
#define SCE_GXM_PDS_DOUTT3_SWIZ_GR                                  0x00000000U
#define SCE_GXM_PDS_DOUTT3_SWIZ_00GR                                0x00000001U
#define SCE_GXM_PDS_DOUTT3_SWIZ_GRRR                                0x00000002U
#define SCE_GXM_PDS_DOUTT3_SWIZ_RGGG                                0x00000003U
#define SCE_GXM_PDS_DOUTT3_SWIZ_GRGR                                0x00000004U
#define SCE_GXM_PDS_DOUTT3_SWIZ_00RG                                0x00000005U
#define SCE_GXM_PDS_DOUTT3_SWIZ_SD                                  0x00000000U
#define SCE_GXM_PDS_DOUTT3_SWIZ_DS                                  0x00000001U
#define SCE_GXM_PDS_DOUTT3_SWIZ_R                                   0x00000000U
#define SCE_GXM_PDS_DOUTT3_SWIZ_000R                                0x00000001U
#define SCE_GXM_PDS_DOUTT3_SWIZ_111R                                0x00000002U
#define SCE_GXM_PDS_DOUTT3_SWIZ_RRRR                                0x00000003U
#define SCE_GXM_PDS_DOUTT3_SWIZ_0RRR                                0x00000004U
#define SCE_GXM_PDS_DOUTT3_SWIZ_1RRR                                0x00000005U
#define SCE_GXM_PDS_DOUTT3_SWIZ_R000                                0x00000006U
#define SCE_GXM_PDS_DOUTT3_SWIZ_R111                                0x00000007U
#define SCE_GXM_PDS_DOUTT3_SWIZ_YUYV_CSC0                           0x00000000U
#define SCE_GXM_PDS_DOUTT3_SWIZ_YVYU_CSC0                           0x00000001U
#define SCE_GXM_PDS_DOUTT3_SWIZ_UYVY_CSC0                           0x00000002U
#define SCE_GXM_PDS_DOUTT3_SWIZ_VYUY_CSC0                           0x00000003U
#define SCE_GXM_PDS_DOUTT3_SWIZ_YUYV_CSC1                           0x00000004U
#define SCE_GXM_PDS_DOUTT3_SWIZ_YVYU_CSC1                           0x00000005U
#define SCE_GXM_PDS_DOUTT3_SWIZ_UYVY_CSC1                           0x00000006U
#define SCE_GXM_PDS_DOUTT3_SWIZ_VYUY_CSC1                           0x00000007U
#define SCE_GXM_PDS_DOUTT3_SWIZ_YUV_CSC0                            0x00000000U
#define SCE_GXM_PDS_DOUTT3_SWIZ_YVU_CSC0                            0x00000001U
#define SCE_GXM_PDS_DOUTT3_SWIZ_YUV_CSC1                            0x00000002U
#define SCE_GXM_PDS_DOUTT3_SWIZ_YVU_CSC1                            0x00000003U
#define SCE_GXM_PDS_DOUTT3_SWIZ_SHIFT                               28
#define SCE_GXM_PDS_DOUTT3_SWIZ_MASK                                0x70000000U
#define SCE_GXM_PDS_DOUTT3_SWIZ_CLRMSK                              0x8FFFFFFFU

#define SCE_GXM_PDS_DOUTT3_LODMINLO_LOD_SHIFT                       0
#define SCE_GXM_PDS_DOUTT3_LODMINLO_SHIFT                           26
#define SCE_GXM_PDS_DOUTT3_LODMINLO_MASK                            0x0C000000U
#define SCE_GXM_PDS_DOUTT3_LODMINLO_CLRMSK                          0xF3FFFFFFU

#define SCE_GXM_PDS_DOUTT3_PALETTEADDR_ALIGNSHIFT                   6
#define SCE_GXM_PDS_DOUTT3_PALETTEADDR_SHIFT                        0
#define SCE_GXM_PDS_DOUTT3_PALETTEADDR_MASK                         0x03FFFFFFU
#define SCE_GXM_PDS_DOUTT3_PALETTEADDR_CLRMSK                       0xFC000000U

#define SCE_GXM_PDS_DOUTT0_VALIDMASK                                0x9FFE1FFEU
#define SCE_GXM_PDS_DOUTT1_VALIDMASK                                0xFFFFFFFFU
#define SCE_GXM_PDS_DOUTT2_VALIDMASK                                0xFFFFFFFFU
#define SCE_GXM_PDS_DOUTT3_VALIDMASK                                0xFFFFFFFFU

#endif /* _DOLCESDK_PSP2_GXM_TEXTURE_DEFS_H_ */

