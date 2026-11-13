#include "dw4/reflected.h"
static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }

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
extern "C" void FUN_002fe480(...);
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
extern "C" int igMetaObject_CreateFields(void *, int *, int);
extern "C" int igMetaObject_GetFieldCount(void *);
extern "C" int igMetaObject_NameFields(void *, int *, int *, int *, int);
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
extern "C" int FUN_002be100(void);
extern "C" void * igMetaObject_GetFieldAt(...);
extern "C" void igFileName_InitFields(void);
extern "C" int igMetaObject_CreateInstance(int, int);
extern "C" void FUN_00334dc0(int arg0);
extern "C" void *FUN_00334e00(void);
extern "C" int igAdxFile_GetVTable(void);
extern "C" void FUN_00334ec0(void);
extern "C" void *igFile_Register(void);
extern "C" void *igAdxFile_Register(void);
extern "C" void igAdxFile_GetMetaObject(void);
extern "C" int FUN_002d3890(int, int);
extern "C" int FUN_002ea4b0(...);
extern "C" int FUN_0030ec10(int, int);
extern "C" int thunk_igFile_GetMetaObject(void);
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
extern "C" int igMetaEnum_Create(int *, int *, int *, int);
extern "C" int FUN_00336140(void);
extern "C" int FUN_003361a0(void);
extern "C" void FUN_00336200(int arg0);
extern "C" void *FUN_00336240(void);
extern "C" int FUN_00131aa0(int *, int);
extern "C" int FUN_00132390(int *, int);
extern "C" int FUN_001d3650(int *, int);
extern "C" int ObjectRef_Destruct_001363f0(int *, int);
extern "C" int StringRef_Destruct_00130720(int *, int);
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
extern "C" int FUN_002dc7a0(void *, int *);
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
extern "C" igMetaObject *g_igAdx_metaObject[4];
struct Obj { int *vt; char pad[4]; };
extern "C" int DAT_00533790[4];
extern "C" void * g_objectSystem[4];
struct igMetaObject_334510;
extern "C" igMetaObject_334510 * igObject_GetMetaObject_ParentAccessor(...);
extern "C" const char igAdx_className[];
extern "C" int g_metadataAllocatorKey[4];
extern "C" igMetaObject *g_igAdxAfsFileList_metaObject[4];
struct Obj_3346b0 { int *vt; char pad[28]; };
extern "C" int DAT_00533c00[4];
struct igMetaObject_334710;
extern "C" igMetaObject_334710 * igObjectList_GetPublishedMetaObject(...);
extern "C" const char igAdxAfsFileList_className[];
extern "C" char g_igAdxAfsFileList_callbackList[];
extern "C" igMetaObject *g_igAdxAfsFile_metaObject[4];
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U_3347f0 { int vt; char b[32]; };
extern "C" int g_igNamedObject_vtable[4];
extern "C" int DAT_00533b40[4];
extern "C" int DAT_00533ba0[4];
struct igMetaObject_3348f0;
extern "C" igMetaObject_3348f0 *igFileName_GetPublishedMetaObject(void);
extern "C" const char igAdxAfsFile_className[];
extern "C" int g_igAdxAfsFile_ctorTable[4];
extern "C" int g_igAdxAfsFile_fieldTable[4];
extern "C" int DAT_004c2680[4];
extern "C" int DAT_004c2688[4];
extern "C" igMetaObject *g_igFileNameList_metaObject[4];
extern "C" int DAT_00533ad0[4];
extern "C" const char igFileNameList_className[];
extern "C" char pL3[];
extern "C" igMetaObject *g_igFileName_metaObject[4];
union U_334b90 { int vt; char b[16]; };
struct igMetaObject_334c90;
extern "C" igMetaObject_334c90 * igNamedObject_GetPublishedMetaObject(...);
extern "C" const char igFileName_className[];
extern "C" char g_igFileName_callbackList[];
extern "C" int g_igFileName_ctorTable[4];
extern "C" int g_igFileName_fieldTable[4];
extern "C" int DAT_004c26b0[4];
extern "C" int DAT_004c26b8[4];
extern "C" igMetaObject *g_igAdxFile_metaObject[4];
struct Obj_334e50 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
extern "C" int FUN_002c0790(struct Obj_334e50 *, int);
extern "C" int DAT_005337f0[4];
struct igMetaObject_334ee0;
extern "C" igMetaObject_334ee0 *igFile_GetPublishedMetaObject(void);
extern "C" const char igAdxFile_className[];
extern "C" int g_igAdxFile_ctorTable[4];
extern "C" int g_igAdxFile_fieldTable[4];
extern "C" int DAT_004c2740[4];
extern "C" int DAT_004c2780[4];
extern "C" igMetaObject *g_igAdxAudio_metaObject[4];
struct W { int *vt; int f[11]; };
extern "C" int DAT_00533730[4];
extern "C" const char igAdxAudio_className[];
extern "C" int g_igAdxAudio_ctorTable[4];
extern "C" int g_igAdxAudio_fieldTable[4];
extern "C" int DAT_004c2820[4];
extern "C" int DAT_004c2850[4];
extern "C" igMetaObject *g_igMovieCodecList_metaObject[4];
extern "C" int DAT_00533a60[4];
extern "C" const char igMovieCodecList_className[];
extern "C" char g_igMovieCodecList_callbackList[];
extern "C" igMetaObject *g_igMovieCodec_metaObject[4];
union U_335670 { int vt; char b[16]; };
extern "C" int DAT_00533d60[4];
extern "C" int thunk_FUN_002ed460__002ff810(struct O *);
typedef struct O { int vt; int pad; int f8; } O;
extern "C" O *FUN_00335700(O *arg0, long long arg1);
extern "C" const char igMovieCodec_className[];
extern "C" igMetaObject *g_igCriMovieCodec_metaObject[4];
extern "C" igMetaObject *FUN_00335850(void);
struct Obj_3358a0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int DAT_00533c70[4];
struct R { int vt; unsigned int rc; };
extern "C" struct R **FUN_00335930(struct R **arg0, short arg1);
struct igMetaObject_3359d0;
extern "C" igMetaObject_3359d0 *igMovieCodec_GetPublishedMetaObject(void);
extern "C" const char igCriMovieCodec_className[];
extern "C" char g_igCriMovieCodec_callbackList[];
struct F { char pad[38]; unsigned char b38; char pad2[17]; int f56; };
extern "C" int g_igCriMovieCodec_ctorTable[4];
extern "C" int g_igCriMovieCodec_fieldTable[4];
extern "C" int DAT_004c28b0[4];
extern "C" int DAT_004c28c0[4];
extern "C" igMetaObject *g_igCriMovieData_metaObject[4];
extern "C" igMetaObject *FUN_00335b80(void);
extern "C" int DAT_00533d00[4];
extern "C" const char igCriMovieData_className[];
extern "C" int g_igCriMovieData_ctorTable[4];
extern "C" int g_igCriMovieData_fieldTable[4];
extern "C" int DAT_004c2910[4];
extern "C" int DAT_004c2930[4];
extern "C" igMetaObject *g_igMovieInfoList_metaObject[4];
extern "C" igMetaObject *FUN_00335e30(void);
extern "C" int DAT_005339f0[4];
extern "C" const char igMovieInfoList_className[];
extern "C" char g_igMovieInfoList_callbackList[];
extern "C" igMetaObject *g_igTextureBindAttrList_metaObject[4];
extern "C" igMetaObject *FUN_00336000(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
typedef struct { int *vt; int pad[7]; } Obj_336050;
extern "C" int DAT_00533980[4];
extern "C" const char igTextureBindAttrList_className[];
extern "C" char g_igTextureBindAttrList_callbackList[];
extern "C" int DAT_004c2958[4];
extern "C" int DAT_004c2968[4];
extern "C" int IG_MOVIE_STATE[4];
extern "C" int DAT_005877a0[4];
extern "C" int DAT_004c2980[4];
extern "C" int DAT_004c2990[4];
extern "C" int IG_MOVIE_TYPE[4];
extern "C" int DAT_005877a8[4];
extern "C" igMetaObject *g_igMovieInfo_metaObject[4];
extern "C" int FUN_00131b20(struct Obj_334e50 *, int);
extern "C" int DAT_00533910[4];
struct igMetaObject_3364e0;
extern "C" igMetaObject_3364e0 *igInfo_GetPublishedMetaObject(void);
extern "C" const char igMovieInfo_className[];
extern "C" char g_igMovieInfo_callbackList[];
struct MovieInfoFieldView { char pad0[38]; char f38; char pad1[13]; int f52; int f56; };
extern "C" int g_igMovieInfo_ctorTable[4];
extern "C" int g_igMovieInfo_fieldTable[4];
extern "C" int DAT_004c2a80[4];
extern "C" int DAT_004c2ae0[4];
extern "C" int DAT_004c2b38[4];
extern "C" int DAT_004c2b40[4];
extern "C" int DAT_004c2b48[4];
extern "C" int DAT_004c2b50[4];
extern "C" int DAT_004c2b58[4];
extern "C" int g_igObject_metaObject[4];
extern "C" igMetaObject *g_igMovieRenderer_metaObject[4];
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
extern "C" const char igMovieRenderer_className[];
extern "C" char g_igMovieRenderer_callbackList[];
extern "C" int g_igMovieRenderer_ctorTable[4];
extern "C" int g_igMovieRenderer_fieldTable[4];
extern "C" int DAT_004c2b78[4];
extern "C" int DAT_004c2b80[4];
extern "C" igMetaObject *g_igMovieManager_metaObject[4];
union U_336cb0 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int DAT_00533e50[4];
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" void **FUN_00336d90(struct Ref **self, short flag);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O_336e90 { S_temp_a0 *m; };
extern "C" O_336e90 *FUN_00336e90(O_336e90 *arg0, short arg1);
struct igMetaObject_336f30;
extern "C" igMetaObject_336f30 *igInfoManager_GetPublishedMetaObject(void);
extern "C" const char igMovieManager_className[];
extern "C" char g_igMovieManager_callbackList[];
struct Fld { char p0[38]; char f38; char p1[13]; char f52; int f56; };
extern "C" int g_igMovieManager_ctorTable[4];
extern "C" int g_igMovieManager_fieldTable[4];
extern "C" int DAT_004c2bf0[4];
extern "C" int DAT_004c2c10[4];
extern "C" igMetaObject *g_igMoviePlugin_metaObject[4];
typedef struct Q { char pad4[4]; int f4; } Q;
typedef struct { int *vt; int w[1]; Q *s; } Obj_337140;
extern "C" int DAT_00533ee0[4];
struct igMetaObject_3371f0;
extern "C" igMetaObject_3371f0 *igInsightPlugin_GetPublishedMetaObject(void);
extern "C" const char igMoviePlugin_className[];
extern "C" char g_igMoviePlugin_callbackList[];
extern "C" int g_igInsightPlugin_metaObject[4];
extern "C" int g_igMoviePlugin_ctorTable[4];
extern "C" int g_igMoviePlugin_fieldTable[4];
extern "C" int DAT_004c2c40[4];
extern "C" int DAT_004c2c48[4];
extern "C" int g_igInsightPlugin_metaObject[4];
extern "C" int g_igTextureBindAttr_metaObject[4];

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

void *FUN_00334460(void) {
    igMetaObject *g = g_igAdx_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003344f0();
    }
    return g_igAdx_metaObject[0];
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
        g_igAdx_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igAdx_GetMetaObject,
        igAdx_className,
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
    FUN_002fe480(FUN_003345f0);
}

