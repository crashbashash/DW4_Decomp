namespace Gap {
namespace Gfx {

void igTgaLoader::releaseDefaults()
{
    igObject::releaseDefaults();
}

bool igTgaLoader::cleanup(bool retVal)
{
    if (_file != 0) {
        _file->fclose();
        _file = 0;
    }
    free(_palette);
    _palette = 0;
    free(_tempMap);
    _tempMap = 0;
    free(_tempRow);
    _tempRow = 0;
    _bCount = 0;
    _bType = 0;
    return retVal;
}

bool igTgaLoader::fillBuffer()
{
    int count = _file->fread(_tempRow, 1, 1024);

    if (count == 0) {
        return false;
    }
    _limitChar = count;
    _nextChar = 0;
    return true;
}

bool igTgaLoader::isBufEmpty()
{
    return _nextChar >= _limitChar;
}

unsigned char igTgaLoader::getNextChar()
{
    if (isBufEmpty() && !fillBuffer()) {
        return 0xFF;
    }
    return _tempRow[_nextChar++];
}

void igTgaLoader::cGetPixel(unsigned char *dp)
{
    int i;
    int a;
    int v;

    v = _bCount - 1;
    _bCount = v;
    if (v <= 0) {
        _bCount = (signed char)getNextChar();
        a = _bCount;
        if (a & 0x80) {
            _bCount = (a & 0x7F) + 1;
            _bType = 1;
            for (i = 0; i < _psize; i++) { dp[i] = getNextChar(); }
        } else {
            _bCount = a + 1;
            _bType = 0;
        }
    }
    if (_bType == 0) {
        for (i = 0; i < _psize; i++) { dp[i] = getNextChar(); }
    }
}

IG_GFX_TEXTURE_FORMAT igTgaLoader::estimateImageFormat(int ftype, int w, IG_GFX_TEXTURE_FORMAT &igFmt, int &srcBpr, IG_GFX_IMAGE_ORDER &order, bool &isCompressed)
{
    srcBpr = w;
    isCompressed = false;
    order = IG_GFX_IMAGE_ORDER_DEFAULT;
    switch (ftype) {
    case 1:
        igFmt = IG_GFX_TEXTURE_FORMAT_X_8;
        break;
    case 6:
        igFmt = IG_GFX_TEXTURE_FORMAT_L_8;
        break;
    case 2:
        igFmt = IG_GFX_TEXTURE_FORMAT_X_8;
        srcBpr *= 2;
        break;
    case 3:
        igFmt = IG_GFX_TEXTURE_FORMAT_RGBA_5551_16;
        srcBpr *= 2;
        break;
    case 4:
        igFmt = IG_GFX_TEXTURE_FORMAT_RGB_888_24;
        srcBpr *= 3;
        break;
    case 5:
        igFmt = IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
        srcBpr *= 4;
        break;
    case 7:
        igFmt = IG_GFX_TEXTURE_FORMAT_X_8;
        isCompressed = true;
        srcBpr = 0x400;
        break;
    case 8:
        igFmt = IG_GFX_TEXTURE_FORMAT_X_8;
        isCompressed = true;
        srcBpr = 0x400;
        break;
    case 12:
        igFmt = IG_GFX_TEXTURE_FORMAT_L_8;
        isCompressed = true;
        srcBpr = 0x400;
        break;
    case 9:
        igFmt = IG_GFX_TEXTURE_FORMAT_RGBA_5551_16;
        isCompressed = true;
        srcBpr = 0x400;
        break;
    case 10:
        igFmt = IG_GFX_TEXTURE_FORMAT_RGB_888_24;
        isCompressed = true;
        srcBpr = 0x400;
        break;
    case 11:
        igFmt = IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
        isCompressed = true;
        srcBpr = 0x400;
        break;
    default:
        igFmt = IG_GFX_TEXTURE_FORMAT_INVALID;
        srcBpr = -1;
        order = IG_GFX_IMAGE_ORDER_INVALID;
        break;
    }
    return igFmt;
}
}
}

/* Builds the render-destination pool, sized by the registry value IG_GFX_VC_RD_ARRAY_SIZE, with no destination
 * current. */
void FUN_001690d0(Gap::Gfx::igPsx2VisualContext *vc) {
    int destinationCount;
    igPsx2RenderDestinationPool *pool;
    destinationCount = 4;
    igGetRegistryValue_Int(g_objectSystem->configRegistry, 4, "IG_GFX_VC_RD_ARRAY_SIZE", &destinationCount, 4, 0);
    pool = new ((igMemoryPoolView *)vc->getListMemoryPool()) igPsx2RenderDestinationPool(destinationCount, "IG_GFX_VC_RD_ARRAY_SIZE");
    vc->_pBufList = (int)pool;
    vc->_currentBuf = -1;
}

