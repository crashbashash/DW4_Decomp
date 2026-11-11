#include "dw4/reflected.h"

extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igMetaObject_Create(...);
extern "C" int DAT_00587040[4];
extern "C" int DAT_0058c680[4];
extern "C" int FUN_004586a0(void);
struct G { int pad[9]; int f; };
extern "C" void *igViewerStatisticsManager_GetMetaObject(void);
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int igObject_InitHeader(...);
extern "C" int FUN_00130140(...);
extern "C" int FUN_0013a880(...);
extern "C" int FUN_001489a0(...);
extern "C" int FUN_0014e420(...);
extern "C" int FUN_0025a2b0(...);
extern "C" int FUN_004583f0(...);
extern "C" int DAT_005425b0[4];
extern "C" char *DAT_00586dc8[4];
extern "C" int igViewerStatisticsManager_GetVTable(void);
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" int igObject_Destroy(...);
extern "C" int FUN_00100610(...);
extern "C" ObjectRefWord *FUN_00458860(ObjectRefWord *self,int delete_storage);
extern "C" void FUN_004588e0(void);
extern "C" char igObject_GetMetaObject_ParentAccessor[];
extern "C" char igObject_Register[];
extern "C" char g_igViewerStatisticsManager_callbackList[];
extern "C" char igViewerStatisticsManager_className[];
extern "C" char g_igViewerStatisticsManager_metaObject[];
extern "C" int igMetaObject_RegisterClass(...);
extern "C" int ViewerLibrary_MarkRegistered(...);
extern "C" void igViewerStatisticsManager_Register(void);
extern "C" void thunk_igViewerStatisticsManager_GetMetaObject(void);
extern "C" int FUN_0014a040(...);
extern "C" int FUN_002b9540(...);
extern "C" int FUN_002c8b30(...);
extern "C" int FUN_002c8e50(...);
extern "C" int FUN_00452340(...);
extern "C" int igMetaObject_CreateFields(...);
extern "C" void *igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int DAT_004d08c0[4];
extern "C" int DAT_004d0900[4];
extern "C" int DAT_004d0940[4];
extern "C" int DAT_004d0980[4];
extern "C" void igViewerStatisticsManager_InitFields(void);
extern "C" int DAT_0058c700[4];
extern "C" int FUN_00458ae0(void);
extern "C" void *igStatisticsItemList_GetMetaObject(void);
struct Obj_458b80 { int *vt; char pad[28]; };
extern "C" int DAT_005421c0[4];
extern "C" int igStatisticsItemList_GetVTable(void);
extern "C" void FUN_00458bc0(void);
extern "C" char igObjectList_GetPublishedMetaObject[];
extern "C" char igObjectList_Register[];
extern "C" char g_igStatisticsItemList_callbackList[];
extern "C" char igStatisticsItemList_className[];
extern "C" char g_igStatisticsItemList_metaObject[];
extern "C" void igStatisticsItemList_Register(void);
extern "C" void thunk_igStatisticsItemList_GetMetaObject(void);
extern "C" int DAT_0058c708[4];
extern "C" int FUN_00458c50(void);
extern "C" void *igStatisticsItem_GetMetaObject(void);
struct Obj_458cf0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int FUN_003cafa0(...);
extern "C" int StringRef_Destruct_00130720(...);
extern "C" int DAT_00542620[4];
extern "C" int igStatisticsItem_GetVTable(void);
extern "C" void **FUN_00458dc0(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00458e40(ObjectRefWord *self,int delete_storage);
extern "C" void FUN_00458ec0(void);
extern "C" char igView_Register[];
extern "C" char igView_GetPublishedMetaObject[];
extern "C" char g_igStatisticsItem_callbackList[];
extern "C" char igStatisticsItem_className[];
extern "C" char g_igStatisticsItem_metaObject[];
extern "C" void igStatisticsItem_Register(void);
extern "C" void thunk_igStatisticsItem_GetMetaObject(void);
extern "C" int FUN_002dc7a0(...);
extern "C" int FUN_002e3810(void *, float);
extern "C" int FUN_002ea4b0(...);
extern "C" int FUN_0044bce0(void);
extern "C" int FUN_0044ff40(...);
extern "C" int FUN_004516e0(void);
extern "C" int FUN_00149b60(void);
extern "C" int DAT_004d09f0[4];
extern "C" int DAT_004d0a20[4];
extern "C" int DAT_004d0a50[4];
extern "C" int DAT_004d0a80[4];
extern "C" int DAT_004d0ab0[4];
extern "C" void igStatisticsItem_InitFields(void);
extern "C" int igMetaObject_CreateInstance(int, int);
extern "C" void FUN_004590c0(int arg0);
extern "C" int DAT_0058c770[4];
extern "C" void *igViewerAction_GetMetaObject(void);
extern "C" int DAT_00542460[4];
extern "C" int igViewerAction_GetVTable(void);
extern "C" void FUN_00459190(void);
extern "C" char igAction_GetPublishedMetaObject[];
extern "C" char igAction_Register[];
extern "C" char g_igViewerAction_callbackList[];
extern "C" char igViewerAction_className[];
extern "C" char g_igViewerAction_metaObject[];
extern "C" void igViewerAction_Register(void);
extern "C" void thunk_igViewerAction_GetMetaObject(void);
extern "C" int DAT_004d0ac0[4];
extern "C" int DAT_004d0ac8[4];
extern "C" int DAT_004d0ad0[4];
extern "C" int DAT_004d0ad8[4];
extern "C" void igViewerAction_InitFields(void);
extern "C" int FUN_00131aa0(...);
extern "C" int FUN_0013a360(...);
extern "C" int FUN_0014aa70(...);
extern "C" int FUN_00231030(...);
extern "C" int FUN_00233a40(...);
extern "C" int FUN_002c3d50(...);
extern "C" int FUN_0044c1c0(...);
extern "C" int FUN_0044cdf0(...);
extern "C" int FUN_0044d840(...);
extern "C" int FUN_0044ded0(...);
extern "C" int FUN_0044fdd0(...);
extern "C" int FUN_00458470(...);
extern "C" int FUN_00458570(...);
extern "C" int FUN_004585f0(...);
extern "C" int FUN_00458600(...);
extern "C" int FUN_00458610(...);
extern "C" int FUN_00458620(...);
extern "C" int FUN_00458630(...);
extern "C" int ObjectPointerList_FindIndex(...);
extern "C" int igMetaEnum_Create(...);
extern "C" int igMetaObject_FinalizeAndReplaceField(...);
extern "C" void **igMetaObject_FindFieldByName(...);
extern "C" void igMetaObject_RunStaticInit(...);
extern "C" int igObjectList_GetOrCreateMetaObject(...);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" char igInfoManager_GetPublishedMetaObject[];
extern "C" char igInfoManager_Register[];
extern "C" char g_igViewerSceneInfoManager_callbackList[];
extern "C" char igViewerSceneInfoManager_className[];
extern "C" char g_igViewerSceneInfoManager_metaObject[];
extern "C" int DAT_004d0ae0[4];
extern "C" int DAT_004d0af0[4];
extern "C" int DAT_004d0b50[4];
extern "C" int DAT_004d0c00[4];
extern "C" int DAT_004d0cb0[4];
extern "C" int DAT_004d0d60[4];
extern "C" int DAT_004d0e10[4];
extern "C" int DAT_0051eaf0[4];
extern "C" int DAT_0051ee50[4];
extern "C" int DAT_0051ee60[4];
extern "C" int DAT_005424c0[4];
extern "C" int DAT_0058c788[4];
extern "C" int DAT_0058c790[4];
extern "C" int DAT_0058c798[4];
struct MetaObjectFlags { char p[36]; unsigned f; };
struct R { int vt; unsigned int rc; };
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
union U { int vt; char b[208]; };
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" int FUN_004592e0(void);
extern "C" void FUN_00459340(int arg0);
extern "C" int FUN_00459380(void);
extern "C" void *igViewerSceneInfoManager_GetMetaObject(void);
extern "C" int igViewerSceneInfoManager_GetVTable(void);
extern "C" struct R **FUN_004597e0(struct R **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00459860(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_004598e0(void **arg0, int arg1);
extern "C" void **FUN_00459960(void **arg0, short arg1);
extern "C" void **FUN_004599e0(struct Ref **self, short flag);
extern "C" void **FUN_00459a60(void **arg0, long long arg1);
extern "C" O *FUN_00459ae0(O *arg0, short arg1);
extern "C" ObjectRefWord *FUN_00459b60(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_00459be0(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00459c60(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_00459ce0(void **arg0, short arg1);
extern "C" int *FUN_00459d60(int *p);
extern "C" int *FUN_00459d70(int *p);
extern "C" int *FUN_00459d80(int *p);
extern "C" int *FUN_00459d90(int *p);
extern "C" int *FUN_00459da0(int *p);
extern "C" int *FUN_00459db0(int *p);
extern "C" int *FUN_00459dc0(int *p);
extern "C" int *FUN_00459dd0(int *p);
extern "C" int *FUN_00459de0(int *p);
extern "C" int *FUN_00459df0(int *p);
extern "C" int *FUN_00459e00(int *p);
extern "C" int *FUN_00459e10(int *p);
extern "C" int *FUN_00459e20(int *p);
extern "C" int *FUN_00459e30(int *p);
extern "C" void FUN_00459e40(void);
extern "C" void igViewerSceneInfoManager_Register(void);
extern "C" void thunk_igViewerSceneInfoManager_GetMetaObject(void);
extern "C" void FUN_00459ee0(void);
typedef struct S { char pad[36]; unsigned flags; } S;
typedef struct { int *vt; int w[2]; char *s; } Obj_45a450;
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" S *g_igViewerModeChangeMessage_metaObject[4];
extern "C" int DAT_0058c8f8[4];
extern "C" int DAT_00542160[4];
extern "C" int DAT_004d0e18[4];
extern "C" int DAT_004d0e20[4];
extern "C" int DAT_004d0e28[4];
extern "C" int DAT_004d0e30[4];
extern "C" char igMessage_GetPublishedMetaObject[];
extern "C" char igMessage_Register[];
extern "C" char igViewerModeChangeMessage_className[];
extern "C" int FUN_0045a450(void);
extern "C" S *igViewerModeChangeMessage_GetMetaObject(void);
extern "C" int igViewerModeChangeMessage_GetVTable(void);
extern "C" void FUN_0045a580(void);
extern "C" void igViewerModeChangeMessage_Register(void);
extern "C" void thunk_igViewerModeChangeMessage_GetMetaObject(void);
extern "C" void igViewerModeChangeMessage_InitFields(void);
struct G_45a680 { char pad[36]; int f; };
struct Obj_45a680 { int *vt; char pad[8]; char *m; };
extern "C" struct G_45a680 *g_igViewerLoadingFileMessage_metaObject[4];
extern "C" int DAT_0058c910[4];
extern "C" int DAT_00542100[4];
extern "C" int DAT_004d0e38[4];
extern "C" int DAT_004d0e40[4];
extern "C" int DAT_004d0e48[4];
extern "C" int DAT_004d0e50[4];
extern "C" int DAT_0051eef0[4];
extern "C" char igViewerLoadingFileMessage_className[];
extern "C" void FUN_0045a680(int arg0);
extern "C" struct G_45a680 *igViewerLoadingFileMessage_GetMetaObject(void);
extern "C" int igViewerLoadingFileMessage_GetVTable(void);
extern "C" void FUN_0045a7a0(void);
extern "C" void igViewerLoadingFileMessage_Register(void);
extern "C" void thunk_igViewerLoadingFileMessage_GetMetaObject(void);
extern "C" void igViewerLoadingFileMessage_InitFields(void);
struct Obj_45a8c0 { int *vt; char pad[28]; };
extern "C" struct G *g_igViewerSceneInfoManagerController_metaObject[4];
extern "C" int DAT_0058c928[4];
extern "C" int DAT_00542540[4];
extern "C" int DAT_004d0e68[4];
extern "C" int DAT_004d0e70[4];
extern "C" int DAT_004d0e78[4];
extern "C" int DAT_004d0e80[4];
extern "C" char g_igViewerSceneInfoManagerController_callbackList[];
extern "C" char igViewerSceneInfoManagerController_className[];
extern "C" int FUN_0045a8c0(void);
extern "C" void *igViewerSceneInfoManagerController_GetMetaObject(void);
extern "C" int igViewerSceneInfoManagerController_GetVTable(void);
extern "C" void FUN_0045a9a0(void);
extern "C" void igViewerSceneInfoManagerController_Register(void);
extern "C" void thunk_igViewerSceneInfoManagerController_GetMetaObject(void);
extern "C" void igViewerSceneInfoManagerController_InitFields(void);
union U_45aaf0 { int vt; int *pv; char b[96]; };
extern "C" int FUN_00133950(void);
extern "C" int FUN_00134940(void);
extern "C" int FUN_00135e60(void);
extern "C" int FUN_00136040(void);
extern "C" int FUN_001361f0(void);
extern "C" int FUN_00136370(...);
extern "C" int FUN_001365e0(void);
extern "C" int FUN_00136750(void);
extern "C" int FUN_00137fb0(void);
extern "C" int FUN_001386d0(void);
extern "C" int FUN_0013b2b0(void);
extern "C" int FUN_0014f770(void);
extern "C" int FUN_00196190(void);
extern "C" int FUN_00197060(...);
extern "C" int FUN_00197160(...);
extern "C" int FUN_00197300(...);
extern "C" int FUN_00197350(...);
extern "C" int FUN_0019ac30(...);
extern "C" int FUN_0019c1a0(...);
extern "C" int FUN_0019c370(...);
extern "C" int FUN_0019c6a0(void);
extern "C" int FUN_0019d9e0(...);
extern "C" int FUN_0019dbb0(void);
extern "C" int FUN_001a38e0(void);
extern "C" int FUN_001a5d70(void);
extern "C" int FUN_001a7580(...);
extern "C" int FUN_001d3090(...);
extern "C" int FUN_001d97f0(...);
extern "C" int FUN_001d9870(...);
extern "C" int FUN_00229460(...);
extern "C" int FUN_00230f70(...);
extern "C" int FUN_00239200(...);
extern "C" int FUN_00239280(...);
extern "C" igMetaObject *g_igViewerRenderer_metaObject[4];
extern "C" int DAT_0058c940[4];
extern "C" int DAT_004d0ee0[4];
extern "C" int DAT_004d0f30[4];
extern "C" int DAT_004d0f80[4];
extern "C" int DAT_004d0fd0[4];
extern "C" int DAT_0052d060[4];
extern "C" int DAT_005423f0[4];
extern "C" char igRenderer_GetPublishedMetaObject[];
extern "C" char igRenderer_Register[];
extern "C" char g_igViewerRenderer_callbackList[];
extern "C" char igViewerRenderer_className[];
extern "C" int FUN_0045aaf0(void);
extern "C" igMetaObject *igViewerRenderer_GetMetaObject(void);
extern "C" int igViewerRenderer_GetVTable(void);
extern "C" ObjectRefWord *FUN_0045add0(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_0045ae50(struct R **arg0, short arg1);
extern "C" void **FUN_0045aed0(void **arg0, long long arg1);
extern "C" void **FUN_0045af50(void **arg0, int arg1);
extern "C" int *FUN_0045afd0(int *p);
extern "C" int *FUN_0045afe0(int *p);
extern "C" int *FUN_0045aff0(int *p);
extern "C" int *FUN_0045b000(int *p);
extern "C" int *FUN_0045b010(int *p);
extern "C" int *FUN_0045b020(int *p);
extern "C" int *FUN_0045b030(int *p);
extern "C" int *FUN_0045b040(int *p);
extern "C" int *FUN_0045b050(int *p);
extern "C" int *FUN_0045b060(int *p);
extern "C" int *FUN_0045b070(int *p);
extern "C" int *FUN_0045b080(int *p);
extern "C" void *FUN_0045b090(void *arg0);
extern "C" void FUN_0045b0d0(void);
extern "C" void igViewerRenderer_Register(void);
extern "C" void thunk_igViewerRenderer_GetMetaObject(void);
extern "C" void igViewerRenderer_InitFields(void);
extern "C" int DAT_0058c9e8[4];
extern "C" int FUN_0045b420(void);
struct SigViewerParameters_GetMetaObject { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern "C" SigViewerParameters_GetMetaObject *igViewerParameters_GetMetaObject(void);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int FUN_00196a50(...);
extern "C" int FUN_0019b1f0(...);
extern "C" int FUN_001d6560(...);
extern "C" int FUN_00229350(...);
extern "C" int FUN_0044c110(...);
extern "C" int DAT_005420a0[4];
extern "C" int DAT_00542090[8];
union U_45b4c0 { int vt; char b[272]; };
extern "C" int igViewerParameters_GetVTable(void);
extern "C" void FUN_0045b590(void);
extern "C" char igModel_GetPublishedMetaObject[];
extern "C" char igModel_Register[];
extern "C" char g_igViewerParameters_callbackList[];
extern "C" char igViewerParameters_className[];
extern "C" char g_igViewerParameters_metaObject[];
extern "C" void igViewerParameters_Register(void);
extern "C" void thunk_igViewerParameters_GetMetaObject(void);
struct Fld { char p0[52]; char f52; char p53[3]; int f56; };
extern "C" int FUN_0018e2f0(...);
extern "C" int FUN_0018e470(...);
extern "C" int FUN_0019f210(void);
extern "C" int FUN_0019f4c0(void);
extern "C" int FUN_0019f670(void);
extern "C" int FUN_001a4d90(void);
extern "C" int FUN_002d3890(...);
extern "C" int DAT_004d1040[4];
extern "C" int DAT_004d10e0[4];
extern "C" int DAT_004d1180[4];
extern "C" int DAT_004d1220[4];
extern "C" void igViewerParameters_InitFields(void);
extern "C" int DAT_0058cb28[4];
extern "C" int FUN_0045b8d0(void);
extern "C" igMetaObject *igViewerGuiFactory_GetMetaObject(void);
struct Obj_45b970 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_00542390[4];
extern "C" int igViewerGuiFactory_GetVTable(void);
extern "C" void **FUN_0045ba90(void **arg0, short arg1);
extern "C" void **FUN_0045bb10(struct Ref **self, short flag);
extern "C" void **FUN_0045bb90(void **arg0, long long arg1);
extern "C" void FUN_0045bc10(void);
extern "C" char g_igViewerGuiFactory_callbackList[];
extern "C" char igViewerGuiFactory_className[];
extern "C" char g_igViewerGuiFactory_metaObject[];
extern "C" void igViewerGuiFactory_Register(void);
extern "C" void thunk_igViewerGuiFactory_GetMetaObject(void);
extern "C" int FUN_00451e40(void);
extern "C" int FUN_00451fc0(void);
extern "C" int FUN_004524f0(void);
extern "C" int DAT_004d12d0[4];
extern "C" int DAT_004d12f0[4];
extern "C" int DAT_004d1310[4];
extern "C" int DAT_004d1330[4];
extern "C" void igViewerGuiFactory_InitFields(void);
extern "C" void FUN_0045be30(int arg0);
extern "C" int DAT_0058cb70[4];
extern "C" void *igViewerDataPumpManager_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U_45bec0 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int DAT_00524950[4];
extern "C" int DAT_00542310[4];
extern "C" int igViewerDataPumpManager_GetVTable(void);
extern "C" void FUN_0045bfa0(void);
extern "C" char g_igViewerDataPumpManager_callbackList[];
extern "C" char igViewerDataPumpManager_className[];
extern "C" char g_igViewerDataPumpManager_metaObject[];
extern "C" int igViewerDataPumpManager_InitFields_0045c040[4];
extern "C" void igViewerDataPumpManager_Register(void);
extern "C" void thunk_igViewerDataPumpManager_GetMetaObject(void);
extern "C" int FUN_001e5150(...);
extern "C" int DAT_004d1358[4];
extern "C" int DAT_004d1360[4];
extern "C" int DAT_004d1368[4];
extern "C" int DAT_004d1370[4];
extern "C" int DAT_0051f500[4];
extern "C" int DAT_0058cb78[4];
extern "C" void FUN_0045c040(void);
extern "C" void FUN_0045c170(int arg0);
extern "C" int DAT_0058cb88[4];
extern "C" void *igPickMode_GetMetaObject(void);
struct Obj_45c200 { int *vt; int w[44]; };
extern "C" int FUN_0019e3c0(...);
extern "C" int FUN_0044e1e0(...);
extern "C" int FUN_0044ee80(...);
extern "C" int DAT_00542720[4];
extern "C" int DAT_00542960[4];
extern "C" int igPickMode_GetVTable(void);
extern "C" void FUN_0045c330(void);
extern "C" char igViewMode_GetPublishedMetaObject[];
extern "C" char g_igPickMode_callbackList[];
extern "C" char igPickMode_className[];
extern "C" char g_igPickMode_metaObject[];
extern "C" void igPickMode_Register(void);
extern "C" void thunk_igPickMode_GetMetaObject(void);
extern "C" int FUN_00188260(void);
extern "C" int FUN_0019dfd0(void);
extern "C" int FUN_0044e430(void);
extern "C" int DAT_004d13a0[4];
extern "C" int DAT_004d13d0[4];
extern "C" int DAT_004d1400[4];
extern "C" int DAT_004d1430[4];
extern "C" void igPickMode_InitFields(void);
extern "C" int DAT_004d1460[4];
extern "C" int DAT_004d1470[4];
extern "C" int DAT_0051f630[4];
extern "C" int DAT_0058cbf0[4];
extern "C" int FUN_0045c540(void);
extern "C" void FUN_0045c5a0(int arg0);
struct S_45c5e0 { char p[36]; unsigned f; };
extern "C" int DAT_0058cbf8[4];
extern "C" void *igRotateMode_GetMetaObject(void);
extern "C" int DAT_005427b0[4];
union U_45c630 { int vt; char b[160]; };
extern "C" int igRotateMode_GetVTable(void);
extern "C" void FUN_0045c680(void);
extern "C" char igRotateMode_className[];
extern "C" char g_igRotateMode_metaObject[];
extern "C" void igRotateMode_Register(void);
extern "C" void thunk_igRotateMode_GetMetaObject(void);
extern "C" int DAT_004d1480[4];
extern "C" int DAT_004d14c0[4];
extern "C" int DAT_004d1500[4];
extern "C" int DAT_004d1540[4];
extern "C" int DAT_004d1580[4];
extern "C" void igRotateMode_InitFields(void);
extern "C" void FUN_0045c8e0(int arg0);
struct S_45c920 { char pad[36]; unsigned flags; };
extern "C" int DAT_0058cc80[4];
extern "C" S_45c920 *igFlyMode_GetMetaObject(void);
struct Obj_45c970 { int *vt; char p4[8]; int sub[4]; char pad[108]; int *ref; char pe[20]; };
extern "C" int DAT_00542840[4];
extern "C" int igFlyMode_GetVTable(void);
extern "C" void FUN_0045ca20(void);
extern "C" char g_igFlyMode_callbackList[];
extern "C" char igFlyMode_className[];
extern "C" char g_igFlyMode_metaObject[];
extern "C" void igFlyMode_Register(void);
extern "C" void thunk_igFlyMode_GetMetaObject(void);
struct V2 { int x; int y; };
struct V3 { int x; int y; int z; };
extern "C" int FUN_00145d40(...);
extern "C" int DAT_004d1590[4];
extern "C" int DAT_004d15c0[4];
extern "C" int DAT_004d15f0[4];
extern "C" int DAT_004d1620[4];
extern "C" void igFlyMode_InitFields(void);
extern "C" void FUN_0045cc40(int arg0);
struct G_45cc80 { char pad[36]; int f; };
extern "C" int DAT_0058cce0[4];
extern "C" G_45cc80 *igCameraMode_GetMetaObject(void);
extern "C" int DAT_005428d0[4];
union U_45ccd0 { int vt; int w[21]; char b[84]; };
extern "C" int igCameraMode_GetVTable(void);
extern "C" void FUN_0045cdc0(void);
extern "C" char g_igCameraMode_callbackList[];
extern "C" char igCameraMode_className[];
extern "C" char g_igCameraMode_metaObject[];
extern "C" void igCameraMode_Register(void);
extern "C" void thunk_igCameraMode_GetMetaObject(void);
extern "C" int FUN_001a4560(void);
extern "C" int DAT_004d1660[4];
extern "C" int DAT_004d1668[4];
extern "C" int DAT_004d1670[4];
extern "C" int DAT_004d1678[4];
extern "C" void igCameraMode_InitFields(void);
extern "C" int DAT_0058ccf8[4];
extern "C" int FUN_0045cf10(void);
extern "C" void *igViewMode_GetMetaObject(void);
struct W { int *vt; int f[19]; };
extern "C" int igViewMode_GetVTable(void);
extern "C" void FUN_0045d000(void);
extern "C" char igViewMode_className[];
extern "C" char g_igViewMode_metaObject[];
extern "C" void igViewMode_Register(void);
extern "C" void thunk_igViewMode_GetMetaObject(void);
extern "C" int DAT_004d1680[4];
extern "C" int DAT_004d1688[4];
extern "C" int DAT_004d1690[4];
extern "C" int DAT_004d1698[4];
extern "C" void igViewMode_InitFields(void);
extern "C" int DAT_0058cd08[4];
extern "C" int FUN_0045d100(void);
extern "C" void *igViewManager_GetMetaObject(void);
extern "C" int DAT_00542690[4];
extern "C" int DAT_00542680[8];
union U_45d1a0 { int vt; int w[21]; char b[84]; };
extern "C" int igViewManager_GetVTable(void);
extern "C" void FUN_0045d2f0(void);
extern "C" char igEventReceiver_GetPublishedMetaObject[];
extern "C" char igEventReceiver_Register[];
extern "C" char g_igViewManager_callbackList[];
extern "C" char igViewManager_className[];
extern "C" char g_igViewManager_metaObject[];
extern "C" void igViewManager_Register(void);
extern "C" void thunk_igViewManager_GetMetaObject(void);
extern "C" int DAT_004d16b0[4];
extern "C" int DAT_004d16c0[4];
extern "C" int DAT_004d16d0[4];
extern "C" int DAT_004d16e0[4];
extern "C" void igViewManager_InitFields(void);
extern "C" int DAT_0058cd30[4];
extern "C" int FUN_0045d470(void);
extern "C" void *igViewModel_GetMetaObject(void);
extern "C" int DAT_00540e30[4];
extern "C" int DAT_00542040[4];
union U_45d510 { int vt; char b[176]; };
extern "C" int igViewModel_GetVTable(void);
extern "C" void FUN_0045d5c0(void);
extern "C" char igViewModel_className[];
extern "C" char g_igViewModel_metaObject[];
extern "C" void igViewModel_Register(void);
extern "C" void thunk_igViewModel_GetMetaObject(void);
extern "C" int DAT_004d16f0[4];
extern "C" int DAT_004d1730[4];
extern "C" int DAT_004d1770[4];
extern "C" int DAT_004d17b0[4];
extern "C" void igViewModel_InitFields(void);
extern "C" int DAT_0058cda0[4];
extern "C" int FUN_0045d830(void);
extern "C" void *igNormalsRenderer_GetMetaObject(void);
struct Obj_45d8d0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int FUN_00136e10(...);
extern "C" int FUN_0013bfe0(...);
extern "C" int FUN_00142d10(...);
extern "C" int FUN_0019ab10(...);
extern "C" int DAT_005422a0[4];
extern "C" int igNormalsRenderer_GetVTable(void);
extern "C" void FUN_0045d9f0(void);
extern "C" char g_igNormalsRenderer_callbackList[];
extern "C" char igNormalsRenderer_className[];
extern "C" char g_igNormalsRenderer_metaObject[];
extern "C" void igNormalsRenderer_Register(void);
extern "C" void thunk_igNormalsRenderer_GetMetaObject(void);
extern "C" int FUN_001356f0(void);
extern "C" int FUN_00138f20(void);
extern "C" int FUN_0013a4d0(...);
extern "C" int FUN_0013af00(void);
extern "C" int DAT_004d1810[4];
extern "C" int DAT_004d1840[4];
extern "C" int DAT_004d1870[4];
extern "C" int DAT_004d18a0[4];
extern "C" void igNormalsRenderer_InitFields(void);
extern "C" void FUN_0045dbe0(int arg0);
struct SigLogoRenderer_GetMetaObject { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
extern "C" int DAT_0058cdf0[4];
extern "C" SigLogoRenderer_GetMetaObject *igLogoRenderer_GetMetaObject(void);
struct Obj_45dc70 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int FUN_001353b0(...);
extern "C" int DAT_00542230[4];
extern "C" int igLogoRenderer_GetVTable(void);
extern "C" void FUN_0045dd20(void);
extern "C" char g_igLogoRenderer_callbackList[];
extern "C" char igLogoRenderer_className[];
extern "C" char g_igLogoRenderer_metaObject[];
extern "C" void igLogoRenderer_Register(void);
extern "C" void thunk_igLogoRenderer_GetMetaObject(void);
extern "C" int FUN_00137850(void);
extern "C" int DAT_004d18e0[4];
extern "C" int DAT_004d18f0[4];
extern "C" int DAT_004d1900[4];
extern "C" int DAT_004d1910[4];
extern "C" void igLogoRenderer_InitFields(void);
extern "C" int DAT_0058ce18[4];
extern "C" int FUN_0045de90(void);
extern "C" igMetaObject *igBoundingBoxRenderer_GetMetaObject(void);
struct Obj_45df30 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_00542a70[4];
extern "C" int igBoundingBoxRenderer_GetVTable(void);
extern "C" void FUN_0045e050(void);
extern "C" char g_igBoundingBoxRenderer_callbackList[];
extern "C" char igBoundingBoxRenderer_className[];
extern "C" char g_igBoundingBoxRenderer_metaObject[];
extern "C" void igBoundingBoxRenderer_Register(void);
extern "C" void thunk_igBoundingBoxRenderer_GetMetaObject(void);
extern "C" int DAT_004d1940[4];
extern "C" int DAT_004d1960[4];
extern "C" int DAT_004d1980[4];
extern "C" int DAT_004d19a0[4];
extern "C" void igBoundingBoxRenderer_InitFields(void);
extern "C" void FUN_0045e230(int arg0);
extern "C" int DAT_0058ce60[4];
extern "C" void *igActorManager_GetMetaObject(void);
struct Obj_45e2c0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int FUN_00135430(...);
extern "C" int FUN_001958f0(...);
extern "C" int FUN_0019ab90(...);
extern "C" int FUN_001a7a00(...);
extern "C" int FUN_001aa310(...);
extern "C" int FUN_004584f0(...);
extern "C" int DAT_005429f0[4];
extern "C" int igActorManager_GetVTable(void);
extern "C" O *FUN_0045e420(O *arg0, short arg1);
extern "C" void FUN_0045e4a0(void);
extern "C" char g_igActorManager_callbackList[];
extern "C" char igActorManager_className[];
extern "C" char g_igActorManager_metaObject[];
extern "C" void igActorManager_Register(void);
extern "C" void thunk_igActorManager_GetMetaObject(void);
extern "C" int FUN_00130440(...);
extern "C" int FUN_0019cbe0(...);
extern "C" int FUN_001a5fe0(...);
extern "C" int FUN_001aa5c0(...);
extern "C" int FUN_002c9170(...);
extern "C" int DAT_004d19f0[4];
extern "C" int DAT_004d1a20[4];
extern "C" int DAT_004d1a50[4];
extern "C" int DAT_004d1a80[4];
extern "C" void igActorManager_InitFields(void);
extern "C" int DAT_0058ceb8[4];
extern "C" int FUN_0045e6f0(void);
extern "C" void *igActorManagerParams_GetMetaObject(void);
extern "C" int DAT_00541fe0[4];
union U_45e790 { int vt; char b[16]; };
extern "C" int igActorManagerParams_GetVTable(void);
extern "C" void FUN_0045e830(void);
extern "C" char igActorManagerParams_className[];
extern "C" char g_igActorManagerParams_metaObject[];
extern "C" void igActorManagerParams_Register(void);
extern "C" void thunk_igActorManagerParams_GetMetaObject(void);
extern "C" int DAT_004d1aa8[4];
extern "C" int DAT_004d1ab0[4];
extern "C" int DAT_004d1ab8[4];
extern "C" int DAT_004d1ac0[4];
extern "C" void igActorManagerParams_InitFields(void);
extern "C" int Gap__Viewer__igActorManagerParams__vfunc_22(void);
extern "C" int Gap__Viewer__igViewModel__vfunc_22(void);
extern "C" int Gap__Viewer__igViewerParameters__vfunc_22(void);
extern "C" int Gap__Viewer__igViewerLoadingFileMessage__vfunc_22(void);
extern "C" int Gap__Viewer__igViewerModeChangeMessage__vfunc_22(void);
extern "C" int Gap__Viewer__igStatisticsItemList__vfunc_22(void);
extern "C" int Gap__Viewer__igStatisticsItemList__vfunc_24(void);

int FUN_004586a0(void) {
    if (DAT_0058c680[0] == 0) {
        DAT_0058c680[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c680[0];
}

void *igViewerStatisticsManager_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058c680[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_004588e0();
    }
    return ((G *)DAT_0058c680[0]);
}

int igViewerStatisticsManager_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005425b0[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_005425b0[0];
    FUN_0014e420(&obj.w10, -1);
    FUN_0013a880(&obj.w9, -1);
    FUN_001489a0(&obj.w7, -1);
    FUN_0025a2b0(&obj.w6, -1);
    FUN_0025a2b0(&obj.w5, -1);
    FUN_004583f0(&obj.w4, -1);
    FUN_00130140(&obj.w3, -1);
    FUN_00458860((ObjectRefWord *)&obj.w2, -1);
    return t;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_00458860(ObjectRefWord *self,int delete_storage) {
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

void FUN_004588e0(void)
{
    igMetaObject_RunStaticInit(igViewerStatisticsManager_Register);
}

void igViewerStatisticsManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerStatisticsManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igViewerStatisticsManager_GetMetaObject,
        igViewerStatisticsManager_className,
        0x48, /* instance size */
        igViewerStatisticsManager_GetVTable,
        &igViewerStatisticsManager_InitFields,
        0, /* extra callback item */
        g_igViewerStatisticsManager_callbackList /* callback list */
    );
}

void thunk_igViewerStatisticsManager_GetMetaObject(void) {
    igViewerStatisticsManager_GetMetaObject();
}

void igViewerStatisticsManager_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s1;

    temp_s1 = (void *)DAT_0058c680[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d08c0[0], 0xF);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00458ae0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0014a040();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0045b8d0();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00452340();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00452340();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_002b9540();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_002c8e50();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_002c8b30();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004d0900[0], &DAT_004d0940[0], &DAT_004d0980[0], temp_s0);
}

int FUN_00458ae0(void) {
    if (DAT_0058c700[0] == 0) {
        DAT_0058c700[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c700[0];
}

void *igStatisticsItemList_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058c700[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00458bc0();
    }
    return ((G *)DAT_0058c700[0]);
}

int igStatisticsItemList_GetVTable(void) {
    struct Obj_458b80 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005421c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
}

void FUN_00458bc0(void)
{
    igMetaObject_RunStaticInit(igStatisticsItemList_Register);
}

void igStatisticsItemList_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStatisticsItemList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igStatisticsItemList_GetMetaObject,
        igStatisticsItemList_className,
        0x14, /* instance size */
        igStatisticsItemList_GetVTable,
        0,
        0, /* extra callback item */
        g_igStatisticsItemList_callbackList /* callback list */
    );
}

void thunk_igStatisticsItemList_GetMetaObject(void) {
    igStatisticsItemList_GetMetaObject();
}

int FUN_00458c50(void) {
    if (DAT_0058c708[0] == 0) {
        DAT_0058c708[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c708[0];
}

void *igStatisticsItem_GetMetaObject(void) {
    unsigned char b;
    if (((void *)DAT_0058c708[0]) != 0) {
        b = (*(int *)((char *)(((void *)DAT_0058c708[0])) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00458ec0();
done:
    return ((void *)DAT_0058c708[0]);
}

int igStatisticsItem_GetVTable(void) {
    struct Obj_458cf0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542620[0];
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_00542620[0];
    FUN_00458e40((ObjectRefWord *)&obj.w11, -1);
    FUN_00458dc0((void **)&obj.w10, -1);
    FUN_003cafa0(&obj.w9, -1);
    StringRef_Destruct_00130720(&obj.w7, -1);
    StringRef_Destruct_00130720(&obj.w6, -1);
    return t;
}

void **FUN_00458dc0(void **arg0, short arg1) {
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

ObjectRefWord *FUN_00458e40(ObjectRefWord *self,int delete_storage) {
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

void FUN_00458ec0(void)
{
    igMetaObject_RunStaticInit(igStatisticsItem_Register);
}

void igStatisticsItem_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStatisticsItem_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igStatisticsItem_GetMetaObject,
        igStatisticsItem_className,
        0x3C, /* instance size */
        igStatisticsItem_GetVTable,
        &igStatisticsItem_InitFields,
        0, /* extra callback item */
        g_igStatisticsItem_callbackList /* callback list */
    );
}

void thunk_igStatisticsItem_GetMetaObject(void) {
    igStatisticsItem_GetMetaObject();
}

void igStatisticsItem_InitFields(void) {
    igEnumMetaField *temp_v0;
    igObjectRefMetaField *temp_s2;
    igObjectRefMetaField *temp_s2_2;
    igObjectRefMetaField *temp_s2_3;
    igObjectRefMetaField *temp_s2_4;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)DAT_0058c708[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d09f0[0], 0xC);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1), -1.0f);
    temp_s2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    temp_s2->_metaObject = FUN_0044ff40();
    temp_s2_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    temp_s2_2->_metaObject = FUN_004516e0();
    temp_s2_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    temp_s2_3->_metaObject = FUN_0044bce0();
    temp_s2_3->_construct = 1;
    temp_s2_4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    temp_s2_4->_metaObject = FUN_004586a0();
    temp_s2_4->_refCounted = 0;
    temp_v0 = (igEnumMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    FUN_002dc7a0(temp_v0, &DAT_004d0ab0[0]);
    temp_v0->_getMetaEnumFunction = (int)(&FUN_00149b60);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB), -1);
    igMetaObject_NameFields(temp_s1, &DAT_004d0a20[0], &DAT_004d0a50[0], &DAT_004d0a80[0], temp_s0);
}

void FUN_004590c0(int arg0) {
    FUN_00459190();
    igMetaObject_CreateInstance(*(int *)0x58C770, arg0);
}

void *igViewerAction_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058c770[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00459190();
    }
    return ((G *)DAT_0058c770[0]);
}

int igViewerAction_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00542460[0];
    off = *(int *)((char *)(((int *)DAT_00586dc8[0])) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_00459190(void)
{
    igMetaObject_RunStaticInit(igViewerAction_Register);
}

void igViewerAction_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerAction_metaObject,
        igAction_Register,
        igAction_GetPublishedMetaObject,
        thunk_igViewerAction_GetMetaObject,
        igViewerAction_className,
        0x18, /* instance size */
        igViewerAction_GetVTable,
        &igViewerAction_InitFields,
        0, /* extra callback item */
        g_igViewerAction_callbackList /* callback list */
    );
}

void thunk_igViewerAction_GetMetaObject(void) {
    igViewerAction_GetMetaObject();
}

void igViewerAction_InitFields(void) {
    void *f2;
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c770[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0ac0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00459380();
    *(char *)((char *)(temp_s1) + 60) = 0;
    f2 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(short *)((char *)f2 + 20) = 0xC;
    igMetaObject_NameFields(temp_s0, &DAT_004d0ac8[0], &DAT_004d0ad0[0], &DAT_004d0ad8[0], temp_s2);
}

int FUN_004592e0(void) {
    if (DAT_0058c788[0] == 0) {
        DAT_0058c788[0] = igMetaEnum_Create(&DAT_0051eaf0[0], &DAT_004d0ae0[0], &DAT_004d0af0[0], 3);
    }
    return DAT_0058c788[0];
}

void FUN_00459340(int arg0) {
    FUN_00459e40();
    igMetaObject_CreateInstance(*(int *)0x58C790, arg0);
}

int FUN_00459380(void) {
    if (DAT_0058c790[0] == 0) {
        DAT_0058c790[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c790[0];
}

void *igViewerSceneInfoManager_GetMetaObject(void) {
    bool ok;
    if (DAT_0058c790[0] == 0) goto make;
    ok = !!(((MetaObjectFlags *)DAT_0058c790[0])->f & 4);
    if (ok != false) goto done;
make:
    FUN_00459e40();
done:;
    return (void *)DAT_0058c790[0];
}

int igViewerSceneInfoManager_GetVTable(void) {
    union U u;
    int r;
    char *p352;
    char *p344;
    char *p340;
    char *p316;
    char *p312;
    char *p308;
    char *p304;
    char *p300;
    char *p296;
    FUN_00458630(u.b);
    u.vt = (int)&DAT_005424c0[0];
    FUN_00459e30((int *)&u.b[16]);
    FUN_00459e20((int *)&u.b[20]);
    FUN_00459e10((int *)&u.b[24]);
    FUN_00459e00((int *)&u.b[28]);
    FUN_00459df0((int *)&u.b[32]);
    FUN_00459de0((int *)&u.b[36]);
    FUN_00459dd0((int *)&u.b[44]);
    FUN_00458620(&u.b[48]);
    FUN_00458610(&u.b[52]);
    FUN_00458600(&u.b[56]);
    FUN_00458600(&u.b[60]);
    FUN_00458610(&u.b[64]);
    FUN_00458600(&u.b[68]);
    FUN_00458610(&u.b[72]);
    FUN_00458610(&u.b[76]);
    FUN_00458610(&u.b[80]);
    FUN_00458610(&u.b[84]);
    FUN_00458610(&u.b[88]);
    FUN_00458600(&u.b[92]);
    FUN_00458610(&u.b[96]);
    FUN_00458610(&u.b[100]);
    FUN_00458610(&u.b[104]);
    FUN_00458610(&u.b[108]);
    FUN_00458610(&u.b[112]);
    FUN_004585f0(&u.b[116]);
    FUN_004585f0(&u.b[120]);
    FUN_004585f0(&u.b[124]);
    FUN_004585f0(&u.b[128]);
    FUN_00459dc0((int *)&u.b[132]);
    p296 = &u.b[136];
    FUN_00459db0((int *)p296);
    p300 = &u.b[140];
    FUN_00459da0((int *)p300);
    p304 = &u.b[144];
    FUN_00459d90((int *)p304);
    p308 = &u.b[148];
    FUN_002c3d50(p308);
    p312 = &u.b[152];
    FUN_00459d80((int *)p312);
    p316 = &u.b[156];
    FUN_002c3d50(p316);
    p340 = &u.b[180];
    FUN_00459d70((int *)p340);
    p344 = &u.b[184];
    FUN_00459d60((int *)p344);
    p352 = &u.b[192];
    FUN_00458600(p352);
    r = *(int *)&u.b[*(int *)((char *)(((void *)DAT_00586dc8[0])) + 916)];
    *(int **)u.b = &DAT_005424c0[0];
    FUN_003cafa0(p352, -1);
    FUN_00459ce0((void **)p344, -1);
    FUN_00131aa0(p340, -1);
    FUN_0014aa70(p316, -1);
    FUN_00458470(p312, -1);
    FUN_0014aa70(p308, -1);
    FUN_0044c1c0(p304, -1);
    FUN_00459c60((ObjectRefWord *)p300, -1);
    FUN_00459be0((void **)p296, -1);
    FUN_00459b60((ObjectRefWord *)&u.b[132], -1);
    FUN_00458570(&u.b[128], -1);
    FUN_00458570(&u.b[124], -1);
    FUN_00458570(&u.b[120], -1);
    FUN_00458570(&u.b[116], -1);
    FUN_0025a2b0(&u.b[112], -1);
    FUN_0025a2b0(&u.b[108], -1);
    FUN_0025a2b0(&u.b[104], -1);
    FUN_0025a2b0(&u.b[100], -1);
    FUN_0025a2b0(&u.b[96], -1);
    FUN_003cafa0(&u.b[92], -1);
    FUN_0025a2b0(&u.b[88], -1);
    FUN_0025a2b0(&u.b[84], -1);
    FUN_0025a2b0(&u.b[80], -1);
    FUN_0025a2b0(&u.b[76], -1);
    FUN_0025a2b0(&u.b[72], -1);
    FUN_003cafa0(&u.b[68], -1);
    FUN_0025a2b0(&u.b[64], -1);
    FUN_003cafa0(&u.b[60], -1);
    FUN_003cafa0(&u.b[56], -1);
    FUN_0025a2b0(&u.b[52], -1);
    FUN_004583f0(&u.b[48], -1);
    FUN_00459ae0((O *)&u.b[44], -1);
    FUN_00459a60((void **)&u.b[36], -1);
    FUN_004599e0((struct Ref **)&u.b[32], -1);
    FUN_00459960((void **)&u.b[28], -1);
    FUN_004598e0((void **)&u.b[24], -1);
    FUN_00459860((ObjectRefWord *)&u.b[20], -1);
    FUN_004597e0((struct R **)&u.b[16], -1);
    FUN_00231030(u.b, 0);
    return r;
}

struct R **FUN_004597e0(struct R **arg0, short arg1) {
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

ObjectRefWord *FUN_00459860(ObjectRefWord *self,int delete_storage) {
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

void **FUN_004598e0(void **arg0, int arg1) {
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

void **FUN_00459960(void **arg0, short arg1) {
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

void **FUN_004599e0(struct Ref **self, short flag) {
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

void **FUN_00459a60(void **arg0, long long arg1) {
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

O *FUN_00459ae0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_00459b60(ObjectRefWord *self,int delete_storage) {
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

void **FUN_00459be0(void **arg0, short arg1) {
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

ObjectRefWord *FUN_00459c60(ObjectRefWord *self,int delete_storage) {
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

void **FUN_00459ce0(void **arg0, short arg1) {
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

int *FUN_00459d60(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459d70(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459d80(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459d90(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459da0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459db0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459dc0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459dd0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459de0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459df0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e00(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e10(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e20(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e30(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_00459e40(void)
{
    igMetaObject_RunStaticInit(igViewerSceneInfoManager_Register);
}

void igViewerSceneInfoManager_Register(void) {
    ViewerLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerSceneInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        thunk_igViewerSceneInfoManager_GetMetaObject,
        igViewerSceneInfoManager_className,
        0xC8, /* instance size */
        igViewerSceneInfoManager_GetVTable,
        FUN_00459ee0,                               /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igViewerSceneInfoManager_callbackList /* callback list */
    );
}

void thunk_igViewerSceneInfoManager_GetMetaObject(void) {
    igViewerSceneInfoManager_GetMetaObject();
}

void FUN_00459ee0(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_10;
    void *temp_s0_11;
    void *temp_s0_12;
    void *temp_s0_13;
    void *temp_s0_14;
    void *temp_s0_15;
    void *temp_s0_16;
    void *temp_s0_17;
    void *temp_s0_18;
    void *temp_s0_19;
    void *temp_s0_20;
    void *temp_s0_21;
    void *temp_s0_22;
    void *temp_s0_23;
    void *temp_s0_24;
    void *temp_s0_25;
    void *temp_s0_26;
    void *temp_s0_27;
    void *temp_s0_28;
    void *temp_s0_29;
    void *temp_s0_2;
    void *temp_s0_30;
    void *temp_s0_31;
    void *temp_s0_32;
    void *temp_s0_33;
    void *temp_s0_34;
    void *temp_s0_35;
    void *temp_s0_36;
    void *temp_s0_37;
    void *temp_s0_38;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s0_7;
    void *temp_s0_8;
    void *temp_s0_9;
    void *temp_s1;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_s1 = (void *)(DAT_0058c790[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d0b50[0], 0x2B);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_0051ee50[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_0051ee60[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_0058c798[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = FUN_0045a8c0();
    *(char *)((char *)(temp_s0) + 52) = 1;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    *(int *)((char *)(temp_s0_2) + 56) = FUN_0045b420();
    *(char *)((char *)(temp_s0_2) + 52) = 1;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    *(int *)((char *)(temp_s0_3) + 56) = FUN_0045aaf0();
    *(char *)((char *)(temp_s0_3) + 52) = 1;
    temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    *(int *)((char *)(temp_s0_4) + 56) = FUN_0045de90();
    *(char *)((char *)(temp_s0_4) + 52) = 1;
    temp_s0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4));
    *(int *)((char *)(temp_s0_5) + 56) = FUN_0045d830();
    *(char *)((char *)(temp_s0_5) + 52) = 1;
    temp_s0_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5));
    *(int *)((char *)(temp_s0_6) + 56) = FUN_00233a40();
    *(char *)((char *)(temp_s0_6) + 52) = 1;
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6), -1);
    temp_s0_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7));
    *(int *)((char *)(temp_s0_7) + 56) = FUN_0044ded0();
    *(char *)((char *)(temp_s0_7) + 52) = 1;
    temp_s0_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8));
    *(int *)((char *)(temp_s0_8) + 56) = FUN_0045b8d0();
    *(char *)((char *)(temp_s0_8) + 52) = 1;
    temp_s0_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9));
    *(int *)((char *)(temp_s0_9) + 56) = FUN_00452340();
    temp_s0_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xA));
    *(int *)((char *)(temp_s0_10) + 56) = FUN_0044ff40();
    temp_s0_11 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xB));
    *(int *)((char *)(temp_s0_11) + 56) = FUN_0044ff40();
    temp_s0_12 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xC));
    *(int *)((char *)(temp_s0_12) + 56) = FUN_00452340();
    temp_s0_13 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xD));
    *(int *)((char *)(temp_s0_13) + 56) = FUN_0044ff40();
    temp_s0_14 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xE));
    *(int *)((char *)(temp_s0_14) + 56) = FUN_00452340();
    temp_s0_15 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xF));
    *(int *)((char *)(temp_s0_15) + 56) = FUN_00452340();
    temp_s0_16 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x10));
    *(int *)((char *)(temp_s0_16) + 56) = FUN_00452340();
    temp_s0_17 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x11));
    *(int *)((char *)(temp_s0_17) + 56) = FUN_00452340();
    temp_s0_18 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x12));
    *(int *)((char *)(temp_s0_18) + 56) = FUN_00452340();
    temp_s0_19 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x13));
    *(int *)((char *)(temp_s0_19) + 56) = FUN_0044ff40();
    temp_s0_20 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x14));
    *(int *)((char *)(temp_s0_20) + 56) = FUN_00452340();
    temp_s0_21 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x15));
    *(int *)((char *)(temp_s0_21) + 56) = FUN_00452340();
    temp_s0_22 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x16));
    *(int *)((char *)(temp_s0_22) + 56) = FUN_00452340();
    temp_s0_23 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x17));
    *(int *)((char *)(temp_s0_23) + 56) = FUN_00452340();
    temp_s0_24 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x18));
    *(int *)((char *)(temp_s0_24) + 56) = FUN_00452340();
    temp_s0_25 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x19));
    *(int *)((char *)(temp_s0_25) + 56) = FUN_00458c50();
    temp_s0_26 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1A));
    *(int *)((char *)(temp_s0_26) + 56) = FUN_00458c50();
    temp_s0_27 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1B));
    *(int *)((char *)(temp_s0_27) + 56) = FUN_00458c50();
    temp_s0_28 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1C));
    *(int *)((char *)(temp_s0_28) + 56) = FUN_00458c50();
    temp_s0_29 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1D));
    *(int *)((char *)(temp_s0_29) + 56) = FUN_0044d840();
    *(char *)((char *)(temp_s0_29) + 52) = 1;
    temp_s0_30 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1E));
    *(int *)((char *)(temp_s0_30) + 56) = FUN_0045d100();
    *(char *)((char *)(temp_s0_30) + 52) = 1;
    temp_s0_31 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x1F));
    *(int *)((char *)(temp_s0_31) + 56) = FUN_004586a0();
    *(char *)((char *)(temp_s0_31) + 52) = 1;
    temp_s0_32 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x20));
    *(int *)((char *)(temp_s0_32) + 56) = FUN_0044fdd0();
    *(char *)((char *)(temp_s0_32) + 52) = 1;
    temp_s0_33 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x21));
    *(int *)((char *)(temp_s0_33) + 56) = igObjectList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_33) + 52) = 1;
    temp_s0_34 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x22));
    *(int *)((char *)(temp_s0_34) + 56) = FUN_0044cdf0();
    *(char *)((char *)(temp_s0_34) + 52) = 1;
    temp_s0_35 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x23));
    *(int *)((char *)(temp_s0_35) + 56) = igObjectList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_35) + 52) = 1;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x26));
    FUN_002dc7a0(temp_v0_3, &DAT_004d0e10[0]);
    *(int *)((char *)(temp_v0_3) + 52) = (int)(&FUN_004592e0);
    temp_s0_36 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x27));
    *(int *)((char *)(temp_s0_36) + 56) = FUN_0013a360();
    *(char *)((char *)(temp_s0_36) + 52) = 1;
    temp_s0_37 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x28));
    *(int *)((char *)(temp_s0_37) + 56) = FUN_0045a450();
    *(char *)((char *)(temp_s0_37) + 52) = 1;
    temp_s0_38 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x2A));
    *(int *)((char *)(temp_s0_38) + 56) = FUN_0044ff40();
    igMetaObject_NameFields(temp_s1, &DAT_004d0c00[0], &DAT_004d0cb0[0], &DAT_004d0d60[0], temp_s2);
}