void FUN_003345d0(void)
{
    igAdx_CreateScratchString();
}

void FUN_003345f0(void)
{
    igAdx_Shutdown();
}

igMetaObject *FUN_00334610(void) {
    if (g_igAdxAfsFileList_metaObject[0] == 0) {
        g_igAdxAfsFileList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAdxAfsFileList_metaObject[0];
}

void *FUN_00334660(void) {
    bool ok;
    if (g_igAdxAfsFileList_metaObject[0] == 0) goto make;
    ok = !!(g_igAdxAfsFileList_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003346f0();
done:;
    return g_igAdxAfsFileList_metaObject[0];
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

void *igAdxAfsFileList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAdxAfsFileList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAdxAfsFileList_GetMetaObject,
        igAdxAfsFileList_className,
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

void *FUN_003347a0(void) {
    igMetaObject *g = g_igAdxAfsFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003348d0();
    }
    return g_igAdxAfsFile_metaObject[0];
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
        g_igAdxAfsFile_metaObject,
        igFileName_Register,
        igFileName_GetPublishedMetaObject,
        igAdxAfsFile_GetMetaObject,
        igAdxAfsFile_className,
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
    return g_igFileName_metaObject[0];
}

void igAdxAfsFile_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAdxAfsFile_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAdxAfsFile_ctorTable[0], 2);
    igMetaObject_NameFields(temp_s0, &g_igAdxAfsFile_fieldTable[0], &DAT_004c2680[0], &DAT_004c2688[0], temp_s1);
}

