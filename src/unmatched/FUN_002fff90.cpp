#include "dw4/reflected.h"
struct Desc { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(void*,int); };
struct Fld { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(void*); };
struct Dat { char p0[4]; int f4; int f8; short s12; };
struct Obj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual igMetaObject* v20(); };
extern "C" {
Desc *igShortMetaField_GetDefaultDescriptor();
int FUN_002fc740(igMetaField*, Obj*, char*, int, int);
int igObject_IsKindOf(igMetaField*, void*);
Desc *igIntMetaField_GetDefaultDescriptor();
int igMetaField_Reset(igMetaField*, Obj*);
igMetaField *igMetaObject_GetFieldAt(igMetaObject*, int);
int igMetaObject_GetFieldCount(igMetaObject*);
extern int DAT_00585a60[4];
extern igMetaObject *DAT_00587198[4];
int FUN_002fff90(Obj *arg0, Dat *arg1, int arg2, int arg3, int arg4) {
    igMetaObject *m;
    char *s2;
    int s1;
    int cnt;
    int s6, s7;
    igMetaField *f;
    m = arg0->v20();
    if (m->_persistent == 0) return 0;
    if (arg4 != 0) {
        igIntMetaField_GetDefaultDescriptor()->v50(arg1, 3);
    }
    s2 = (char *)arg1 + 12;
    s1 = igMetaObject_GetFieldCount(DAT_00587198[0]);
    cnt = igMetaObject_GetFieldCount(m);
    s6 = 0;
    s7 = 0;
    for (; s1 < cnt; s1++) {
        f = igMetaObject_GetFieldAt(m, s1);
        if (f->_isRunTime != 0) {
            s6 += 1;
            ((Fld *)f)->v29(arg0);
            if (igObject_IsKindOf(f, (void*)DAT_00585a60[0]) == 0 || *(unsigned char *)((char *)f + 52) == 0) igMetaField_Reset(f, arg0);
        } else if (s7 >= arg1->f8) {
            ((Fld *)f)->v29(arg0);
            if (igObject_IsKindOf(f, (void*)DAT_00585a60[0]) == 0 || *(unsigned char *)((char *)f + 52) == 0) igMetaField_Reset(f, arg0);
        } else {
            if (arg4 != 0) igShortMetaField_GetDefaultDescriptor()->v50(s2, 2);
            if (s1 < *(short *)s2 + s6) {
                ((Fld *)f)->v29(arg0);
                if (igObject_IsKindOf(f, (void*)DAT_00585a60[0]) == 0 || *(unsigned char *)((char *)f + 52) == 0) igMetaField_Reset(f, arg0);
                if (arg4 != 0) igShortMetaField_GetDefaultDescriptor()->v50(s2, 2);
            } else {
                s7 += 1;
                s2 += FUN_002fc740(f, arg0, s2, arg2, arg4);
            }
        }
    }
    {
        int r = arg1->f4;
        if (arg4 != 0) igIntMetaField_GetDefaultDescriptor()->v50(arg1, 3);
        arg0->v14();
        return r;
    }
}
}
