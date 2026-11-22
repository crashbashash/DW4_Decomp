namespace Gap {
namespace Gfx {

bool igClut::loadBuffer(IG_GFX_TEXTURE_FORMAT fmt, unsigned int numEntries, unsigned char *clutData)
{
    int clutSize;
    int stride;

    if (clutData != 0 && _pData == clutData && fmt == _fmt && fmt != IG_GFX_TEXTURE_FORMAT_INVALID) {
        resize(numEntries);
        return true;
    }
    if (_pData != 0) {
        free(_pData);
    }
    _fmt = fmt;
    _numEntries = numEntries;
    estimateClutSizeAndStride(fmt, numEntries, clutSize, stride);
    _clutSize = clutSize;
    _stride = stride;
    _pData = (unsigned char *)mallocAligned(_clutSize, 0x80);
    if (clutData != 0) {
        memcpy(_pData, clutData, getSize());
    } else {
        memset(_pData, 0, getSize());
    }
    return true;
}

bool igClut::load(IG_GFX_TEXTURE_FORMAT fmt, unsigned int numEntries, unsigned char *clutData)
{
    bool result;

    result = loadBuffer(fmt, numEntries, clutData);
    scaleAlpha();
    return result;
}

bool igClut::unScaleAlphaWork()
{
    unsigned int i;
    unsigned char *entry;
    bool done = false;

    if (_fmt == IG_GFX_TEXTURE_FORMAT_RGBA_8888_32) {
        entry = _pData;
        for (i = 0; i < _numEntries; i++) {
            entry[3] = (entry[3] & 0x80) ? ~(entry[3] & 0xFF) << 1 : entry[3] << 1;
            entry += 4;
        }
        done = true;
    } else if (_fmt != IG_GFX_TEXTURE_FORMAT_RGB_888_24) {
        return false;
    }
    return done;
}

int igClut::unScaleAlpha()
{
    int result;

    if (_isAlphaScaled) {
        result = unScaleAlphaWork();
        _isAlphaScaled = false;
        return result;
    }
    return true;
}

int igClut::estimateClutSizeAndStride(IG_GFX_TEXTURE_FORMAT pfmt, unsigned int nEntries, int &clutSize, int &stride)
{
    switch (pfmt) {
    case IG_GFX_TEXTURE_FORMAT_L_8: stride = 1; break;
    case IG_GFX_TEXTURE_FORMAT_A_8: stride = 1; break;
    case IG_GFX_TEXTURE_FORMAT_LA_44_8: stride = 1; break;
    case IG_GFX_TEXTURE_FORMAT_LA_88_16: stride = 2; break;
    case IG_GFX_TEXTURE_FORMAT_RGB_332_8: stride = 1; break;
    case IG_GFX_TEXTURE_FORMAT_RGB_888_24: stride = 3; break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_2222_8: stride = 1; break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32: stride = 4; break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16: stride = 2; break;
    case IG_GFX_TEXTURE_FORMAT_X_8: stride = 1; break;
    case IG_GFX_TEXTURE_FORMAT_X_4: stride = 1; break;
    default:
        clutSize = -2;
        stride = -2;
        return clutSize;
    }
    clutSize = nEntries * stride;
    return clutSize;
}

void igClut::copy(const igClut *src, bool copy)
{
    if (this != src) {
        if (_pData != 0) {
            free(_pData);
            _pData = 0;
        }
        _fmt = src->_fmt;
        _numEntries = src->_numEntries;
        _stride = src->_stride;
        _clutSize = src->_clutSize;
        _isAlphaScaled = src->_isAlphaScaled;
        if (copy) {
            _pData = (unsigned char *)mallocAligned(_clutSize, 0x80);
            memcpy(_pData, src->_pData, (unsigned int)_clutSize);
        }
    }
}

int igClut::scaleAlpha()
{
    int result;

    if (!_isAlphaScaled) {
        result = scaleAlphaWork();
        _isAlphaScaled = true;
        return result;
    }
    return true;
}

bool igClut::scaleAlphaWork()
{
    unsigned int i;
    unsigned char *entry;
    bool done = false;

    if (_fmt == IG_GFX_TEXTURE_FORMAT_RGBA_8888_32) {
        entry = _pData;
        for (i = 0; i < _numEntries; i++) {
            entry[3] = (entry[3] >> 1) + (entry[3] & 1);
            entry += 4;
        }
        done = true;
    } else if (_fmt != IG_GFX_TEXTURE_FORMAT_RGB_888_24) {
        return false;
    }
    return done;
}

void igClut::releaseDefaults()
{
    if (_pData != 0) {
        free(_pData);
        _pData = 0;
    }
}

void igClut::resize(int numClutEntries)
{
    if (numClutEntries != _numEntries) {
        _pData = (unsigned char *)reallocAligned(_pData, numClutEntries * _stride, 0x80);
        _numEntries = numClutEntries;
        _clutSize = numClutEntries * _stride;
    }
}

bool igClut::load(const char *fileName)
{
    const char *extension;

    extension = (const char *)FUN_0015ad50((char *)fileName);
    if (extension != 0 && (strcmp(extension, ".act") == 0 || strcmp(extension, ".ACT") == 0)) {
        return loadAct(fileName);
    }
    return false;
}

bool igClut::loadAct(const char *fileName)
{
    int pool;
    int allocator;
    int i;
    int *p;

    pool = (int)getMemoryPool();
    if (g_useOwnerAllocator != 0) {
        allocator = pool;
    } else {
        allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
    }
    pool = allocator;
    igSmartPointer<igFile> h(igFile::_instantiateFromPool((igMemoryPoolView *)pool), kRetainReference);
    h.p->release();
    if (_pData != 0) free(_pData);
    _pData = 0;
    if (h.p->fopen(fileName, "rb") == 0) {
        return false;
    }
    _pData = (unsigned char *)mallocAligned(0x400, 0x80);
    p = (int *)_pData;
    i = 0;
    do {
        h.p->fread(p, 1, 3);
        i++;
        *((unsigned char *)p + 3) = 0xff;
        p++;
    } while ((unsigned)i < 0x100);
    if ((unsigned)i < 0x100) memset(p, 0, (0x100 - i) * 4);
    _clutSize = 0x400;
    _stride = 4;
    _numEntries = 0x100;
    _fmt = IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
    h.p->fclose();
    return true;
}
}
}

