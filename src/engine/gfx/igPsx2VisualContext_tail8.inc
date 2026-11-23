namespace Gap {
namespace Gfx {

IG_GFX_PIXEL_PIPELINE_MODE igPsx2VisualContext::getPixelPipelineMode() const {
    return _pixelPipelineMode;
}
}
}

/* A colour with its alpha rescaled between the full 0-255 range and the GS's 0-128 range:
 * alphaRange 0x80 halves it, 0xFF doubles it back, anything else leaves the colour as it is. */
static inline unsigned int rescaleColorAlpha(unsigned int color, int alphaRange) {
    unsigned int carry;
    if (alphaRange == 0x80) {
        return (color & 0xFFFFFF) | (((color >> 1) & 0x7F000000) + (color & 0x01000000));
    }
    if (alphaRange == 0xFF) {
        carry = (color & 0x80000000) >> 7;
        return (color & 0xFFFFFF) | (carry + (((color & 0xFF000000) - carry) * 2));
    }
    return color;
}

/* Stores each colour of `colors` into `converted` with its alpha rescaled to `alphaRange`. */
void FUN_0017fd80(Gap::Core::igUnsignedIntList **colors, Gap::Core::igUnsignedIntList **converted, int alphaRange) {
    unsigned int i = 0;
    unsigned int color;
    Gap::Core::igUnsignedIntList *list;
    while (i < (unsigned int)(*colors)->_count) {
        color = (*colors)->get(i);
        color = rescaleColorAlpha(color, alphaRange);
        list = *converted;
        if (list->_count != 0 && (int)i >= 0 && (int)i < list->_count) {
            list->get(i) = color;
        }
        i++;
    }
}

