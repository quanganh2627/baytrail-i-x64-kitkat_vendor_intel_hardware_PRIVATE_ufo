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
 * This <ufo/gralloc.h> file contains public extensions provided by UFO GRALLOC HAL.
 */

#ifndef INTEL_UFO_GRALLOC_H
#define INTEL_UFO_GRALLOC_H

#include <hardware/gralloc.h>

#ifdef __cplusplus
extern "C" {
#endif

// Enable for FB reference counting.
#define INTEL_UFO_GRALLOC_HAVE_FB_REF_COUNTING 1


/** Operations for the (*perform)() hook
 * \see gralloc_module_t::perform
 */
enum {
    INTEL_UFO_GRALLOC_MODULE_PERFORM_CHECK_VERSION  = 0, // (void)
    INTEL_UFO_GRALLOC_MODULE_PERFORM_GET_DRM_FD     = 1, // (int*)
    INTEL_UFO_GRALLOC_MODULE_PERFORM_SET_DISPLAY    = 2, // (int display, uint32_t width, uint32_t height, uint32_t xdpi, uint32_t ydpi)
    INTEL_UFO_GRALLOC_MODULE_PERFORM_GET_BO_HANDLE  = 3, // (buffer_handle_t, int*)
    INTEL_UFO_GRALLOC_MODULE_PERFORM_GET_BO_NAME    = 4, // (buffer_handle_t, uint32_t*)
    INTEL_UFO_GRALLOC_MODULE_PERFORM_GET_BO_FBID    = 5, // (buffer_handle_t, uint32_t*)
    INTEL_UFO_GRALLOC_MODULE_PERFORM_GET_BO_INFO    = 6, // (buffer_handle_t, buffer_info_t*)
    INTEL_UFO_GRALLOC_MODULE_PERFORM_GET_BO_STATUS  = 7, // (buffer_handle_t)
#if INTEL_UFO_GRALLOC_HAVE_FB_REF_COUNTING
    INTEL_UFO_GRALLOC_MODULE_PERFORM_FB_ACQUIRE     = 8, // (uint32_t)
    INTEL_UFO_GRALLOC_MODULE_PERFORM_FB_RELEASE     = 9, // (uint32_t)
#endif
};


/** Simple version control
 * \see gralloc_module_t::perform
 * \see INTEL_UFO_GRALLOC_MODULE_PERFORM_CHECK_VERSION
 */
enum {
    INTEL_UFO_GRALLOC_MODULE_VERSION_0 = ANDROID_NATIVE_MAKE_CONSTANT('I','N','T','C'),
    INTEL_UFO_GRALLOC_MODULE_VERSION_LATEST = INTEL_UFO_GRALLOC_MODULE_VERSION_0,
};


/** Structure with detailed info about allocated buffer.
 * \see INTEL_UFO_GRALLOC_MODULE_PERFORM_GET_BO_INFO
 */
typedef struct intel_ufo_buffer_details_t
{
    int width;       // \see alloc_device_t::alloc
    int height;      // \see alloc_device_t::alloc
    int format;      // \see alloc_device_t::alloc
    int usage;       // \see alloc_device_t::alloc
    int name;        // flink
    uint32_t fb;     // framebuffer id
    int drmformat;   // drm format
    int pitch;       // buffer pitch (in bytes)
    int size;        // buffer size (in bytes)

    int allocWidth;  // allocated buffer width in pixels.
    int allocHeight; // allocated buffer height in lines.
    int allocOffsetX;// horizontal pixel offset to content origin within allocated buffer.
    int allocOffsetY;// vertical line offset to content origin within allocated buffer.
} intel_ufo_buffer_details_t;


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* INTEL_UFO_GRALLOC_H */