int FUN_0045a450(void) {
    if (DAT_0058c8f8[0] == 0) {
        DAT_0058c8f8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c8f8[0];
}

S *igViewerModeChangeMessage_GetMetaObject(void) {
    S *g = g_igViewerModeChangeMessage_metaObject[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0045a580();
done:
    return g_igViewerModeChangeMessage_metaObject[0];
}

int igViewerModeChangeMessage_GetVTable(void) {
    Obj_45a450 o;
    int r;
    char *p;
    int *hdr;
    int c;

    igObject_InitHeader(&o);
    o.vt = &DAT_00542160[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    o.vt = &DAT_00542160[0];
    if (&o.s != 0) {
        p = (char *)o.s;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
    }
    return r;
}

void FUN_0045a580(void)
{
    igMetaObject_RunStaticInit(igViewerModeChangeMessage_Register);
}

void igViewerModeChangeMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerModeChangeMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewerModeChangeMessage_GetMetaObject,
        igViewerModeChangeMessage_className,
        0x10, /* instance size */
        igViewerModeChangeMessage_GetVTable,
        &igViewerModeChangeMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewerModeChangeMessage_GetMetaObject(void) {
    igViewerModeChangeMessage_GetMetaObject();
}

void igViewerModeChangeMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c8f8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e18[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004d0e20[0], &DAT_004d0e28[0], &DAT_004d0e30[0], temp_s1);
}

void FUN_0045a680(int arg0) {
    FUN_0045a7a0();
    igMetaObject_CreateInstance(*(int *)0x58C910, arg0);
}

struct G_45a680 *igViewerLoadingFileMessage_GetMetaObject(void) {
    struct G_45a680 *g = g_igViewerLoadingFileMessage_metaObject[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0045a7a0();
    return g_igViewerLoadingFileMessage_metaObject[0];
}

int igViewerLoadingFileMessage_GetVTable(void) {
    struct Obj_45a680 obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542100[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_00542100[0];
    if (&obj.m != 0) {
        o = obj.m;
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

void FUN_0045a7a0(void)
{
    igMetaObject_RunStaticInit(igViewerLoadingFileMessage_Register);
}

void igViewerLoadingFileMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerLoadingFileMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewerLoadingFileMessage_GetMetaObject,
        igViewerLoadingFileMessage_className,
        0x10, /* instance size */
        igViewerLoadingFileMessage_GetVTable,
        &igViewerLoadingFileMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewerLoadingFileMessage_GetMetaObject(void) {
    igViewerLoadingFileMessage_GetMetaObject();
}

void igViewerLoadingFileMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c910[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e38[0], 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), &DAT_0051eef0[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004d0e40[0], &DAT_004d0e48[0], &DAT_004d0e50[0], temp_s1);
}

int FUN_0045a8c0(void) {
    if (DAT_0058c928[0] == 0) {
        DAT_0058c928[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c928[0];
}

void *igViewerSceneInfoManagerController_GetMetaObject(void) {
    struct G *g = g_igViewerSceneInfoManagerController_metaObject[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045a9a0();
    }
    return g_igViewerSceneInfoManagerController_metaObject[0];
}

int igViewerSceneInfoManagerController_GetVTable(void) {
    struct Obj_45a8c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542540[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
}

void FUN_0045a9a0(void)
{
    igMetaObject_RunStaticInit(igViewerSceneInfoManagerController_Register);
}

void igViewerSceneInfoManagerController_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerSceneInfoManagerController_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igViewerSceneInfoManagerController_GetMetaObject,
        igViewerSceneInfoManagerController_className,
        0x14, /* instance size */
        igViewerSceneInfoManagerController_GetVTable,
        &igViewerSceneInfoManagerController_InitFields,
        0, /* extra callback item */
        g_igViewerSceneInfoManagerController_callbackList /* callback list */
    );
}

void thunk_igViewerSceneInfoManagerController_GetMetaObject(void) {
    igViewerSceneInfoManagerController_GetMetaObject();
}

void igViewerSceneInfoManagerController_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c928[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e68[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00459380();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0045aaf0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004d0e70[0], &DAT_004d0e78[0], &DAT_004d0e80[0], temp_s2);
}

int FUN_0045aaf0(void) {
    if (DAT_0058c940[0] == 0) {
        DAT_0058c940[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c940[0];
}

igMetaObject *igViewerRenderer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igViewerRenderer_metaObject[0] != 0) {
        ready = (g_igViewerRenderer_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0045b0d0();
done:
    return g_igViewerRenderer_metaObject[0];
}

int igViewerRenderer_GetVTable(void) {
    union U_45aaf0 u;
    int r;
    FUN_0045b090(&u.b[0]);
    u.pv = &DAT_005423f0[0];
    FUN_00459e20((int *)&u.b[12]);
    FUN_00197300(&u.b[16]);
    FUN_0045b080((int *)&u.b[20]);
    FUN_0045b070((int *)&u.b[24]);
    FUN_0045b060((int *)&u.b[28]);
    FUN_0045b050((int *)&u.b[32]);
    FUN_0019ac30(&u.b[36]);
    FUN_0045b040((int *)&u.b[40]);
    FUN_0045b030((int *)&u.b[44]);
    FUN_0045b020((int *)&u.b[48]);
    FUN_0045b010((int *)&u.b[52]);
    FUN_0045b000((int *)&u.b[56]);
    FUN_0019c370(&u.b[60]);
    FUN_0045aff0((int *)&u.b[64]);
    FUN_0045afe0((int *)&u.b[72]);
    FUN_00197350(&u.b[76]);
    FUN_0045afe0((int *)&u.b[80]);
    FUN_00197350(&u.b[84]);
    FUN_0045afd0((int *)&u.b[88]);
    r = *(int *)&u.b[*(int *)((char *)(((void *)DAT_00586dc8[0])) + 916)];
    u.pv = &DAT_005423f0[0];
    FUN_0045af50((void **)&u.b[88], -1);
    FUN_00197160(&u.b[84], -1);
    FUN_001d9870(&u.b[80], -1);
    FUN_00197160(&u.b[76], -1);
    FUN_001d9870(&u.b[72], -1);
    FUN_0019d9e0(&u.b[64], -1);
    FUN_0019c1a0(&u.b[60], -1);
    FUN_00239280(&u.b[56], -1);
    FUN_001a7580(&u.b[52], -1);
    FUN_0045aed0((void **)&u.b[48], -1);
    FUN_001d97f0(&u.b[44], -1);
    FUN_00229460(&u.b[40], -1);
    FUN_00136370(&u.b[36], -1);
    FUN_00239200(&u.b[32], -1);
    FUN_0045ae50((struct R **)&u.b[28], -1);
    FUN_0045add0((ObjectRefWord *)&u.b[24], -1);
    FUN_001d3090(&u.b[20], -1);
    FUN_00197060(&u.b[16], -1);
    FUN_00459860((ObjectRefWord *)&u.b[12], -1);
    FUN_00230f70(&u.b[0], 0);
    return r;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_0045add0(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_0045ae50(struct R **arg0, short arg1) {
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

void **FUN_0045aed0(void **arg0, long long arg1) {
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

void **FUN_0045af50(void **arg0, int arg1) {
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

int *FUN_0045afd0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045afe0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045aff0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b000(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b010(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b020(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b030(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b040(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b050(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b060(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b070(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b080(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_0045b090(void *arg0) {
    igObject_InitHeader();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_0052d060[0]);
    *(int *)((char *)(arg0) + 8) = 0;
    return arg0;
}

void FUN_0045b0d0(void)
{
    igMetaObject_RunStaticInit(igViewerRenderer_Register);
}

void igViewerRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igViewerRenderer_GetMetaObject,
        igViewerRenderer_className,
        0x5C, /* instance size */
        igViewerRenderer_GetVTable,
        &igViewerRenderer_InitFields,
        0, /* extra callback item */
        g_igViewerRenderer_callbackList /* callback list */
    );
}

void thunk_igViewerRenderer_GetMetaObject(void) {
    igViewerRenderer_GetMetaObject();
}

void igViewerRenderer_InitFields(void) {
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_13;
    void *temp_s2_14;
    void *temp_s2_15;
    void *temp_s2_16;
    void *temp_s2_17;
    void *temp_s2_18;
    void *temp_s2_19;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c940[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0ee0[0], 0x14);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0045b420();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_001386d0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0013b2b0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00133950();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00134940();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00135e60();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00136750();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_001361f0();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_001a5d70();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_0019c6a0();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = FUN_00196190();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_0019dbb0();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    temp_s2_13 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_001365e0();
    ((igRefMetaField *)temp_s2_13)->_construct = 1;
    temp_s2_14 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_00136040();
    ((igRefMetaField *)temp_s2_14)->_construct = 1;
    temp_s2_15 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF));
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = FUN_001a38e0();
    ((igRefMetaField *)temp_s2_15)->_construct = 1;
    temp_s2_16 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10));
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = FUN_00137fb0();
    temp_s2_17 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = FUN_001a38e0();
    temp_s2_18 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = FUN_00137fb0();
    temp_s2_19 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x13));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = FUN_0014f770();
    igMetaObject_NameFields(temp_s0, &DAT_004d0f30[0], &DAT_004d0f80[0], &DAT_004d0fd0[0], temp_s1);
}

int FUN_0045b420(void) {
    if (DAT_0058c9e8[0] == 0) {
        DAT_0058c9e8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c9e8[0];
}

SigViewerParameters_GetMetaObject *igViewerParameters_GetMetaObject(void) {
    if (((SigViewerParameters_GetMetaObject *)DAT_0058c9e8[0]) == 0 || !((SigViewerParameters_GetMetaObject *)DAT_0058c9e8[0])->ok()) FUN_0045b590();
    return ((SigViewerParameters_GetMetaObject *)DAT_0058c9e8[0]);
}

int igViewerParameters_GetVTable(void) {
    union U_45b4c0 u;
    int temp_s1;
    int pi = (int)u.b;
    char *p;
    igObject_InitHeader(pi);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_005420a0[0];
    p = &u.b[12];
    *(int *)p = 0;
    igMatrix44f_SetIdentity(&u.b[44]);
    igMatrix44f_SetIdentity(pi + 108);
    *(int *)(pi + 204) = 0;
    *(int *)(pi + 220) = 0;
    *(int *)(pi + 240) = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(((void *)DAT_00586dc8[0])) + 916)];
    u.vt = (int)&DAT_00542090[4];
    FUN_001d6560(&u.b[240], -1);
    FUN_0019b1f0(&u.b[220], -1);
    FUN_00196a50(&u.b[204], -1);
    FUN_00229350(p, -1);
    FUN_0044c110(u.b, 0);
    return temp_s1;
}

void FUN_0045b590(void)
{
    igMetaObject_RunStaticInit(igViewerParameters_Register);
}

void igViewerParameters_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerParameters_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igViewerParameters_GetMetaObject,
        igViewerParameters_className,
        0x108, /* instance size */
        igViewerParameters_GetVTable,
        &igViewerParameters_InitFields,
        0, /* extra callback item */
        g_igViewerParameters_callbackList /* callback list */
    );
}

void thunk_igViewerParameters_GetMetaObject(void) {
    igViewerParameters_GetMetaObject();
}

void igViewerParameters_InitFields(void) {
    struct Fld *temp_s2_4;
    struct Fld *temp_s2_3;
    struct Fld *temp_s2_2;
    struct Fld *temp_s2;
    void *temp_a0_2;
    void *temp_a0;
    int temp_s1;
    void *temp_s0;
    int sp50[3];
    int sp48[2];

    temp_s0 = (void *)DAT_0058c9e8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1040[0], 0x27);
    temp_s2 = (struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1);
    temp_s2->f56 = FUN_0019f210();
    temp_s2->f52 = 1;
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    sp50[0] = 0;
    sp50[1] = 0x3F800000;
    sp50[2] = 0;
    FUN_0018e470(temp_a0, sp50);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 45.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5), 1000.0f);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC), 0);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10), 1);
    temp_s2_2 = (struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x18);
    temp_s2_2->f56 = FUN_001a4d90();
    temp_s2_2->f52 = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x19), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1A), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1D), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1E), 4);
    temp_s2_3 = (struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x1F);
    temp_s2_3->f56 = FUN_0019f4c0();
    temp_s2_3->f52 = 1;
    temp_s2_4 = (struct Fld *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x22);
    temp_s2_4->f56 = FUN_0019f670();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x23), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x24), 2);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x25), 1.0f);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x26));
    sp48[0] = 0;
    sp48[1] = 0;
    FUN_0018e2f0(temp_a0_2, sp48);
    igMetaObject_NameFields(temp_s0, &DAT_004d10e0[0], &DAT_004d1180[0], &DAT_004d1220[0], temp_s1);
}

