#include "dw4/igobject_release.h"
struct igResult { int w0; igResult() {} igResult(int v) { w0 = v; } };
class MediaStream { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual igResult Open(int mode);
    virtual void Close();
    unsigned int _refCount;
};
struct StreamHolder { MediaStream *p; StreamHolder(MediaStream *v) { p = v; } ~StreamHolder(); };
struct MediaStreamOwner { char pad[104]; MediaStream *stream; char pad108[172]; void *source; };
extern "C" {
MediaStream *FUN_002c4ca0(void *);
void FUN_002e30b0(MediaStream *, void *);
void igObject_Destroy(MediaStream *);
extern igResult DAT_004fb418[4];
igResult FUN_002e3a60(MediaStreamOwner *self, void *data, int mode);
}
inline StreamHolder::~StreamHolder() {
    IG_OBJECT_RELEASE(p);
}
static inline void assign(MediaStreamOwner *self, const StreamHolder &h) {
    MediaStream *v = h.p;
    MediaStream *old;
    if (v != 0) {
        v->_refCount = v->_refCount + 1;
    }
    old = self->stream;
    IG_OBJECT_RELEASE(old);
    self->stream = v;
}
igResult FUN_002e3a60(MediaStreamOwner *self, void *data, int mode) {
    if (data == 0 && self->stream == 0) {
        return DAT_004fb418[0];
    }
    if (data == 0 && self->stream != 0) {
        return self->stream->Open(mode);
    }
    if (self->stream == 0 && data != 0) {
        {
            StreamHolder h(FUN_002c4ca0(self->source));
            assign(self, h);
        }
        if (self->stream == 0) {
            return DAT_004fb418[0];
        }
        FUN_002e30b0(self->stream, data);
        return self->stream->Open(mode);
    }
    self->stream->Close();
    {
        StreamHolder h(FUN_002c4ca0(self->source));
        assign(self, h);
    }
    FUN_002e30b0(self->stream, data);
    return self->stream->Open(mode);
}
