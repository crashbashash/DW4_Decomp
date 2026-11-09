typedef struct PngSignificantBits {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char gray;
    unsigned char alpha;
} PngSignificantBits;

int FUN_00167540(void *png, int bitDepth, int colorType, PngSignificantBits *bits, int *format) {
    int result = -1;
    *format = result;
    switch (colorType) {
    case 0:
        switch (bitDepth) {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
            *format = 0;
            result = *format;
            break;
        }
        break;
    case 2:
        switch (bitDepth) {
        case 8:
        case 16:
            *format = 5;
            result = *format;
            if (bits != 0) {
                if (bits->red == 3 && bits->green == 3 && bits->blue == 2) {
                    result = 4;
                } else if (bits->red == 5 && bits->green == 6 && bits->blue == 5) {
                    result = 10;
                } else if (bits->red == 8 && bits->green == 8 && bits->blue == 8) {
                    result = 5;
                }
            }
        }
        break;
    case 3:
        switch (bitDepth) {
        case 8:
            *format = 0x10000;
            result = *format;
            break;
        case 4:
        case 2:
        case 1:
            *format = 0x10000;
            result = 0x10001;
            break;
        }
        break;
    case 4:
        switch (bitDepth) {
        case 8:
        case 16:
            *format = 3;
            result = *format;
            if (bits != 0) {
                if (bits->gray == 4 && bits->alpha == 4) {
                    result = 2;
                } else if (bits->gray == 8 && bits->alpha == 8) {
                    result = 3;
                }
            }
        }
        break;
    case 6:
        switch (bitDepth) {
        case 8:
        case 16:
            *format = 7;
            result = *format;
            if (bits != 0) {
                if (bits->red == 5 && bits->green == 5 && bits->blue == 5 && bits->alpha == 1) {
                    result = 8;
                } else if (bits->red == 2 && bits->green == 2 && bits->blue == 2 && bits->alpha == 2) {
                    result = 6;
                } else if (bits->red == 4 && bits->green == 4 && bits->blue == 4 && bits->alpha == 4) {
                    result = 9;
                } else if (bits->red == 8 && bits->green == 8 && bits->blue == 8 && bits->alpha == 8) {
                    result = 7;
                }
            }
        }
        break;
    }
    return result;
}
