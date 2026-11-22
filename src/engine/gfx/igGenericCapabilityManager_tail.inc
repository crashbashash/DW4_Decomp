/* igGenericCapabilityManager vtable slot 23: always answers 1. The
 * igVisualContextCapabilityManager override forwards the same slot to its igVisualContext, so this
 * is a yes/no capability query where the generic manager says "yes". The receiver is not read. */
int Gap__Gfx__igGenericCapabilityManager__vfunc_23(void) {
    return 1;
}

int FUN_00155340(FieldTypeTable *table, unsigned int type) {
    FieldTypeList *list;

    if (type < 47) {
        switch (type) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
            return (int)Gap::Math::igVec4fMetaField::getClassMeta();
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
            return (int)Gap::Math::igMatrix44fMetaField::getClassMeta();
        default:
            return 0;
        }
    }
    list = table->extraTypes;
    if ((int)type < list->_count + 47) {
        int index = type - 47;
        igSmartPointer<FieldTypeEntry> entry(list->_data[index], kRetainReference);
        if (entry == 0) {
            return 0;
        }
        return entry->source->getMetaObject();
    }
    return 0;
}

int FUN_00155490(void) {
    return (int)Gap::Core::igMetaField::getClassMeta();
}

StringRef FUN_001554a0(int arg1) {
    int i;
    char *s;
    int r;
    igSmartPointer<Ref_1554a0> text((Ref_1554a0 *)igStringObj_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString)));
    igStringObj_Set((igStringObj *)((int)(text.get())), (char *)arg1);
    igStringObj_ToLower((igStringObj *)(text.get()));
    for (i = text.get()->len - 1; i >= 0; i--) {
        if (text.get()->str[i] == 0x5F) {
            igStringObj_Erase((igStringObj *)(text.get()), i, 1);
        }
    }
    s = text.get()->str;
    if (s == 0) {
        s = (char *)g_stringObjEmptyText;
    }
    if (s == 0) {
        r = 0;
    } else {
        if (g_stringPool == 0) {
            r = (int)StringPool_Allocate(0x10);
            if (r != 0) {
                r = (int)StringPool_Construct((StringPool *)r);
            }
            g_stringPool = (StringPool *)r;
        }
        r = (int)StringPool_Intern(g_stringPool, s);
    }
    return StringRef((char *)r);
}

void *igObject_GetMetaObject_Virtual(void){return Gap::Core::igObject::getClassMeta();}

void FUN_00155c00(igResult *out, Owner *owner, int id) {
    int i;
    List *l = owner->a;
    if (id >= l->count || l->data[id] == 0) {
        *out = g_resultFailure;
        return;
    }
    for (i = 0; i < owner->b->count; i++) {
        List *lb = owner->b;
        Obj_155c00 *o = lb->data[i];
        if (o && id == o->id) {
            REL(o);
            if (lb->count && i >= 0 && i < lb->count) lb->data[i] = 0;
        }
    }
    {
        List *la = owner->a;
        Obj_155c00 *o = la->data[id];
        REL(o);
        if (la->count && id >= 0 && id < la->count) la->data[id] = 0;
    }
    *out = g_resultSuccess;
}

void FUN_00155db0(O_155db0 *arg0) {
    Ls *s2;
    int s1;
    int s0;
    int n2;
    int a1;
    Rc *o;
    s2 = arg0->f308;
    s1 = s2->cnt;
    for (s0 = 0; s0 < s1; s0++) {
        o = s2->data[s0];
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
    }
    n2 = s2->cnt;
    for (a1 = 0; a1 < n2; a1++) {
        s2->data[a1] = 0;
    }
    s2->cnt = 0;
    s2 = arg0->f304;
    s1 = s2->cnt;
    for (s0 = 0; s0 < s1; s0++) {
        o = s2->data[s0];
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
    }
    n2 = s2->cnt;
    for (a1 = 0; a1 < n2; a1++) {
        s2->data[a1] = 0;
    }
    s2->cnt = 0;
}

int FUN_00155f10(Table *table, int key) {
    StringRef name = FUN_001554a0(key);
    int i = 0;
    if (table->entries->count > 0) {
        for (; i < table->entries->count; i++) {
            igSmartPointer<Entry> entry(table->entries->data[i], kRetainReference);
            if (entry.p == 0) {
                continue;
            }
            if (entry.p->name == name.p) {
                return i;
            }
        }
    }
    return -1;
}

static inline const char *nameOf(const KeyedEntry *entry) {
    return entry->name ? entry->name : emptyString;
}

static NamedValue g_gfxShaderConstantNames[47] = {
    { "constant.zero", 0 },
    { "constant.blendhelper", 1 },
    { "material.ambient", 2 },
    { "material.diffuse", 3 },
    { "material.specular", 4 },
    { "material.emission", 5 },
    { "material.shininess", 6 },
    { "light.point.ambient", 7 },
    { "light.point.diffuse", 8 },
    { "light.point.specular", 9 },
    { "light.point.ambientmaterial", 10 },
    { "light.point.diffusematerial", 11 },
    { "light.point.specularmaterial", 12 },
    { "light.point.position", 13 },
    { "light.point.attenuation", 14 },
    { "light.directional.ambient", 15 },
    { "light.directional.diffuse", 16 },
    { "light.directional.specular", 17 },
    { "light.directional.direction", 18 },
    { "light.directional.half", 19 },
    { "light.directional.ambientmaterial", 20 },
    { "light.directional.diffusematerial", 21 },
    { "light.directional.specularmaterial", 22 },
    { "light.spot.ambient", 23 },
    { "light.spot.diffuse", 24 },
    { "light.spot.specular", 25 },
    { "light.spot.position", 26 },
    { "light.spot.direction", 27 },
    { "light.spot.attenuation", 28 },
    { "light.spot.ambientmaterial", 29 },
    { "light.spot.diffusematerial", 30 },
    { "light.spot.specularmaterial", 31 },
    { "lightmodel.sceneambient", 32 },
    { "lightmodel.sceneambientmaterial", 33 },
    { "lightmodel.lightingambient", 34 },
    { "lightmodel.lightingambientnonspot", 35 },
    { "fog.color", 36 },
    { "fog.parameters", 37 },
    { "point.size", 38 },
    { "point.attenuation", 39 },
    { "matrix.model", 40 },
    { "matrix.view", 41 },
    { "matrix.modelview", 42 },
    { "matrix.projection", 43 },
    { "matrix.mvp", 44 },
    { "matrix.texture", 45 },
    { "matrix.blending", 46 },
};

int igVisualContext_GetStateFieldHandle(KeyedEntryOwner *table, int key) {
    StringRef name = FUN_001554a0(key);
    int i = 0;
    if (table->entries->count > 0) {
        for (i = 0; i < table->entries->count; i++) {
            igSmartPointer<KeyedEntry> entry(table->entries->data[i], kRetainReference);
            if (entry.p && nameOf(entry.p) == name.p) {
                return i + 47;
            }
        }
    }
    for (i = 0; i < 47; i++) {
        if (strcmp(g_gfxShaderConstantNames[i].name, name.p) == 0) {
            return g_gfxShaderConstantNames[i].value;
        }
    }
    return -1;
}

int FUN_001562b0(void) {
    return -1;
}

int FUN_001562c0(void) {
    return -1;
}

int FUN_001562d0(struct A_1562d0 *arg0, int arg1) {
    if (arg1 >= 0x2F) {
        return (*(struct C **)((char *)arg0->b->tab + arg1 * 4 - 188))->fc;
    }
    return -1;
}

