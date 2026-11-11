#include "dw4/reflected.h"

struct O { int vt; char b[468]; };
struct V { int x; int y; int z; int w; };
struct M { int m[16]; };

extern igMetaObject *g_igCommonTraversal_metaObject[4];

extern "C" {
igMetaObject *igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
void igMetaObject_RunStaticInit(...);
int igObject_InitHeader(...);
int SceneGraphLibrary_MarkRegistered(...);
int igMetaObject_RegisterClass(...);
int igMetaObject_CreateFields(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igIntList_GetOrCreateMetaObject(...);
int FUN_00130140(...);
int FUN_001380e0(...);
int FUN_00150eb0(...);
int FUN_001510a0(...);
int FUN_001510d0(...);
int FUN_00194490(...);
int FUN_00194830(...);
int FUN_00197330(...);
int FUN_0019ff10(...);
int FUN_0019ff90(...);
int FUN_001a0010(...);
int FUN_001a0090(...);
int FUN_001a0110(...);
int FUN_001a0190(...);
int FUN_001a0210(...);
int FUN_001a0290(...);
int FUN_001a0310(...);
int FUN_001a0390(...);
int FUN_001a0410(...);
int FUN_001a0490(...);
int FUN_001a0510(...);
int FUN_001a0590(...);
int FUN_001a0610(...);
int FUN_001a0690(...);
int FUN_001a0710(...);
int FUN_001a0790(...);
int FUN_001a0810(...);
int FUN_001a0890(...);
int FUN_001a2c50(...);
int FUN_001a3150(...);
int FUN_001a3160(...);
int FUN_00130e90(...);
int FUN_00130f60(...);
int FUN_00134fb0(...);
int FUN_001359e0(...);
int FUN_0013aab0(...);
int FUN_0013ad40(...);
int FUN_0014a040(...);
int FUN_0014fd40(...);
int FUN_0018c640(...);
int FUN_00195d00(...);
int FUN_00195fe0(...);
int FUN_00196c10(...);
int FUN_001999f0(...);
int FUN_00199b60(...);
int FUN_00199cd0(...);
int FUN_00199e40(...);
int FUN_00199fb0(...);
int FUN_0019a120(...);
int FUN_0019a290(...);
int FUN_0019a400(...);
int FUN_0019ca30(...);
int FUN_001a5330(...);
int FUN_001e4010(...);
int FUN_001e4970(...);
int FUN_002b9390(...);
int FUN_002ebc00(...);
int FUN_002fe480(...);
int FUN_001b6be0(...);
int FUN_002fe490(void (*)(void));
void FUN_001b68b0(void);
int FUN_001b6c50(...);

extern int DAT_005293c0[4];
extern int D_005293c0[4];
extern void * DAT_00586dc8[4];
extern int DAT_00528250[4];
extern int DAT_00587040[4];
extern int DAT_0048c7d0[4];
extern int DAT_0048c860[4];
extern int DAT_0048c8f0[4];
extern int DAT_0048c980[4];
extern char igTraversal_Register[];
extern char igTraversal_GetPublishedMetaObject[];
extern char g_igCommonTraversal_callbackList[];
extern char igCommonTraversal_className[];

igMetaObject *FUN_001a38e0(void);
igMetaObject *igCommonTraversal_GetMetaObject(void);
int igCommonTraversal_GetVTable(void);
int *FUN_001a3c60(void *p);
int *FUN_001a3c70(void *p);
int *FUN_001a3c80(void *p);
int *FUN_001a3c90(void *p);
int *FUN_001a3ca0(void *p);
int *FUN_001a3cb0(void *p);
int *FUN_001a3cc0(void *p);
int *FUN_001a3cd0(void *p);
int *FUN_001a3ce0(void *p);
int *FUN_001a3cf0(void *p);
int *FUN_001a3d00(void *p);
int *FUN_001a3d10(void *p);
int *FUN_001a3d20(void *p);
int *FUN_001a3d30(void *p);
int *FUN_001a3d40(void *p);
int *FUN_001a3d50(void *p);
int *FUN_001a3d60(void *p);
int *FUN_001a3d70(void *p);
int *FUN_001a3d80(void *p);
void *FUN_001a3d90(igTraversal *arg0);
void FUN_001a3dd0(void);
void igCommonTraversal_Register(void);
void thunk_igCommonTraversal_GetMetaObject(void);
void igCommonTraversal_InitFields(void);
void FUN_001a44d0(void);
void thunk_FUN_001b6c50(void);
}

igMetaObject *FUN_001a38e0(void) {
    if (g_igCommonTraversal_metaObject[0] == 0) {
        g_igCommonTraversal_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return g_igCommonTraversal_metaObject[0];
}

igMetaObject *igCommonTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igCommonTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3dd0();
    return g_igCommonTraversal_metaObject[0];
}

int igCommonTraversal_GetVTable(void) {
    struct O o; int t; int *p; int *q4; int *q3; int *q2; int *q1; int *q0; int *q6; int *q7; int *q8;
    p = (int*)&o;
    FUN_001a3d90((igTraversal *)p);
    o.vt = (int)&DAT_005293c0[0];
    FUN_001a3d80((char*)&o + 32);
    FUN_001a3d70((char*)&o + 36);
    FUN_001a3d60((char*)&o + 52);
    FUN_001a3d50((char*)&o + 56);
    FUN_001a3d40((char*)&o + 60);
    FUN_00197330((char*)&o + 64);
    q8 = (int*)((char*)&o + 68);
    FUN_001a3d30(q8);
    q7 = (int*)((char*)&o + 72);
    FUN_001a3d20(q7);
    q6 = (int*)((char*)&o + 76);
    FUN_001a3d10(q6);
    q0 = (int*)((char*)&o + 80);
    FUN_001a3d00(q0);
    q1 = (int*)((char*)&o + 84);
    FUN_001a3cf0(q1);
    q2 = (int*)((char*)&o + 88);
    FUN_001a3ce0(q2);
    q3 = (int*)((char*)&o + 92);
    FUN_001a3cd0(q3);
    q4 = (int*)((char*)&o + 96);
    FUN_001a3cc0(q4);
    FUN_001510a0((char*)&o + 100);
    FUN_001510a0(p + 41);
    FUN_001a2c50(p + 58);
    FUN_001a3cb0(p + 59);
    FUN_001a3ca0(p + 60);
    FUN_001a3160(p + 61);
    FUN_001a3150(p + 62);
    FUN_001a3150(p + 63);
    FUN_001510d0(p + 64);
    FUN_001a3c90(p + 65);
    FUN_001a3c80(p + 66);
    FUN_001a3c70(p + 67);
    FUN_001510a0(p + 68);
    FUN_001a3c60(p + 84);
    FUN_001510a0(p + 86);
    FUN_001510a0(p + 102);
    t = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = (int)&D_005293c0[0];
    FUN_001a0890((char*)&o + 336, -1);
    FUN_001a0810((char*)&o + 268, -1);
    FUN_00194830((char*)&o + 264, -1);
    FUN_001a0790((char*)&o + 260, -1);
    FUN_00150eb0((char*)&o + 256, -1);
    FUN_001a0710((char*)&o + 252, -1);
    FUN_001a0710((char*)&o + 248, -1);
    FUN_001a0690((char*)&o + 244, -1);
    FUN_001a0610((char*)&o + 240, -1);
    FUN_001a0590((char*)&o + 236, -1);
    FUN_001a0510((char*)&o + 232, -1);
    FUN_001a0490(q4, -1);
    FUN_001a0410(q3, -1);
    FUN_001a0390(q2, -1);
    FUN_001a0310(q1, -1);
    FUN_001a0290(q0, -1);
    FUN_001a0210(q6, -1);
    FUN_001a0190(q7, -1);
    FUN_001a0110(q8, -1);
    FUN_001380e0((char*)&o + 64, -1);
    FUN_00130140((char*)&o + 60, -1);
    FUN_001a0090((char*)&o + 56, -1);
    FUN_001a0010((char*)&o + 52, -1);
    FUN_0019ff90((char*)&o + 36, -1);
    FUN_0019ff10((char*)&o + 32, -1);
    FUN_00194490(&o, 0);
    return t;
}

int *FUN_001a3c60(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3c70(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3c80(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3c90(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3ca0(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3cb0(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3cc0(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3cd0(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3ce0(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3cf0(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3d00(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3d10(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3d20(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3d30(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3d40(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3d50(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3d60(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3d70(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

int *FUN_001a3d80(void *p)
{
    *(int *)((char *)p + 0) = 0;
    return (int *)p;
}

void *FUN_001a3d90(igTraversal *arg0) {
    igObject_InitHeader();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00528250[0]);
    arg0->_travProcs = 0;
    return arg0;
}

void FUN_001a3dd0(void)
{
    igMetaObject_RunStaticInit(igCommonTraversal_Register);
}

void igCommonTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCommonTraversal_metaObject,
        igTraversal_Register,
        igTraversal_GetPublishedMetaObject,
        &thunk_igCommonTraversal_GetMetaObject,
        igCommonTraversal_className,
        0x1D8, /* instance size */
        &igCommonTraversal_GetVTable,
        &igCommonTraversal_InitFields,
        &FUN_001a44d0, /* extra callback item */
        g_igCommonTraversal_callbackList /* callback list */
    );
}

void thunk_igCommonTraversal_GetMetaObject(void) {
    igCommonTraversal_GetMetaObject();
}

void igCommonTraversal_InitFields(void) {
    void *temp_v0;
    void *temp_s2_9;
    void *temp_s2_8;
    void *temp_s2_7;
    void *temp_s2_6;
    void *temp_s2_5;
    void *temp_s2_4;
    void *temp_s2_3;
    void *temp_s2_30;
    void *temp_s2_2;
    void *temp_s2_29;
    void *temp_s2_28;
    void *temp_s2_27;
    void *temp_s2_26;
    void *temp_s2_25;
    void *temp_s2_24;
    void *temp_s2_23;
    void *temp_s2_22;
    void *temp_s2_21;
    void *temp_s2_20;
    void *temp_s2_19;
    void *temp_s2_18;
    void *temp_s2_17;
    void *temp_s2_16;
    void *temp_s2_15;
    void *temp_s2_14;
    void *temp_s2_13;
    void *temp_s2_12;
    void *temp_s2_11;
    void *temp_s2_10;
    void *temp_s2;
    int temp_s1;
    void *temp_s0;
    struct M b1o;
    struct V b1a;
    struct V b1b;
    struct V b1c;
    struct V b1d;
    struct M b2o;
    struct V b2a;
    struct V b2b;
    struct V b2c;
    struct V b2d;
    struct M b3o;
    struct V b3a;
    struct V b3b;
    struct V b3c;
    struct V b3d;
    struct M b4o;
    struct V b4a;
    struct V b4b;
    struct V b4c;
    struct V b4d;
    struct M b5o;
    struct V b5a;
    struct V b5b;
    struct V b5c;
    struct V b5d;

    temp_s0 = (void *)g_igCommonTraversal_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048c7d0[0], 0x23);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001a5330();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00195fe0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0014a040();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0014fd40();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0013aab0();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0013ad40();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00196c10();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_0019a400();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_0019a290();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_00199fb0();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = FUN_00199b60();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_00199e40();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    temp_s2_13 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_00199cd0();
    ((igRefMetaField *)temp_s2_13)->_construct = 1;
    temp_s2_14 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_0019a120();
    ((igRefMetaField *)temp_s2_14)->_construct = 1;
    temp_s2_15 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE));
    b1d.x = 0;b1d.y = 0;b1d.z = 0;b1d.w = 0x3F800000;
    b1c.x = 0;b1c.y = 0;b1c.z = 0x3F800000;b1c.w = 0;
    b1b.x = 0;b1b.y = 0x3F800000;b1b.z = 0;b1b.w = 0;
    b1a.x = 0x3F800000;b1a.y = 0;b1a.z = 0;b1a.w = 0;
    FUN_00130e90(&b1o, &b1a, &b1b, &b1c, &b1d);
    FUN_0018c640(temp_s2_15, &b1o);
    temp_s2_16 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF));
    b2d.x = 0;b2d.y = 0;b2d.z = 0;b2d.w = 0x3F800000;
    b2c.x = 0;b2c.y = 0;b2c.z = 0x3F800000;b2c.w = 0;
    b2b.x = 0;b2b.y = 0x3F800000;b2b.z = 0;b2b.w = 0;
    b2a.x = 0x3F800000;b2a.y = 0;b2a.z = 0;b2a.w = 0;
    FUN_00130e90(&b2o, &b2a, &b2b, &b2c, &b2d);
    FUN_0018c640(temp_s2_16, &b2o);
    temp_s2_17 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = FUN_001359e0();
    ((igRefMetaField *)temp_s2_17)->_construct = 1;
    temp_s2_18 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = FUN_00134fb0();
    ((igRefMetaField *)temp_s2_18)->_construct = 1;
    temp_s2_19 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x13));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = FUN_001e4010();
    ((igRefMetaField *)temp_s2_19)->_construct = 1;
    temp_s2_20 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x14));
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = FUN_001e4970();
    ((igRefMetaField *)temp_s2_20)->_construct = 1;
    ((igMetaField *)temp_s2_20)->_persistent = 0;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15));
    FUN_002ebc00(temp_v0, -1);
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x16))->_persistent = 0;
    temp_s2_21 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x17));
    ((igObjectRefMetaField *)temp_s2_21)->_metaObject = FUN_00195d00();
    ((igRefMetaField *)temp_s2_21)->_construct = 1;
    ((igMetaField *)temp_s2_21)->_persistent = 0;
    temp_s2_22 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x18));
    ((igObjectRefMetaField *)temp_s2_22)->_metaObject = FUN_00195d00();
    ((igRefMetaField *)temp_s2_22)->_construct = 1;
    ((igMetaField *)temp_s2_22)->_persistent = 0;
    temp_s2_23 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x19));
    ((igObjectRefMetaField *)temp_s2_23)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_23)->_construct = 1;
    ((igMetaField *)temp_s2_23)->_persistent = 0;
    temp_s2_24 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1A));
    ((igObjectRefMetaField *)temp_s2_24)->_metaObject = FUN_002b9390();
    ((igRefMetaField *)temp_s2_24)->_construct = 1;
    ((igMetaField *)temp_s2_24)->_persistent = 0;
    temp_s2_25 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1B));
    ((igObjectRefMetaField *)temp_s2_25)->_metaObject = FUN_0019ca30();
    ((igRefMetaField *)temp_s2_25)->_construct = 1;
    ((igMetaField *)temp_s2_25)->_persistent = 0;
    temp_s2_26 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1C));
    ((igObjectRefMetaField *)temp_s2_26)->_metaObject = FUN_001999f0();
    ((igRefMetaField *)temp_s2_26)->_construct = 1;
    ((igMetaField *)temp_s2_26)->_persistent = 0;
    temp_s2_27 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1D));
    b3d.x = 0;b3d.y = 0;b3d.z = 0;b3d.w = 0x3F800000;
    b3c.x = 0;b3c.y = 0;b3c.z = 0x3F800000;b3c.w = 0;
    b3b.x = 0;b3b.y = 0x3F800000;b3b.z = 0;b3b.w = 0;
    b3a.x = 0x3F800000;b3a.y = 0;b3a.z = 0;b3a.w = 0;
    FUN_00130e90(&b3o, &b3a, &b3b, &b3c, &b3d);
    FUN_0018c640(temp_s2_27, &b3o);
    temp_s2_28 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1E));
    ((igObjectRefMetaField *)temp_s2_28)->_metaObject = FUN_00130f60();
    ((igRefMetaField *)temp_s2_28)->_construct = 1;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1F))->_persistent = 0;
    temp_s2_29 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x20));
    b4d.x = 0;b4d.y = 0;b4d.z = 0;b4d.w = 0x3F800000;
    b4c.x = 0;b4c.y = 0;b4c.z = 0x3F800000;b4c.w = 0;
    b4b.x = 0;b4b.y = 0x3F800000;b4b.z = 0;b4b.w = 0;
    b4a.x = 0x3F800000;b4a.y = 0;b4a.z = 0;b4a.w = 0;
    FUN_00130e90(&b4o, &b4a, &b4b, &b4c, &b4d);
    FUN_0018c640(temp_s2_29, &b4o);
    ((igMetaField *)temp_s2_29)->_persistent = 0;
    temp_s2_30 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x21));
    b5d.x = 0;b5d.y = 0;b5d.z = 0;b5d.w = 0x3F800000;
    b5c.x = 0;b5c.y = 0;b5c.z = 0x3F800000;b5c.w = 0;
    b5b.x = 0;b5b.y = 0x3F800000;b5b.z = 0;b5b.w = 0;
    b5a.x = 0x3F800000;b5a.y = 0;b5a.z = 0;b5a.w = 0;
    FUN_00130e90(&b5o, &b5a, &b5b, &b5c, &b5d);
    FUN_0018c640(temp_s2_30, &b5o);
    ((igMetaField *)temp_s2_30)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x22))->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048c860[0], &DAT_0048c8f0[0], &DAT_0048c980[0], temp_s1);
    FUN_002fe480(&thunk_FUN_001b6c50);
}

void FUN_001a44d0(void) {
    FUN_001b6be0();
    FUN_002fe490(FUN_001b68b0);
}

void thunk_FUN_001b6c50(void) {
    FUN_001b6c50();
}
