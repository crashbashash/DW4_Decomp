#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"
#define CHAR_METRICS_ITEM_SIZE 0x28

extern "C" void igMetaObject_RunStaticInit(...);
extern "C" int FUN_002d7090(...);
extern "C" int List_InsertWords(...);
extern "C" int DAT_0058c618[4];
extern "C" int FUN_00191f30(...);
extern "C" int FUN_00192fc0(...);
extern "C" int DAT_0058c418[4];
extern "C" unsigned char g_GuiLibrary_registered;
extern "C" void GuiLibrary_MarkRegistered(void);
extern "C" int igMetaObject_Create(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int DAT_00587040[4];
extern "C" int DAT_0058c1b0[4];
extern "C" int FUN_0044b880(void);
extern "C" igMetaObject *g_igNonRefCountedViewList_metaObject[4];
extern "C" igMetaObject *igNonRefCountedViewList_GetMetaObject(void);
struct Obj { int *vt; char pad[28]; };
extern "C" int igObject_InitHeader(...);
extern "C" int DAT_00541f70[4];
extern "C" void * DAT_00586dc8[4];
extern "C" int igNonRefCountedViewList_GetVTable(void);
extern "C" void igNonRefCountedViewList_EnsureRegistered(void);
extern "C" char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern "C" char igNonRefCountedObjectList_Register[];
extern "C" char g_igNonRefCountedViewList_callbackList[];
extern "C" char igNonRefCountedViewList_className[];
extern "C" int igMetaObject_RegisterClass(...);
extern "C" void igNonRefCountedViewList_Register(void);
extern "C" void thunk_igNonRefCountedViewList_GetMetaObject(void);
extern "C" int DAT_0058c1b8[4];
extern "C" int FUN_0044b9f0(void);
extern "C" igMetaObject *g_igViewList_metaObject[4];
extern "C" igMetaObject *igViewList_GetMetaObject(void);
extern "C" int DAT_00541f00[4];
extern "C" int igViewList_GetVTable(void);
extern "C" void igViewList_EnsureRegistered(void);
extern "C" char igObjectList_GetPublishedMetaObject[];
extern "C" char igObjectList_Register[];
extern "C" char g_igViewList_callbackList[];
extern "C" char igViewList_className[];
extern "C" void igViewList_Register(void);
extern "C" void thunk_igViewList_GetMetaObject(void);
extern "C" igMetaObject *g_igView_metaObject[4];
extern "C" igMetaObject *igView_GetMetaObject(void);
extern "C" void igView_EnsureRegistered(void);
extern "C" char igObject_GetMetaObject_ParentAccessor[];
extern "C" char igObject_Register[];
extern "C" char g_igView_callbackList[];
extern "C" char igView_className[];
extern "C" void igView_Register(void);
extern "C" void thunk_igView_GetMetaObject(void);
extern "C" int igMetaObject_CreateFields(...);
extern "C" void *igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int DAT_004cfef8[4];
extern "C" int DAT_004cff00[4];
extern "C" int DAT_004cff08[4];
extern "C" int DAT_004cff10[4];
extern "C" int DAT_0058c1c0[4];
extern "C" void igView_InitFields(void);
extern "C" int DAT_0058c1d0[4];
extern "C" int FUN_0044bce0(void);
extern "C" igMetaObject *g_igTextElement_metaObject[4];
extern "C" igMetaObject *igTextElement_GetMetaObject(void);
extern "C" int FUN_001353b0(...);
extern "C" int StringRef_Destruct_00130720(...);
union U { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" int DAT_00540c10[4];
extern "C" int igTextElement_GetVTable(void);
extern "C" int thunk_FUN_002ed460__002ff810(...);
extern "C" int DAT_00541e90[4];
extern "C" void *FUN_0044be30(igGeometryElement *arg0, short arg1);
extern "C" int FUN_00100610(...);
extern "C" void **FUN_0044bf10(void **arg0, long long arg1);
extern "C" void igTextElement_EnsureRegistered(void);
extern "C" char igGeometryElement_GetPublishedMetaObject[];
extern "C" char g_igTextElement_callbackList[];
extern "C" char igTextElement_className[];
extern "C" void igTextElement_Register(void);
extern "C" void thunk_igTextElement_GetMetaObject(void);
extern "C" int DAT_0058c4e8[4];
extern "C" int FUN_0044c030(void);
extern "C" int FUN_00137850(...);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" int DAT_004cff28[4];
extern "C" int DAT_004cff38[4];
extern "C" int DAT_004cff48[4];
extern "C" int DAT_004cff58[4];
extern "C" int DAT_0051dd88[4];
extern "C" void igTextElement_InitFields(void);
extern "C" int DAT_00540e30[4];
struct S {
    void *f0;
    char pad[4];
    void *f8;
};
extern "C" void *FUN_0044c110(struct S *arg0, short arg1);
extern "C" int DAT_0058c438[4];
extern "C" int FUN_0044c1b0(void);
extern "C" void **FUN_0044c1c0(void **arg0, int arg1);
extern "C" int DAT_0058c480[4];
extern "C" int FUN_0044c240(void);
extern "C" int DAT_0058c1f0[4];
extern "C" int FUN_0044c250(void);
extern "C" igMetaObject *g_igClearRenderer_metaObject[4];
extern "C" igMetaObject *igClearRenderer_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
extern "C" int DAT_0052d060[4];
extern "C" int DAT_00540c80[4];
union U_44c2f0 { int vt; char b[16]; };
extern "C" int igClearRenderer_GetVTable(void);
extern "C" void igClearRenderer_EnsureRegistered(void);
extern "C" char igRenderer_GetPublishedMetaObject[];
extern "C" char igClearRenderer_className[];
extern "C" void igClearRenderer_Register(void);
extern "C" void thunk_igClearRenderer_GetMetaObject(void);
extern "C" int DAT_004cff68[4];
extern "C" int DAT_004cff70[4];
extern "C" int DAT_004cff78[4];
extern "C" int DAT_004cff80[4];
extern "C" void igClearRenderer_InitFields(void);
extern "C" int igMetaObject_CreateInstance(int, int);
extern "C" void FUN_0044c490(int arg0);
extern "C" int DAT_0058c200[4];
extern "C" int FUN_0044c4d0(void);
extern "C" igMetaObject *g_igRendererOrderedList_metaObject[4];
extern "C" igMetaObject *igRendererOrderedList_GetMetaObject(void);
struct Obj_44c570 { int *vt; int w[7]; };
extern "C" int DAT_00541d70[4];
extern "C" int igRendererOrderedList_GetVTable(void);
extern "C" int FUN_00135430(...);
extern "C" int FUN_0014aa70(...);
extern "C" int ObjectRef_Destruct_001c6460(...);
extern "C" int FUN_00233590(...);
extern "C" int DAT_0052cc20[4];
extern "C" int DAT_00541dd0[4];
extern "C" int **FUN_0044c5e0(int **arg0, long long arg1);
extern "C" void igRendererOrderedList_EnsureRegistered(void);
extern "C" char igDependencyOrderedList_GetPublishedMetaObject[];
extern "C" char igDependencyOrderedList_Register[];
extern "C" char g_igRendererOrderedList_callbackList[];
extern "C" char igRendererOrderedList_className[];
extern "C" void igRendererOrderedList_Register(void);
extern "C" void thunk_igRendererOrderedList_GetMetaObject(void);
extern "C" igMetaObject *g_igRenderer_metaObject[4];
extern "C" igMetaObject *igRenderer_GetMetaObject(void);
extern "C" void igRenderer_EnsureRegistered(void);
extern "C" char g_igRenderer_callbackList[];
extern "C" char igRenderer_className[];
extern "C" void igRenderer_Register(void);
extern "C" void thunk_igRenderer_GetMetaObject(void);
extern "C" int FUN_0014a040(...);
extern "C" int DAT_004cff98[4];
extern "C" int DAT_004cffa0[4];
extern "C" int DAT_004cffa8[4];
extern "C" int DAT_004cffb0[4];
extern "C" int DAT_0058c208[4];
extern "C" void igRenderer_InitFields(void);
extern "C" int DAT_0058c218[4];
extern "C" int FUN_0044c880(void);
extern "C" igMetaObject *g_igOnOffValueObserverList_metaObject[4];
extern "C" igMetaObject *igOnOffValueObserverList_GetMetaObject(void);
typedef struct { int *vt; int pad[7]; } Obj_44c920;
extern "C" int DAT_00541d00[4];
extern "C" int igOnOffValueObserverList_GetVTable(void);
extern "C" void igOnOffValueObserverList_EnsureRegistered(void);
extern "C" char g_igOnOffValueObserverList_callbackList[];
extern "C" char igOnOffValueObserverList_className[];
extern "C" void igOnOffValueObserverList_Register(void);
extern "C" void thunk_igOnOffValueObserverList_GetMetaObject(void);
extern "C" igMetaObject *g_igOnOffValueObserver_metaObject[4];
extern "C" igMetaObject *igOnOffValueObserver_GetMetaObject(void);
struct Obj_44ca40 { int *vt; char pad[12]; };
extern "C" int DAT_00540cf0[4];
extern "C" int igOnOffValueObserver_GetVTable(void);
extern "C" void igOnOffValueObserver_EnsureRegistered(void);
extern "C" char igView_GetPublishedMetaObject[];
extern "C" char g_igOnOffValueObserver_callbackList[];
extern "C" char igOnOffValueObserver_className[];
extern "C" void igOnOffValueObserver_Register(void);
extern "C" void thunk_igOnOffValueObserver_GetMetaObject(void);
extern "C" int FUN_0044cb20(void);
extern "C" int DAT_004cffc8[4];
extern "C" int DAT_004cffd0[4];
extern "C" int DAT_004cffd8[4];
extern "C" int DAT_004cffe0[4];
extern "C" int DAT_0058c220[4];
extern "C" void igOnOffValueObserver_InitFields(void);
extern "C" int DAT_0058c230[4];
extern "C" int FUN_0044cbd0(void);
extern "C" igMetaObject *g_igRadioGroupSelectedObserver_metaObject[4];
extern "C" igMetaObject *igRadioGroupSelectedObserver_GetMetaObject(void);
struct O { int *vt; char post[12]; };
extern "C" int DAT_00540d60[4];
extern "C" int igRadioGroupSelectedObserver_GetVTable(void);
extern "C" void igRadioGroupSelectedObserver_EnsureRegistered(void);
extern "C" char g_igRadioGroupSelectedObserver_callbackList[];
extern "C" char igRadioGroupSelectedObserver_className[];
extern "C" void igRadioGroupSelectedObserver_Register(void);
extern "C" void thunk_igRadioGroupSelectedObserver_GetMetaObject(void);
extern "C" int DAT_004cfff0[4];
extern "C" int DAT_004cfff8[4];
extern "C" int DAT_004d0000[4];
extern "C" int DAT_004d0008[4];
extern "C" void igRadioGroupSelectedObserver_InitFields(void);
extern "C" int DAT_0058c240[4];
extern "C" int FUN_0044cdf0(void);
extern "C" igMetaObject *g_igRadioGroup_metaObject[4];
extern "C" igMetaObject *igRadioGroup_GetMetaObject(void);
extern "C" int DAT_00540dd0[4];
union U_44ce90 { int vt; char b[32]; };
extern "C" int igRadioGroup_GetVTable(void);
extern "C" void igRadioGroup_EnsureRegistered(void);
extern "C" char g_igRadioGroup_callbackList[];
extern "C" char igRadioGroup_className[];
extern "C" void igRadioGroup_Register(void);
extern "C" void thunk_igRadioGroup_GetMetaObject(void);
extern "C" int FUN_002d3890(...);
extern "C" int FUN_002ea4b0(...);
extern "C" int DAT_004d0020[4];
extern "C" int DAT_004d0040[4];
extern "C" int DAT_004d0060[4];
extern "C" int DAT_004d0080[4];
extern "C" void igRadioGroup_InitFields(void);
extern "C" int DAT_0058c278[4];
extern "C" int FUN_0044d170(void);
extern "C" igMetaObject *g_igRadioGroupModel_metaObject[4];
extern "C" igMetaObject *igRadioGroupModel_GetMetaObject(void);
extern "C" int DAT_00541ca0[4];
union U_44d210 { int vt; char b[16]; };
extern "C" int igRadioGroupModel_GetVTable(void);
extern "C" void igRadioGroupModel_RunStaticInit(void);
extern "C" char igModel_GetPublishedMetaObject[];
extern "C" char igRadioGroupModel_className[];
extern "C" void igRadioGroupModel_Register(void);
extern "C" void thunk_igRadioGroupModel_GetMetaObject(void);
extern "C" int DAT_0058c298[4];
extern "C" int FUN_0044d340(void);
extern "C" int DAT_004d0098[4];
extern "C" int DAT_004d00a0[4];
extern "C" int DAT_004d00a8[4];
extern "C" int DAT_004d00b0[4];
extern "C" void igRadioGroupModel_InitFields(void);
extern "C" igMetaObject *g_igOnOffModel_metaObject[4];
extern "C" igMetaObject *igOnOffModel_GetMetaObject(void);
extern "C" int DAT_00541c40[4];
union U_44d430 { int vt; char b[48]; };
extern "C" int igOnOffModel_GetVTable(void);
extern "C" void igOnOffModel_RunStaticInit(void);
extern "C" char igGuiComponentModel_GetPublishedMetaObject[];
extern "C" char igOnOffModel_className[];
extern "C" void igOnOffModel_Register(void);
extern "C" void thunk_igOnOffModel_GetMetaObject(void);
extern "C" int DAT_004d00b8[4];
extern "C" int DAT_004d00c0[4];
extern "C" int DAT_004d00c8[4];
extern "C" int DAT_004d00d0[4];
extern "C" int DAT_0058c288[4];
extern "C" void igOnOffModel_InitFields(void);
extern "C" int FUN_0044d5d0(void);
extern "C" igMetaObject *g_igModel_metaObject[4];
extern "C" igMetaObject *igModel_GetMetaObject(void);
struct Obj_44d670 { int *vt; char pad[4]; char *m; char pad2[4]; };
extern "C" int igModel_GetVTable(void);
extern "C" void igModel_RunStaticInit(void);
extern "C" char g_igModel_callbackList[];
extern "C" char igModel_className[];
extern "C" void igModel_Register(void);
extern "C" void thunk_igModel_GetMetaObject(void);
extern "C" int DAT_004d00e0[4];
extern "C" int DAT_004d00e8[4];
extern "C" int DAT_004d00f0[4];
extern "C" int DAT_004d00f8[4];
extern "C" void igModel_InitFields(void);
extern "C" int DAT_0058c2a8[4];
extern "C" int FUN_0044d840(void);
extern "C" igMetaObject *g_igHotKeyEventReceiver_metaObject[4];
extern "C" igMetaObject *igHotKeyEventReceiver_GetMetaObject(void);
extern "C" int DAT_00540e90[4];
union U_44d8e0 { int vt; char b[16]; };
extern "C" int igHotKeyEventReceiver_GetVTable(void);
extern "C" void igHotKeyEventReceiver_RunStaticInit(void);
extern "C" char igEventReceiver_GetPublishedMetaObject[];
extern "C" char g_igHotKeyEventReceiver_callbackList[];
extern "C" char igHotKeyEventReceiver_className[];
extern "C" void igHotKeyEventReceiver_Register(void);
extern "C" void thunk_igHotKeyEventReceiver_GetMetaObject(void);
extern "C" int DAT_004d0108[4];
extern "C" int DAT_004d0110[4];
extern "C" int DAT_004d0118[4];
extern "C" int DAT_004d0120[4];
extern "C" void igHotKeyEventReceiver_InitFields(void);
extern "C" int DAT_0058c2b8[4];
extern "C" int FUN_0044dab0(void);
extern "C" igMetaObject *g_igHotKeyBindingList_metaObject[4];
extern "C" igMetaObject *igHotKeyBindingList_GetMetaObject(void);
extern "C" int DAT_00541bd0[4];
extern "C" int igHotKeyBindingList_GetVTable(void);
extern "C" void igHotKeyBindingList_RunStaticInit(void);
extern "C" char g_igHotKeyBindingList_callbackList[];
extern "C" char igHotKeyBindingList_className[];
extern "C" void igHotKeyBindingList_Register(void);
extern "C" void thunk_igHotKeyBindingList_GetMetaObject(void);
extern "C" int FUN_0044dc20(int arg0);
extern "C" igMetaObject *g_igHotKeyBinding_metaObject[4];
extern "C" igMetaObject *igHotKeyBinding_GetMetaObject(void);
extern "C" int DAT_00541b70[4];
struct R { int vt; unsigned int rc; };
struct Obj_44dcb0 { int *vt; char pad[12]; struct R *p; char pad2[12]; };
extern "C" int igHotKeyBinding_GetVTable(void);
extern "C" void igHotKeyBinding_RunStaticInit(void);
extern "C" char g_igHotKeyBinding_callbackList[];
extern "C" char igHotKeyBinding_className[];
extern "C" void igHotKeyBinding_Register(void);
extern "C" void thunk_igHotKeyBinding_GetMetaObject(void);
extern "C" int FUN_002dc7a0(...);
extern "C" void FUN_00145eb0(void);
extern "C" void FUN_00146850(void);
extern "C" int DAT_004d0138[4];
extern "C" int DAT_004d0148[4];
extern "C" int DAT_004d0158[4];
extern "C" int DAT_004d0168[4];
extern "C" int DAT_004d0178[4];
extern "C" int DAT_004d0180[4];
extern "C" int DAT_0058c2c0[4];
extern "C" void igHotKeyBinding_InitFields(void);
extern "C" int DAT_0058c2e0[4];
extern "C" int FUN_0044ded0(void);
extern "C" igMetaObject *g_igGuiSystem_metaObject[4];
extern "C" igMetaObject *igGuiSystem_GetMetaObject(void);
struct Obj_44df70 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int FUN_001a7580(...);
extern "C" int FUN_001d97f0(...);
extern "C" int DAT_00540f20[4];
extern "C" int igGuiSystem_GetVTable(void);
extern "C" void **FUN_0044e060(void **arg0, short arg1);
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" void **FUN_0044e0e0(struct Ref **self, short flag);
extern "C" void **FUN_0044e160(void **arg0, long long arg1);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O_44e1e0 { S_temp_a0 *m; };
extern "C" O_44e1e0 *FUN_0044e1e0(O_44e1e0 *arg0, short arg1);
extern "C" void igGuiSystem_RunStaticInit(void);
extern "C" char g_igGuiSystem_callbackList[];
extern "C" char igGuiSystem_className[];
extern "C" void igGuiSystem_Register(void);
extern "C" void thunk_igGuiSystem_GetMetaObject(void);
extern "C" int FUN_00196190(...);
extern "C" int FUN_001a5d70(...);
extern "C" int DAT_004d01b0[4];
extern "C" int DAT_004d01d0[4];
extern "C" int DAT_004d01f0[4];
extern "C" int DAT_004d0210[4];
extern "C" void igGuiSystem_InitFields(void);
extern "C" int DAT_0058c320[4];
extern "C" int FUN_0044e430(void);
extern "C" igMetaObject *g_igMouseCursor_metaObject[4];
extern "C" igMetaObject *igMouseCursor_GetMetaObject(void);
struct Obj_44e4d0 { int *vt; char pad[4]; char *m; char pad2[20]; };
extern "C" int DAT_00541b10[4];
extern "C" int igMouseCursor_GetVTable(void);
extern "C" void igMouseCursor_RunStaticInit(void);
extern "C" char g_igMouseCursor_callbackList[];
extern "C" char igMouseCursor_className[];
extern "C" void igMouseCursor_Register(void);
extern "C" void thunk_igMouseCursor_GetMetaObject(void);
extern "C" int FUN_0018e2f0(void *, int *);
extern "C" int DAT_004d0238[4];
extern "C" int DAT_004d0240[4];
extern "C" int DAT_004d0248[4];
extern "C" int DAT_004d0250[4];
extern "C" void igMouseCursor_InitFields(void);
extern "C" int DAT_0058c338[4];
extern "C" int FUN_0044e6b0(void);
extern "C" igMetaObject *g_igGuiSystemRenderer_metaObject[4];
extern "C" igMetaObject *igGuiSystemRenderer_GetMetaObject(void);
struct Obj_44e750 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int FUN_00197160(...);
extern "C" int FUN_00198210(...);
extern "C" int FUN_001d9870(...);
extern "C" int FUN_00230f70(...);
extern "C" int DAT_00540fb0[4];
extern "C" int igGuiSystemRenderer_GetVTable(void);
extern "C" void igGuiSystemRenderer_RunStaticInit(void);
extern "C" char g_igGuiSystemRenderer_callbackList[];
extern "C" char igGuiSystemRenderer_className[];
extern "C" void igGuiSystemRenderer_Register(void);
extern "C" void thunk_igGuiSystemRenderer_GetMetaObject(void);
extern "C" int FUN_00137fb0(...);
extern "C" int FUN_0019cd50(...);
extern "C" int FUN_001a38e0(...);
extern "C" int DAT_004d0280[4];
extern "C" int DAT_004d0290[4];
extern "C" int DAT_004d02a0[4];
extern "C" int DAT_004d02b0[4];
extern "C" void igGuiSystemRenderer_InitFields(void);
extern "C" int FUN_0044e990(int arg0);
extern "C" igMetaObject *g_igActiveComponentsObserver_metaObject[4];
extern "C" igMetaObject *igActiveComponentsObserver_GetMetaObject(void);
extern "C" int DAT_00541020[4];
union U_44ea20 { int vt; char b[32]; };
extern "C" int igActiveComponentsObserver_GetVTable(void);
extern "C" void igActiveComponentsObserver_RunStaticInit(void);
extern "C" char g_igActiveComponentsObserver_callbackList[];
extern "C" char igActiveComponentsObserver_className[];
extern "C" void igActiveComponentsObserver_Register(void);
extern "C" void thunk_igActiveComponentsObserver_GetMetaObject(void);
extern "C" int DAT_004d02c8[4];
extern "C" int DAT_004d02d8[4];
extern "C" int DAT_004d02e8[4];
extern "C" int DAT_004d02f8[4];
extern "C" int DAT_0058c360[4];
extern "C" void igActiveComponentsObserver_InitFields(void);
extern "C" int FUN_0044ecb0(int arg0);
extern "C" igMetaObject *g_igMousePosObserver_metaObject[4];
extern "C" igMetaObject *igMousePosObserver_GetMetaObject(void);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int DAT_00541090[4];
extern "C" int D_00541090[4];
extern "C" int igMousePosObserver_GetVTable(void);
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" ObjectRefWord *FUN_0044ee80(ObjectRefWord *self,int delete_storage);
extern "C" void igMousePosObserver_RunStaticInit(void);
extern "C" char g_igMousePosObserver_callbackList[];
extern "C" char igMousePosObserver_className[];
extern "C" void igMousePosObserver_Register(void);
extern "C" void thunk_igMousePosObserver_GetMetaObject(void);
extern "C" int FUN_00188260(...);
extern "C" int FUN_0019dfd0(...);
extern "C" int FUN_0019f670(...);
extern "C" int FUN_002e3810(int, float);
extern "C" int DAT_004d0330[4];
extern "C" int DAT_004d0350[4];
extern "C" int DAT_004d0370[4];
extern "C" int DAT_004d0390[4];
extern "C" int DAT_0058c380[4];
extern "C" void igMousePosObserver_InitFields(void);
extern "C" int FUN_0044f0b0(int arg0);
extern "C" igMetaObject *g_igWindowSizeObserver_metaObject[4];
extern "C" igMetaObject *igWindowSizeObserver_GetMetaObject(void);
extern "C" int DAT_00541100[4];
extern "C" int igWindowSizeObserver_GetVTable(void);
extern "C" void igWindowSizeObserver_RunStaticInit(void);
extern "C" char igWindowSizeObserver_className[];
extern "C" void igWindowSizeObserver_Register(void);
extern "C" void thunk_igWindowSizeObserver_GetMetaObject(void);
extern "C" int DAT_0058c3c8[4];
extern "C" int FUN_0044f210(void);
extern "C" igMetaObject *g_igGuiSystemModel_metaObject[4];
extern "C" igMetaObject *igGuiSystemModel_GetMetaObject(void);
extern "C" int FUN_003cafa0(...);
extern "C" int DAT_00541170[4];
extern "C" int igGuiSystemModel_GetVTable(void);
extern "C" void igGuiSystemModel_RunStaticInit(void);
extern "C" char g_igGuiSystemModel_callbackList[];
extern "C" char igGuiSystemModel_className[];
extern "C" void igGuiSystemModel_Register(void);
extern "C" void thunk_igGuiSystemModel_GetMetaObject(void);
extern "C" int DAT_004d03c0[4];
extern "C" int DAT_004d03f0[4];
extern "C" int DAT_004d0420[4];
extern "C" int DAT_004d0450[4];
extern "C" void igGuiSystemModel_InitFields(void);
extern "C" int DAT_0058c428[4];
extern "C" int FUN_0044f540(void);
extern "C" igMetaObject *g_igGuiComponentNode_metaObject[4];
extern "C" igMetaObject *igGuiComponentNode_GetMetaObject(void);
struct Obj_44f5e0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int FUN_00195a90(...);
extern "C" int DAT_005411d0[4];
extern "C" int igGuiComponentNode_GetVTable(void);
extern "C" void igGuiComponentNode_RunStaticInit(void);
extern "C" char igGroup_GetPublishedMetaObject[];
extern "C" char igGroup_Register[];
extern "C" char g_igGuiComponentNode_callbackList[];
extern "C" char igGuiComponentNode_className[];
extern "C" void igGuiComponentNode_Register(void);
extern "C" void thunk_igGuiComponentNode_GetMetaObject(void);
extern "C" int DAT_004d0488[4];
extern "C" int DAT_004d0490[4];
extern "C" int DAT_004d0498[4];
extern "C" int DAT_004d04a0[4];
extern "C" void igGuiComponentNode_InitFields(void);
extern "C" int FUN_0044f790(void);
extern "C" igMetaObject *g_igGuiComponentModel_metaObject[4];
extern "C" igMetaObject *igGuiComponentModel_GetMetaObject(void);
extern "C" int DAT_00541e30[4];
union U_44f830 { int vt; char b[48]; };
extern "C" int igGuiComponentModel_GetVTable(void);
extern "C" void igGuiComponentModel_RunStaticInit(void);
extern "C" char g_igGuiComponentModel_callbackList[];
extern "C" char igGuiComponentModel_className[];
extern "C" void igGuiComponentModel_Register(void);
extern "C" void thunk_igGuiComponentModel_GetMetaObject(void);
extern "C" int FUN_0018e470(...);
extern "C" int DAT_004d04b0[4];
extern "C" int DAT_004d04d0[4];
extern "C" int DAT_004d04f0[4];
extern "C" int DAT_004d0510[4];
extern "C" void igGuiComponentModel_InitFields(void);
extern "C" int DAT_0058c478[4];
extern "C" int FUN_0044fa40(void);
extern "C" igMetaObject *g_igGuiComponentController_metaObject[4];
extern "C" igMetaObject *igGuiComponentController_GetMetaObject(void);
struct Obj_44fae0 { int *vt; char pad[12]; };
extern "C" int DAT_00541270[4];
extern "C" int igGuiComponentController_GetVTable(void);
extern "C" void igGuiComponentController_EnsureRegistered(void);
extern "C" char igGuiComponentController_className[];
extern "C" void igGuiComponentController_Register(void);
extern "C" void thunk_igGuiComponentController_GetMetaObject(void);
extern "C" int FUN_0044fbb0(void);
extern "C" igMetaObject *g_igGuiComponentAspect_metaObject[4];
extern "C" igMetaObject *igGuiComponentAspect_GetMetaObject(void);
extern "C" void igGuiComponentAspect_EnsureRegistered(void);
extern "C" char g_igGuiComponentAspect_callbackList[];
extern "C" char igGuiComponentAspect_className[];
extern "C" void igGuiComponentAspect_Register(void);
extern "C" void thunk_igGuiComponentAspect_GetMetaObject(void);
extern "C" int DAT_004d0538[4];
extern "C" int DAT_004d0548[4];
extern "C" int DAT_004d0558[4];
extern "C" int DAT_004d0568[4];
struct GuiAspectMetaField { char pad[56]; int f56; char b60; };
extern "C" void igGuiComponentAspect_InitFields(void);
extern "C" int DAT_0058c4a0[4];
extern "C" int FUN_0044fdd0(void);
extern "C" igMetaObject *g_igGuiComponentList_metaObject[4];
extern "C" igMetaObject *igGuiComponentList_GetMetaObject(void);
extern "C" int DAT_00541aa0[4];
extern "C" int igGuiComponentList_GetVTable(void);
extern "C" void igGuiComponentList_EnsureRegistered(void);
extern "C" char g_igGuiComponentList_callbackList[];
extern "C" char igGuiComponentList_className[];
extern "C" void igGuiComponentList_Register(void);
extern "C" void thunk_igGuiComponentList_GetMetaObject(void);
extern "C" int DAT_0058c4a8[4];
extern "C" int FUN_0044ff40(void);
extern "C" igMetaObject *g_igGuiComponent_metaObject[4];
extern "C" igMetaObject *igGuiComponent_GetMetaObject(void);
struct Obj_44ffe0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_00541300[4];
extern "C" int igGuiComponent_GetVTable(void);
struct S1 { char pad4[4]; int f4; };
struct O_450090 { int *vt; char pad4[8]; S1 *m12; S1 *m16; S1 *m20; char pad24[4]; S1 *m28; };
extern "C" O_450090 *FUN_00450090(O_450090 *arg0, short arg1);
typedef struct S_temp_a0_4501f0 { char pad4[4]; int f4; } S_temp_a0_4501f0;
extern "C" void **FUN_004501f0(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00450270(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_004502f0(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00450370(ObjectRefWord *self,int delete_storage);
extern "C" void igGuiComponent_EnsureRegistered(void);
extern "C" char g_igGuiComponent_callbackList[];
extern "C" char igGuiComponent_className[];
extern "C" void igGuiComponent_Register(void);
extern "C" void thunk_igGuiComponent_GetMetaObject(void);
extern "C" int DAT_004d05a0[4];
extern "C" int DAT_004d05c0[4];
extern "C" int DAT_004d05e0[4];
extern "C" int DAT_004d0600[4];
extern "C" void igGuiComponent_InitFields(void);
extern "C" int FUN_004505b0(void);
extern "C" igMetaObject *g_igGeometryElement_metaObject[4];
extern "C" igMetaObject *igGeometryElement_GetMetaObject(void);
extern "C" void igGeometryElement_EnsureRegistered(void);
extern "C" char g_igGeometryElement_callbackList[];
extern "C" char igGeometryElement_className[];
extern "C" void igGeometryElement_Register(void);
extern "C" void thunk_igGeometryElement_GetMetaObject(void);
extern "C" int FUN_0013af00(...);
extern "C" int FUN_0018e670(...);
extern "C" int FUN_0019fae0(...);
extern "C" int DAT_004d0630[4];
extern "C" int DAT_004d0640[4];
extern "C" int DAT_004d0650[4];
extern "C" int DAT_004d0660[4];
extern "C" void igGeometryElement_InitFields(void);
extern "C" int DAT_0058c510[4];
extern "C" int FUN_004507f0(void);
extern "C" igMetaObject *g_igFont_metaObject[4];
extern "C" igMetaObject *igFont_GetMetaObject(void);
extern "C" void igFont_EnsureRegistered(void);
extern "C" char igNamedObject_GetPublishedMetaObject[];
extern "C" int igNamedObject_Register(...);
extern "C" char g_igFont_callbackList[];
extern "C" char igFont_className[];
extern "C" void igFont_Register(void);
extern "C" void thunk_igFont_GetMetaObject(void);
extern "C" int DAT_004d0680[4];
extern "C" int DAT_004d0690[4];
extern "C" int DAT_004d06a0[4];
extern "C" int DAT_004d06b0[4];
extern "C" void igFont_InitFields(void);
extern "C" void FUN_004509c0(int arg0);
extern "C" int DAT_0058c538[4];
extern "C" int FUN_00450a00(void);
extern "C" igMetaObject *g_igFieldSynchronizer_metaObject[4];
extern "C" igMetaObject *igFieldSynchronizer_GetMetaObject(void);
extern "C" int DAT_00541a40[4];
struct Obj_450aa0 { int *vt; char pad[4]; struct R *p; char pad2[4]; };
extern "C" int igFieldSynchronizer_GetVTable(void);
extern "C" void igFieldSynchronizer_EnsureRegistered(void);
extern "C" char g_igFieldSynchronizer_callbackList[];
extern "C" char igFieldSynchronizer_className[];
extern "C" void igFieldSynchronizer_Register(void);
extern "C" void thunk_igFieldSynchronizer_GetMetaObject(void);
extern "C" int DAT_004d06c8[4];
extern "C" int DAT_004d06d0[4];
extern "C" int DAT_004d06d8[4];
extern "C" int DAT_004d06e0[4];
extern "C" void igFieldSynchronizer_InitFields(void);
extern "C" int DAT_0058c548[4];
extern "C" int FUN_00450c70(void);
extern "C" igMetaObject *g_igFieldChangeViewList_metaObject[4];
extern "C" igMetaObject *igFieldChangeViewList_GetMetaObject(void);
extern "C" int DAT_005419d0[4];
extern "C" int igFieldChangeViewList_GetVTable(void);
extern "C" void igFieldChangeViewList_EnsureRegistered(void);
extern "C" char g_igFieldChangeViewList_callbackList[];
extern "C" char igFieldChangeViewList_className[];
extern "C" void igFieldChangeViewList_Register(void);
extern "C" void thunk_igFieldChangeViewList_GetMetaObject(void);
extern "C" int FUN_00450de0(int arg0);
extern "C" igMetaObject *g_igFieldChangeView_metaObject[4];
extern "C" igMetaObject *igFieldChangeView_GetMetaObject(void);
struct Obj_450e70 { int *vt; char pad[12]; char *m; char pad2[12]; };
extern "C" int DAT_00541360[4];
extern "C" int igFieldChangeView_GetVTable(void);
extern "C" void igFieldChangeView_EnsureRegistered(void);
extern "C" char g_igFieldChangeView_callbackList[];
extern "C" char igFieldChangeView_className[];
extern "C" void igFieldChangeView_Register(void);
extern "C" void thunk_igFieldChangeView_GetMetaObject(void);
extern "C" int FUN_002beca0(...);
extern "C" int DAT_004d0700[4];
extern "C" int DAT_004d0708[4];
extern "C" int DAT_004d0710[4];
extern "C" int DAT_004d0718[4];
extern "C" int DAT_0058c550[4];
extern "C" void igFieldChangeView_InitFields(void);
extern "C" int DAT_0058c568[4];
extern "C" int FUN_00451050(void);
extern "C" igMetaObject *g_igEventReceiverOrderedList_metaObject[4];
extern "C" igMetaObject *igEventReceiverOrderedList_GetMetaObject(void);
extern "C" int DAT_00541910[4];
union U_4510f0 { int vt; char b[32]; };
extern "C" int igEventReceiverOrderedList_GetVTable(void);
extern "C" int DAT_00541970[4];
extern "C" int **FUN_00451160(int **arg0, long long arg1);
extern "C" void igEventReceiverOrderedList_EnsureRegistered(void);
extern "C" char g_igEventReceiverOrderedList_callbackList[];
extern "C" char igEventReceiverOrderedList_className[];
extern "C" void igEventReceiverOrderedList_Register(void);
extern "C" void thunk_igEventReceiverOrderedList_GetMetaObject(void);
extern "C" igMetaObject *g_igEventReceiver_metaObject[4];
extern "C" igMetaObject *igEventReceiver_GetMetaObject(void);
struct Obj_4512e0 { int *vt; char pad[4]; };
extern "C" int DAT_0052cce0[4];
extern "C" int igEventReceiver_GetVTable(void);
extern "C" void igEventReceiver_EnsureRegistered(void);
extern "C" char igEventReceiver_className[];
extern "C" void igEventReceiver_Register(void);
extern "C" void thunk_igEventReceiver_GetMetaObject(void);
extern "C" int DAT_0058c578[4];
extern "C" int FUN_004513b0(void);
extern "C" igMetaObject *g_igEventDispatcher_metaObject[4];
extern "C" igMetaObject *igEventDispatcher_GetMetaObject(void);
extern "C" int DAT_00524da0[4];
extern "C" int DAT_005413d0[4];
union U_451450 { int vt; int w[5]; char b[20]; };
extern "C" int igEventDispatcher_GetVTable(void);
extern "C" void igEventDispatcher_EnsureRegistered(void);
extern "C" char igInterfaceManager_Register[];
extern "C" char igInterfaceManager_GetPublishedMetaObject[];
extern "C" char g_igEventDispatcher_callbackList[];
extern "C" char igEventDispatcher_className[];
extern "C" void igEventDispatcher_Register(void);
extern "C" void thunk_igEventDispatcher_GetMetaObject(void);
extern "C" int FUN_00146660(...);
extern "C" int DAT_004d0738[4];
extern "C" int DAT_004d0740[4];
extern "C" int DAT_004d0748[4];
extern "C" int DAT_004d0750[4];
extern "C" void igEventDispatcher_InitFields(void);
extern "C" int DAT_0058c590[4];
extern "C" int FUN_004516e0(void);
extern "C" igMetaObject *g_igDefaultAspect_metaObject[4];
extern "C" igMetaObject *igDefaultAspect_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int DAT_00541480[4];
struct Obj_451780 {
    int *vt; int w0[9]; T *ref; int w1[1]; 
    inline void release() {
        T **self = &ref;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" int igDefaultAspect_GetVTable(void);
extern "C" void igDefaultAspect_EnsureRegistered(void);
extern "C" char igGuiComponentAspect_GetPublishedMetaObject[];
extern "C" char g_igDefaultAspect_callbackList[];
extern "C" char igDefaultAspect_className[];
extern "C" void igDefaultAspect_Register(void);
extern "C" void thunk_igDefaultAspect_GetMetaObject(void);
extern "C" int DAT_004d0760[4];
extern "C" int DAT_004d0768[4];
extern "C" int DAT_004d0770[4];
extern "C" int DAT_004d0778[4];
extern "C" void igDefaultAspect_InitFields(void);
extern "C" int DAT_0058c5a0[4];
extern "C" int FUN_00451950(void);
extern "C" igMetaObject *g_igDefaultAspectElementList_metaObject[4];
extern "C" igMetaObject *igDefaultAspectElementList_GetMetaObject(void);
extern "C" int DAT_005418a0[4];
extern "C" int igDefaultAspectElementList_GetVTable(void);
extern "C" void igDefaultAspectElementList_EnsureRegistered(void);
extern "C" char g_igDefaultAspectElementList_callbackList[];
extern "C" char igDefaultAspectElementList_className[];
extern "C" void igDefaultAspectElementList_Register(void);
extern "C" void thunk_igDefaultAspectElementList_GetMetaObject(void);
extern "C" int igMetaEnum_Create(...);
extern "C" int DAT_004d0790[4];
extern "C" int DAT_004d07a0[4];
extern "C" int DAT_0051e648[4];
extern "C" int DAT_0058c5a8[4];
extern "C" int FUN_00451ac0(void);
extern "C" igMetaObject *g_igDefaultAspectElement_metaObject[4];
extern "C" igMetaObject *igDefaultAspectElement_GetMetaObject(void);
extern "C" int StringChunk_ReleaseHeader(...);
union U_451b70 { int vt; int w[5]; void *p[5]; char b[20]; };
struct Rc { int vt; int rc; };
extern "C" int DAT_00541840[4];
extern "C" int igDefaultAspectElement_GetVTable(void);
extern "C" void igDefaultAspectElement_EnsureRegistered(void);
extern "C" char g_igDefaultAspectElement_callbackList[];
extern "C" char igDefaultAspectElement_className[];
extern "C" void igDefaultAspectElement_Register(void);
extern "C" void thunk_igDefaultAspectElement_GetMetaObject(void);
extern "C" int DAT_004d07c0[4];
extern "C" int DAT_004d07e0[4];
extern "C" int DAT_004d0800[4];
extern "C" int DAT_004d0820[4];
extern "C" int DAT_004d0838[4];
extern "C" int DAT_0058c5b0[4];
extern "C" void igDefaultAspectElement_InitFields(void);
extern "C" int DAT_0058c5e8[4];
extern "C" int FUN_00451e40(void);
extern "C" igMetaObject *g_igOnOffColorChanger_metaObject[4];
extern "C" igMetaObject *igOnOffColorChanger_GetMetaObject(void);
struct Obj_451ee0 { int *vt; char pad[92]; };
extern "C" int DAT_005414f0[4];
extern "C" int igOnOffColorChanger_GetVTable(void);
extern "C" void igOnOffColorChanger_RunStaticInit(void);
extern "C" char igBasicColorChanger_GetPublishedMetaObject[];
extern "C" char igOnOffColorChanger_className[];
extern "C" void igOnOffColorChanger_Register(void);
extern "C" void thunk_igOnOffColorChanger_GetMetaObject(void);
extern "C" int DAT_0058c5f0[4];
extern "C" int FUN_00451fb0(void);
extern "C" int FUN_00451fc0(void);
extern "C" igMetaObject *g_igBasicColorChanger_metaObject[4];
extern "C" igMetaObject *igBasicColorChanger_GetMetaObject(void);
struct Obj_452060 { int *vt; char pad[92]; };
extern "C" int DAT_00541550[4];
extern "C" int igBasicColorChanger_GetVTable(void);
extern "C" void igBasicColorChanger_RunStaticInit(void);
extern "C" char igColorChanger_GetPublishedMetaObject[];
extern "C" char igBasicColorChanger_className[];
extern "C" void igBasicColorChanger_Register(void);
extern "C" void thunk_igBasicColorChanger_GetMetaObject(void);
extern "C" int DAT_0058c608[4];
extern "C" int FUN_00452130(void);
extern "C" int DAT_004d0840[4];
extern "C" int DAT_004d0848[4];
extern "C" int DAT_004d0850[4];
extern "C" int DAT_004d0858[4];
extern "C" void igBasicColorChanger_InitFields(void);
extern "C" int FUN_004521d0(void);
extern "C" igMetaObject *g_igColorChanger_metaObject[4];
extern "C" igMetaObject *igColorChanger_GetMetaObject(void);
struct Obj_452270 { int *vt; char pad[4]; };
extern "C" int DAT_005415b0[4];
extern "C" int igColorChanger_GetVTable(void);
extern "C" void igColorChanger_RunStaticInit(void);
extern "C" char igColorChanger_className[];
extern "C" void igColorChanger_Register(void);
extern "C" void thunk_igColorChanger_GetMetaObject(void);
extern "C" int DAT_0058c610[4];
extern "C" int FUN_00452340(void);
extern "C" igMetaObject *g_igBoxComponent_metaObject[4];
extern "C" igMetaObject *igBoxComponent_GetMetaObject(void);
struct F { int *vt; int w[11]; };
extern "C" int DAT_005417e0[4];
extern "C" int igBoxComponent_GetVTable(void);
extern "C" void igBoxComponent_RunStaticInit(void);
extern "C" char igGuiComponent_GetPublishedMetaObject[];
extern "C" char igBoxComponent_className[];
extern "C" void igBoxComponent_Register(void);
extern "C" void thunk_igBoxComponent_GetMetaObject(void);
extern "C" int FUN_004524e0(void);
extern "C" int DAT_0058c620[4];
extern "C" int FUN_004524f0(void);
extern "C" igMetaObject *g_igBitmapFont_metaObject[4];
extern "C" igMetaObject *igBitmapFont_GetMetaObject(void);
struct Obj_452590 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int FUN_0019aa10(...);
extern "C" int FUN_003619a0(...);
extern "C" int FUN_00361a20(...);
extern "C" int DAT_00541610[4];
extern "C" int igBitmapFont_GetVTable(void);
extern "C" void igBitmapFont_RunStaticInit(void);
extern "C" char igFont_GetPublishedMetaObject[];
extern "C" char g_igBitmapFont_callbackList[];
extern "C" char igBitmapFont_className[];
extern "C" void igBitmapFont_Register(void);
extern "C" void thunk_igBitmapFont_GetMetaObject(void);
extern "C" int FUN_004526c0(void);
extern "C" int FUN_00132850(...);
extern "C" int DAT_004d0870[4];
extern "C" int DAT_004d0878[4];
extern "C" int DAT_004d0880[4];
extern "C" int DAT_004d0888[4];
extern "C" void igBitmapFont_InitFields(void);
extern "C" int DAT_0058c638[4];
extern "C" int FUN_00452790(void);
extern "C" igMetaObject *g_igCharMetricsList_metaObject[4];
extern "C" igMetaObject *igCharMetricsList_GetMetaObject(void);
typedef struct { int *vt; int pad[7]; } Obj_452830;
extern "C" int DAT_00541780[4];
extern "C" int igCharMetricsList_GetVTable(void);
extern "C" void igCharMetricsList_RunStaticInit(void);
extern "C" char igDataList_GetPublishedMetaObject[];
extern "C" char igDataList_Register[];
extern "C" char igCharMetricsList_className[];
extern "C" void igCharMetricsList_Register(void);
extern "C" void thunk_igCharMetricsList_GetMetaObject(void);
extern "C" int ObjectPointerList_FindIndex(...);
extern "C" int igMetaObject_FinalizeAndReplaceField(...);
extern "C" void **igMetaObject_FindFieldByName(...);
extern "C" int DAT_0051e798[4];
extern "C" int DAT_0058c640[4];
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" void FUN_00452900(void);
extern "C" igMetaObject *g_igCharMetricsMetaField_metaObject[4];
extern "C" igMetaObject *igCharMetricsMetaField_GetMetaObject(void);
extern "C" int igMetaField_Init(...);
extern "C" int DAT_0052f230[4];
extern "C" int DAT_00531740[4];
extern "C" int DAT_00541680[4];
union U_452a10 { int vt; char b[64]; };
extern "C" int igCharMetricsMetaField_GetVTable(void);
extern "C" void igCharMetricsMetaField_RunStaticInit(void);
extern "C" char igCompoundMetaField_GetPublishedMetaObject[];
extern "C" char igCompoundMetaField_Register[];
extern "C" char g_igCharMetricsMetaField_callbackList[];
extern "C" char igCharMetricsMetaField_className[];
extern "C" void igCharMetricsMetaField_Register(void);
extern "C" void thunk_igCharMetricsMetaField_GetMetaObject(void);
extern "C" void *FUN_002fc250(...);
extern "C" int MetaRefList_AppendRetained(...);
extern "C" int igMetaField_FinalizeDescriptor(...);
extern "C" int DAT_0058c648[4];
extern "C" void * DAT_0058c650[4];
extern "C" void FUN_00452b70(void);
extern "C" int FUN_00452c40(void);
extern "C" int Gap__Gui__igCharMetricsMetaField__vfunc_25(void);
extern "C" void Gap__Gui__igCharMetricsMetaField__vfunc_11(void *arg0);
extern "C" void *FUN_00187b50(...);
extern "C" void *FUN_002b5fe0(...);
extern "C" void *FUN_002c45f0(...);
extern "C" int FUN_002eb010(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int StringPool_Construct(...);
extern "C" void *StringPool_Intern(...);
extern "C" int igMetaField_SetFieldName(...);
extern "C" int DAT_0051e7b8[4];
extern "C" int DAT_0051e7c8[4];
extern "C" int DAT_0051e7d0[4];
extern "C" int DAT_0051e7d8[4];
extern "C" int DAT_0051e7e0[4];
extern "C" int DAT_0051e7f0[4];
extern "C" int DAT_00586f20[4];
extern "C" void FUN_00452ca0(int arg0);
extern "C" int DAT_0058c658[4];
extern "C" int FUN_00453250(void);
extern "C" igMetaObject *g_igAction_metaObject[4];
extern "C" igMetaObject *igAction_GetMetaObject(void);
extern "C" void igAction_RunStaticInit(void);
extern "C" char igAction_className[];
extern "C" void igAction_Register(void);
extern "C" void thunk_igAction_GetMetaObject(void);
extern "C" int FUN_00453370(unsigned short *arg0, unsigned short *arg1);
extern "C" int Gap__Bec__beFontImage__vfunc_23(beFontImage *arg0, int arg1);
extern "C" float Gap__Bec__beFontImage__vfunc_24(beFontImage *arg0, int arg1);
/* The compare is inverted for the at-register temporary. */
struct GlyphPos { float x; float y; };
struct GlyphMetricsRecord { char pad[4]; float f4; };
/* Glyph-metrics list header: the record buffer pointer is at +16. */
struct GlyphMetricsList { char pad[16]; char *f16; };
struct GlyphVertexBuffer { char pad[12]; int f12; };
extern "C" void Gap__Bec__beFontImage__vfunc_21(beFontImage *arg0, struct GlyphVertexBuffer *arg1, char *arg2);
/* The compare is inverted for the at-register temporary. */
struct V2 { float x; float y; };
struct TextLayoutBuffer { char pad[12]; int f12; };
extern "C" void Gap__Bec__beFontImage__vfunc_22(beFontImage *arg0, struct TextLayoutBuffer *arg1, unsigned short *arg2);
struct V { float x; float y; int z; };
struct P { float x; float y; };
struct R_4535d0 { char pad0[8]; float f8; float f12; float f16; float f20; float f24; float f28; float f32; float f36; };
class DW4VC_116_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int, V *); };
class DW4VC_200_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int vX(int, int, void *); };
extern "C" void FUN_004535d0(beFontImage *arg0, DW4VC_116_2 *arg1, int arg2, P *arg3, R_4535d0 *arg4);
extern "C" int List_BinarySearch(...);
struct K { short key; char pad[38]; };
extern "C" int FUN_00453830(beFontImage *arg0, int arg1);
extern "C" void *FUN_00131390(int);
extern "C" void *FUN_00139600(int);
extern "C" int Gap__Core__igObject__vfunc_11(...);
extern "C" int igObject_GetAllocator(...);
class Layer : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setEnabled(int);
  };
class FillLayer : public Layer {};
class OutlineLayer : public Layer {};
struct FontImage { char pad[20]; int layers; int state; char pad3[4]; int base; };
extern "C" void Gap__Bec__beFontImage__vfunc_11(FontImage *self, int enable);
extern "C" void FUN_00453980(int arg0, int arg1);
extern "C" void FUN_00453a20(void *arg0, int arg1);
extern "C" float DAT_004e1170[4];
extern "C" int *Gap__Gui__igColorChanger__vfunc_23(void);
extern "C" void FUN_00453a40(igBasicColorChanger *arg0, int arg1, int arg2, int arg3, void *arg4);
extern "C" int Gap__Gui__igBasicColorChanger__vfunc_23(int arg0, void *arg1);
struct OnOffColorState { unsigned char pad[12]; bool enabled; bool on; unsigned char pad2; bool hilite; unsigned char pad3[20]; bool current; };
extern "C" int Gap__Gui__igOnOffColorChanger__vfunc_23(int arg0, OnOffColorState *s);
extern "C" void thunk_FUN_00453a40(igBasicColorChanger *arg0, int arg1, int arg2, int arg3, void *arg4);
typedef struct B { char p[12]; float x, y, z; } B;
typedef struct A { char p[8]; B *b; char q[12]; float dx, dy; } A;
extern "C" void FUN_00453b90(float *out, A *a);
extern "C" int FUN_001c5d10(...);
extern "C" int FUN_00453e70(...);
extern "C" void Gap__Gui__igDefaultAspect__vfunc_25(igDefaultAspect *arg0);
extern "C" int FUN_001c5eb0(...);
extern "C" float DAT_004e1058[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" int DAT_0058c468[4];
typedef struct R_453f70 { int w0; int refs; } R_453f70;
typedef struct T_453f70 { char pad[16]; float f16; float f20; float f24; } T_453f70;
typedef struct L { char pad[8]; int count; } L;
typedef struct A_453f70 { char pad[8]; T_453f70 *f8; int f12; char pad16[24]; L *f40; } A_453f70;
extern "C" void Gap__Gui__igDefaultAspect__vfunc_26(A_453f70 *arg0);
struct S_454050 { char pad[8]; int f8; };
extern "C" int DAT_0058c290[4];
extern "C" int DAT_0058c448[4];
extern "C" int DAT_0058c450[4];
extern "C" int DAT_0058c460[4];
extern "C" void Gap__Gui__igDefaultAspect__vfunc_27(void *arg0, struct S_454050 *arg1);
class V92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual float *vX(int); };
class V96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); char pad[20]; float f24; float f28; float f32; float f36; };
struct E { char pad[8]; V96 *f8; V92 *f12; };
struct L_4540d0 { char pad[8]; int count; char pad1[4]; E **data; };
struct S_4540d0 { char pad[8]; int f8; char pad1[28]; L_4540d0 *f40; };
extern "C" void FUN_004540d0(S_4540d0 *arg0);
extern "C" int FUN_00453be0(...);
extern "C" void FUN_00454180(void *arg0);
class C22 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int *); };
class C30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int *, int *); };
class C28 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void vX(int *, int, int); };
extern "C" void FUN_004541f0(int *arg0, int *arg1);
extern "C" int FUN_002d6f50(...);
extern "C" void FUN_00454290(void *arg0, int arg1);
extern "C" int FUN_002d7750(...);
typedef struct Obj_4542a0 { char pad[12]; int f12; } Obj_4542a0;
extern "C" void FUN_004542a0(Obj_4542a0 *arg0, int arg1);
extern "C" int FUN_004542d0(int *p);
typedef struct S0 { char pad12[12]; int fC; } S0;
extern "C" int FUN_002d7760(...);
extern "C" void FUN_004542e0(S0 *arg0, int arg1, int arg2);
class VP {
public:
    virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();
    virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();
    virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual void d23();
    virtual void d24();virtual void d25();virtual void d26();virtual void d27();virtual void d28();virtual void d29();
    virtual void getSize(int *, int *);
};
class Item {
public:
    virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();
    virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();
    virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();
    virtual int hit(float, float);
};
struct Mid { char p0[8]; int count; char p12[4]; Item **items; };
struct Mid2 { char p0[8]; Mid *m; };
struct Owner { char p0[12]; Mid2 *m2; };
struct Cur {
    char p0[12]; short x; short y; VP *vp; unsigned char valid; char pad[3]; float nx; float ny;
    void Update() {
        int w, h;
        vp->getSize(&w, &h);
        nx = 2.0f * ((float)x / (float)w - 0.5f);
        ny = 2.0f * ((float)y / (float)h - 0.5f);
        valid = 1;
    }
    float GetX() { if (!valid) Update(); return nx; }
    float GetY() { if (!valid) Update(); return ny; }
};
extern "C" void Gap__Gui__igEventDispatcher__vfunc_26(Owner *o, int unused, Cur *c);
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();  virtual int vX(int, int); };
struct L_4544d0 { char pad8[8]; int cnt; char pad[4]; VC **arr; };
struct M { char pad8[8]; L_4544d0 *list; };
struct S_4544d0 { char pad12[12]; M *m; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_27(S_4544d0 *arg0, int arg1, int arg2, int arg3);
class VC_454570 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned char vX(int, int); };
struct L_454570 { char pad[8]; int count; char pad2[4]; VC_454570 **data; };
struct M_454570 { char pad[8]; L_454570 *list; };
struct S_454570 { char pad[12]; M_454570 *m; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_28(S_454570 *arg0, int a1, int a2, int arg3);
class V132 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int, int); };
struct L_454610 { char p0[8]; int count; char p1[4]; V132 **items; };
struct M_454610 { char p0[8]; L_454610 *list; };
struct O_454610 { char p0[12]; M_454610 *m; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_29(O_454610 *arg0, int arg1, int arg2, int arg3);
class X { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int); };
struct L2 { char pad8[8]; int f8; char pad12[4]; X **f16; };
struct L1 { char pad8[8]; L2 *f8; };
struct T_4546c0 { char pad12[12]; L1 *f12; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_30(T_4546c0 *arg0, int arg1, int arg2, int arg3);
class V136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(); };
class V104 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vY(); };
struct L_454770 { char p0[8]; int count; char p1[4]; V136 **items; };
struct M_454770 { char p0[8]; L_454770 *list; };
struct O_454770 { char p0[12]; M_454770 *m; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_31(O_454770 *arg0, V104 *arg1);
extern "C" void FUN_002ed5c0(void *);
struct K_454820 { int p; K_454820(int x) { p = x; } ~K_454820() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
class Elem { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual int vX(int, int, float, float);
};
struct Finder {
    static int Find(igDataList *l, K_454820 &key) {
        int n = l->_count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == ((int *)l->_data)[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" void Gap__Gui__igEventDispatcher__vfunc_32(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f0, float f1);
struct K_454930 { int p; K_454930(int x) { p = x; } ~K_454930() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
class Lis { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual unsigned char v108(int, int, int);  };
struct Finder_454930 {
    static int Find(igDataList *l, K_454930 &key) {
        int n = l->_count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == ((int *)l->_data)[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" void Gap__Gui__igEventDispatcher__vfunc_33(igEventDispatcher *arg0, int arg1, int arg2, int arg3);
class EventReceiver {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual int onKeyEvent(int, int, int);
    virtual void d26();
    virtual unsigned char onAxisEvent(int, int, float);
    virtual void d28();
    virtual unsigned char onButtonEvent(int, int);
};
struct DispatchKey;
struct ReceiverHolder { char pad[8]; igTDataList<EventReceiver *> *list; };
struct DispatchKeyHolder { char pad[8]; igTDataList<DispatchKey *> *list; };
struct EventDispatcherView { char pad[12]; ReceiverHolder *receivers; DispatchKeyHolder *keys; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_34(EventDispatcherView *self, int, DispatchKey *key, int arg3);
struct K_454b30 { int p; K_454b30(int x) { p = x; } ~K_454b30() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
class Lis_454b30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual unsigned char v112(int, int, float);  };
struct IList { char pad[8]; int count; char pad2[4]; int *data; };
struct List { char pad[8]; int n; char pad2[4]; Lis_454b30 **data; };
struct Hold { char pad[8]; IList *l; };
struct Hold2 { char pad[8]; List *l; };
struct Finder_454b30 {
    static int Find(IList *l, K_454b30 &key) {
        int n = l->count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == l->data[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" void Gap__Gui__igEventDispatcher__vfunc_35(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f);
struct K_454c30 { int p; K_454c30(int x) { p = x; } ~K_454c30() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
class Lis_454c30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual unsigned char v120(int, int, float);  };
struct Finder_454c30 {
    static int Find(igControllerList *l, K_454c30 &key) {
        int n = l->_count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == ((int *)l->_data)[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" void Gap__Gui__igEventDispatcher__vfunc_39(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f);
extern "C" void Gap__Gui__igEventDispatcher__vfunc_38(EventDispatcherView *self, int, DispatchKey *key, int arg3, float f);
struct K_454e30 { int p; K_454e30(int x) { p = x; } ~K_454e30() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
class Lis_454e30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual unsigned char v124(int, int);  };
struct Finder_454e30 {
    static int Find(igControllerList *l, K_454e30 &key) {
        int n = l->_count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == ((int *)l->_data)[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" void Gap__Gui__igEventDispatcher__vfunc_36(igEventDispatcher *arg0, int arg1, int arg2);
extern "C" void Gap__Gui__igEventDispatcher__vfunc_37(EventDispatcherView *self, int, DispatchKey *key);
class E_455010 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual unsigned char vX(int, int); };
struct L2_455010 { int p0; int p1; int n; int p3; E_455010 **arr; };
struct L1_455010 { int p0; int p1; L2_455010 *l2; };
struct O_455010 { int vt; int p1; int p2; L1_455010 *f12; };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_40(O_455010 *arg0, int arg1, int arg2);
class A_4550b0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int, int); };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_41(int *arg0, int arg1, int arg2);
extern "C" void Gap__Gui__igFieldChangeView__vfunc_24(void *arg0, void *arg1);
extern "C" int FUN_002fd150(...);
struct S_4551a0 { char pad[8]; int a; int pad2; int b; };
extern "C" void FUN_004551a0(struct S_4551a0 *arg0, int arg1, int arg2);
struct Rc_4551f0 { int vt; int rc; int p8; int f12; int f16; };
struct Ref_4551f0 {
    Rc_4551f0 *p;
    ~Ref_4551f0() {
        Rc_4551f0 *object = p;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct A_4551f0 { char pad8[8]; int f8; };
extern "C" void FUN_004551f0(void *arg0v, int arg1, void *arg2v);
extern "C" void FUN_004552e0(int *arg0, int *arg1);
class VC_455370 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(long long); };
extern "C" int FUN_00455370(VC_455370 *arg0, char *arg1);
class VC100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
extern "C" int FUN_004553e0(void **arg0, unsigned short *arg1);
extern "C" void Gap__Gui__igGuiComponent__vfunc_13(void *arg0);
typedef struct C { char pad12[12]; int f0c; } C;
typedef struct B_455470 { char pad32[32]; int f20; } B_455470;
typedef struct A_455470 { char pad12[12]; int f0c; B_455470 *f10; C *f14; char pad24[8]; unsigned char f20; } A_455470;
extern "C" void FUN_00455470(A_455470 *arg0);
extern "C" int Gap__Core__igObject__vfunc_08__002ff0f0(...);
extern "C" void Gap__Gui__igGuiComponent__vfunc_10(void *arg0);
extern "C" int FUN_001c59e0(...);
extern "C" void *igObject_IsKindOf(...);
struct O_455510 {
    char p[32]; int v;
    static O_455510 *cast(O_455510 *o) {
        if (o != 0 && igObject_IsKindOf(o, DAT_0058c428[0]) != 0) return o;
        return 0;
    }
};
struct B_455510 { char p[16]; O_455510 **arr; };
struct A_455510 { char p[8]; B_455510 *b; };
extern "C" int FUN_00455510(A_455510 *arg0);
class igGuiComponentControllerView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual void *vfunc_23(void *component, void *context);
};
class igGuiComponentView {
public:
    int _vtable;
    unsigned int _refCount;
    char _pad8[4];
    igGuiComponentControllerView *_controller;
};
extern "C" void *FUN_004555c0(igGuiComponentView *self, void *component, void *context);
extern "C" int FUN_004555e0(void *arg0);
extern "C" void FUN_004555f0(int *p, unsigned char value);
extern "C" void FUN_00455600(int *p, unsigned char value);
extern "C" void FUN_00455610(int *p, unsigned char value);
extern "C" unsigned char FUN_00455620(void *arg0);
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
class DW4VC_104_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
class DW4VC_108_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int); };
extern "C" void Gap__Gui__igDefaultAspect__vfunc_24(igDefaultAspect *arg0, int *arg1);
extern "C" void Gap__Gui__igGuiComponentController__vfunc_23(igGuiComponentController *self, int model);
extern "C" int DAT_0058c458[4];
class DW4VC_104_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int, int); };
class DW4VC_108_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int); };
class DW4VC_112_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int, int); };
class DW4VC_116_2_4556e0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int, int); };
class DW4VC_120_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(int, int); };
class DW4VC_124_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(int, int); };
class DW4VC_128_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int); };
class DW4VC_132_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int, int); };
extern "C" void Gap__Gui__igGuiComponentController__vfunc_24(igGuiComponentController *arg0, void *arg1);
extern "C" void Gap__Gui__igGuiComponentController__vfunc_33(void);
extern "C" void Gap__Gui__igGuiComponentController__vfunc_32(void);
extern "C" void Gap__Gui__igGuiComponentController__vfunc_31(void);
extern "C" void Gap__Gui__igGuiComponentController__vfunc_30(void);
extern "C" void Gap__Gui__igGuiComponentController__vfunc_29(void);
extern "C" void Gap__Gui__igGuiComponentController__vfunc_28(void);
extern "C" void Gap__Gui__igGuiComponentController__vfunc_27(void);
extern "C" void Gap__Gui__igGuiComponentController__vfunc_26(void);
extern "C" int Gap__Gui__igGuiComponentController__vfunc_25(void);
struct S_4558b0 { char pad[13]; unsigned char b; };
extern "C" void FUN_004558b0(struct S_4558b0 *arg0, unsigned char arg1);
struct S_455900 { char pad[14]; unsigned char f; };
extern "C" void FUN_00455900(struct S_455900 *arg0, unsigned char arg1);
typedef struct S_455950 { char pad[15]; unsigned char b; } S_455950;
extern "C" void FUN_00455950(S_455950 *arg0, unsigned char arg1);
extern "C" int DAT_0058c470[4];
struct S_4559a0 { char pad[28]; unsigned char b; };
extern "C" void FUN_004559a0(struct S_4559a0 *arg0, unsigned char arg1);
struct Vec3 { int x; int y; int z; };
struct Node : igObject { int fc_pad; igObject *child; };
extern "C" igObject *FUN_0018a660(int);
extern "C" int FUN_001900d0(igObject *, Vec3 *);
extern "C" int FUN_001d3550(Node *);
extern "C" void Gap__Gui__igGuiComponentNode__vfunc_13(Node *self);
extern "C" int DAT_0058c678[4];
extern "C" int FUN_00455ad0(int arg0, int arg1, int arg2);
extern "C" int Matrix44_SetTranslation(...);
extern "C" int DAT_0058c3e8[4];
extern "C" void Gap__Gui__igGuiSystemModel__vfunc_13(int arg0, int arg1);
struct A_455b90 { char pad[8]; int x; int y; };
struct T_455b90 { char pad[12]; float w; float h; };
extern "C" int FUN_00191860(void *, float, float, float, float, float, float);
extern "C" int DAT_0058c3d0[4];
extern "C" int DAT_0058c3f0[4];
extern "C" void Gap__Gui__igWindowSizeObserver__vfunc_24(void *arg0, int *arg1);
struct ObserverIntListView { int w0; int w4; int cnt; int cap; int *data; };
struct ObserverEventView : igObject { int w8; int a; ObserverIntListView *list; };
struct ObserverModelView { char pad[40]; igObject *ref; int flags; int fn; };
struct MousePosObserverView { char pad[16]; ObserverModelView *m; int f20; };
extern "C" ObserverEventView *FUN_0019e680(...);
extern "C" void Gap__Gui__igMousePosObserver__vfunc_13(MousePosObserverView *self);
struct Obj_455f50 : public igObject { };
struct Y { char pad[8]; int f8; char pad2[8]; float f20; };
struct Z { char pad[24]; float f24; unsigned char f28; char pad2[3]; Obj_455f50 *f32; };
extern "C" Obj_455f50 *FUN_0019f630(...);
extern "C" int FUN_001c5790(...);
extern "C" void FUN_00455f50(Z *arg0, Y *arg1);
extern "C" int FUN_001ce970(void *);
extern "C" int FUN_0018d2b0(void *, void *, void *);
extern "C" int FUN_0018d360(void *, void *);
extern "C" int DAT_0058c410[4];
/* vtable-call shim for the intersect traversal (slot 23 = vtable offset 100); not a data layout */
struct IntersectTraversalCalls { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(int); };
extern "C" void FUN_00456050(igMousePosObserver *a, igGuiSystemModel *b);
typedef struct N { int w0, w4, w8, wC; int f10; int f14; struct N *f18; } N;
extern "C" int FUN_00456540(int arg0, N *arg1, N *arg2, unsigned char arg3);
extern "C" void *FUN_004565c0(int arg0, void *arg1);
extern "C" int FUN_001b6ee0(void *, void *);
extern "C" int Matrix44_Copy(void *, void *);
class Obj_456610 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int); };
extern "C" void Gap__Gui__igGuiSystemRenderer__vfunc_23(int *arg0);
extern "C" void Gap__Gui__igGuiSystemRenderer__vfunc_24(void);
class C29 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void vX(); };
class C23 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void vX(int); };
class C28_456670 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual igObject *vX(); };
extern "C" void Gap__Gui__igGuiSystemRenderer__vfunc_25(int *arg0);
class CA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void vX(int, int); };
class CB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int); };
extern "C" void Gap__Gui__igGuiSystemRenderer__vfunc_26(char *arg0);
struct R_456780 : public igObject { int w8; int wc; };
struct X_456780 { char p[12]; R_456780 *f12; R_456780 *f16; };
struct A_456780 { char p[8]; X_456780 *f8; int f12; int f16; R_456780 *f20; char q[4]; int f28; };
extern "C" void Gap__Gui__igGuiSystem__vfunc_13(A_456780 *self);
class T_4569c0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX();
  char pad[20]; float f24; float f28; float f32; float f36; };