int FUN_0045b8d0(void) {
    if (DAT_0058cb28[0] == 0) {
        DAT_0058cb28[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058cb28[0];
}

igMetaObject *igViewerGuiFactory_GetMetaObject(void)
{
    igMetaObject *g = ((igMetaObject *)DAT_0058cb28[0]);
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0045bc10();
    return ((igMetaObject *)DAT_0058cb28[0]);
}

int igViewerGuiFactory_GetVTable(void) {
    struct Obj_45b970 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542390[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_00542390[0];
    FUN_0045bb90((void **)&obj.w9, -1);
    FUN_0045bb10((Ref **)&obj.w8, -1);
    FUN_0045bb10((Ref **)&obj.w7, -1);
    FUN_0045bb10((Ref **)&obj.w6, -1);
    FUN_0045ba90((void **)&obj.w5, -1);
    FUN_0045bb10((Ref **)&obj.w4, -1);
    FUN_0045ba90((void **)&obj.w3, -1);
    FUN_0045ba90((void **)&obj.w2, -1);
    return t;
}

void **FUN_0045ba90(void **arg0, short arg1) {
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

void **FUN_0045bb10(struct Ref **self, short flag) {
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

void **FUN_0045bb90(void **arg0, long long arg1) {
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

void FUN_0045bc10(void)
{
    igMetaObject_RunStaticInit(igViewerGuiFactory_Register);
}

void igViewerGuiFactory_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerGuiFactory_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igViewerGuiFactory_GetMetaObject,
        igViewerGuiFactory_className,
        0x28, /* instance size */
        igViewerGuiFactory_GetVTable,
        &igViewerGuiFactory_InitFields,
        0, /* extra callback item */
        g_igViewerGuiFactory_callbackList /* callback list */
    );
}

void thunk_igViewerGuiFactory_GetMetaObject(void) {
    igViewerGuiFactory_GetMetaObject();
}

void igViewerGuiFactory_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058cb28[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d12d0[0], 8);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00451fc0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00451fc0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00451fc0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00451e40();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_004524f0();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d12f0[0], &DAT_004d1310[0], &DAT_004d1330[0], temp_s1);
}

void FUN_0045be30(int arg0) {
    FUN_0045bfa0();
    igMetaObject_CreateInstance(*(int *)0x58CB70, arg0);
}

void *igViewerDataPumpManager_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058cb70[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045bfa0();
    }
    return ((G *)DAT_0058cb70[0]);
}

int igViewerDataPumpManager_GetVTable(void) {
    union U_45bec0 u;
    int temp_s1;
    void **q2;
    S_ref *q4;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_00542310[0]);
    q4 = (S_ref *)&u.p[4];
    *(int *)q4 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(((void *)DAT_00586dc8[0])) + 916)];
    u.w[0] = (int)(&DAT_00542310[0]);
    if (q4 != 0) {
        q4 = *(S_ref **)q4;
        if (q4 != 0) {
            q4->f4 = (int)((int) (q4->f4 - 1));
            if (((unsigned long long) ((long long) q4->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q4);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q2 != 0) {
        temp_v1 = *q2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void FUN_0045bfa0(void)
{
    igMetaObject_RunStaticInit(igViewerDataPumpManager_Register);
}

void igViewerDataPumpManager_Register(void) {
    ViewerLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerDataPumpManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        thunk_igViewerDataPumpManager_GetMetaObject,
        igViewerDataPumpManager_className,
        0x14, /* instance size */
        igViewerDataPumpManager_GetVTable,
        &igViewerDataPumpManager_InitFields_0045c040[0],                              /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igViewerDataPumpManager_callbackList /* callback list */
    );
}

void thunk_igViewerDataPumpManager_GetMetaObject(void) {
    igViewerDataPumpManager_GetMetaObject();
}

void FUN_0045c040(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(((void *)DAT_0058cb70[0]));
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d1358[0], 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_0051ee50[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_0051f500[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_0058cb78[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = FUN_001e5150();
    *(char *)((char *)(temp_s0) + 52) = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004d1360[0], &DAT_004d1368[0], &DAT_004d1370[0], temp_s2);
}

void FUN_0045c170(int arg0) {
    FUN_0045c330();
    igMetaObject_CreateInstance(*(int *)0x58CB88, arg0);
}

void *igPickMode_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058cb88[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045c330();
    }
    return ((G *)DAT_0058cb88[0]);
}

int igPickMode_GetVTable(void) {
    struct Obj_45c200 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542960[0];
    igMatrix44f_SetIdentity(&obj.w[2]);
    obj.vt = &DAT_00542720[0];
    obj.w[18] = 0;
    obj.w[19] = 0;
    obj.w[20] = 0;
    obj.w[21] = 0;
    obj.w[23] = 0;
    obj.w[24] = 0;
    obj.w[27] = 0;
    igMatrix44f_SetIdentity(&obj.w[28]);
    r = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_00542720[0];
    FUN_001d6560(&obj.w[27], -1);
    FUN_0019e3c0(&obj.w[24], -1);
    FUN_0044ee80(&obj.w[23], -1);
    FUN_0044e1e0(&obj.w[21], -1);
    FUN_0044e1e0(&obj.w[20], -1);
    FUN_00459ae0((O *)&obj.w[19], -1);
    FUN_00459860((ObjectRefWord *)&obj.w[18], -1);
    return r;
}

void FUN_0045c330(void)
{
    igMetaObject_RunStaticInit(igPickMode_Register);
}

void igPickMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPickMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igPickMode_GetMetaObject,
        igPickMode_className,
        0xBC, /* instance size */
        igPickMode_GetVTable,
        &igPickMode_InitFields,
        0, /* extra callback item */
        g_igPickMode_callbackList /* callback list */
    );
}

void thunk_igPickMode_GetMetaObject(void) {
    igPickMode_GetMetaObject();
}

void igPickMode_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;
    int temp_s0;
    int sp48[2];
    void *temp_a0;

    temp_s1 = (void *)DAT_0058cb88[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d13a0[0], 0xC);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0045b420();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0044ded0();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0044e430();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0044e430();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0019dfd0();
    ((igObjectRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00188260();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7), 0.0f);
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_0019f670();
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    sp48[0] = 0;
    sp48[1] = 0;
    FUN_0018e2f0(temp_a0, sp48);
    igMetaObject_NameFields(temp_s1, &DAT_004d13d0[0], &DAT_004d1400[0], &DAT_004d1430[0], temp_s0);
}

int FUN_0045c540(void) {
    if (DAT_0058cbf0[0] == 0) {
        DAT_0058cbf0[0] = igMetaEnum_Create(&DAT_0051f630[0], &DAT_004d1460[0], &DAT_004d1470[0], 3);
    }
    return DAT_0058cbf0[0];
}

void FUN_0045c5a0(int arg0) {
    FUN_0045c680();
    igMetaObject_CreateInstance(*(int *)0x58CBF8, arg0);
}

void *igRotateMode_GetMetaObject(void) {
    bool ok;
    if (((S_45c5e0 *)DAT_0058cbf8[0]) == 0) goto make;
    ok = !!(((S_45c5e0 *)DAT_0058cbf8[0])->f & 4);
    if (ok != false) goto done;
make:
    FUN_0045c680();
done:;
    return ((S_45c5e0 *)DAT_0058cbf8[0]);
}

int igRotateMode_GetVTable(void) {
    union U_45c630 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00542960[0];
    igMatrix44f_SetIdentity(&u.b[12]);
    u.vt = (int)&DAT_005427b0[0];
    return *(int *)&u.b[*(int *)((char *)((void *)DAT_00586dc8[0]) + 916)];
}

void FUN_0045c680(void)
{
    igMetaObject_RunStaticInit(igRotateMode_Register);
}

void igRotateMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRotateMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igRotateMode_GetMetaObject,
        igRotateMode_className,
        0x94, /* instance size */
        igRotateMode_GetVTable,
        &igRotateMode_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRotateMode_GetMetaObject(void) {
    igRotateMode_GetMetaObject();
}

void igRotateMode_InitFields(void) {
    int temp_s2;
    int spA[2];
    int spB[2];
    int spC[2];
    int spD[3];
    void *temp_v0;
    void *temp_a0_4;
    void *temp_a0_3;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058cbf8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1480[0], 0x10);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1.0f);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    spA[0] = 0;
    spA[1] = 0;
    FUN_0018e2f0(temp_a0, spA);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    spB[0] = 0;
    spB[1] = 0;
    FUN_0018e2f0(temp_a0_2, spB);
    temp_a0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    spC[0] = 0;
    spC[1] = 0;
    FUN_0018e2f0(temp_a0_3, spC);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    FUN_002dc7a0(temp_v0, &DAT_004d1580[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_0045c540);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9), 1);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xE), 1.0f);
    temp_a0_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xF));
    spD[0] = 0;
    spD[1] = 0;
    spD[2] = 0;
    FUN_0018e470(temp_a0_4, spD);
    igMetaObject_NameFields(temp_s0, &DAT_004d14c0[0], &DAT_004d1500[0], &DAT_004d1540[0], temp_s2);
}

