#ifndef DW4_GUI_LIBRARY_H
#define DW4_GUI_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igTDataList.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/game/beFontImage.h"
#include "dw4/gui/igAction.h"
#include "dw4/gui/igBasicColorChanger.h"
#include "dw4/gui/igBitmapFont.h"
#include "dw4/gui/igBoxComponent.h"
#include "dw4/gui/igDefaultAspect.h"
#include "dw4/gui/igEventDispatcher.h"
#include "dw4/gui/igEventReceiver.h"
#include "dw4/gui/igGuiComponent.h"
#include "dw4/gui/igGuiComponentList.h"
#include "dw4/gui/igGuiSystem.h"
#include "dw4/gui/igHotKeyEventReceiver.h"
#include "dw4/gui/igModel.h"
#include "dw4/gui/igMouseCursor.h"
#include "dw4/gui/igOnOffColorChanger.h"
#include "dw4/gui/igOnOffModel.h"
#include "dw4/gui/igRadioGroup.h"
#include "dw4/gui/igRenderer.h"
#include "dw4/gui/igRendererOrderedList.h"
#include "dw4/gui/igTextElement.h"
#include "dw4/gui/igView.h"
#define CHAR_METRICS_ITEM_SIZE 0x28

#include "dw4/support/ClassRegistration.h"
#include "dw4/maths/igAABox.h"
#include "dw4/maths/igRay.h"
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/maths/igMatrix44fMetaField.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igUnsignedIntMetaField.h"
#include "dw4/core/igUnsignedShortMetaField.h"
#include "dw4/maths/igVec2fMetaField.h"
#include "dw4/maths/igVec3fMetaField.h"
#include "dw4/maths/igVec4fMetaField.h"
#include "dw4/core/igMetaField.h"
extern "C" void FUN_0019e440(void);
#include "dw4/scenegraph/igNode.h"
#include "dw4/gfx/igVisualContext.h"
class igMemoryPoolView;

