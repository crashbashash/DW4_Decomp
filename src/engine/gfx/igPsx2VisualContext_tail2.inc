void FUN_00169260(Gap::Gfx::igPsx2VisualContext *vc, int keepPool) {
    int handle;
    igPsx2RenderDestinationPool *pool;
    handle = ((igPsx2RenderDestinationPool *)vc->_pBufList)->capacity - 1;
    for (; handle > -1; handle--) {
        if (((igPsx2RenderDestinationPool *)vc->_pBufList)->isIndexAllocated(handle)) {
            ((igPsx2RenderDestinationPool *)vc->_pBufList)->freeElement(handle);
        }
    }
    if (keepPool == 0) {
        pool = (igPsx2RenderDestinationPool *)vc->_pBufList;
        delete pool;
        vc->_pBufList = 0;
    }
    vc->_currentBuf = -1;
}

/* The destination a handle names, addressed in bytes from the pool's element array. */
static inline igPsx2RenderDestination *destinationAt(igPsx2RenderDestinationPool *pool, int handle) {
    return (igPsx2RenderDestination *)((int)pool->elements + handle * sizeof(igPsx2RenderDestination));
}

/* A word of a destination read through the pool as an igDataList: the element array's address plus a byte offset
 * (the compiler's address arithmetic differs from indexing the typed element array). */
static inline int *destinationWord(::igDataList *pool, int handle, int field) {
    return (int *)(pool->_data + handle * (int)sizeof(igPsx2RenderDestination) + field);
}

namespace Gap {
namespace Gfx {

int igPsx2VisualContext::createRenderDestination(igRenderDestinationFormat *pFormat) {
    igPsx2RenderDestination *destination;
    int handle;
    handle = ((igPsx2RenderDestinationPool *)_pBufList)->getFreeElement();
    destination = ((igPsx2RenderDestinationPool *)_pBufList)->elements + handle;
    destination->type = pFormat->_iType;
    destination->width = pFormat->_iWidth;
    destination->height = pFormat->_iHeight;
    destination->colorBitsPerPixel = pFormat->_iColorBitsPerPixel;
    destination->alphaBitsPerPixel = pFormat->_iAlphaBitsPerPixel;
    destination->depthBitsPerPixel = pFormat->_iDepthBitsPerPixel;
    destination->stencilBitsPerPixel = pFormat->_iStencilBitsPerPixel;
    destination->pixelAspectRatio = pFormat->_fPixelAspectRatio;
    destination->colorTarget = 0;
    destination->depthTarget = 0;
    destination->textureHandle = -1;
    _currentBuf = handle;
    return handle;
}

void igPsx2VisualContext::deleteRenderDestination(int handle) {
    int textureHandle;
    igPsx2RenderDestinationPool *pool;
    igPsx2RenderDestinationPool *current;

    pool = (igPsx2RenderDestinationPool *)_pBufList;
    /* matching construct: the record's address in bytes from the element array, as the getters read it */
    textureHandle = *destinationWord((::igDataList *)pool, handle, offsetof(igPsx2RenderDestination, textureHandle));
    if (-1 < textureHandle) {
        /* matching construct: the call to deleteTexture leaves the pool in its second argument register */
        ((DW4VC_524 *)this)->vX(textureHandle, pool);
    }
    current = (igPsx2RenderDestinationPool *)_pBufList;
    current->freeElement(handle);
}

void igPsx2VisualContext::setRenderDestination(int iHandle, int unused) {
    igPsx2RenderDestination *destinations;
    igPsx2RenderDestination *destination;
    igPsx2RenderDestination *current;
    int type;
    destinations = ((igPsx2RenderDestinationPool *)_pBufList)->elements;
    destination = destinations + iHandle;
    current = destinations + _currentBuf;
    type = destination->type;
    if (type != 2 && current->type == 2) {
        p2RestoreRenderTarget();
        p2SetViewport(_iViewportX, _iViewportY, _iViewportW, _iViewportH, 1.0f - _viewportNear, 1.0f - _viewportFar);
    } else if (type == 2) {
        p2SetRenderTarget((P2Texture *)destination->colorTarget, (P2Texture *)destination->depthTarget);
        p2SetViewport(0, 0, destination->width, destination->height, 1.0f - _viewportNear, 1.0f - _viewportFar);
    }
    _currentBuf = iHandle;
    FUN_0016a520(this);
    if (destination->depthBitsPerPixel <= 0) {
        setDepthTestState(false);
        return;
    }
    setDepthTestState(true);
}

void igPsx2VisualContext::setRenderDestination(int iHandle, int *piTex, int unused) {
    int index;
    int format;
    bool create;
    igPsx2TextureRecord *tex;
    int colorFormat;
    igPsx2RenderDestination *buf;
    buf = &((igPsx2RenderDestinationPool *)_pBufList)->elements[iHandle];
    tex = 0;
    index = *piTex;
    create = false;
    if (index == -1) {
        create = true;
    } else {
        tex = &((igPsx2TexturePool *)_pTexList)->elements[index];
        if (*tex->buffers == 0) {
            create = true;
        }
    }
    if (create) {
        switch (buf->colorBitsPerPixel) {
        case 16:
        case 15:
            colorFormat = 3;
            format = 8;
            break;
        case 24:
            if (buf->alphaBitsPerPixel == 0) {
                colorFormat = 1;
                format = 5;
            } else {
                colorFormat = 0;
                format = 7;
            }
            break;
        case 7:
        case 8:
        default:
            colorFormat = 0;
            format = 7;
            break;
        }
        if (index == -1) {
            *piTex = allocateTexture(buf->width, buf->height, format, 3, 0, 1);
            buf->textureHandle = *piTex;
            tex = &((igPsx2TexturePool *)_pTexList)->elements[*piTex];
        }
        if (buf->colorTarget != 0) {
            unloadTexture(buf->textureHandle);
        }
        if (buf->depthBitsPerPixel > 0) {
            int depthFormat;
            switch (buf->depthBitsPerPixel) {
            case 16:
            default:
                depthFormat = 12;
                break;
            case 24:
                depthFormat = 10;
                break;
            case 32:
                depthFormat = 9;
                break;
            }
            buf->depthTarget = (int)p2LoadTexture(0, buf->width, buf->height, depthFormat, 0);
        }
        buf->colorTarget = (int)p2LoadTexture(0, buf->width, buf->height, colorFormat, 0);
        if (buf->colorTarget != 0) {
            *tex->buffers = buf->colorTarget;
            tex->buffer = buf->depthTarget;
            tex->state = 2;
        } else {
            deleteTexture(*piTex);
            *piTex = -1;
            return;
        }
    }
    p2SetRenderTarget((P2Texture *)buf->colorTarget, (P2Texture *)buf->depthTarget);
    _currentBuf = iHandle;
    p2SetViewport(0, 0, buf->width, buf->height, 1.0f - _viewportNear, 1.0f - _viewportFar);
    FUN_0016a520(this);
    if (buf->depthBitsPerPixel <= 0) {
        setDepthTestState(false);
        return;
    }
    setDepthTestState(true);
}

void igPsx2VisualContext::getRenderDestinationSize(int iHandle, int &piWidth, int &piHeight) const {
    piWidth = destinationAt((igPsx2RenderDestinationPool *)_pBufList, iHandle)->width;
    piHeight = destinationAt((igPsx2RenderDestinationPool *)_pBufList, iHandle)->height;
}

bool igPsx2VisualContext::setRenderDestinationSize(int iHandle, int iWidth, int iHeight) {
    destinationAt((igPsx2RenderDestinationPool *)_pBufList, iHandle)->width = iWidth;
    destinationAt((igPsx2RenderDestinationPool *)_pBufList, iHandle)->height = iHeight;
    return 1;
}

int igPsx2VisualContext::getCurrentRenderDestination() const {
    return _currentBuf;
}

IG_GFX_RENDERDESTINATION_TYPE igPsx2VisualContext::getRenderDestinationType(int iHandle) const {
    return (IG_GFX_RENDERDESTINATION_TYPE)*destinationWord((::igDataList *)_pBufList, iHandle, offsetof(igPsx2RenderDestination, type));
}
}
}

