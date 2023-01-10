/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PICO_SCANVIDEO_H_
#define PICO_SCANVIDEO_H_

// note that defining to false will force non-inclusion also
#if !defined(PICO_SCANVIDEO_DPI)
//#define PICO_SCANVIDEO_DPI 1

#ifndef PARAM_ASSERTIONS_ENABLED_SCANVIDEO_DPI
#define PARAM_ASSERTIONS_ENABLED_SCANVIDEO_DPI 0
#endif

#include "scanvideo_base.h"

//used within scanvideo.c  lines 440+
#ifndef PICO_SCANVIDEO_DPI_PIXEL_RSHIFT
#define PICO_SCANVIDEO_DPI_PIXEL_RSHIFT 0u //0u
#endif

#ifndef PICO_SCANVIDEO_DPI_PIXEL_GSHIFT
#define PICO_SCANVIDEO_DPI_PIXEL_GSHIFT 6u //3u
#endif

#ifndef PICO_SCANVIDEO_DPI_PIXEL_BSHIFT
#define PICO_SCANVIDEO_DPI_PIXEL_BSHIFT 11u //6u
#endif

//used within scanvideo.c  lines 445+
#ifndef PICO_SCANVIDEO_DPI_PIXEL_RCOUNT
#define PICO_SCANVIDEO_DPI_PIXEL_RCOUNT 5 //3
#endif

#ifndef PICO_SCANVIDEO_DPI_PIXEL_GCOUNT
#define PICO_SCANVIDEO_DPI_PIXEL_GCOUNT 5 //3
#endif

#ifndef PICO_SCANVIDEO_DPI_PIXEL_BCOUNT
#define PICO_SCANVIDEO_DPI_PIXEL_BCOUNT 5 //2
#endif

#ifndef PICO_SCANVIDEO_PIXEL_RSHIFT
#define PICO_SCANVIDEO_PIXEL_RSHIFT PICO_SCANVIDEO_DPI_PIXEL_RSHIFT
#endif

#ifndef PICO_SCANVIDEO_PIXEL_GSHIFT
#define PICO_SCANVIDEO_PIXEL_GSHIFT PICO_SCANVIDEO_DPI_PIXEL_GSHIFT
#endif

#ifndef PICO_SCANVIDEO_PIXEL_BSHIFT
#define PICO_SCANVIDEO_PIXEL_BSHIFT PICO_SCANVIDEO_DPI_PIXEL_BSHIFT
#endif

#ifndef PICO_SCANVIDEO_PIXEL_RCOUNT
#define PICO_SCANVIDEO_PIXEL_RCOUNT PICO_SCANVIDEO_DPI_PIXEL_RCOUNT
#endif

#ifndef PICO_SCANVIDEO_PIXEL_GCOUNT
#define PICO_SCANVIDEO_PIXEL_GCOUNT PICO_SCANVIDEO_DPI_PIXEL_GCOUNT
#endif

#ifndef PICO_SCANVIDEO_PIXEL_BCOUNT
#define PICO_SCANVIDEO_PIXEL_BCOUNT PICO_SCANVIDEO_DPI_PIXEL_BCOUNT
#endif




#ifndef PICO_SCANVIDEO_PIXEL_FROM_RGB8
#define PICO_SCANVIDEO_PIXEL_FROM_RGB8(r, g, b) ((((b)>>3u)<<PICO_SCANVIDEO_PIXEL_BSHIFT)|(((g)>>3u)<<PICO_SCANVIDEO_PIXEL_GSHIFT)|(((r)>>3u)<<PICO_SCANVIDEO_PIXEL_RSHIFT))
#endif

#ifndef PICO_SCANVIDEO_PIXEL_FROM_RGB5
#define PICO_SCANVIDEO_PIXEL_FROM_RGB5(r, g, b) (((b)<<PICO_SCANVIDEO_PIXEL_BSHIFT)|((g)<<PICO_SCANVIDEO_PIXEL_GSHIFT)|((r)<<PICO_SCANVIDEO_PIXEL_RSHIFT))
#endif

#ifndef PICO_SCANVIDEO_R5_FROM_PIXEL
#define PICO_SCANVIDEO_R5_FROM_PIXEL(p) (((p)>>PICO_SCANVIDEO_PIXEL_RSHIFT)&0x1f)
#endif

#ifndef PICO_SCANVIDEO_G5_FROM_PIXEL
#define PICO_SCANVIDEO_G5_FROM_PIXEL(p) (((p)>>PICO_SCANVIDEO_PIXEL_GSHIFT)&0x1f)
#endif

#ifndef PICO_SCANVIDEO_B5_FROM_PIXEL
#define PICO_SCANVIDEO_B5_FROM_PIXEL(p) (((p)>>PICO_SCANVIDEO_PIXEL_BSHIFT)&0x1f)
#endif

/** \file scanvideo.h
 *  \defgroup pico_scanvideo_dpi pico_scanvideo_dpi
 *
 * DPI Scan-out Video using the PIO
 */

#endif
#endif
