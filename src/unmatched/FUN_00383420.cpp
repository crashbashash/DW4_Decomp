#include "dw4/reflected.h"
/* Selects the text group whose two names match an entry of a layout table, pushes the entry's
 * active refcounted object (the caller's, or one converted from its string) through the group's
 * fragment list and the panel's current slot, then moves the finished fragment into the entry's
 * output list. */
struct Ref;
extern "C" {

void igObject_Destroy(void *);
int igStrCmp(const char *, const char *);
int FUN_0015db90(void *);
Ref FUN_00382eb0(void *, const char *);
int FUN_00383350(void *, int, void *);
void FUN_00383ab0(void *, void *, int, int);
void FUN_00383bf0(void *, int, void *, void *);
void FUN_00383ed0(void *, int, void *, void *);
void FUN_00384010(void *, void *, void *, void *);
void ObjectList_AppendRetained(void *, void *);
void List_RemoveWordAt(void *, int);
class Source {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual igMetaObject *getInfo();
};
class Sink {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void drop(void *, int);
};
class Slot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void apply(Sink *, int);
};
struct Entry { char p0[8]; const int *name1; int p12; int names; char p20[16]; int kind; int key; };
struct Table { char p0[20]; igObjectList *entries; };
struct Layout { char p0[12]; Table *table; };
extern const char *DAT_004c22f0[4];
extern int DAT_004e0858[4];
extern char DAT_0050e798[16];
extern char DAT_0050e7a8[16];
}
struct Ref {
    beUnicodeObj *p;
    Ref(beUnicodeObj *x) { p = x; }
    ~Ref() { beUnicodeObj *o; if ((o = p) != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_00383420(beFont *self, Layout *layout, Source *src, int idx) {
    Entry *ent = (Entry *)((int *)layout->table->entries->_data)[idx];
    igAttrSet *out = (igAttrSet *)((int *)((igObjectList *)((igAttrSet *)((int *)((igObjectList *)((igAttrSet *)ent->names)->_childList)->_data)[0])->_childList)->_data)[0];
    void *keep = (void *)((int *)((igObjectList *)out->_attributes)->_data)[0];
    Ref cur(0);
    igMetaObject *info;
    if (cur.p != 0) ++cur.p->_refCount;
    info = src->getInfo();
    if (igStrCmp((const char *)info->_name, DAT_0050e798) == 0) {
        const char *s0 = (const char *)((igStringObj *)src)->_buffer;
        const char *s;
        if (s0 == 0) s = DAT_004c22f0[0]; else s = s0;
        Ref tmp(FUN_00382eb0(self, s));
        beUnicodeObj *n = tmp.p;
        if (n != 0) ++n->_refCount;
        beUnicodeObj *o = cur.p;
        if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); }
        cur.p = n;
    } else if (igStrCmp((const char *)info->_name, DAT_0050e7a8) == 0) {
        if (src != 0) ++((beUnicodeObj *)src)->_refCount;
        beUnicodeObj *o = cur.p;
        if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); }
        cur.p = (beUnicodeObj *)src;
    } else {
        return;
    }
    beFontGeomAttrPairList *gl = (beFontGeomAttrPairList *)self->_gaPairList;
    beFontGeomAttrPair *g = 0;
    beFontGeomAttrPairList *l = gl;
    int i;
    beFontGeomAttrPair *e;
    int off;
    if (l->_count > 0) {
        i = 0;
        if (i < l->_count) {
            off = 0;
            do {
                e = (beFontGeomAttrPair *)((int *)((char *)l->_data + off))[0];
                const int *a = ent->name1;
                const int *a2;
                if (a != 0) a2 = a; else a2 = DAT_004e0858;
                if ((int)a2 == e->_category) {
                    const int *b = (const int *)((igAttrSet *)ent->names)->_name;
                    const int *b2;
                    if (b != 0) b2 = b; else b2 = DAT_004e0858;
                    if ((int)b2 == e->_panel) { g = e; break; }
                }
                l = gl;
                i++;
                off += 4;
            } while (i < *(volatile int *)&l->_count);
        }
    }
    int fid = cur.p->_buffer;
    self->_fontIdx = FUN_00383350(self, ent->key, gl);
    igGeometryAttr *fr = (igGeometryAttr *)((int *)((igObjectList *)g->_geomAttrs)->_data)[0];
    FUN_00383ab0(self, fr, fid, 1);
    Sink *sk = (Sink *)fr->_vertexArray;
    ((Slot *)((int *)((beFontImageList *)self->_fonts)->_data)[self->_fontIdx])->apply(sk, fid);
    char bufB[32];
    char buf9[32];
    FUN_0015db90(bufB);
    FUN_0015db90(buf9);
    FUN_00384010(self, sk, bufB, buf9);
    FUN_00383bf0(self, fid, ent, bufB);
    if (ent->kind == 1 || ent->kind == 2) FUN_00383ed0(self, fid, ent, bufB);
    sk->drop(buf9, 0);
    sk->drop(bufB, 0);
    ObjectList_AppendRetained((void *)g->_geomAttrs, keep);
    igObjectList *fl = (igObjectList *)out->_attributes;
    if (fr != 0) ++fr->_refCount;
    igGeometryAttr *old = (igGeometryAttr *)((int *)fl->_data)[0];
    if (old != 0) { --old->_refCount; if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old); }
    int k = 0;
    if (fl->_count != 0 && k >= 0 && k < fl->_count) ((int *)fl->_data)[0] = (int)fr;
    igObjectList *fl2 = (igObjectList *)g->_geomAttrs;
    igGeometryAttr *old2 = (igGeometryAttr *)((int *)fl2->_data)[0];
    if (old2 != 0) { --old2->_refCount; if ((old2->_refCount & 0x7fffff) == 0) igObject_Destroy(old2); }
    List_RemoveWordAt(fl2, 0);
    ((int *)fl2->_data)[fl2->_count] = 0;
}