void FUN_00169be0(Gap::Gfx::igPsx2VisualContext *vc, int mode) {
    if (mode == 1) {
        p2SetClearWidth(0x40);
        return;
    }
    p2SetClearWidth(0);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::clearRenderDestination(unsigned int which) {
    int buffers;

    buffers = 0;
    if (which & 1) {
        buffers |= 1;
    }
    if (which & 2) {
        buffers |= 2;
    }
    /* matching construct: retail loads the clear depth before the clear colour; the fields read as raw words do that */
    p2Clear(buffers, *(int *)&_uiClearColor, *(int *)&_uiClearDepth);
}

bool igPsx2VisualContext::copyRenderDestinationToTexture(int srcHandle, int hTexture, int srcX, int srcY, int width, int height, int destX, int destY) {
    igPsx2RenderDestination *source;
    igPsx2TextureRecord *texture;
    int filter;

    source = &((igPsx2RenderDestinationPool *)_pBufList)->elements[srcHandle];
    texture = &((igPsx2TexturePool *)_pTexList)->elements[hTexture];
    if (*texture->buffers == 0) {
        *texture->buffers = (int)p2LoadTexture(0, texture->width, texture->height, igPsx2TextureFormat_GetP2Format(texture->format), 0);
    }
    if ((destX == -1) || (destY == -1)) {
        if (_textureStateFilter != 0) {
            filter = (_textureMagFilter << 0x10) | _textureMinFilter;
            if (_currentTextureFilter[0] != filter) {
                _currentTextureFilter[0] = filter;
                p2SetTextureFilter(DAT_0048acd0[_textureMagFilter], DAT_0048acd0[_textureMinFilter]);
            }
        }
        FUN_00209cf0(source->colorTarget, *texture->buffers, srcX, srcY, width, height, 0);
    } else if (source->type == 2) {
        p2CopyTexture((void *)source->colorTarget, srcX, srcY, (void *)*texture->buffers, destX, destY, width, height);
    } else {
        p2CopyFramebufferToTexture((P2Texture *)*texture->buffers, srcX, srcY, destX, destY, width, height, 0);
    }
    texture->state = 3;
    return 1;
}

bool igPsx2VisualContext::copyRenderDestinationToMemory(int srcHandle, igImage *destImage, int srcX, int srcY, int width, int height) {
    return readRenderDestination(srcHandle, destImage, srcX, srcY, width, height, 0);
}

/* Reads the width x height region at (x, y) of render destination `handle` into `image`: into the image's own
 * memory when it is 16-byte aligned and sized, else through a temporary buffer from the image memory pool. */
/* matching construct: a small sweep of spellings */
bool igPsx2VisualContext::readRenderDestination(int handle, igImage *image, int x, int y, int width, int height, int flags) {
    void *pixels;
    igPsx2RenderDestination *destination;
    destination = &((igPsx2RenderDestinationPool *)_pBufList)->elements[handle];
    pixels = image->_pImage;
    bool allocated = false;
    int format;
    if (pixels == 0 || image->_imageSize < 0 || ((int)pixels & 15) != 0) {
        pixels = ((igMemoryPoolView *)this->getImageMemoryPool())->AllocateAligned(width * height * 4, 16);
        allocated = true;
    }
    if (destination->type == 2) {
        FUN_00203c50(x, y, width, height, destination->colorTarget, pixels, flags);
        format = ((igPsx2TexturePool *)_pTexList)->elements[destination->textureHandle].format;
    } else {
        FUN_00203580(x, y, width, height, 1, pixels, flags);
        if (destination->colorBitsPerPixel == 32) {
            format = 7;
        } else if (destination->colorBitsPerPixel == 24) {
            if (destination->alphaBitsPerPixel) {
                format = 7;
            } else {
                format = 5;
            }
        } else if (destination->colorBitsPerPixel == 15 || destination->colorBitsPerPixel == 16) {
            format = 8;
        } else {
            format = 7;
        }
    }
    if (allocated) {
        image->load(pixels, (IG_GFX_TEXTURE_FORMAT)format, (IG_GFX_IMAGE_ORDER)IG_GFX_IMAGE_ORDER_DEFAULT, width, height);
        Memory_FreeBuffer(pixels);
    } else {
        image->load(pixels, (IG_GFX_TEXTURE_FORMAT)format, width, height);
    }
    return 1;
}

void igPsx2VisualContext::setViewport(int x, int y, int w, int h, float nearZ, float farZ) {
    _iViewportX = x;
    _iViewportY = y;
    _iViewportW = w;
    _iViewportH = h;
    _viewportNear = nearZ;
    _viewportFar = farZ;
    if (_scissorType == 0) {
        FUN_0016a520(this);
    }
    p2SetViewport(x, y, w, h, 1.0f - _viewportNear, 1.0f - _viewportFar);
}

void igPsx2VisualContext::getViewport(int &x, int &y, int &w, int &h) const {
    x = _iViewportX;
    y = _iViewportY;
    w = _iViewportW;
    h = _iViewportH;
}

void igPsx2VisualContext::getViewport(int &x, int &y, int &w, int &h, float &nearZ, float &farZ) const {
    x = _iViewportX;
    y = _iViewportY;
    w = _iViewportW;
    h = _iViewportH;
    nearZ = _viewportNear;
    farZ = _viewportFar;
}

void igPsx2VisualContext::setClearColor(const igVec4f &rgba) {
    _clearColor.set(rgba);
    int green = (unsigned int)(255.0f * _clearColor.vec[1]) << 8;
    _uiClearColor = ((unsigned int)(255.0f * ((128.0f * _clearColor.vec[3]) / 255.0f)) << 24)
        + (((unsigned int)(255.0f * _clearColor.vec[2]) << 16) + ((unsigned int)(255.0f * _clearColor.vec[0]) + green));
}

void igPsx2VisualContext::setClearColor(unsigned int color) {
    _uiClearColor = (color & 0xffffff) | (((color >> 1) & 0x7f000000) + (color & 0x01000000));
}

unsigned igPsx2VisualContext::getClearColor() const {
    int color;
    unsigned int alphaHigh;

    color = _uiClearColor;
    alphaHigh = (unsigned int)(color & 0x80000000) >> 7;
    return (color & 0xFFFFFF) | (alphaHigh + (((color & 0xFF000000) - alphaHigh) * 2));
}

void igPsx2VisualContext::getClearColor(igVec4f &abgr) const {
    Color4f_Unpack(&abgr, 1, _uiClearColor);
}

void igPsx2VisualContext::setClearDepth(float val) {
    _clearDepth = val;
    if (_depthTestFunc & 4) {
        _uiClearDepth = (unsigned)(2.1474836e9f * _clearDepth);
        return;
    }
    _uiClearDepth = (unsigned)(2.1474836e9f * (1.0f - _clearDepth));
}

float igPsx2VisualContext::getClearDepth() const {
    return _clearDepth;
}

void igPsx2VisualContext::setClearStencil(unsigned int val) {
    _clearStencil = val;
}

unsigned igPsx2VisualContext::getClearStencil() const {
    return _clearStencil;
}

int igPsx2VisualContext::getColorBitsPerPixel(int iHandle) const {
    return *destinationWord((::igDataList *)_pBufList, iHandle, offsetof(igPsx2RenderDestination, colorBitsPerPixel));
}

int igPsx2VisualContext::getAlphaBitsPerPixel(int iHandle) const {
    return *destinationWord((::igDataList *)_pBufList, iHandle, offsetof(igPsx2RenderDestination, alphaBitsPerPixel));
}

int igPsx2VisualContext::getDepthBitsPerPixel(int iHandle) const {
    return *destinationWord((::igDataList *)_pBufList, iHandle, offsetof(igPsx2RenderDestination, depthBitsPerPixel));
}

int igPsx2VisualContext::getStencilBitsPerPixel(int iHandle) const {
    return *destinationWord((::igDataList *)_pBufList, iHandle, offsetof(igPsx2RenderDestination, stencilBitsPerPixel));
}

float igPsx2VisualContext::getPixelAspectRatio(int iHandle) const {
    return *(float *)destinationWord((::igDataList *)_pBufList, iHandle, offsetof(igPsx2RenderDestination, pixelAspectRatio));
}
}
}

