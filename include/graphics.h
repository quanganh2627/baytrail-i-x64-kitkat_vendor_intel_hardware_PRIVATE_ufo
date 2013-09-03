/*
 * INTEL CONFIDENTIAL
 *
 * Copyright 2013 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to the
 * source code ("Material") are owned by Intel Corporation or its suppliers or
 * licensors. Title to the Material remains with Intel Corporation or its suppliers
 * and licensors. The Material contains trade secrets and proprietary and confidential
 * information of Intel or its suppliers and licensors. The Material is protected by
 * worldwide copyright and trade secret laws and treaty provisions. No part of the
 * Material may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intels prior express
 * written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or delivery
 * of the Materials, either expressly, by implication, inducement, estoppel
 * or otherwise. Any license under such intellectual property rights must be
 * express and approved by Intel in writing.
 *
 */

/**
 * This <ufo/graphics.h> file contains UFO specific pixel formats.
 *
 * \remark This file is Android specific
 * \remark Do not put any internal definitions here!
 */

#ifndef INTEL_UFO_GRAPHICS_H
#define INTEL_UFO_GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * UFO specific pixel format definitions
 *
 * Range 0x100 - 0x1FF is reserved for pixel formats specific to the HAL implementation
 *
 * \see #include <system/graphics.h>
 */
enum {
    /**
     * A format in which all Y samples are found first in memory as an array
     * of unsigned char with an even number of lines (possibly with a larger
     * stride for memory alignment). This is followed immediately by an array
     * of unsigned char containing interleaved Cb and Cr samples. If these
     * samples are addressed as a little-endian WORD type, Cb would be in the
     * least significant bits and Cr would be in the most significant bits
     * with the same total stride as the Y samples.
     * NV12 is the preferred 4:2:0 pixel format.
     */
    HAL_PIXEL_FORMAT_NV12_TILED_INTEL = 0x100,

    /**
     * \todo
     *
     * Same as NV12_INTEL, but with additional restrictions:
     * - tiling: linear
     * - pitch: 512, 1024, 1280, 2048, 4096
     * - height: need be 32 aligned
     */
    HAL_PIXEL_FORMAT_NV12_LINEAR_INTEL = 0x101,

    /**
     * \deprecated alias name for use by legacy apps only
     * \see HAL_PIXEL_FORMAT_NV12_TILED_INTEL
     */
    HAL_PIXEL_FORMAT_NV12_INTEL = HAL_PIXEL_FORMAT_NV12_TILED_INTEL,

    /**
     * \deprecated alias name for use by legacy apps only
     * \see HAL_PIXEL_FORMAT_NV12_INTEL
     */
    HAL_PIXEL_FORMAT_INTEL_NV12 = HAL_PIXEL_FORMAT_NV12_INTEL,

    /**
     * HAL_PIXEL_FORMAT_YCrCb_422_H_INTEL is not defined in 
     * ./system/core/include/system/graphics.h
     */
    HAL_PIXEL_FORMAT_YCrCb_422_H_INTEL = 0x102, // YV16

    /**
     * for the PACKED mode, pitch=width and no need any alignment for height
     */
    HAL_PIXEL_FORMAT_NV12_LINEAR_PACKED_INTEL = 0x103,
    
    /**
     * \note THIS WILL BE GOING AWAY!
     *
     * \deprecated value out of range of reserved pixel formats
     * \see #include <openmax/OMX_IVCommon.h>
     * \see OMX_INTEL_COLOR_FormatYUV420PackedSemiPlanar
     */
    HAL_PIXEL_FORMAT_YUV420PackedSemiPlanar_INTEL = 0x7FA00E00,

    /**
     * \note THIS WILL BE GOING AWAY!
     *
     * \deprecated value out of range of reserved pixel formats
     * \see #include <openmax/OMX_IVCommon.h>
     * \see OMX_INTEL_COLOR_FormatYUV420PackedSemiPlanar
     */
    HAL_PIXEL_FORMAT_YUV420PackedSemiPlanar_Tiled_INTEL = 0x7FA00F00,
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* INTEL_UFO_GRAPHICS_H */