namespace Gap {
namespace Gfx {

void igImage::userRegister()
{
    igResource_AddAlignment((igResource *)g_globalContext, "ImageData", 0x10);
    ((igMemoryRefMetaField *)k_pImage)->setAlignmentType("ImageData");
}

void igImage::setName(igStringRef name)
{
    _pNameString = name;
}

void igImage::copy(const igImage *src, bool copyImage)
{
    if (src == this) {
        if (!_localImage && copyImage && _pImage != 0) {
            void *pixels = poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(_imageSize, 0x80);
            memcpy(pixels, _pImage, _imageSize);
            _localImage = true;
            _pImage = (unsigned char *)pixels;
        }
        return;
    }
    _px = src->_px;
    _py = src->_py;
    _pz = src->_pz;
    _ps = src->_ps;
    _order = src->_order;
    _pfmt = src->_pfmt;
    _compressed = src->_compressed;
    setName(src->getName());
    _imageSize = src->_imageSize;
    _bytesPerRow = src->_bytesPerRow;
    _bitsInt = src->_bitsInt;
    _bitsRed = src->_bitsRed;
    _bitsGrn = src->_bitsGrn;
    _bitsBlu = src->_bitsBlu;
    _bitsAlpha = src->_bitsAlpha;
    _bitsIdx = src->_bitsIdx;
    _bitsDepth = src->_bitsDepth;
    if (_pImage != 0 && _localImage) {
        Memory_FreeBuffer(_pImage);
    }
    _pImage = 0;
    if (_pClut != 0) {
        igObject::release(_pClut.p);
        _pClut.p = 0;
    }
    if (copyImage) {
        if (src->_pImage != 0) {
            _pImage = (unsigned char *)poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(_imageSize, 0x80);
            _localImage = true;
            memcpy(_pImage, src->_pImage, _imageSize);
        }
        if (src->_pClut != 0) {
            igMemoryPoolView *pool = getMemoryPool();
            igObject::release(_pClut.p);
            _pClut.p = igClut::_instantiateFromPool(pool);
            _pClut->copy(src->_pClut, true);
        }
    }
}
}
}

namespace Gap {
namespace Gfx {

void igImage::copySubImage(const igImage *src, int offX, int offY, int width, int height)
{
    igSmartPointer<igImage> converted(0);
    igSmartPointer<igImageConvertRows> spare((igImageConvertRows *)igImageConvert_Create((int)getMemoryPool()));
    int imageSize;
    int bytesPerRow;
    unsigned int components;
    const igImage *source;
    char *dstRow;
    const char *srcRow;
    int row;

    if (src->getTotalBitsPerPixel() & 7) {
        igMemoryPoolView *pool = getMemoryPool();
        igObject::release(converted.p);
        converted.p = igImage::_instantiateFromPool(pool);
        igImage *created = converted.p;
        if (!(created->convert(estimateUnpackedFmt2((IG_GFX_TEXTURE_FORMAT)src->_pfmt), src) & 0xFF)) {
            return;
        }
        copy(converted.p, false);
    } else {
        copy(src, false);
    }
    source = src;
    if (converted.p != 0) {
        source = converted.p;
    }
    _px = width;
    _py = height;
    estimateImageSize((IG_GFX_TEXTURE_FORMAT)_pfmt, _px, _py, imageSize, components, bytesPerRow);
    _imageSize = imageSize;
    _pz = components;
    _bytesPerRow = bytesPerRow;
    _pImage = (unsigned char *)poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(_imageSize, 0x80);
    _localImage = true;
    row = 0;
    dstRow = (char *)_pImage;
    srcRow = (const char *)source->_pImage + offY * source->_bytesPerRow + offX * (source->getTotalBitsPerPixel() >> 3);
    while (row < height) {
        memcpy(dstRow, srcRow, _bytesPerRow);
        row++;
        srcRow += source->_bytesPerRow;
        dstRow += _bytesPerRow;
    }
    if (src->_pClut != 0) {
        igMemoryPoolView *pool = getMemoryPool();
        igObject::release(_pClut.p);
        _pClut.p = igClut::_instantiateFromPool(pool);
        _pClut->copy(src->_pClut, true);
    }
    if (src->getTotalBitsPerPixel() & 7) {
        convert((IG_GFX_TEXTURE_FORMAT)src->_pfmt, this);
    }
}
}
}

int FUN_00156ae0(int arg0, int arg1, float fparg0) {
    int var_v0;

    var_v0 = (int)((int) (0.5f + ((float) arg0 * fparg0)));
    if (var_v0 >= arg1) {
        var_v0 = arg1 - 1;
    }
    return var_v0;
}