void FUN_0045c8e0(int arg0) {
    FUN_0045ca20();
    igMetaObject_CreateInstance(*(int *)0x58CC80, arg0);
}

S_45c920 *igFlyMode_GetMetaObject(void) {
    S_45c920 *g = ((S_45c920 *)DAT_0058cc80[0]);
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0045ca20();
done:
    return ((S_45c920 *)DAT_0058cc80[0]);
}

int igFlyMode_GetVTable(void) {
    struct Obj_45c970 o;
    int r;
    int *t;
    igObject_InitHeader(&o);
    o.vt = &DAT_00542960[0];
    igMatrix44f_SetIdentity(o.sub);
    o.vt = &DAT_00542840[0];
    o.ref = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    o.vt = &DAT_00542840[0];
    if (&o.ref != 0) {
        t = o.ref;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void FUN_0045ca20(void)
{
    igMetaObject_RunStaticInit(igFlyMode_Register);
}

void igFlyMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFlyMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igFlyMode_GetMetaObject,
        igFlyMode_className,
        0xA0, /* instance size */
        igFlyMode_GetVTable,
        &igFlyMode_InitFields,
        0, /* extra callback item */
        g_igFlyMode_callbackList /* callback list */
    );
}

void thunk_igFlyMode_GetMetaObject(void) {
    igFlyMode_GetMetaObject();
}

