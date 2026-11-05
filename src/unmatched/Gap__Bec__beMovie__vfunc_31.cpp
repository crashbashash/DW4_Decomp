#include "dw4/reflected.h"
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class MovieVirtual {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual int v30(int *);
};
struct ItemPtrList { int pad0[2]; int count; int pad1; int **items; };
struct InfoHolder { int pad0[5]; ItemPtrList *list; };
struct MovieInfoArg { int pad0[3]; InfoHolder *inner; };
extern "C" {
int FUN_00236f80(int, int);
int *bePadManager_GetPadForPlayer(int, int);
int igObject_IsKindOf(void *, int);
int beLua__RunNamedChunk(int, int, int);
int igStrCmp(int *, int *);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
void StringChunk_ReleaseHeader(int, void *);
extern int DAT_004e0858[4];
extern int DAT_00586f20[4];
extern int DAT_00588518[4];
extern int DAT_00588760[4];
extern int DAT_00589208[4];
void Gap__Bec__beMovie__vfunc_31(beMovie *self, MovieInfoArg *arg1);
}
void Gap__Bec__beMovie__vfunc_31(beMovie *self, MovieInfoArg *arg1) {
    int *pad; int flags; MovieVirtual *o; bool ok; int h; ItemPtrList *l; int i; beMovieInfoData *it; int *name;
    int *t; int ref; int *hdr; int cnt; int off;
    if ((int *)self->_playingName != 0) {
        pad = bePadManager_GetPadForPlayer(FUN_00236f80(self->_insight, DAT_00588518[0]), 0);
        flags = pad[18];
        if ((flags & 8) || (flags & 0x4000)) {
            o = (MovieVirtual *)self->_movie;
            if (o != 0) o->v26();
        }
        o = (MovieVirtual *)self->_movie;
        ok = false;
        if (o != 0) {
            if (o->v30((int *)self->_playingName) == 2) ok = true;
        } else ok = true;
        if (ok) {
            h = FUN_00236f80(self->_insight, DAT_00589208[0]);
            l = arg1->inner->list;
            for (i = 0; i < l->count; i++) {
                it = (beMovieInfoData *)l->items[i];
                if (it != 0 && igObject_IsKindOf(it, DAT_00588760[0]) != 0) { it = (beMovieInfoData *)it; } else it = 0;
                if (it == 0) goto done;
                name = (int *)it->_name;
                if (name != 0) { name = (int *)name; } else name = DAT_004e0858;
                if (igStrCmp((int *)self->_playingName, name) == 0) {
                    beLua__RunNamedChunk(h, it->_callLuaName, 0);
                    break;
                }
            }
block25: /* matching construct: unreferenced label kept from the matching draft */
            if (DAT_00586f20[0] == 0) {
                ref = FUN_002eb010(16);
                if (ref) ref = StringPool_Construct(ref);
                DAT_00586f20[0] = ref;
            }
            ref = StringPool_Intern(DAT_00586f20[0], 0);
            t = (int *)self->_playingName;
            if (t) {
                hdr = t - 2;
                cnt = t[-1] - 1;
                t[-1] = cnt;
                if (cnt == 0) StringChunk_ReleaseHeader(*hdr, hdr);
            }
            self->_playingName = ref;
        }
    }
done:;
}
