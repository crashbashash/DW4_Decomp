int StringChunk_ReleaseHeader();
int igObject_Destroy();
int thunk_FUN_002ed460__002ff810();
extern int DAT_00524950[4];
extern int DAT_00528800[4];
struct Rc { int vt; int rc; };
struct T { int *vt; int w4; char *f8; struct Rc *f12; struct Rc *f16; };
void *FUN_00199330(struct T *arg0, long long arg1) {
    struct Rc *o;
    int *a1;
    int v0;
    if (arg0 != 0) {
        arg0->vt = &DAT_00528800[0];
        if (&arg0->f16 != 0) {
            o = arg0->f16;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        if (&arg0->f12 != 0) {
            o = arg0->f12;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        if (arg0 != 0) {
            arg0->vt = &DAT_00524950[0];
            if (&arg0->f8 != 0) {
                char *p = arg0->f8;
                if (p != 0) {
                    a1 = (int *)(p - 8);
                    v0 = *(int *)(p - 4) - 1;
                    *(int *)(p - 4) = v0;
                    if (v0 == 0) {
                        StringChunk_ReleaseHeader(*a1, a1);
                    }
                }
            }
        }
        if ((short)arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}