void igFlyMode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_a0_7;
    void *temp_a0_6;
    void *temp_a0_5;
    void *temp_a0_4;
    void *temp_a0_3;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;
    struct V3 a;
    struct V3 b;
    struct V2 c;
    struct V3 d;
    struct V2 e;
    struct V2 f;
    struct V2 g;

    temp_s0 = (void *)DAT_0058cc80[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1590[0], 0xB);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    a.x = 0;
    a.y = 0;
    a.z = 0;
    FUN_0018e470(temp_a0, &a);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    b.x = 0;
    b.y = 0;
    b.z = 0;
    FUN_0018e470(temp_a0_2, &b);
    temp_a0_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    c.x = 0;
    c.y = 0;
    FUN_0018e2f0(temp_a0_3, &c);
    temp_a0_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    d.x = 0;
    d.y = 0;
    d.z = 0;
    FUN_0018e470(temp_a0_4, &d);
    temp_a0_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    e.x = 0;
    e.y = 0;
    FUN_0018e2f0(temp_a0_5, &e);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    *(int *)((char *)(temp_s1) + 56) = FUN_00145d40();
    temp_a0_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    f.x = 0;
    f.y = 0;
    FUN_0018e2f0(temp_a0_6, &f);
    temp_a0_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    g.x = 0;
    g.y = 0;
    FUN_0018e2f0(temp_a0_7, &g);
    igMetaObject_NameFields(temp_s0, &DAT_004d15c0[0], &DAT_004d15f0[0], &DAT_004d1620[0], temp_s2);
}

