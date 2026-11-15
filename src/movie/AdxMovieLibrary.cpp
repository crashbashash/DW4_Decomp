#include "dw4/reflected.h"

#pragma push
#pragma readonly_strings on
static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }

typedef void (*igMetaObjectCallback)();
typedef igMetaField *(*FieldFactory)(void *);
extern "C" igMetaField *igBoolMetaField_Create(void *);
extern "C" igMetaField *igEnumMetaField_Create(void *);
extern "C" igMetaField *igIntMetaField_Create(void *);
extern "C" igMetaField *igObjectRefMetaField_Create(void *);
extern "C" igMetaField *igRawRefMetaField_Create(void *);
extern "C" igMetaField *igShortMetaField_Create(void *);
extern "C" igMetaField *igStringMetaField_Create(void *);
extern "C" igMetaField *igStructMetaField_Create(void *);
extern "C" igMetaField *igUnsignedLongMetaField_Create(void *);
extern "C" void FUN_00132a00(void);
extern "C" void FUN_00143010(void);
extern "C" void FUN_0013a440(void);
extern "C" void FUN_0014a0e0(void);
extern "C" void FUN_0014e050(void);
extern "C" void FUN_0019b270(void);
extern "C" void igObject_EnsureRegistered(void);
extern "C" void igNamedObjectList_EnsureRegistered(void);
extern "C" void igRendererOrderedList_EnsureRegistered(void);