#include "dw4/core/igMetaObject.h"
#include "dw4/support/list-services.h"
#include "dw4/core/igDataLists.h"
extern "C" int DAT_0058c618[4];
extern "C" unsigned char g_GuiLibrary_registered;
extern "C" void GuiLibrary_MarkRegistered(void);
#include "dw4/core/igMemoryPoolContext.h"
struct Obj { int *vt; char pad[28]; };
#include "dw4/core/igObject.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igObjectList.h"
extern "C" igMetaObject *g_igTextElement_metaObject;
extern "C" igMetaObject *igTextElement_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igTextElement_GetMetaObject(void);
union U { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" int g_igTextElement_vtable[4];
extern "C" int igTextElement_GetVTable(void);
extern "C" int DAT_00541e90[4];
extern "C" void *FUN_0044be30(igGeometryElement *arg0, short arg1);
extern "C" void **FUN_0044bf10(void **arg0, long long arg1);
extern "C" igMetaObject *igGeometryElement_GetPublishedMetaObject(void);
extern "C" CallbackArray *igTextElement_Register(void);
extern "C" void igTextElement_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igGeometryElement_metaObject;
extern "C" igMetaObject *igGeometryElement_GetPublishedMetaObject(void);
extern "C" void igTextElement_InitFields(void);
extern "C" igMetaObject *g_igGuiComponentModel_metaObject;
extern "C" igMetaObject *igGuiComponentModel_GetPublishedMetaObject(void);
extern "C" void **FUN_0044c1c0(void **arg0, int arg1);
extern "C" igMetaObject *g_igGuiComponentAspect_metaObject;
extern "C" igMetaObject *igGuiComponentAspect_GetPublishedMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U_44c2f0 { int vt; char b[16]; };
extern "C" igMetaObject *g_igRendererOrderedList_metaObject;
extern "C" igMetaObject *igRendererOrderedList_GetMetaObject(void);
struct Obj_44c570 { int *vt; int w[7]; };
extern "C" int g_igRendererOrderedList_vtable[4];
extern "C" int igRendererOrderedList_GetVTable(void);
#include "dw4/core/igDependencyOrderedList.h"
extern "C" int DAT_00541dd0[4];
extern "C" int **FUN_0044c5e0(int **arg0, long long arg1);
extern "C" CallbackArray *igRendererOrderedList_Register(void);
extern "C" void igRendererOrderedList_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igOnOffValueObserverList_metaObject;
extern "C" igMetaObject *igOnOffValueObserverList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igOnOffValueObserverList_GetMetaObject(void);
typedef struct { int *vt; int pad[7]; } Obj_44c920;
extern "C" int g_igOnOffValueObserverList_vtable[4];
extern "C" int igOnOffValueObserverList_GetVTable(void);
extern "C" void igOnOffValueObserverList_EnsureRegistered(void);
extern "C" CallbackArray *igOnOffValueObserverList_Register(void);
extern "C" void igOnOffValueObserverList_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igOnOffValueObserver_metaObject;
extern "C" igMetaObject *igOnOffValueObserver_GetMetaObject(void);
struct Obj_44ca40 { int *vt; char pad[12]; };
extern "C" int g_igOnOffValueObserver_vtable[4];
extern "C" int igOnOffValueObserver_GetVTable(void);
extern "C" void igOnOffValueObserver_EnsureRegistered(void);
extern "C" CallbackArray *igOnOffValueObserver_Register(void);
extern "C" void igOnOffValueObserver_GetMetaObjectFunction(void);
extern "C" void igOnOffValueObserver_InitFields(void);
extern "C" igMetaObject *g_igRadioGroupSelectedObserver_metaObject;
extern "C" igMetaObject *igRadioGroupSelectedObserver_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igRadioGroupSelectedObserver_GetMetaObject(void);
struct O { int *vt; char post[12]; };
extern "C" int g_igRadioGroupSelectedObserver_vtable[4];
extern "C" int igRadioGroupSelectedObserver_GetVTable(void);
extern "C" void igRadioGroupSelectedObserver_EnsureRegistered(void);
extern "C" CallbackArray *igRadioGroupSelectedObserver_Register(void);
extern "C" void igRadioGroupSelectedObserver_GetMetaObjectFunction(void);
extern "C" void igRadioGroupSelectedObserver_InitFields(void);
extern "C" igMetaObject *g_igRadioGroup_metaObject;
extern "C" igMetaObject *igRadioGroup_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igRadioGroup_GetMetaObject(void);
extern "C" int g_igRadioGroup_vtable[4];
union U_44ce90 { int vt; char b[32]; };
extern "C" int igRadioGroup_GetVTable(void);
extern "C" CallbackArray *igRadioGroup_Register(void);
extern "C" void igRadioGroup_GetMetaObjectFunction(void);
extern "C" void igRadioGroup_InitFields(void);
extern "C" igMetaObject *g_igRadioGroupModel_metaObject;
extern "C" igMetaObject *igRadioGroupModel_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igRadioGroupModel_GetMetaObject(void);
extern "C" int g_igRadioGroupModel_vtable[4];
union U_44d210 { int vt; char b[16]; };
extern "C" int igRadioGroupModel_GetVTable(void);
extern "C" void igRadioGroupModel_RunStaticInit(void);
extern "C" CallbackArray *igRadioGroupModel_Register(void);
extern "C" void thunk_igRadioGroupModel_GetMetaObject(void);
extern "C" void igRadioGroupModel_InitFields(void);
extern "C" igMetaObject *g_igOnOffModel_metaObject;
extern "C" int g_igOnOffModel_vtable[4];
union U_44d430 { int vt; char b[48]; };
extern "C" int igOnOffModel_GetVTable(void);
extern "C" void igOnOffModel_RunStaticInit(void);
extern "C" igMetaObject *igGuiComponentModel_GetPublishedMetaObject(void);
extern "C" CallbackArray *igOnOffModel_Register(void);
extern "C" void thunk_igOnOffModel_GetMetaObject(void);
extern "C" void igOnOffModel_InitFields(void);
struct Obj_44d670 { int *vt; char pad[4]; char *m; char pad2[4]; };
extern "C" igMetaObject *g_igHotKeyEventReceiver_metaObject;
extern "C" igMetaObject *igHotKeyEventReceiver_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igHotKeyEventReceiver_GetMetaObject(void);
extern "C" int g_igHotKeyEventReceiver_vtable[4];
union U_44d8e0 { int vt; char b[16]; };
extern "C" int igHotKeyEventReceiver_GetVTable(void);
extern "C" CallbackArray *igHotKeyEventReceiver_Register(void);
extern "C" void thunk_igHotKeyEventReceiver_GetMetaObject(void);
extern "C" void igHotKeyEventReceiver_InitFields(void);
extern "C" igMetaObject *g_igHotKeyBindingList_metaObject;
extern "C" igMetaObject *igHotKeyBindingList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igHotKeyBindingList_GetMetaObject(void);
extern "C" int g_igHotKeyBindingList_vtable[4];
extern "C" int igHotKeyBindingList_GetVTable(void);
extern "C" void igHotKeyBindingList_RunStaticInit(void);
extern "C" CallbackArray *igHotKeyBindingList_Register(void);
extern "C" void thunk_igHotKeyBindingList_GetMetaObject(void);
extern "C" int igHotKeyBinding_Create(int arg0);
extern "C" igMetaObject *g_igHotKeyBinding_metaObject;
extern "C" igMetaObject *igHotKeyBinding_GetMetaObject(void);
extern "C" int g_igHotKeyBinding_vtable[4];
struct R { int vt; unsigned int rc; };
struct Obj_44dcb0 { int *vt; char pad[12]; struct R *p; char pad2[12]; };
extern "C" int igHotKeyBinding_GetVTable(void);
extern "C" void igHotKeyBinding_RunStaticInit(void);
extern "C" CallbackArray *igHotKeyBinding_Register(void);
extern "C" void thunk_igHotKeyBinding_GetMetaObject(void);
extern "C" igMetaEnum* FUN_00145eb0(void);
extern "C" igMetaEnum* FUN_00146850(void);
extern "C" void igHotKeyBinding_InitFields(void);
extern "C" igMetaObject *g_igGuiSystem_metaObject;
extern "C" igMetaObject *igGuiSystem_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGuiSystem_GetMetaObject(void);
struct Obj_44df70 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_igGuiSystem_vtable[4];
extern "C" int igGuiSystem_GetVTable(void);
extern "C" void **FUN_0044e060(void **arg0, short arg1);
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" void **FUN_0044e0e0(struct Ref **self, short flag);
extern "C" void **FUN_0044e160(void **arg0, long long arg1);
extern "C" CallbackArray *igGuiSystem_Register(void);
extern "C" void thunk_igGuiSystem_GetMetaObject(void);
#include "dw4/scenegraph/igTransform.h"
#include "dw4/scenegraph/igAttrSet.h"
extern "C" void igGuiSystem_InitFields(void);
extern "C" igMetaObject *g_igMouseCursor_metaObject;
extern "C" igMetaObject *igMouseCursor_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igMouseCursor_GetMetaObject(void);
struct Obj_44e4d0 { int *vt; char pad[4]; char *m; char pad2[20]; };
extern "C" int g_igMouseCursor_vtable[4];
extern "C" int igMouseCursor_GetVTable(void);
extern "C" CallbackArray *igMouseCursor_Register(void);
extern "C" void thunk_igMouseCursor_GetMetaObject(void);
extern "C" void igMouseCursor_InitFields(void);
extern "C" igMetaObject *g_igGuiSystemRenderer_metaObject;
extern "C" igMetaObject *igGuiSystemRenderer_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGuiSystemRenderer_GetMetaObject(void);
struct Obj_44e750 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" void** FUN_001d9870(void**, short);
extern "C" int g_igGuiSystemRenderer_vtable[4];
extern "C" int igGuiSystemRenderer_GetVTable(void);
extern "C" void igGuiSystemRenderer_RunStaticInit(void);
extern "C" CallbackArray *igGuiSystemRenderer_Register(void);
extern "C" void thunk_igGuiSystemRenderer_GetMetaObject(void);
extern "C" igMetaObject* FUN_001a38e0(void);
extern "C" void igGuiSystemRenderer_InitFields(void);
extern "C" int igActiveComponentsObserver_Create(int arg0);
extern "C" igMetaObject *g_igActiveComponentsObserver_metaObject;
extern "C" igMetaObject *igActiveComponentsObserver_GetMetaObject(void);
extern "C" int g_igActiveComponentsObserver_vtable[4];
union U_44ea20 { int vt; char b[32]; };
extern "C" int igActiveComponentsObserver_GetVTable(void);
extern "C" void igActiveComponentsObserver_RunStaticInit(void);
extern "C" CallbackArray *igActiveComponentsObserver_Register(void);
extern "C" void thunk_igActiveComponentsObserver_GetMetaObject(void);
extern "C" void igActiveComponentsObserver_InitFields(void);
extern "C" int igMousePosObserver_Create(int arg0);
extern "C" igMetaObject *g_igMousePosObserver_metaObject;
extern "C" igMetaObject *igMousePosObserver_GetMetaObject(void);
#include "dw4/maths/igMatrix44f.h"
#include "dw4/core/igResult.h"
extern "C" int g_igMousePosObserver_vtable[4];
extern "C" int D_00541090[4];
extern "C" int igMousePosObserver_GetVTable(void);
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" ObjectRefWord *FUN_0044ee80(ObjectRefWord *self,int delete_storage);
extern "C" void igMousePosObserver_RunStaticInit(void);
extern "C" CallbackArray *igMousePosObserver_Register(void);
extern "C" void thunk_igMousePosObserver_GetMetaObject(void);
#include "dw4/scenegraph/igGraphPath.h"
extern "C" void igMousePosObserver_InitFields(void);
extern "C" int igWindowSizeObserver_Create(int arg0);
extern "C" igMetaObject *g_igWindowSizeObserver_metaObject;
extern "C" igMetaObject *igWindowSizeObserver_GetMetaObject(void);
extern "C" int g_igWindowSizeObserver_vtable[4];
extern "C" int igWindowSizeObserver_GetVTable(void);
extern "C" void igWindowSizeObserver_RunStaticInit(void);
extern "C" CallbackArray *igWindowSizeObserver_Register(void);
extern "C" void thunk_igWindowSizeObserver_GetMetaObject(void);
extern "C" igMetaObject *g_igGuiSystemModel_metaObject;
extern "C" igMetaObject *igGuiSystemModel_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGuiSystemModel_GetMetaObject(void);
extern "C" int g_igGuiSystemModel_vtable[4];
extern "C" int igGuiSystemModel_GetVTable(void);
extern "C" void igGuiSystemModel_RunStaticInit(void);
extern "C" CallbackArray *igGuiSystemModel_Register(void);
extern "C" void thunk_igGuiSystemModel_GetMetaObject(void);
extern "C" void igGuiSystemModel_InitFields(void);
extern "C" igMetaObject *g_igGuiComponentNode_metaObject;
extern "C" igMetaObject *igGuiComponentNode_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGuiComponentNode_GetMetaObject(void);
struct Obj_44f5e0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_igGuiComponentNode_vtable[4];
extern "C" int igGuiComponentNode_GetVTable(void);
extern "C" void igGuiComponentNode_RunStaticInit(void);
#include "dw4/scenegraph/igGroup.h"
extern "C" CallbackArray *igGuiComponentNode_Register(void);
extern "C" void thunk_igGuiComponentNode_GetMetaObject(void);
extern "C" void igGuiComponentNode_InitFields(void);
extern "C" igMetaObject *igGuiComponentModel_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGuiComponentModel_GetMetaObject(void);
extern "C" int g_igGuiComponentModel_vtable[4];
union U_44f830 { int vt; char b[48]; };
extern "C" int igGuiComponentModel_GetVTable(void);
extern "C" void igGuiComponentModel_RunStaticInit(void);
extern "C" CallbackArray *igGuiComponentModel_Register(void);
extern "C" void thunk_igGuiComponentModel_GetMetaObject(void);
extern "C" void igGuiComponentModel_InitFields(void);
extern "C" igMetaObject *g_igGuiComponentController_metaObject;
extern "C" igMetaObject *igGuiComponentController_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGuiComponentController_GetMetaObject(void);
struct Obj_44fae0 { int *vt; char pad[12]; };
extern "C" int g_igGuiComponentController_vtable[4];
extern "C" int igGuiComponentController_GetVTable(void);
extern "C" void igGuiComponentController_EnsureRegistered(void);
extern "C" CallbackArray *igGuiComponentController_Register(void);
extern "C" void igGuiComponentController_GetMetaObjectFunction(void);
extern "C" igMetaObject *igGuiComponentAspect_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGuiComponentAspect_GetMetaObject(void);
extern "C" void igGuiComponentAspect_EnsureRegistered(void);
extern "C" CallbackArray *igGuiComponentAspect_Register(void);
extern "C" void igGuiComponentAspect_GetMetaObjectFunction(void);
struct GuiAspectMetaField { char pad[56]; int f56; char b60; };
extern "C" void igGuiComponentAspect_InitFields(void);
extern "C" igMetaObject *g_igGuiComponentList_metaObject;
extern "C" igMetaObject *igGuiComponentList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGuiComponentList_GetMetaObject(void);
extern "C" int g_igGuiComponentList_vtable[4];
extern "C" int igGuiComponentList_GetVTable(void);
extern "C" CallbackArray *igGuiComponentList_Register(void);
extern "C" void igGuiComponentList_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igGuiComponent_metaObject;
extern "C" igMetaObject *igGuiComponent_GetMetaObject(void);
struct Obj_44ffe0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_igGuiComponent_vtable[4];
extern "C" int igGuiComponent_GetVTable(void);
struct S1 { char pad4[4]; int f4; };
struct O_450090 { int *vt; char pad4[8]; S1 *m12; S1 *m16; S1 *m20; char pad24[4]; S1 *m28; };
extern "C" O_450090 *FUN_00450090(O_450090 *arg0, short arg1);
typedef struct S_temp_a0_4501f0 { char pad4[4]; int f4; } S_temp_a0_4501f0;
extern "C" void **FUN_004501f0(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00450270(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_004502f0(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00450370(ObjectRefWord *self,int delete_storage);
extern "C" CallbackArray *igGuiComponent_Register(void);
extern "C" void igGuiComponent_GetMetaObjectFunction(void);
extern "C" void igGuiComponent_InitFields(void);
extern "C" igMetaObject *igGeometryElement_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGeometryElement_GetMetaObject(void);
extern "C" void igGeometryElement_EnsureRegistered(void);
extern "C" CallbackArray *igGeometryElement_Register(void);
extern "C" void igGeometryElement_GetMetaObjectFunction(void);
#include "dw4/attrs/igAttrList.h"
#include "dw4/scenegraph/igGeometry.h"
extern "C" void igGeometryElement_InitFields(void);
extern "C" igMetaObject *g_igFont_metaObject;
extern "C" igMetaObject *igFont_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igFont_GetMetaObject(void);
extern "C" void igFont_EnsureRegistered(void);
#include "dw4/core/igNamedObject.h"
extern "C" CallbackArray *igFont_Register(void);
extern "C" void igFont_GetMetaObjectFunction(void);
extern "C" void igFont_InitFields(void);
extern "C" igMetaObject *g_igFieldSynchronizer_metaObject;
extern "C" igMetaObject *igFieldSynchronizer_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igFieldSynchronizer_GetMetaObject(void);
extern "C" int g_igFieldSynchronizer_vtable[4];
struct Obj_450aa0 { int *vt; char pad[4]; struct R *p; char pad2[4]; };
extern "C" int igFieldSynchronizer_GetVTable(void);
extern "C" void igFieldSynchronizer_EnsureRegistered(void);
extern "C" CallbackArray *igFieldSynchronizer_Register(void);
extern "C" void igFieldSynchronizer_GetMetaObjectFunction(void);
extern "C" void igFieldSynchronizer_InitFields(void);
extern "C" igMetaObject *g_igFieldChangeViewList_metaObject;
extern "C" igMetaObject *igFieldChangeViewList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igFieldChangeViewList_GetMetaObject(void);
extern "C" int g_igFieldChangeViewList_vtable[4];
extern "C" int igFieldChangeViewList_GetVTable(void);
extern "C" void igFieldChangeViewList_EnsureRegistered(void);
extern "C" CallbackArray *igFieldChangeViewList_Register(void);
extern "C" void igFieldChangeViewList_GetMetaObjectFunction(void);
extern "C" int igFieldChangeView_Create(int arg0);
extern "C" igMetaObject *g_igFieldChangeView_metaObject;
extern "C" igMetaObject *igFieldChangeView_GetMetaObject(void);
struct Obj_450e70 { int *vt; char pad[12]; char *m; char pad2[12]; };
extern "C" int g_igFieldChangeView_vtable[4];
extern "C" int igFieldChangeView_GetVTable(void);
extern "C" void igFieldChangeView_EnsureRegistered(void);
extern "C" CallbackArray *igFieldChangeView_Register(void);
extern "C" void igFieldChangeView_GetMetaObjectFunction(void);
extern "C" void igFieldChangeView_InitFields(void);
extern "C" igMetaObject *g_igEventReceiverOrderedList_metaObject;
extern "C" igMetaObject *igEventReceiverOrderedList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igEventReceiverOrderedList_GetMetaObject(void);
extern "C" int g_igEventReceiverOrderedList_vtable[4];
union U_4510f0 { int vt; char b[32]; };
extern "C" int igEventReceiverOrderedList_GetVTable(void);
extern "C" int DAT_00541970[4];
extern "C" int **FUN_00451160(int **arg0, long long arg1);
extern "C" void igEventReceiverOrderedList_EnsureRegistered(void);
extern "C" CallbackArray *igEventReceiverOrderedList_Register(void);
extern "C" void igEventReceiverOrderedList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igEventReceiver_GetMetaObject(void);
struct Obj_4512e0 { int *vt; char pad[4]; };
extern "C" int g_igEventReceiver_vtable[4];
extern "C" int igEventReceiver_GetVTable(void);
extern "C" void igEventReceiver_EnsureRegistered(void);
extern "C" void igEventReceiver_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igEventDispatcher_metaObject;
extern "C" igMetaObject *igEventDispatcher_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igEventDispatcher_GetMetaObject(void);
extern "C" int DAT_00524da0[4];
extern "C" int g_igEventDispatcher_vtable[4];
union U_451450 { int vt; int w[5]; char b[20]; };
extern "C" int igEventDispatcher_GetVTable(void);
#include "dw4/windowinput/igInterfaceManager.h"
extern "C" CallbackArray *igEventDispatcher_Register(void);
extern "C" void igEventDispatcher_GetMetaObjectFunction(void);
extern "C" void igEventDispatcher_InitFields(void);
extern "C" igMetaObject *g_igDefaultAspect_metaObject;
extern "C" igMetaObject *igDefaultAspect_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igDefaultAspect_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int g_igDefaultAspect_vtable[4];
struct Obj_451780 {
    int *vt; int w0[9]; T *ref; int w1[1]; 
    inline void release() {
        T **self = &ref;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};
extern "C" int igDefaultAspect_GetVTable(void);
extern "C" igMetaObject *igGuiComponentAspect_GetPublishedMetaObject(void);
extern "C" CallbackArray *igDefaultAspect_Register(void);
extern "C" void igDefaultAspect_GetMetaObjectFunction(void);
extern "C" void igDefaultAspect_InitFields(void);
extern "C" igMetaObject *g_igDefaultAspectElementList_metaObject;
extern "C" igMetaObject *igDefaultAspectElementList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igDefaultAspectElementList_GetMetaObject(void);
extern "C" int g_igDefaultAspectElementList_vtable[4];
extern "C" int igDefaultAspectElementList_GetVTable(void);
extern "C" void igDefaultAspectElementList_EnsureRegistered(void);
extern "C" CallbackArray *igDefaultAspectElementList_Register(void);
extern "C" void igDefaultAspectElementList_GetMetaObjectFunction(void);
extern "C" igMetaEnum *FUN_00451ac0(void);
extern "C" igMetaObject *g_igDefaultAspectElement_metaObject;
extern "C" igMetaObject *igDefaultAspectElement_GetMetaObject(void);
#include "dw4/core/StringPool.h"
union U_451b70 { int vt; int w[5]; void *p[5]; char b[20]; };
struct Rc { int vt; int rc; };
extern "C" int g_igDefaultAspectElement_vtable[4];
extern "C" int igDefaultAspectElement_GetVTable(void);
extern "C" void igDefaultAspectElement_EnsureRegistered(void);
extern "C" CallbackArray *igDefaultAspectElement_Register(void);
extern "C" void igDefaultAspectElement_GetMetaObjectFunction(void);
extern "C" void igDefaultAspectElement_InitFields(void);
extern "C" igMetaObject *g_igOnOffColorChanger_metaObject;
extern "C" igMetaObject *igOnOffColorChanger_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igOnOffColorChanger_GetMetaObject(void);
struct Obj_451ee0 { int *vt; char pad[92]; };
extern "C" int g_igOnOffColorChanger_vtable[4];
extern "C" int igOnOffColorChanger_GetVTable(void);
extern "C" igMetaObject *igBasicColorChanger_GetPublishedMetaObject(void);
extern "C" CallbackArray *igOnOffColorChanger_Register(void);
extern "C" void thunk_igOnOffColorChanger_GetMetaObject(void);
extern "C" igMetaObject *g_igBasicColorChanger_metaObject;
extern "C" igMetaObject *igBasicColorChanger_GetPublishedMetaObject(void);
extern "C" igMetaObject *igBasicColorChanger_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igBasicColorChanger_GetMetaObject(void);
struct Obj_452060 { int *vt; char pad[92]; };
extern "C" int g_igBasicColorChanger_vtable[4];
extern "C" int igBasicColorChanger_GetVTable(void);
extern "C" igMetaObject *igColorChanger_GetPublishedMetaObject(void);
extern "C" CallbackArray *igBasicColorChanger_Register(void);
extern "C" void thunk_igBasicColorChanger_GetMetaObject(void);
extern "C" igMetaObject *g_igColorChanger_metaObject;
extern "C" igMetaObject *igColorChanger_GetPublishedMetaObject(void);
extern "C" void igBasicColorChanger_InitFields(void);
extern "C" igMetaObject *igColorChanger_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igColorChanger_GetMetaObject(void);
struct Obj_452270 { int *vt; char pad[4]; };
extern "C" int g_igColorChanger_vtable[4];
extern "C" int igColorChanger_GetVTable(void);
extern "C" void igColorChanger_RunStaticInit(void);
extern "C" CallbackArray *igColorChanger_Register(void);
extern "C" void thunk_igColorChanger_GetMetaObject(void);
extern "C" igMetaObject *g_igBoxComponent_metaObject;
extern "C" igMetaObject *igBoxComponent_GetMetaObject(void);
struct F { int *vt; int w[11]; };
extern "C" int g_igBoxComponent_vtable[4];
extern "C" int igBoxComponent_GetVTable(void);
extern "C" igMetaObject *igGuiComponent_GetPublishedMetaObject(void);
extern "C" CallbackArray *igBoxComponent_Register(void);
extern "C" void thunk_igBoxComponent_GetMetaObject(void);
extern "C" igMetaObject *igGuiComponent_GetPublishedMetaObject(void);
extern "C" igMetaObject *igBitmapFont_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igBitmapFont_GetMetaObject(void);
struct Obj_452590 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
#include "dw4/gui/igFont.h"
extern "C" int igBitmapFont_GetVTable(void);
extern "C" igMetaObject *igFont_GetPublishedMetaObject(void);
extern "C" void thunk_igBitmapFont_GetMetaObject(void);
extern "C" igMetaObject *igFont_GetPublishedMetaObject(void);
extern "C" void igBitmapFont_InitFields(void);
extern "C" igMetaObject *g_igCharMetricsList_metaObject;
extern "C" igMetaObject *igCharMetricsList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igCharMetricsList_GetMetaObject(void);
typedef struct { int *vt; int pad[7]; } Obj_452830;
extern "C" int g_igCharMetricsList_vtable[4];
extern "C" int igCharMetricsList_GetVTable(void);
extern "C" void igCharMetricsList_RunStaticInit(void);
extern "C" CallbackArray *igCharMetricsList_Register(void);
extern "C" void thunk_igCharMetricsList_GetMetaObject(void);
extern "C" int g_igCharMetricsList_externalStorage;
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" void FUN_00452900(void);
extern "C" igMetaObject *g_igCharMetricsMetaField_metaObject;
extern "C" igMetaObject *igCharMetricsMetaField_GetMetaObject(void);
#include "dw4/core/igCompoundMetaField.h"
extern "C" int g_igCharMetricsMetaField_vtable[4];
union U_452a10 { int vt; char b[64]; };
extern "C" int igCharMetricsMetaField_GetVTable(void);
extern "C" void igCharMetricsMetaField_RunStaticInit(void);
extern "C" CallbackArray *igCharMetricsMetaField_Register(void);
extern "C" void thunk_igCharMetricsMetaField_GetMetaObject(void);
extern "C" void FUN_00452b70(void);
extern "C" int FUN_00452c40(void);
extern "C" int Gap__Gui__igCharMetricsMetaField__vfunc_25(void);
extern "C" void igCharMetricsMetaField_InitDefaults(igCharMetricsMetaField *self);
extern "C" void FUN_00452ca0(int arg0);
extern "C" igMetaObject *igAction_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAction_GetMetaObject(void);
extern "C" void igAction_RunStaticInit(void);
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
struct K { short key; char pad[38]; };
extern "C" int FUN_00453830(beFontImage *arg0, int arg1);
#include "dw4/attrs/igTextureStateAttr.h"
#include "dw4/attrs/igBlendStateAttr.h"
class Layer : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setEnabled(int);
  };
class FillLayer : public Layer {};
class OutlineLayer : public Layer {};
struct FontImage { char pad[20]; int layers; int state; char pad3[4]; int base; };
extern "C" void igBitmapFont_resetFields(FontImage *self, int enable);
extern "C" void FUN_00453980(int arg0, int arg1);
#include "dw4/maths/igMathConstants.h"
extern "C" int *Gap__Gui__igColorChanger__vfunc_23(void);
extern "C" int Gap__Gui__igBasicColorChanger__vfunc_23(int arg0, void *arg1);
struct OnOffColorState { unsigned char pad[12]; bool enabled; bool on; unsigned char pad2; bool hilite; unsigned char pad3[20]; bool current; };
extern "C" int Gap__Gui__igOnOffColorChanger__vfunc_23(int arg0, OnOffColorState *s);
typedef struct B { char p[12]; float x, y, z; } B;
typedef struct A { char p[8]; B *b; char q[12]; float dx, dy; } A;
extern "C" igVec3f FUN_00453b90(A *a);
extern "C" void igDefaultAspect_UpdateMinimumSize(igDefaultAspect *self);
extern "C" void Gap__Gui__igDefaultAspect__vfunc_25(igDefaultAspect *arg0);
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
typedef struct R_453f70 { int w0; int refs; } R_453f70;
typedef struct T_453f70 { char pad[16]; float f16; float f20; float f24; } T_453f70;
typedef struct L { char pad[8]; int count; } L;
typedef struct A_453f70 { char pad[8]; T_453f70 *f8; int f12; char pad16[24]; L *f40; } A_453f70;
extern "C" void Gap__Gui__igDefaultAspect__vfunc_26(A_453f70 *arg0);
struct S_454050 { char pad[8]; int f8; };
extern "C" void Gap__Gui__igDefaultAspect__vfunc_27(void *arg0, struct S_454050 *arg1);
class V92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual float *vX(int); };
class V96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); char pad[20]; float f24; float f28; float f32; float f36; };
struct E { char pad[8]; V96 *f8; V92 *f12; };
struct L_4540d0 { char pad[8]; int count; char pad1[4]; E **data; };
struct S_4540d0 { char pad[8]; int f8; char pad1[28]; L_4540d0 *f40; };
extern "C" void FUN_004540d0(S_4540d0 *arg0);
extern "C" void igDefaultAspectElement_PlaceGeometry(igDefaultAspectElement *self, const igVec3f *size);
class igGeometryElementSizeView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void setSize(const igVec3f *size); };
extern "C" void FUN_00454180(void *arg0);
class C22 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int *); };
class C30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int *, int *); };
class C28 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void vX(int *, int, int); };
extern "C" void FUN_004541f0(int *arg0, int *arg1);
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
extern "C" void igEventDispatcher_MouseMotion(Owner *o, int unused, Cur *c);
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();  virtual int vX(int, int); };
struct L_4544d0 { char pad8[8]; int cnt; char pad[4]; VC **arr; };
struct M { char pad8[8]; L_4544d0 *list; };
struct S_4544d0 { char pad12[12]; M *m; };
extern "C" void igEventDispatcher_MouseButtonDown(S_4544d0 *arg0, int arg1, int arg2, int arg3);
class VC_454570 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned char vX(int, int); };
struct L_454570 { char pad[8]; int count; char pad2[4]; VC_454570 **data; };
struct M_454570 { char pad[8]; L_454570 *list; };
struct S_454570 { char pad[12]; M_454570 *m; };
extern "C" void igEventDispatcher_MouseButtonUp(S_454570 *arg0, int a1, int a2, int arg3);
class V132 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int, int); };
struct L_454610 { char p0[8]; int count; char p1[4]; V132 **items; };
struct M_454610 { char p0[8]; L_454610 *list; };
struct O_454610 { char p0[12]; M_454610 *m; };
extern "C" void igEventDispatcher_WindowMove(O_454610 *arg0, int arg1, int arg2, int arg3);
class X { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int); };
struct L2 { char pad8[8]; int f8; char pad12[4]; X **f16; };
struct L1 { char pad8[8]; L2 *f8; };
struct T_4546c0 { char pad12[12]; L1 *f12; };
extern "C" void igEventDispatcher_WindowResize(T_4546c0 *arg0, int arg1, int arg2, int arg3);
class V136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(); };
class V104 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vY(); };
struct L_454770 { char p0[8]; int count; char p1[4]; V136 **items; };
struct M_454770 { char p0[8]; L_454770 *list; };
struct O_454770 { char p0[12]; M_454770 *m; };
extern "C" void igEventDispatcher_WindowClose(O_454770 *arg0, V104 *arg1);
#include "dw4/core/igMemory.h"
struct K_454820 { int p; K_454820(int x) { p = x; } ~K_454820() { } static void operator delete(void *q) { Memory_FreeBufferAliasB(q); } };
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
extern "C" void igEventDispatcher_ControllerJoystickMotion(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f0, float f1);
struct K_454930 { int p; K_454930(int x) { p = x; } ~K_454930() { } static void operator delete(void *q) { Memory_FreeBufferAliasB(q); } };
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
extern "C" void igEventDispatcher_ControllerButtonDown(igEventDispatcher *arg0, int arg1, int arg2, int arg3);
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
extern "C" void igEventDispatcher_ControllerButtonUp(EventDispatcherView *self, int, DispatchKey *key, int arg3);
struct K_454b30 { int p; K_454b30(int x) { p = x; } ~K_454b30() { } static void operator delete(void *q) { Memory_FreeBufferAliasB(q); } };
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
extern "C" void igEventDispatcher_ControllerButtonPressure(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f);
struct K_454c30 { int p; K_454c30(int x) { p = x; } ~K_454c30() { } static void operator delete(void *q) { Memory_FreeBufferAliasB(q); } };
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
extern "C" void igEventDispatcher_ControllerPointOfView(igEventDispatcher *arg0, int arg1, int arg2, int arg3, float f);
extern "C" void igEventDispatcher_ControllerSlider(EventDispatcherView *self, int, DispatchKey *key, int arg3, float f);
struct K_454e30 { int p; K_454e30(int x) { p = x; } ~K_454e30() { } static void operator delete(void *q) { Memory_FreeBufferAliasB(q); } };
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
extern "C" void igEventDispatcher_ControllerConnection(igEventDispatcher *arg0, int arg1, int arg2);
extern "C" void igEventDispatcher_ControllerDisconnection(EventDispatcherView *self, int, DispatchKey *key);
class E_455010 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual unsigned char vX(int, int); };
struct L2_455010 { int p0; int p1; int n; int p3; E_455010 **arr; };
struct L1_455010 { int p0; int p1; L2_455010 *l2; };
struct O_455010 { int vt; int p1; int p2; L1_455010 *f12; };
extern "C" void igEventDispatcher_KeyDown(O_455010 *arg0, int arg1, int arg2);
class A_4550b0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int, int); };
extern "C" void igEventDispatcher_KeyUp(igEventDispatcher *self, int arg1, int arg2);
extern "C" void igFieldChangeView_OnModelChange(igFieldChangeView *self, void *arg1);
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
                igObject_Destroy((igObject *)object);
        }
    }
};
struct A_4551f0 { char pad8[8]; int f8; };
extern "C" void FUN_004552e0(int *arg0, int *arg1);
class VC_455370 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(long long); };
class VC100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
extern "C" void igGuiComponent_resetFields(igGuiComponent *self, int flags);
typedef struct C { char pad12[12]; int f0c; } C;
typedef struct B_455470 { char pad32[32]; int f20; } B_455470;
typedef struct A_455470 { char pad12[12]; int f0c; B_455470 *f10; C *f14; char pad24[8]; unsigned char f20; } A_455470;
extern "C" void FUN_00455470(A_455470 *arg0);
extern "C" void igGuiComponent_userDestruct(igGuiComponent *self);
struct O_455510 {
    char p[32]; int v;
    static O_455510 *cast(O_455510 *o) {
        if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(g_igGuiComponentNode_metaObject) != 0) return o;
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
extern "C" void igDefaultAspect_OnModelChange(igDefaultAspect *arg0, int *arg1);
extern "C" void igGuiComponentController_IsCompatible(igGuiComponentController *self, int model);
class DW4VC_104_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int, int); };
class DW4VC_108_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int); };
class DW4VC_112_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int, int); };
class DW4VC_116_2_4556e0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int, int); };
class DW4VC_120_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(int, int); };
class DW4VC_124_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(int, int); };
class DW4VC_128_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int); };
class DW4VC_132_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int, int); };
extern "C" void igGuiComponentController_OnModelChange(igGuiComponentController *arg0, void *arg1);
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
struct S_4559a0 { char pad[28]; unsigned char b; };
extern "C" void FUN_004559a0(struct S_4559a0 *arg0, unsigned char arg1);
struct Vec3 { int x; int y; int z; };
struct Node : igObject { int fc_pad; igObject *child; };
extern "C" void FUN_001900d0(void**, int);
extern "C" void igGuiComponentNode_resetFields(Node *self, int flags);
extern "C" int g_activeMousePosObserver;
extern "C" int FUN_00455ad0(int arg0, int arg1, int arg2);
extern "C" void igGuiSystemModel_resetFields(int arg0, int arg1);
struct A_455b90 { char pad[8]; int x; int y; };
struct T_455b90 { char pad[12]; float w; float h; };
extern "C" int FUN_00191860(void *, float, float, float, float, float, float);
extern "C" void igWindowSizeObserver_OnModelChange(igWindowSizeObserver *self, int *arg1);
struct ObserverIntListView { int w0; int w4; int cnt; int cap; int *data; };
struct ObserverEventView : igObject { int w8; int a; ObserverIntListView *list; };
struct ObserverModelView { char pad[40]; igObject *ref; int flags; int fn; };
struct MousePosObserverView { char pad[16]; ObserverModelView *m; int f20; };
#include "dw4/scenegraph/igProbe.h"
extern "C" void igMousePosObserver_resetFields(MousePosObserverView *self, int flags);
struct Obj_455f50 : public igObject { };
struct Y { char pad[8]; int f8; char pad2[8]; float f20; };
struct Z { char pad[24]; float f24; unsigned char f28; char pad2[3]; Obj_455f50 *f32; };
extern "C" void FUN_00455f50(Z *arg0, Y *arg1);
#include "dw4/scenegraph/igIntersectTraversal.h"
/* vtable-call shim for the intersect traversal (slot 23 = vtable offset 100); not a data layout */
struct IntersectTraversalCalls { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(int); };
extern "C" void FUN_00456050(igMousePosObserver *a, igGuiSystemModel *b);
typedef struct N { int w0, w4, w8, wC; int f10; int f14; struct N *f18; } N;
extern "C" int FUN_00456540(int arg0, N *arg1, N *arg2, unsigned char arg3);
extern "C" void *FUN_004565c0(int arg0, void *arg1);
#include "dw4/scenegraph/igCommonTraversal.h"
class Obj_456610 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int); };
extern "C" void igGuiSystemRenderer_InitializeDrawing(int *arg0);
extern "C" void igGuiSystemRenderer_ReleaseDrawing(void);
class C29 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void vX(); };
class C23 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void vX(int); };
class C28_456670 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual igObject *vX(); };
extern "C" void igGuiSystemRenderer_Traverse(int *arg0);
class CA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void vX(int, int); };
class CB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int); };
extern "C" void igGuiSystemRenderer_Render(igGuiSystemRenderer *self);
struct R_456780 : public igObject { int w8; int wc; };
struct X_456780 { char p[12]; R_456780 *f12; R_456780 *f16; };
struct A_456780 { char p[8]; X_456780 *f8; int f12; int f16; R_456780 *f20; char q[4]; int f28; };
extern "C" void igGuiSystem_resetFields(A_456780 *self, int flags);
class T_4569c0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX();
  char pad[20]; float f24; float f28; float f32; float f36; };