void FUN_0045cc40(int arg0) {
    FUN_0045cdc0();
    igMetaObject_CreateInstance(*(int *)0x58CCE0, arg0);
}

G_45cc80 *igCameraMode_GetMetaObject(void) {
    G_45cc80 *g = ((G_45cc80 *)DAT_0058cce0[0]);
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0045cdc0();
    return ((G_45cc80 *)DAT_0058cce0[0]);
}

int igCameraMode_GetVTable(void) {
    union U_45ccd0 u;
    int temp_s1;
    S_ref *q1;
    S_ref *q2;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00542960[0]);
    igMatrix44f_SetIdentity(&u.w[3]);
    u.w[0] = (int)(&DAT_005428d0[0]);
    q1 = (S_ref *)&u.b[76];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[80];
    *(int *)q2 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(((void *)DAT_00586dc8[0])) + 916)];
    u.w[0] = (int)(&DAT_005428d0[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s1;
}

void FUN_0045cdc0(void)
{
    igMetaObject_RunStaticInit(igCameraMode_Register);
}

void igCameraMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCameraMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        thunk_igCameraMode_GetMetaObject,
        igCameraMode_className,
        0x54, /* instance size */
        igCameraMode_GetVTable,
        &igCameraMode_InitFields,
        0, /* extra callback item */
        g_igCameraMode_callbackList /* callback list */
    );
}