void *FUN_00334a00(void) {
    unsigned char b;
    if (g_igFileNameList_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_igFileNameList_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00334a90();
done:
    return g_igFileNameList_metaObject[0];
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

void *igFileNameList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileNameList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igFileNameList_GetMetaObject,
        igFileNameList_className,
        0x14, /* instance size */
        igFileNameList_GetVTable,
        0,
        0, /* extra callback item */
        pL3 /* callback list */
    );
}

void igFileNameList_GetMetaObject(void)
{
    FUN_00334a00();
}

void *FUN_00334b40(void) {
    igMetaObject *g = g_igFileName_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00334c70();
    }
    return g_igFileName_metaObject[0];
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

void *igFileName_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileName_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igFileName_GetMetaObject,
        igFileName_className,
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

void igFileName_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFileName_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igFileName_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002be100();
    igMetaObject_NameFields(temp_s0, &g_igFileName_fieldTable[0], &DAT_004c26b0[0], &DAT_004c26b8[0], temp_s2);
}

void FUN_00334dc0(int arg0) {
    FUN_00334ec0();
    igMetaObject_CreateInstance(*(int *)0x587668, arg0);
}

void *FUN_00334e00(void) {
    igMetaObject *g = g_igAdxFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00334ec0();
    }
    return g_igAdxFile_metaObject[0];
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
    FUN_002c0790(&obj, 0);
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
        g_igAdxFile_metaObject,
        igFile_Register,
        igFile_GetPublishedMetaObject,
        igAdxFile_GetMetaObject,
        igAdxFile_className,
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

