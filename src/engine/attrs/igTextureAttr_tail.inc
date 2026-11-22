char *igTextureAttr_GetFileName(char *arg0) {
    char *p;
    char c;

    if (arg0 == 0) {
        return 0;
    }
    p = arg0 + strlen(arg0);
    for (; arg0 < p; p--) {
        c = p[-1];
        if (c == 0x5C || c == 0x2F) {
            break;
        }
    }
    return p;
}

namespace Gap {
namespace Attrs {

char *igTextureAttr::generateKey(bool stripPath, igMemoryPoolView *mp)
{
    char text[8204];

    if (mp == 0) {
        mp = (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault);
    }
    igSmartPointer<igImage> image(getImage(0), kRetainReference);
    const char *name = "NO_IMAGE";
    if (image != 0) {
        if (image->getName() != 0) {
            name = igTextureAttr_GetFileName((char *)image->getName());
        }
    }
    sprintf(text, "%s %d %d %d %d %d %d %d %d", name, _bColor, getMagnificationFilter(), getMinificationFilter(), getWrapS(), getWrapT(), (long long)_mipmapMode, (long long)_source, (long long)_paging);
    char *key = (char *)mp->Allocate(strlen(text) + 1);
    strcpy(key, text);
    return key;
}

bool igTextureAttr::isKeyForAttr(char *key)
{
    int bColor;
    int magFilter;
    int minFilter;
    int wrapS;
    int wrapT;
    int mipmapMode;
    int source;
    int paging;
    char name[8192];
    const char *imageName;
    const char *fileName;

    if (sscanf(key, "%s %d %d %d %d %d %d %d %d", name, &bColor, &magFilter, &minFilter, &wrapS, &wrapT, &mipmapMode, &source, &paging) != 9) {
        return false;
    }
    fileName = "NO_IMAGE";
    imageName = "NO_IMAGE";
    if (getImage(0) != 0) {
        if (getImage(0)->getName() != 0) {
            fileName = igTextureAttr_GetFileName((char *)getImage(0)->getName());
        }
        imageName = fileName;
    }
    if (strcmp(name, imageName) == 0) {
        if (bColor == _bColor) {
            if ((magFilter == _magFilter) && (minFilter == _minFilter) && (wrapS == _wrapS) && (wrapT == _wrapT) && (mipmapMode == _mipmapMode) && (source == _source) && (paging == _paging)) {
                return true;
            }
        }
    }
    return false;
}

void igTextureAttr::synchronizeDefault(igVisualContext *vc)
{

}

void igTextureAttr::userPostLoad()
{
    if (_imageCount == 0) {
        _imageCount = 1;
    }
    igVisualAttribute::userPostLoad();
}

void igTextureAttr::apply(igVisualContext *vc)
{
    if (_texId < 0) {
        igImage *image;
        switch (_source) {
        case IG_GFX_TEXTURE_SOURCE_IMAGE:
        case IG_GFX_TEXTURE_SOURCE_IMAGE_REF:
        default: {
            int level;
            image = _image;
            if (image == 0) {
                return;
            }
            _texId = Gap__Gfx__igPsx2VisualContext__createTexture((igPsx2VisualContext *)vc, image->_px, image->_py, image->_pfmt, 0, _mipmapMode, _imageCount);
            for (level = 0; level < _imageCount; level++) {
                igImage *levelImage;
                if (level == 0) {
                    levelImage = _image;
                } else {
                    levelImage = ((igImage **)((::igImageMipMapList *)(igImageMipMapList *)_imageMipMaps)->_data)[level - 1];
                }
                igPsx2VisualContext_SetTextureSourceLevel(vc, _texId, (::igImage *)levelImage, level);
            }
            break;
        }
        case IG_GFX_TEXTURE_SOURCE_VIDEO:
            image = _image;
            if (image == 0) {
                return;
            }
            _texId = Gap__Gfx__igPsx2VisualContext__createTexture((igPsx2VisualContext *)vc, image->_px, image->_py, image->_pfmt, 2, 0, 1);
            break;
        case IG_GFX_TEXTURE_SOURCE_BUFFER:
        case IG_GFX_TEXTURE_SOURCE_BUFFER_REF:
            image = _image;
            if (image == 0) {
                return;
            }
            _texId = Gap__Gfx__igPsx2VisualContext__createTexture((igPsx2VisualContext *)vc, image->_px, image->_py, image->_pfmt, 3, 0, 1);
            break;
        }
        _vc = vc;
    }
    if (_source == IG_GFX_TEXTURE_SOURCE_VIDEO) {
        igPsx2VisualContext_SetTextureSourceFromBuffer((igPsx2VisualContext *)vc, _texId, _videoBuffer);
    }
    igPsx2VisualContext_SetTextureAddressingMode((igPsx2VisualContext *)vc, _texId, getWrapS(), getWrapT());
    igPsx2VisualContext_SetTextureMinificationFilter((igPsx2VisualContext *)vc, _texId, getMinificationFilter());
    igPsx2VisualContext_SetTextureMagnificationFilter((igPsx2VisualContext *)vc, _texId, getMagnificationFilter());
}

void igTextureAttr::setImage(igImage *img, int level)
{
    if (level == 0) {
        _image = img;
        return;
    }
    if (_imageMipMaps->getCount() == 0) {
        _imageMipMaps->setCount(_imageCount - 1);
    }
    /* the kit's _imageMipMaps->set(level - 1, img), written through the flat list: retail keeps level * 4 for both
     * the read of the old image and the store */
    ::igImageMipMapList *list = (::igImageMipMapList *)(igImageMipMapList *)_imageMipMaps;
    ::igObject::ref((::igObject *)img);
    int offset = level * 4;
    ::igObject::release(*(::igObject **)((char *)list->_data + offset - 4));
    int count = list->_count;
    int index = level - 1;
    if (count != 0 && index >= 0 && index < count) {
        *(igImage **)(offset + (int)list->_data - 4) = img;
    }
}

igImage *igTextureAttr::getImage(int level) const
{
    if (level == 0) {
        return _image;
    }
    /* through the flat list's data word: with the kit's get() MWCC swaps the list and index registers */
    return ((igImage **)((::igImageMipMapList *)(igImageMipMapList *)_imageMipMaps)->_data)[level - 1];
}

void igTextureAttr::releaseDefaults()
{
    reset();
    igVisualAttribute::releaseDefaults();
}

void igTextureAttr::reset()
{
    if (_texId != -1 && _vc != 0)
        ((igVisualContextDispatchView *)(igVisualContext *)_vc)->deleteTexture(_texId);
    _texId = -1;
    _vc = 0;
}
}
}