extern "C" void FUN_003343a0(void);
extern "C" void AdxMovieLibrary_MarkRegistered(void);
extern "C" void *FUN_00334460(void);
extern "C" int igObject_InitHeader(...);
extern "C" int igAdx_GetVTable(void);
extern "C" void igMetaObject_RunStaticInit(void *(*)(void));
extern "C" void FUN_003344f0(void);
extern "C" void * igMetaObject_RegisterClass(...);
extern "C" void *igObject_Register(void);
extern "C" void *igAdx_Register(void);
extern "C" void igAdx_GetMetaObject(void);
extern "C" void igMetaObject_AddExitCallback(...);
extern "C" void igAdx_InitFields(void);
extern "C" void igAdx_CreateScratchString(void);
extern "C" void FUN_003345d0(void);
extern "C" void igAdx_Shutdown(void);
extern "C" void FUN_003345f0(void);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" igMetaObject *igMetaObject_Create(int);
extern "C" igMetaObject *FUN_00334610(void);
extern "C" void *FUN_00334660(void);
extern "C" int igAdxAfsFileList_GetVTable(void);
extern "C" void FUN_003346f0(void);
extern "C" void *igObjectList_Register(void);
extern "C" void *igAdxAfsFileList_Register(void);
extern "C" void igAdxAfsFileList_GetMetaObject(void);
extern "C" void *FUN_003347a0(void);
extern "C" int igObject_Destroy(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int igAdxAfsFile_GetVTable(void);
extern "C" void FUN_003348d0(void);
extern "C" void *igAdxAfsFile_Register(void);
extern "C" void igAdxAfsFile_GetMetaObject(void);
extern "C" igMetaObject *FUN_00334980(void);
extern "C" void igMetaObject_CreateFields(void *, FieldFactory *, int);
extern "C" int igMetaObject_GetFieldCount(void *);
extern "C" void igMetaObject_NameFields(void *, const char **, igMetaField ***, int *, int);
extern "C" void igAdxAfsFile_InitFields(void);
extern "C" void *FUN_00334a00(void);
extern "C" int igFileNameList_GetVTable(void);
extern "C" void FUN_00334a90(void);
extern "C" void *igFileNameList_Register(void);
extern "C" void igFileNameList_GetMetaObject(void);
extern "C" void *FUN_00334b40(void);
extern "C" int igFileName_GetVTable(void);
extern "C" void FUN_00334c70(void);
extern "C" void *igNamedObject_Register(void);
extern "C" void *igFileName_Register(void);
extern "C" void igFileName_GetMetaObject(void);
extern "C" int igNamedObjectList_GetOrCreateMetaObject(void);
extern "C" void * igMetaObject_GetFieldAt(...);
extern "C" void igFileName_InitFields(void);
extern "C" int igMetaObject_CreateInstance(igMetaObject *, int);
extern "C" void FUN_00334dc0(int arg0);
extern "C" void *FUN_00334e00(void);
extern "C" int igAdxFile_GetVTable(void);
extern "C" void FUN_00334ec0(void);
extern "C" void *igFile_Register(void);
extern "C" void *igAdxFile_Register(void);
extern "C" void igAdxFile_GetMetaObject(void);
extern "C" int igBoolMetaField_SetDefaultValue(int, int);
extern "C" int igIntMetaField_SetDefault(...);
extern "C" int igUnsignedLongMetaField_SetDefaultValue(int, int);
extern "C" int igFile_GetMetaObjectFunction(void);
extern "C" void igAdxFile_InitFields(void);
extern "C" void igAdxFile_StaticInitialize(void);
extern "C" void FUN_003350b0(void);
extern "C" void igAdxFile_StaticFinalize(void);
extern "C" void FUN_003350d0(void);
extern "C" void igAdxAudio_Create(int arg0);
extern "C" igMetaObject *FUN_00335130(void);
extern "C" void *FUN_00335180(void);
extern "C" int igAdxAudio_GetVTable(void);
extern "C" void FUN_00335260(void);
extern "C" void *igAdxAudio_Register(void);
extern "C" void igAdxAudio_GetMetaObject(void);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" void igAdxAudio_InitFields(void);
extern "C" void FUN_00335400(int arg0);
extern "C" igMetaObject *FUN_00335440(void);
extern "C" void *FUN_00335490(void);
extern "C" int igMovieCodecList_GetVTable(void);
extern "C" void FUN_00335520(void);
extern "C" void *igMovieCodecList_Register(void);
extern "C" void igMovieCodecList_GetMetaObject(void);
extern "C" igMetaObject *FUN_003355d0(void);
extern "C" void *FUN_00335620(void);
extern "C" int igMovieCodec_GetVTable(void);
extern "C" void FUN_003357a0(void);
extern "C" void *igMovieCodec_Register(void);
extern "C" void igMovieCodec_GetMetaObject(void);
extern "C" int FUN_00130140(int *, int);
extern "C" int igCriMovieCodec_GetVTable(void);
extern "C" int __dl__FPv(...);
extern "C" void FUN_003359b0(void);
extern "C" void *igCriMovieCodec_Register(void);
extern "C" void igCriMovieCodec_GetMetaObject(void);
extern "C" igMetaObject *FUN_00335a70(void);
extern "C" int FUN_00142f70(void);
extern "C" int FUN_0014a040(void);
extern "C" void igCriMovieCodec_InitFields(void);
extern "C" void FUN_00335b40(int arg0);
extern "C" int igCriMovieData_GetVTable(void);
extern "C" void FUN_00335c10(void);
extern "C" void *igCriMovieData_Register(void);
extern "C" void igCriMovieData_GetMetaObject(void);
extern "C" void igCriMovieData_InitFields(void);
extern "C" void FUN_00335da0(int arg0);
extern "C" igMetaObject *FUN_00335de0(void);
extern "C" int igMovieInfoList_GetVTable(void);
extern "C" void FUN_00335ec0(void);
extern "C" void *igMovieInfoList_Register(void);
extern "C" void igMovieInfoList_GetMetaObject(void);
extern "C" void FUN_00335f70(int arg0);
extern "C" igMetaObject *FUN_00335fb0(void);
extern "C" int igTextureBindAttrList_GetVTable(void);
extern "C" void FUN_00336090(void);
extern "C" void *igTextureBindAttrList_Register(void);
extern "C" void igTextureBindAttrList_GetMetaObject(void);
extern "C" igMetaEnum *igMetaEnum_Create(const char *, const char **, int *, int);
extern "C" igMetaEnum *FUN_00336140(void);
extern "C" igMetaEnum *FUN_003361a0(void);
extern "C" void FUN_00336200(int arg0);
extern "C" void *FUN_00336240(void);
extern "C" int FUN_00131aa0(int *, int);
extern "C" int FUN_00132390(int *, int);
extern "C" int FUN_001d3650(int *, int);
extern "C" int ObjectRef_Destruct_001363f0(int *, int);
extern "C" int igStringRef_Destruct(int *, int);
extern "C" int igMovieInfo_GetVTable(void);
extern "C" void **FUN_003363c0(void **arg0, long long arg1);
extern "C" void **FUN_00336440(void **arg0, int arg1);
extern "C" void FUN_003364c0(void);
extern "C" void *igInfo_Register(void);
extern "C" void *igMovieInfo_Register(void);
extern "C" void igMovieInfo_GetMetaObject(void);
extern "C" int FUN_0013a360(void);
extern "C" int FUN_0014dfb0(void);
extern "C" int FUN_0019aee0(void);
extern "C" int igEnumMetaField_SetDefaultValue(void *field, const int &value);
extern "C" void FUN_00149980(void);
extern "C" void FUN_001499e0(void);
extern "C" void igMovieInfo_InitFields(void);
extern "C" igMetaObject *FUN_00336860(void);
extern "C" void *FUN_003368b0(void);
extern "C" int igMovieRenderer_GetVTable(void);
extern "C" void **FUN_003369f0(void **arg0, short arg1);
extern "C" void FUN_00336a70(void);
extern "C" void *igRenderer_Register(void);
extern "C" void *igMovieRenderer_Register(void);
extern "C" void igMovieRenderer_GetMetaObject(void);
extern "C" void igMovieRenderer_InitFields(void);
extern "C" void igMovieManager_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00336c10(void);
extern "C" void *FUN_00336c60(void);
extern "C" int FUN_00231030(char *, int);
extern "C" int FUN_00232ae0(int *, int);
extern "C" int igMovieManager_GetVTable(void);
extern "C" void **FUN_00336e10(void **arg0, long long arg1);
extern "C" void FUN_00336f10(void);
extern "C" void *igInfoManager_Register(void);
extern "C" void *igMovieManager_Register(void);
extern "C" void igMovieManager_GetMetaObject(void);
extern "C" int FUN_0044c4d0(void);
extern "C" void igMovieManager_InitFields(void);
extern "C" void *FUN_003370f0(void);
extern "C" int igMoviePlugin_GetVTable(void);
extern "C" void FUN_003371d0(void);
extern "C" void *igInsightPlugin_Register(void);
extern "C" void *igMoviePlugin_Register(void);
extern "C" void igMoviePlugin_GetMetaObject(void);
extern "C" int FUN_00337290(void);
extern "C" void igMoviePlugin_InitFields(void);
extern "C" int Gap__Insight__igInsightPlugin__vfunc_20(void);
extern "C" igMetaObject *Gap__igMovieInfo__vfunc_20(void);
extern "C" igMetaObject *Gap__igTextureBindAttrList__vfunc_20(void);
extern "C" int Gap__igTextureBindAttrList__vfunc_22(void);
extern "C" igMetaObject *Gap__igMovieInfoList__vfunc_20(void);
extern "C" igMetaObject *Gap__igMovieInfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__igMovieCodecList__vfunc_20(void);
extern "C" igMetaObject *Gap__igMovieCodecList__vfunc_22(void);
extern "C" igMetaObject *Gap__igFileNameList__vfunc_20(void);
extern "C" igMetaObject *Gap__igFileNameList__vfunc_22(void);
extern "C" igMetaObject *Gap__igAdxAfsFile__vfunc_20(void);
extern "C" igMetaObject *Gap__igFileName__vfunc_20(void);
extern "C" igMetaObject *Gap__igAdxAfsFileList__vfunc_20(void);
extern "C" igMetaObject *Gap__igAdxAfsFileList__vfunc_22(void);
extern "C" unsigned char g_AdxMovieLibrary_registered;
extern "C" igMetaObject *g_igAdx_metaObject;
struct Obj { int *vt; char pad[4]; };
extern "C" int DAT_00533790[4];
extern "C" void * g_objectSystem[4];
struct igMetaObject_334510;
extern "C" igMetaObject_334510 * igObject_GetMetaObject_ParentAccessor(...);
extern "C" int kIGMemoryPoolHandleMetaData[4];
extern "C" igMetaObject *g_igAdxAfsFileList_metaObject;
struct Obj_3346b0 { int *vt; char pad[28]; };
extern "C" int DAT_00533c00[4];
struct igMetaObject_334710;
extern "C" igMetaObject_334710 * igObjectList_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_igAdxAfsFile_metaObject;
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U_3347f0 { int vt; char b[32]; };
extern "C" int g_igNamedObject_vtable[4];
extern "C" int DAT_00533b40[4];
extern "C" int DAT_00533ba0[4];
struct igMetaObject_3348f0;
extern "C" igMetaObject_3348f0 *igFileName_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_igFileNameList_metaObject;
extern "C" int DAT_00533ad0[4];
extern "C" igMetaObject *g_igFileName_metaObject;
union U_334b90 { int vt; char b[16]; };
struct igMetaObject_334c90;
extern "C" igMetaObject_334c90 * igNamedObject_GetPublishedMetaObject(...);
extern "C" igMetaObject *g_igAdxFile_metaObject;
struct Obj_334e50 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
extern "C" int igFile_Destroy(struct Obj_334e50 *, int);
extern "C" int DAT_005337f0[4];
struct igMetaObject_334ee0;
extern "C" igMetaObject_334ee0 *igFile_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_igAdxAudio_metaObject;
struct W { int *vt; int f[11]; };
extern "C" int DAT_00533730[4];
extern "C" igMetaObject *g_igMovieCodecList_metaObject;
extern "C" int DAT_00533a60[4];
extern "C" igMetaObject *g_igMovieCodec_metaObject;
union U_335670 { int vt; char b[16]; };
extern "C" int DAT_00533d60[4];
extern "C" int Memory_FreeBufferAliasC(struct O *);
typedef struct O { int vt; int pad; int f8; } O;
extern "C" O *FUN_00335700(O *arg0, long long arg1);
extern "C" igMetaObject *g_igCriMovieCodec_metaObject;
extern "C" igMetaObject *FUN_00335850(void);
struct Obj_3358a0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int DAT_00533c70[4];
struct R { int vt; unsigned int rc; };
extern "C" struct R **FUN_00335930(struct R **arg0, short arg1);
struct igMetaObject_3359d0;
extern "C" igMetaObject_3359d0 *igMovieCodec_GetPublishedMetaObject(void);
struct F { char pad[38]; unsigned char b38; char pad2[17]; int f56; };
extern "C" igMetaObject *g_igCriMovieData_metaObject;
extern "C" igMetaObject *FUN_00335b80(void);
extern "C" int DAT_00533d00[4];
extern "C" igMetaObject *g_igMovieInfoList_metaObject;
extern "C" igMetaObject *FUN_00335e30(void);
extern "C" int DAT_005339f0[4];
extern "C" igMetaObject *g_igTextureBindAttrList_metaObject;
extern "C" igMetaObject *FUN_00336000(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_336050;
extern "C" int DAT_00533980[4];
extern "C" igMetaObject *g_igMovieInfo_metaObject;
extern "C" int igInfo_Destroy(struct Obj_334e50 *, int);
extern "C" int DAT_00533910[4];
struct igMetaObject_3364e0;
extern "C" igMetaObject_3364e0 *igInfo_GetPublishedMetaObject(void);
struct MovieInfoFieldView { char pad0[38]; char f38; char pad1[13]; int f52; int f56; };
extern "C" int g_igObject_metaObject[4];
extern "C" igMetaObject *g_igMovieRenderer_metaObject;
struct T_336900 { int word0; int references; };
extern "C" int DAT_0052d060[4];
extern "C" int DAT_00533de0[4];
struct Obj_336900 {
    int *vt; char p4[4]; T_336900 *m8; T_336900 *m12;
    inline void rel8() {
        T_336900 **self = &m8;
        if (self) {
            T_336900 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void rel12() {
        T_336900 **self = &m12;
        if (self) {
            T_336900 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
struct igMetaObject_336a90;
extern "C" igMetaObject_336a90 *igRenderer_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_igMovieManager_metaObject;
union U_336cb0 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int DAT_00533e50[4];
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" void **FUN_00336d90(struct Ref **self, short flag);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O_336e90 { S_temp_a0 *m; };
extern "C" O_336e90 *FUN_00336e90(O_336e90 *arg0, short arg1);
struct igMetaObject_336f30;
extern "C" igMetaObject_336f30 *igInfoManager_GetPublishedMetaObject(void);
struct Fld { char p0[38]; char f38; char p1[13]; char f52; int f56; };
extern "C" igMetaObject *g_igMoviePlugin_metaObject;
typedef struct Q { char pad4[4]; int f4; } Q;
typedef struct { int *vt; int w[1]; Q *s; } Obj_337140;
extern "C" int DAT_00533ee0[4];
struct igMetaObject_3371f0;
extern "C" igMetaObject_3371f0 *igInsightPlugin_GetPublishedMetaObject(void);
extern "C" int g_igInsightPlugin_metaObject[4];
extern "C" int g_igTextureBindAttr_metaObject[4];

unsigned char g_AdxMovieLibrary_registered;

void FUN_003343a0(void) {
    FUN_00334c70();
    FUN_00334a90();
    FUN_003348d0();
    FUN_003346f0();
    FUN_003344f0();
    FUN_00334ec0();
    FUN_00335260();
    FUN_003357a0();
    FUN_00335520();
    FUN_00335c10();
    FUN_003359b0();
    FUN_003364c0();
    FUN_00336090();
    FUN_00335ec0();
    FUN_00336f10();
    FUN_00336a70();
    FUN_003371d0();
}

void AdxMovieLibrary_MarkRegistered(void) {
    if (g_AdxMovieLibrary_registered == 0) {
        g_AdxMovieLibrary_registered = 1;
    }
}

igMetaObject *g_igAdx_metaObject;

void *FUN_00334460(void) {
    igMetaObject *g = g_igAdx_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003344f0();
    }
    return g_igAdx_metaObject;
}

int igAdx_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00533790[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003344f0(void)
{
    igMetaObject_RunStaticInit(igAdx_Register);
}

void *igAdx_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdx_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igAdx_GetMetaObject,
        "igAdx",
        8, /* instance size */
        igAdx_GetVTable,
        igAdx_InitFields,
        FUN_003345d0, /* extra callback item */
        0 /* callback list */
    );
}

void igAdx_GetMetaObject(void)
{
    FUN_00334460();
}

void igAdx_InitFields(void)
{
    igMetaObject_AddExitCallback(FUN_003345f0);
}

void FUN_003345d0(void)
{
    igAdx_CreateScratchString();
}

void FUN_003345f0(void)
{
    igAdx_Shutdown();
}

igMetaObject *g_igAdxAfsFileList_metaObject;

igMetaObject *FUN_00334610(void) {
    if (g_igAdxAfsFileList_metaObject == 0) {
        g_igAdxAfsFileList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAdxAfsFileList_metaObject;
}

void *FUN_00334660(void) {
    bool ok;
    if (g_igAdxAfsFileList_metaObject == 0) goto make;
    ok = !!(g_igAdxAfsFileList_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003346f0();
done:;
    return g_igAdxAfsFileList_metaObject;
}

int igAdxAfsFileList_GetVTable(void) {
    struct Obj_3346b0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00533c00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003346f0(void)
{
    igMetaObject_RunStaticInit(igAdxAfsFileList_Register);
}

static igMetaObjectCallback g_igAdxAfsFileList_callbackList[] = { FUN_003348d0, 0 };

void *igAdxAfsFileList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdxAfsFileList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAdxAfsFileList_GetMetaObject,
        "igAdxAfsFileList",
        0x14, /* instance size */
        igAdxAfsFileList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAdxAfsFileList_callbackList /* callback list */
    );
}

void igAdxAfsFileList_GetMetaObject(void)
{
    FUN_00334660();
}

igMetaObject *g_igAdxAfsFile_metaObject;
igMetaField *g_igAdxAfsFile_ptNumberMetaField;
igMetaField *g_igAdxAfsFile_fileNumberMetaField;

void *FUN_003347a0(void) {
    igMetaObject *g = g_igAdxAfsFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003348d0();
    }
    return g_igAdxAfsFile_metaObject;
}

int igAdxAfsFile_GetVTable(void) {
    union U_3347f0 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00533ba0[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00533b40[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00533ba0[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_003348d0(void)
{
    igMetaObject_RunStaticInit(igAdxAfsFile_Register);
}

void *igAdxAfsFile_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdxAfsFile_metaObject,
        igFileName_Register,
        igFileName_GetPublishedMetaObject,
        igAdxAfsFile_GetMetaObject,
        "igAdxAfsFile",
        0x14, /* instance size */
        igAdxAfsFile_GetVTable,
        igAdxAfsFile_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igAdxAfsFile_GetMetaObject(void)
{
    FUN_003347a0();
}

igMetaObject *FUN_00334980(void) {
    return g_igFileName_metaObject;
}

static FieldFactory g_igAdxAfsFile_ctorTable[] = {
    igShortMetaField_Create,
    igShortMetaField_Create,
};
static const char *g_igAdxAfsFile_fieldTable[] = {
    "_ptNumber",
    "_fileNumber",
};
static igMetaField **g_igAdxAfsFile_fieldHandles[] = {
    &g_igAdxAfsFile_ptNumberMetaField,
    &g_igAdxAfsFile_fileNumberMetaField,
};
static int g_igAdxAfsFile_fieldOffsets[] = {
    16,
    18,
};

void igAdxAfsFile_InitFields(void) {
    int firstField;
    void *meta;

    meta = g_igAdxAfsFile_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igAdxAfsFile_ctorTable, 2);
    igMetaObject_NameFields(meta, g_igAdxAfsFile_fieldTable, g_igAdxAfsFile_fieldHandles, g_igAdxAfsFile_fieldOffsets, firstField);
}

igMetaObject *g_igFileNameList_metaObject;

void *FUN_00334a00(void) {
    unsigned char b;
    if (g_igFileNameList_metaObject != 0) {
        b = (*(int *)((char *)(g_igFileNameList_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00334a90();
done:
    return g_igFileNameList_metaObject;
}

int igFileNameList_GetVTable(void) {
    struct Obj_3346b0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00533ad0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00334a90(void)
{
    igMetaObject_RunStaticInit(igFileNameList_Register);
}

static igMetaObjectCallback g_igFileNameList_callbackList[] = { FUN_00334c70, 0 };

void *igFileNameList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFileNameList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igFileNameList_GetMetaObject,
        "igFileNameList",
        0x14, /* instance size */
        igFileNameList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFileNameList_callbackList /* callback list */
    );
}

void igFileNameList_GetMetaObject(void)
{
    FUN_00334a00();
}

igMetaObject *g_igFileName_metaObject;
igMetaField *g_igFileName_pathListMetaField;

void *FUN_00334b40(void) {
    igMetaObject *g = g_igFileName_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00334c70();
    }
    return g_igFileName_metaObject;
}

int igFileName_GetVTable(void) {
    union U_334b90 u;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;

    igObject_InitHeader(u.b);
    p0 = (S_ref *)&u.b[8];
    *(int *)p0 = 0;
    u.vt = (int)&DAT_00533ba0[0];
    p1 = (S_ref *)&u.b[12];
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00533ba0[0];
    if (p1 != 0) {
        p1 = *(S_ref **)p1;
        if (p1 != 0) {
            p1->f4 = (int)((int) (p1->f4 - 1));
            if (((unsigned long long) ((long long) p1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p0 != 0) {
        o = *(char **)p0;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_00334c70(void)
{
    igMetaObject_RunStaticInit(igFileName_Register);
}

static igMetaObjectCallback g_igFileName_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

void *igFileName_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFileName_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igFileName_GetMetaObject,
        "igFileName",
        0x10, /* instance size */
        igFileName_GetVTable,
        igFileName_InitFields,
        0, /* extra callback item */
        g_igFileName_callbackList /* callback list */
    );
}

void igFileName_GetMetaObject(void)
{
    FUN_00334b40();
}

static FieldFactory g_igFileName_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igFileName_fieldTable[] = {
    "_pathList",
};
static igMetaField **g_igFileName_fieldHandles[] = {
    &g_igFileName_pathListMetaField,
};
static int g_igFileName_fieldOffsets[] = {
    12,
};

void igFileName_InitFields(void) {
    int firstField;
    void *pathListField;
    void *meta;

    meta = g_igFileName_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igFileName_ctorTable, 1);
    pathListField = (void *)(igMetaObject_GetFieldAt(meta, firstField));
    ((igObjectRefMetaField *)pathListField)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_igFileName_fieldTable, g_igFileName_fieldHandles, g_igFileName_fieldOffsets, firstField);
}

igMetaObject *g_igAdxFile_metaObject;
igMetaField *g_igAdxFile_bIsOpenMetaField;
igMetaField *g_igAdxFile_pBufferMetaField;
igMetaField *g_igAdxFile_pBufferPtrMetaField;
igMetaField *g_igAdxFile_pTmpBufferMetaField;
igMetaField *g_igAdxFile_bUseAsyncMetaField;
igMetaField *g_igAdxFile_bUseAlchemyAsyncMetaField;
igMetaField *g_igAdxFile_bUseBufferMetaField;
igMetaField *g_igAdxFile_bBufferFilledMetaField;
igMetaField *g_igAdxFile_iBufferSizeMetaField;
igMetaField *g_igAdxFile_iBufferPosMetaField;
igMetaField *g_igAdxFile_iSeekPositionMetaField;
igMetaField *g_igAdxFile_iFileSizeMetaField;
igMetaField *g_igAdxFile_iSectorSizeMetaField;
igMetaField *g_igAdxFile_lSleepTimeMetaField;

void FUN_00334dc0(int arg0) {
    FUN_00334ec0();
    igMetaObject_CreateInstance(g_igAdxFile_metaObject, arg0);
}

void *FUN_00334e00(void) {
    igMetaObject *g = g_igAdxFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00334ec0();
    }
    return g_igAdxFile_metaObject;
}

int igAdxFile_GetVTable(void) {
    struct Obj_334e50 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w10 = 0;
    obj.vt = &DAT_005337f0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005337f0[0];
    igFile_Destroy(&obj, 0);
    return t;
}

void FUN_00334ec0(void)
{
    igMetaObject_RunStaticInit(igAdxFile_Register);
}

void *igAdxFile_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdxFile_metaObject,
        igFile_Register,
        igFile_GetPublishedMetaObject,
        igAdxFile_GetMetaObject,
        "igAdxFile",
        0x68, /* instance size */
        igAdxFile_GetVTable,
        igAdxFile_InitFields,
        FUN_003350b0, /* extra callback item */
        0 /* callback list */
    );
}

void igAdxFile_GetMetaObject(void)
{
    FUN_00334e00();
}

static FieldFactory g_igAdxFile_ctorTable[] = {
    igBoolMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igUnsignedLongMetaField_Create,
};
static const char *g_igAdxFile_fieldTable[] = {
    "_bIsOpen",
    "_pBuffer",
    "_pBufferPtr",
    "_pTmpBuffer",
    "_bUseAsync",
    "_bUseAlchemyAsync",
    "_bUseBuffer",
    "_bBufferFilled",
    "_iBufferSize",
    "_iBufferPos",
    "_iSeekPosition",
    "_iFileSize",
    "_iSectorSize",
    "_lSleepTime",
};
static igMetaField **g_igAdxFile_fieldHandles[] = {
    &g_igAdxFile_bIsOpenMetaField,
    &g_igAdxFile_pBufferMetaField,
    &g_igAdxFile_pBufferPtrMetaField,
    &g_igAdxFile_pTmpBufferMetaField,
    &g_igAdxFile_bUseAsyncMetaField,
    &g_igAdxFile_bUseAlchemyAsyncMetaField,
    &g_igAdxFile_bUseBufferMetaField,
    &g_igAdxFile_bBufferFilledMetaField,
    &g_igAdxFile_iBufferSizeMetaField,
    &g_igAdxFile_iBufferPosMetaField,
    &g_igAdxFile_iSeekPositionMetaField,
    &g_igAdxFile_iFileSizeMetaField,
    &g_igAdxFile_iSectorSizeMetaField,
    &g_igAdxFile_lSleepTimeMetaField,
};
static int g_igAdxFile_fieldOffsets[] = {
    44,
    48,
    52,
    56,
    60,
    61,
    62,
    63,
    64,
    68,
    72,
    76,
    80,
    88,
};

void igAdxFile_InitFields(void) {
    int firstField;
    void *meta;

    meta = g_igAdxFile_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igAdxFile_ctorTable, 0xE);
    igBoolMetaField_SetDefaultValue(((int)igMetaObject_GetFieldAt(meta, firstField + 4)), 1);
    igBoolMetaField_SetDefaultValue(((int)igMetaObject_GetFieldAt(meta, firstField + 5)), 1);
    igBoolMetaField_SetDefaultValue(((int)igMetaObject_GetFieldAt(meta, firstField + 6)), 1);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, firstField + 8)), 0x20000);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, firstField + 0xC)), 0x800);
    igUnsignedLongMetaField_SetDefaultValue(((int)igMetaObject_GetFieldAt(meta, firstField + 0xD)), 0xFE502A);
    igMetaObject_NameFields(meta, g_igAdxFile_fieldTable, g_igAdxFile_fieldHandles, g_igAdxFile_fieldOffsets, firstField);
    *(int *)((char *)g_igAdxFile_metaObject + 64) = (int)(&igFile_GetMetaObjectFunction);
    igMetaObject_AddExitCallback(&FUN_003350d0);
}

void FUN_003350b0(void)
{
    igAdxFile_StaticInitialize();
}

void FUN_003350d0(void)
{
    igAdxFile_StaticFinalize();
}

igMetaObject *g_igAdxAudio_metaObject;
igMetaField *g_igAdxAudio_pWorkAreaMetaField;
igMetaField *g_igAdxAudio_iWorkSizeMetaField;
igMetaField *g_igAdxAudio_iMaxHandlesMetaField;
igMetaField *g_igAdxAudio_iMaxChannelsMetaField;
igMetaField *g_igAdxAudio_iTypeMetaField;
igMetaField *g_igAdxAudio_iMaxStreamsMetaField;
igMetaField *g_igAdxAudio_iMaxFrequencyMetaField;
igMetaField *g_igAdxAudio_bIsInitializedMetaField;
igMetaField *g_igAdxAudio_filenameMetaField;

void igAdxAudio_Create(int arg0) {
    FUN_00335260();
    igMetaObject_CreateInstance(g_igAdxAudio_metaObject, arg0);
}

igMetaObject *FUN_00335130(void) {
    if (g_igAdxAudio_metaObject == 0) {
        g_igAdxAudio_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAdxAudio_metaObject;
}

void *FUN_00335180(void) {
    igMetaObject *g = g_igAdxAudio_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00335260();
    }
    return g_igAdxAudio_metaObject;
}

int igAdxAudio_GetVTable(void) {
    struct W o;
    int r;

    int *p; int *a1; int t;
    igObject_InitHeader(&o);
    o.vt = DAT_00533730;
    *(int *)((char *)&o + 40) = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_00533730;
    if (&*(int *)((char *)&o + 40) != 0) { p = *(int **)((char *)&o + 40); if (p != 0) { a1 = p - 2; t = p[-1] - 1; p[-1] = t; if (t == 0) StringChunk_ReleaseHeader(*a1, a1); } }
    return r;
}

void FUN_00335260(void)
{
    igMetaObject_RunStaticInit(igAdxAudio_Register);
}

void *igAdxAudio_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdxAudio_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igAdxAudio_GetMetaObject,
        "igAdxAudio",
        0x30, /* instance size */
        igAdxAudio_GetVTable,
        igAdxAudio_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igAdxAudio_GetMetaObject(void)
{
    FUN_00335180();
}

static FieldFactory g_igAdxAudio_ctorTable[] = {
    igRawRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_igAdxAudio_fieldTable[] = {
    "_pWorkArea",
    "_iWorkSize",
    "_iMaxHandles",
    "_iMaxChannels",
    "_iType",
    "_iMaxStreams",
    "_iMaxFrequency",
    "_bIsInitialized",
    "_filename",
};
static igMetaField **g_igAdxAudio_fieldHandles[] = {
    &g_igAdxAudio_pWorkAreaMetaField,
    &g_igAdxAudio_iWorkSizeMetaField,
    &g_igAdxAudio_iMaxHandlesMetaField,
    &g_igAdxAudio_iMaxChannelsMetaField,
    &g_igAdxAudio_iTypeMetaField,
    &g_igAdxAudio_iMaxStreamsMetaField,
    &g_igAdxAudio_iMaxFrequencyMetaField,
    &g_igAdxAudio_bIsInitializedMetaField,
    &g_igAdxAudio_filenameMetaField,
};
static int g_igAdxAudio_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void igAdxAudio_InitFields(void) {
    int firstField;
    void *meta;

    meta = g_igAdxAudio_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igAdxAudio_ctorTable, 9);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, firstField + 2)), 4);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, firstField + 3)), 2);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, firstField + 5)), 4);
    igIntMetaField_SetDefault(((int)igMetaObject_GetFieldAt(meta, firstField + 6)), 0xBB80);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(meta, firstField + 8)), 0);
    igMetaObject_NameFields(meta, g_igAdxAudio_fieldTable, g_igAdxAudio_fieldHandles, g_igAdxAudio_fieldOffsets, firstField);
}