namespace Gap {
namespace Gfx {

void igImage::setClut(igClut *clut)
{
    _pClut = clut;
}
void igImage::scale(int width, int height, igImage *source)
{
    igSmartPointer<igImageConvertRows> convert((igImageConvertRows *)igImageConvert_Create((int)getMemoryPool()));
    if (source == 0) {
        source = this;
    } else {
        copy(source, false);
    }
    int format;
    char *sourceRow;
    int sourceBytesPerRow;
    int sourceWidth;
    int sourceHeight;
    int pixelSize;
    int order;
    char *sourcePixels;
    igImageRowConvert toPlain;
    igImageRowConvert fromPlain;
    int plainSize;
    unsigned int plainComponents;
    int plainRow;
    int scaledRow;
    int scaledSize;
    int newSize;
    int newRow;
    unsigned int newComponents;
    char *destRow;
    float xScale;
    float yScale;
    char *pixels;
    int y;
    char *row;
    int x;
    format = source->_pfmt;
    sourceRow = 0;
    toPlain = 0;
    sourceBytesPerRow = source->_bytesPerRow;
    fromPlain = 0;
    sourceWidth = source->_px;
    sourceHeight = source->_py;
    pixelSize = source->_pz;
    order = source->_order;
    sourcePixels = (char *)source->_pImage;
    plainSize = source->_imageSize;
    plainComponents = pixelSize;
    plainRow = sourceBytesPerRow;
    destRow = 0;
    if (isPacked((IG_GFX_TEXTURE_FORMAT)source->_pfmt)) {
        IG_GFX_TEXTURE_FORMAT plainFormat = estimateUnpackedFmt2((IG_GFX_TEXTURE_FORMAT)format);
        estimateImageSize(plainFormat, sourceWidth, sourceHeight, plainSize, plainComponents, plainRow);
        sourceRow = (char *)poolOf(this, kIGMemoryPoolHandleTemporary)->allocateAligned(plainRow, 0x80);
        toPlain = convert->v23(order, format, 1);
        fromPlain = convert->v23(order, format, 0);
        estimateImageSize(plainFormat, width, height, scaledSize, plainComponents, scaledRow);
        destRow = (char *)poolOf(this, kIGMemoryPoolHandleTemporary)->allocateAligned(scaledRow, 0x80);
    }
    xScale = (float)(unsigned int)sourceWidth / (float)width;
    yScale = (float)(unsigned int)sourceHeight / (float)height;
    _px = width;
    _py = height;
    estimateImageSize((IG_GFX_TEXTURE_FORMAT)format, _px, _py, newSize, newComponents, newRow);
    _imageSize = newSize;
    _pz = newComponents;
    _bytesPerRow = newRow;
    pixels = (char *)poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(_imageSize, 0x80);
    row = pixels;
    for (y = 0; y < height; y++) {
        int sourceY = FUN_00156ae0(y, sourceHeight, yScale);
        /* Without a conversion the rows are read and written in place, through the same two pointers. */
        if (toPlain != 0) {
            toPlain(sourceRow, sourcePixels + sourceY * sourceBytesPerRow, sourceWidth, 0);
        } else {
            destRow = row;
            sourceRow = sourcePixels + sourceY * sourceBytesPerRow;
        }
        for (x = 0; x < width; x++) {
            int sourceX = FUN_00156ae0(x, sourceWidth, xScale);
            memcpy(destRow + x * pixelSize, sourceRow + sourceX * pixelSize, pixelSize);
        }
        if (fromPlain != 0) {
            fromPlain(row, destRow, width, 0);
        }
        row += _bytesPerRow;
    }
    if (isPacked((IG_GFX_TEXTURE_FORMAT)source->_pfmt)) {
        poolOf(this, kIGMemoryPoolHandleTemporary)->free(destRow);
        poolOf(this, kIGMemoryPoolHandleTemporary)->free(sourceRow);
    }
    if (_pImage != 0 && _localImage) {
        Memory_FreeBuffer(_pImage);
    }
    _pImage = (unsigned char *)pixels;
    _localImage = true;
    if (isIndexed((IG_GFX_TEXTURE_FORMAT)source->_pfmt) && source != this && source->_pClut != 0) {
        igSmartPointer<igClut> clut(igClut::_instantiateFromPool(getMemoryPool()));
        clut->copy(source->_pClut, true);
        setClut(clut.p);
    }
}

bool igImage::canConvert(IG_GFX_TEXTURE_FORMAT tfmt, igSmartPointer<igImageConvertRows> convert) const
{
    bool r = false;
    if (tfmt == _pfmt) {
        return true;
    }
    if (convert->findConverter(_order, (IG_GFX_TEXTURE_FORMAT)_pfmt, tfmt, _px, _py) != 0) {
        r = true;
        if (_pfmt == IG_GFX_TEXTURE_FORMAT_X_8 && tfmt == IG_GFX_TEXTURE_FORMAT_X_4) {
            if (_pClut == 0) {
                r = false;
            } else if (16 < _pClut->getNumEntries()) {
                r = false;
            }
        }
    }
    return r;
}

unsigned char igImage::convert(IG_GFX_TEXTURE_FORMAT format, const igImage *source)
{
    igSmartPointer<igImageConvertRows> convert((igImageConvertRows *)igImageConvert_Create((int)getMemoryPool()));
    int sourceFormat;
    igImageRowConvert rowConvert;
    int sourceBytesPerRow;
    char *pixels;
    igClut *clut;
    int sourceClut;
    if (source == 0) {
        source = this;
    }
    sourceFormat = source->_pfmt;
    if (sourceFormat == format) {
        copy(source, true);
        return true;
    }
    ::igMetaEnum *formatEnum = IG_GFX_TEXTURE_FORMAT_GetMetaEnum();
    igStringRef fromName = ((Gap::Core::igMetaEnum *)formatEnum)->getEnumName(source->_pfmt);
    igStringRef toName = ((Gap::Core::igMetaEnum *)formatEnum)->getEnumName(format);
    if (!source->canConvert(format, convert)) {
        return false;
    }
    unsigned char done = platformConvert(format, source);
    if (done) {
        return done;
    }
    rowConvert = convert->findConverter(source->_order, (IG_GFX_TEXTURE_FORMAT)source->_pfmt, format, _px, _py);
    if (source != this) {
        if (_pImage != 0 && _localImage) {
            Memory_FreeBuffer(_pImage);
        }
        _pImage = 0;
        clut = _pClut.p;
        if (clut != 0) {
            igObject::release(clut);
            _pClut.p = 0;
        }
    }
    sourceBytesPerRow = source->_bytesPerRow;
    _px = source->_px;
    _py = source->_py;
    _order = source->_order;
    _pfmt = format;
    int size;
    int bytesPerRow;
    unsigned int components;
    estimateImageSize(format, _px, _py, size, components, bytesPerRow);
    _imageSize = size;
    _pz = components;
    _bytesPerRow = bytesPerRow;
    unsigned int bitsInt;
    unsigned int bitsIdx;
    unsigned int bitsRed;
    unsigned int bitsGrn;
    unsigned int bitsBlu;
    unsigned int bitsAlpha;
    unsigned int bitsDepth;
    estimateBitDepths(format, bitsInt, bitsIdx, bitsRed, bitsGrn, bitsBlu, bitsAlpha, bitsDepth);
    clut = 0;
    _bitsInt = bitsInt;
    _bitsIdx = bitsIdx;
    _bitsRed = bitsRed;
    _bitsGrn = bitsGrn;
    _bitsBlu = bitsBlu;
    _bitsAlpha = bitsAlpha;
    _bitsDepth = bitsDepth;
    pixels = (char *)poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(_imageSize, 0x80);
    if (source == this) {
        if (isIndexed((IG_GFX_TEXTURE_FORMAT)source->_pfmt) && isIndexed(format)) {
            clut = _pClut.p;
        }
    } else if (isIndexed((IG_GFX_TEXTURE_FORMAT)source->_pfmt) && isIndexed(format) && source->_pClut != 0) {
        clut = igClut::_instantiateFromPool(poolOf(this, kIGMemoryPoolHandleClut));
        clut->copy(source->_pClut, true);
    }
    sourceClut = (int)source->_pClut.p;
    if ((unsigned int)(format - IG_GFX_TEXTURE_FORMAT_RGB_DXT1) <= 3 || format == IG_GFX_TEXTURE_FORMAT_TILED_DXT1_GAMECUBE ||
        sourceFormat == IG_GFX_TEXTURE_FORMAT_TILED_DXT1_GAMECUBE ||
        (unsigned int)(sourceFormat - IG_GFX_TEXTURE_FORMAT_RGB_DXT1) <= 2 || sourceFormat == IG_GFX_TEXTURE_FORMAT_RGBA_DXT5) {
        rowConvert(pixels, (void *)source->_pImage, (unsigned short)_px | ((unsigned short)_py << 16), sourceClut);
        _compressed = true;
    } else {
        unsigned int y;
        char *to = pixels;
        char *from = (char *)source->_pImage;
        for (y = 0; y < _py; y++) {
            rowConvert(to, from, _px, sourceClut);
            to += _bytesPerRow;
            from += sourceBytesPerRow;
        }
    }
    if (_pImage != 0 && _localImage) {
        Memory_FreeBuffer(_pImage);
    }
    _pImage = (unsigned char *)pixels;
    _localImage = true;
    if (format == IG_GFX_TEXTURE_FORMAT_TILED_DXT1_GAMECUBE ||
        (unsigned int)(format - IG_GFX_TEXTURE_FORMAT_TILED_RGBA_5553_16_GAMECUBE) <= 4 ||
        format == IG_GFX_TEXTURE_FORMAT_TILED_RGBA_8888_32_GAMECUBE) {
        int postSize;
        int postBytesPerRow;
        unsigned int postComponents;
        unsigned char *post;
        estimateImageSize(format, _px, _py, postSize, postComponents, postBytesPerRow);
        post = (unsigned char *)poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(postSize, 0x80);
        FUN_0015a750((::igImage *)this, post);
        Memory_FreeBuffer(_pImage);
        _pImage = post;
    }
    if (_pClut.p != clut) {
        igObject::ref(clut);
        igObject::release(_pClut.p);
        _pClut.p = clut;
        igObject::release(_pClut.p);
    }
    autoSetUnfilledParameters();
    return true;
}

/* igFileImagePng vtable slot 42: constant-zero leaf. Slots 40 and 41 also return 0 and slot 45
 * returns 1. The receiver is not read. */
unsigned char igImage::platformConvert(IG_GFX_TEXTURE_FORMAT format, const igImage *img)
{
    return false;
}

void igImage::setPixelFormat(IG_GFX_TEXTURE_FORMAT pixelFormat)
{
    int imageSize;
    int bytesPerRow;
    unsigned int bitsInt;
    unsigned int bitsIdx;
    unsigned int bitsRed;
    unsigned int bitsGrn;
    unsigned int bitsBlu;
    unsigned int bitsAlpha;
    unsigned int bitsDepth;
    unsigned int components;

    _pfmt = pixelFormat;
    if (!isUninterpreted((IG_GFX_TEXTURE_FORMAT)_pfmt)) {
        estimateBitDepths((IG_GFX_TEXTURE_FORMAT)_pfmt, bitsInt, bitsIdx, bitsRed, bitsGrn, bitsBlu, bitsAlpha, bitsDepth);
        _bitsInt = bitsInt;
        _bitsIdx = bitsIdx;
        _bitsRed = bitsRed;
        _bitsGrn = bitsGrn;
        _bitsBlu = bitsBlu;
        _bitsAlpha = bitsAlpha;
        _bitsDepth = bitsDepth;
        estimateImageSize((IG_GFX_TEXTURE_FORMAT)_pfmt, _px, _py, imageSize, components, bytesPerRow);
        _pz = components;
    }
}

void igImage::reduce(igImage *img)
{
    if (img == 0) {
        img = this;
    }
    if (isIndexed((IG_GFX_TEXTURE_FORMAT)img->_pfmt)) {
        reduceAux(img, 1);
        return;
    }
    reduceAux(img, 0);
}

void igImage::setData(void *data, int size)
{
    if (_pImage != 0 && _localImage) {
        Memory_FreeBuffer(_pImage);
    }
    _pImage = (unsigned char *)data;
    _localImage = false;
    autoSetUnfilledParameters();
    _imageSize = size;
}

void igImage::setPlatformSpecificOrder()
{
    _order = IG_GFX_IMAGE_ORDER_PSX2;
}

void igImage::autoSetUnfilledParameters()
{
    unsigned int components;
    int imageSize;
    int bytesPerRow;
    unsigned int bitsInt;
    unsigned int bitsIdx;
    unsigned int bitsRed;
    unsigned int bitsGrn;
    unsigned int bitsBlu;
    unsigned int bitsAlpha;
    unsigned int bitsDepth;
    IG_GFX_TEXTURE_FORMAT format;
    unsigned int numComponents;

    if (!isUninterpreted((IG_GFX_TEXTURE_FORMAT)_pfmt)) {
        if (_pfmt < 0) {
            numComponents = _pz;
            if ((numComponents != 0) && (numComponents < 5U)) {
                _pfmt = guessPixelFormatFromNumComponents(numComponents);
            }
        }
        switch (_pfmt) {
        case IG_GFX_TEXTURE_FORMAT_TILED_DXT1_GAMECUBE:
        case IG_GFX_TEXTURE_FORMAT_RGB_DXT1:
        case IG_GFX_TEXTURE_FORMAT_RGBA_DXT1:
        case IG_GFX_TEXTURE_FORMAT_RGBA_DXT3:
        case IG_GFX_TEXTURE_FORMAT_RGBA_DXT5:
            _compressed = true;
            break;
        }
        format = (IG_GFX_TEXTURE_FORMAT)_pfmt;
        estimateImageSize(format, _px, _py, imageSize, components, bytesPerRow);
        _imageSize = imageSize;
        _bytesPerRow = bytesPerRow;
        estimateBitDepths(format, bitsInt, bitsIdx, bitsRed, bitsGrn, bitsBlu, bitsAlpha, bitsDepth);
        _bitsInt = bitsInt;
        _bitsIdx = bitsIdx;
        _bitsRed = bitsRed;
        _bitsGrn = bitsGrn;
        _bitsBlu = bitsBlu;
        _bitsAlpha = bitsAlpha;
        _bitsDepth = bitsDepth;
        _pz = components;
    }
}

void igImage::allocateImageMemory()
{
    if (_pImage != 0 && _localImage) {
        Memory_FreeBuffer(_pImage);
        _pImage = 0;
    }
    autoSetUnfilledParameters();
    _pImage = (unsigned char *)poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(_imageSize, 0x80);
    _localImage = true;
}

void igImage::setPixel(int x, int y, const void *src)
{
    int bpp = getTotalBitsPerPixel() >> 3;
    memcpy(_pImage + (y * _bytesPerRow + bpp * x), src, bpp);
}

bool igImage::swapComponentOrder()
{
    bool result = true;
    igSmartPointer<igImageConvertView> convert((igImageConvertView *)igImageConvert_Create((int)getMemoryPool()));
    switch (_pfmt) {
    case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32:
        convert->v25(_pImage, _px * _py, &_order);
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_888_24: {
        char *row = (char *)_pImage;
        int rows = _py;
        while (rows != 0) {
            convert->v26(row, _px, &_order);
            rows--;
            row += _bytesPerRow;
        }
        break;
    }
    case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16:
        convert->v27(_pImage, (_bytesPerRow >> 1) * _py, &_order);
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16:
        convert->v28(_pImage, (_bytesPerRow >> 1) * _py, &_order);
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_332_8:
        convert->v30(_pImage, _imageSize, &_order);
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_3328_16:
        convert->v34(_pImage, (_bytesPerRow >> 1) * _py, &_order);
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_565_16:
        convert->v29(_pImage, (_bytesPerRow >> 1) * _py, &_order);
        break;
    case IG_GFX_TEXTURE_FORMAT_LA_88_16:
        convert->v31(_pImage, (_bytesPerRow >> 1) * _py, &_order);
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_2222_8:
        convert->v32(_pImage, _imageSize, &_order);
        break;
    case IG_GFX_TEXTURE_FORMAT_LA_44_8:
        convert->v33(_pImage, _imageSize, &_order);
        break;
    case IG_GFX_TEXTURE_FORMAT_L_8:
    case IG_GFX_TEXTURE_FORMAT_A_8:
    case IG_GFX_TEXTURE_FORMAT_X_8:
    case IG_GFX_TEXTURE_FORMAT_X_4:
    case IG_GFX_TEXTURE_FORMAT_DDS:
    case IG_GFX_TEXTURE_FORMAT_RGB_DXT1:
    case IG_GFX_TEXTURE_FORMAT_RGBA_DXT1:
    case IG_GFX_TEXTURE_FORMAT_RGBA_DXT3:
    case IG_GFX_TEXTURE_FORMAT_RGBA_DXT5:
        break;
    case IG_GFX_TEXTURE_FORMAT_TILED_RGB_565_16_GAMECUBE:
    case IG_GFX_TEXTURE_FORMAT_TILED_RGBA_5553_16_GAMECUBE:
    case IG_GFX_TEXTURE_FORMAT_TILED_DXT1_GAMECUBE:
    case IG_GFX_TEXTURE_FORMAT_RGBA_5553_16:
    case IG_GFX_TEXTURE_FORMAT_TILED_L_8_GAMECUBE:
    case IG_GFX_TEXTURE_FORMAT_TILED_LA_88_16_GAMECUBE:
    case IG_GFX_TEXTURE_FORMAT_TILED_LA_44_8_GAMECUBE:
    case IG_GFX_TEXTURE_FORMAT_TILED_RGBA_8888_32_GAMECUBE:
        setPlatformSpecificOrder();
        return true;
    default:
        result = false;
        break;
    }
    if (result) {
        result = toggleComponentOrder();
    }
    return result;
}

unsigned char igImage::oldLoad(igFile *file)
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

