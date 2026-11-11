#include "dw4/reflected.h"

struct S { int *vt; char pad[468]; int a; char b[72]; int c; };
struct R { int vt; unsigned int rc; };
struct T { int w0; int refs; };
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
struct T1a0910 { int word0; int references; };
struct Obj;
struct V { int x; int y; int z; int w; };
struct M { int m[16]; };

extern igMetaObject *g_igFrustCullTraversal_metaObject[4];

extern "C" {
void FUN_00100610(void *);
void igObject_Destroy(void *);
int thunk_FUN_002ed460__002ff810(void *);
void igMetaObject_RunStaticInit(...);
int igMetaObject_CreateInstance(int, int);
int FUN_001510a0(...);
int FUN_00198190(...);
int igMatrix44f_SetIdentity(...);
int igObject_InitHeader(...);
int SceneGraphLibrary_MarkRegistered(...);
int igMetaObject_RegisterClass(...);
int FUN_00130e90(...);
int FUN_00139170(...);
int FUN_0018a6a0(...);
int FUN_0018c640(...);
int FUN_002e3810(void *, float);
int FUN_002fe480(...);
int igMetaObject_CreateFields(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int FUN_001c45a0(...);
int FUN_002fe490(int *);
void FUN_001c4590(void);
int FUN_001c45d0(...);

extern int DAT_00528f10[4];
extern void *DAT_00586dc8[4];
extern int DAT_00528250[4];
extern int DAT_005293c0[4];
extern int DAT_00561d78[4];
extern int DAT_0048c090[4];
extern int DAT_0048c0b0[4];
extern int DAT_0048c0d0[4];
extern int DAT_0048c0f0[4];
extern int DAT_00561a50[4];
extern char igCommonTraversal_Register[];
extern char g_igFrustCullTraversal_callbackList[];
extern char igFrustCullTraversal_className[];

void FUN_0019fde0(int arg0);
igMetaObject *igFrustCullTraversal_GetMetaObject(void);
int igFrustCullTraversal_GetVTable(void);
struct R **FUN_0019ff10(struct R **arg0, short arg1);
struct T **FUN_0019ff90(struct T **arg0, short arg1);
void **FUN_001a0010(void **arg0, int arg1);
void **FUN_001a0090(void **arg0, short arg1);
void **FUN_001a0110(struct Ref **self, short flag);
void **FUN_001a0190(void **arg0, long long arg1);
O *FUN_001a0210(O *arg0, short arg1);
void **FUN_001a0290(void **arg0, short arg1);
void **FUN_001a0310(void **arg0, short arg1);
ObjectRefWord *FUN_001a0390(ObjectRefWord *self,int delete_storage);
void **FUN_001a0410(void **arg0, short arg1);
ObjectRefWord *FUN_001a0490(ObjectRefWord *self,int delete_storage);
struct R **FUN_001a0510(struct R **arg0, short arg1);
ObjectRefWord *FUN_001a0590(ObjectRefWord *self,int delete_storage);
void **FUN_001a0610(void **arg0, int arg1);
void **FUN_001a0690(void **arg0, short arg1);
void **FUN_001a0710(struct Ref **self, short flag);
void **FUN_001a0790(void **arg0, long long arg1);
O *FUN_001a0810(O *arg0, short arg1);
ObjectRefWord *FUN_001a0890(ObjectRefWord *self,int delete_storage);
Obj *FUN_001a0910(Obj *arg0, short arg1);
void **FUN_001a1000(void **arg0, short arg1);
int *FUN_001a1080(int *p);
int *FUN_001a1090(int *p);
void *FUN_001a10a0(igCommonTraversal *arg0);
void FUN_001a1170(void);
void igFrustCullTraversal_Register(void);
void thunk_igFrustCullTraversal_GetMetaObject(void);
int FUN_001a1210(void);
void igFrustCullTraversal_InitFields(void);
void FUN_001a13a0(void);
void thunk_FUN_001c45d0(void);
}

struct Obj {
    int *vt;
    char p4[24];
    T1a0910 *m28;
    T1a0910 *m32;
    T1a0910 *m36;
    char p40[12];
    T1a0910 *m52;
    T1a0910 *m56;
    T1a0910 *m60;
    T1a0910 *m64;
    T1a0910 *m68;
    T1a0910 *m72;
    T1a0910 *m76;
    T1a0910 *m80;
    T1a0910 *m84;
    T1a0910 *m88;
    T1a0910 *m92;
    T1a0910 *m96;
    char p100[132];
    T1a0910 *m232;
    T1a0910 *m236;
    T1a0910 *m240;
    T1a0910 *m244;
    T1a0910 *m248;
    T1a0910 *m252;
    T1a0910 *m256;
    T1a0910 *m260;
    T1a0910 *m264;
    T1a0910 *m268;
    char p272[64];
    T1a0910 *m336;
    inline void rel(T1a0910 **self) {
        if (self) {
            T1a0910 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};

void FUN_0019fde0(int arg0) {
    FUN_001a1170();
    igMetaObject_CreateInstance(*(int *)0x561A50, arg0);
}

igMetaObject *igFrustCullTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igFrustCullTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a1170();
    return g_igFrustCullTraversal_metaObject[0];
}

int igFrustCullTraversal_GetVTable(void) {
    struct S s; char *p;
    int r;
    p = (char *)&s; FUN_001a10a0((igCommonTraversal *)p);
    s.vt = &DAT_00528f10[0];
    FUN_001a1090(&s.a);
    FUN_001510a0(s.b);
    FUN_001a1080((int *)(p + 548));
    r = *(int *)((char *)&s + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    s.vt = &DAT_00528f10[0];
    FUN_001a1000((void **)&s.c, -1);
    FUN_00198190(&s.a, -1);
    FUN_001a0910((Obj *)&s, 0);
    return r;
}

struct R **FUN_0019ff10(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

struct T **FUN_0019ff90(struct T **arg0, short arg1) {
    struct T *o;
    if (arg0 != 0) {
        o = *arg0;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0010(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0090(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0110(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) FUN_00100610(self);
    }
    return (void **)self;
}

void **FUN_001a0190(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_001a0210(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void **FUN_001a0290(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0310(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_001a0390(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_001a0410(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_001a0490(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

struct R **FUN_001a0510(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_001a0590(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_001a0610(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0690(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0710(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) FUN_00100610(self);
    }
    return (void **)self;
}

void **FUN_001a0790(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_001a0810(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_001a0890(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

Obj *FUN_001a0910(Obj *arg0, short arg1) {
    if (arg0) {
        arg0->vt = DAT_005293c0;
        arg0->rel(&arg0->m336);
        arg0->rel(&arg0->m268);
        arg0->rel(&arg0->m264);
        arg0->rel(&arg0->m260);
        arg0->rel(&arg0->m256);
        arg0->rel(&arg0->m252);
        arg0->rel(&arg0->m248);
        arg0->rel(&arg0->m244);
        arg0->rel(&arg0->m240);
        arg0->rel(&arg0->m236);
        arg0->rel(&arg0->m232);
        arg0->rel(&arg0->m96);
        arg0->rel(&arg0->m92);
        arg0->rel(&arg0->m88);
        arg0->rel(&arg0->m84);
        arg0->rel(&arg0->m80);
        arg0->rel(&arg0->m76);
        arg0->rel(&arg0->m72);
        arg0->rel(&arg0->m68);
        arg0->rel(&arg0->m64);
        arg0->rel(&arg0->m60);
        arg0->rel(&arg0->m56);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        if (arg0) {
            arg0->vt = DAT_00528250;
            arg0->rel(&arg0->m28);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void **FUN_001a1000(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

int *FUN_001a1080(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_001a1090(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_001a10a0(igCommonTraversal *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)(&DAT_00528250[0]);
    arg0->_travProcs = 0;
    arg0->_vtable = (int)(&DAT_005293c0[0]);
    arg0->_capabilityManager = 0;
    arg0->_defaultManager = 0;
    arg0->_attrStack = 0;
    arg0->_transformStack = 0;
    arg0->_vc = 0;
    arg0->_flushedAttrs = 0;
    arg0->_sorter = 0;
    arg0->_matrixPool = 0;
    arg0->_timePool = 0;
    arg0->_blendMatrixPool = 0;
    arg0->_texMatPool = 0;
    arg0->_vertexBlendMatListPool = 0;
    arg0->_matrixObjectPool = 0;
    arg0->_projectionMatrixPool = 0;
    igMatrix44f_SetIdentity((char *)arg0 + 0x64);
    igMatrix44f_SetIdentity((char *)arg0 + 0xA4);
    arg0->_matrixOptimization = 0;
    arg0->_normalizeNormalsEnable = 0;
    arg0->_timeStack = 0;
    arg0->_matrixObjectList = 0;
    arg0->_boneMatrixPaletteList = 0;
    arg0->_blendMatrixPaletteList = 0;
    arg0->_blendMatrixPaletteLengths = 0;
    arg0->_segmentOverrideNames = 0;
    arg0->_segmentOverrideStacks = 0;
    arg0->_blendMatricesAttrPool = 0;
    igMatrix44f_SetIdentity((char *)arg0 + 0x110);
    arg0->_defaultTimeAttr = 0;
    igMatrix44f_SetIdentity((char *)arg0 + 0x158);
    igMatrix44f_SetIdentity((char *)arg0 + 0x198);
    return arg0;
}

void FUN_001a1170(void)
{
    igMetaObject_RunStaticInit(igFrustCullTraversal_Register);
}

void igFrustCullTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFrustCullTraversal_metaObject,
        igCommonTraversal_Register,
        FUN_001a1210,
        thunk_igFrustCullTraversal_GetMetaObject,
        igFrustCullTraversal_className,
        0x230, /* instance size */
        igFrustCullTraversal_GetVTable,
        &igFrustCullTraversal_InitFields,
        &FUN_001a13a0, /* extra callback item */
        g_igFrustCullTraversal_callbackList /* callback list */
    );
}

void thunk_igFrustCullTraversal_GetMetaObject(void) {
    igFrustCullTraversal_GetMetaObject();
}

int FUN_001a1210(void) {
    return DAT_00561d78[0];
}

void igFrustCullTraversal_InitFields(void) {
    void *temp_s2_3;
    void *temp_s2_2;
    void *temp_s2;
    void *temp_s1;
    int temp_s0;
    struct M o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    temp_s1 = (void *)DAT_00561a50[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048c090[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    FUN_00130e90(&o1, &o2, &o3, &o4, &o5);
    FUN_0018c640(temp_s2, &o1);
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00139170();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5), 2.0f);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0018a6a0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_0048c0b0[0], &DAT_0048c0d0[0], &DAT_0048c0f0[0], temp_s0);
    FUN_002fe480(&thunk_FUN_001c45d0);
}

void FUN_001a13a0(void) {
    FUN_001c45a0();
    FUN_002fe490((int *)FUN_001c4590);
}

void thunk_FUN_001c45d0(void) {
    FUN_001c45d0();
}