igMetaObject *g_igMovieCodecList_metaObject;

void FUN_00335400(int arg0) {
    FUN_00335520();
    igMetaObject_CreateInstance(g_igMovieCodecList_metaObject, arg0);
}

igMetaObject *FUN_00335440(void) {
    if (g_igMovieCodecList_metaObject == 0) {
        g_igMovieCodecList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMovieCodecList_metaObject;
}

void *FUN_00335490(void) {
    igMetaObject *g = g_igMovieCodecList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00335520();
    }
    return g_igMovieCodecList_metaObject;
}

int igMovieCodecList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00533a60[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_00335520(void)
{
    igMetaObject_RunStaticInit(igMovieCodecList_Register);
}

static igMetaObjectCallback g_igMovieCodecList_callbackList[] = { FUN_003357a0, 0 };

void *igMovieCodecList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieCodecList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMovieCodecList_GetMetaObject,
        "igMovieCodecList",
        0x14, /* instance size */
        igMovieCodecList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMovieCodecList_callbackList /* callback list */
    );
}

void igMovieCodecList_GetMetaObject(void)
{
    FUN_00335490();
}

igMetaObject *g_igMovieCodec_metaObject;

igMetaObject *FUN_003355d0(void) {
    if (g_igMovieCodec_metaObject == 0) {
        g_igMovieCodec_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMovieCodec_metaObject;
}

void *FUN_00335620(void) {
    igMetaObject *g = g_igMovieCodec_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003357a0();
    }
    return g_igMovieCodec_metaObject;
}