/* A rectangle side limited to what remains of the destination, at least one pixel. */
static inline int clampExtent(int limit, int remaining) {
    if (MIN(limit, remaining) > 1) return MIN(limit, remaining);
    return 1;
}

/* A rectangle origin limited to the destination's size. */
static inline int clampOrigin(int limit, int size) {
    if (MIN(limit, size) > 0) return MIN(limit, size);
    return 0;
}

/* Sets the GS scissor to the viewport (scissor type 0) or the scissor rectangle, clipped to the current
 * render destination. */
void FUN_0016a520(Gap::Gfx::igPsx2VisualContext *vc) {
    igPsx2RenderDestination *destination = ((igPsx2RenderDestinationPool *)vc->_pBufList)->elements + vc->_currentBuf;
    if (destination != 0) {
        if (vc->_scissorType == 0) {
            int y = vc->_iViewportY; int height = destination->height; int h = vc->_iViewportH;
            h = clampExtent(h, height - y);
            { int x = vc->_iViewportX; int width = destination->width; int w = vc->_iViewportW;
              w = clampExtent(w, width - x);
              y = clampOrigin(y, height);
              x = clampOrigin(x, width);
              p2SetScissor(x, y, w, h); }
        } else {
            int y = vc->_scissorY; int height = destination->height; int h = vc->_scissorH;
            h = clampExtent(h, height - y);
            { int x = vc->_scissorX; int width = destination->width; int w = vc->_scissorW;
              w = clampExtent(w, width - x);
              y = clampOrigin(y, height);
              x = clampOrigin(x, width);
              p2SetScissor(x, y, w, h); }
        }
    }
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setScissor(int x, int y, int w, int h) {
    _scissorX = x;
    _scissorY = y;
    _scissorW = w;
    _scissorH = h;
    if (_scissorType == 1) {
        FUN_0016a520(this);
    }
}

void igPsx2VisualContext::getScissor(int &x, int &y, int &w, int &h) const {
    x = _scissorX;
    y = _scissorY;
    w = _scissorW;
    h = _scissorH;
}

void igPsx2VisualContext::setScissorType(IG_GFX_SCISSOR_TYPE type) {
    _scissorType = type;
    FUN_0016a520(this);
}
}
}