struct M_4569c0 { int p0; int p1; T_4569c0 *t; };
struct O_4569c0 { char pad[24]; M_4569c0 *m; char pad2[4]; char f32; };
extern "C" float DAT_004e1174[4];
extern "C" float DAT_004e1178[4];
extern "C" float DAT_004e117c[4];
extern "C" void FUN_004569c0(O_4569c0 *arg0, int arg1);
typedef struct Rc_456a60 { int vt; int rc; int p8; } Rc_456a60;
typedef struct Q { char pad8[8]; int f8; } Q;
typedef struct P_456a60 { char pad28[28]; Q *f28; } P_456a60;
typedef struct A_456a60 { char pad12[12]; int f12; char pad16[8]; Rc_456a60 *f24; P_456a60 *f28; unsigned char f32; } A_456a60;
typedef struct R_456a60 { char pad8[8]; Q *f8; } R_456a60;
typedef struct V3 { int a; int b; int c; int pad[4]; } V3;
extern "C" int DAT_0058c3d8[4];
extern "C" void FUN_00456a60(A_456a60 *arg0, R_456a60 *arg1);
class Obj_456b80 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void vX(void *); };
struct P_456b80 { char pad[12]; float x; float y; };
extern "C" void FUN_00456b80(int *arg0, float *arg1);
extern "C" int DAT_0058c408[4];
extern "C" void FUN_00456c20(igGuiSystemModel *arg0, igGuiComponent *arg1);
struct T_456cc0 { int word0; int references; int f8; char pad12[16]; int f28; };
struct LL { char pad8[8]; int f8; };
class VC_456cc0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void v140(int, int); };
struct Obj_456cc0 : VC_456cc0 { char pad4[24]; LL *f28; };
struct P_456cc0 { char pad164[164]; T_456cc0 *f164; };
struct W { char pad12[12]; P_456cc0 *f12; char pad16[4]; Obj_456cc0 *f20; };
extern "C" int DAT_0058c400[4];
extern "C" void FUN_00456cc0(W *arg0, T_456cc0 *arg1);
struct N_456e10 { char pad[24]; struct N_456e10 *f24; };
struct O_456e10 { char pad[12]; struct M_456e10 *f12; };
struct M_456e10 { char pad[164]; void *f164; };
extern "C" void *FUN_00456e10(struct O_456e10 *arg0, struct N_456e10 *arg1, int arg2);
/* The loop test is written `((F(x) != 0) ^ 1)`, which materialises the sltu/xori. */
struct Item_456eb0 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual int test();
};
struct Item2 { char p[12]; Item_456eb0 *f12; };
struct Ctl2 { char p[168]; Item2 *f168; };
struct Ctl { char p[12]; Ctl2 *f12; };
extern "C" void FUN_00456eb0(Ctl *arg0, int arg1);
extern "C" int Gap__Gui__igGuiComponentController__vfunc_34(void);
struct In { char p[160]; unsigned char f160; };
struct Ob { char p[12]; In *f12; };
extern "C" bool Gap__Gui__igGuiSystem__vfunc_23(Ob *arg0, int arg1, int arg2);
extern "C" void FUN_004570a0(void *arg0);
typedef struct B_457100 { char pad20[20]; float f14; float f18; char pad28[132]; unsigned char fa0; char pada1[15]; int fb0; } B_457100;
typedef struct A_457100 { char pad12[12]; B_457100 *fc; } A_457100;
extern "C" int Gap__Gui__igGuiSystem__vfunc_24(A_457100 *arg0, float fparg0, float fparg1);
struct P_457170 { int a, b, c; };
extern "C" int Gap__Gui__igGuiSystem__vfunc_32(int *self, int x, int y);
extern "C" int DAT_0058c420[4];
extern "C" int Gap__Gui__igGuiSystem__vfunc_34(igGuiSystem *arg0);
struct O_457220 { char pad[28]; char f1c; char pad2[131]; unsigned char fa0; char pad3[11]; int fac; };
struct P_457220 { char pad[12]; struct O_457220 *o; };
extern "C" int DAT_0058c3e0[4];
extern "C" int Gap__Gui__igGuiSystem__vfunc_25(struct P_457220 *arg0, int arg1, char arg2);
struct GuiModelView {
    char pad0[160];
    unsigned char enabled;
};
extern "C" bool Gap__Gui__igGuiSystem__vfunc_27(igGuiSystem *system, int device, int key, int pressed);
extern "C" int Gap__Gui__igGuiSystem__vfunc_26(void);
extern "C" void FUN_004573c0(int arg0, int arg1, int arg2);
extern "C" void FUN_004573d0(int arg0, int arg1, int arg2);
struct Entry : igObject { int a; int b; igObject *value; };
struct AttrEntryOwner { char pad[8]; int entries; };
extern "C" void FUN_004573f0(AttrEntryOwner *owner, int a, int b, igObject *value);
typedef struct E_4574f0 { char pad4[4]; int f4; int f8; int f12; } E_4574f0;
typedef struct LST { char pad8[8]; int f8; char pad12[4]; E_4574f0 **f16; } LST;
typedef struct T_4574f0 { char pad8[8]; LST *f8; } T_4574f0;
extern "C" int List_RemoveWordAt(...);
extern "C" void FUN_004574f0(T_4574f0 *arg0, int arg1);
class VC_4575d0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(); };
struct E_4575d0 { char pad8[8]; int f08; char pad12[4]; VC_4575d0 *f10; };
struct B_4575d0 { char pad8[8]; int cnt; char pad2[4]; E_4575d0 **arr; };
extern "C" int Gap__Gui__igHotKeyEventReceiver__vfunc_23(B_4575d0 *arg0, int arg1, int arg2);
class VC_457650 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(); };
struct E_457650 { char pad12[12]; int f0c; VC_457650 *f10; };
struct B_457650 { char pad8[8]; int cnt; char pad2[4]; E_457650 **arr; };
extern "C" int Gap__Gui__igHotKeyEventReceiver__vfunc_27(B_457650 *arg0, int arg1, int arg2, int arg3);
class ContextHandler { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int *out); };
extern "C" void FUN_004576d0(igContext *context, ContextHandler *handler);
class OV { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(void *); };
struct K_4577f0 { void *p; K_4577f0(void *x) { p = x; } ~K_4577f0() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
struct Flags { int a; int b; int c; int d[4]; };
struct Finder_4577f0 {
    static int Find(igObjectList *l, K_4577f0 &key) {
        int n = l->_count;
        void *p = *(void **)&key.p;
        int i = 0;
        for (; i < n; i++) {
            if (p == ((void **)l->_data)[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" void FUN_004577f0(igModel *arg0, OV *arg1);
struct S_4578c0;
class VC_4578c0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(S_4578c0 *); };
struct L_4578c0 { char p[8]; int n; char q[4]; VC_4578c0 **arr; };
struct S_4578c0 { char p[4]; VC_4578c0 *f4; L_4578c0 *f8; };
extern "C" void FUN_004578c0(S_4578c0 *arg0, S_4578c0 *arg1);
struct L_457950 { char pad[8]; int n; int pad2; int *arr; };
struct O_457950 { char pad[8]; struct L_457950 *l; };
extern "C" void Gap__Gui__igModel__vfunc_10(struct O_457950 *arg0);
extern "C" void Gap__Gui__igRadioGroup__vfunc_13(void *arg0);
struct RadioButtonListView { char p[8]; int n; char q[4]; int *arr; };
struct RadioSelectionView { char p[12]; int sel; };
struct RadioGroupView { char p[8]; struct RadioSelectionView *a; char p2[4]; struct RadioButtonListView *b; int f20; int cur; };
extern "C" void FUN_00457a10(struct RadioGroupView *s);
extern "C" int DAT_0058c280[4];
struct K_457ab0 { void *p; K_457ab0(void *x) { p = x; } ~K_457ab0() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
struct Msg { int a; int b; int c; int d; };
struct Finder_457ab0 {
    static int Find(igObjectList *l, K_457ab0 &key) {
        int n = l->_count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == ((void **)l->_data)[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" void FUN_00457ab0(igRadioGroup *arg0, igRadioGroupSelectedObserver *arg1, int arg2);
extern "C" void Gap__Gui__igRadioGroupSelectedObserver__vfunc_24(void *arg0, void *arg1);
extern "C" void Gap__Gui__igOnOffValueObserver__vfunc_24(void *arg0, void *arg1);
struct T_457c40 { char pad[36]; unsigned char b; };
struct S_457c40 { char pad[8]; struct T_457c40 *t; };
extern "C" void FUN_00457c40(struct S_457c40 *arg0, unsigned char arg1);
struct R_457ca0 { int w0; int refs; };
class O_457ca0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void v92(); virtual void v96(); int w4; R_457ca0 *r; };
extern "C" void FUN_00457ca0(O_457ca0 *arg0, R_457ca0 *arg1);
class E_457d60 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int v200(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual int v228(int); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void v732(int); };
struct O_457d60 { int p0; int p1; E_457d60 *f8; int f12; };
extern "C" void Gap__Gui__igClearRenderer__vfunc_23(O_457d60 *arg0);
class igVisualContextView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71();
    virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79();
    virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87();
    virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95();
    virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103();
    virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111();
    virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119();
    virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135();
    virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143();
    virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151();
    virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159();
    virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167();
    virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172();
    virtual void vfunc_173();
    virtual void vfunc_174(unsigned int buffers);
};
class igClearRendererView {
public:
    int _vtable;
    unsigned int _refCount;
    igVisualContextView *_visualContext;
    unsigned int _buffersToClear;
};
extern "C" void Gap__Gui__igClearRenderer__vfunc_26(igClearRendererView *self);
extern "C" void Gap__Gui__igTextElement__vfunc_23(igTextElement *self);
class V168 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int vX(int, char *); };
struct Q_457e10 { char p0[12]; int count; };
struct M_457e10 { char p0[12]; V168 *obj; };
struct O_457e10 { char p0[24]; char buf[1]; char p1[23]; M_457e10 *m; };
extern "C" void Gap__Gui__igTextElement__vfunc_24(O_457e10 *arg0);
typedef struct S0_457e90 { char pad8[8]; int f8; } S0_457e90;
extern "C" void FUN_00457e90(S0_457e90 *arg0, int arg1);
extern "C" void Gap__Bec__beCameraMode__vfunc_08(beCameraMode *self);
extern "C" int Gap__Gui__igTextElement__vfunc_22(void);
extern "C" int Gap__Gui__igClearRenderer__vfunc_22(void);
extern "C" void Gap__Gui__igClearRenderer__vfunc_25(void);
extern "C" void Gap__Gui__igClearRenderer__vfunc_24(void);
extern "C" int Gap__Gui__igOnOffValueObserver__vfunc_22(void);
extern "C" void Gap__Gui__igOnOffValueObserver__vfunc_23(void *arg0, int arg1);
extern "C" int Gap__Gui__igRadioGroupSelectedObserver__vfunc_22(void);
extern "C" void Gap__Gui__igRadioGroupSelectedObserver__vfunc_23(void *arg0, int arg1);
extern "C" int Gap__Gui__igRadioGroup__vfunc_22(void);
extern "C" int Gap__Gui__igModel__vfunc_22(void);
extern "C" int Gap__Gui__igHotKeyEventReceiver__vfunc_22(void);
extern "C" int Gap__Gui__igGuiSystem__vfunc_22(void);
extern "C" int Gap__Gui__igGuiSystemRenderer__vfunc_22(void);
extern "C" int Gap__Gui__igActiveComponentsObserver__vfunc_22(void);
extern "C" void Gap__Gui__igActiveComponentsObserver__vfunc_23(void *arg0, int arg1);
extern "C" int Gap__Gui__igMousePosObserver__vfunc_22(void);
extern "C" void Gap__Gui__igMousePosObserver__vfunc_23(void *arg0, int arg1);
extern "C" int DAT_0058c3c0[4];
extern "C" int Gap__Gui__igWindowSizeObserver__vfunc_22(void);
extern "C" void Gap__Gui__igWindowSizeObserver__vfunc_23(void *arg0, int arg1);
extern "C" int Gap__Gui__igGuiSystemModel__vfunc_22(void);
extern "C" int Gap__Gui__igGuiComponentNode__vfunc_22(void);
extern "C" int Gap__Gui__igGuiComponentController__vfunc_22(void);
extern "C" int Gap__Gui__igGuiComponent__vfunc_22(void);
extern "C" int Gap__Gui__igFieldChangeView__vfunc_22(void);
extern "C" int Gap__Gui__igFieldChangeView__vfunc_23(void);
extern "C" int Gap__Gui__igEventDispatcher__vfunc_22(void);
extern "C" int Gap__Gui__igDefaultAspect__vfunc_22(void);
extern "C" void Gap__Gui__igDefaultAspect__vfunc_23(igDefaultAspect *self, int model);
extern "C" int Gap__Gui__igOnOffColorChanger__vfunc_22(void);
extern "C" int Gap__Gui__igBasicColorChanger__vfunc_22(void);
extern "C" int Gap__Gui__igColorChanger__vfunc_22(void);
extern "C" int Gap__Gui__igBitmapFont__vfunc_22(void);
extern "C" int Gap__Gui__igCharMetricsMetaField__vfunc_22(void);
extern "C" int Gap__Gui__igCharMetricsMetaField__vfunc_23(void);
extern "C" int Gap__Gui__igCharMetricsList__vfunc_22(void);
extern "C" int Gap__Gui__igBoxComponent__vfunc_22(void);
extern "C" int Gap__Gui__igDefaultAspectElement__vfunc_22(void);
extern "C" int Gap__Gui__igDefaultAspectElementList__vfunc_22(void);
extern "C" int Gap__Gui__igEventReceiverOrderedList__vfunc_22(void);
extern "C" int Gap__Gui__igFieldChangeViewList__vfunc_22(void);
extern "C" int Gap__Gui__igFieldSynchronizer__vfunc_22(void);
extern "C" int Gap__Gui__igGuiComponentList__vfunc_22(void);
extern "C" int Gap__Gui__igMouseCursor__vfunc_22(void);
extern "C" int Gap__Gui__igHotKeyBinding__vfunc_22(void);
extern "C" int Gap__Gui__igHotKeyBindingList__vfunc_22(void);
extern "C" int Gap__Gui__igOnOffModel__vfunc_22(void);
extern "C" int Gap__Gui__igRadioGroupModel__vfunc_22(void);
extern "C" int Gap__Gui__igOnOffValueObserverList__vfunc_22(void);
extern "C" int Gap__Gui__igRendererOrderedList__vfunc_22(void);
extern "C" int Gap__Gui__igGuiComponentModel__vfunc_22(void);
extern "C" int FUN_00458310(void);
extern "C" int Gap__Gui__igViewList__vfunc_22(void);
extern "C" int Gap__Gui__igNonRefCountedViewList__vfunc_22(void);
extern "C" int Gap__Gui__igNonRefCountedViewList__vfunc_24(void);
extern "C" int Gap__Gui__igCharMetricsList__vfunc_23(void);
extern "C" int Gap__Gui__igDefaultAspectElementList__vfunc_24(void);
extern "C" int Gap__Gui__igFieldChangeViewList__vfunc_24(void);
extern "C" int Gap__Gui__igHotKeyBindingList__vfunc_24(void);
extern "C" int Gap__Gui__igOnOffValueObserverList__vfunc_24(void);
extern "C" int Gap__Gui__igGuiComponentList__vfunc_24(void);
extern "C" int Gap__Gui__igViewList__vfunc_24(void);
extern "C" int List_Reserve(...);
extern "C" void Gap__Gui__igCharMetricsList__vfunc_18(igCharMetricsList *self);
extern "C" void FUN_00453990(struct FontLayers_453990 *self, int index, struct FontLayerItem_453990 *item);
extern "C" void Gap__Gui__igMousePosObserver__vfunc_24(igMousePosObserver *self, struct GuiMessage_455d80 *msg);
extern "C" void Gap__Gui__igActiveComponentsObserver__vfunc_24(igActiveComponentsObserver *self, struct GuiMessage_455d80 *msg);

void GuiLibrary_MarkRegistered(void) {
    if (g_GuiLibrary_registered == 0) {
        g_GuiLibrary_registered = 1;
    }
}

int FUN_0044b880(void) {
    if (DAT_0058c1b0[0] == 0) {
        DAT_0058c1b0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c1b0[0];
}

igMetaObject *igNonRefCountedViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedViewList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedViewList_EnsureRegistered();
    return g_igNonRefCountedViewList_metaObject[0];
}

int igNonRefCountedViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541f70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igNonRefCountedViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedViewList_Register);
}

void igNonRefCountedViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedViewList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedViewList_GetMetaObject,
        igNonRefCountedViewList_className,
        0x14, /* instance size */
        igNonRefCountedViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedViewList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedViewList_GetMetaObject(void) {
    igNonRefCountedViewList_GetMetaObject();
}

int FUN_0044b9f0(void) {
    if (DAT_0058c1b8[0] == 0) {
        DAT_0058c1b8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c1b8[0];
}

igMetaObject *igViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igViewList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igViewList_EnsureRegistered();
    return g_igViewList_metaObject[0];
}

int igViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541f00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewList_Register);
}

void igViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igViewList_GetMetaObject,
        igViewList_className,
        0x14, /* instance size */
        igViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igViewList_callbackList /* callback list */
    );
}