int igMovieCodec_GetVTable(void) {
    union U_335670 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00533d60[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

O *FUN_00335700(O *arg0, long long arg1) {
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    if (arg0 != 0) {
        arg0->vt = (int)(&DAT_00533d60[0]);
        if (arg0 != 0) {
            arg0->vt = (int)(&g_igNamedObject_vtable[0]);
            if (&arg0->f8 != 0) {
                temp_v1 = (void *)(arg0->f8);
                if (temp_v1 != 0) {
                    temp_a1 = (int *)((char *)temp_v1 - 8);
                    temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
                    *(int *)((char *)(temp_v1) - 4) = temp_v0;
                    if (temp_v0 == 0) {
                        StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                    }
                }
            }
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void FUN_003357a0(void)
{
    igMetaObject_RunStaticInit(igMovieCodec_Register);
}

void *igMovieCodec_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieCodec_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igMovieCodec_GetMetaObject,
        "igMovieCodec",
        0xc, /* instance size */
        igMovieCodec_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMovieCodec_GetMetaObject(void)
{
    FUN_00335620();
}

igMetaObject *g_igCriMovieCodec_metaObject;
igMetaField *g_igCriMovieCodec_initializedMetaField;
igMetaField *g_igCriMovieCodec_visualContextMetaField;
igMetaField *g_igCriMovieCodec_audioContextMetaField;

igMetaObject *FUN_00335850(void)
{
    igMetaObject *g = g_igCriMovieCodec_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003359b0();
    return g_igCriMovieCodec_metaObject;
}

int igCriMovieCodec_GetVTable(void) {
    struct Obj_3358a0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00533c70[0];
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00533c70[0];
    FUN_00335930((struct R **)&obj.w5, (short)(-1));
    FUN_00130140(&obj.w4, -1);
    FUN_00335700((O *)&obj, (long long)0);
    return t;
}

struct R **FUN_00335930(struct R **arg0, short arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_003359b0(void)
{
    igMetaObject_RunStaticInit(igCriMovieCodec_Register);
}

static igMetaObjectCallback g_igCriMovieCodec_callbackList[] = { FUN_0014a0e0, FUN_00143010, 0 };

void *igCriMovieCodec_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCriMovieCodec_metaObject,
        igMovieCodec_Register,
        igMovieCodec_GetPublishedMetaObject,
        igCriMovieCodec_GetMetaObject,
        "igCriMovieCodec",
        0x18, /* instance size */
        igCriMovieCodec_GetVTable,
        igCriMovieCodec_InitFields,
        0, /* extra callback item */
        g_igCriMovieCodec_callbackList /* callback list */
    );
}

void igCriMovieCodec_GetMetaObject(void)
{
    FUN_00335850();
}

igMetaObject *FUN_00335a70(void) {
    return g_igMovieCodec_metaObject;
}

static FieldFactory g_igCriMovieCodec_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igCriMovieCodec_fieldTable[] = {
    "_initialized",
    "_visualContext",
    "_audioContext",
};
static igMetaField **g_igCriMovieCodec_fieldHandles[] = {
    &g_igCriMovieCodec_initializedMetaField,
    &g_igCriMovieCodec_visualContextMetaField,
    &g_igCriMovieCodec_audioContextMetaField,
};
static int g_igCriMovieCodec_fieldOffsets[] = {
    12,
    16,
    20,
};

void igCriMovieCodec_InitFields(void) {
    int firstField;
    igObjectRefMetaField *visualContextField;
    igObjectRefMetaField *audioContextField;
    void *meta;
    igMetaField *initializedField;

    meta = g_igCriMovieCodec_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igCriMovieCodec_ctorTable, 3);
    initializedField = (igMetaField *)igMetaObject_GetFieldAt(meta, firstField);
    initializedField->_persistent = 0;
    visualContextField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, firstField + 1);
    visualContextField->_metaObject = FUN_0014a040();
    visualContextField->_persistent = 0;
    audioContextField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, firstField + 2);
    audioContextField->_metaObject = FUN_00142f70();
    audioContextField->_persistent = 0;
    igMetaObject_NameFields(meta, g_igCriMovieCodec_fieldTable, g_igCriMovieCodec_fieldHandles, g_igCriMovieCodec_fieldOffsets, firstField);
}

igMetaObject *g_igCriMovieData_metaObject;
igMetaField *g_igCriMovieData_mwplyMetaField;
igMetaField *g_igCriMovieData_cprmbufMetaField;
igMetaField *g_igCriMovieData_adxtMetaField;
igMetaField *g_igCriMovieData_adxworkMetaField;
igMetaField *g_igCriMovieData_macroFunctionMetaField;

void FUN_00335b40(int arg0) {
    FUN_00335c10();
    igMetaObject_CreateInstance(g_igCriMovieData_metaObject, arg0);
}

igMetaObject *FUN_00335b80(void) {
    igMetaObject *g = g_igCriMovieData_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_00335c10();
    return g_igCriMovieData_metaObject;
}

int igCriMovieData_GetVTable(void) {
    struct Obj_3346b0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00533d00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00335c10(void)
{
    igMetaObject_RunStaticInit(igCriMovieData_Register);
}

void *igCriMovieData_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCriMovieData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igCriMovieData_GetMetaObject,
        "igCriMovieData",
        0x1c, /* instance size */
        igCriMovieData_GetVTable,
        igCriMovieData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igCriMovieData_GetMetaObject(void)
{
    FUN_00335b80();
}

static FieldFactory g_igCriMovieData_ctorTable[] = {
    igStructMetaField_Create,
    igRawRefMetaField_Create,
    igStructMetaField_Create,
    igRawRefMetaField_Create,
    igStructMetaField_Create,
};
static const char *g_igCriMovieData_fieldTable[] = {
    "_mwply",
    "_cprmbuf",
    "_adxt",
    "_adxwork",
    "_macroFunction",
};
static igMetaField **g_igCriMovieData_fieldHandles[] = {
    &g_igCriMovieData_mwplyMetaField,
    &g_igCriMovieData_cprmbufMetaField,
    &g_igCriMovieData_adxtMetaField,
    &g_igCriMovieData_adxworkMetaField,
    &g_igCriMovieData_macroFunctionMetaField,
};
static int g_igCriMovieData_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
};

void igCriMovieData_InitFields(void) {
    int firstField;
    void *mwplyField;
    void *adxtField;
    void *macroFunctionField;
    void *meta;

    meta = g_igCriMovieData_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igCriMovieData_ctorTable, 5);
    mwplyField = (void *)(igMetaObject_GetFieldAt(meta, firstField));
    ((igMetaField *)mwplyField)->_size = 4;
    ((igMetaField *)mwplyField)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, firstField + 1))->_persistent = 0;
    adxtField = (void *)(igMetaObject_GetFieldAt(meta, firstField + 2));
    ((igMetaField *)adxtField)->_size = 4;
    ((igMetaField *)adxtField)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, firstField + 3))->_persistent = 0;
    macroFunctionField = (void *)(igMetaObject_GetFieldAt(meta, firstField + 4));
    ((igMetaField *)macroFunctionField)->_size = 4;
    ((igMetaField *)macroFunctionField)->_persistent = 0;
    igMetaObject_NameFields(meta, g_igCriMovieData_fieldTable, g_igCriMovieData_fieldHandles, g_igCriMovieData_fieldOffsets, firstField);
}