void thunk_igCameraMode_GetMetaObject(void) {
    igCameraMode_GetMetaObject();
}

void igCameraMode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058cce0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1660[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019f670();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_001a4560();
    igMetaObject_NameFields(temp_s0, &DAT_004d1668[0], &DAT_004d1670[0], &DAT_004d1678[0], temp_s2);
}

int FUN_0045cf10(void) {
    if (DAT_0058ccf8[0] == 0) {
        DAT_0058ccf8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058ccf8[0];
}

void *igViewMode_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058ccf8[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045d000();
    }
    return ((G *)DAT_0058ccf8[0]);
}

int igViewMode_GetVTable(void) {
    struct W o;
    igObject_InitHeader(&o);
    o.vt = DAT_00542960;
    igMatrix44f_SetIdentity(&o.f[2]);
    return *(int *)((char *)&o + *(int *)(((char *)DAT_00586dc8[0]) + 916));
}

void FUN_0045d000(void)
{
    igMetaObject_RunStaticInit(igViewMode_Register);
}

void igViewMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewMode_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igViewMode_GetMetaObject,
        igViewMode_className,
        0x4C, /* instance size */
        igViewMode_GetVTable,
        &igViewMode_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewMode_GetMetaObject(void) {
    igViewMode_GetMetaObject();
}

void igViewMode_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058ccf8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1680[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004d1688[0], &DAT_004d1690[0], &DAT_004d1698[0], temp_s1);
}