void igAdxFile_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(((void * *)g_igAdxFile_metaObject)[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAdxFile_ctorTable[0], 0xE);
    FUN_002d3890(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4)), 1);
    FUN_002d3890(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)), 1);
    FUN_002d3890(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6)), 1);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8)), 0x20000);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC)), 0x800);
    FUN_0030ec10(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD)), 0xFE502A);
    igMetaObject_NameFields(temp_s0, &g_igAdxFile_fieldTable[0], &DAT_004c2740[0], &DAT_004c2780[0], temp_s1);
    *(int *)((char *)(((void * *)g_igAdxFile_metaObject)[0]) + 64) = (int)(&thunk_igFile_GetMetaObject);
    FUN_002fe480(&FUN_003350d0);
}

void FUN_003350b0(void)
{
    igAdxFile_StaticInitialize();
}

void FUN_003350d0(void)
{
    igAdxFile_StaticFinalize();
}

void igAdxAudio_Create(int arg0) {
    FUN_00335260();
    igMetaObject_CreateInstance(*(int *)0x5876E0, arg0);
}

igMetaObject *FUN_00335130(void) {
    if (g_igAdxAudio_metaObject[0] == 0) {
        g_igAdxAudio_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAdxAudio_metaObject[0];
}

void *FUN_00335180(void) {
    igMetaObject *g = g_igAdxAudio_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00335260();
    }
    return g_igAdxAudio_metaObject[0];
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
        g_igAdxAudio_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igAdxAudio_GetMetaObject,
        igAdxAudio_className,
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

void igAdxAudio_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAdxAudio_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAdxAudio_ctorTable[0], 9);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)), 4);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)), 2);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)), 4);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6)), 0xBB80);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8)), 0);
    igMetaObject_NameFields(temp_s0, &g_igAdxAudio_fieldTable[0], &DAT_004c2820[0], &DAT_004c2850[0], temp_s1);
}