igMetaObject *g_igMovieInfoList_metaObject;

void FUN_00335da0(int arg0) {
    FUN_00335ec0();
    igMetaObject_CreateInstance(g_igMovieInfoList_metaObject, arg0);
}

igMetaObject *FUN_00335de0(void) {
    if (g_igMovieInfoList_metaObject == 0) {
        g_igMovieInfoList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMovieInfoList_metaObject;
}

igMetaObject *FUN_00335e30(void) {
    igMetaObject *g = g_igMovieInfoList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_00335ec0();
done:
    return g_igMovieInfoList_metaObject;
}

int igMovieInfoList_GetVTable(void) {
    struct Obj_3346b0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005339f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00335ec0(void)
{
    igMetaObject_RunStaticInit(igMovieInfoList_Register);
}

static igMetaObjectCallback g_igMovieInfoList_callbackList[] = { FUN_003364c0, 0 };

void *igMovieInfoList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMovieInfoList_GetMetaObject,
        "igMovieInfoList",
        0x14, /* instance size */
        igMovieInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMovieInfoList_callbackList /* callback list */
    );
}

void igMovieInfoList_GetMetaObject(void)
{
    FUN_00335e30();
}

igMetaObject *g_igTextureBindAttrList_metaObject;

void FUN_00335f70(int arg0) {
    FUN_00336090();
    igMetaObject_CreateInstance(g_igTextureBindAttrList_metaObject, arg0);
}

