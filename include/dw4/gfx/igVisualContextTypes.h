#ifndef DW4_IGVISUALCONTEXTTYPES_H
#define DW4_IGVISUALCONTEXTTYPES_H

#ifdef __cplusplus
#include "dw4/gfx/GfxMetaEnums.h"

/* The structures igVisualContext's slots take (alchemy-kit_202309 include/igGfx/igVisualContext.h), in the
 * revision DW4 was built from: the render destination format has no front-buffer, back-buffer, flag or
 * multisample fields (it is eight words), and the video format ends at the video type. */
struct igRenderDestinationFormat {
    IG_GFX_RENDERDESTINATION_TYPE _iType;
    int _iWidth;
    int _iHeight;
    int _iColorBitsPerPixel;
    int _iAlphaBitsPerPixel;
    int _iDepthBitsPerPixel;
    int _iStencilBitsPerPixel;
    float _fPixelAspectRatio;
};

/* The mode a visual context is set to or reports: full screen, interlaced with its field count and size, the
 * refresh rate in Hz (NTSC 59.94, PAL 50), the swap interval in vertical retraces and the video type (0 NTSC).
 * The constructor is the kit's, which leaves the field count and size unset. */
struct igVideoFormat {
    bool _bFullScreen;
    bool _bInterlaced;
    int _iFieldCount;
    int _iFieldSize;
    float _fRefreshRate;
    int _iSwapInterval;
    int _iVideoType;

    inline igVideoFormat() {
        _iVideoType = 0;
        _bFullScreen = false;
        _bInterlaced = false;
        _fRefreshRate = 0.0f;
        _iSwapInterval = 0;
    }
};
#endif

#endif