struct M_4569c0 { int p0; int p1; T_4569c0 *t; };
struct O_4569c0 { char pad[24]; M_4569c0 *m; char pad2[4]; char f32; };
typedef struct Rc_456a60 { int vt; int rc; int p8; } Rc_456a60;
typedef struct Q { char pad8[8]; int f8; } Q;
typedef struct P_456a60 { char pad28[28]; Q *f28; } P_456a60;
typedef struct A_456a60 { char pad12[12]; int f12; char pad16[8]; Rc_456a60 *f24; P_456a60 *f28; bool f32; } A_456a60;
typedef struct R_456a60 { char pad8[8]; Q *f8; } R_456a60;
typedef struct V3 { int a; int b; int c; int pad[4]; } V3;
#include "dw4/gui/igGuiSystemModel.h"
#include "dw4/attrs/igDisplayListAttr.h"
#include "dw4/attrs/igGeometryAttr.h"
#include "dw4/attrs/igTextureBindAttr.h"
#include "dw4/windowinput/igControllerManager.h"
#include "dw4/gui/igFieldSynchronizer.h"
class Obj_456b80 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void vX(void *); };
struct P_456b80 { char pad[12]; float x; float y; };
extern "C" void FUN_00456b80(int *arg0, float *arg1);
extern "C" void FUN_00456c20(igGuiSystemModel *arg0, igGuiComponent *arg1);
struct T_456cc0 { int word0; int references; int f8; char pad12[16]; int f28; };
struct LL { char pad8[8]; int f8; };
class VC_456cc0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void v140(int, int); };
struct Obj_456cc0 : VC_456cc0 { char pad4[24]; LL *f28; };
struct P_456cc0 { char pad164[164]; T_456cc0 *f164; };
struct W { char pad12[12]; P_456cc0 *f12; char pad16[4]; Obj_456cc0 *f20; };
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
extern "C" bool igGuiSystem_OnKeyEvent(Ob *arg0, int arg1, int arg2);
extern "C" void FUN_004570a0(void *arg0);
typedef struct B_457100 { char pad20[20]; float f14; float f18; char pad28[132]; unsigned char fa0; char pada1[15]; int fb0; } B_457100;
typedef struct A_457100 { char pad12[12]; B_457100 *fc; } A_457100;
extern "C" int igGuiSystem_MouseMotionEvent(A_457100 *arg0, float fparg0, float fparg1);
struct P_457170 { int a, b, c; };
extern "C" int igGuiSystem_WindowResizeEvent(int *self, int x, int y);
extern "C" int igGuiSystem_WindowCloseEvent(igGuiSystem *arg0);
struct O_457220 { char pad[28]; char f1c; char pad2[131]; unsigned char fa0; char pad3[11]; int fac; };
struct P_457220 { char pad[12]; struct O_457220 *o; };
extern "C" int igGuiSystem_MouseButtonEvent(struct P_457220 *arg0, int arg1, char arg2);
struct GuiModelView {
    char pad0[160];
    unsigned char enabled;
};
extern "C" bool igGuiSystem_ControllerButtonEvent(igGuiSystem *system, int device, int key, int pressed);
extern "C" int igGuiSystem_ControllerMotionEvent(void);
struct Entry : igObject { int a; int b; igObject *value; };
typedef struct E_4574f0 { char pad4[4]; int f4; int f8; int f12; } E_4574f0;
typedef struct LST { char pad8[8]; int f8; char pad12[4]; E_4574f0 **f16; } LST;
class VC_4575d0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(); };
struct E_4575d0 { char pad8[8]; int f08; char pad12[4]; VC_4575d0 *f10; };
struct B_4575d0 { char pad8[8]; int cnt; char pad2[4]; E_4575d0 **arr; };
extern "C" int igHotKeyEventReceiver_OnKeyEvent(igHotKeyEventReceiver *self, int arg1, int arg2);
class VC_457650 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(); };
struct E_457650 { char pad12[12]; int f0c; VC_457650 *f10; };
struct B_457650 { char pad8[8]; int cnt; char pad2[4]; E_457650 **arr; };
extern "C" int igHotKeyEventReceiver_ControllerButtonEvent(igHotKeyEventReceiver *self, int arg1, int arg2, int arg3);
extern "C" void igRadioGroup_resetFields(igRadioGroup *self, int flags);
struct RadioButtonListView { char p[8]; int n; char q[4]; int *arr; };
struct RadioSelectionView { char p[12]; int sel; };
struct RadioGroupView { char p[8]; struct RadioSelectionView *a; char p2[4]; struct RadioButtonListView *b; int f20; int cur; };
extern "C" void FUN_00457a10(struct RadioGroupView *s);
struct K_457ab0 { void *p; K_457ab0(void *x) { p = x; } ~K_457ab0() { } static void operator delete(void *q) { Memory_FreeBufferAliasB(q); } };
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
extern "C" void igRadioGroupSelectedObserver_OnModelChange(igRadioGroupSelectedObserver *self, void *arg1);
extern "C" void igOnOffValueObserver_OnModelChange(igOnOffValueObserver *self, void *arg1);
struct T_457c40 { char pad[36]; unsigned char b; };
struct S_457c40 { char pad[8]; struct T_457c40 *t; };
extern "C" void FUN_00457c40(struct S_457c40 *arg0, unsigned char arg1);
extern "C" void Gap__Gui__igTextElement__vfunc_23(igTextElement *self);
class V168 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int vX(int, char *); };
struct Q_457e10 { char p0[12]; int count; };
struct M_457e10 { char p0[12]; V168 *obj; };
struct O_457e10 { char p0[24]; char buf[1]; char p1[23]; M_457e10 *m; };
extern "C" void Gap__Gui__igTextElement__vfunc_24(O_457e10 *arg0);
extern "C" int igTextElement_GetMeta(void);
extern "C" igMetaObject *igOnOffValueObserver_GetMeta(void);
extern "C" void igOnOffValueObserver_IsCompatible(void *arg0, int arg1);
extern "C" igMetaObject *igRadioGroupSelectedObserver_GetMeta(void);
extern "C" void igRadioGroupSelectedObserver_IsCompatible(void *arg0, int arg1);
extern "C" igMetaObject *igRadioGroup_GetMeta(void);
extern "C" igMetaObject *igHotKeyEventReceiver_GetMeta(void);
extern "C" igMetaObject *igGuiSystem_GetMeta(void);
extern "C" igMetaObject *igGuiSystemRenderer_GetMeta(void);
extern "C" igMetaObject *igActiveComponentsObserver_GetMeta(void);
extern "C" void igActiveComponentsObserver_IsCompatible(void *arg0, int arg1);
extern "C" igMetaObject *igMousePosObserver_GetMeta(void);
extern "C" void igMousePosObserver_IsCompatible(void *arg0, int arg1);
extern "C" igMetaObject *igWindowSizeObserver_GetMeta(void);
extern "C" void igWindowSizeObserver_IsCompatible(void *arg0, int arg1);
extern "C" igMetaObject *igGuiSystemModel_GetMeta(void);
extern "C" igMetaObject *igGuiComponentNode_GetMeta(void);
extern "C" int igGuiComponentController_GetMeta(void);
extern "C" igMetaObject *igGuiComponent_GetMeta(void);
extern "C" igMetaObject *igFieldChangeView_GetMeta(void);
extern "C" int igFieldChangeView_IsCompatible(void);
extern "C" igMetaObject *igEventDispatcher_GetMeta(void);
extern "C" int igDefaultAspect_GetMeta(void);
extern "C" void igDefaultAspect_IsCompatible(igDefaultAspect *self, int model);
extern "C" igMetaObject *igOnOffColorChanger_GetMeta(void);
extern "C" igMetaObject *igBasicColorChanger_GetMeta(void);
extern "C" igMetaObject *igColorChanger_GetMeta(void);
extern "C" igMetaObject *igBitmapFont_GetMeta(void);
extern "C" igMetaObject *igCharMetricsMetaField_GetMeta(void);
extern "C" int igCharMetricsMetaField_GetDescriptor(void);
extern "C" int igCharMetricsList_GetMeta(void);
extern "C" igMetaObject *igBoxComponent_GetMeta(void);
extern "C" igMetaObject *igDefaultAspectElement_GetMeta(void);
extern "C" igMetaObject *igDefaultAspectElementList_GetMeta(void);
extern "C" igMetaObject *igEventReceiverOrderedList_GetMeta(void);
extern "C" int igFieldChangeViewList_GetMeta(void);
extern "C" igMetaObject *igFieldSynchronizer_GetMeta(void);
extern "C" igMetaObject *igGuiComponentList_GetMeta(void);
extern "C" igMetaObject *igMouseCursor_GetMeta(void);
extern "C" igMetaObject *igHotKeyBinding_GetMeta(void);
extern "C" igMetaObject *igHotKeyBindingList_GetMeta(void);
extern "C" igMetaObject *igOnOffModel_GetMeta(void);
extern "C" igMetaObject *igRadioGroupModel_GetMeta(void);
extern "C" igMetaObject *igOnOffValueObserverList_GetMeta(void);
extern "C" igMetaObject *igRendererOrderedList_GetMeta(void);
extern "C" int igGuiComponentModel_GetMeta(void);
extern "C" int FUN_00458310(void);
extern "C" int igCharMetricsList_GetElementSize(void);
extern "C" igMetaObject *igDefaultAspectElementList_GetElementMeta(void);
extern "C" int igFieldChangeViewList_GetElementMeta(void);
extern "C" igMetaObject *igHotKeyBindingList_GetElementMeta(void);
extern "C" igMetaObject *igOnOffValueObserverList_GetElementMeta(void);
extern "C" igMetaObject *igGuiComponentList_GetElementMeta(void);
extern "C" void igCharMetricsList_TrimCapacity(igCharMetricsList *self);
extern "C" void FUN_00453990(struct FontLayers_453990 *self, int index, struct FontLayerItem_453990 *item);
extern "C" void igMousePosObserver_OnModelChange(igMousePosObserver *self, struct GuiMessage_455d80 *msg);
extern "C" void igActiveComponentsObserver_OnModelChange(igActiveComponentsObserver *self, struct GuiMessage_455d80 *msg);

#endif