void thunk_igViewList_GetMetaObject(void) {
    igViewList_GetMetaObject();
}

igMetaObject *igView_GetMetaObject(void)
{
    igMetaObject *g = g_igView_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igView_EnsureRegistered();
    return g_igView_metaObject[0];
}

void igView_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igView_Register);
}

void igView_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igView_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igView_GetMetaObject,
        igView_className,
        0xC, /* instance size */
        0,
        &igView_InitFields,
        0, /* extra callback item */
        g_igView_callbackList /* callback list */
    );
}

void thunk_igView_GetMetaObject(void) {
    igView_GetMetaObject();
}

void igView_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c1c0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cfef8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044d5d0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cff00[0], &DAT_004cff08[0], &DAT_004cff10[0], temp_s2);
}

int FUN_0044bce0(void) {
    if (DAT_0058c1d0[0] == 0) {
        DAT_0058c1d0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c1d0[0];
}

igMetaObject *igTextElement_GetMetaObject(void)
{
    igMetaObject *g = g_igTextElement_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igTextElement_EnsureRegistered();
    return g_igTextElement_metaObject[0];
}

int igTextElement_GetVTable(void) {
    union U u;

    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[10] = 0;
    u.w[0] = (int)(&DAT_00540c10[0]);
    u.w[11] = 0;
    u.w[12] = 0;
    u.w[13] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00540c10[0]);
    StringRef_Destruct_00130720(&u.w[13], -1);
    FUN_001353b0(&u.w[12], -1);
    FUN_0044bf10((void **)&u.w[11], -1);
    FUN_0044be30((igGeometryElement *)u.b, 0);
    return temp_s2;
}

