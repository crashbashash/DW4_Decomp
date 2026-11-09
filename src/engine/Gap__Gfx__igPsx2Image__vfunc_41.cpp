#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
struct ConvertedImage : public igVirtualObject { virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void convert(void *, int); char pad[44]; void *pixels; };
struct Stream : public igVirtualObject {
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void close(); virtual void d25(); virtual void d26(); virtual int write(void *, int, int);
    
    void release() {
        _refCount = _refCount - 1;
        if ((_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(this);
        }
    }
};
extern "C" {
int igObject_GetAllocator(igPsx2Image *);
ConvertedImage *FUN_0014df70(int);
int FUN_0015a380(ConvertedImage *);
}

extern "C" int Gap__Gfx__igPsx2Image__vfunc_41(igPsx2Image *image, Stream *stream) {
    igSmartPointer<ConvertedImage> converted(FUN_0014df70(igObject_GetAllocator(image)));
    int word;
    int masks;
    converted->convert(image, 1);
    FUN_0015a380(converted.p);
    word = 0x312A57F2;
    stream->write(&word, 4, 1);
    stream->write(&image->_imageSize, 4, 1);
    stream->write(&image->_px, 4, 1);
    stream->write(&image->_py, 4, 1);
    stream->write(&image->_pz, 4, 1);
    stream->write(&image->_ps, 4, 1);
    masks = (image->_bitsRed << 24) | (image->_bitsGrn << 16) | (image->_bitsBlu << 8) | image->_bitsAlpha;
    stream->write(&masks, 4, 1);
    word = 0;
    stream->write(&word, 4, 1);
    stream->write(&word, 4, 1);
    stream->write(converted->pixels, 1, image->_imageSize);
    stream->close();
    stream->release();
    return 1;
}