igMetaObject *FUN_00335fb0(void) {
    if (g_igTextureBindAttrList_metaObject == 0) {
        g_igTextureBindAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTextureBindAttrList_metaObject;
}

igMetaObject *FUN_00336000(void) {
    if (g_igTextureBindAttrList_metaObject == 0 || !isValid(g_igTextureBindAttrList_metaObject)) FUN_00336090();
    return g_igTextureBindAttrList_metaObject;
}

int igTextureBindAttrList_GetVTable(void) {
    Obj_336050 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00533980[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00336090(void)
{
    igMetaObject_RunStaticInit(igTextureBindAttrList_Register);
}

static igMetaObjectCallback g_igTextureBindAttrList_callbackList[] = { FUN_00132a00, 0 };

void *igTextureBindAttrList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureBindAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igTextureBindAttrList_GetMetaObject,
        "igTextureBindAttrList",
        0x14, /* instance size */
        igTextureBindAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igTextureBindAttrList_callbackList /* callback list */
    );
}

void igTextureBindAttrList_GetMetaObject(void)
{
    FUN_00336000();
}

static const char *g_igMovieInfo_movieStateNames[] = {
    "IG_MOVIE_PLAY",
    "IG_MOVIE_PAUSE",
    "IG_MOVIE_ENDED",
};
static int g_igMovieInfo_movieStateValues[] = {
    0,
    1,
    2,
};
igMetaEnum *g_igMovieInfo_movieStateMetaEnum;

igMetaEnum *FUN_00336140(void) {
    if (g_igMovieInfo_movieStateMetaEnum == 0) {
        g_igMovieInfo_movieStateMetaEnum = igMetaEnum_Create("IG_MOVIE_STATE", g_igMovieInfo_movieStateNames, g_igMovieInfo_movieStateValues, 3);
    }
    return g_igMovieInfo_movieStateMetaEnum;
}

static const char *g_igMovieInfo_movieTypeNames[] = {
    "IG_MOVIE_TYPE_DEFAULT",
    "IG_MOVIE_TYPE_VIDEO",
    "IG_MOVIE_TYPE_AUDIO",
    "IG_MOVIE_TYPE_BOTH",
};
static int g_igMovieInfo_movieTypeValues[] = {
    0,
    1,
    2,
    3,
};
igMetaEnum *g_igMovieInfo_movieTypeMetaEnum;

igMetaEnum *FUN_003361a0(void) {
    if (g_igMovieInfo_movieTypeMetaEnum == 0) {
        g_igMovieInfo_movieTypeMetaEnum = igMetaEnum_Create("IG_MOVIE_TYPE", g_igMovieInfo_movieTypeNames, g_igMovieInfo_movieTypeValues, 4);
    }
    return g_igMovieInfo_movieTypeMetaEnum;
}

igMetaObject *g_igMovieInfo_metaObject;
igMetaField *g_igMovieInfo_pathMetaField;
igMetaField *g_igMovieInfo_typeMetaField;
igMetaField *g_igMovieInfo_loopMetaField;
igMetaField *g_igMovieInfo_widthMetaField;
igMetaField *g_igMovieInfo_heightMetaField;
igMetaField *g_igMovieInfo_audioChannelMetaField;
igMetaField *g_igMovieInfo_audioVolumeMetaField;
igMetaField *g_igMovieInfo_videoTexturesMetaField;
igMetaField *g_igMovieInfo_minificationFilterMetaField;
igMetaField *g_igMovieInfo_magnificationFilterMetaField;
igMetaField *g_igMovieInfo_tileWidthMetaField;
igMetaField *g_igMovieInfo_tileHeightMetaField;
igMetaField *g_igMovieInfo_codecTypeMetaField;
igMetaField *g_igMovieInfo_codecMetaField;
igMetaField *g_igMovieInfo_stateMetaField;
igMetaField *g_igMovieInfo_sceneInfoMetaField;
igMetaField *g_igMovieInfo_runtimeImageMetaField;
igMetaField *g_igMovieInfo_runtimeTexturesMetaField;
igMetaField *g_igMovieInfo_imageFormatMetaField;
igMetaField *g_igMovieInfo_userdataMetaField;
igMetaField *g_igMovieInfo_bitrateMetaField;

void FUN_00336200(int arg0) {
    FUN_003364c0();
    igMetaObject_CreateInstance(g_igMovieInfo_metaObject, arg0);
}

void *FUN_00336240(void) {
    igMetaObject *g = g_igMovieInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003364c0();
    }
    return g_igMovieInfo_metaObject;
}

int igMovieInfo_GetVTable(void) {
    struct Obj_334e50 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00533910[0];
    obj.w5 = 0;
    obj.w12 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w20 = 0;
    obj.w21 = 0;
    obj.w22 = 0;
    obj.w24 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00533910[0];
    ObjectRef_Destruct_001363f0(&obj.w24, -1);
    FUN_00131aa0(&obj.w22, -1);
    FUN_00132390(&obj.w21, -1);
    FUN_001d3650(&obj.w20, -1);
    FUN_00336440((void **)&obj.w18, -1);
    igStringRef_Destruct(&obj.w17, -1);
    FUN_003363c0((void **)&obj.w12, (long long)(-1));
    igStringRef_Destruct(&obj.w5, -1);
    igInfo_Destroy(&obj, 0);
    return t;
}

void **FUN_003363c0(void **arg0, long long arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_00336440(void **arg0, int arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_003364c0(void)
{
    igMetaObject_RunStaticInit(igMovieInfo_Register);
}

static igMetaObjectCallback g_igMovieInfo_callbackList[] = { FUN_00336090, FUN_003357a0, FUN_0019b270, FUN_0014e050, FUN_0013a440, igObject_EnsureRegistered, 0 };

void *igMovieInfo_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        igMovieInfo_GetMetaObject,
        "igMovieInfo",
        0x68, /* instance size */
        igMovieInfo_GetVTable,
        igMovieInfo_InitFields,
        0, /* extra callback item */
        g_igMovieInfo_callbackList /* callback list */
    );
}