void FUN_00335400(int arg0) {
    FUN_00335520();
    igMetaObject_CreateInstance(*(int *)0x587730, arg0);
}

igMetaObject *FUN_00335440(void) {
    if (g_igMovieCodecList_metaObject[0] == 0) {
        g_igMovieCodecList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igMovieCodecList_metaObject[0];
}

void *FUN_00335490(void) {
    igMetaObject *g = g_igMovieCodecList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00335520();
    }
    return g_igMovieCodecList_metaObject[0];
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

void *igMovieCodecList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieCodecList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMovieCodecList_GetMetaObject,
        igMovieCodecList_className,
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

igMetaObject *FUN_003355d0(void) {
    if (g_igMovieCodec_metaObject[0] == 0) {
        g_igMovieCodec_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igMovieCodec_metaObject[0];
}

void *FUN_00335620(void) {
    igMetaObject *g = g_igMovieCodec_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003357a0();
    }
    return g_igMovieCodec_metaObject[0];
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
            thunk_FUN_002ed460__002ff810(arg0);
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
        g_igMovieCodec_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igMovieCodec_GetMetaObject,
        igMovieCodec_className,
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

igMetaObject *FUN_00335850(void)
{
    igMetaObject *g = g_igCriMovieCodec_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003359b0();
    return g_igCriMovieCodec_metaObject[0];
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

void *igCriMovieCodec_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCriMovieCodec_metaObject,
        igMovieCodec_Register,
        igMovieCodec_GetPublishedMetaObject,
        igCriMovieCodec_GetMetaObject,
        igCriMovieCodec_className,
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
    return g_igMovieCodec_metaObject[0];
}

void igCriMovieCodec_InitFields(void) {
    int temp_s2;
    struct F *temp_s1;
    struct F *temp_s1_2;
    void *temp_s0;
    struct F *t0;

    temp_s0 = (void *)g_igCriMovieCodec_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igCriMovieCodec_ctorTable[0], 3);
    t0 = (struct F *)((struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s2));
    t0->b38 = 0;
    temp_s1 = (struct F *)(((struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    temp_s1->f56 = FUN_0014a040();
    temp_s1->b38 = 0;
    temp_s1_2 = (struct F *)(((struct F *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)));
    temp_s1_2->f56 = FUN_00142f70();
    temp_s1_2->b38 = 0;
    igMetaObject_NameFields(temp_s0, &g_igCriMovieCodec_fieldTable[0], &DAT_004c28b0[0], &DAT_004c28c0[0], temp_s2);
}

void FUN_00335b40(int arg0) {
    FUN_00335c10();
    igMetaObject_CreateInstance(*(int *)0x587760, arg0);
}

igMetaObject *FUN_00335b80(void) {
    igMetaObject *g = g_igCriMovieData_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_00335c10();
    return g_igCriMovieData_metaObject[0];
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
        g_igCriMovieData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igCriMovieData_GetMetaObject,
        igCriMovieData_className,
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

void igCriMovieData_InitFields(void) {
    int temp_s1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_s0;

    temp_s0 = (void *)g_igCriMovieData_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igCriMovieData_ctorTable[0], 5);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igMetaField *)temp_v0)->_size = 4;
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1))->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igMetaField *)temp_v0_2)->_size = 4;
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3))->_persistent = 0;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igMetaField *)temp_v0_3)->_size = 4;
    ((igMetaField *)temp_v0_3)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_igCriMovieData_fieldTable[0], &DAT_004c2910[0], &DAT_004c2930[0], temp_s1);
}

