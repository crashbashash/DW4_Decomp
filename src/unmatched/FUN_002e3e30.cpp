struct R { int w0; R(int v) { w0 = v; } R() {} bool operator==(const R &o) const { return w0 == o.w0; } };
struct Ref { int vt; unsigned int _refCount; };
struct RecordFile { char pad[104]; Ref *handle; char pad2[88]; int open; };
extern "C" {
void igObject_Destroy(void *);
void FUN_002e3d30(RecordFile *);
void FUN_002e31b0(Ref *, int);
R FUN_002e3a60(RecordFile *, int, int);
extern R DAT_004fb410[2];
extern R DAT_004fb418[2];
}
extern "C" R FUN_002e3e30(RecordFile *f, int mode) {
    if (f->handle == 0 && mode == 0) {
        return DAT_004fb418[0];
    }
    if (f->handle == 0) {
        if (FUN_002e3a60(f, mode, 5) == DAT_004fb418[0]) {
            if (mode != 0) {
                Ref *h = f->handle;
                if (h != 0) {
                    h->_refCount = (int)h->_refCount - 1;
                    if (((unsigned long long)((long long)(int)h->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(h);
                    }
                }
                f->handle = 0;
            }
            return DAT_004fb418[0];
        }
        f->open = 1;
    }
    if (f->handle == 0) {
        return DAT_004fb418[0];
    }
    FUN_002e3d30(f);
    FUN_002e31b0(f->handle, 5);
    return DAT_004fb410[0];
}