void igMovieInfo_GetMetaObject(void)
{
    FUN_00336240();
}

static FieldFactory g_igMovieInfo_ctorTable[] = {
    igStringMetaField_Create,
    igEnumMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igMovieInfo_fieldTable[] = {
    "_path",
    "_type",
    "_loop",
    "_width",
    "_height",
    "_audioChannel",
    "_audioVolume",
    "_videoTextures",
    "_minificationFilter",
    "_magnificationFilter",
    "_tileWidth",
    "_tileHeight",
    "_codecType",
    "_codec",
    "_state",
    "_sceneInfo",
    "_runtimeImage",
    "_runtimeTextures",
    "_imageFormat",
    "_userdata",
    "_bitrate",
};
static igMetaField **g_igMovieInfo_fieldHandles[] = {
    &g_igMovieInfo_pathMetaField,
    &g_igMovieInfo_typeMetaField,
    &g_igMovieInfo_loopMetaField,
    &g_igMovieInfo_widthMetaField,
    &g_igMovieInfo_heightMetaField,
    &g_igMovieInfo_audioChannelMetaField,
    &g_igMovieInfo_audioVolumeMetaField,
    &g_igMovieInfo_videoTexturesMetaField,
    &g_igMovieInfo_minificationFilterMetaField,
    &g_igMovieInfo_magnificationFilterMetaField,
    &g_igMovieInfo_tileWidthMetaField,
    &g_igMovieInfo_tileHeightMetaField,
    &g_igMovieInfo_codecTypeMetaField,
    &g_igMovieInfo_codecMetaField,
    &g_igMovieInfo_stateMetaField,
    &g_igMovieInfo_sceneInfoMetaField,
    &g_igMovieInfo_runtimeImageMetaField,
    &g_igMovieInfo_runtimeTexturesMetaField,
    &g_igMovieInfo_imageFormatMetaField,
    &g_igMovieInfo_userdataMetaField,
    &g_igMovieInfo_bitrateMetaField,
};
static int g_igMovieInfo_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
    96,
    100,
};

void igMovieInfo_InitFields(void) {
    int firstField;
    void *meta;
    struct MovieInfoFieldView *videoTexturesField;
    struct MovieInfoFieldView *codecField;
    struct MovieInfoFieldView *sceneInfoField;
    struct MovieInfoFieldView *runtimeImageField;
    struct MovieInfoFieldView *runtimeTexturesField;
    struct MovieInfoFieldView *typeField;
    struct MovieInfoFieldView *minificationFilterField;
    struct MovieInfoFieldView *magnificationFilterField;
    struct MovieInfoFieldView *stateField;
    struct MovieInfoFieldView *imageFormatField;
    struct MovieInfoFieldView *userdataField;

    meta = g_igMovieInfo_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igMovieInfo_ctorTable, 0x15);
    igStringMetaField_SetDefaultText(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField)), 0);
    typeField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 1)));
    igEnumMetaField_SetDefaultValue(typeField, 0);
    typeField->f52 = (int)FUN_003361a0;
    igIntMetaField_SetDefault(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 3)), -1);
    igIntMetaField_SetDefault(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 4)), -1);
    igIntMetaField_SetDefault(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 5)), -1);
    igIntMetaField_SetDefault(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 6)), -1);
    videoTexturesField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 7)));
    videoTexturesField->f56 = (int)FUN_00335fb0();
    minificationFilterField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 8)));
    igEnumMetaField_SetDefaultValue(minificationFilterField, 0);
    *(void (**)(void))&minificationFilterField->f52 = FUN_00149980;
    magnificationFilterField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 9)));
    igEnumMetaField_SetDefaultValue(magnificationFilterField, 0);
    *(void (**)(void))&magnificationFilterField->f52 = FUN_00149980;
    igIntMetaField_SetDefault(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0xA)), -1);
    igIntMetaField_SetDefault(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0xB)), -1);
    igStringMetaField_SetDefaultText(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0xC)), 0);
    codecField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0xD)));
    codecField->f56 = (int)FUN_003355d0();
    codecField->f38 = 0;
    stateField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0xE)));
    igEnumMetaField_SetDefaultValue(stateField, 1);
    stateField->f52 = (int)FUN_00336140;
    sceneInfoField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0xF)));
    sceneInfoField->f56 = FUN_0019aee0();
    sceneInfoField->f38 = 0;
    runtimeImageField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0x10)));
    runtimeImageField->f56 = FUN_0014dfb0();
    runtimeImageField->f38 = 0;
    runtimeTexturesField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0x11)));
    runtimeTexturesField->f56 = FUN_0013a360();
    runtimeTexturesField->f38 = 0;
    imageFormatField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0x12)));
    igEnumMetaField_SetDefaultValue(imageFormatField, 7);
    imageFormatField->f38 = 0;
    imageFormatField->f52 = (int)FUN_001499e0;
    userdataField = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0x13)));
    userdataField->f56 = (int)((int) g_igObject_metaObject[0]);
    userdataField->f38 = 0;
    igIntMetaField_SetDefault(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(meta, firstField + 0x14)), -1);
    igMetaObject_NameFields(meta, g_igMovieInfo_fieldTable, g_igMovieInfo_fieldHandles, g_igMovieInfo_fieldOffsets, firstField);
}

igMetaObject *g_igMovieRenderer_metaObject;
igMetaField *g_igMovieRenderer_movieManagerMetaField;

igMetaObject *FUN_00336860(void) {
    if (g_igMovieRenderer_metaObject == 0) {
        g_igMovieRenderer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMovieRenderer_metaObject;
}

void *FUN_003368b0(void) {
    igMetaObject *g = g_igMovieRenderer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00336a70();
    }
    return g_igMovieRenderer_metaObject;
}

int igMovieRenderer_GetVTable(void) {
    Obj_336900 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.m8 = 0;
    obj.vt = &DAT_00533de0[0];
    obj.m12 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00533de0[0];
    obj.rel12();
    obj.vt = &DAT_0052d060[0];
    obj.rel8();
    return r;
}

void **FUN_003369f0(void **arg0, short arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00336a70(void)
{
    igMetaObject_RunStaticInit(igMovieRenderer_Register);
}

static igMetaObjectCallback g_igMovieRenderer_callbackList[] = { FUN_00336f10, 0 };

void *igMovieRenderer_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        igMovieRenderer_GetMetaObject,
        "igMovieRenderer",
        0x10, /* instance size */
        igMovieRenderer_GetVTable,
        igMovieRenderer_InitFields,
        0, /* extra callback item */
        g_igMovieRenderer_callbackList /* callback list */
    );
}

void igMovieRenderer_GetMetaObject(void)
{
    FUN_003368b0();
}

static FieldFactory g_igMovieRenderer_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igMovieRenderer_fieldTable[] = {
    "_movieManager",
};
static igMetaField **g_igMovieRenderer_fieldHandles[] = {
    &g_igMovieRenderer_movieManagerMetaField,
};
static int g_igMovieRenderer_fieldOffsets[] = {
    12,
};

void igMovieRenderer_InitFields(void) {
    int firstField;
    void *movieManagerField;
    void *meta;

    meta = g_igMovieRenderer_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igMovieRenderer_ctorTable, 1);
    movieManagerField = (void *)(igMetaObject_GetFieldAt(meta, firstField));
    ((igObjectRefMetaField *)movieManagerField)->_metaObject = (int)FUN_00336c10();
    ((igMetaField *)movieManagerField)->_persistent = 0;
    igMetaObject_NameFields(meta, g_igMovieRenderer_fieldTable, g_igMovieRenderer_fieldHandles, g_igMovieRenderer_fieldOffsets, firstField);
}

igMetaObject *g_igMovieManager_metaObject;
igMetaField *g_igMovieManager_movieListMetaField;
igMetaField *g_igMovieManager_audioDisabledMetaField;
igMetaField *g_igMovieManager_audioMetaField;
igMetaField *g_igMovieManager_codecListMetaField;
igMetaField *g_igMovieManager_movieRendererMetaField;
igMetaField *g_igMovieManager_rendererListMetaField;