/* Forgets a colour table's igClut and its uploaded image state. */
void igPsx2ClutRecord_Reset(igPsx2ClutRecord *record) {
    Gap::Gfx::igClut *clut;
    clut = record->clut;
    if (clut != 0) {
        ((::igObject *)clut)->_refCount = (int)((int)(((::igObject *)clut)->_refCount - 1));
        if (((unsigned long long)((long long)(int)((::igObject *)clut)->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)clut);
        }
    }
    record->clut = 0;
    record->image = 0;
    record->state = 0;
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::initializeCluts() {
    int clutCount;
    igPsx2ClutPool *pool;
    clutCount = 64;
    igGetRegistryValue_Int(g_objectSystem->configRegistry, 4, "IG_GFX_VC_CLUT_ARRAY_SIZE", &clutCount, 64, 0);
    pool = new ((igMemoryPoolView *)this->getListMemoryPool()) igPsx2ClutPool(clutCount, "IG_GFX_VC_CLUT_ARRAY_SIZE");
    _pClutList = (int)pool;
    _currentCLUT = -1;
}

void igPsx2VisualContext::uninitializeCluts(int keepPool) {
    int handle;
    igPsx2ClutPool *pool;
    handle = ((igPsx2ClutPool *)_pClutList)->capacity - 1;
    for (; handle > -1; handle--) {
        if (((igPsx2ClutPool *)_pClutList)->isIndexAllocated(handle)) {
            deleteClut(handle);
        }
    }
    if (keepPool == 0) {
        pool = (igPsx2ClutPool *)_pClutList;
        delete pool;
        _pClutList = 0;
    }
}

void igPsx2VisualContext::deleteClut(int handle) {
    igPsx2ClutPool *pool;
    igPsx2ClutRecord *record;
    Gap::Gfx::igClut *clut;
    pool = (igPsx2ClutPool *)_pClutList;
    if (pool->isIndexAllocated(handle)) {
        record = pool->elements + handle;
        if (record->image != 0) {
            freeClutImage(handle);
        }
        clut = record->clut;
        if (clut != 0) {
            --((::igObject *)clut)->_refCount;
            if (!(((::igObject *)clut)->_refCount & 0x7fffff)) igObject_Destroy((::igObject *)clut);
        }
        record->clut = 0;
        if (record->palette != 0) {
            Memory_FreeBuffer(record->palette);
        }
        pool = (igPsx2ClutPool *)_pClutList;
        pool->freeElement(handle);
    }
}

/* Makes a colour table of `entryCount` colours (at most 256) in `layout` and returns its handle, or -1. */
int igPsx2VisualContext::createClut(int entryCount, int layout) {
    igPsx2ClutPool *pool;
    igPsx2ClutRecord *record;
    int handle;
    if (entryCount > 256) {
        return -1;
    }
    pool = (igPsx2ClutPool *)_pClutList;
    handle = pool->getFreeElement();
    record = ((igPsx2ClutPool *)_pClutList)->elements + handle;
    igPsx2ClutRecord_Reset(record);
    record->state = 0;
    record->layout = layout;
    record->entryCount = entryCount;
    record->palette = 0;
    return handle;
}

/* Copies colours into a GS palette: 16 colours as they are (layout 0), or 256 with bits 3 and 4 of the index
 * exchanged (layout 1). */
void igPsx2VisualContext::copyClutPalette(int layout, int *palette, int *colors) {
    int *destination;
    int *source;
    int swizzled;
    int index;
    int index2;

    destination = palette;
    source = colors;
    switch (layout) {
    case 0:
        index = 0;
        do {
            index += 1;
            *destination = *source;
            source += 1;
            destination += 1;
        } while (index < 0x10);
        return;
    case 1:
        index2 = 0;
        do {
            swizzled = (index2 & 0xE7) | (((index2 >> 1) & 8) | ((index2 & 8) * 2));
            index2 += 1;
            *destination = *(source + swizzled);
            destination += 1;
        } while (index2 < 0x100);
        return;
    }
}

/* Gives colour table `handle` the colours of `clut` and refreshes its GS palette. */
void igPsx2VisualContext::setClut(int handle, igClut *clut) {
    igPsx2ClutRecord *record;
    int paletteSize;
    Gap::Gfx::igClut *old;
    record = &((igPsx2ClutPool *)_pClutList)->elements[handle];
    if (clut != 0) {
        ((::igObject *)clut)->_refCount = ((::igObject *)clut)->_refCount + 1;
    }
    old = record->clut;
    if (old != 0) {
        ((::igObject *)old)->_refCount = ((::igObject *)old)->_refCount - 1;
        if (((unsigned long long)((long long)(int)((::igObject *)old)->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((::igObject *)old);
        }
    }
    record->clut = clut;
    record->state = 0;
    paletteSize = 256;
    if (_clutOptimization != 0 && record->entryCount < 17) {
        record->layout = 0;
        paletteSize = 16;
    }
    if (record->palette != 0 && record->image != 0) {
        p2WaitDmaSequence(2, p2GetTextureUploadSequence((P2Texture *)p2GetImageTexture((p2Image *)record->image)));
    } else if (record->palette == 0) {
        record->palette = ((igMemoryPoolView *)this->getImageMemoryPool())->AllocateAligned(paletteSize * 4, 128);
    }
    if (record->palette != 0) {
        clut->_clutDirty = 1;
        copyClutPalette(record->layout, (int *)record->palette, (int *)clut->_pData);
    }
}

/* Uploads colour table `handle`'s palette to the GS when it changed, and makes sure its texture is resident. */
bool igPsx2VisualContext::uploadClut(int handle) {
    int resident;
    bool uploaded;
    int texture;
    int ignored;
    igPsx2ClutRecord *record;
    Gap::Gfx::igClut *clut;
    record = &((igPsx2ClutPool *)_pClutList)->elements[handle];
    uploaded = true;
    if (record->image == 0 || record->clut->_clutDirty != 0) {
        if (record->image != 0) {
            texture = (int)p2GetImageTexture((p2Image *)record->image);
            p2InvalidateTexture((P2Texture *)texture);
            p2WaitDmaSequence(2, p2GetTextureUploadSequence((P2Texture *)texture));
            clut = record->clut;
            clut->_clutDirty = 1;
            copyClutPalette(record->layout, (int *)record->palette, (int *)clut->_pData);
        } else {
            record->image = (int)p2CreateImage(DAT_0048a4e0[record->layout], 0, DAT_0048a4ec[0], record->palette);
        }
        record->clut->_clutDirty = 0;
    }
    if (record->state != 5) {
        resident = (int)p2GetImageTexture((p2Image *)record->image);
        uploaded = FUN_0020bb20((P2Texture **)&resident, 0, 0) != 0;
    }
    record->state = 4;
    return uploaded;
}

/* Frees colour table `handle`'s GS image and palette texture. */
void igPsx2VisualContext::freeClutImage(int handle) {
    igPsx2ClutPool *pool;
    int texture;
    igPsx2ClutRecord *record;
    pool = (igPsx2ClutPool *)_pClutList;
    if (pool->isIndexAllocated(handle)) {
        record = pool->elements + handle;
        if (record->image != 0) {
            texture = (int)p2GetImageTexture((p2Image *)record->image);
            p2WaitDmaSequence(2, p2GetTextureUploadSequence((P2Texture *)texture));
            p2FreeTexture((P2Texture *)texture);
            p2FreeImage((p2Image *)record->image);
        }
        record->image = 0;
        _currentCLUT = -1;
    }
}
}
}

/* The override is a jump to igVisualContext's constructFields: the callee takes the caller's
 * registers untouched. */

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::constructFields(int flags) {
    igVisualContext::constructFields(flags);
}

void igPsx2VisualContext::userDestruct() {
    if (_inverseTranspose != 0) {
        Memory_FreeBuffer(_inverseTranspose);
        _inverseTranspose = 0;
    }
    FUN_00169260(this, 0);
    uninitializeTextures(0);
    uninitializeCluts(0);
    uninitializeLighting(0);
    FUN_0016c650(this, 0);
    releaseStatisticCaptures(0);
    if (_iContextOpen != 0) {
        p2CloseDisplay();
    }
    igVisualContext::userDestruct();
}
}
}

