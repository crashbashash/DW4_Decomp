class igResult;
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const; };
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
struct IgbBlockStream { char p0[20]; int mode; };
struct IgbBlockCursor { char p0[80]; int offset; int done; int total; char p92[12]; IgbBlockStream *stream; char p108[108]; int pending; char p220[32]; int mark; char p256[4]; int cap; int base; };
extern "C" {
igResult FUN_002e7030(IgbBlockCursor *);
int FUN_002e3a10(IgbBlockCursor *, int);
}
extern "C" void Gap__Core__igIGBFile__vfunc_26(IgbBlockCursor *self, int at) {
    if (self->stream->mode == 4) {
        int prev = self->base + self->offset;
        self->offset = at - self->base;
        self->done = self->done + (at - prev);
        if (self->done != self->total) {
            if (self->offset > self->cap - 9) {
                FUN_002e7030(self);
                return;
            }
            if (self->offset + (self->pending * 4 + FUN_002e3a10(self, at)) > self->cap) {
                FUN_002e7030(self);
            }
        }
    } else {
        self->mark = at;
    }
}
