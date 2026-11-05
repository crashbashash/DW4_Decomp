extern "C" {
int StringChunk_ReleaseHeader(...);
void thunk_FUN_002ed460__002ff810(void *);
extern int DAT_00524950[4];
extern int DAT_00530360[4];
extern int DAT_00530900[4];
}
struct Str { int *p;
    ~Str() { if (p != 0) { int *h = p - 2; int r = p[-1] - 1; p[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
struct W { int *vt; Str s4; Str s8; char pad[16]; Str s28; Str s32; char pad2[4]; Str s40; };
extern "C" W *FUN_0014f580(W *t, short flag);
W *FUN_0014f580(W *t, short flag)
{
    if (t != 0) {
        t->vt = DAT_00530360;
        t->s40.~Str();
        t->s32.~Str();
        t->s28.~Str();
        if (t != 0) {
            t->vt = DAT_00530900;
            if (t != 0) {
                t->vt = DAT_00524950;
                t->s8.~Str();
            }
        }
        if (flag > 0) {
            thunk_FUN_002ed460__002ff810(t);
        }
    }
    return t;
}