    ((VStream *)file)->v25(&_imageSize, 4, 1);
    ((VStream *)file)->v25(&_pz, 4, 1);
    ((VStream *)file)->v25(&_px, 4, 1);
    ((VStream *)file)->v25(&_py, 4, 1);
    _ps = 1;
    _pImage = (unsigned char *)poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(_imageSize, 0x80);
    _localImage = true;
    ((VStream *)file)->v25(_pImage, 1, _imageSize);
    ((VStream *)file)->v24();
    switch (_pz) {
    case 1:
        _pfmt = IG_GFX_TEXTURE_FORMAT_L_8;
        break;
    case 2:
        _pfmt = IG_GFX_TEXTURE_FORMAT_LA_88_16;
        break;
    case 3:
        _pfmt = IG_GFX_TEXTURE_FORMAT_RGB_888_24;
        break;
    case 4:
        _pfmt = IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
        break;
    default:
        _pfmt = IG_GFX_TEXTURE_FORMAT_RGB_888_24;
        _pz = 3;
        break;
    }
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
    _order = IG_GFX_IMAGE_ORDER_DEFAULT;
    return true;
}

unsigned char igImage::newLoad(igFile *file)
{
    unsigned int skippedWord;
    unsigned int maskWord;
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
    VStream *st = (VStream *)file;

    if (!(platformLoad(file) & 0xFF)) {
        st->v25(&_imageSize, 4, 1);
        st->v25(&_px, 4, 1);
        st->v25(&_py, 4, 1);
        st->v25(&_pz, 4, 1);
        st->v25(&_ps, 4, 1);
        st->v25(&maskWord, 4, 1);
        _bitsRed = (maskWord >> 24) & 0xFF;
        _bitsGrn = (maskWord >> 16) & 0xFF;
        _bitsBlu = (maskWord >> 8) & 0xFF;
        _bitsAlpha = (unsigned char)maskWord;
        _bitsDepth = 0;
        _bitsIdx = 0;
        _bitsInt = 0;
        st->v25(&skippedWord, 4, 1);
        st->v25(&skippedWord, 4, 1);
        _pImage = (unsigned char *)poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(_imageSize, 0x80);
        _localImage = true;
        st->v25(_pImage, 1, _imageSize);
        st->v24();
        _pfmt = guessPixelFormatFromNumComponents(_pz);
    }
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
    _order = IG_GFX_IMAGE_ORDER_DEFAULT;
    return true;
}

/* Constant leaf in the igFileImagePng vtable (slot 40): ignores the image object and returns 0,
 * like the adjacent slots 39 and 41. */
unsigned char igImage::platformLoad(igFile *file)
{
    return false;
}

unsigned char igImage::load(const char *fileName)
{
    unsigned int bitsInt;
    unsigned int bitsIdx;
    unsigned int bitsRed;
    unsigned int bitsGrn;
    unsigned int bitsBlu;
    unsigned int bitsAlpha;
    unsigned int bitsDepth;
    int r;

    if (_pImage != 0 && _localImage) {
        Memory_FreeBuffer(_pImage);
    }
    _pImage = 0;
    _bitsInt = 0;
    _bitsIdx = 0;
    _bitsRed = 0;
    _bitsGrn = 0;
    _bitsBlu = 0;
    _bitsAlpha = 0;
    _bitsDepth = 0;
    setName(fileName);
    if ((platformLoad(fileName) & 0xFF) == 1) {
        if (_pfmt < 0) {
            _pfmt = guessPixelFormatFromNumComponents(_pz);
            estimateBitDepths((IG_GFX_TEXTURE_FORMAT)_pfmt, bitsInt, bitsIdx, bitsRed, bitsGrn, bitsBlu, bitsAlpha, bitsDepth);
            _bitsInt = bitsInt;
            _bitsIdx = bitsIdx;
            _bitsRed = bitsRed;
            _bitsGrn = bitsGrn;
            _bitsBlu = bitsBlu;
            _bitsAlpha = bitsAlpha;
            _bitsDepth = bitsDepth;
        }
        return true;
    }
    igSmartPointer<VStream_158f50> file((VStream_158f50 *)Gap::Core::igFile::_instantiateFromPool(getMemoryPool()));
    int signature;
    if (file.p->v23((int)fileName, "rb") == 0) {
        return false;
    }
    file.p->v25(&signature, 4, 1);
    switch (signature) {
    case 0x1F295FF4:
    case 0xF45F291F:
        r = oldLoad((igFile *)file.p) & 0xFF;
        return r;
    case 0x312A57F2:
    case 0xF2572A31:
        r = newLoad((igFile *)file.p) & 0xFF;
        return r;
    default:
        file.p->v24();
        return false;
    }
}

/* Constant leaf in the igFileImagePng vtable (slot 39): ignores the image object and returns 0,
 * like the adjacent slots 40 and 41. */
unsigned char igImage::platformLoad(const char *fileName)
{
    return false;
}

/* igFileImagePng vtable slot 41: constant-zero leaf. Slots 40 and 42 also return 0 and slot 45
 * returns 1. The receiver is not read. */
unsigned char igImage::platformSave(igFile *file)
{
    return false;
}

void igImage::releaseDefaults()
{
    if (_pName != 0) {
        free(_pName);
    }
    if (_pImage != 0 && _localImage) {
        Memory_FreeBuffer(_pImage);
        _pImage = 0;
    }
}

int igImage::estimateImageSize(IG_GFX_TEXTURE_FORMAT pfmt, unsigned int w, unsigned int h, int &imageSize, unsigned int &stride, int &pitch)
{
    if (pfmt == IG_GFX_TEXTURE_FORMAT_UNINTERPRETED) {
        return -1;
    }
    switch (pfmt) {
    case IG_GFX_TEXTURE_FORMAT_L_8:
        stride = 1;
        pitch = w;
        break;
    case IG_GFX_TEXTURE_FORMAT_A_8:
        stride = 1;
        pitch = w;
        break;
    case IG_GFX_TEXTURE_FORMAT_LA_44_8:
        stride = 2;
        pitch = w;
        break;
    case IG_GFX_TEXTURE_FORMAT_LA_88_16:
        stride = 2;
        pitch = w * 2;
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_332_8:
        stride = 3;
        pitch = w;
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_888_24:
        stride = 3;
        pitch = w * 3;
        break;
    case IG_GFX_TEXTURE_FORMAT_Z_8:
        stride = 1;
        pitch = w;
        break;
    case IG_GFX_TEXTURE_FORMAT_Z_16:
        stride = 2;
        pitch = w * 2;
        break;
    case IG_GFX_TEXTURE_FORMAT_Z_24:
        stride = 3;
        pitch = w * 3;
        break;
    case IG_GFX_TEXTURE_FORMAT_Z_32:
        stride = 4;
        pitch = w * 4;
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_2222_8:
        stride = 4;
        pitch = w;
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32:
    case IG_GFX_TEXTURE_FORMAT_TILED_RGBA_8888_32_GAMECUBE:
        stride = 4;
        pitch = w * 4;
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16:
        stride = 4;
        pitch = w * 2;
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_565_16:
        stride = 3;
        pitch = w * 2;
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16:
        stride = 4;
        pitch = w * 2;
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_3328_16:
        stride = 4;
        pitch = w * 2;
        break;
    case IG_GFX_TEXTURE_FORMAT_X_8:
        stride = 1;
        pitch = w;
        break;
    case IG_GFX_TEXTURE_FORMAT_X_4:
        stride = 1;
        pitch = (w + 1) >> 1;
        break;
    case IG_GFX_TEXTURE_FORMAT_XA_88_16:
        stride = 2;
        pitch = w * 2;
        break;
    case IG_GFX_TEXTURE_FORMAT_RGBA_5553_16:
    case IG_GFX_TEXTURE_FORMAT_TILED_RGBA_5553_16_GAMECUBE:
    {
        int blocksWide = w >> 2;
        int blocksHigh = h >> 2;
        stride = 4;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = (blocksWide * blocksHigh) << 5;
        pitch = blocksWide * 8;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_TILED_LA_88_16_GAMECUBE:
    {
        int blocksWide = w >> 2;
        int blocksHigh = h >> 2;
        stride = 2;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = (blocksWide * blocksHigh) << 5;
        pitch = blocksWide * 8;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_TILED_L_8_GAMECUBE:
    {
        int blocksWide = w >> 2;
        int blocksHigh = h >> 3;
        stride = 1;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = (blocksWide * blocksHigh) << 5;
        pitch = blocksWide * 4;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_TILED_LA_44_8_GAMECUBE:
    {
        int blocksWide = w >> 2;
        int blocksHigh = h >> 3;
        stride = 2;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = (blocksWide * blocksHigh) << 5;
        pitch = blocksWide * 4;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_TILED_RGB_565_16_GAMECUBE:
    {
        int blocksWide = w >> 2;
        int blocksHigh = h >> 2;
        stride = 3;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = (blocksWide * blocksHigh) << 5;
        pitch = blocksWide * 8;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_TILED_Z_8_GAMECUBE:
    {
        int blocksWide = w >> 2;
        int blocksHigh = h >> 3;
        stride = 1;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = (blocksWide * blocksHigh) << 6;
        pitch = blocksWide * 4;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_TILED_Z_16_GAMECUBE:
    {
        int blocksWide = w >> 2;
        int blocksHigh = h >> 2;
        stride = 1;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = (blocksWide * blocksHigh) << 5;
        pitch = blocksWide * 8;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_TILED_Z_32_GAMECUBE:
    {
        int blocksWide = w >> 2;
        int blocksHigh = h >> 2;
        stride = 1;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = (blocksWide * blocksHigh) << 6;
        pitch = blocksWide * 16;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_TILED_DXT1_GAMECUBE:
    case IG_GFX_TEXTURE_FORMAT_RGB_DXT1:
    case IG_GFX_TEXTURE_FORMAT_RGBA_DXT1:
    {
        int blocksWide = w >> 2;
        int blocksHigh;
        stride = 4;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = h >> 2;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = blocksWide * blocksHigh * 8;
        pitch = blocksWide * 8;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_RGBA_DXT3:
    case IG_GFX_TEXTURE_FORMAT_RGBA_DXT5:
    {
        int blocksWide = w >> 2;
        int blocksHigh;
        stride = 4;
        blocksWide = blocksWide > 1 ? blocksWide : 1;
        blocksHigh = h >> 2;
        blocksHigh = blocksHigh > 1 ? blocksHigh : 1;
        imageSize = blocksWide * blocksHigh * 16;
        pitch = blocksWide * 16;
        return imageSize;
    }
    case IG_GFX_TEXTURE_FORMAT_V8U8_DX:
        stride = 2;
        pitch = w * 2;
        break;
    case IG_GFX_TEXTURE_FORMAT_V16U16_DX:
        stride = 2;
        pitch = w * 4;
        break;
    case IG_GFX_TEXTURE_FORMAT_L6V5U5_DX:
        stride = 3;
        pitch = w * 2;
        break;
    case IG_GFX_TEXTURE_FORMAT_Q8W8V8U8_DX:
        stride = 4;
        pitch = w * 4;
        break;
    case IG_GFX_TEXTURE_FORMAT_X8L8V8U8_DX:
        stride = 4;
        pitch = w * 4;
        break;
    default:
        return imageSize;
    }
    correctBytesPerRow(pitch);
    imageSize = h * pitch;
    return imageSize;
}

void igImage::estimateBitDepths(IG_GFX_TEXTURE_FORMAT pfmt, unsigned int &bI, unsigned int &bIdx, unsigned int &bR, unsigned int &bG, unsigned int &bB, unsigned int &bA, unsigned int &bD)
{
    if (!isUninterpreted(pfmt)) {
        bI = 0;
        bIdx = 0;
        bR = 0;
        bG = 0;
        bB = 0;
        bA = 0;
        bD = 0;
        switch (pfmt) {
        case IG_GFX_TEXTURE_FORMAT_L_8:
        case IG_GFX_TEXTURE_FORMAT_TILED_L_8_GAMECUBE:
            bI = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_A_8:
            bA = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_LA_44_8:
        case IG_GFX_TEXTURE_FORMAT_TILED_LA_44_8_GAMECUBE:
            bI = 4;
            bA = 4;
            break;
        case IG_GFX_TEXTURE_FORMAT_LA_88_16:
        case IG_GFX_TEXTURE_FORMAT_TILED_LA_88_16_GAMECUBE:
            bI = 8;
            bA = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_RGB_332_8:
            bR = 3;
            bG = 3;
            bB = 2;
            bA = 0;
            break;
        case IG_GFX_TEXTURE_FORMAT_TILED_Z_8_GAMECUBE:
        case IG_GFX_TEXTURE_FORMAT_Z_8:
            bD = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_TILED_Z_16_GAMECUBE:
        case IG_GFX_TEXTURE_FORMAT_Z_16:
            bD = 16;
            break;
        case IG_GFX_TEXTURE_FORMAT_Z_24:
            bD = 24;
            break;
        case IG_GFX_TEXTURE_FORMAT_TILED_Z_32_GAMECUBE:
        case IG_GFX_TEXTURE_FORMAT_Z_32:
            bD = 32;
            break;
        case IG_GFX_TEXTURE_FORMAT_RGB_888_24:
            bR = 8;
            bG = 8;
            bB = 8;
            bA = 0;
            break;
        case IG_GFX_TEXTURE_FORMAT_RGBA_2222_8:
            bR = 2;
            bG = 2;
            bB = 2;
            bA = 2;
            break;
        case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32:
        case IG_GFX_TEXTURE_FORMAT_TILED_RGBA_8888_32_GAMECUBE:
            bR = 8;
            bG = 8;
            bB = 8;
            bA = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16:
            bR = 5;
            bG = 5;
            bB = 5;
            bA = 1;
            break;
        case IG_GFX_TEXTURE_FORMAT_TILED_RGB_565_16_GAMECUBE:
        case IG_GFX_TEXTURE_FORMAT_RGB_565_16:
            bR = 5;
            bG = 6;
            bB = 5;
            break;
        case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16:
            bR = 4;
            bG = 4;
            bB = 4;
            bA = 4;
            break;
        case IG_GFX_TEXTURE_FORMAT_RGBA_3328_16:
            bR = 3;
            bG = 3;
            bB = 2;
            bA = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_X_8:
            bIdx = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_X_4:
            bIdx = 4;
            break;
        case IG_GFX_TEXTURE_FORMAT_XA_88_16:
            bIdx = 8;
            bA = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_RGBA_5553_16:
        case IG_GFX_TEXTURE_FORMAT_TILED_RGBA_5553_16_GAMECUBE:
            bR = 4;
            bG = 4;
            bB = 4;
            bA = 4;
            break;
        case IG_GFX_TEXTURE_FORMAT_TILED_DXT1_GAMECUBE:
        case IG_GFX_TEXTURE_FORMAT_RGB_DXT1:
        case IG_GFX_TEXTURE_FORMAT_RGBA_DXT1:
            bR = 1;
            bG = 1;
            bB = 1;
            bA = 1;
            break;
        case IG_GFX_TEXTURE_FORMAT_RGBA_DXT3:
        case IG_GFX_TEXTURE_FORMAT_RGBA_DXT5:
            bR = 2;
            bG = 2;
            bB = 2;
            bA = 2;
            break;
        case IG_GFX_TEXTURE_FORMAT_V8U8_DX:
            bR = 8;
            bG = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_V16U16_DX:
            bR = 16;
            bG = 16;
            break;
        case IG_GFX_TEXTURE_FORMAT_L6V5U5_DX:
            bR = 5;
            bG = 5;
            bA = 6;
            break;
        case IG_GFX_TEXTURE_FORMAT_Q8W8V8U8_DX:
            bR = 8;
            bG = 8;
            bB = 8;
            bA = 8;
            break;
        case IG_GFX_TEXTURE_FORMAT_X8L8V8U8_DX:
            bR = 8;
            bG = 8;
            bB = 8;
            bA = 8;
            /* matching construct: variant search — the closing case and default end in `return;`; the deleted
             * jumps stop fall-through slot filling, so the case blocks keep retail's copied first instructions */
            return;
        default:
            return;
        }
    }
}

IG_GFX_TEXTURE_FORMAT igImage::guessPixelFormatFromNumComponents(unsigned int numComponents)
{
    IG_GFX_TEXTURE_FORMAT r;
    switch (numComponents) {
    case 1: r = IG_GFX_TEXTURE_FORMAT_L_8; break;
    case 2: r = IG_GFX_TEXTURE_FORMAT_LA_88_16; break;
    case 3: r = IG_GFX_TEXTURE_FORMAT_RGB_888_24; break;
    case 4: r = IG_GFX_TEXTURE_FORMAT_RGBA_8888_32; break;
    default: r = IG_GFX_TEXTURE_FORMAT_INVALID; break;
    }
    return r;
}

bool igImage::isIndexed(IG_GFX_TEXTURE_FORMAT fmt)
{
    return (unsigned int)((fmt - 0x8000) - 0x8000) < 3U;
}

bool igImage::isPacked(IG_GFX_TEXTURE_FORMAT fmt)
{
    bool r = true;
    if (!isPackedSubByte(fmt)) {
        bool b = true;
        bool a = false;
        unsigned int t = fmt - 2;
        if (t < 0x18U && ((1 << t) & 0x987FD5)) {
            a = true;
        }
        if (!a && 1U < (unsigned int)(fmt - 0x22)) {
            b = false;
        }
        if (!b) {
            r = false;
        }
    }
    return r;
}

bool igImage::isPackedSubByte(IG_GFX_TEXTURE_FORMAT fmt)
{
    return fmt == IG_GFX_TEXTURE_FORMAT_X_4;
}

void igImage::userPostLoad()
{
    igObject::userPostLoad();
    if (_pName != 0) {
        _pNameString = _pName;
        free(_pName);
        _pName = 0;
    }
    fixBytesPerRowAndReallocate();
}

void igImage::userPostRead()
{
    igObject::userPostRead();
}

void igImage::fixBytesPerRowAndReallocate()
{
    int n;
    int j;
    unsigned i;
    unsigned char *src;
    unsigned char *dst;
    unsigned char *buf;
    int v = _bytesPerRow;
    if (v > 0) {
        n = v;
    } else {
        n = (unsigned)_imageSize / _py;
    }
    autoSetUnfilledParameters();
    if (_pImage != 0 && n != _bytesPerRow) {
        buf = (unsigned char *)poolOf(this, kIGMemoryPoolHandleImage)->allocateAligned(_imageSize, 0x80);
        src = _pImage;
        dst = buf;
        for (i = 0; i < _py; i++) {
            for (j = 0; j < n; j++) {
                *dst = *src;
                src++;
                dst++;
            }
            dst += _bytesPerRow - n;
        }
        Memory_FreeBuffer(_pImage);
        _pImage = buf;
    }
}

unsigned char igImage::hasAlpha(IG_GFX_TEXTURE_FORMAT fmt)
{
    unsigned char r = 0;
    long long one = 1;
    unsigned int t = fmt - 1;
    if (t < 35) {
        if ((one << t) & 0x401900DE7LL) {
            r = one;
        }
    }
    return r;
}

bool igImage::isUninterpreted(IG_GFX_TEXTURE_FORMAT fmt)
{
    return fmt == IG_GFX_TEXTURE_FORMAT_UNINTERPRETED;
}

void igImage::scaleAlpha(unsigned char *dp, int nSample, IG_GFX_TEXTURE_FORMAT fmt)
{
    int i;
    switch (fmt) {
    case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32:
        for (i = 0; i < nSample; i++) {
            unsigned char t = dp[3];
            dp[3] = (t >> 1) + (t & 1);
            dp += 4;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_A_8:
    case IG_GFX_TEXTURE_FORMAT_LA_88_16:
    case IG_GFX_TEXTURE_FORMAT_LA_44_8:
    case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16:
    case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16:
        break;
    }
}

void igImage::unScaleAlpha(unsigned char *dp, int nSample, IG_GFX_TEXTURE_FORMAT fmt)
{
    int i;
    int v;
    int c;
    switch (fmt) {
    case IG_GFX_TEXTURE_FORMAT_RGBA_8888_32:
        for (i = 0; i < nSample; i++) {
            c = dp[3];
            if (c & 0x80) {
                v = ~(c & 0xff) << 1;
            } else {
                v = c << 1;
            }
            dp[3] = v;
            dp += 4;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_A_8:
    case IG_GFX_TEXTURE_FORMAT_LA_88_16:
    case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16:
    case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16:
    default:
        break;
    }
}

int igImage::unScaleAlpha()
{
    if (!hasAlpha((IG_GFX_TEXTURE_FORMAT)_pfmt) && !isIndexed((IG_GFX_TEXTURE_FORMAT)_pfmt)) {
        return 1;
    }
    if (_pImage != 0) {
        unScaleAlpha(_pImage, _px * _py, (IG_GFX_TEXTURE_FORMAT)_pfmt);
    }
    if (isIndexed((IG_GFX_TEXTURE_FORMAT)_pfmt) && _pClut != 0) {
        return _pClut->unScaleAlpha();
    }
    return 1;
}

void igImage::load(void *data, IG_GFX_TEXTURE_FORMAT pixelFormat, IG_GFX_IMAGE_ORDER order, int width, int height)
{
    setPixelFormat(pixelFormat);
    setWidth(width);
    setHeight(height);
    setComponentOrder(order);
    if (data != _pImage) {
        allocateImageMemory();
        memcpy(_pImage, data, _imageSize);
    } else {
        _localImage = true;
        autoSetUnfilledParameters();
    }
}

void igImage::load(void *data, IG_GFX_TEXTURE_FORMAT pixelFormat, int width, int height)
{
    setWidth(width);
    setHeight(height);
    setPlatformSpecificOrder();
    setPixelFormat(pixelFormat);
    if (data != _pImage) {
        allocateImageMemory();
        memcpy(_pImage, data, (unsigned int)_imageSize);
    } else {
        _localImage = true;
        autoSetUnfilledParameters();
    }
}

int igImage::scaleAlpha()
{
    int t;
    if (!hasAlpha((IG_GFX_TEXTURE_FORMAT)_pfmt) && !isIndexed((IG_GFX_TEXTURE_FORMAT)_pfmt)) {
        return 1;
    }
    if (_pImage != 0) {
        scaleAlpha(_pImage, _px * _py, (IG_GFX_TEXTURE_FORMAT)_pfmt);
    }
    if (isIndexed((IG_GFX_TEXTURE_FORMAT)_pfmt)) {
        if (_pClut != 0) {
            return _pClut->scaleAlpha();
        }
    }
    return 1;
}
}
}

void FUN_0015a6a0(Img *arg0, E *out) {
    int w;
    int h;
    E *r0;
    E *r1;
    int x;
    int y;
    long long t;
    long long u;
    w = arg0->w >> 2;
    h = arg0->h >> 2;
    r0 = arg0->data;
    r1 = r0 + w;
    for (y = 0; y < h; y += 2) {
        for (x = 0; x < w; x += 2) {
            /* matching construct: spelling grid — field-wise copies through two shared temporaries keep the ld/ld/sd/sd pairs */
            t = r0[0].a; u = r0[0].b; out[0].a = t; out[0].b = u;
            t = r0[1].a; u = r0[1].b; out[1].a = t; out[1].b = u;
            t = r1[0].b; u = r1[0].a; out[2].a = u; out[2].b = t;
            t = r1[1].b; u = r1[1].a; out[3].a = u; out[3].b = t;
            r0 += 2;
            r1 += 2;
            out += 4;
        }
        r0 += w;
        r1 += w;
    }
}

void FUN_0015aaf0(unsigned char *dst, unsigned char *src, int count)
{
    int i;
    unsigned int packed;

    for (i = 0; i < count - 1; i += 2) {
        packed = src[0] & 0xF;
        packed |= src[1] << 4;
        *dst++ = packed;
        src += 2;
    }
    if (i < count)
        *dst = (*src & 0xF) << 4;
}

void FUN_0015ab50(void *dst, const void *src, unsigned int size) {
    if (dst != src) {
        memmove(dst, src, size);
    }
}

void FUN_0015ab70(void *dst, const void *src, unsigned int size) {
    if (dst != src) {
        memmove(dst, src, size);
    }
}

/* matching construct: 24-variant sweep — statement and declaration order */
void FUN_0015ab90(unsigned char *dst, unsigned char *src, int count)
{
    int i;
    unsigned int packed;

    dst = dst + count - 1;
    src = src + ((count + 1) >> 1) - 1;
    i = 0;
    if (count & 1) {
        *dst = ((unsigned int)*src >> 4) & 0xF;
        i++;
        src--;
        dst--;
    }
    for (; i < count; i += 2) {
        packed = *src;
        dst[0] = (packed >> 4) & 0xF;
        dst[-1] = packed & 0xF;
        src--;
        dst -= 2;
    }
}

namespace Gap {
namespace Gfx {

IG_GFX_TEXTURE_FORMAT igImage::estimateUnpackedFmt2(IG_GFX_TEXTURE_FORMAT packed)
{
    int x = packed;
    switch (x) {
    default:
        switch (x) {
        case IG_GFX_TEXTURE_FORMAT_LA_44_8: return IG_GFX_TEXTURE_FORMAT_LA_88_16;
        case IG_GFX_TEXTURE_FORMAT_RGB_332_8: return IG_GFX_TEXTURE_FORMAT_RGB_888_24;
        case IG_GFX_TEXTURE_FORMAT_RGBA_2222_8: return IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
        case IG_GFX_TEXTURE_FORMAT_RGBA_5551_16:
        case IG_GFX_TEXTURE_FORMAT_RGBA_5553_16: return IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
        case IG_GFX_TEXTURE_FORMAT_X_4: return IG_GFX_TEXTURE_FORMAT_X_8;
        }
        break;
    case IG_GFX_TEXTURE_FORMAT_RGB_565_16: return IG_GFX_TEXTURE_FORMAT_RGB_888_24;
    case IG_GFX_TEXTURE_FORMAT_RGBA_4444_16: return IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
    case IG_GFX_TEXTURE_FORMAT_RGBA_3328_16: return IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
    }
    if (isPacked((IG_GFX_TEXTURE_FORMAT)x)) {
        x = -1;
    }
    return (IG_GFX_TEXTURE_FORMAT)x;
}
}
}

void FUN_0015ad20(void *loader, igImage *image, void *pixels)
{
    image->_pImage = (int)pixels;
}

void FUN_0015ad30(void *loader, igImage *image, int format, int width, int height, int *size, int *components,
                  int *rowBytes) {
    ((Gap::Gfx::igImage *)image)->estimateImageSize((IG_GFX_TEXTURE_FORMAT)format, width, height, *size, *(unsigned int *)components, *rowBytes);
}

int FUN_0015ad50(char *arg0) {
    int n = strlen(arg0);

    while (n > 0) {
        n--;
        if (arg0[n] == 0x2E) {
            return (int)arg0 + n;
        }
    }
    return 0;
}

namespace Gap {
namespace Gfx {

unsigned int igIndexArray::configure(unsigned int num, unsigned int usageFlags, IG_GFX_INDEX_DATA_SIZE dataSize, igVisualContext *context)
{
    unsigned int size;

    if (_indexData != 0) {
        return 0;
    }
    _numIndices = num;
    _dataSize = dataSize;
    _usageFlags = usageFlags;
    if (dataSize == IG_GFX_INDEX_SIZE_16_BIT) {
        size = _numIndices * 2;
    } else {
        size = _numIndices * 4;
    }
    if (_memPool == 0) {
        _memPool = (igMemoryPool *)getMemoryPool();
    }
    _indexData = (unsigned char *)((igMemoryPoolView *)_memPool.p)->malloc(size);
    return size;
}

unsigned int igIndexArray::reconfigure(unsigned int num, unsigned int usageFlags, IG_GFX_INDEX_DATA_SIZE dataSize, igVisualContext *context)
{
    unsigned int count;
    unsigned int *oldIndices32;
    unsigned short *oldIndices16;
    unsigned int result;
    unsigned int i;
    unsigned int *indices32;
    unsigned short *indices16;

    count = _numIndices;
    count = (count < num) ? count : num;
    oldIndices32 = 0;
    oldIndices16 = 0;
    reset();
    if (dataSize == IG_GFX_INDEX_SIZE_16_BIT) {
        oldIndices16 = (unsigned short *)_indexData;
    } else {
        oldIndices32 = (unsigned int *)_indexData;
    }
    _indexData = 0;
    _numIndices = 0;
    result = configure(num, usageFlags, dataSize, context);
    if (oldIndices16 != 0) {
        if (dataSize == IG_GFX_INDEX_SIZE_16_BIT) {
            memcpy(_indexData, oldIndices16, count * 2);
        } else {
            indices32 = (unsigned int *)_indexData;
            for (i = 0; i < count; i++) {
                indices32[i] = oldIndices16[i];
            }
        }
        Memory_FreeBuffer(oldIndices16);
    } else {
        if (dataSize == IG_GFX_INDEX_SIZE_32_BIT) {
            memcpy(_indexData, oldIndices32, count * 4);
        } else {
            indices16 = (unsigned short *)_indexData;
            for (i = 0; i < count; i++) {
                indices16[i] = oldIndices32[i];
            }
        }
        Memory_FreeBuffer(oldIndices32);
    }
    cache();
    return result;
}

void igIndexArray::setIndex16(unsigned int indexNumber, unsigned short value)
{
    ((unsigned short *)_indexData)[indexNumber] = value;
}

void igIndexArray::setIndex32(unsigned int indexNumber, unsigned int value)
{
    ((unsigned int *)_indexData)[indexNumber] = value;
}

void igIndexArray::setIndex(unsigned int indexNumber, unsigned int value)
{
    switch (_dataSize) {
    case IG_GFX_INDEX_SIZE_32_BIT:
        setIndex32(indexNumber, value);
        break;
    case IG_GFX_INDEX_SIZE_16_BIT:
        setIndex16((unsigned short)indexNumber, value);
        break;
    }
}

unsigned short igIndexArray::getIndex16(unsigned int indexNumber)
{
    return ((unsigned short *)_indexData)[indexNumber];
}

unsigned int igIndexArray::getIndex32(unsigned int indexNumber)
{
    return ((unsigned int *)_indexData)[indexNumber];
}

unsigned int igIndexArray::getIndex(unsigned int indexNumber)
{
    switch (_dataSize) {
    case IG_GFX_INDEX_SIZE_32_BIT:
        return getIndex32(indexNumber);
    case IG_GFX_INDEX_SIZE_16_BIT:
        return getIndex16((unsigned short)indexNumber);
    default:
        return 0;
    }
}

/* arg1 is unused but must stay: the value arrives in the third parameter (a2), and a two-parameter
 * spelling would put it in a1. */
unsigned short *igIndexArray::getEditableIndices16(unsigned int editFlags, unsigned int startIndex, unsigned int num)
{
    return (unsigned short *)_indexData + startIndex;
}

unsigned int *igIndexArray::getEditableIndices32(unsigned int editFlags, unsigned int startIndex, unsigned int num)
{
    return (unsigned int *)_indexData + startIndex;
}

void igIndexArray::commitIndexEdits(unsigned short *indices, unsigned int commitFlags, unsigned int startIndex, unsigned int num) {

}

void igIndexArray::commitIndexEdits(unsigned int *indices, unsigned int commitFlags, unsigned int startIndex, unsigned int num) {

}
}
}

void FUN_0015b1e0(void *arg0) {
    *(int *)((char *)arg0 + 0) = 0;
    *(int *)((char *)arg0 + 4) = 0;
    *(int *)((char *)arg0 + 8) = 0;
    *(int *)((char *)arg0 + 12) = 0;
    *(int *)((char *)arg0 + 16) = 0;
    *(int *)((char *)arg0 + 20) = 0;
    *(int *)((char *)arg0 + 24) = 0;
    *(int *)((char *)arg0 + 28) = 0;
    *(int *)((char *)arg0 + 32) = 0;
    *(int *)((char *)arg0 + 36) = 0;
    *(int *)((char *)arg0 + 40) = 0;
    *(int *)((char *)arg0 + 44) = 0;
    *(int *)((char *)arg0 + 48) = 0;
    *(int *)((char *)arg0 + 52) = 0;
    *(int *)((char *)arg0 + 56) = 0;
    *(int *)((char *)arg0 + 60) = 0;
    *(int *)((char *)arg0 + 64) = 0;
    *(int *)((char *)arg0 + 68) = 0;
    *(int *)((char *)arg0 + 72) = 0;
    *(int *)((char *)arg0 + 76) = 0;
    *(int *)((char *)arg0 + 80) = 0;
    *(int *)((char *)arg0 + 84) = 0;
    *(int *)((char *)arg0 + 88) = 0;
    *(int *)((char *)arg0 + 92) = 0;
    *(int *)((char *)arg0 + 96) = 0;
    *(int *)((char *)arg0 + 100) = 0;
    *(int *)((char *)arg0 + 104) = 0;
    *(int *)((char *)arg0 + 108) = 0;
    *(int *)((char *)arg0 + 112) = 0;
    *(int *)((char *)arg0 + 116) = 0x3F800000;
    *(int *)((char *)arg0 + 120) = 0x3F800000;
    *(int *)((char *)arg0 + 124) = 0;
    *(int *)((char *)arg0 + 128) = 0;
    *(int *)((char *)arg0 + 132) = 0;
    *(int *)((char *)arg0 + 136) = 0;
    *(int *)((char *)arg0 + 140) = 0;
}