int FUN_0045d100(void) {
    if (DAT_0058cd08[0] == 0) {
        DAT_0058cd08[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058cd08[0];
}

void *igViewManager_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058cd08[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045d2f0();
    }
    return ((G *)DAT_0058cd08[0]);
}

int igViewManager_GetVTable(void) {
    union U_45d1a0 u;
    int temp_s3;
    S_ref *q3;
    S_ref *q2;
    S_ref *q1;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00542690[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[12];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[16];
    *(int *)q3 = 0;
    igMatrix44f_SetIdentity(&u.w[5]);
    temp_s3 = *(int *)&u.b[*(int *)((char *)(((void *)DAT_00586dc8[0])) + 916)];
    u.w[0] = (int)(&DAT_00542680[4]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s3;
}

void FUN_0045d2f0(void)
{
    igMetaObject_RunStaticInit(igViewManager_Register);
}

void igViewManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewManager_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igViewManager_GetMetaObject,
        igViewManager_className,
        0x54, /* instance size */
        igViewManager_GetVTable,
        &igViewManager_InitFields,
        0, /* extra callback item */
        g_igViewManager_callbackList /* callback list */
    );
}

void thunk_igViewManager_GetMetaObject(void) {
    igViewManager_GetMetaObject();
}

void igViewManager_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058cd08[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d16b0[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0045cf10();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0045d470();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d16c0[0], &DAT_004d16d0[0], &DAT_004d16e0[0], temp_s2);
}

int FUN_0045d470(void) {
    if (DAT_0058cd30[0] == 0) {
        DAT_0058cd30[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058cd30[0];
}

void *igViewModel_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058cd30[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045d5c0();
    }
    return ((G *)DAT_0058cd30[0]);
}

int igViewModel_GetVTable(void) {
    union U_45d510 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    igObject_InitHeader(u.b);
    p38 = &u.b[8];
    *(int *)p38 = 0;
    u.vt = (int)&DAT_00542040[0];
    igMatrix44f_SetIdentity(&u.b[12]);
    r = *(int *)&u.b[*(int *)((char *)(((void *)DAT_00586dc8[0])) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (p38 != 0) {
        v1 = *(int **)p38;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void FUN_0045d5c0(void)
{
    igMetaObject_RunStaticInit(igViewModel_Register);
}

void igViewModel_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igViewModel_GetMetaObject,
        igViewModel_className,
        0xB0, /* instance size */
        igViewModel_GetVTable,
        &igViewModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewModel_GetMetaObject(void) {
    igViewModel_GetMetaObject();
}

void igViewModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    void *temp_a1, *temp_a2, *temp_a3, *temp_a4, *temp_a5, *temp_a6;
    float v1[4];
    float v2[4];
    float v3[4];
    float v4[4];
    float v5[4];
    float v6[4];

    temp_s0 = (void *)DAT_0058cd30[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d16f0[0], 0xD);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 45.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 1000.0f);
    temp_a1 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5);
    v1[0] = 0.0f; v1[1] = 0.0f; v1[2] = 0.0f;
    FUN_0018e470(temp_a1, v1);
    temp_a2 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6);
    v2[0] = 0.0f; v2[1] = 0.0f; v2[2] = 1.0f;
    FUN_0018e470(temp_a2, v2);
    temp_a3 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7);
    v3[0] = 0.0f; v3[1] = 1.0f; v3[2] = 0.0f;
    FUN_0018e470(temp_a3, v3);
    temp_a4 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8);
    v4[0] = 1.0f; v4[1] = 0.0f; v4[2] = 0.0f;
    FUN_0018e470(temp_a4, v4);
    temp_a5 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9);
    v5[0] = 0.0f; v5[1] = 1.0f; v5[2] = 0.0f;
    FUN_0018e470(temp_a5, v5);
    temp_a6 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB);
    v6[0] = 0.0f; v6[1] = 0.0f; v6[2] = 0.0f;
    FUN_0018e470(temp_a6, v6);
    igMetaObject_NameFields(temp_s0, &DAT_004d1730[0], &DAT_004d1770[0], &DAT_004d17b0[0], temp_s1);
}

int FUN_0045d830(void) {
    if (DAT_0058cda0[0] == 0) {
        DAT_0058cda0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058cda0[0];
}

void *igNormalsRenderer_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058cda0[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045d9f0();
    }
    return ((G *)DAT_0058cda0[0]);
}

int igNormalsRenderer_GetVTable(void) {
    struct Obj_45d8d0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_005422a0[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w10 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_005422a0[0];
    FUN_001d6560(&obj.w10, -1);
    FUN_00136e10(&obj.w8, -1);
    FUN_0019ab10(&obj.w7, -1);
    FUN_00142d10(&obj.w6, -1);
    FUN_0013bfe0(&obj.w5, -1);
    FUN_0013bfe0(&obj.w4, -1);
    FUN_00459860((ObjectRefWord *)&obj.w3, -1);
    FUN_00230f70(&obj, 0);
    return t;
}

void FUN_0045d9f0(void)
{
    igMetaObject_RunStaticInit(igNormalsRenderer_Register);
}

void igNormalsRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNormalsRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igNormalsRenderer_GetMetaObject,
        igNormalsRenderer_className,
        0x30, /* instance size */
        igNormalsRenderer_GetVTable,
        &igNormalsRenderer_InitFields,
        0, /* extra callback item */
        g_igNormalsRenderer_callbackList /* callback list */
    );
}

void thunk_igNormalsRenderer_GetMetaObject(void) {
    igNormalsRenderer_GetMetaObject();
}

void igNormalsRenderer_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;

    temp_s1 = (void *)DAT_0058cda0[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d1810[0], 9);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0045b420();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_001356f0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00138f20();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0013a4d0();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_0019f670();
    igMetaObject_NameFields(temp_s1, &DAT_004d1840[0], &DAT_004d1870[0], &DAT_004d18a0[0], temp_s0);
}

void FUN_0045dbe0(int arg0) {
    FUN_0045dd20();
    igMetaObject_CreateInstance(*(int *)0x58CDF0, arg0);
}

SigLogoRenderer_GetMetaObject *igLogoRenderer_GetMetaObject(void) {
    if (((SigLogoRenderer_GetMetaObject *)DAT_0058cdf0[0]) == 0 || !((SigLogoRenderer_GetMetaObject *)DAT_0058cdf0[0])->ok()) FUN_0045dd20();
    return ((SigLogoRenderer_GetMetaObject *)DAT_0058cdf0[0]);
}

int igLogoRenderer_GetVTable(void) {
    struct Obj_45dc70 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00542230[0];
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_00542230[0];
    FUN_0013bfe0(&obj.w8, -1);
    FUN_0019ab10(&obj.w7, -1);
    FUN_001353b0(&obj.w6, -1);
    FUN_00230f70(&obj, 0);
    return t;
}

void FUN_0045dd20(void)
{
    igMetaObject_RunStaticInit(igLogoRenderer_Register);
}

void igLogoRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLogoRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igLogoRenderer_GetMetaObject,
        igLogoRenderer_className,
        0x28, /* instance size */
        igLogoRenderer_GetVTable,
        &igLogoRenderer_InitFields,
        0, /* extra callback item */
        g_igLogoRenderer_callbackList /* callback list */
    );
}

void thunk_igLogoRenderer_GetMetaObject(void) {
    igLogoRenderer_GetMetaObject();
}

void igLogoRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058cdf0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d18e0[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00137850();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00138f20();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d18f0[0], &DAT_004d1900[0], &DAT_004d1910[0], temp_s2);
}

int FUN_0045de90(void) {
    if (DAT_0058ce18[0] == 0) {
        DAT_0058ce18[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058ce18[0];
}

igMetaObject *igBoundingBoxRenderer_GetMetaObject(void)
{
    igMetaObject *g = ((igMetaObject *)DAT_0058ce18[0]);
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0045e050();
    return ((igMetaObject *)DAT_0058ce18[0]);
}

int igBoundingBoxRenderer_GetVTable(void) {
    struct Obj_45df30 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00542a70[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_00542a70[0];
    FUN_001d6560(&obj.w9, -1);
    FUN_001353b0(&obj.w8, -1);
    FUN_001353b0(&obj.w7, -1);
    FUN_00142d10(&obj.w6, -1);
    FUN_0013bfe0(&obj.w5, -1);
    FUN_00197160(&obj.w4, -1);
    FUN_00459860((ObjectRefWord *)&obj.w3, -1);
    FUN_00230f70(&obj, 0);
    return t;
}

void FUN_0045e050(void)
{
    igMetaObject_RunStaticInit(igBoundingBoxRenderer_Register);
}

void igBoundingBoxRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoundingBoxRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igBoundingBoxRenderer_GetMetaObject,
        igBoundingBoxRenderer_className,
        0x2C, /* instance size */
        igBoundingBoxRenderer_GetVTable,
        &igBoundingBoxRenderer_InitFields,
        0, /* extra callback item */
        g_igBoundingBoxRenderer_callbackList /* callback list */
    );
}

void thunk_igBoundingBoxRenderer_GetMetaObject(void) {
    igBoundingBoxRenderer_GetMetaObject();
}

void igBoundingBoxRenderer_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)DAT_0058ce18[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d1940[0], 8);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0045b420();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00137fb0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_001356f0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00137850();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00137850();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_0019f670();
    igMetaObject_NameFields(temp_s1, &DAT_004d1960[0], &DAT_004d1980[0], &DAT_004d19a0[0], temp_s0);
}

void FUN_0045e230(int arg0) {
    FUN_0045e4a0();
    igMetaObject_CreateInstance(*(int *)0x58CE60, arg0);
}

void *igActorManager_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058ce60[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045e4a0();
    }
    return ((G *)DAT_0058ce60[0]);
}

int igActorManager_GetVTable(void) {
    struct Obj_45e2c0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_005429f0[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_005429f0[0];
    FUN_0014aa70(&obj.w13, -1);
    FUN_004584f0(&obj.w12, -1);
    FUN_0019ab90(&obj.w11, -1);
    FUN_0019ab90(&obj.w10, -1);
    FUN_0013a880(&obj.w9, -1);
    FUN_00135430(&obj.w8, -1);
    FUN_0045e420((O *)&obj.w7, -1);
    FUN_001aa310(&obj.w6, -1);
    FUN_001958f0(&obj.w5, -1);
    FUN_001a7a00(&obj.w4, -1);
    FUN_00231030(&obj, 0);
    return t;
}

O *FUN_0045e420(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void FUN_0045e4a0(void)
{
    igMetaObject_RunStaticInit(igActorManager_Register);
}

void igActorManager_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActorManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        thunk_igActorManager_GetMetaObject,
        igActorManager_className,
        0x38, /* instance size */
        igActorManager_GetVTable,
        &igActorManager_InitFields,
        0, /* extra callback item */
        g_igActorManager_callbackList /* callback list */
    );
}

void thunk_igActorManager_GetMetaObject(void) {
    igActorManager_GetMetaObject();
}

void igActorManager_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058ce60[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d19f0[0], 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001a5fe0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019cbe0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_001aa5c0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0045e6f0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002c9170();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_002c8e50();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00130440();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_00130440();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_00459380();
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d1a20[0], &DAT_004d1a50[0], &DAT_004d1a80[0], temp_s1);
}

int FUN_0045e6f0(void) {
    if (DAT_0058ceb8[0] == 0) {
        DAT_0058ceb8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058ceb8[0];
}

void *igActorManagerParams_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058ceb8[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045e830();
    }
    return ((G *)DAT_0058ceb8[0]);
}

int igActorManagerParams_GetVTable(void) {
    union U_45e790 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00540e30[0];
    u.vt = (int)&DAT_00541fe0[0];
    s0 = *(int *)&u.b[*(int *)((char *)(((void *)DAT_00586dc8[0])) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return s0;
}

void FUN_0045e830(void)
{
    igMetaObject_RunStaticInit(igActorManagerParams_Register);
}

void igActorManagerParams_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActorManagerParams_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igActorManagerParams_GetMetaObject,
        igActorManagerParams_className,
        0x10, /* instance size */
        igActorManagerParams_GetVTable,
        &igActorManagerParams_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igActorManagerParams_GetMetaObject(void) {
    igActorManagerParams_GetMetaObject();
}

void igActorManagerParams_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058ceb8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1aa8[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004d1ab0[0], &DAT_004d1ab8[0], &DAT_004d1ac0[0], temp_s1);
}

int Gap__Viewer__igActorManagerParams__vfunc_22(void) {
    return DAT_0058ceb8[0];
}

int Gap__Viewer__igViewModel__vfunc_22(void) {
    return DAT_0058cd30[0];
}

int Gap__Viewer__igViewerParameters__vfunc_22(void) {
    return DAT_0058c9e8[0];
}

int Gap__Viewer__igViewerLoadingFileMessage__vfunc_22(void) {
    return DAT_0058c910[0];
}

int Gap__Viewer__igViewerModeChangeMessage__vfunc_22(void) {
    return DAT_0058c8f8[0];
}

int Gap__Viewer__igStatisticsItemList__vfunc_22(void) {
    return DAT_0058c700[0];
}

int Gap__Viewer__igStatisticsItemList__vfunc_24(void) {
    return DAT_0058c708[0];
}

