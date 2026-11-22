namespace Gap {
namespace Gfx {

void igPsx2Image::userApplyWriteProxy(int value)
{
    unScaleAlpha();
    if (_order == IG_GFX_IMAGE_ORDER_PSX2) {
        swapComponentOrder();
    }
}

void igPsx2Image::userMakeConcrete(igMetaObject *meta)
{
    int order = _order;
    if ((order == IG_GFX_IMAGE_ORDER_DEFAULT) || (order == 0)) {
        _order = IG_GFX_IMAGE_ORDER_DEFAULT;
        swapComponentOrder();
    }
    scaleAlpha();
}

void igPsx2Image::initDefaults()
{
    igObject::initDefaults();
}

void igPsx2Image::releaseDefaults()
{
    igImage::releaseDefaults();
}

void igPsx2Image::copy(const igImage *src, bool copyImage)
{
    igImage::copy(src, copyImage);
    src->getMeta();
}

unsigned char igPsx2Image::platformConvert(IG_GFX_TEXTURE_FORMAT format, const igImage *source)
{
    bool supported = false;
    switch (source->_pfmt) {
    case IG_GFX_TEXTURE_FORMAT_L_8:
        switch (format) {
        case IG_GFX_TEXTURE_FORMAT_X_8:
            supported = true;
            break;
        case IG_GFX_TEXTURE_FORMAT_A_8:
        case IG_GFX_TEXTURE_FORMAT_L_8:
            supported = true;
            break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_A_8:
        switch (format) {
        case IG_GFX_TEXTURE_FORMAT_X_8:
            supported = true;
            break;
        case IG_GFX_TEXTURE_FORMAT_L_8:
        case IG_GFX_TEXTURE_FORMAT_A_8:
            supported = true;
            break;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_LA_88_16:
        break;
    case IG_GFX_TEXTURE_FORMAT_LA_44_8:
        switch (format) {
        case IG_GFX_TEXTURE_FORMAT_X_8:
            supported = true;
            break;
        case IG_GFX_TEXTURE_FORMAT_LA_44_8:
            break;
        }
        break;
    }
    if (supported) {
        if (this != source || !_localImage) {
            copy(source, true);
        }
        switch (source->_pfmt) {
        case IG_GFX_TEXTURE_FORMAT_L_8:
            switch (format) {
            case IG_GFX_TEXTURE_FORMAT_X_8:
                setPixelFormat(IG_GFX_TEXTURE_FORMAT_X_8);
                _bitsInt = 0;
                _bitsIdx = 8;
                supported = true;
                break;
            case IG_GFX_TEXTURE_FORMAT_A_8:
                setPixelFormat(IG_GFX_TEXTURE_FORMAT_A_8);
                _bitsInt = 0;
                _bitsAlpha = 8;
                break;
            case IG_GFX_TEXTURE_FORMAT_L_8:
                break;
            }
            break;
        case IG_GFX_TEXTURE_FORMAT_A_8:
            switch (format) {
            case IG_GFX_TEXTURE_FORMAT_X_8:
                setPixelFormat(IG_GFX_TEXTURE_FORMAT_X_8);
                _bitsAlpha = 0;
                _bitsIdx = 8;
                supported = true;
                break;
            case IG_GFX_TEXTURE_FORMAT_L_8:
                setPixelFormat(IG_GFX_TEXTURE_FORMAT_L_8);
                _bitsAlpha = 0;
                _bitsInt = 8;
                break;
            case IG_GFX_TEXTURE_FORMAT_A_8:
                break;
            }
            break;
        case IG_GFX_TEXTURE_FORMAT_LA_88_16:
            break;
        case IG_GFX_TEXTURE_FORMAT_LA_44_8:
            switch (format) {
            case IG_GFX_TEXTURE_FORMAT_X_8:
                setPixelFormat(IG_GFX_TEXTURE_FORMAT_X_8);
                _bitsInt = 0;
                _bitsAlpha = 0;
                _bitsIdx = 8;
                supported = true;
                _pz = 1;
                break;
            case IG_GFX_TEXTURE_FORMAT_LA_44_8:
                break;
            }
            break;
        }
    }
    return supported;
}

unsigned char igPsx2Image::platformLoad(const char *fileName)
{
    unsigned char var_s0 = 0;
    int s;
    s = FUN_0015ad50((char *)fileName);
    if (s != 0) {
        if (strcmp((char *)s, ".tga") != 0) {
            if (strcmp((char *)s, ".TGA") == 0) goto block_4;
            goto block_22;
        }
    block_4:
        {
            igSmartPointer<O0> name((O0 *)igStringObj_Create((int)getMemoryPool()));
            igStringObj_Set((igStringObj *)((int)name.p), (char *)fileName);
            LoaderRef loader((O1 *)igTgaLoader_Create((int)getMemoryPool()));
            var_s0 = loader.p->v21(name.p, this) & 0xFF;
            setName(fileName);
        }
        return var_s0;
    }
    block_22:
    if (s != 0) {
        if (strcmp((char *)s, ".png") != 0) {
            if (strcmp((char *)s, ".PNG") == 0) goto block_26;
        } else {
    block_26:
            ReaderRef reader((O2 *)igFileImagePng_Create((int)getMemoryPool()));
            var_s0 = reader.p->v31((int)fileName) & 0xFF;
            if (var_s0 != 0) {
                copy((igImage *)reader.p, true);
            }
        }
    }
    return var_s0;
}

unsigned char igPsx2Image::platformLoad(igFile *file)
{
    unsigned int b;
    unsigned int a;
    Strm *s = (Strm *)file;
    s->Read(&_imageSize, 4, 1);
    s->Read(&_px, 4, 1);
    s->Read(&_py, 4, 1);
    s->Read(&_pz, 4, 1);
    s->Read(&_ps, 4, 1);
    s->Read(&a, 4, 1);
    _bitsRed = (a >> 24) & 0xFF;
    _bitsGrn = (a >> 16) & 0xFF;
    _bitsBlu = (a >> 8) & 0xFF;
    _bitsAlpha = (unsigned char)a;
    _bitsIdx = 0;
    _bitsInt = 0;
    _bitsDepth = 0;
    s->Read(&b, 4, 1);
    s->Read(&b, 4, 1);
    _pImage = (unsigned char *)mallocAligned(_imageSize, 0x80);
    _localImage = true;
    s->Read(_pImage, 1, _imageSize);
    ((VStream *)s)->v24();
    _pfmt = guessPixelFormatFromNumComponents(_pz);
    _order = IG_GFX_IMAGE_ORDER_PSX2;
    scaleAlpha();
    return true;
}

unsigned char igPsx2Image::platformSave(igFile *file)
{
    igSmartPointer<igImage> converted(igImage::_instantiateFromPool(getMemoryPool()));
    int word;
    int masks;
    Stream *stream = (Stream *)file;
    converted->copy(this, true);
    converted->unScaleAlpha();
    word = 0x312A57F2;
    stream->write(&word, 4, 1);
    stream->write(&_imageSize, 4, 1);
    stream->write(&_px, 4, 1);
    stream->write(&_py, 4, 1);
    stream->write(&_pz, 4, 1);
    stream->write(&_ps, 4, 1);
    masks = (_bitsRed << 24) | (_bitsGrn << 16) | (_bitsBlu << 8) | _bitsAlpha;
    stream->write(&masks, 4, 1);
    word = 0;
    stream->write(&word, 4, 1);
    stream->write(&word, 4, 1);
    stream->write(converted->_pImage, 1, _imageSize);
    stream->close();
    stream->release();
    return true;
}

unsigned char igPsx2Image::oldLoad(igFile *file)
{
    int imageSize;
    unsigned int components;
    int bytesPerRow;
    unsigned int bitsInt;
    unsigned int bitsIdx;
    unsigned int bitsRed;
    unsigned int bitsGrn;
    unsigned int bitsBlu;
    unsigned int bitsAlpha;
    unsigned int bitsDepth;
    IG_GFX_TEXTURE_FORMAT format;
    Strm_16ece0 *stream = (Strm_16ece0 *)file;
    stream->v25(&_imageSize, 4, 1);
    stream->v25(&_pz, 4, 1);
    stream->v25(&_px, 4, 1);
    stream->v25(&_py, 4, 1);
    _ps = 1;
    _pImage = (unsigned char *)mallocAligned(_imageSize, 0x80);
    _localImage = true;
    stream->v25(_pImage, 1, _imageSize);
    stream->v24();
    _pfmt = guessPixelFormatFromNumComponents(_pz);
    scaleAlpha();
    format = (IG_GFX_TEXTURE_FORMAT)_pfmt;
    estimateImageSize(format, _px, _py, imageSize, components, bytesPerRow);
    _bytesPerRow = bytesPerRow;
    estimateBitDepths(format, bitsInt, bitsIdx, bitsRed, bitsGrn, bitsBlu, bitsAlpha, bitsDepth);
    _bitsInt = bitsInt;
    _bitsIdx = bitsIdx;
    _bitsRed = bitsRed;
    _bitsGrn = bitsGrn;
    _bitsBlu = bitsBlu;
    _bitsAlpha = bitsAlpha;
    _bitsDepth = bitsDepth;
    _order = IG_GFX_IMAGE_ORDER_PSX2;
    ((igObject *)file)->release();
    return true;
}
}
}

static inline unsigned imageSize(const ImageBuffer *i) { return i->size; }

namespace Gap {
namespace Gfx {

void igPsx2Image::load(void *data, IG_GFX_TEXTURE_FORMAT pixelFormat, IG_GFX_IMAGE_ORDER order, int width, int height)
{
    setPixelFormat(pixelFormat);
    setWidth(width);
    setHeight(height);
    setComponentOrder(order);
    allocateImageMemory();
    memcpy(_pImage, data, _imageSize);
}
}
}

