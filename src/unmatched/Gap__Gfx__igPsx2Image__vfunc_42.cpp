#include "dw4/reflected.h"
class ImageCalls {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void copyFrom(igPsx2Image *source, int deep);
    virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void setFormat(int format);
};
extern "C" unsigned char Gap__Gfx__igPsx2Image__vfunc_42(igPsx2Image *self, int format, igPsx2Image *source);
unsigned char Gap__Gfx__igPsx2Image__vfunc_42(igPsx2Image *self, int format, igPsx2Image *source) {
    unsigned char supported = 0;
    switch (source->_pfmt) {
    case 0:
        switch (format) {
        case 0x10000:
            supported = 1;
            break;
        case 1:
        case 0:
            supported = 1;
            break;
        }
        break;
    case 1:
        switch (format) {
        case 0x10000:
            supported = 1;
            break;
        case 0:
        case 1:
            supported = 1;
            break;
        }
        break;
    case 3:
        break;
    case 2:
        switch (format) {
        case 0x10000:
            supported = 1;
            break;
        case 2:
            break;
        }
        break;
    }
    if (supported) {
        if (self != source || !self->_localImage) {
            ((ImageCalls *)self)->copyFrom(source, 1);
        }
        switch (source->_pfmt) {
        case 0:
            switch (format) {
            case 0x10000:
                ((ImageCalls *)self)->setFormat(0x10000);
                self->_bitsInt = 0;
                self->_bitsIdx = 8;
                supported = 1;
                break;
            case 1:
                ((ImageCalls *)self)->setFormat(1);
                self->_bitsInt = 0;
                self->_bitsAlpha = 8;
                break;
            case 0:
                break;
            }
            break;
        case 1:
            switch (format) {
            case 0x10000:
                ((ImageCalls *)self)->setFormat(0x10000);
                self->_bitsAlpha = 0;
                self->_bitsIdx = 8;
                supported = 1;
                break;
            case 0:
                ((ImageCalls *)self)->setFormat(0);
                self->_bitsAlpha = 0;
                self->_bitsInt = 8;
                break;
            case 1:
                break;
            }
            break;
        case 3:
            break;
        case 2:
            switch (format) {
            case 0x10000:
                ((ImageCalls *)self)->setFormat(0x10000);
                self->_bitsInt = 0;
                self->_bitsAlpha = 0;
                self->_bitsIdx = 8;
                supported = 1;
                self->_pz = 1;
                break;
            case 2:
                break;
            }
            break;
        }
    }
    return supported;
}