/* The context's render-destination pool, and the destination a handle names. */
static inline igPsx2RenderDestinationPool *destinationPool(Gap::Gfx::igPsx2VisualContext *vc) {
    return (igPsx2RenderDestinationPool *)vc->_pBufList;
}
static inline igPsx2RenderDestination *renderDestination(Gap::Gfx::igPsx2VisualContext *vc, int handle) {
    return &destinationPool(vc)->elements[handle];
}
struct ContextText : public igObject {
    const char *_text;
    int _length;
    const char *text() const {
        const char *t = _text;
        if (t == 0) t = (const char *)g_stringObjEmptyText;
        return t;
    }
};
#include "dw4/p2/p2core.h"
#include "dw4/p2/p2swap.h"
extern "C" int p2OpenDisplay(int mode, int colorBits, int depthBits, const char *config, const char *symbols, int width, int height);

namespace Gap {
namespace Gfx {

igResult igPsx2VisualContext::open() {
    igPsx2RenderDestination *record;
    ::igRegistry *registry;
    int colorBits;
    int alphaBits;
    int depthBits;
    bool useWatchdog;
    int width;
    int height;

    loadDefaultDriverDatabase();
    igSmartPointer<ContextText> ucodeConfig((ContextText *)igStringObj_Create((int)getInternalMemoryPool()));
    igSmartPointer<ContextText> ucodeSym((ContextText *)igStringObj_Create((int)getInternalMemoryPool()));
    int size;
    int syncMode;
    record = renderDestination(this, _currentBuf);
    if (record->type != 0 && record->type != 1 && record->type != 2) {
        igPsx2RenderDestinationPool *pool = destinationPool(this);
        record = 0;
        for (int i = 0; i < pool->capacity - pool->freeCount; i++) {
            record = renderDestination(this, i);
            if (record->type == 0 || record->type == 1 || record->type == 2) {
                _currentBuf = i;
                break;
            }
        }
    }
    if (record == 0) {
        return g_resultFailure;
    }
    if (_videoMode._bInterlaced == 1) {
        if (_videoMode._iFieldSize == 0) {
            p2SetFrameMode(0);
        } else if (_videoMode._iFieldSize == 1) {
            p2SetFrameMode(1);
        }
        p2SetDisplayFrameCount(_videoMode._iFieldCount);
    } else {
        p2SetFrameMode(0);
        p2SetDisplayFrameCount(2);
    }
    if (_videoMode._fRefreshRate < 40.0f) {
        p2SetSwapInterval(1);
    }
    colorBits = getColorBitsPerPixel(_currentBuf);
    alphaBits = getAlphaBitsPerPixel(_currentBuf);
    depthBits = getDepthBitsPerPixel(_currentBuf);
    if (colorBits >= 32 || colorBits <= 0) {
        colorBits = 32;
    } else if (colorBits >= 24) {
        colorBits = 24;
    } else {
        colorBits = 16;
    }
    if (alphaBits >= 8) {
        alphaBits = 8;
    } else if (alphaBits >= 6) {
        alphaBits = 6;
    } else if (alphaBits >= 4) {
        alphaBits = 4;
    } else {
        alphaBits = 0;
    }
    if (depthBits >= 32) {
        depthBits = 32;
    } else if (depthBits >= 24) {
        depthBits = 24;
    } else {
        depthBits = 16;
    }
    record->colorBitsPerPixel = colorBits;
    record->alphaBitsPerPixel = alphaBits;
    record->depthBitsPerPixel = depthBits;
    record->stencilBitsPerPixel = 0;
    registry = (::igRegistry *)g_objectSystem->configRegistry;
    igGetRegistryValue_StringObj(registry, 4, "ucodeConfig", (igStringObj **)&ucodeConfig, "", 0);
    igGetRegistryValue_StringObj(registry, 4, "ucodeSym", (igStringObj **)&ucodeSym, "", 0);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_CLUT_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(3, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMAPREDICATE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(7, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMACOMPLETION_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(8, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_FINISH_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(9, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_TEXTURE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(10, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF0_SIZE_PSX2", &size, -1, 0);
    if (size >= 0) p2SetPoolSize(4, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF1_SIZE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(5, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_GIF_SIZE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(6, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF0_PSX2", &size, -1, 0);
    if (size >= 0) p2SetPoolSize(0, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF1_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(1, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_GIF_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(2, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_STATE_CACHE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(11, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_MULTIPASS_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(12, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_RENDERLIST_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(13, size);
    ((Gap::Core::igRegistry *)registry)->getValue(4, "IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES", _maxStageNum, 1, 0);
    _maxStageNum = _maxStageNum < 16 ? _maxStageNum : 16;
    _maxStageNum = _maxStageNum > 1 ? _maxStageNum : 1;
    syncMode = 0;
    ((Gap::Core::igRegistry *)registry)->getValue(4, "IG_GFX_TEXTURE_SYNC_MODE_PSX2", syncMode, 1, 0);
    p2SetTextureWaitMode(syncMode);
    useWatchdog = true;
    ((Gap::Core::igRegistry *)registry)->getValue(4, "useWatchdog", *(unsigned char *)&useWatchdog, 1, 0);
    p2EnableWatchdog(useWatchdog);
    loadStatisticCaptures();
    {
        int bits = colorBits + alphaBits;
        bits = bits < 32 ? bits : 32;
        int standard = _videoMode._iVideoType;
        if (standard != 2 && standard != 3) {
            if (standard == 0) {
                int mode;
                switch (record->width) {
                case 256: mode = 0; break;
                case 320: mode = 1; break;
                case 384: mode = 2; break;
                case 512: mode = 3; break;
                default:
                    mode = 4;
                    record->width = 640;
                    record->height = 448;
                    break;
                }
                const char *config = ucodeConfig->text();
                const char *symbols = ucodeSym->text();
                p2OpenDisplay(mode, bits, depthBits, config, symbols, record->width, record->height);
            } else if (_videoMode._iVideoType == 1) {
                int mode;
                switch (record->width) {
                case 256: mode = 5; break;
                case 320: mode = 6; break;
                case 384: mode = 7; break;
                case 512: mode = 8; break;
                default:
                    mode = 9;
                    record->width = 640;
                    record->height = 576;
                    break;
                }
                const char *config = ucodeConfig->text();
                const char *symbols = ucodeSym->text();
                p2OpenDisplay(mode, bits, depthBits, config, symbols, record->width, record->height);
            }
        }
    }
    p2GetDisplaySize(&width, &height, 0, 0);
    _iDisplayWidth = width;
    _iDisplayHeight = height;
    {
        bool slowSpotLight;
        if (igGetRegistryValue_Bool(registry, 4, "useSlowSpotLight", (unsigned char *)&slowSpotLight, 0, 0) != 0 && slowSpotLight) {
            p2DisableCapability(24);
        } else {
            p2EnableCapability(24);
        }
    }
    {
        bool eyeLocalLight;
        igGetRegistryValue_Bool(registry, 4, "useEyeLocalLight", (unsigned char *)&eyeLocalLight, 0, 0);
        if (eyeLocalLight) p2EnableCapability(20); else p2DisableCapability(20);
    }
    {
        bool cpuLightLoading;
        igGetRegistryValue_Bool(registry, 4, "useCpuLightLoading", (unsigned char *)&cpuLightLoading, 0, 0);
        if (cpuLightLoading) p2EnableCapability(21); else p2DisableCapability(21);
    }
    {
        bool lock;
        igGetRegistryValue_Bool(registry, 4, "lockDMAVif1", (unsigned char *)&lock, 0, 0);
        if (lock) p2FixDmaPacketPool(1);
        igGetRegistryValue_Bool(registry, 4, "lockDMAGif", (unsigned char *)&lock, 0, 0);
        if (lock) p2FixDmaPacketPool(2);
    }
    {
        bool showGuardBand;
        igGetRegistryValue_Bool(registry, 4, "showGuardBand", (unsigned char *)&showGuardBand, 0, 0);
        if (showGuardBand) p2SetClearPasses(1);
    }
    FUN_00174090(this);
    _iContextOpen = 1;
    createFrameBufferTextures();
    return g_resultSuccess;
}

void igPsx2VisualContext::reset() {
    igVisualContext::reset();
    _pVertexArray = 0;
    _pIndexArray = 0;
    _pStripLengthArray = 0;
}

int igPsx2VisualContext::getCapability(IG_GFX_CAPABILITY which) const {
    switch (which) {
    case 0:
        return 640;
    case 1:
        return 448;
    case 2:
        return 24;
    case 3:
        return 8;
    case 4:
        return 32;
    case 5:
        return 0;
    case 6:
        return 0;
    case 8:
        return 1;
    case 22:
        return _maxStageNum;
    case 7:
        return 1024;
    case 9:
        return 8;
    case 10:
        return 1;
    case 11:
        return 0;
    case 12:
        return 1;
    case 13:
        return 4;
    case 14:
        return 0;
    case 15:
        return 0;
    case 16:
        return 0;
    case 17:
        return 0;
    case 23:
        return 1;
    case 21:
        return 0;
    case 28:
    default:
        return 0;
    }
}
}
}

/* Deletes every render list and, unless the pool is kept, the pool itself. */
void FUN_0016c650(Gap::Gfx::igPsx2VisualContext *vc, int keepPool) {
    int handle;
    igPsx2RenderListPool *pool;
    handle = ((igPsx2RenderListPool *)vc->_pDLists)->capacity - 1;
    for (; handle > -1; handle--) {
        vc->deleteRenderList(handle);
    }
    if (keepPool == 0) {
        pool = (igPsx2RenderListPool *)vc->_pDLists;
        delete pool;
        vc->_pDLists = 0;
    }
}

namespace Gap {
namespace Gfx {

int igPsx2VisualContext::createRenderList() {
    int handle;
    handle = ((igPsx2RenderListPool *)_pDLists)->getFreeElement();
    {
        igPsx2RenderList *list = new ((igMemoryPoolView *)getDriverDataMemoryPool()) igPsx2RenderList;
        Gap::Core::igIntList *displayLists = (Gap::Core::igIntList *)igIntList_Create((int)getDriverDataMemoryPool());
        ((igPsx2RenderListPool *)_pDLists)->elements[handle] = list;
        list->displayLists = displayLists;
    }
    _dlistErrors = 0;
    return handle;
}

void igPsx2VisualContext::deleteRenderList(int dlistHandle) {
    igPsx2RenderListPool *pool;
    Gap::Core::igIntList *displayLists;
    int i;
    pool = (igPsx2RenderListPool *)_pDLists;
    /* matching construct: retail masks the inlined allocation test to a byte before it branches */
    if (pool->isIndexAllocated(dlistHandle) & 0xFF) {
        displayLists = pool->elements[dlistHandle]->displayLists;
        for (i = 0; i < displayLists->_count; i++) {
            p2ReleaseDisplayList((p2DisplayList *)displayLists->get(i));
        }
        displayLists->release();
        Memory_FreeBufferAliasB(((igPsx2RenderListPool *)_pDLists)->elements[dlistHandle]);
        ((igPsx2RenderListPool *)_pDLists)->freeElement(dlistHandle);
    }
}

void igPsx2VisualContext::beginRenderListDraw(int dlistHandle) {
    _currentDListHandle = dlistHandle;
    if (_blendMatricesCount < 0x10) {
        p2SetBlendMatrices(0, 0x10);
    }
}

bool igPsx2VisualContext::endRenderListDraw() {
    int count;
    count = _blendMatricesCount;
    if (count > 0) {
        p2SetBlendMatrices((int)_blendMatrices, count);
    }
    _currentDListHandle = -1;
    return _dlistErrors == 0;
}

bool igPsx2VisualContext::executeRenderList(int dlistHandle) {
    Gap::Core::igIntList *displayLists;
    int state;
    int weightCount;
    int i;
    int listWeights;

    displayLists = ((igPsx2RenderListPool *)_pDLists)->elements[dlistHandle]->displayLists;
    if (displayLists->_count > 0) {
        state = FUN_00177010((::igPsx2VisualContext *)this, 0, 0, displayLists->get(0), dlistHandle);
        if ((state == 1) || (state == 3)) {
            return false;
        }
        weightCount = 0;
        if (state == 2) {
            weightCount = p2GetDisplayListBlendWeightCount((p2DisplayList *)displayLists->get(0));
        }
        for (i = 0; i < displayLists->_count; i += 1) {
            listWeights = p2GetDisplayListBlendWeightCount((p2DisplayList *)displayLists->get(i));
            if ((state == 2) && (weightCount != listWeights)) {
                p2SetBlendWeightCount(listWeights, listWeights);
            }
            p2CallDisplayList((p2DisplayList *)displayLists->get(i));
        }
    }
    return true;
}
}
}

void FUN_0016cc50(Gap::Gfx::igPsx2VisualContext *vc, int mode) {
    vc->_renderlistMode = mode;
}

/* Starts recording a p2 display list into the current render list, in the render-list mode's p2 mode. */
void FUN_0016cc60(Gap::Gfx::igPsx2VisualContext *vc) {
    int handle;
    Gap::Core::igIntList *displayLists;
    int list;
    handle = vc->_currentDListHandle;
    if (handle >= 0) {
        displayLists = ((igPsx2RenderListPool *)vc->_pDLists)->elements[handle]->displayLists;
        list = (int)p2BeginDisplayList(DAT_0048a4f0[vc->_renderlistMode]);
        displayLists->append(list);
    }
}

void FUN_0016cd10(Gap::Gfx::igPsx2VisualContext *vc) {
    if (vc->_currentDListHandle >= 0) {
        p2EndDisplayList();
    }
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::detectDriverDatabaseProperties(igDriverDatabase *database) {
    igDriverDatabase_SetCurrentProperty((void *)database, 1, "psx2");
    igDriverDatabase_SetCurrentProperty((void *)database, 2, "1.0");
    igDriverDatabase_SetCurrentProperty((void *)database, 3, "sony");
    igDriverDatabase_SetCurrentProperty((void *)database, 4, "psx2");
    igDriverDatabase_SetCurrentProperty((void *)database, 5, "1.0");
}

void igPsx2VisualContext::callDmaChain(void *packet, int size, int flush) {
    p2CallGifChain((unsigned int)packet, size, flush);
}

int igPsx2VisualContext::isDisplayingFirstBuffer() {
    return swapbuffersDrawPredicate(1);
}
}
}
