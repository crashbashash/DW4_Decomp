int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
char *StringPool_Intern();
int igObject_Destroy();
extern int DAT_00586f20[4];
struct R { int w0; int rc; };
struct A { char pad[24]; struct R *f24; char pad2[4]; int *f32; int f36; char f40; };
void Gap__igPsx2Window__vfunc_26(struct A *arg0) {
    int *a1;
    int v1;
    int var_v0;
    struct R *p;
    int *old;
    int *s1;

    arg0->f36 = -1;
    p = arg0->f24;
    if (p != 0) {
        p->rc = p->rc - 1;
        if ((p->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(p);
        }
    }
    arg0->f24 = 0;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
    old = arg0->f32;
    if (old != 0) {
        a1 = old - 2;
        v1 = old[-1] - 1;
        old[-1] = v1;
        if (v1 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->f32 = s1;
    arg0->f40 = 0;
}