void *FUN_0044be30(igGeometryElement *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_00541e90[0];
        if (&arg0->_sharableAttrs) {
            p = (igObject *)arg0->_sharableAttrs;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->_geometry) {
            p = (igObject *)arg0->_geometry;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void **FUN_0044bf10(void **arg0, long long arg1) {
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

void igTextElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextElement_Register);
}

void igTextElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextElement_metaObject,
        igGeometryElement_Register,
        igGeometryElement_GetPublishedMetaObject,
        thunk_igTextElement_GetMetaObject,
        igTextElement_className,
        0x38, /* instance size */
        igTextElement_GetVTable,
        &igTextElement_InitFields,
        0, /* extra callback item */
        g_igTextElement_callbackList /* callback list */
    );
}

void thunk_igTextElement_GetMetaObject(void) {
    igTextElement_GetMetaObject();
}

int FUN_0044c030(void) {
    return DAT_0058c4e8[0];
}

void igTextElement_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c1d0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cff28[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_004507f0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00137850();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), &DAT_0051dd88[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004cff38[0], &DAT_004cff48[0], &DAT_004cff58[0], temp_s2);
}

void *FUN_0044c110(struct S *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00540e30[0];
        if (&arg0->f8) {
            p = arg0->f8;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

int FUN_0044c1b0(void) {
    return DAT_0058c438[0];
}

void **FUN_0044c1c0(void **arg0, int arg1) {
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

int FUN_0044c240(void) {
    return DAT_0058c480[0];
}

int FUN_0044c250(void) {
    if (DAT_0058c1f0[0] == 0) {
        DAT_0058c1f0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c1f0[0];
}

igMetaObject *igClearRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igClearRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igClearRenderer_EnsureRegistered();
    return g_igClearRenderer_metaObject[0];
}

int igClearRenderer_GetVTable(void) {
    union U_44c2f0 u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0052d060[0];
    u.vt = (int)&DAT_00540c80[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0052d060[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void igClearRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igClearRenderer_Register);
}

void igClearRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igClearRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igClearRenderer_GetMetaObject,
        igClearRenderer_className,
        0x10, /* instance size */
        igClearRenderer_GetVTable,
        &igClearRenderer_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igClearRenderer_GetMetaObject(void) {
    igClearRenderer_GetMetaObject();
}

void igClearRenderer_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c1f0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cff68[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cff70[0], &DAT_004cff78[0], &DAT_004cff80[0], temp_s1);
}

void FUN_0044c490(int arg0) {
    igRendererOrderedList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58C200, arg0);
}

int FUN_0044c4d0(void) {
    if (DAT_0058c200[0] == 0) {
        DAT_0058c200[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c200[0];
}

igMetaObject *igRendererOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igRendererOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRendererOrderedList_EnsureRegistered();
    return g_igRendererOrderedList_metaObject[0];
}

int igRendererOrderedList_GetVTable(void) {
    struct Obj_44c570 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.vt = &DAT_00541d70[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00541d70[0];
    FUN_0044c5e0((int **)&obj, 0);
    return r;
}

int **FUN_0044c5e0(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00541dd0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_0052cc20[0];
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x14), -1);
            FUN_00135430((int **)((char *)arg0 + 0x10), -1);
            FUN_00233590((int **)((char *)arg0 + 0xC), -1);
            FUN_0014aa70((int **)((char *)arg0 + 8), -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void igRendererOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRendererOrderedList_Register);
}

void igRendererOrderedList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRendererOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igRendererOrderedList_GetMetaObject,
        igRendererOrderedList_className,
        0x1C, /* instance size */
        igRendererOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRendererOrderedList_callbackList /* callback list */
    );
}

void thunk_igRendererOrderedList_GetMetaObject(void) {
    igRendererOrderedList_GetMetaObject();
}

igMetaObject *igRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRenderer_EnsureRegistered();
    return g_igRenderer_metaObject[0];
}

void igRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRenderer_Register);
}

void igRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igRenderer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRenderer_GetMetaObject,
        igRenderer_className,
        0xC, /* instance size */
        0,
        &igRenderer_InitFields,
        0, /* extra callback item */
        g_igRenderer_callbackList /* callback list */
    );
}

void thunk_igRenderer_GetMetaObject(void) {
    igRenderer_GetMetaObject();
}

void igRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c208[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cff98[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014a040();
    igMetaObject_NameFields(temp_s0, &DAT_004cffa0[0], &DAT_004cffa8[0], &DAT_004cffb0[0], temp_s2);
}

int FUN_0044c880(void) {
    if (DAT_0058c218[0] == 0) {
        DAT_0058c218[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c218[0];
}

igMetaObject *igOnOffValueObserverList_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffValueObserverList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffValueObserverList_EnsureRegistered();
    return g_igOnOffValueObserverList_metaObject[0];
}

int igOnOffValueObserverList_GetVTable(void) {
    Obj_44c920 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00541d00[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igOnOffValueObserverList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igOnOffValueObserverList_Register);
}

void igOnOffValueObserverList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffValueObserverList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igOnOffValueObserverList_GetMetaObject,
        igOnOffValueObserverList_className,
        0x14, /* instance size */
        igOnOffValueObserverList_GetVTable,
        0,
        0, /* extra callback item */
        g_igOnOffValueObserverList_callbackList /* callback list */
    );
}

void thunk_igOnOffValueObserverList_GetMetaObject(void) {
    igOnOffValueObserverList_GetMetaObject();
}

igMetaObject *igOnOffValueObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffValueObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffValueObserver_EnsureRegistered();
    return g_igOnOffValueObserver_metaObject[0];
}

int igOnOffValueObserver_GetVTable(void) {
    struct Obj_44ca40 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540cf0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igOnOffValueObserver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igOnOffValueObserver_Register);
}

void igOnOffValueObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffValueObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igOnOffValueObserver_GetMetaObject,
        igOnOffValueObserver_className,
        0x10, /* instance size */
        igOnOffValueObserver_GetVTable,
        &igOnOffValueObserver_InitFields,
        0, /* extra callback item */
        g_igOnOffValueObserver_callbackList /* callback list */
    );
}

void thunk_igOnOffValueObserver_GetMetaObject(void) {
    igOnOffValueObserver_GetMetaObject();
}

int FUN_0044cb20(void) {
    return DAT_0058c1c0[0];
}

void igOnOffValueObserver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c220[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cffc8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044cdf0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cffd0[0], &DAT_004cffd8[0], &DAT_004cffe0[0], temp_s2);
}

int FUN_0044cbd0(void) {
    if (DAT_0058c230[0] == 0) {
        DAT_0058c230[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c230[0];
}

igMetaObject *igRadioGroupSelectedObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroupSelectedObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRadioGroupSelectedObserver_EnsureRegistered();
    return g_igRadioGroupSelectedObserver_metaObject[0];
}

int igRadioGroupSelectedObserver_GetVTable(void) {
    struct O o;
    igObject_InitHeader(&o.vt);
    o.vt = DAT_00540d60;
    return *(int *)((char *)&o.vt + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igRadioGroupSelectedObserver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRadioGroupSelectedObserver_Register);
}

void igRadioGroupSelectedObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRadioGroupSelectedObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igRadioGroupSelectedObserver_GetMetaObject,
        igRadioGroupSelectedObserver_className,
        0x10, /* instance size */
        igRadioGroupSelectedObserver_GetVTable,
        &igRadioGroupSelectedObserver_InitFields,
        0, /* extra callback item */
        g_igRadioGroupSelectedObserver_callbackList /* callback list */
    );
}

void thunk_igRadioGroupSelectedObserver_GetMetaObject(void) {
    igRadioGroupSelectedObserver_GetMetaObject();
}

void igRadioGroupSelectedObserver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c230[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cfff0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044cdf0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cfff8[0], &DAT_004d0000[0], &DAT_004d0008[0], temp_s2);
}

int FUN_0044cdf0(void) {
    if (DAT_0058c240[0] == 0) {
        DAT_0058c240[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c240[0];
}

igMetaObject *igRadioGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRadioGroup_EnsureRegistered();
    return g_igRadioGroup_metaObject[0];
}

int igRadioGroup_GetVTable(void) {
    union U_44ce90 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00540dd0[0];
    p48 = &u.b[8];
    *(int *)p48 = 0;
    p4C = &u.b[12];
    *(int *)p4C = 0;
    p50 = &u.b[16];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00540dd0[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void igRadioGroup_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRadioGroup_Register);
}

void igRadioGroup_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRadioGroup_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRadioGroup_GetMetaObject,
        igRadioGroup_className,
        0x20, /* instance size */
        igRadioGroup_GetVTable,
        &igRadioGroup_InitFields,
        0, /* extra callback item */
        g_igRadioGroup_callbackList /* callback list */
    );
}

void thunk_igRadioGroup_GetMetaObject(void) {
    igRadioGroup_GetMetaObject();
}

void igRadioGroup_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s1;

    temp_s1 = (void *)DAT_0058c240[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d0020[0], 6);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0044d170();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0044cbd0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0044c880();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), -1);
    igMetaObject_NameFields(temp_s1, &DAT_004d0040[0], &DAT_004d0060[0], &DAT_004d0080[0], temp_s0);
}

int FUN_0044d170(void) {
    if (DAT_0058c278[0] == 0) {
        DAT_0058c278[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c278[0];
}

igMetaObject *igRadioGroupModel_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroupModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRadioGroupModel_RunStaticInit();
    return g_igRadioGroupModel_metaObject[0];
}

int igRadioGroupModel_GetVTable(void) {
    union U_44d210 u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00540e30[0];
    u.vt = (int)&DAT_00541ca0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void igRadioGroupModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igRadioGroupModel_Register);
}

void igRadioGroupModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRadioGroupModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igRadioGroupModel_GetMetaObject,
        igRadioGroupModel_className,
        0x10, /* instance size */
        igRadioGroupModel_GetVTable,
        &igRadioGroupModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRadioGroupModel_GetMetaObject(void) {
    igRadioGroupModel_GetMetaObject();
}

int FUN_0044d340(void) {
    return DAT_0058c298[0];
}

void igRadioGroupModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c278[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0098[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004d00a0[0], &DAT_004d00a8[0], &DAT_004d00b0[0], temp_s1);
}

igMetaObject *igOnOffModel_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffModel_RunStaticInit();
    return g_igOnOffModel_metaObject[0];
}

int igOnOffModel_GetVTable(void) {
    union U_44d430 u;
    int temp_s0;
    char *q1;
    void *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00540e30[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00541c40[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (q1 != 0) {
        temp_a0 = *(void **)q1;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void igOnOffModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igOnOffModel_Register);
}

void igOnOffModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffModel_metaObject,
        igGuiComponentModel_Register,
        igGuiComponentModel_GetPublishedMetaObject,
        thunk_igOnOffModel_GetMetaObject,
        igOnOffModel_className,
        0x28, /* instance size */
        igOnOffModel_GetVTable,
        &igOnOffModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igOnOffModel_GetMetaObject(void) {
    igOnOffModel_GetMetaObject();
}

void igOnOffModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c288[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d00b8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004d00c0[0], &DAT_004d00c8[0], &DAT_004d00d0[0], temp_s1);
}

int FUN_0044d5d0(void) {
    if (DAT_0058c298[0] == 0) {
        DAT_0058c298[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c298[0];
}

igMetaObject *igModel_GetMetaObject(void)
{
    igMetaObject *g = g_igModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igModel_RunStaticInit();
    return g_igModel_metaObject[0];
}

int igModel_GetVTable(void) {
    struct Obj_44d670 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540e30[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00540e30[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void igModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igModel_Register);
}

void igModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModel_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igModel_GetMetaObject,
        igModel_className,
        0xC, /* instance size */
        igModel_GetVTable,
        &igModel_InitFields,
        0, /* extra callback item */
        g_igModel_callbackList /* callback list */
    );
}

void thunk_igModel_GetMetaObject(void) {
    igModel_GetMetaObject();
}

void igModel_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c298[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d00e0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044b880();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d00e8[0], &DAT_004d00f0[0], &DAT_004d00f8[0], temp_s2);
}

int FUN_0044d840(void) {
    if (DAT_0058c2a8[0] == 0) {
        DAT_0058c2a8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c2a8[0];
}

igMetaObject *igHotKeyEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyEventReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyEventReceiver_RunStaticInit();
    return g_igHotKeyEventReceiver_metaObject[0];
}

int igHotKeyEventReceiver_GetVTable(void) {
    union U_44d8e0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00540e90[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00540e90[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void igHotKeyEventReceiver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyEventReceiver_Register);
}

void igHotKeyEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igHotKeyEventReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igHotKeyEventReceiver_GetMetaObject,
        igHotKeyEventReceiver_className,
        0xC, /* instance size */
        igHotKeyEventReceiver_GetVTable,
        &igHotKeyEventReceiver_InitFields,
        0, /* extra callback item */
        g_igHotKeyEventReceiver_callbackList /* callback list */
    );
}

void thunk_igHotKeyEventReceiver_GetMetaObject(void) {
    igHotKeyEventReceiver_GetMetaObject();
}

void igHotKeyEventReceiver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c2a8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0108[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044dab0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d0110[0], &DAT_004d0118[0], &DAT_004d0120[0], temp_s2);
}

int FUN_0044dab0(void) {
    if (DAT_0058c2b8[0] == 0) {
        DAT_0058c2b8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c2b8[0];
}

igMetaObject *igHotKeyBindingList_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyBindingList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyBindingList_RunStaticInit();
    return g_igHotKeyBindingList_metaObject[0];
}

int igHotKeyBindingList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541bd0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igHotKeyBindingList_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyBindingList_Register);
}

void igHotKeyBindingList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igHotKeyBindingList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igHotKeyBindingList_GetMetaObject,
        igHotKeyBindingList_className,
        0x14, /* instance size */
        igHotKeyBindingList_GetVTable,
        0,
        0, /* extra callback item */
        g_igHotKeyBindingList_callbackList /* callback list */
    );
}

void thunk_igHotKeyBindingList_GetMetaObject(void) {
    igHotKeyBindingList_GetMetaObject();
}

int FUN_0044dc20(int arg0) {
    igHotKeyBinding_RunStaticInit();
    return igMetaObject_CreateInstance(*(int *)0x58C2C0, arg0);
}

igMetaObject *igHotKeyBinding_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyBinding_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyBinding_RunStaticInit();
    return g_igHotKeyBinding_metaObject[0];
}

int igHotKeyBinding_GetVTable(void) {
    struct Obj_44dcb0 o;
    struct R *t;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_00541b70[0];
    o.p = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00541b70[0];
    if (&o.p != 0) {
        t = o.p;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void igHotKeyBinding_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igHotKeyBinding_Register);
}

void igHotKeyBinding_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igHotKeyBinding_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igHotKeyBinding_GetMetaObject,
        igHotKeyBinding_className,
        0x14, /* instance size */
        igHotKeyBinding_GetVTable,
        &igHotKeyBinding_InitFields,
        0, /* extra callback item */
        g_igHotKeyBinding_callbackList /* callback list */
    );
}

void thunk_igHotKeyBinding_GetMetaObject(void) {
    igHotKeyBinding_GetMetaObject();
}

void igHotKeyBinding_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c2c0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0138[0], 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_004d0178[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_00145eb0);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    FUN_002dc7a0(temp_v0_2, &DAT_004d0180[0]);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(FUN_00146850);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00453250();
    igMetaObject_NameFields(temp_s0, &DAT_004d0148[0], &DAT_004d0158[0], &DAT_004d0168[0], temp_s2);
}

int FUN_0044ded0(void) {
    if (DAT_0058c2e0[0] == 0) {
        DAT_0058c2e0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c2e0[0];
}

igMetaObject *igGuiSystem_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystem_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystem_RunStaticInit();
    return g_igGuiSystem_metaObject[0];
}

int igGuiSystem_GetVTable(void) {
    struct Obj_44df70 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540f20[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00540f20[0];
    FUN_001a7580(&obj.w7, -1);
    FUN_0044e1e0((O_44e1e0 *)&obj.w6, -1);
    FUN_001d97f0(&obj.w5, -1);
    FUN_0044e160((void **)&obj.w4, -1);
    FUN_0044e0e0((Ref **)&obj.w3, -1);
    FUN_0044e060((void **)&obj.w2, -1);
    return t;
}

void **FUN_0044e060(void **arg0, short arg1) {
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

void **FUN_0044e0e0(struct Ref **self, short flag) {
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

void **FUN_0044e160(void **arg0, long long arg1) {
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

O_44e1e0 *FUN_0044e1e0(O_44e1e0 *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void igGuiSystem_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystem_Register);
}

void igGuiSystem_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiSystem_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igGuiSystem_GetMetaObject,
        igGuiSystem_className,
        0x24, /* instance size */
        igGuiSystem_GetVTable,
        &igGuiSystem_InitFields,
        0, /* extra callback item */
        g_igGuiSystem_callbackList /* callback list */
    );
}

void thunk_igGuiSystem_GetMetaObject(void) {
    igGuiSystem_GetMetaObject();
}

void igGuiSystem_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;

    temp_s1 = (void *)DAT_0058c2e0[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d01b0[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0044e6b0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0044f210();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0044b9f0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_001a5d70();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0044e430();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00196190();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004d01d0[0], &DAT_004d01f0[0], &DAT_004d0210[0], temp_s0);
}

int FUN_0044e430(void) {
    if (DAT_0058c320[0] == 0) {
        DAT_0058c320[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c320[0];
}

igMetaObject *igMouseCursor_GetMetaObject(void)
{
    igMetaObject *g = g_igMouseCursor_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMouseCursor_RunStaticInit();
    return g_igMouseCursor_metaObject[0];
}

int igMouseCursor_GetVTable(void) {
    struct Obj_44e4d0 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541b10[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00541b10[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void igMouseCursor_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igMouseCursor_Register);
}

void igMouseCursor_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMouseCursor_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMouseCursor_GetMetaObject,
        igMouseCursor_className,
        0x14, /* instance size */
        igMouseCursor_GetVTable,
        &igMouseCursor_InitFields,
        0, /* extra callback item */
        g_igMouseCursor_callbackList /* callback list */
    );
}

void thunk_igMouseCursor_GetMetaObject(void) {
    igMouseCursor_GetMetaObject();
}

void igMouseCursor_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;
    void *temp_a0;
    int buf[2];

    temp_s0 = (void *)DAT_0058c320[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0238[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_004505b0();
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    buf[0] = 0;
    buf[1] = 0;
    FUN_0018e2f0(temp_a0, buf);
    igMetaObject_NameFields(temp_s0, &DAT_004d0240[0], &DAT_004d0248[0], &DAT_004d0250[0], temp_s2);
}

int FUN_0044e6b0(void) {
    if (DAT_0058c338[0] == 0) {
        DAT_0058c338[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c338[0];
}

igMetaObject *igGuiSystemRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystemRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystemRenderer_RunStaticInit();
    return g_igGuiSystemRenderer_metaObject[0];
}

int igGuiSystemRenderer_GetVTable(void) {
    struct Obj_44e750 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00540fb0[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00540fb0[0];
    FUN_00197160(&obj.w6, -1);
    FUN_001d9870(&obj.w5, -1);
    FUN_0044e0e0((Ref **)&obj.w4, -1);
    FUN_00198210(&obj.w3, -1);
    FUN_00230f70(&obj, 0);
    return t;
}

void igGuiSystemRenderer_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystemRenderer_Register);
}

void igGuiSystemRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiSystemRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igGuiSystemRenderer_GetMetaObject,
        igGuiSystemRenderer_className,
        0x1C, /* instance size */
        igGuiSystemRenderer_GetVTable,
        &igGuiSystemRenderer_InitFields,
        0, /* extra callback item */
        g_igGuiSystemRenderer_callbackList /* callback list */
    );
}

void thunk_igGuiSystemRenderer_GetMetaObject(void) {
    igGuiSystemRenderer_GetMetaObject();
}

void igGuiSystemRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c338[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0280[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019cd50();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0044f210();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_001a38e0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_00137fb0();
    igMetaObject_NameFields(temp_s0, &DAT_004d0290[0], &DAT_004d02a0[0], &DAT_004d02b0[0], temp_s2);
}

int FUN_0044e990(int arg0) {
    igActiveComponentsObserver_RunStaticInit();
    return igMetaObject_CreateInstance(*(int *)0x58C360, arg0);
}

igMetaObject *igActiveComponentsObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igActiveComponentsObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igActiveComponentsObserver_RunStaticInit();
    return g_igActiveComponentsObserver_metaObject[0];
}

int igActiveComponentsObserver_GetVTable(void) {
    union U_44ea20 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00541020[0];
    p48 = &u.b[12];
    *(int *)p48 = 0;
    p4C = &u.b[16];
    *(int *)p4C = 0;
    p50 = &u.b[20];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00541020[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void igActiveComponentsObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igActiveComponentsObserver_Register);
}

void igActiveComponentsObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActiveComponentsObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igActiveComponentsObserver_GetMetaObject,
        igActiveComponentsObserver_className,
        0x18, /* instance size */
        igActiveComponentsObserver_GetVTable,
        &igActiveComponentsObserver_InitFields,
        0, /* extra callback item */
        g_igActiveComponentsObserver_callbackList /* callback list */
    );
}

void thunk_igActiveComponentsObserver_GetMetaObject(void) {
    igActiveComponentsObserver_GetMetaObject();
}

void igActiveComponentsObserver_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c360[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d02c8[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044ff40();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0044ff40();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0044ff40();
    igMetaObject_NameFields(temp_s0, &DAT_004d02d8[0], &DAT_004d02e8[0], &DAT_004d02f8[0], temp_s2);
}

int FUN_0044ecb0(int arg0) {
    igMousePosObserver_RunStaticInit();
    return igMetaObject_CreateInstance(*(int *)0x58C380, arg0);
}

igMetaObject *igMousePosObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igMousePosObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMousePosObserver_RunStaticInit();
    return g_igMousePosObserver_metaObject[0];
}

int igMousePosObserver_GetVTable(void) {
    igMousePosObserver s; igMousePosObserver *o = &s; igObject *a; int t; int *p2; int *p1; int *p0;
    igObject_InitHeader(o);
    o->_vtable = (int)&DAT_00541090[0];
    p0 = &o->_intersectTraversal; p1 = &o->_ray; p2 = &o->_hitPath;
    *p0 = 0; *p1 = 0; *p2 = 0;
    igMatrix44f_SetIdentity(o->_inverseProjectionMatrix);
    t = *(int *)((char *)o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o->_vtable = (int)&D_00541090[0];
    if (p2 != 0) {
        a = *(igObject **)p2;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (p1 != 0) {
        a = *(igObject **)p1;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (p0 != 0) {
        a = *(igObject **)p0;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}

ObjectRefWord *FUN_0044ee80(ObjectRefWord *self,int delete_storage) {
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

void igMousePosObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igMousePosObserver_Register);
}

void igMousePosObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMousePosObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igMousePosObserver_GetMetaObject,
        igMousePosObserver_className,
        0x64, /* instance size */
        igMousePosObserver_GetVTable,
        &igMousePosObserver_InitFields,
        0, /* extra callback item */
        g_igMousePosObserver_callbackList /* callback list */
    );
}

void thunk_igMousePosObserver_GetMetaObject(void) {
    igMousePosObserver_GetMetaObject();
}

void igMousePosObserver_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)DAT_0058c380[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d0330[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0044ded0();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019dfd0();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00188260();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_002e3810((int)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), 0.0f);
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0019f670();
    igMetaObject_NameFields(temp_s1, &DAT_004d0350[0], &DAT_004d0370[0], &DAT_004d0390[0], temp_s0);
}

