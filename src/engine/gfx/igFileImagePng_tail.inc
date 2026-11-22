/* matching construct: sweep of about 30 spellings — the combined null test */
void FUN_001673a0(png_structp png_ptr, png_row_infop row_info, png_bytep data) {
    if (png_ptr == 0 || row_info == 0) {
        return;
    }
}

namespace Gap {
namespace Gfx {

void igFileImagePng::releaseDefaults()
{
    igImage::releaseDefaults();
}

void igFileImagePng::copy(const igImage *src, bool copyImage)
{
    igImage::copy(src, copyImage);
    src->getMeta();
}

int igFileImagePng::cleanup(png_structp png, png_infop info, png_infop endInfo, void *rowPointers, void *pixels, int result, int reading)
{
    if (rowPointers != 0) {
        free(rowPointers);
    }
    if (pixels != 0) {
        free(pixels);
    }
    if (png != 0) {
        if (reading != 0) {
            png_destroy_read_struct(&png, &info, &endInfo);
        } else {
            png_destroy_info_struct(png, &endInfo);
            png_destroy_write_struct(&png, &info);
        }
    }
    if (_file != 0) {
        _file->fclose();
        _file->release();
    }
    _file = 0;
    return result;
}

IG_GFX_TEXTURE_FORMAT igFileImagePng::estimatePixelFormat(int bitDepth, int colorType, png_color_8p significantBits, IG_GFX_TEXTURE_FORMAT *format)
{
    IG_GFX_TEXTURE_FORMAT result = IG_GFX_TEXTURE_FORMAT_INVALID;
    *format = result;
    switch (colorType) {
    case PNG_COLOR_TYPE_GRAY:
        switch (bitDepth) {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
            *format = IG_GFX_TEXTURE_FORMAT_L_8;
            result = *format;
            break;
        }
        break;
    case PNG_COLOR_TYPE_RGB:
        switch (bitDepth) {
        case 8:
        case 16:
            *format = IG_GFX_TEXTURE_FORMAT_RGB_888_24;
            result = *format;
            if (significantBits != 0) {
                if (significantBits->red == 3 && significantBits->green == 3 && significantBits->blue == 2) {
                    result = IG_GFX_TEXTURE_FORMAT_RGB_332_8;
                } else if (significantBits->red == 5 && significantBits->green == 6 && significantBits->blue == 5) {
                    result = IG_GFX_TEXTURE_FORMAT_RGB_565_16;
                } else if (significantBits->red == 8 && significantBits->green == 8 && significantBits->blue == 8) {
                    result = IG_GFX_TEXTURE_FORMAT_RGB_888_24;
                }
            }
        }
        break;
    case PNG_COLOR_TYPE_PALETTE:
        switch (bitDepth) {
        case 8:
            *format = IG_GFX_TEXTURE_FORMAT_X_8;
            result = *format;
            break;
        case 4:
        case 2:
        case 1:
            *format = IG_GFX_TEXTURE_FORMAT_X_8;
            result = IG_GFX_TEXTURE_FORMAT_X_4;
            break;
        }
        break;
    case PNG_COLOR_TYPE_GRAY_ALPHA:
        switch (bitDepth) {
        case 8:
        case 16:
            *format = IG_GFX_TEXTURE_FORMAT_LA_88_16;
            result = *format;
            if (significantBits != 0) {
                if (significantBits->gray == 4 && significantBits->alpha == 4) {
                    result = IG_GFX_TEXTURE_FORMAT_LA_44_8;
                } else if (significantBits->gray == 8 && significantBits->alpha == 8) {
                    result = IG_GFX_TEXTURE_FORMAT_LA_88_16;
                }
            }
        }
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
        switch (bitDepth) {
        case 8:
        case 16:
            *format = IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
            result = *format;
            if (significantBits != 0) {
                if (significantBits->red == 5 && significantBits->green == 5 && significantBits->blue == 5 && significantBits->alpha == 1) {
                    result = IG_GFX_TEXTURE_FORMAT_RGBA_5551_16;
                } else if (significantBits->red == 2 && significantBits->green == 2 && significantBits->blue == 2 && significantBits->alpha == 2) {
                    result = IG_GFX_TEXTURE_FORMAT_RGBA_2222_8;
                } else if (significantBits->red == 4 && significantBits->green == 4 && significantBits->blue == 4 && significantBits->alpha == 4) {
                    result = IG_GFX_TEXTURE_FORMAT_RGBA_4444_16;
                } else if (significantBits->red == 8 && significantBits->green == 8 && significantBits->blue == 8 && significantBits->alpha == 8) {
                    result = IG_GFX_TEXTURE_FORMAT_RGBA_8888_32;
                }
            }
        }
        break;
    }
    return result;
}

bool igFileImagePng::setReadTransforms(png_structp png, png_infop info)
{
    png_uint_32 width;
    png_uint_32 height;
    int bitDepth;
    int colorType;
    int interlaceType;
    int compressionType;
    int filterType;

    png_get_IHDR(png, info, &width, &height, &bitDepth, &colorType, &interlaceType, &compressionType, &filterType);
    png_set_strip_16(png);
    if ((bitDepth < 8) && (colorType == PNG_COLOR_TYPE_PALETTE)) {
        png_set_packing(png);
    }
    if (bitDepth < 8) {
        if (colorType == PNG_COLOR_TYPE_GRAY) {
            png_set_gray_1_2_4_to_8(png);
        }
    }
    if ((png_get_valid(png, info, PNG_INFO_tRNS) != 0) && !(colorType & PNG_COLOR_MASK_ALPHA) && !(colorType & PNG_COLOR_MASK_PALETTE)) {
        png_set_tRNS_to_alpha(png);
    }
    png_set_read_user_transform_fn(png, FUN_001673a0);
    return true;
}

bool igFileImagePng::toggleComponentOrder()
{
    return true;
}
}
}

