#include "dw4/reflected.h"
extern "C" {
void *FUN_002d7e90(...);
int FUN_002d7f10(...);
int FUN_002d8310(...);
int igObject_IsKindOf(...);
int igMetaField_ShallowCopy(...);
void *igMetaObject_CreateInstanceDefault(...);
void *igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igObjectSystem_FindMetaByNameDefault(...);
int igObject_Destroy(...);
extern int DAT_00585b70[4];
extern int DAT_00586128[4];
extern int DAT_00587198[4];
void FUN_00309c90(igDirectory *arg0, int arg1, int arg2);
}
/* matching construct: dummy virtual slots so vX() dispatches through the retail vtable offset (igMetaField slot at +0x50) */
struct MetaFieldVirtual { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *vX(); };
struct C1 {
    igObjectDirEntry *Cast(void *p) {
        if (p != 0 && igObject_IsKindOf(p, DAT_00585b70[0]) != 0) { return (igObjectDirEntry *)p; }
        return 0;
    }
};
void FUN_00309c90(igDirectory *arg0, int arg1, int arg2)
{
    C1 c;
    igObject *spAC;
    igObject *spA8;
    igObject *spA4;
    igObject *spA0;
    int s4, s3, s7, i, s8, s1;
    igObjectDirEntry *o;
    if (arg0 != 0) {
        s4 = igObjectSystem_FindMetaByNameDefault(arg1);
        s3 = igObjectSystem_FindMetaByNameDefault(arg2);
        if (s4 != 0) {
            s7 = arg0->_count;
            for (i = 0; i < s7; i++) {
                o = c.Cast(FUN_002d7e90(arg0, i));
                if (o != 0 && igObject_IsKindOf((igObject *)o->_ref, s4) != 0) {
                    igObject *t;
                    if (s3 == 0) return;
                    *(igObject * volatile *)&spAC = (igObject *)o->_ref;
                    t = *(igObject * volatile *)&spAC;
                    if (t) t->_refCount = t->_refCount + 1;
                    *(igObject * volatile *)&spA8 = (igObject *)igMetaObject_CreateInstanceDefault(s3);
                    t = *(igObject * volatile *)&spA8;
                    if (t) t->_refCount = t->_refCount + 1;
                    {
                        igObject *u = spA8;
                        u->_refCount = u->_refCount - 1;
                        if (((unsigned long long)(long long)u->_refCount & 0x7fffffULL) == 0) igObject_Destroy(u);
                    }
                    s8 = igMetaObject_GetFieldCount(s4);
                    s1 = igMetaObject_GetFieldCount(DAT_00587198[0]);
                    for (; s1 < s8; s1++) {
                        igMetaField *f = (igMetaField *)igMetaObject_GetFieldAt(s4, s1);
                        igMetaField *g = (igMetaField *)igMetaObject_FindFieldByName(s3, f->_fieldName);
                        if (g != 0) { bool ok = igObject_IsKindOf(g, ((MetaFieldVirtual *)f)->vX()) != 0; bool nok = ok ^ true; if (!nok) { igMetaField_ShallowCopy(f, (char *)spA8 + g->_offset - f->_offset, spAC); } }
                    }
                    *(igObject * volatile *)&spA4 = spAC;
                    t = *(igObject * volatile *)&spA4;
                    if (t) t->_refCount = t->_refCount + 1;
                    *(igObject * volatile *)&spA0 = spA8;
                    t = *(igObject * volatile *)&spA0;
                    if (t) t->_refCount = t->_refCount + 1;
                    FUN_002d7f10(arg0, &spA4, &spA0);
                    if (spA0 != 0) {
                        spA0->_refCount = spA0->_refCount - 1;
                        if (((unsigned long long)(long long)spA0->_refCount & 0x7fffffULL) == 0) igObject_Destroy(spA0);
                    }
                    if (spA4 != 0) {
                        spA4->_refCount = spA4->_refCount - 1;
                        if (((unsigned long long)(long long)spA4->_refCount & 0x7fffffULL) == 0) igObject_Destroy(spA4);
                    }
                    if (igObject_IsKindOf(spA8, DAT_00586128[0]) != 0) {
                        FUN_002d8310(arg0, spA8);
                    }
                    {
                        igObject *u = spA8;
                        if (u != 0) {
                            u->_refCount = u->_refCount - 1;
                            if (((unsigned long long)(long long)u->_refCount & 0x7fffffULL) == 0) igObject_Destroy(u);
                        }
                    }
                    {
                        igObject *u = spAC;
                        if (u != 0) {
                            u->_refCount = u->_refCount - 1;
                            if (((unsigned long long)(long long)u->_refCount & 0x7fffffULL) == 0) igObject_Destroy(u);
                        }
                    }
                }
            }
        }
    }
}
