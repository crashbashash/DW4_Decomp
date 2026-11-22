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
    /* The Xbox build's igDxImage::copy (default.xbe 0x51050) copies its DDS header at this test, which a PNG image,
       having none, skips; igPsx2Image holds no platform header, so the branch is empty. */
    if (src->getMeta() != igFileImagePng::getClassMeta()) {
    }
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
    unsigned char result = 0;
    const char *extension = Gap::Gfx::igImageUtils::getExt(fileName);

    if (extension != 0 && (strcmp(extension, ".tga") == 0 || strcmp(extension, ".TGA") == 0)) {
        igStringObjRef name((igStringObj *)igStringObj_Create((int)getMemoryPool()));
        igStringObj_Set(name, fileName);
        igSmartPointer<igTgaLoader> loader(igTgaLoader::_instantiateFromPool(getMemoryPool()));
        result = loader->load(name.p, this);
        setName(fileName);
        return result;
    }
    if (extension != 0 && (strcmp(extension, ".png") == 0 || strcmp(extension, ".PNG") == 0)) {
        igSmartPointer<igFileImagePng> reader(igFileImagePng::_instantiateFromPool(getMemoryPool()));
        result = reader->load(fileName) & 0xFF;
        if (result != 0) {
            copy(reader, true);
        }
    }
    return result;
}

unsigned char igPsx2Image::platformLoad(igFile *file)
{
    unsigned int b;
    unsigned int a;
    file->fread(&_imageSize, 4, 1);
    file->fread(&_px, 4, 1);
    file->fread(&_py, 4, 1);
    file->fread(&_pz, 4, 1);
    file->fread(&_ps, 4, 1);
    file->fread(&a, 4, 1);
    _bitsRed = (a >> 24) & 0xFF;
    _bitsGrn = (a >> 16) & 0xFF;
    _bitsBlu = (a >> 8) & 0xFF;
    _bitsAlpha = (unsigned char)a;
    _bitsIdx = 0;
    _bitsInt = 0;
    _bitsDepth = 0;
    file->fread(&b, 4, 1);
    file->fread(&b, 4, 1);
    _pImage = (unsigned char *)mallocAligned(_imageSize, 0x80);
    _localImage = true;
    file->fread(_pImage, 1, _imageSize);
    file->fclose();
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
    converted->copy(this, true);
    converted->unScaleAlpha();
    word = 0x312A57F2;
    file->fwrite(&word, 4, 1);
    file->fwrite(&_imageSize, 4, 1);
    file->fwrite(&_px, 4, 1);
    file->fwrite(&_py, 4, 1);
    file->fwrite(&_pz, 4, 1);
    file->fwrite(&_ps, 4, 1);
    masks = (_bitsRed << 24) | (_bitsGrn << 16) | (_bitsBlu << 8) | _bitsAlpha;
    file->fwrite(&masks, 4, 1);
    word = 0;
    file->fwrite(&word, 4, 1);
    file->fwrite(&word, 4, 1);
    file->fwrite(converted->_pImage, 1, _imageSize);
    file->fclose();
    file->release();
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
    file->fread(&_imageSize, 4, 1);
    file->fread(&_pz, 4, 1);
    file->fread(&_px, 4, 1);
    file->fread(&_py, 4, 1);
    _ps = 1;
    _pImage = (unsigned char *)mallocAligned(_imageSize, 0x80);
    _localImage = true;
    file->fread(_pImage, 1, _imageSize);
    file->fclose();
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
    file->release();
    return true;
}

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