int FUN_0044f0b0(int arg0) {
    igWindowSizeObserver_RunStaticInit();
    return igMetaObject_CreateInstance(*(int *)0x58C3C0, arg0);
}

igMetaObject *igWindowSizeObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igWindowSizeObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igWindowSizeObserver_RunStaticInit();
    return g_igWindowSizeObserver_metaObject[0];
}

int igWindowSizeObserver_GetVTable(void) {
    struct O o;
    igObject_InitHeader(&o.vt);
    o.vt = DAT_00541100;
    return *(int *)((char *)&o.vt + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igWindowSizeObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igWindowSizeObserver_Register);
}

void igWindowSizeObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igWindowSizeObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igWindowSizeObserver_GetMetaObject,
        igWindowSizeObserver_className,
        0xC, /* instance size */
        igWindowSizeObserver_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igWindowSizeObserver_GetMetaObject(void) {
    igWindowSizeObserver_GetMetaObject();
}

int FUN_0044f210(void) {
    if (DAT_0058c3c8[0] == 0) {
        DAT_0058c3c8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c3c8[0];
}

igMetaObject *igGuiSystemModel_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystemModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystemModel_RunStaticInit();
    return g_igGuiSystemModel_metaObject[0];
}

int igGuiSystemModel_GetVTable(void) {
    struct igGuiSystemModel s;
    char *p;
    int r;
    p = (char *)&s;
    igObject_InitHeader(p);
    s._views = 0;
    *(int **)&s._vtable = &DAT_00541170[0];
    igMatrix44f_SetIdentity(s._viewMatrix);
    igMatrix44f_SetIdentity(((struct igGuiSystemModel *)p)->_projectionMatrix);
    ((struct igGuiSystemModel *)p)->_rootComponent = 0;
    ((struct igGuiSystemModel *)p)->_focusedComponent = 0;
    ((struct igGuiSystemModel *)p)->_componentUnderMouse = 0;
    ((struct igGuiSystemModel *)p)->_pushedComponent = 0;
    r = *(int *)((char *)&s + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    *(int **)&s._vtable = &DAT_00541170[0];
    FUN_003cafa0(&s._pushedComponent, -1);
    FUN_003cafa0(&s._componentUnderMouse, -1);
    FUN_003cafa0(&s._focusedComponent, -1);
    FUN_003cafa0(&s._rootComponent, -1);
    FUN_0044c110((S *)&s, 0);
    return r;
}

void igGuiSystemModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystemModel_Register);
}

void igGuiSystemModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiSystemModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igGuiSystemModel_GetMetaObject,
        igGuiSystemModel_className,
        0xB8, /* instance size */
        igGuiSystemModel_GetVTable,
        &igGuiSystemModel_InitFields,
        0, /* extra callback item */
        g_igGuiSystemModel_callbackList /* callback list */
    );
}

void thunk_igGuiSystemModel_GetMetaObject(void) {
    igGuiSystemModel_GetMetaObject();
}

void igGuiSystemModel_InitFields(void) {
    int temp_s2;
    int sp48[2];
    int sp40[2];
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c3c8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d03c0[0], 0xB);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    sp48[0] = 0;
    sp48[1] = 0;
    FUN_0018e2f0(temp_a0, sp48);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    sp40[0] = 0;
    sp40[1] = 0;
    FUN_0018e2f0(temp_a0_2, sp40);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    *(int *)((char *)(temp_s1) + 56) = FUN_0044ff40();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_0044ff40();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_0044ff40();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    *(int *)((char *)(temp_s1_4) + 56) = FUN_0044ff40();
    igMetaObject_NameFields(temp_s0, &DAT_004d03f0[0], &DAT_004d0420[0], &DAT_004d0450[0], temp_s2);
}

int FUN_0044f540(void) {
    if (DAT_0058c428[0] == 0) {
        DAT_0058c428[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c428[0];
}

igMetaObject *igGuiComponentNode_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentNode_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentNode_RunStaticInit();
    return g_igGuiComponentNode_metaObject[0];
}

int igGuiComponentNode_GetVTable(void) {
    struct Obj_44f5e0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &DAT_005411d0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005411d0[0];
    FUN_00195a90(&obj, 0);
    return t;
}

void igGuiComponentNode_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiComponentNode_Register);
}

void igGuiComponentNode_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igGuiComponentNode_GetMetaObject,
        igGuiComponentNode_className,
        0x24, /* instance size */
        igGuiComponentNode_GetVTable,
        &igGuiComponentNode_InitFields,
        0, /* extra callback item */
        g_igGuiComponentNode_callbackList /* callback list */
    );
}

void thunk_igGuiComponentNode_GetMetaObject(void) {
    igGuiComponentNode_GetMetaObject();
}

void igGuiComponentNode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c428[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0488[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044ff40();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004d0490[0], &DAT_004d0498[0], &DAT_004d04a0[0], temp_s2);
}

int FUN_0044f790(void) {
    if (DAT_0058c438[0] == 0) {
        DAT_0058c438[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c438[0];
}

igMetaObject *igGuiComponentModel_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentModel_RunStaticInit();
    return g_igGuiComponentModel_metaObject[0];
}

int igGuiComponentModel_GetVTable(void) {
    union U_44f830 u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00540e30[0];
    u.vt = (int)&DAT_00541e30[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void igGuiComponentModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiComponentModel_Register);
}

void igGuiComponentModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igGuiComponentModel_GetMetaObject,
        igGuiComponentModel_className,
        0x24, /* instance size */
        igGuiComponentModel_GetVTable,
        &igGuiComponentModel_InitFields,
        0, /* extra callback item */
        g_igGuiComponentModel_callbackList /* callback list */
    );
}

void thunk_igGuiComponentModel_GetMetaObject(void) {
    igGuiComponentModel_GetMetaObject();
}

void igGuiComponentModel_InitFields(void) {
    int temp_s2;
    void *temp_a0;
    void *temp_s1;
    struct { int a; int b; int c; } z;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c438[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d04b0[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_0044ff40();
    *(char *)(60 + (char *)(temp_s1)) = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    z.a = 0;
    z.b = 0;
    z.c = 0;
    FUN_0018e470(temp_a0, &z);
    igMetaObject_NameFields(temp_s0, &DAT_004d04d0[0], &DAT_004d04f0[0], &DAT_004d0510[0], temp_s2);
}

int FUN_0044fa40(void) {
    if (DAT_0058c478[0] == 0) {
        DAT_0058c478[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c478[0];
}

igMetaObject *igGuiComponentController_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentController_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentController_EnsureRegistered();
    return g_igGuiComponentController_metaObject[0];
}

int igGuiComponentController_GetVTable(void) {
    struct Obj_44fae0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541270[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igGuiComponentController_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentController_Register);
}

void igGuiComponentController_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentController_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igGuiComponentController_GetMetaObject,
        igGuiComponentController_className,
        0xC, /* instance size */
        igGuiComponentController_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igGuiComponentController_GetMetaObject(void) {
    igGuiComponentController_GetMetaObject();
}

int FUN_0044fbb0(void) {
    if (DAT_0058c480[0] == 0) {
        DAT_0058c480[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c480[0];
}

igMetaObject *igGuiComponentAspect_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentAspect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentAspect_EnsureRegistered();
    return g_igGuiComponentAspect_metaObject[0];
}

void igGuiComponentAspect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentAspect_Register);
}

void igGuiComponentAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igGuiComponentAspect_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igGuiComponentAspect_GetMetaObject,
        igGuiComponentAspect_className,
        0x28, /* instance size */
        0,
        &igGuiComponentAspect_InitFields,
        0, /* extra callback item */
        g_igGuiComponentAspect_callbackList /* callback list */
    );
}

void thunk_igGuiComponentAspect_GetMetaObject(void) {
    igGuiComponentAspect_GetMetaObject();
}

void igGuiComponentAspect_InitFields(void) {
    float v1[3];
    float v2[4];
    void *temp_a0_2;
    void *temp_a0;
    int temp_s2;
    struct GuiAspectMetaField *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c480[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0538[0], 3);
    temp_s1 = (struct GuiAspectMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    temp_s1->f56 = FUN_0044f540();
    temp_s1->b60 = 0;
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    v1[0] = 0.0f;
    v1[1] = 0.0f;
    v1[2] = 0.0f;
    FUN_0018e470(temp_a0, v1);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    v2[2] = 1.0f;
    v2[0] = 3.4028235e+38f;
    v2[1] = 3.4028235e+38f;
    FUN_0018e470(temp_a0_2, v2);
    igMetaObject_NameFields(temp_s0, &DAT_004d0548[0], &DAT_004d0558[0], &DAT_004d0568[0], temp_s2);
}

int FUN_0044fdd0(void) {
    if (DAT_0058c4a0[0] == 0) {
        DAT_0058c4a0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c4a0[0];
}

igMetaObject *igGuiComponentList_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentList_EnsureRegistered();
    return g_igGuiComponentList_metaObject[0];
}

int igGuiComponentList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541aa0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igGuiComponentList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentList_Register);
}

void igGuiComponentList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGuiComponentList_GetMetaObject,
        igGuiComponentList_className,
        0x14, /* instance size */
        igGuiComponentList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGuiComponentList_callbackList /* callback list */
    );
}

void thunk_igGuiComponentList_GetMetaObject(void) {
    igGuiComponentList_GetMetaObject();
}

int FUN_0044ff40(void) {
    if (DAT_0058c4a8[0] == 0) {
        DAT_0058c4a8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c4a8[0];
}

igMetaObject *igGuiComponent_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponent_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponent_EnsureRegistered();
    return g_igGuiComponent_metaObject[0];
}

int igGuiComponent_GetVTable(void) {
    struct Obj_44ffe0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541300[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00541300[0];
    FUN_00450370((ObjectRefWord *)&obj.w7, -1);
    FUN_004502f0((void **)&obj.w5, -1);
    FUN_00450270((ObjectRefWord *)&obj.w4, -1);
    FUN_004501f0((void **)&obj.w3, -1);
    return t;
}

O_450090 *FUN_00450090(O_450090 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00541300[0];
        if (&arg0->m28) {
            S1 *t = arg0->m28;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m20) {
            S1 *t = arg0->m20;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m16) {
            S1 *t = arg0->m16;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m12) {
            S1 *t = arg0->m12;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (arg1 > 0) thunk_FUN_002ed460__002ff810(arg0);
    }
    return arg0;
}

void **FUN_004501f0(void **arg0, short arg1) {
    S_temp_a0_4501f0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_4501f0 *)(*arg0);
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

ObjectRefWord *FUN_00450270(ObjectRefWord *self,int delete_storage) {
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

void **FUN_004502f0(void **arg0, short arg1) {
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

ObjectRefWord *FUN_00450370(ObjectRefWord *self,int delete_storage) {
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

void igGuiComponent_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponent_Register);
}

void igGuiComponent_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponent_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igGuiComponent_GetMetaObject,
        igGuiComponent_className,
        0x24, /* instance size */
        igGuiComponent_GetVTable,
        &igGuiComponent_InitFields,
        0, /* extra callback item */
        g_igGuiComponent_callbackList /* callback list */
    );
}

void thunk_igGuiComponent_GetMetaObject(void) {
    igGuiComponent_GetMetaObject();
}

void igGuiComponent_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;

    temp_s1 = (void *)DAT_0058c4a8[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d05a0[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0044fa40();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0044f790();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0044fbb0();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0044ff40();
    ((igObjectRefMetaField *)temp_s2_4)->_refCounted = 0;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0044ded0();
    ((igObjectRefMetaField *)temp_s2_5)->_refCounted = 0;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0044f540();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004d05c0[0], &DAT_004d05e0[0], &DAT_004d0600[0], temp_s0);
}

int FUN_004505b0(void) {
    if (DAT_0058c4e8[0] == 0) {
        DAT_0058c4e8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c4e8[0];
}

igMetaObject *igGeometryElement_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryElement_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGeometryElement_EnsureRegistered();
    return g_igGeometryElement_metaObject[0];
}

void igGeometryElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometryElement_Register);
}

void igGeometryElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igGeometryElement_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igGeometryElement_GetMetaObject,
        igGeometryElement_className,
        0x2C, /* instance size */
        0,
        &igGeometryElement_InitFields,
        0, /* extra callback item */
        g_igGeometryElement_callbackList /* callback list */
    );
}

void thunk_igGeometryElement_GetMetaObject(void) {
    igGeometryElement_GetMetaObject();
}

void igGeometryElement_InitFields(void) {
    struct GeometryMetaFieldView { char p[52]; char f52; char p2[3]; int f56; };
    void *temp_a0;
    struct GeometryMetaFieldView *temp_s1_2;
    int temp_s2;
    struct GeometryMetaFieldView *temp_s1;
    void *temp_s0;
    void *temp_a0_2;
    float v4[4];
    float v3[3];

    temp_s0 = (void *)DAT_0058c4e8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0630[0], 4);
    temp_s1 = (struct GeometryMetaFieldView *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    temp_s1->f56 = FUN_0019fae0();
    temp_s1->f52 = 1;
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    v3[0] = 0.0f;
    v3[1] = 0.0f;
    v3[2] = 0.0f;
    FUN_0018e470(temp_a0, v3);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    v4[0] = 1.0f;
    v4[1] = 1.0f;
    v4[2] = 1.0f;
    v4[3] = 1.0f;
    FUN_0018e670(temp_a0_2, v4);
    temp_s1_2 = (struct GeometryMetaFieldView *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    temp_s1_2->f56 = FUN_0013af00();
    temp_s1_2->f52 = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d0640[0], &DAT_004d0650[0], &DAT_004d0660[0], temp_s2);
}

int FUN_004507f0(void) {
    if (DAT_0058c510[0] == 0) {
        DAT_0058c510[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c510[0];
}

igMetaObject *igFont_GetMetaObject(void)
{
    igMetaObject *g = g_igFont_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFont_EnsureRegistered();
    return g_igFont_metaObject[0];
}

void igFont_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFont_Register);
}

void igFont_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igFont_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igFont_GetMetaObject,
        igFont_className,
        0x1C, /* instance size */
        0,
        &igFont_InitFields,
        0, /* extra callback item */
        g_igFont_callbackList /* callback list */
    );
}

void thunk_igFont_GetMetaObject(void) {
    igFont_GetMetaObject();
}

void igFont_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c510[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0680[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d0690[0], &DAT_004d06a0[0], &DAT_004d06b0[0], temp_s2);
}

void FUN_004509c0(int arg0) {
    igFieldSynchronizer_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58C538, arg0);
}

int FUN_00450a00(void) {
    if (DAT_0058c538[0] == 0) {
        DAT_0058c538[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c538[0];
}

igMetaObject *igFieldSynchronizer_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldSynchronizer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldSynchronizer_EnsureRegistered();
    return g_igFieldSynchronizer_metaObject[0];
}

int igFieldSynchronizer_GetVTable(void) {
    struct Obj_450aa0 o;
    struct R *t;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_00541a40[0];
    o.p = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00541a40[0];
    if (&o.p != 0) {
        t = o.p;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void igFieldSynchronizer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldSynchronizer_Register);
}

void igFieldSynchronizer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFieldSynchronizer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igFieldSynchronizer_GetMetaObject,
        igFieldSynchronizer_className,
        0xC, /* instance size */
        igFieldSynchronizer_GetVTable,
        &igFieldSynchronizer_InitFields,
        0, /* extra callback item */
        g_igFieldSynchronizer_callbackList /* callback list */
    );
}

void thunk_igFieldSynchronizer_GetMetaObject(void) {
    igFieldSynchronizer_GetMetaObject();
}

void igFieldSynchronizer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c538[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d06c8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00450c70();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d06d0[0], &DAT_004d06d8[0], &DAT_004d06e0[0], temp_s2);
}

int FUN_00450c70(void) {
    if (DAT_0058c548[0] == 0) {
        DAT_0058c548[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c548[0];
}

igMetaObject *igFieldChangeViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldChangeViewList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldChangeViewList_EnsureRegistered();
    return g_igFieldChangeViewList_metaObject[0];
}

int igFieldChangeViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005419d0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igFieldChangeViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldChangeViewList_Register);
}

void igFieldChangeViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFieldChangeViewList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igFieldChangeViewList_GetMetaObject,
        igFieldChangeViewList_className,
        0x14, /* instance size */
        igFieldChangeViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFieldChangeViewList_callbackList /* callback list */
    );
}

void thunk_igFieldChangeViewList_GetMetaObject(void) {
    igFieldChangeViewList_GetMetaObject();
}

int FUN_00450de0(int arg0) {
    igFieldChangeView_EnsureRegistered();
    return igMetaObject_CreateInstance(*(int *)0x58C550, arg0);
}

igMetaObject *igFieldChangeView_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldChangeView_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldChangeView_EnsureRegistered();
    return g_igFieldChangeView_metaObject[0];
}

int igFieldChangeView_GetVTable(void) {
    struct Obj_450e70 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541360[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00541360[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void igFieldChangeView_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldChangeView_Register);
}

void igFieldChangeView_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFieldChangeView_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igFieldChangeView_GetMetaObject,
        igFieldChangeView_className,
        0x14, /* instance size */
        igFieldChangeView_GetVTable,
        &igFieldChangeView_InitFields,
        0, /* extra callback item */
        g_igFieldChangeView_callbackList /* callback list */
    );
}

void thunk_igFieldChangeView_GetMetaObject(void) {
    igFieldChangeView_GetMetaObject();
}

void igFieldChangeView_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c550[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0700[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00450a00();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_002beca0();
    igMetaObject_NameFields(temp_s0, &DAT_004d0708[0], &DAT_004d0710[0], &DAT_004d0718[0], temp_s2);
}

int FUN_00451050(void) {
    if (DAT_0058c568[0] == 0) {
        DAT_0058c568[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c568[0];
}

igMetaObject *igEventReceiverOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igEventReceiverOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventReceiverOrderedList_EnsureRegistered();
    return g_igEventReceiverOrderedList_metaObject[0];
}

int igEventReceiverOrderedList_GetVTable(void) {
    union U_4510f0 u;
    int t;
    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    u.vt = (int)&DAT_00541910[0];
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00541910[0];
    FUN_00451160((int **)u.b, 0);
    return t;
}

int **FUN_00451160(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00541970[0];
        if (arg0 != 0) {
            *arg0 = &DAT_0052cc20[0];
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x14), -1);
            FUN_00135430((int **)((char *)arg0 + 0x10), -1);
            FUN_00233590((int **)((char *)arg0 + 0xC), -1);
            FUN_0014aa70((int **)((char *)arg0 + 8), -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void igEventReceiverOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventReceiverOrderedList_Register);
}

void igEventReceiverOrderedList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventReceiverOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igEventReceiverOrderedList_GetMetaObject,
        igEventReceiverOrderedList_className,
        0x1C, /* instance size */
        igEventReceiverOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igEventReceiverOrderedList_callbackList /* callback list */
    );
}

void thunk_igEventReceiverOrderedList_GetMetaObject(void) {
    igEventReceiverOrderedList_GetMetaObject();
}

igMetaObject *igEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igEventReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventReceiver_EnsureRegistered();
    return g_igEventReceiver_metaObject[0];
}

int igEventReceiver_GetVTable(void) {
    struct Obj_4512e0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052cce0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igEventReceiver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventReceiver_Register);
}

void igEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventReceiver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEventReceiver_GetMetaObject,
        igEventReceiver_className,
        8, /* instance size */
        igEventReceiver_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igEventReceiver_GetMetaObject(void) {
    igEventReceiver_GetMetaObject();
}

int FUN_004513b0(void) {
    if (DAT_0058c578[0] == 0) {
        DAT_0058c578[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c578[0];
}

igMetaObject *igEventDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igEventDispatcher_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventDispatcher_EnsureRegistered();
    return g_igEventDispatcher_metaObject[0];
}

int igEventDispatcher_GetVTable(void) {
    union U_451450 u;
    int temp_s2;
    S_ref *q2;
    S_ref *q1;
    S_ref *q3;
    
    
    igObject_InitHeader(u.b);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_005413d0[0]);
    q2 = (S_ref *)&u.b[12];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[16];
    *(int *)q3 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_005413d0[0]);
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
    u.w[0] = (int)(&DAT_00524da0[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s2;
}

void igEventDispatcher_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventDispatcher_Register);
}

void igEventDispatcher_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventDispatcher_metaObject,
        igInterfaceManager_Register,
        igInterfaceManager_GetPublishedMetaObject,
        thunk_igEventDispatcher_GetMetaObject,
        igEventDispatcher_className,
        0x14, /* instance size */
        igEventDispatcher_GetVTable,
        &igEventDispatcher_InitFields,
        0, /* extra callback item */
        g_igEventDispatcher_callbackList /* callback list */
    );
}

void thunk_igEventDispatcher_GetMetaObject(void) {
    igEventDispatcher_GetMetaObject();
}

void igEventDispatcher_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c578[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0738[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00451050();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00146660();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d0740[0], &DAT_004d0748[0], &DAT_004d0750[0], temp_s2);
}

int FUN_004516e0(void) {
    if (DAT_0058c590[0] == 0) {
        DAT_0058c590[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c590[0];
}

igMetaObject *igDefaultAspect_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspect_EnsureRegistered();
    return g_igDefaultAspect_metaObject[0];
}

int igDefaultAspect_GetVTable(void) {
    Obj_451780 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541480[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00541480[0];
    obj.release();
    return r;
}

void igDefaultAspect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspect_Register);
}

void igDefaultAspect_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultAspect_metaObject,
        igGuiComponentAspect_Register,
        igGuiComponentAspect_GetPublishedMetaObject,
        thunk_igDefaultAspect_GetMetaObject,
        igDefaultAspect_className,
        0x2C, /* instance size */
        igDefaultAspect_GetVTable,
        &igDefaultAspect_InitFields,
        0, /* extra callback item */
        g_igDefaultAspect_callbackList /* callback list */
    );
}

void thunk_igDefaultAspect_GetMetaObject(void) {
    igDefaultAspect_GetMetaObject();
}

void igDefaultAspect_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c590[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0760[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00451950();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d0768[0], &DAT_004d0770[0], &DAT_004d0778[0], temp_s2);
}

int FUN_00451950(void) {
    if (DAT_0058c5a0[0] == 0) {
        DAT_0058c5a0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c5a0[0];
}

igMetaObject *igDefaultAspectElementList_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspectElementList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspectElementList_EnsureRegistered();
    return g_igDefaultAspectElementList_metaObject[0];
}

int igDefaultAspectElementList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005418a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igDefaultAspectElementList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspectElementList_Register);
}

void igDefaultAspectElementList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultAspectElementList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDefaultAspectElementList_GetMetaObject,
        igDefaultAspectElementList_className,
        0x14, /* instance size */
        igDefaultAspectElementList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDefaultAspectElementList_callbackList /* callback list */
    );
}

void thunk_igDefaultAspectElementList_GetMetaObject(void) {
    igDefaultAspectElementList_GetMetaObject();
}

int FUN_00451ac0(void) {
    if (DAT_0058c5a8[0] == 0) {
        DAT_0058c5a8[0] = igMetaEnum_Create(&DAT_0051e648[0], &DAT_004d0790[0], &DAT_004d07a0[0], 4);
    }
    return DAT_0058c5a8[0];
}

igMetaObject *igDefaultAspectElement_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspectElement_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspectElement_EnsureRegistered();
    return g_igDefaultAspectElement_metaObject[0];
}

int igDefaultAspectElement_GetVTable(void) {
    union U_451b70 u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q4c;
    void **q48;
    void **q50;
    igObject_InitHeader(u.b);
    q48 = &u.p[2];
    q4c = &u.p[3];
    q50 = &u.p[4];
    u.w[0] = (int)(&DAT_00541840[0]);
    *q48 = 0;
    *q4c = 0;
    *q50 = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00541840[0]);
    if (q50 != 0) {
        a = (struct Rc *)*q50;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q4c != 0) {
        a = (struct Rc *)*q4c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q48 != 0) {
        a = (struct Rc *)*q48;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}

void igDefaultAspectElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspectElement_Register);
}

void igDefaultAspectElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultAspectElement_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDefaultAspectElement_GetMetaObject,
        igDefaultAspectElement_className,
        0x20, /* instance size */
        igDefaultAspectElement_GetVTable,
        &igDefaultAspectElement_InitFields,
        0, /* extra callback item */
        g_igDefaultAspectElement_callbackList /* callback list */
    );
}

void thunk_igDefaultAspectElement_GetMetaObject(void) {
    igDefaultAspectElement_GetMetaObject();
}

void igDefaultAspectElement_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c5b0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d07c0[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_004505b0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_004521d0();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_00196190();
    *(unsigned char *)((char *)(temp_s1_3) + 52) = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    FUN_002dc7a0(temp_v0, &DAT_004d0838[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(FUN_00451ac0);
    igMetaObject_NameFields(temp_s0, &DAT_004d07e0[0], &DAT_004d0800[0], &DAT_004d0820[0], temp_s2);
}

int FUN_00451e40(void) {
    if (DAT_0058c5e8[0] == 0) {
        DAT_0058c5e8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c5e8[0];
}

igMetaObject *igOnOffColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffColorChanger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffColorChanger_RunStaticInit();
    return g_igOnOffColorChanger_metaObject[0];
}

int igOnOffColorChanger_GetVTable(void) {
    struct Obj_451ee0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005414f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igOnOffColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igOnOffColorChanger_Register);
}

void igOnOffColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffColorChanger_metaObject,
        igBasicColorChanger_Register,
        igBasicColorChanger_GetPublishedMetaObject,
        thunk_igOnOffColorChanger_GetMetaObject,
        igOnOffColorChanger_className,
        0x58, /* instance size */
        igOnOffColorChanger_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igOnOffColorChanger_GetMetaObject(void) {
    igOnOffColorChanger_GetMetaObject();
}

int FUN_00451fb0(void) {
    return DAT_0058c5f0[0];
}

int FUN_00451fc0(void) {
    if (DAT_0058c5f0[0] == 0) {
        DAT_0058c5f0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c5f0[0];
}

igMetaObject *igBasicColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igBasicColorChanger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBasicColorChanger_RunStaticInit();
    return g_igBasicColorChanger_metaObject[0];
}

int igBasicColorChanger_GetVTable(void) {
    struct Obj_452060 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541550[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igBasicColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBasicColorChanger_Register);
}

void igBasicColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBasicColorChanger_metaObject,
        igColorChanger_Register,
        igColorChanger_GetPublishedMetaObject,
        thunk_igBasicColorChanger_GetMetaObject,
        igBasicColorChanger_className,
        0x58, /* instance size */
        igBasicColorChanger_GetVTable,
        &igBasicColorChanger_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBasicColorChanger_GetMetaObject(void) {
    igBasicColorChanger_GetMetaObject();
}

int FUN_00452130(void) {
    return DAT_0058c608[0];
}

void igBasicColorChanger_InitFields(void) {
    int temp_s1;
    void *f;
    void *temp_s0;
    temp_s0 = (void *)DAT_0058c5f0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0840[0], 2);
    f = igMetaObject_GetFieldAt(temp_s0, temp_s1);
    *(int *)((char *)f + 52) = 4;
    igMetaObject_NameFields(temp_s0, &DAT_004d0848[0], &DAT_004d0850[0], &DAT_004d0858[0], temp_s1);
}

