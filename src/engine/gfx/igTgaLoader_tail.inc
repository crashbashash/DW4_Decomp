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

void FUN_001690d0(Arg0d0 *arg0) {
    int sp5C;
    int i;
    P_1690d0 *p;
    int n;
    int v;
    int *old;
    int *s3;
    Buf860 *b;
    sp5C = 4;
    igGetRegistryValue_Int((igRegistry *)(*(int *)((char *)g_objectSystem + 56)), 4, "IG_GFX_VC_RD_ARRAY_SIZE", &sp5C, 4, 0);
    p = (P_1690d0 *)Memory_AllocateBufferDirect(20, (igMemoryPoolView *)igVisualContext_GetListMemoryPool((int *)arg0));
    if (p != 0) {
        n = sp5C;
        p->f8 = 0;
        if (g_stringPool == 0) {
            v = (int)StringPool_Allocate(16);
            if (v != 0) {
                v = (int)StringPool_Construct((StringPool *)v);
            }
            g_stringPool = (StringPool *)v;
        }
        s3 = (int *)StringPool_Intern(g_stringPool, "IG_GFX_VC_RD_ARRAY_SIZE");
        old = p->f8;
        if (old != 0) {
            int *a1 = old - 2;
            int v0 = old[-1] - 1;
            old[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
            }
        }
        p->f8 = s3;
        if (n == 0) {
            n = 1;
        }
        b = (Buf860 *)Memory_FindBufferOwner(p);
        p->f16 = b->vA(n, 48, 16);
        p->f12 = b->vB(n, 2);
        i = 0;
        p->f2 = n;
        p->f0 = n;
        p->f4 = n;
        while (i < n) {
            p->f12[i] = i;
            i = i + 1;
        }
    }
    arg0->f868 = p;
    arg0->f872 = -1;
}