void FUN_00335da0(int arg0) {
    FUN_00335ec0();
    igMetaObject_CreateInstance(*(int *)0x587790, arg0);
}

igMetaObject *FUN_00335de0(void) {
    if (g_igMovieInfoList_metaObject[0] == 0) {
        g_igMovieInfoList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igMovieInfoList_metaObject[0];
}

igMetaObject *FUN_00335e30(void) {
    igMetaObject *g = g_igMovieInfoList_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_00335ec0();
done:
    return g_igMovieInfoList_metaObject[0];
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

void *igMovieInfoList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMovieInfoList_GetMetaObject,
        igMovieInfoList_className,
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

void FUN_00335f70(int arg0) {
    FUN_00336090();
    igMetaObject_CreateInstance(*(int *)0x587798, arg0);
}

igMetaObject *FUN_00335fb0(void) {
    if (g_igTextureBindAttrList_metaObject[0] == 0) {
        g_igTextureBindAttrList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igTextureBindAttrList_metaObject[0];
}

igMetaObject *FUN_00336000(void) {
    if (g_igTextureBindAttrList_metaObject[0] == 0 || !isValid(g_igTextureBindAttrList_metaObject[0])) FUN_00336090();
    return g_igTextureBindAttrList_metaObject[0];
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

void *igTextureBindAttrList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureBindAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igTextureBindAttrList_GetMetaObject,
        igTextureBindAttrList_className,
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

int FUN_00336140(void) {
    if (DAT_005877a0[0] == 0) {
        DAT_005877a0[0] = igMetaEnum_Create(&IG_MOVIE_STATE[0], &DAT_004c2958[0], &DAT_004c2968[0], 3);
    }
    return DAT_005877a0[0];
}

int FUN_003361a0(void) {
    if (DAT_005877a8[0] == 0) {
        DAT_005877a8[0] = igMetaEnum_Create(&IG_MOVIE_TYPE[0], &DAT_004c2980[0], &DAT_004c2990[0], 4);
    }
    return DAT_005877a8[0];
}

void FUN_00336200(int arg0) {
    FUN_003364c0();
    igMetaObject_CreateInstance(*(int *)0x5877B0, arg0);
}

void *FUN_00336240(void) {
    igMetaObject *g = g_igMovieInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003364c0();
    }
    return g_igMovieInfo_metaObject[0];
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
    StringRef_Destruct_00130720(&obj.w17, -1);
    FUN_003363c0((void **)&obj.w12, (long long)(-1));
    StringRef_Destruct_00130720(&obj.w5, -1);
    FUN_00131b20(&obj, 0);
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

void *igMovieInfo_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        igMovieInfo_GetMetaObject,
        igMovieInfo_className,
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

void igMovieInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    struct MovieInfoFieldView *temp_s2;
    struct MovieInfoFieldView *temp_s2_2;
    struct MovieInfoFieldView *temp_s2_3;
    struct MovieInfoFieldView *temp_s2_4;
    struct MovieInfoFieldView *temp_s2_5;
    struct MovieInfoFieldView *temp_v0;
    struct MovieInfoFieldView *temp_v0_2;
    struct MovieInfoFieldView *temp_v0_3;
    struct MovieInfoFieldView *temp_v0_4;
    struct MovieInfoFieldView *temp_v0_5;
    struct MovieInfoFieldView *temp_v0_6;

    temp_s0 = (void *)g_igMovieInfo_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igMovieInfo_ctorTable[0], 0x15);
    igStringMetaField_SetDefaultText(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1)), 0);
    temp_v0 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)));
    FUN_002dc7a0(temp_v0, &DAT_004c2b38[0]);
    temp_v0->f52 = (int)FUN_003361a0;
    FUN_002ea4b0(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)), -1);
    FUN_002ea4b0(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4)), -1);
    FUN_002ea4b0(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)), -1);
    FUN_002ea4b0(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6)), -1);
    temp_s2 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7)));
    temp_s2->f56 = (int)FUN_00335fb0();
    temp_v0_2 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8)));
    FUN_002dc7a0(temp_v0_2, &DAT_004c2b40[0]);
    *(void (**)(void))&temp_v0_2->f52 = FUN_00149980;
    temp_v0_3 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9)));
    FUN_002dc7a0(temp_v0_3, &DAT_004c2b48[0]);
    *(void (**)(void))&temp_v0_3->f52 = FUN_00149980;
    FUN_002ea4b0(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA)), -1);
    FUN_002ea4b0(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB)), -1);
    igStringMetaField_SetDefaultText(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC)), 0);
    temp_s2_2 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD)));
    temp_s2_2->f56 = (int)FUN_003355d0();
    temp_s2_2->f38 = 0;
    temp_v0_4 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE)));
    FUN_002dc7a0(temp_v0_4, &DAT_004c2b50[0]);
    temp_v0_4->f52 = (int)FUN_00336140;
    temp_s2_3 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF)));
    temp_s2_3->f56 = FUN_0019aee0();
    temp_s2_3->f38 = 0;
    temp_s2_4 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10)));
    temp_s2_4->f56 = FUN_0014dfb0();
    temp_s2_4->f38 = 0;
    temp_s2_5 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11)));
    temp_s2_5->f56 = FUN_0013a360();
    temp_s2_5->f38 = 0;
    temp_v0_5 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12)));
    FUN_002dc7a0(temp_v0_5, &DAT_004c2b58[0]);
    temp_v0_5->f38 = 0;
    temp_v0_5->f52 = (int)FUN_001499e0;
    temp_v0_6 = (((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x13)));
    temp_v0_6->f56 = (int)((int) g_igObject_metaObject[0]);
    temp_v0_6->f38 = 0;
    FUN_002ea4b0(((struct MovieInfoFieldView *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x14)), -1);
    igMetaObject_NameFields(temp_s0, &g_igMovieInfo_fieldTable[0], &DAT_004c2a80[0], &DAT_004c2ae0[0], temp_s1);
}