int FUN_004521d0(void) {
    if (DAT_0058c608[0] == 0) {
        DAT_0058c608[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c608[0];
}

igMetaObject *igColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igColorChanger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igColorChanger_RunStaticInit();
    return g_igColorChanger_metaObject[0];
}

int igColorChanger_GetVTable(void) {
    struct Obj_452270 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005415b0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igColorChanger_Register);
}

void igColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igColorChanger_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igColorChanger_GetMetaObject,
        igColorChanger_className,
        8, /* instance size */
        igColorChanger_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igColorChanger_GetMetaObject(void) {
    igColorChanger_GetMetaObject();
}

int FUN_00452340(void) {
    if (DAT_0058c610[0] == 0) {
        DAT_0058c610[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c610[0];
}

igMetaObject *igBoxComponent_GetMetaObject(void)
{
    igMetaObject *g = g_igBoxComponent_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoxComponent_RunStaticInit();
    return g_igBoxComponent_metaObject[0];
}

int igBoxComponent_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[2] = 0;
    f.w[3] = 0;
    f.w[4] = 0;
    f.w[6] = 0;
    f.vt = &DAT_005417e0[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_005417e0[0];
    FUN_00450090((O_450090 *)&f, 0);
    return temp_s0;
}

void igBoxComponent_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBoxComponent_Register);
}

void igBoxComponent_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoxComponent_metaObject,
        igGuiComponent_Register,
        igGuiComponent_GetPublishedMetaObject,
        thunk_igBoxComponent_GetMetaObject,
        igBoxComponent_className,
        0x24, /* instance size */
        igBoxComponent_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBoxComponent_GetMetaObject(void) {
    igBoxComponent_GetMetaObject();
}

int FUN_004524e0(void) {
    return DAT_0058c4a8[0];
}

int FUN_004524f0(void) {
    if (DAT_0058c620[0] == 0) {
        DAT_0058c620[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c620[0];
}

igMetaObject *igBitmapFont_GetMetaObject(void)
{
    igMetaObject *g = g_igBitmapFont_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBitmapFont_RunStaticInit();
    return g_igBitmapFont_metaObject[0];
}

int igBitmapFont_GetVTable(void) {
    struct Obj_452590 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.vt = &DAT_00541610[0];
    obj.w7 = 0;
    obj.w8 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00541610[0];
    FUN_0019aa10(&obj.w8, -1);
    FUN_003619a0(&obj.w7, -1);
    FUN_00361a20(&obj, 0);
    return t;
}

void igBitmapFont_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBitmapFont_Register);
}

void igBitmapFont_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBitmapFont_metaObject,
        igFont_Register,
        igFont_GetPublishedMetaObject,
        thunk_igBitmapFont_GetMetaObject,
        igBitmapFont_className,
        0x24, /* instance size */
        igBitmapFont_GetVTable,
        &igBitmapFont_InitFields,
        0, /* extra callback item */
        g_igBitmapFont_callbackList /* callback list */
    );
}

void thunk_igBitmapFont_GetMetaObject(void) {
    igBitmapFont_GetMetaObject();
}

int FUN_004526c0(void) {
    return DAT_0058c510[0];
}

void igBitmapFont_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c620[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0870[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00452790();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00132850();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d0878[0], &DAT_004d0880[0], &DAT_004d0888[0], temp_s2);
}