void igMovieManager_CreateInstance(int arg0) {
    FUN_00336f10();
    igMetaObject_CreateInstance(g_igMovieManager_metaObject, arg0);
}

igMetaObject *FUN_00336c10(void) {
    if (g_igMovieManager_metaObject == 0) {
        g_igMovieManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMovieManager_metaObject;
}

void *FUN_00336c60(void) {
    bool ok;
    if (g_igMovieManager_metaObject == 0) goto make;
    ok = !!(g_igMovieManager_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00336f10();
done:;
    return g_igMovieManager_metaObject;
}

int igMovieManager_GetVTable(void) {
    union U_336cb0 u;
    int temp_s4;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[0] = (int)(&DAT_00533e50[0]);
    u.w[4] = 0;
    u.w[6] = 0;
    u.w[7] = 0;
    u.w[8] = 0;
    u.w[9] = 0;
    temp_s4 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00533e50[0]);
    FUN_00232ae0(&u.w[9], -1);
    FUN_00336e90((O_336e90 *)(&u.w[8]), (short)(-1));
    FUN_00336e10((void **)(&u.w[7]), (long long)(-1));
    FUN_00335930((struct R **)(&u.w[6]), (short)(-1));
    FUN_00336d90((struct Ref **)(&u.w[4]), (short)(-1));
    FUN_00231030(u.b, 0);
    return temp_s4;
}

void **FUN_00336d90(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_00336e10(void **arg0, long long arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O_336e90 *FUN_00336e90(O_336e90 *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void FUN_00336f10(void)
{
    igMetaObject_RunStaticInit(igMovieManager_Register);
}

static igMetaObjectCallback g_igMovieManager_callbackList[] = { FUN_00335ec0, FUN_00143010, FUN_00335520, FUN_00336a70, igRendererOrderedList_EnsureRegistered, 0 };

void *igMovieManager_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        igMovieManager_GetMetaObject,
        "igMovieManager",
        0x28, /* instance size */
        igMovieManager_GetVTable,
        igMovieManager_InitFields,
        0, /* extra callback item */
        g_igMovieManager_callbackList /* callback list */
    );
}

void igMovieManager_GetMetaObject(void)
{
    FUN_00336c60();
}

static FieldFactory g_igMovieManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igMovieManager_fieldTable[] = {
    "_movieList",
    "_audioDisabled",
    "_audio",
    "_codecList",
    "_movieRenderer",
    "_rendererList",
};
static igMetaField **g_igMovieManager_fieldHandles[] = {
    &g_igMovieManager_movieListMetaField,
    &g_igMovieManager_audioDisabledMetaField,
    &g_igMovieManager_audioMetaField,
    &g_igMovieManager_codecListMetaField,
    &g_igMovieManager_movieRendererMetaField,
    &g_igMovieManager_rendererListMetaField,
};
static int g_igMovieManager_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
};

void igMovieManager_InitFields(void) {
    igObjectRefMetaField *movieListField;
    igObjectRefMetaField *audioField;
    igObjectRefMetaField *codecListField;
    igObjectRefMetaField *movieRendererField;
    igObjectRefMetaField *rendererListField;
    void *meta;
    int startIndex;

    meta = g_igMovieManager_metaObject;
    startIndex = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igMovieManager_ctorTable, 6);
    movieListField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, startIndex));
    movieListField->_metaObject = (int)FUN_00335de0();
    ((igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, startIndex + 1))->_persistent = 0;
    audioField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, startIndex + 2));
    audioField->_metaObject = FUN_00142f70();
    audioField->_persistent = 0;
    codecListField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, startIndex + 3));
    codecListField->_metaObject = (int)FUN_00335440();
    codecListField->_persistent = 0;
    movieRendererField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, startIndex + 4));
    movieRendererField->_metaObject = (int)FUN_00336860();
    movieRendererField->_construct = 1;
    movieRendererField->_persistent = 0;
    rendererListField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, startIndex + 5));
    rendererListField->_metaObject = FUN_0044c4d0();
    igMetaObject_NameFields(meta, g_igMovieManager_fieldTable, g_igMovieManager_fieldHandles, g_igMovieManager_fieldOffsets, startIndex);
}

igMetaObject *g_igMoviePlugin_metaObject;
igMetaField *g_igMoviePlugin_movieManagerMetaField;

void *FUN_003370f0(void) {
    igMetaObject *g = g_igMoviePlugin_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003371d0();
    }
    return g_igMoviePlugin_metaObject;
}

int igMoviePlugin_GetVTable(void) {
    Obj_337140 o;
    int r;
    Q *q;

    igObject_InitHeader(&o);
    o.vt = &DAT_00533ee0[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00533ee0[0];
    if (&o.s != 0) {
        q = o.s;
        if (q != 0) {
            q->f4 -= 1;
            if ((q->f4 & 0x7fffff) == 0) {
                igObject_Destroy(q);
            }
        }
    }
    return r;
}

void FUN_003371d0(void)
{
    igMetaObject_RunStaticInit(igMoviePlugin_Register);
}

static igMetaObjectCallback g_igMoviePlugin_callbackList[] = { FUN_00336f10, 0 };

void *igMoviePlugin_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMoviePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        igMoviePlugin_GetMetaObject,
        "igMoviePlugin",
        0xc, /* instance size */
        igMoviePlugin_GetVTable,
        igMoviePlugin_InitFields,
        0, /* extra callback item */
        g_igMoviePlugin_callbackList /* callback list */
    );
}

void igMoviePlugin_GetMetaObject(void)
{
    FUN_003370f0();
}

int FUN_00337290(void) {
    return g_igInsightPlugin_metaObject[0];
}

static FieldFactory g_igMoviePlugin_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igMoviePlugin_fieldTable[] = {
    "_movieManager",
};
static igMetaField **g_igMoviePlugin_fieldHandles[] = {
    &g_igMoviePlugin_movieManagerMetaField,
};
static int g_igMoviePlugin_fieldOffsets[] = {
    8,
};

void igMoviePlugin_InitFields(void) {
    int firstField;
    void *movieManagerField;
    void *meta;

    meta = g_igMoviePlugin_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igMoviePlugin_ctorTable, 1);
    movieManagerField = (void *)(igMetaObject_GetFieldAt(meta, firstField));
    ((igObjectRefMetaField *)movieManagerField)->_metaObject = (int)FUN_00336c10();
    igMetaObject_NameFields(meta, g_igMoviePlugin_fieldTable, g_igMoviePlugin_fieldHandles, g_igMoviePlugin_fieldOffsets, firstField);
}

int Gap__Insight__igInsightPlugin__vfunc_20(void)
{
    return g_igInsightPlugin_metaObject[0];
}

igMetaObject *Gap__igMovieInfo__vfunc_20(void)
{
    return g_igMovieInfo_metaObject;
}

igMetaObject *Gap__igTextureBindAttrList__vfunc_20(void)
{
    return g_igTextureBindAttrList_metaObject;
}

igMetaObject *Gap__igMovieInfoList__vfunc_20(void)
{
    return g_igMovieInfoList_metaObject;
}

igMetaObject *Gap__igMovieCodecList__vfunc_20(void)
{
    return g_igMovieCodecList_metaObject;
}

igMetaObject *Gap__igFileNameList__vfunc_20(void)
{
    return g_igFileNameList_metaObject;
}

igMetaObject *Gap__igAdxAfsFile__vfunc_20(void)
{
    return g_igAdxAfsFile_metaObject;
}

igMetaObject *Gap__igFileName__vfunc_20(void)
{
    return g_igFileName_metaObject;
}

igMetaObject *Gap__igAdxAfsFileList__vfunc_20(void)
{
    return g_igAdxAfsFileList_metaObject;
}

igMetaObject *Gap__igMovieCodecList__vfunc_22(void)
{
    return g_igMovieCodec_metaObject;
}

igMetaObject *Gap__igMovieInfoList__vfunc_22(void)
{
    return g_igMovieInfo_metaObject;
}

int Gap__igTextureBindAttrList__vfunc_22(void)
{
    return g_igTextureBindAttr_metaObject[0];
}

igMetaObject *Gap__igAdxAfsFileList__vfunc_22(void)
{
    return g_igAdxAfsFile_metaObject;
}

igMetaObject *Gap__igFileNameList__vfunc_22(void)
{
    return g_igFileName_metaObject;
}

#pragma pop