igMetaObject *FUN_00336860(void) {
    if (g_igMovieRenderer_metaObject[0] == 0) {
        g_igMovieRenderer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igMovieRenderer_metaObject[0];
}

void *FUN_003368b0(void) {
    igMetaObject *g = g_igMovieRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00336a70();
    }
    return g_igMovieRenderer_metaObject[0];
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

void *igMovieRenderer_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        igMovieRenderer_GetMetaObject,
        igMovieRenderer_className,
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

void igMovieRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMovieRenderer_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igMovieRenderer_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00336c10();
    ((igMetaField *)temp_s1)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_igMovieRenderer_fieldTable[0], &DAT_004c2b78[0], &DAT_004c2b80[0], temp_s2);
}

void igMovieManager_CreateInstance(int arg0) {
    FUN_00336f10();
    igMetaObject_CreateInstance(*(int *)0x587870, arg0);
}

igMetaObject *FUN_00336c10(void) {
    if (g_igMovieManager_metaObject[0] == 0) {
        g_igMovieManager_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igMovieManager_metaObject[0];
}

void *FUN_00336c60(void) {
    bool ok;
    if (g_igMovieManager_metaObject[0] == 0) goto make;
    ok = !!(g_igMovieManager_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00336f10();
done:;
    return g_igMovieManager_metaObject[0];
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

void *igMovieManager_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        igMovieManager_GetMetaObject,
        igMovieManager_className,
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

void igMovieManager_InitFields(void) {
    struct Fld *temp_s2;
    struct Fld *temp_s2_2;
    struct Fld *temp_s2_3;
    struct Fld *temp_s2_4;
    struct Fld *temp_s2_5;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_igMovieManager_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igMovieManager_ctorTable[0], 6);
    temp_s2 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s1, temp_s0));
    temp_s2->f56 = (int)FUN_00335de0();
    ((struct Fld *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1))->f38 = 0;
    temp_s2_2 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    temp_s2_2->f56 = FUN_00142f70();
    temp_s2_2->f38 = 0;
    temp_s2_3 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    temp_s2_3->f56 = (int)FUN_00335440();
    temp_s2_3->f38 = 0;
    temp_s2_4 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    temp_s2_4->f56 = (int)FUN_00336860();
    temp_s2_4->f52 = 1;
    temp_s2_4->f38 = 0;
    temp_s2_5 = ((struct Fld *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    temp_s2_5->f56 = FUN_0044c4d0();
    igMetaObject_NameFields(temp_s1, &g_igMovieManager_fieldTable[0], &DAT_004c2bf0[0], &DAT_004c2c10[0], temp_s0);
}

void *FUN_003370f0(void) {
    igMetaObject *g = g_igMoviePlugin_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003371d0();
    }
    return g_igMoviePlugin_metaObject[0];
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

void *igMoviePlugin_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMoviePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        igMoviePlugin_GetMetaObject,
        igMoviePlugin_className,
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

void igMoviePlugin_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMoviePlugin_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igMoviePlugin_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00336c10();
    igMetaObject_NameFields(temp_s0, &g_igMoviePlugin_fieldTable[0], &DAT_004c2c40[0], &DAT_004c2c48[0], temp_s2);
}

int Gap__Insight__igInsightPlugin__vfunc_20(void)
{
    return g_igInsightPlugin_metaObject[0];
}

igMetaObject *Gap__igMovieInfo__vfunc_20(void)
{
    return g_igMovieInfo_metaObject[0];
}

igMetaObject *Gap__igTextureBindAttrList__vfunc_20(void)
{
    return g_igTextureBindAttrList_metaObject[0];
}

igMetaObject *Gap__igMovieInfoList__vfunc_20(void)
{
    return g_igMovieInfoList_metaObject[0];
}

igMetaObject *Gap__igMovieCodecList__vfunc_20(void)
{
    return g_igMovieCodecList_metaObject[0];
}

igMetaObject *Gap__igFileNameList__vfunc_20(void)
{
    return g_igFileNameList_metaObject[0];
}

igMetaObject *Gap__igAdxAfsFile__vfunc_20(void)
{
    return g_igAdxAfsFile_metaObject[0];
}

igMetaObject *Gap__igFileName__vfunc_20(void)
{
    return g_igFileName_metaObject[0];
}

igMetaObject *Gap__igAdxAfsFileList__vfunc_20(void)
{
    return g_igAdxAfsFileList_metaObject[0];
}

igMetaObject *Gap__igMovieCodecList__vfunc_22(void)
{
    return g_igMovieCodec_metaObject[0];
}

igMetaObject *Gap__igMovieInfoList__vfunc_22(void)
{
    return g_igMovieInfo_metaObject[0];
}

int Gap__igTextureBindAttrList__vfunc_22(void)
{
    return g_igTextureBindAttr_metaObject[0];
}

igMetaObject *Gap__igAdxAfsFileList__vfunc_22(void)
{
    return g_igAdxAfsFile_metaObject[0];
}

igMetaObject *Gap__igFileNameList__vfunc_22(void)
{
    return g_igFileName_metaObject[0];
}