int FUN_00452790(void) {
    if (DAT_0058c638[0] == 0) {
        DAT_0058c638[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c638[0];
}

igMetaObject *igCharMetricsList_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetricsList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharMetricsList_RunStaticInit();
    return g_igCharMetricsList_metaObject[0];
}

int igCharMetricsList_GetVTable(void) {
    Obj_452830 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00541780[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igCharMetricsList_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igCharMetricsList_Register);
}

void igCharMetricsList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharMetricsList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igCharMetricsList_GetMetaObject,
        igCharMetricsList_className,
        0x14, /* instance size */
        igCharMetricsList_GetVTable,
        FUN_00452900,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCharMetricsList_GetMetaObject(void) {
    igCharMetricsList_GetMetaObject();
}

void FUN_00452900(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_0058c638[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_0051e798[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_00452c40();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_0058c640[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

igMetaObject *igCharMetricsMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetricsMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharMetricsMetaField_RunStaticInit();
    return g_igCharMetricsMetaField_metaObject[0];
}

int igCharMetricsMetaField_GetVTable(void) {
    union U_452a10 u;
    int temp_s0;
    S_ref *q0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q1;

    igMetaField_Init(u.b);
    u.vt = (int)&DAT_00531740[0];
    q0 = (S_ref *)&u.b[52];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00541680[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00531740[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&DAT_0052f230[0];
    if (&u.b[12] != 0) {
        temp_v1 = *(int **)&u.b[12];
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

void igCharMetricsMetaField_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igCharMetricsMetaField_Register);
}

void igCharMetricsMetaField_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharMetricsMetaField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igCharMetricsMetaField_GetMetaObject,
        igCharMetricsMetaField_className,
        0x38, /* instance size */
        igCharMetricsMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igCharMetricsMetaField_callbackList /* callback list */
    );
}

void thunk_igCharMetricsMetaField_GetMetaObject(void) {
    igCharMetricsMetaField_GetMetaObject();
}

void FUN_00452b70(void) {
    void *temp_s0;

    if (DAT_0058c650[0] == 0) {
        DAT_0058c650[0] = (void *)(igMetaObject_CreateInstance(DAT_0058c648[0], Memory_GetAllocatorBySelector(DAT_00587040[0])));
        temp_s0 = (void *)(DAT_0058c650[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            {
                void *held = (void *)DAT_0058c650[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_0058c650[0]) + 18) = (short) (*(int *)((char *)(FUN_002fc250()) + 12) - 1);
            igMetaField_FinalizeDescriptor(DAT_0058c650[0]);
        }
    }
}

int FUN_00452c40(void) {
    if (DAT_0058c650[0] == 0) {
        igCharMetricsMetaField_RunStaticInit();
    }
    return (int)DAT_0058c650[0];
}

int Gap__Gui__igCharMetricsMetaField__vfunc_25(void) {
    return 0x28;
}

void Gap__Gui__igCharMetricsMetaField__vfunc_11(void *arg0) {
    FUN_00452ca0(*(int *)((char *)arg0 + 52));
}

void FUN_00452ca0(int arg0) {
    void *sp4C;
    void *sp48;
    void *sp44;
    void *sp40;
    void *sp3C;
    void *sp38;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int *temp_a1_4;
    int *temp_a1_5;
    int *temp_a1_6;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int temp_v0_4;
    int temp_v0_5;
    int temp_v0_6;
    int var_v0_10;
    int var_v0_12;
    int var_v0_2;
    int var_v0_4;
    int var_v0_6;
    int var_v0_8;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s1_5;
    void *temp_s1_6;
    void *var_v0;
    void *var_v0_11;
    void *var_v0_3;
    void *var_v0_5;
    void *var_v0_7;
    void *var_v0_9;

    temp_s1 = (void *)(FUN_002b5fe0(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_0051e7b8[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_0051e7b8[0]));
    }
    sp4C = (void *)(var_v0);
    igMetaField_SetFieldName(temp_s1, &sp4C);
    if (sp4C != 0) {
        temp_a1 = (int *)((char *)sp4C - 8);
        temp_v0 = *(int *)((char *)(sp4C) - 4) - 1;
        *(int *)((char *)(sp4C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *(int *)((char *)(temp_s1) + 8) = 0;
    igMetaField_FinalizeDescriptor(temp_s1);
    ObjectList_AppendRetained(arg0, temp_s1);
    *(int *)((char *)(temp_s1) + 4) = (int)((int) (*(int *)((char *)(temp_s1) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1);
    }
    temp_s1_2 = (void *)(FUN_002c45f0(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_0051e7c8[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_4 = FUN_002eb010(0x10);
            if (var_v0_4 != 0) {
                var_v0_4 = StringPool_Construct(var_v0_4);
            }
            DAT_00586f20[0] = var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_0051e7c8[0]));
    }
    sp48 = (void *)(var_v0_3);
    igMetaField_SetFieldName(temp_s1_2, &sp48);
    if (sp48 != 0) {
        temp_a1_2 = (int *)((char *)sp48 - 8);
        temp_v0_2 = *(int *)((char *)(sp48) - 4) - 1;
        *(int *)((char *)(sp48) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    *(int *)((char *)(temp_s1_2) + 8) = 4;
    igMetaField_FinalizeDescriptor(temp_s1_2);
    ObjectList_AppendRetained(arg0, temp_s1_2);
    *(int *)((char *)(temp_s1_2) + 4) = (int)((int) (*(int *)((char *)(temp_s1_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_2);
    }
    temp_s1_3 = (void *)(FUN_00187b50(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_0051e7d0[0] == 0) {
        var_v0_5 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_6 = FUN_002eb010(0x10);
            if (var_v0_6 != 0) {
                var_v0_6 = StringPool_Construct(var_v0_6);
            }
            DAT_00586f20[0] = var_v0_6;
        }
        var_v0_5 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_0051e7d0[0]));
    }
    sp44 = (void *)(var_v0_5);
    igMetaField_SetFieldName(temp_s1_3, &sp44);
    if (sp44 != 0) {
        temp_a1_3 = (int *)((char *)sp44 - 8);
        temp_v0_3 = *(int *)((char *)(sp44) - 4) - 1;
        *(int *)((char *)(sp44) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    *(int *)((char *)(temp_s1_3) + 8) = 8;
    igMetaField_FinalizeDescriptor(temp_s1_3);
    ObjectList_AppendRetained(arg0, temp_s1_3);
    *(int *)((char *)(temp_s1_3) + 4) = (int)((int) (*(int *)((char *)(temp_s1_3) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_3) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_3);
    }
    temp_s1_4 = (void *)(FUN_00187b50(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_0051e7d8[0] == 0) {
        var_v0_7 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_8 = FUN_002eb010(0x10);
            if (var_v0_8 != 0) {
                var_v0_8 = StringPool_Construct(var_v0_8);
            }
            DAT_00586f20[0] = var_v0_8;
        }
        var_v0_7 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_0051e7d8[0]));
    }
    sp40 = (void *)(var_v0_7);
    igMetaField_SetFieldName(temp_s1_4, &sp40);
    if (sp40 != 0) {
        temp_a1_4 = (int *)((char *)sp40 - 8);
        temp_v0_4 = *(int *)((char *)(sp40) - 4) - 1;
        *(int *)((char *)(sp40) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_4, temp_a1_4);
        }
    }
    *(int *)((char *)(temp_s1_4) + 8) = 0x10;
    igMetaField_FinalizeDescriptor(temp_s1_4);
    ObjectList_AppendRetained(arg0, temp_s1_4);
    *(int *)((char *)(temp_s1_4) + 4) = (int)((int) (*(int *)((char *)(temp_s1_4) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_4) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_4);
    }
    temp_s1_5 = (void *)(FUN_00187b50(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_0051e7e0[0] == 0) {
        var_v0_9 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_10 = FUN_002eb010(0x10);
            if (var_v0_10 != 0) {
                var_v0_10 = StringPool_Construct(var_v0_10);
            }
            DAT_00586f20[0] = var_v0_10;
        }
        var_v0_9 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_0051e7e0[0]));
    }
    sp3C = (void *)(var_v0_9);
    igMetaField_SetFieldName(temp_s1_5, &sp3C);
    if (sp3C != 0) {
        temp_a1_5 = (int *)((char *)sp3C - 8);
        temp_v0_5 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v0_5;
        if (temp_v0_5 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_5, temp_a1_5);
        }
    }
    *(int *)((char *)(temp_s1_5) + 8) = 0x18;
    igMetaField_FinalizeDescriptor(temp_s1_5);
    ObjectList_AppendRetained(arg0, temp_s1_5);
    *(int *)((char *)(temp_s1_5) + 4) = (int)((int) (*(int *)((char *)(temp_s1_5) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_5) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_5);
    }
    temp_s1_6 = (void *)(FUN_00187b50(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_0051e7f0[0] == 0) {
        var_v0_11 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_12 = FUN_002eb010(0x10);
            if (var_v0_12 != 0) {
                var_v0_12 = StringPool_Construct(var_v0_12);
            }
            DAT_00586f20[0] = var_v0_12;
        }
        var_v0_11 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_0051e7f0[0]));
    }
    sp38 = (void *)(var_v0_11);
    igMetaField_SetFieldName(temp_s1_6, &sp38);
    if (sp38 != 0) {
        temp_a1_6 = (int *)((char *)sp38 - 8);
        temp_v0_6 = *(int *)((char *)(sp38) - 4) - 1;
        *(int *)((char *)(sp38) - 4) = temp_v0_6;
        if (temp_v0_6 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_6, temp_a1_6);
        }
    }
    *(int *)((char *)(temp_s1_6) + 8) = 0x20;
    igMetaField_FinalizeDescriptor(temp_s1_6);
    ObjectList_AppendRetained(arg0, temp_s1_6);
    *(int *)((char *)(temp_s1_6) + 4) = (int)((int) (*(int *)((char *)(temp_s1_6) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_6) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_6);
    }
}

int FUN_00453250(void) {
    if (DAT_0058c658[0] == 0) {
        DAT_0058c658[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c658[0];
}

igMetaObject *igAction_GetMetaObject(void)
{
    igMetaObject *g = g_igAction_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igAction_RunStaticInit();
    return g_igAction_metaObject[0];
}

void igAction_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igAction_Register);
}

void igAction_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAction_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAction_GetMetaObject,
        igAction_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAction_GetMetaObject(void) {
    igAction_GetMetaObject();
}

int FUN_00453370(unsigned short *arg0, unsigned short *arg1) {
    return *arg0 - *arg1;
}

int Gap__Bec__beFontImage__vfunc_23(beFontImage *arg0, int arg1) {
    if (FUN_00453830(arg0, arg1) < 0) {
        return 0;
    }
    return 2;
}

float Gap__Bec__beFontImage__vfunc_24(beFontImage *arg0, int arg1) {
    int temp_v0;
    igCharMetricsList *metrics;
    temp_v0 = FUN_00453830(arg0, arg1);
    if (temp_v0 < 0) {
        return 0.0f;
    }
    metrics = (igCharMetricsList *)arg0->_charMetricsList;
    return *(float *)((char *)((metrics->_data + (temp_v0 * 0x28))) + 4);
}

void Gap__Bec__beFontImage__vfunc_21(beFontImage *arg0, struct GlyphVertexBuffer *arg1, char *arg2) {
    struct GlyphPos p;
    int len;
    int i;
    int idx;
    char *s;
    struct GlyphMetricsRecord *rec;
    i = 0;
    p.y = arg0->_baseLine;
    p.x = 0.0f;
    len = arg1->f12;
    s = arg2;
    for (; *s != 0; s++) {
        idx = FUN_00453830(arg0, *s);
        if (idx >= 0) {
            if (i + 6 > len) {
                break;
            }
            rec = (struct GlyphMetricsRecord *)(((struct GlyphMetricsList *)arg0->_charMetricsList)->f16 + idx * 40);
            FUN_004535d0(arg0, (DW4VC_116_2 *)arg1, i, (P *)&p, (R_4535d0 *)rec);
            i += 6;
            p.x += rec->f4;
        }
    }
}

void Gap__Bec__beFontImage__vfunc_22(beFontImage *arg0, struct TextLayoutBuffer *arg1, unsigned short *arg2) {
    struct V2 p;
    int len;
    int i;
    int idx;
    int c;
    unsigned short *s;
    struct GlyphMetricsRecord *rec;
    i = 0;
    p.y = arg0->_baseLine;
    p.x = 0.0f;
    len = arg1->f12;
    s = arg2;
    for (; (c = *s) != 0; s++) {
        idx = FUN_00453830(arg0, c);
        if (idx >= 0) {
            if (i + 6 >= len) {
                break;
            }
            rec = (struct GlyphMetricsRecord *)((char *)((igCharMetricsList *)arg0->_charMetricsList)->_data + idx * 40);
            FUN_004535d0(arg0, (DW4VC_116_2 *)arg1, i, (P *)&p, (R_4535d0 *)rec);
            i += 6;
            p.x += rec->f4;
        }
    }
}

void FUN_004535d0(beFontImage *arg0, DW4VC_116_2 *arg1, int arg2, P *arg3, R_4535d0 *arg4) {
    V a, b, c, d, e, f;
    P g, h;
    float x0, y0, x1, y1, ta, tb;
    int i1, i2, i3, i4, i5;
    x0 = arg3->x;
    y0 = arg3->y;
    x0 = x0 + arg4->f8;
    y0 = y0 + arg4->f12;
    x1 = x0 + arg4->f16;
    y1 = y0 + arg4->f20;
    a.z = 0; a.x = x0; a.y = y0;
    arg1->vX(arg2, &a);
    b.x = x1; b.z = 0; b.y = y1;
    i1 = arg2 + 1;
    arg1->vX(i1, &b);
    c.x = x1; c.z = 0; c.y = y0;
    i2 = arg2 + 2;
    arg1->vX(i2, &c);
    d.y = y0; d.z = 0; d.x = x0;
    i3 = arg2 + 3;
    arg1->vX(i3, &d);
    e.x = x0; e.z = 0; e.y = y1;
    i4 = arg2 + 4;
    arg1->vX(i4, &e);
    f.x = x1; f.z = 0; f.y = y1;
    i5 = arg2 + 5;
    arg1->vX(i5, &f);
    ((DW4VC_200_3 *)arg1)->vX(0, arg2, &arg4->f24);
    ((DW4VC_200_3 *)arg1)->vX(0, i1, &arg4->f32);
    ta = arg4->f28; tb = arg4->f32; g.x = tb; g.y = ta;
    ((DW4VC_200_3 *)arg1)->vX(0, i2, &g);
    ((DW4VC_200_3 *)arg1)->vX(0, i3, &arg4->f24);
    ta = arg4->f36; tb = arg4->f24; h.x = tb; h.y = ta;
    ((DW4VC_200_3 *)arg1)->vX(0, i4, &h);
    ((DW4VC_200_3 *)arg1)->vX(0, i5, &arg4->f32);
}

int FUN_00453830(beFontImage *arg0, int arg1) {
    struct K k;
    k.key = arg1;
    return List_BinarySearch(arg0->_charMetricsList, &k, FUN_00453370, 0x28);
}

void Gap__Bec__beFontImage__vfunc_11(FontImage *self, int enable) {
    Gap__Core__igObject__vfunc_11(self);
    if (enable != 0) {
        ObjectList_AppendRetained((unsigned)self->layers, (void *)self->base);
        igSmartPointer<FillLayer> first((FillLayer *)FUN_00139600(igObject_GetAllocator(self)));
        first.get()->setEnabled(1);
        ObjectList_AppendRetained((unsigned)self->layers, first.get());
        igSmartPointer<OutlineLayer> second((OutlineLayer *)FUN_00131390(igObject_GetAllocator(self)));
        second.get()->setEnabled(1);
        ObjectList_AppendRetained((unsigned)self->layers, second.get());
        self->state = 0x10001;
    }
}

void FUN_00453980(int arg0, int arg1) {
    FUN_00453990((struct FontLayers_453990 *)arg0, *(int *)((char *)(*(int *)((char *)(arg0) + 36)) + 8), (struct FontLayerItem_453990 *)arg1);
}

struct InsertRef_453990 { struct FontLayerItem_453990 *p; };
struct FontLayerItem_453990 { char pad[4]; int refCount; char pad2[16]; int order; };
struct FontLayers_453990 { char pad[32]; int order; int list; };
void FUN_00453990(struct FontLayers_453990 *self, int index, struct FontLayerItem_453990 *item) {
    struct InsertRef_453990 r;
    int list;
    int msg[4];
    item->order = self->order;
    r.p = item;
    list = self->list;
    if (r.p != 0) r.p->refCount = r.p->refCount + 1;
    List_InsertWords(list, index, 1, &r);
    msg[0] = 3;
    msg[1] = 0;
    msg[2] = DAT_0058c618[0];
    msg[3] = index;
    FUN_004578c0((S_4578c0 *)self, (S_4578c0 *)msg);
}

void FUN_00453a20(void *arg0, int arg1) {
    FUN_00453980(*(int *)((char *)arg0 + 16), arg1);
}

int *Gap__Gui__igColorChanger__vfunc_23(void) {
    return (int *)&DAT_004e1170[0];
}

void FUN_00453a40(igBasicColorChanger *arg0, int arg1, int arg2, int arg3, void *arg4) {
    int var_v1;
    igBasicColorChanger *temp_v1;
    int idx;
    var_v1 = 0;
    if (arg3 != 0) {
        *(float *)&arg0->_disabledColor = (float) *(float *)((char *)(arg4) + 0);
        *(float *)((char *)(arg0) + 76) = (float) *(float *)((char *)(arg4) + 4);
        *(float *)((char *)(arg0) + 80) = (float) *(float *)((char *)(arg4) + 8);
        *(float *)((char *)(arg0) + 84) = (float) *(float *)((char *)(arg4) + 12);
        return;
    }
    if (arg1 != 0) {
        var_v1 += 1;
    }
    if (arg2 != 0) {
        var_v1 += 2;
    }
    idx = var_v1 * 0x10;
    temp_v1 = (igBasicColorChanger *)(idx + (int)arg0);
    *(float *)&temp_v1->_colors[0] = (float) *(float *)((char *)(arg4) + 0);
    *(float *)&temp_v1->_colors[1] = (float) *(float *)((char *)(arg4) + 4);
    *(float *)&temp_v1->_colors[2] = (float) *(float *)((char *)(arg4) + 8);
    *(float *)&temp_v1->_colors[3] = (float) *(float *)((char *)(arg4) + 12);
}

int Gap__Gui__igBasicColorChanger__vfunc_23(int arg0, void *arg1) {
    int i;
    if (*(unsigned char *)((char *)(arg1) + 12) == 0) {
        return arg0 + 0x48;
    }
    i = 0;
    if (*(unsigned char *)((char *)(arg1) + 13) != 0) {
        i = i + 1;
    }
    if (*(unsigned char *)((char *)(arg1) + 15) != 0) {
        i = i + 2;
    }
    return arg0 + i * 0x10 + 8;
}

int Gap__Gui__igOnOffColorChanger__vfunc_23(int arg0, OnOffColorState *s) { int n; bool t, f; if (!s->enabled) return arg0 + 0x48; t = s->on; n = 0; if (t) n += 1; f = s->hilite && t; if (s->current ^ f) n += 2; return arg0 + n * 0x10 + 8; }

void thunk_FUN_00453a40(igBasicColorChanger *arg0, int arg1, int arg2, int arg3, void *arg4)
{
    FUN_00453a40(arg0, arg1, arg2, arg3, arg4);
}

void FUN_00453b90(float *out, A *a) {
    B *b = a->b;
    float z0 = 0.0f, two = 2.0f; float dx = a->dx, dy = a->dy; float x = b->x, y = b->y, z = b->z; x += two * dx; y += two * dy; z += z0; out[0] = x; out[1] = y; out[2] = z;
}

void Gap__Gui__igDefaultAspect__vfunc_25(igDefaultAspect *arg0) {
    int i;
    void *l;

    for (i = 0; l = (void *)arg0->_elementList, i < *(int *)((char *)l + 8); i++) {
        FUN_001c5d10(arg0->_node, *(int *)((char *)((*(int *)(*(int *)((char *)l + 16) + (i * 4)))) + 16));
    }
    FUN_004540d0((S_4540d0 *)arg0);
    FUN_00453e70(arg0);
}

void Gap__Gui__igDefaultAspect__vfunc_26(A_453f70 *arg0) {
    R_453f70 *sp4C;
    int sp30[7];
    int var_s0;
    T_453f70 *temp_v1;

    var_s0 = arg0->f40->count - 1;
    while (var_s0 >= 0) {
        FUN_001c5eb0(&sp4C, arg0->f12, var_s0);
        if (sp4C != 0) {
            sp4C->refs = sp4C->refs - 1;
            if (((unsigned long long)((long long)sp4C->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(sp4C);
            }
        }
        var_s0 -= 1;
    }
    temp_v1 = arg0->f8;
    temp_v1->f16 = DAT_004e1058[0];
    temp_v1->f20 = DAT_004e105c[0];
    temp_v1->f24 = DAT_004e1060[0];
    sp30[0] = 2;
    sp30[1] = 0;
    sp30[2] = DAT_0058c468[0];
    FUN_004578c0((S_4578c0 *)arg0->f8, (S_4578c0 *)&sp30[0]);
}

void Gap__Gui__igDefaultAspect__vfunc_27(void *arg0, struct S_454050 *arg1) {
    int temp_a1;

    temp_a1 = arg1->f8;
    if ((temp_a1 == DAT_0058c450[0]) || (temp_a1 == DAT_0058c460[0]) || (temp_a1 == DAT_0058c290[0]) || (temp_a1 == DAT_0058c448[0])) {
        FUN_004540d0((S_4540d0 *)arg0);
        return;
    }
    if (temp_a1 == DAT_0058c468[0]) {
        FUN_00454180(arg0);
    }
}

void FUN_004540d0(S_4540d0 *arg0) {
    int i;
    E *e;
    float *v;
    V96 *o;

    for (i = 0; i < arg0->f40->count; i++) {
        e = arg0->f40->data[i];
        v = e->f12->vX(arg0->f8);
        o = e->f8;
        o->f24 = v[0];
        o->f28 = v[1];
        o->f32 = v[2];
        o->f36 = v[3];
        o->vX();
    }
}

void FUN_00454180(void *arg0) {
    int i;
    int *t;
    i = 0;
    while (t = *(int **)((char *)arg0 + 40), i < t[2]) {
        FUN_00453be0(*(int *)(t[4] + (i * 4)), *(int *)((char *)(arg0) + 8) + 0x10);
        i += 1;
    }
}

void FUN_004541f0(int *arg0, int *arg1) {
    int sp3C;
    int sp38;
    ((C22 *)arg0[4])->vX(arg1);
    ((C22 *)arg0)->vX((int *)arg0[4]);
    ((C22 *)arg0)->vX(arg1);
    ((C30 *)arg1)->vX(&sp3C, &sp38);
    ((C28 *)arg0)->vX(arg1, sp3C, sp38);
}

void FUN_00454290(void *arg0, int arg1) {
    FUN_002d6f50(*(int *)((char *)(arg0) + 12), arg1, 0);
}

void FUN_004542a0(Obj_4542a0 *arg0, int arg1) {
    int sp1C;
    FUN_002d7750(&sp1C, arg0->f12, arg1);
}

int FUN_004542d0(int *p)
{
    return FUN_002d7090(*(int *)((char *)p + 12));
}

void FUN_004542e0(S0 *arg0, int arg1, int arg2) {
    int sp1C;

    FUN_002d7760(&sp1C, arg0->fC, arg1, arg2);
}

void Gap__Gui__igEventDispatcher__vfunc_26(Owner *o, int unused, Cur *c) {
    int n = o->m2->m->count;
    int i = 0;
    while (i < n) {
        Item *it = o->m2->m->items[i];
        float x = c->GetX();
        float y = c->GetY();
        if (it->hit(x, y) & 0xFF) break;
        i++;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_27(S_4544d0 *arg0, int arg1, int arg2, int arg3) {
    int n = arg0->m->list->cnt;
    int i;
    for (i = 0; i < n; i++) {
        if (arg0->m->list->arr[i]->vX(arg3, 1) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_28(S_454570 *arg0, int a1, int a2, int arg3) {
    int n = arg0->m->list->count;
    int i;
    for (i = 0; i < n; i++) {
        if (arg0->m->list->data[i]->vX(arg3, 0) != 0) {
            break;
        }
    }
}

void Gap__Gui__igEventDispatcher__vfunc_29(O_454610 *arg0, int arg1, int arg2, int arg3) {
    int n = arg0->m->list->count;
    int i;
    for (i = 0; i < n; i++) {
        if (arg0->m->list->items[i]->vX(arg2, arg3) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_30(T_4546c0 *arg0, int arg1, int arg2, int arg3) {
    int temp_s1;
    int var_s0;

    temp_s1 = arg0->f12->f8->f8;
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        if (arg0->f12->f8->f16[var_s0]->vX(arg2, arg3) & 0xFF) {
            break;
        }
    }
}

void Gap__Gui__igEventDispatcher__vfunc_31(O_454770 *arg0, V104 *arg1) {
    int n = arg0->m->list->count;
    int found = 0;
    int i = 0;
    for (; i < n; i++) {
        found = 0xFF & arg0->m->list->items[i]->vX();
        if (found != 0) break;
    }
    if (!found) arg1->vY();
}

/* matching construct: _receivers/_controllerManager/_objectList/_controllers/_data are 4-byte reference fields in the reflected structs; the casts give the typed views (no layout effect) */
void Gap__Gui__igEventDispatcher__vfunc_32(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f0, float f1) {
    igDataList *l1 = (igDataList *)((igControllerManager *)arg0->_controllerManager)->_controllers;
    K_454820 key(arg2);
    int idx = Finder::Find(l1, key);
    int n2 = ((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_count;
    int j = 0;
    for (; j < n2; j++) {
        Elem *o = ((Elem **)((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_data)[j];
        if (o->vX(idx, arg3, f0, f1) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_33(igEventDispatcher *arg0, int arg1, int arg2, int arg3) {
    igDataList *l1 = (igDataList *)((igControllerManager *)arg0->_controllerManager)->_controllers;
    K_454930 key(arg2);
    int idx = Finder_454930::Find(l1, key);
    int n2 = ((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_count;
    int j = 0;
    for (; j < n2; j++) {
        Lis *o = ((Lis **)((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_data)[j];
        if (o->v108(idx, arg3, 1) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_34(EventDispatcherView *self, int, DispatchKey *key, int arg3) {
    int idx;
    int cnt;
    int i;
    igTDataList<DispatchKey *> *l;
    l = self->keys->list;
    idx = l->find(key);
    cnt = self->receivers->list->_count;
    for (i = 0; i < cnt; i++) {
        if (self->receivers->list->_data[i]->onKeyEvent(idx, arg3, 0) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_35(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f) {
    IList *l1 = ((Hold *)arg0->_controllerManager)->l;
    K_454b30 key(arg2);
    int idx = Finder_454b30::Find(l1, key);
    int n2 = ((Hold2 *)arg0->_receivers)->l->n;
    int j = 0;
    for (; j < n2; j++) {
        Lis_454b30 *o = ((Hold2 *)arg0->_receivers)->l->data[j];
        if (o->v112(idx, arg3, f) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_39(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f) {
    igControllerList *l1 = (igControllerList *)((igControllerManager *)arg0->_controllerManager)->_controllers;
    K_454c30 key(arg2);
    int idx = Finder_454c30::Find(l1, key);
    int n2 = ((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_count;
    int j = 0;
    for (; j < n2; j++) {
        Lis_454c30 *o = ((Lis_454c30 **)((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_data)[j];
        if (o->v120(idx, arg3, f) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_38(EventDispatcherView *self, int, DispatchKey *key, int arg3, float f) {
    igTDataList<DispatchKey *> *l = self->keys->list;
    int idx = l->find(key);
    int n = self->receivers->list->_count;
    for (int i = 0; i < n; i++) {
        unsigned char r = self->receivers->list->_data[i]->onAxisEvent(idx, arg3, f);
        if (r) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_36(igEventDispatcher *arg0, int arg1, int arg2) {
    igControllerList *l1 = (igControllerList *)((igControllerManager *)arg0->_controllerManager)->_controllers;
    K_454e30 key(arg2);
    int idx = Finder_454e30::Find(l1, key);
    igObjectList *recv = (igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList;
    int n2 = recv->_count;
    int j = 0;
    for (; j < n2; j++) {
        Lis_454e30 *o = ((Lis_454e30 **)((igObjectList *)((igEventReceiverOrderedList *)arg0->_receivers)->_objectList)->_data)[j];
        if (o->v124(idx, 1) & 0xFF) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_37(EventDispatcherView *self, int, DispatchKey *key) {
    igTDataList<DispatchKey *> *l = self->keys->list;
    int idx = l->find(key);
    int n = self->receivers->list->_count;
    for (int i = 0; i < n; i++) {
        unsigned char r = self->receivers->list->_data[i]->onButtonEvent(idx, 0);
        if (r) break;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_40(O_455010 *arg0, int arg1, int arg2) {
    int n;
    int i;
    E_455010 *e;
    n = arg0->f12->l2->n;
    i = 0;
    while (i < n) {
        e = arg0->f12->l2->arr[i];
        if (e->vX(arg2, 1) & 0xFF) break;
        i += 1;
    }
}

void Gap__Gui__igEventDispatcher__vfunc_41(int *arg0, int arg1, int arg2) {
    int temp_s1;
    int var_s0;
    A_4550b0 *temp_a0;
    temp_s1 = *(int *)(*(int *)((char *)(arg0[3]) + 8) + 8);
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        temp_a0 = (A_4550b0 *)(*(int *)(*(int *)(*(int *)((char *)(arg0[3]) + 8) + 16) + (var_s0 * 4)));
        if (temp_a0->vX(arg2, 0) & 0xFF) {
            break;
        }
    }
}

void Gap__Gui__igFieldChangeView__vfunc_24(void *arg0, void *arg1) {
    int temp_a0;

    if ((*(int *)((char *)arg1 + 0) == 0) || (*(int *)((char *)arg0 + 16) == *(int *)((char *)arg1 + 8))) {
        temp_a0 = *(int *)((char *)arg0 + 12);
        if (temp_a0 != 0) {
            FUN_004552e0((int *)temp_a0, (int *)arg0);
        }
    }
}

void FUN_004551a0(struct S_4551a0 *arg0, int arg1, int arg2) {
    int sp[3];
    int b;
    FUN_002fd150(arg0->b, arg0->a, arg2, arg1);
    b = arg0->b;
    sp[0] = 2;
    sp[2] = b;
    sp[1] = (int)arg0;
    FUN_004578c0((S_4578c0 *)arg0->a, (S_4578c0 *)sp);
}

void FUN_004551f0(void *arg0v, int arg1, void *arg2v) {
    A_4551f0 *arg0 = (A_4551f0 *)arg0v;
    Rc_4551f0 *arg2 = (Rc_4551f0 *)arg2v;
    Ref_4551f0 sp4C;
    sp4C.p = (Rc_4551f0 *)FUN_00450de0(igObject_GetAllocator());
    ObjectList_AppendRetained(arg0->f8, sp4C.p);
    sp4C.p->f12 = (int)arg0;
    Rc_4551f0 *t = sp4C.p;
    if (arg2 != 0) {
        arg2->rc = arg2->rc + 1;
    }
    Rc_4551f0 *old = (Rc_4551f0 *)t->f16;
    if (old != 0) {
        old->rc = old->rc - 1;
        if (((unsigned long long)((long long)old->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(old);
        }
    }
    t->f16 = (int)arg2;
    FUN_00457e90((S0_457e90 *)sp4C.p, arg1);
}

void FUN_004552e0(int *arg0, int *arg1) {
    int n = *(int *)(arg0[2] + 8);
    int i = 0;
    while (i < n) {
        int a = ((int *)*(int *)(arg0[2] + 16))[i];
        if (a != (int)arg1) {
            FUN_004551a0((S_4551a0 *)a, arg1[2], arg1[4]);
        }
        i++;
    }
}

int FUN_00455370(VC_455370 *arg0, char *arg1) {
    int s = 0;
    char *p = arg1;
    while (*p != 0) {
        s += arg0->vX(*p);
        p++;
    }
    return s;
}

int FUN_004553e0(void **arg0, unsigned short *arg1) {
    int sum;
    unsigned short *p;
    int c;
    p = arg1;
    sum = 0;
    while ((c = *p) != 0) {
        sum += ((VC100 *)arg0)->vX(c);
        p += 1;
    }
    return sum;
}

void Gap__Gui__igGuiComponent__vfunc_13(void *arg0) {
    Gap__Core__igObject__vfunc_11();
    *(int *)((char *)(*(int *)((char *)(arg0) + 28)) + 32) = (int)(arg0);
}

void FUN_00455470(A_455470 *arg0) {
    C *temp_a0;

    if (arg0->f20 != 0) {
        temp_a0 = arg0->f14;
        if (temp_a0 != 0) {
            FUN_00457e90((S0_457e90 *)temp_a0, 0);
            arg0->f14->f0c = 0;
        }
        FUN_00457e90((S0_457e90 *)arg0->f0c, 0);
        arg0->f10->f20 = 0;
        arg0->f20 = 0;
    }
}

void Gap__Gui__igGuiComponent__vfunc_10(void *arg0) {
    Gap__Core__igObject__vfunc_08__002ff0f0();
    if (*(unsigned char *)((char *)(arg0) + 32) != 0) {
        FUN_00455470((A_455470 *)arg0);
    }
}

int FUN_00455510(A_455510 *arg0) {
    int n = FUN_001c59e0();
    int i;
    O_455510 *o;
    if (n <= 0) return 0;
    i = n - 1;
    while (i >= 0) {
        o = O_455510::cast(arg0->b->arr[i]);
        if (o != 0) return o->v;
        i--;
    }
    return 0;
}

void *FUN_004555c0(igGuiComponentView *self, void *component, void *context)
{
    return self->_controller->vfunc_23(component, context);
}

int FUN_004555e0(void *arg0) {
    return *(unsigned char *)((char *)(*(int *)((char *)(arg0) + 16)) + 12);
}

void FUN_004555f0(int *p, unsigned char value)
{
    FUN_004558b0((S_4558b0 *)*(int *)((char *)p + 16), value);
}

void FUN_00455600(int *p, unsigned char value)
{
    FUN_00455900((S_455900 *)*(int *)((char *)p + 16), value);
}

void FUN_00455610(int *p, unsigned char value)
{
    FUN_00455950((S_455950 *)*(int *)((char *)p + 16), value);
}

unsigned char FUN_00455620(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 15);
}

void Gap__Gui__igDefaultAspect__vfunc_24(igDefaultAspect *arg0, int *arg1) {
    int temp_a2;

    temp_a2 = *arg1;
    switch (temp_a2) {
    case 0:
        ((DW4VC_100_1 *)(((char *)(arg0) + 0)))->vX((int)(arg1));
        return;
    case 1:
        ((DW4VC_104_1 *)(((char *)(arg0) + 0)))->vX((int)(arg1));
        return;
    default:
        if (arg0->_model != 0) {
            ((DW4VC_108_1 *)(((char *)(arg0) + 0)))->vX((int)(arg1));
        }
        return;
    }
}

void Gap__Gui__igGuiComponentController__vfunc_23(igGuiComponentController *self, int model) {
    igObject_IsKindOf(model, igGuiComponentModel_GetMetaObject());
}

void Gap__Gui__igGuiComponentController__vfunc_24(igGuiComponentController *arg0, void *arg1) {
    int temp_a1;
    igGuiComponentModel *temp_a2;

    temp_a1 = *(int *)((char *)(arg1) + 8);
    temp_a2 = (igGuiComponentModel *)(arg0->_model);
    if (temp_a1 == DAT_0058c448[0]) {
        if (temp_a2->_enabled != 0) {
            ((DW4VC_104_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_108_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == DAT_0058c450[0]) {
        if (temp_a2->_hasFocus != 0) {
            ((DW4VC_112_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_116_2_4556e0 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == DAT_0058c458[0]) {
        if (temp_a2->_mouseOver != 0) {
            ((DW4VC_120_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_124_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == DAT_0058c460[0]) {
        if (temp_a2->_pushed != 0) {
            ((DW4VC_128_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_132_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
    }
}

void Gap__Gui__igGuiComponentController__vfunc_33(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_32(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_31(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_30(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_29(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_28(void) {

}

void Gap__Gui__igGuiComponentController__vfunc_27(void) {
}

void Gap__Gui__igGuiComponentController__vfunc_26(void) {
}

int Gap__Gui__igGuiComponentController__vfunc_25(void) {
    return 0;
}

void FUN_004558b0(struct S_4558b0 *arg0, unsigned char arg1) {
    int sp10[4];
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != arg1) {
        arg0->b = arg1;
        sp10[0] = 2;
        sp10[1] = 0;
        sp10[2] = DAT_0058c450[0];
        FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)&sp10[0]);
    }
}

void FUN_00455900(struct S_455900 *arg0, unsigned char arg1) {
    int sp10[3];
    unsigned char temp_a2;

    temp_a2 = arg0->f;
    if (temp_a2 != arg1) {
        arg0->f = arg1;
        sp10[0] = 2;
        sp10[1] = 0;
        sp10[2] = DAT_0058c458[0];
        FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)sp10);
    }
}

void FUN_00455950(S_455950 *arg0, unsigned char arg1) {
    int sp10[3];
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != (arg1 & 0xFF)) {
        arg0->b = arg1;
        sp10[0] = 2;
        sp10[1] = 0;
        sp10[2] = DAT_0058c460[0];
        FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)sp10);
    }
}

void FUN_004559a0(struct S_4559a0 *arg0, unsigned char arg1) {
    int sp[3];
    unsigned char temp_a2;

    temp_a2 = arg0->b;
    if (temp_a2 != arg1) {
        arg0->b = arg1;
        sp[0] = 2;
        sp[1] = 0;
        sp[2] = DAT_0058c470[0];
        FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)sp);
    }
}

void Gap__Gui__igGuiComponentNode__vfunc_13(Node *self) {
    Vec3 origin;
    FUN_001d3550(self);
    igSmartPointer<igObject> transform(FUN_0018a660(igObject_GetAllocator(self)));
    origin.x = 0;
    origin.y = 0;
    origin.z = 0;
    FUN_001900d0(transform.get(), &origin);
    igObject *retained = transform.get();
    if (retained != 0) {
        retained->_refCount = retained->_refCount + 1;
    }
    igObject *previous = self->child;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->child = retained;
}

int FUN_00455ad0(int arg0, int arg1, int arg2) {
    if (DAT_0058c678[0] != 0) {
        FUN_00455f50((Z *)DAT_0058c678[0], (Y *)arg2);
    }
    return 0;
}

void Gap__Gui__igGuiSystemModel__vfunc_13(int arg0, int arg1) {
    int args[4];
    float vec[3];

    Gap__Core__igObject__vfunc_11();
    if (arg1 != 0) {
        igMatrix44f_SetIdentity(arg0 + 0x20);
        vec[0] = 0.375f;
        vec[2] = -0.5f;
        vec[1] = 0.375f;
        Matrix44_SetTranslation(arg0 + 0x20, vec);
        args[0] = 2;
        args[1] = 0;
        args[2] = DAT_0058c3e8[0];
        FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)args);
    }
}

void Gap__Gui__igWindowSizeObserver__vfunc_24(void *arg0, int *arg1) {
    int sp30[3];
    struct T_455b90 *temp_s0;
    if ((arg1[2] == DAT_0058c3d0[0]) || (arg1[0] == 0)) {
        temp_s0 = *(struct T_455b90 **)((char *)arg0 + 8);
        FUN_00191860((char *)temp_s0 + 0x60, 0.0f, temp_s0->w, temp_s0->h, 0.0f, 0.0f, 2.0f);
        sp30[0] = 2;
        sp30[1] = (int)arg0;
        sp30[2] = DAT_0058c3f0[0];
        FUN_004578c0((S_4578c0 *)temp_s0, (S_4578c0 *)sp30);
    }
}

static inline int count_of(const ObserverIntListView *list) { return list->cnt; }

static inline void setEvent(MousePosObserverView *self, const igSmartPointer<ObserverEventView> &event) {
    igObject *retained = event.get();
    ObserverModelView *model = self->m;
    igObject *previous;
    if (retained != 0) {
        retained->_refCount = retained->_refCount + 1;
    }
    previous = model->ref;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    model->ref = retained;
}

void Gap__Gui__igMousePosObserver__vfunc_13(MousePosObserverView *self) {
    ObserverEventView *created;
    ObserverIntListView *list;
    int top;
    Gap__Core__igObject__vfunc_11(self);
    igSmartPointer<ObserverEventView> event(FUN_0019e680(igObject_GetAllocator(self)));
    created = event.get();
    ObjectList_AppendRetained(created->a, self->f20);
    list = created->list;
    top = count_of(list);
    if (top < list->cap) {
        list->cnt = list->cnt + 1;
    } else {
        List_Resize(list, top + 1, 4);
    }
    list->data[top] = 2;
    setEvent(self, event);
    self->m->flags = 0;
    self->m->flags = self->m->flags | 4;
    self->m->fn = (int)&FUN_00455ad0;
}

struct Vec3f_455d80 { float x; float y; float z; Vec3f_455d80() {} Vec3f_455d80(float a, float b, float c) : x(a), y(b), z(c) {} };
struct GuiMessage_455d80 { int handled; int f4; int type; };
void Gap__Gui__igMousePosObserver__vfunc_24(igMousePosObserver *self, struct GuiMessage_455d80 *msg) {
    igGuiSystemModel *model;
    int type;
    model = (igGuiSystemModel *)self->_model;
    type = msg->type;
    if (type == DAT_0058c3d8[0]) {
        Vec3f_455d80 v(model->_mousePosition[0], model->_mousePosition[1], 0.0f);
        Vec3f_455d80 p;
        FUN_00192fc0(&v, &v, self->_inverseProjectionMatrix);
        p = v;
        FUN_00456b80((int *)self->_guiSystem, &p.x);
        FUN_00456050(self, model);
    } else if (type == DAT_0058c3f0[0]) {
        int result;
        FUN_00191f30(&result, self->_inverseProjectionMatrix, model->_projectionMatrix);
    } else if (type == DAT_0058c3e0[0]) {
        igObject *under;
        int m[4];
        under = (igObject *)model->_componentUnderMouse;
        if ((igObject *)model->_focusedComponent != under) {
            FUN_00456c20(model, (igGuiComponent *)under);
        }
        if (model->_mousePressed) {
            if (under != 0) {
                under->_refCount = under->_refCount + 1;
            }
            igRelease((igObject *)model->_pushedComponent);
            model->_pushedComponent = (int)under;
        } else {
            igRelease((igObject *)model->_pushedComponent);
            model->_pushedComponent = 0;
        }
        m[0] = 2;
        m[1] = 0;
        m[2] = DAT_0058c418[0];
        FUN_004578c0((S_4578c0 *)model, (S_4578c0 *)m);
    } else if (msg->handled == 0) {
        int result;
        FUN_00191f30(&result, self->_inverseProjectionMatrix, model->_projectionMatrix);
    }
}

static inline void setPick(Z *z, const igSmartPointer<Obj_455f50> &value) {
    Obj_455f50 *held = value.get();
    Obj_455f50 *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = z->f32;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    z->f32 = held;
}

void FUN_00455f50(Z *arg0, Y *arg1) {
    int s1 = arg1->f8;
    if (arg1->f20 <= arg0->f24) {
        arg0->f28 = 1;
        arg0->f24 = arg1->f20;
        setPick(arg0, igSmartPointer<Obj_455f50>(FUN_0019f630(igObject_GetAllocator(arg0))));
        FUN_001c5790(arg0->f32, s1);
    }
}

/* matching construct: the *Ref fields are 4-byte arena handles in the reflected structs; the casts give the typed views (no layout effect) */
void FUN_00456050(igMousePosObserver *a, igGuiSystemModel *b) {
    float v2[3];
    float v1[3];
    int sp[3];
    igObject *s0 = 0;
    if (b->_rootComponent != 0) {
        float x, y;
        igObject *t;
        FUN_001ce970((void *)a->_intersectTraversal);
        x = ((float *)b->_mousePosition)[0];
        y = ((float *)b->_mousePosition)[1];
        v2[0] = x; v2[1] = y; v2[2] = -10.0f;
        v1[0] = x; v1[1] = y; v1[2] = 10.0f;
        FUN_0018d2b0((void *)a->_ray, v2, v1);
        FUN_0018d360((void *)a->_ray, &a->_inverseProjectionMatrix);
        a->_impactLength = ((igRay *)a->_ray)->_len;
        a->_hit = 0;
        t = (igObject *)a->_hitPath;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        a->_hitPath = 0;
        DAT_0058c678[0] = (int)a;
        ((IntersectTraversalCalls *)a->_intersectTraversal)->v23(((igGuiComponent *)b->_rootComponent)->_node);
        DAT_0058c678[0] = 0;
        if (a->_hit != 0) {
            s0 = (igObject *)FUN_00455510((A_455510 *)((void *)a->_hitPath));
        }
    }
    if (s0 != 0) {
        s0->_refCount = s0->_refCount + 1;
    }
    {
        igObject *t = (igObject *)b->_componentUnderMouse;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    b->_componentUnderMouse = (int)s0;
    sp[0] = 2;
    sp[1] = (int)a;
    sp[2] = DAT_0058c410[0];
    FUN_004578c0((S_4578c0 *)b, (S_4578c0 *)sp);
}

static inline void setComponent_4561e0(int *slot, igObject *next) {
    if (next != 0) {
        next->_refCount = next->_refCount + 1;
    }
    igRelease((igObject *)*slot);
    *slot = (int)next;
}
void Gap__Gui__igActiveComponentsObserver__vfunc_24(igActiveComponentsObserver *self, struct GuiMessage_455d80 *msg) {
    igGuiSystemModel *model;
    int type;
    type = msg->type;
    model = (igGuiSystemModel *)self->_model;
    if (type == DAT_0058c410[0]) {
        igObject *under = (igObject *)model->_componentUnderMouse;
        if ((igObject *)self->_oldComponentUnderMouse != under) {
            if (self->_oldComponentUnderMouse != 0) {
                FUN_00455600((int *)self->_oldComponentUnderMouse, 0);
            }
            if (under != 0) {
                FUN_00455600((int *)under, 1);
            }
        }
        if (under != 0 && FUN_004555e0(under) != 0 && under != (igObject *)model->_focusedComponent) {
            FUN_00456c20(model, (igGuiComponent *)under);
        }
        setComponent_4561e0(&self->_oldComponentUnderMouse, under);
    } else if (type == DAT_0058c408[0]) {
        igObject *focused = (igObject *)model->_focusedComponent;
        void *common = FUN_004565c0((int)self, focused);
        if (self->_oldFocusedComponent != 0) {
            FUN_004555f0((int *)self->_oldFocusedComponent, 0);
            FUN_00456540((int)self, (N *)self->_oldFocusedComponent, (N *)common, 0);
        }
        if (focused != 0) {
            FUN_004555f0((int *)focused, 1);
            FUN_00456540((int)self, (N *)focused, (N *)common, 1);
        }
        setComponent_4561e0(&self->_oldFocusedComponent, focused);
    } else if (type == DAT_0058c418[0]) {
        igObject *pushed = (igObject *)model->_pushedComponent;
        if (self->_oldPushedComponent != 0) {
            FUN_00455610((int *)self->_oldPushedComponent, 0);
        }
        if (pushed != 0) {
            FUN_00455610((int *)pushed, 1);
        }
        setComponent_4561e0(&self->_oldPushedComponent, pushed);
    } else if (msg->handled == 0) {
        setComponent_4561e0(&self->_oldPushedComponent, (igObject *)model->_pushedComponent);
        setComponent_4561e0(&self->_oldFocusedComponent, (igObject *)model->_focusedComponent);
        setComponent_4561e0(&self->_oldComponentUnderMouse, (igObject *)model->_componentUnderMouse);
        if (self->_oldPushedComponent != 0) {
            FUN_00455610((int *)self->_oldPushedComponent, 1);
        }
        if (self->_oldFocusedComponent != 0) {
            FUN_004555f0((int *)self->_oldFocusedComponent, 1);
        }
        if (self->_oldComponentUnderMouse != 0) {
            FUN_00455600((int *)self->_oldComponentUnderMouse, 1);
        }
    }
}

int FUN_00456540(int arg0, N *arg1, N *arg2, unsigned char arg3) {
    int r;

    if (arg1 != 0) {
        if (arg1 == arg2) {
            return r;
        }
        FUN_004559a0((S_4559a0 *)arg1->f10, arg3);
        r = FUN_00456540(arg0, arg1->f18, arg2, arg3);
    }
    return r;
}

void *FUN_004565c0(int arg0, void *arg1) {
    if (arg1 == 0) {
        return 0;
    }
    if (*(unsigned char *)(*(int *)((char *)arg1 + 16) + 28) != 0) {
        return arg1;
    }
    return FUN_004565c0(arg0, *(void **)((char *)arg1 + 24));
}

void Gap__Gui__igGuiSystemRenderer__vfunc_23(int *arg0) {
    int m[16];
    ((Obj_456610 *)arg0[5])->vX(arg0[2]);
    Matrix44_Copy(m, (char *)arg0[4] + 0x20);
    FUN_001b6ee0((void *)arg0[5], m);
}

void Gap__Gui__igGuiSystemRenderer__vfunc_24(void) {

}

void Gap__Gui__igGuiSystemRenderer__vfunc_25(int *arg0) {
    igObject *temp_v0;
    igObject *temp_a0_4;
    ((C29 *)arg0[5])->vX();
    ((C23 *)arg0[5])->vX(arg0[3]);
    temp_v0 = ((C28_456670 *)arg0[5])->vX();
    if (temp_v0 != 0) {
        temp_v0->_refCount = temp_v0->_refCount + 1;
    }
    temp_a0_4 = (igObject *)arg0[6];
    if (temp_a0_4 != 0) {
        temp_a0_4->_refCount = temp_a0_4->_refCount - 1;
        if ((temp_a0_4->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0_4);
        }
    }
    arg0[6] = (int)temp_v0;
}

void Gap__Gui__igGuiSystemRenderer__vfunc_26(char *arg0) {
    ((CA *)(*(int *)(arg0 + 8)))->vX(0, *(int *)(arg0 + 16) + 0x60);
    ((CB *)(*(int *)(arg0 + 24)))->vX(*(int *)(arg0 + 8));
}

static inline void set(R_456780 *&field, R_456780 *value) {
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    R_456780 *old = field;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    field = value;
}

void Gap__Gui__igGuiSystem__vfunc_13(A_456780 *self) {
    Gap__Core__igObject__vfunc_11(self);
    igSmartPointer<R_456780> first(0);
    int allocator = igObject_GetAllocator(self);
    first.release();
    first.p = (R_456780 *)FUN_0044f0b0(allocator);
    FUN_00457e90((S0_457e90 *)(first.get()), self->f12);
    ObjectList_AppendRetained(self->f16, first.get());
    igSmartPointer<R_456780> second((R_456780 *)FUN_0044ecb0(igObject_GetAllocator(self)));
    second.get()->wc = (int)self;
    FUN_00457e90((S0_457e90 *)(second.get()), self->f12);
    ObjectList_AppendRetained(self->f16, second.get());
    allocator = igObject_GetAllocator(self);
    first.release();
    first.p = (R_456780 *)FUN_0044e990(allocator);
    FUN_00457e90((S0_457e90 *)(first.get()), self->f12);
    ObjectList_AppendRetained(self->f16, first.get());
    FUN_001c5d10(self->f20, self->f28);
    R_456780 *value = self->f20;
    X_456780 *x = self->f8;
    set(x->f12, value);
    value = (R_456780 *)self->f12;
    x = self->f8;
    set(x->f16, value);
}

void FUN_004569c0(O_4569c0 *arg0, int arg1) {
    T_4569c0 *temp_a0;
    arg0->f32 = arg1;
    if (arg1 != 0) {
        temp_a0 = arg0->m->t;
        temp_a0->f24 = 1.0f;
        temp_a0->f28 = 1.0f;
        temp_a0->f32 = 1.0f;
        temp_a0->f36 = 1.0f;
        temp_a0->vX();
        return;
    }
    temp_a0 = arg0->m->t;
    temp_a0->f24 = DAT_004e1170[0];
    temp_a0->f28 = DAT_004e1174[0];
    temp_a0->f32 = DAT_004e1178[0];
    temp_a0->f36 = DAT_004e117c[0];
    temp_a0->vX();
}

void FUN_00456a60(A_456a60 *arg0, R_456a60 *arg1) {
    Rc_456a60 *sp4C;
    V3 sp30;
    int var_v0;
    Rc_456a60 *temp_a0;
    P_456a60 *temp_a1;
    Q *temp_v0;

    if (arg1 != 0) {
        ((Rc_456a60 *)arg1)->rc = ((Rc_456a60 *)arg1)->rc + 1;
    }
    temp_a0 = arg0->f24;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if (((unsigned long long)((long long)temp_a0->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f24 = (Rc_456a60 *)arg1;
    temp_a1 = arg0->f28;
    temp_v0 = temp_a1->f28;
    if (temp_v0 != 0) {
        var_v0 = temp_v0->f8;
    } else {
        var_v0 = 0;
    }
    if (var_v0 > 0) {
        FUN_001c5eb0(&sp4C, temp_a1, 0);
        if (sp4C != 0) {
            sp4C->rc = sp4C->rc - 1;
            if (((unsigned long long)((long long)sp4C->rc << 0x29) >> 0x29) == 0) {
                igObject_Destroy(sp4C);
            }
        }
    }
    if (arg1 != 0) {
        FUN_001c5d10(arg0->f28, arg1->f8->f8);
    }
    FUN_004569c0((O_4569c0 *)arg0, arg0->f32);
    sp30.a = 2;
    sp30.b = 0;
    sp30.c = DAT_0058c3d8[0];
    FUN_004578c0((S_4578c0 *)arg0->f12, (S_4578c0 *)&sp30);
}

void FUN_00456b80(int *arg0, float *arg1) {
    float m[16];
    struct P_456b80 *p;
    float fx;
    float fy;
    float z;

    p = (struct P_456b80 *)arg0[6];
    if (p != 0) {
        fx = p->x;
        fy = p->y;
        z = 0.0f;
        igMatrix44f_SetIdentity(m);
        arg1[0] = arg1[0] - fx;
        arg1[1] = arg1[1] - fy;
        arg1[2] = arg1[2] - z;
        Matrix44_SetTranslation(m, arg1);
        ((Obj_456b80 *)arg0[7])->vX(m);
    }
}

void FUN_00456c20(igGuiSystemModel *arg0, igGuiComponent *arg1) {
    int sp30[3];
    igGuiComponent *o;
    if (arg1 != 0) {
        arg1->_refCount = arg1->_refCount + 1;
    }
    o = (igGuiComponent *)arg0->_focusedComponent;
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->_focusedComponent = (int)arg1;
    sp30[0] = 2;
    sp30[1] = 0;
    sp30[2] = DAT_0058c408[0];
    FUN_004578c0((S_4578c0 *)arg0, (S_4578c0 *)sp30);
}

void FUN_00456cc0(W *arg0, T_456cc0 *arg1) {
    T_456cc0 *sp5C; int sp40[4]; T_456cc0 **p; T_456cc0 *old; int v; LL *l;
    if (arg0->f12->f164 != 0) { arg0->f12->f164->f8 = 0; }
    p = &arg0->f12->f164;
    if (arg1 != 0) { arg1->references = arg1->references + 1; }
    old = *p;
    if (old != 0) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0) { igObject_Destroy(old); }
    }
    *p = arg1;
    sp40[0] = 2;
    sp40[1] = 0;
    sp40[2] = DAT_0058c400[0];
    FUN_004578c0((S_4578c0 *)arg0->f12, (S_4578c0 *)sp40);
    l = arg0->f20->f28;
    if (l != 0) { v = l->f8; } else { v = 0; }
    if (v > 1) {
        FUN_001c5eb0(&sp5C, arg0->f20, 0);
        if (sp5C != 0) {
        --sp5C->references;
        if (((unsigned long long)(long long)sp5C->references & 0x7fffffULL) == 0) { igObject_Destroy(sp5C); }
        }
    }
    if (arg1 != 0) { arg0->f20->v140(0, arg1->f28); }
    if (arg1 != 0) { arg1->f8 = (int)arg0; }
}

void *FUN_00456e10(struct O_456e10 *arg0, struct N_456e10 *arg1, int arg2) {
    struct N_456e10 *temp_s0;
    void *var_v0;

    if (arg1 != 0) {
        while (1) {
            temp_s0 = arg1->f24;
            if (temp_s0 == 0) {
                return 0;
            }
            var_v0 = FUN_004555c0((igGuiComponentView *)temp_s0, (void *)arg1, (void *)arg2);
            arg1 = temp_s0;
            if (var_v0 != 0) {
                break;
            }
        }
    } else {
        var_v0 = arg0->f12->f164;
    }
    while (var_v0 != 0) {
        arg1 = (struct N_456e10 *)var_v0;
        var_v0 = FUN_004555c0((igGuiComponentView *)var_v0, (void *)0, (void *)arg2);
    }
    return arg1;
}

void FUN_00456eb0(Ctl *arg0, int arg1) {
    Item2 *s0;
    int ok;
    ok = 0;
    s0 = arg0->f12->f168;
    if (s0 != 0) {
        ok = s0->f12->test() & 0xFF;
    }
    if (ok == 0) {
        do {
            s0 = (Item2 *)FUN_00456e10((O_456e10 *)arg0, (N_456e10 *)s0, arg1);
            if (s0 == arg0->f12->f168 || s0 == 0) break;
        } while ((FUN_004555e0(s0) != 0) ^ 1);
    }
    FUN_00456c20((igGuiSystemModel *)arg0->f12, (igGuiComponent *)s0);
}

int Gap__Gui__igGuiComponentController__vfunc_34(void) {
    return 0;
}

bool Gap__Gui__igGuiSystem__vfunc_23(Ob *arg0, int arg1, int arg2) {
    if (arg0->f12->f160 == 0) {
        return false;
    }
    bool r = false;
    switch (arg1) {
    case 0x81:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 2);
        }
        r = true;
        break;
    case 0x83:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 3);
        }
        r = true;
        break;
    case 0x80:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 0);
        }
        r = true;
        break;
    case 0x82:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 1);
        }
        r = true;
        break;
    case 0x9:
        if (arg2 != 0) {
            FUN_00456eb0((Ctl *)arg0, 4);
        }
        r = true;
        break;
    case 0xD:
    case 0x20:
        if (arg2 != 0) {
            FUN_004570a0(arg0);
        }
        r = true;
        break;
    default:
        break;
    }
    return r;
}

void FUN_004570a0(void *arg0) {
    unsigned char temp_s1;
    int temp_s0;
    temp_s0 = *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 168);
    if (temp_s0 != 0) {
        temp_s1 = FUN_00455620((void *)temp_s0) & 0xFF;
        FUN_00455610((int *)temp_s0, !temp_s1);
        FUN_00455610((int *)temp_s0, temp_s1);
    }
}

int Gap__Gui__igGuiSystem__vfunc_24(A_457100 *arg0, float fparg0, float fparg1) {
    struct { int a; int b; int c; } s;
    B_457100 *temp_v1;

    temp_v1 = arg0->fc;
    if (temp_v1->fa0 == 0) {
        return 0;
    }
    temp_v1->f14 = fparg0;
    temp_v1->f18 = fparg1;
    s.a = 2;
    s.b = 0;
    s.c = DAT_0058c3d8[0];
    FUN_004578c0((S_4578c0 *)arg0->fc, (S_4578c0 *)&s);
    return arg0->fc->fb0 != 0;
}

int Gap__Gui__igGuiSystem__vfunc_32(int *self, int x, int y) {
    struct P_457170 p;
    float *f = (float *)self[3];
    f[3] = (float)x;
    f[4] = (float)y;
    p.a = 2;
    p.b = 0;
    p.c = DAT_0058c3d0[0];
    FUN_004578c0((S_4578c0 *)((void *)self[3]), (S_4578c0 *)&p);
    return 0;
}

int Gap__Gui__igGuiSystem__vfunc_34(igGuiSystem *arg0) {
    int buf[3];

    *(char *)((char *)(arg0->_model) + 180) = 1;
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058c420[0];
    FUN_004578c0((S_4578c0 *)arg0->_model, (S_4578c0 *)buf);
    return 1;
}

int Gap__Gui__igGuiSystem__vfunc_25(struct P_457220 *arg0, int arg1, char arg2) {
    int sp[3];
    struct O_457220 *o;

    o = arg0->o;
    if (o->fa0 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        return 0;
    }
    o->f1c = arg2;
    sp[0] = 2;
    sp[1] = 0;
    sp[2] = DAT_0058c3e0[0];
    FUN_004578c0((S_4578c0 *)arg0->o, (S_4578c0 *)&sp[0]);
    return arg0->o->fac != 0;
}

bool Gap__Gui__igGuiSystem__vfunc_27(igGuiSystem *system, int device, int key, int pressed) {
    bool handled;

    if (!((GuiModelView *)system->_model)->enabled) {
        return false;
    }
    handled = false;
    switch (key) {
    case 4:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 2);
        }
        handled = true;
        break;
    case 6:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 3);
        }
        handled = true;
        break;
    case 7:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 0);
        }
        handled = true;
        break;
    case 5:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 1);
        }
        handled = true;
        break;
    case 8:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 5);
        }
        handled = true;
        break;
    case 9:
        if (pressed) {
            FUN_00456eb0((Ctl *)system, 4);
        }
        handled = true;
        break;
    case 13:
        if (pressed) {
            FUN_004570a0(system);
        }
        handled = true;
        break;
    }
    return handled;
}

int Gap__Gui__igGuiSystem__vfunc_26(void) {
    return 0;
}

void FUN_004573c0(int arg0, int arg1, int arg2) {
    FUN_004573f0((AttrEntryOwner *)arg0, arg1, 32, (igObject *)arg2);
}

void FUN_004573d0(int arg0, int arg1, int arg2) {
    FUN_004573f0((AttrEntryOwner *)arg0, 0, arg1, (igObject *)arg2);
}

static inline void assign(igObject **slot, igObject *value) {
    igObject *old;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    old = *slot;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = value;
}

void FUN_004573f0(AttrEntryOwner *owner, int a, int b, igObject *value) {
    igSmartPointer<Entry> entry((Entry *)FUN_0044dc20(igObject_GetAllocator(owner)));
    entry->a = a;
    entry->b = b;
    assign(&entry->value, value);
    ObjectList_AppendRetained(owner->entries, entry.get());
}

void FUN_004574f0(T_4574f0 *arg0, int arg1) {
    E_4574f0 *temp_a0;
    int var_s1;
    LST *temp_s0;

    for (var_s1 = arg0->f8->f8 - 1; var_s1 >= 0; var_s1 -= 1) {
        temp_s0 = arg0->f8;
        temp_a0 = temp_s0->f16[var_s1];
        if (temp_a0->f12 == arg1) {
            if (temp_a0->f8 == 0) {
                if (temp_a0 != 0) {
                    temp_a0->f4 = temp_a0->f4 - 1;
                    if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(temp_a0);
                    }
                }
                List_RemoveWordAt(temp_s0, var_s1);
                temp_s0->f16[temp_s0->f8] = 0;
            } else {
                temp_a0->f12 = 0x20;
            }
        }
    }
}

int Gap__Gui__igHotKeyEventReceiver__vfunc_23(B_4575d0 *arg0, int arg1, int arg2) {
    int i;
    int n;
    if (arg2 == 0) {
        return 0;
    }
    arg0 = *(B_4575d0 **)((char *)arg0 + 8);
    n = arg0->cnt;
    for (i = 0; i < n; i++) {
        E_4575d0 *e = arg0->arr[i];
        if (e->f08 == arg1) {
            e->f10->vX();
            return 1;
        }
    }
    return 0;
}

int Gap__Gui__igHotKeyEventReceiver__vfunc_27(B_457650 *arg0, int arg1, int arg2, int arg3) {
    int i;
    int n;
    if (arg3 == 0) {
        return 0;
    }
    arg0 = *(B_457650 **)((char *)arg0 + 8);
    n = arg0->cnt;
    for (i = 0; i < n; i++) {
        E_457650 *e = arg0->arr[i];
        if (e->f0c == arg2) {
            e->f10->vX();
            return 1;
        }
    }
    return 0;
}

void FUN_004576d0(igContext *context, ContextHandler *handler) {
    int s[4];
    igTDataList<ContextHandler *> *list;
    int index;
    index = (list = (igTDataList<ContextHandler *> *)context->_pExtList)->find(0);
    if (index < 0) {
        int n = list->_count;
        if (n < list->_capacity) {
            list->_count = list->count() + 1;
        } else {
            List_Resize(list, n + 1, 4);
        }
        list->_data[n] = handler;
    } else if (list->count() != 0 && index >= 0 && index < list->count()) {
        list->_data[index] = handler;
    }
    s[0] = 0;
    s[1] = 0;
    s[2] = 0;
    handler->vX(s);
}

void FUN_004577f0(igModel *arg0, OV *arg1) {
    Flags f;
    igObjectList *l;
    int i;
    int n;
    f.b = 0;
    f.c = 0;
    f.a = 1;
    arg1->vX(&f);
    K_4577f0 key(arg1);
    l = (igObjectList *)arg0->_views;
    i = Finder_4577f0::Find(l, key);
    if (i >= 0) {
        n = *(int *)&l->_count;
        if (n != 0 && i >= 0 && i < n) {
            ((void **)l->_data)[i] = 0;
        }
    }
}

void FUN_004578c0(S_4578c0 *arg0, S_4578c0 *arg1) {
    int var_s0;
    VC_4578c0 *o;
    for (var_s0 = 0; var_s0 < arg0->f8->n; var_s0++) {
        o = arg0->f8->arr[var_s0];
        if (o != 0 && o != arg1->f4) {
            o->vX(arg1);
        }
    }
}

void Gap__Gui__igModel__vfunc_10(struct O_457950 *arg0) {
    int n;
    int i;
    int p;

    n = arg0->l->n;
    for (i = 0; i < n; i++) {
        p = arg0->l->arr[i];
        if (p != 0) {
            FUN_00457e90((S0_457e90 *)p, 0);
        }
    }
}

void Gap__Gui__igRadioGroup__vfunc_13(void *arg0) {
    Gap__Core__igObject__vfunc_11();
    *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 12) = (int)(arg0);
    FUN_00457e90((S0_457e90 *)(*(int *)((char *)(arg0) + 12)), *(int *)((char *)(arg0) + 8));
}

void FUN_00457a10(struct RadioGroupView *s) {
    struct RadioButtonListView *b;
    int idx;
    int c;
    idx = s->a->sel;
    if (s->cur != idx) {
        b = s->b;
        if (idx < b->n) {
            if (idx >= 0) {
                FUN_00457c40((S_457c40 *)b->arr[idx], 1);
            }
            c = s->cur;
            if (c >= 0) {
                FUN_00457c40((S_457c40 *)s->b->arr[c], 0);
            }
            s->cur = s->a->sel;
        }
    }
}

void FUN_00457ab0(igRadioGroup *arg0, igRadioGroupSelectedObserver *arg1, int arg2) {
    int idx;
    int flag;
    igObjectList *l;
    igRadioGroupModel *s;
    int *pf;
    l = (igObjectList *)arg0->_observerList;
    flag = ((igOnOffModel *)arg1->_model)->_value;
    K_457ab0 key(arg1);
    idx = Finder_457ab0::Find(l, key);
    if (flag != 0) {
        s = (igRadioGroupModel *)arg0->_model;
        pf = &s->_selected;
        if (idx != s->_selected) {
            *pf = idx;
            Msg m;
            m.a = 2;
            m.b = 0;
            m.c = DAT_0058c280[0];
            FUN_004578c0((S_4578c0 *)((void *)arg0->_model), (S_4578c0 *)&m);
        }
    } else {
        s = (igRadioGroupModel *)arg0->_model;
        pf = &s->_selected;
        if (idx == s->_selected) {
            if (arg0->_alwaysSelected != 0) {
                FUN_00457c40((S_457c40 *)arg1, 1);
                return;
            }
            *pf = -1;
            Msg m2;
            m2.a = 2;
            m2.b = 0;
            m2.c = DAT_0058c280[0];
            FUN_004578c0((S_4578c0 *)((void *)arg0->_model), (S_4578c0 *)&m2);
        }
    }
}

void Gap__Gui__igRadioGroupSelectedObserver__vfunc_24(void *arg0, void *arg1) {
    int temp_a1;

    temp_a1 = *(int *)((char *)arg1 + 8);
    if (temp_a1 == *(int *)0x58C280) {
        FUN_00457a10((RadioGroupView *)*(int *)((char *)arg0 + 12));
    }
}

void Gap__Gui__igOnOffValueObserver__vfunc_24(void *arg0, void *arg1) {
    if ((*(int *)((char *)arg1 + 8) == *(int *)0x58C290) || (*(int *)((char *)arg1 + 0) == 0)) {
        FUN_00457ab0((igRadioGroup *)(*(int *)((char *)arg0 + 12)), (igRadioGroupSelectedObserver *)arg0, (int)arg0);
    }
}

void FUN_00457c40(struct S_457c40 *arg0, unsigned char arg1) {
    int sp[3];
    unsigned char temp_a2;
    struct T_457c40 *temp_v1;
    unsigned char *pb;

    temp_v1 = arg0->t;
    if (temp_v1 != 0) {
        temp_a2 = temp_v1->b;
        pb = &temp_v1->b;
        if (temp_a2 != arg1) {
            *pb = arg1;
            sp[0] = 2;
            sp[1] = 0;
            sp[2] = DAT_0058c290[0];
            FUN_004578c0((S_4578c0 *)arg0->t, (S_4578c0 *)sp);
        }
    }
}

void FUN_00457ca0(O_457ca0 *arg0, R_457ca0 *arg1) {
    R_457ca0 *old;
    R_457ca0 *a;

    old = arg0->r;
    if (old != arg1) {
        if (old != 0) {
            arg0->v96();
        }
        if (arg1 != 0) {
            arg1->refs = arg1->refs + 1;
        }
        a = arg0->r;
        if (a != 0) {
            a->refs = a->refs - 1;
            if ((a->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
        arg0->r = arg1;
        if (arg0->r != 0) {
            arg0->v92();
        }
    }
}

void Gap__Gui__igClearRenderer__vfunc_23(O_457d60 *arg0) {
    E_457d60 *temp_a0;
    E_457d60 *temp_s0;
    temp_a0 = arg0->f8;
    temp_a0->v732(0);
    arg0->f12 = 3;
    temp_s0 = arg0->f8;
    if (temp_s0->v228(temp_s0->v200()) > 0) {
        arg0->f12 = arg0->f12 | 4;
    }
}

void Gap__Gui__igClearRenderer__vfunc_26(igClearRendererView *self)
{
    self->_visualContext->vfunc_174(self->_buffersToClear);
}

void Gap__Gui__igTextElement__vfunc_23(igTextElement *self) {
}

void Gap__Gui__igTextElement__vfunc_24(O_457e10 *arg0) {
    int n;
    int i;
    struct Q_457e10 *q = (struct Q_457e10 *)arg0->m->obj;
    if (q != 0) {
        n = q->count;
        for (i = 0; i < n; i++) {
            arg0->m->obj->vX(i, arg0->buf);
        }
    }
}

void FUN_00457e90(S0_457e90 *arg0, int arg1) {
    int temp_a0;
    int temp_a0_2;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        FUN_004577f0((igModel *)temp_a0, (OV *)arg0);
    }
    arg0->f8 = arg1;
    temp_a0_2 = arg0->f8;
    if (temp_a0_2 != 0) {
        FUN_004576d0((igContext *)temp_a0_2, (ContextHandler *)arg0);
    }
}

/* Teardown slot (the slot the other classes' teardown bodies also chain from to the igObject
 * base): if the mode still has its _model, FUN_004577f0 detaches the mode from it (it nulls the
 * mode's entry in the model's list at +8), then the base igObject teardown runs. */
void Gap__Bec__beCameraMode__vfunc_08(beCameraMode *self) {
    int model;

    model = self->_model;
    if (model != 0) {
        FUN_004577f0((igModel *)model, (OV *)self);
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(self);
}

int Gap__Gui__igTextElement__vfunc_22(void) {
    return (int)g_igTextElement_metaObject[0];
}

int Gap__Gui__igClearRenderer__vfunc_22(void) {
    return DAT_0058c1f0[0];
}

void Gap__Gui__igClearRenderer__vfunc_25(void) {

}

void Gap__Gui__igClearRenderer__vfunc_24(void) {

}

int Gap__Gui__igOnOffValueObserver__vfunc_22(void) {
    return DAT_0058c220[0];
}

void Gap__Gui__igOnOffValueObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igOnOffModel_GetMetaObject());
}

int Gap__Gui__igRadioGroupSelectedObserver__vfunc_22(void) {
    return DAT_0058c230[0];
}

void Gap__Gui__igRadioGroupSelectedObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igRadioGroupModel_GetMetaObject());
}

int Gap__Gui__igRadioGroup__vfunc_22(void) {
    return DAT_0058c240[0];
}

int Gap__Gui__igModel__vfunc_22(void) {
    return DAT_0058c298[0];
}

int Gap__Gui__igHotKeyEventReceiver__vfunc_22(void) {
    return DAT_0058c2a8[0];
}

int Gap__Gui__igGuiSystem__vfunc_22(void) {
    return DAT_0058c2e0[0];
}

int Gap__Gui__igGuiSystemRenderer__vfunc_22(void) {
    return DAT_0058c338[0];
}

int Gap__Gui__igActiveComponentsObserver__vfunc_22(void) {
    return DAT_0058c360[0];
}

void Gap__Gui__igActiveComponentsObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}

int Gap__Gui__igMousePosObserver__vfunc_22(void) {
    return DAT_0058c380[0];
}

void Gap__Gui__igMousePosObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}

int Gap__Gui__igWindowSizeObserver__vfunc_22(void) {
    return DAT_0058c3c0[0];
}

void Gap__Gui__igWindowSizeObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}

int Gap__Gui__igGuiSystemModel__vfunc_22(void) {
    return DAT_0058c3c8[0];
}

int Gap__Gui__igGuiComponentNode__vfunc_22(void) {
    return DAT_0058c428[0];
}

int Gap__Gui__igGuiComponentController__vfunc_22(void) {
    return (int)g_igGuiComponentController_metaObject[0];
}

int Gap__Gui__igGuiComponent__vfunc_22(void) {
    return DAT_0058c4a8[0];
}

int Gap__Gui__igFieldChangeView__vfunc_22(void) {
    return DAT_0058c550[0];
}

int Gap__Gui__igFieldChangeView__vfunc_23(void) {
    return 1;
}

int Gap__Gui__igEventDispatcher__vfunc_22(void) {
    return DAT_0058c578[0];
}

int Gap__Gui__igDefaultAspect__vfunc_22(void) {
    return (int)g_igDefaultAspect_metaObject[0];
}

void Gap__Gui__igDefaultAspect__vfunc_23(igDefaultAspect *self, int model) {
    igObject_IsKindOf(model, igGuiComponentModel_GetMetaObject());
}

int Gap__Gui__igOnOffColorChanger__vfunc_22(void) {
    return DAT_0058c5e8[0];
}

int Gap__Gui__igBasicColorChanger__vfunc_22(void) {
    return DAT_0058c5f0[0];
}

int Gap__Gui__igColorChanger__vfunc_22(void) {
    return DAT_0058c608[0];
}

int Gap__Gui__igBitmapFont__vfunc_22(void) {
    return DAT_0058c620[0];
}

int Gap__Gui__igCharMetricsMetaField__vfunc_22(void) {
    return DAT_0058c648[0];
}

int Gap__Gui__igCharMetricsMetaField__vfunc_23(void) {
    return (int)DAT_0058c650[0];
}

int Gap__Gui__igCharMetricsList__vfunc_22(void) {
    return (int)g_igCharMetricsList_metaObject[0];
}

int Gap__Gui__igBoxComponent__vfunc_22(void) {
    return DAT_0058c610[0];
}

int Gap__Gui__igDefaultAspectElement__vfunc_22(void) {
    return DAT_0058c5b0[0];
}

int Gap__Gui__igDefaultAspectElementList__vfunc_22(void) {
    return DAT_0058c5a0[0];
}

int Gap__Gui__igEventReceiverOrderedList__vfunc_22(void) {
    return DAT_0058c568[0];
}

int Gap__Gui__igFieldChangeViewList__vfunc_22(void) {
    return (int)g_igFieldChangeViewList_metaObject[0];
}

int Gap__Gui__igFieldSynchronizer__vfunc_22(void) {
    return DAT_0058c538[0];
}

int Gap__Gui__igGuiComponentList__vfunc_22(void) {
    return DAT_0058c4a0[0];
}

int Gap__Gui__igMouseCursor__vfunc_22(void) {
    return DAT_0058c320[0];
}

int Gap__Gui__igHotKeyBinding__vfunc_22(void) {
    return DAT_0058c2c0[0];
}

int Gap__Gui__igHotKeyBindingList__vfunc_22(void) {
    return DAT_0058c2b8[0];
}

int Gap__Gui__igOnOffModel__vfunc_22(void) {
    return DAT_0058c288[0];
}

int Gap__Gui__igRadioGroupModel__vfunc_22(void) {
    return DAT_0058c278[0];
}

int Gap__Gui__igOnOffValueObserverList__vfunc_22(void) {
    return DAT_0058c218[0];
}

int Gap__Gui__igRendererOrderedList__vfunc_22(void) {
    return DAT_0058c200[0];
}

int Gap__Gui__igGuiComponentModel__vfunc_22(void) {
    return (int)g_igGuiComponentModel_metaObject[0];
}

int FUN_00458310(void) {
    return (int)g_igGeometryElement_metaObject[0];
}

int Gap__Gui__igViewList__vfunc_22(void) {
    return (int)g_igViewList_metaObject[0];
}

int Gap__Gui__igNonRefCountedViewList__vfunc_22(void) {
    return DAT_0058c1b0[0];
}

int Gap__Gui__igNonRefCountedViewList__vfunc_24(void) {
    return DAT_0058c1c0[0];
}

/* Element size in bytes of the list's items: 0x28 (one igCharMetrics record). The same class's
 * TrimCapacity (vfunc_18) re-sizes the buffer with List_Reserve(self, count, 0x28), and the
 * sibling lists igDependencyList (8) and igPsx2AudioSourceList (0x24) return their item size from
 * this same slot 23. */

int Gap__Gui__igCharMetricsList__vfunc_23(void) {
    return CHAR_METRICS_ITEM_SIZE;
}

int Gap__Gui__igDefaultAspectElementList__vfunc_24(void) {
    return DAT_0058c5b0[0];
}

int Gap__Gui__igFieldChangeViewList__vfunc_24(void) {
    return (int)g_igFieldChangeView_metaObject[0];
}

int Gap__Gui__igHotKeyBindingList__vfunc_24(void) {
    return DAT_0058c2c0[0];
}

int Gap__Gui__igOnOffValueObserverList__vfunc_24(void) {
    return DAT_0058c220[0];
}

int Gap__Gui__igGuiComponentList__vfunc_24(void) {
    return DAT_0058c4a8[0];
}

int Gap__Gui__igViewList__vfunc_24(void) {
    return (int)g_igView_metaObject[0];
}

void Gap__Gui__igCharMetricsList__vfunc_18(igCharMetricsList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve(self, count, 0x28);
    }
}

