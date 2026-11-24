#ifndef DW4_VIEWER_REGISTRATION_H
#define DW4_VIEWER_REGISTRATION_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/viewer/igActorManager.h"
#include "dw4/viewer/igBoundingBoxRenderer.h"
#include "dw4/viewer/igCameraMode.h"
#include "dw4/viewer/igFlyMode.h"
#include "dw4/viewer/igLogoRenderer.h"
#include "dw4/viewer/igNormalsRenderer.h"
#include "dw4/viewer/igPickMode.h"
#include "dw4/viewer/igRotateMode.h"
#include "dw4/viewer/igStatisticsItem.h"
#include "dw4/viewer/igViewManager.h"
#include "dw4/viewer/igViewMode.h"
#include "dw4/viewer/igViewModel.h"
#include "dw4/viewer/igViewerAction.h"
#include "dw4/viewer/igViewerDataPumpManager.h"
#include "dw4/viewer/igViewerGuiFactory.h"
#include "dw4/viewer/igViewerLoadingFileMessage.h"
#include "dw4/viewer/igViewerParameters.h"
#include "dw4/viewer/igViewerRenderer.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"
#include "dw4/viewer/igViewerSceneInfoManagerController.h"
#include "dw4/viewer/igViewerStatisticsManager.h"


#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igLongMetaField.h"
#include "dw4/maths/igMatrix44fMetaField.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igStructMetaField.h"
#include "dw4/maths/igVec2fMetaField.h"
#include "dw4/maths/igVec3fMetaField.h"
class igMemoryPoolView;
#include "dw4/support/ClassRegistration.h"
#include "dw4/attrs/igGeometryAttrList.h"
#include "dw4/gfx/igVisualContext.h"
#include "dw4/maths/igRay.h"
extern "C" void igViewerModeChangeMessage_EnsureRegistered(void);
extern "C" void igViewerRenderer_EnsureRegistered(void);
extern "C" void igViewMode_EnsureRegistered(void);
extern "C" void igViewManager_EnsureRegistered(void);
#include "dw4/gui/igBasicColorChanger.h"
#include "dw4/gui/igBitmapFont.h"
#include "dw4/gui/igBoxComponent.h"
#include "dw4/gui/igDefaultAspect.h"
#include "dw4/gui/igGuiComponentList.h"
#include "dw4/gui/igGuiComponent.h"
#include "dw4/gui/igGuiSystem.h"
#include "dw4/core/igMetaFieldList.h"
#include "dw4/core/igPointerList.h"
#include "dw4/core/igMetaObjectList.h"
#include "dw4/gui/igMouseCursor.h"
#include "dw4/core/igObjectList.h"
#include "dw4/gui/igOnOffColorChanger.h"
#include "dw4/gui/igRadioGroup.h"
#include "dw4/core/igStringObj.h"
#include "dw4/gui/igTextElement.h"

#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igObjectSystem.h"
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" void ViewerLibrary_MarkRegistered(void);
#include "dw4/gui/igView.h"
#include "dw4/attrs/igTextureList.h"
#include "dw4/insight/igInfoManager.h"
extern "C" void** FUN_0044c1c0(void**, int);
extern "C" int text_name_3[4];
extern "C" int text_Viewer_scene_manager[4];
extern "C" int g_igViewerSceneInfoManager_vtable[4];
struct MetaObjectFlags { char p[36]; unsigned f; };
struct R { int vt; unsigned int rc; };
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
union U { int vt; char b[208]; };
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" igMetaEnum *FUN_004592e0(void);
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
extern "C" CallbackArray *igViewerSceneInfoManager_Register(void);
extern "C" void igViewerSceneInfoManager_GetMetaObjectFunction(void);
extern "C" void FUN_00459ee0(void);
typedef struct { int *vt; int w[2]; char *s; } Obj_45a450;
#include "dw4/core/StringPool.h"
extern "C" int g_igViewerModeChangeMessage_vtable[4];
#include "dw4/insight/igMessage.h"
extern "C" igMetaObject *igViewerModeChangeMessage_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igViewerModeChangeMessage_GetMetaObject(void);
extern "C" int igViewerModeChangeMessage_GetVTable(void);
extern "C" CallbackArray *igViewerModeChangeMessage_Register(void);
extern "C" void igViewerModeChangeMessage_GetMetaObjectFunction(void);
extern "C" void igViewerModeChangeMessage_InitFields(void);
struct Obj_45a680 { int *vt; char pad[8]; char *m; };
extern "C" int g_igViewerLoadingFileMessage_vtable[4];
extern "C" int DAT_0051eef0[4];
extern "C" igMetaObject *igViewerLoadingFileMessage_GetMetaObject(void);
extern "C" int igViewerLoadingFileMessage_GetVTable(void);
extern "C" void igViewerLoadingFileMessage_EnsureRegistered(void);
extern "C" CallbackArray *igViewerLoadingFileMessage_Register(void);
extern "C" void igViewerLoadingFileMessage_GetMetaObjectFunction(void);
extern "C" void igViewerLoadingFileMessage_InitFields(void);
struct Obj_45a8c0 { int *vt; char pad[28]; };
union U_45aaf0 { int vt; int *pv; char b[96]; };
#include "dw4/attrs/igLightingStateAttr.h"
extern "C" ObjectRefWord* FUN_00136370(ObjectRefWord*, int);
#include "dw4/scenegraph/igTransform.h"
#include "dw4/scenegraph/igAttrSet.h"
extern "C" igSmartPointer<igObject> *igSmartPointer_igAlphaStateAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" void** FUN_001d9870(void**, short);
extern "C" void** FUN_00229460(void**, short);
extern "C" void** FUN_00239280(void**, short);
extern "C" int g_igViewerRenderer_vtable[4];
#include "dw4/gui/igRenderer.h"
extern "C" igMetaObject *igViewerRenderer_GetOrCreateMetaObject(void);
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
extern "C" CallbackArray *igViewerRenderer_Register(void);
extern "C" void igViewerRenderer_GetMetaObjectFunction(void);
extern "C" void igViewerRenderer_InitFields(void);
#include "dw4/maths/igMatrix44f.h"
#include "dw4/gui/igModel.h"
struct Fld { char p0[52]; char f52; char p53[3]; int f56; };
#include "dw4/scenegraph/igGroup.h"
#include "dw4/scenegraph/igGraphPath.h"
struct Obj_45b970 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" void *igViewerDataPumpManager_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U_45bec0 { int vt; int w[8]; void *p[8]; char b[32]; };
#include "dw4/core/igNamedObject.h"
extern "C" int g_igViewerDataPumpManager_vtable[4];
extern "C" int igViewerDataPumpManager_GetVTable(void);
extern "C" void igViewerDataPumpManager_EnsureRegistered(void);
extern "C" void igViewerDataPumpManager_InitFields_0045c040(void);
extern "C" CallbackArray *igViewerDataPumpManager_Register(void);
extern "C" void igViewerDataPumpManager_GetMetaObjectFunction(void);
extern "C" int text_Viewer_data_pump_manager[4];
extern "C" void FUN_0045c040(void);
extern "C" void *igPickMode_GetMetaObject(void);
struct Obj_45c200 { int *vt; int w[44]; };
extern "C" ObjectRefWord* FUN_0044ee80(ObjectRefWord*, int);
extern "C" int g_igPickMode_vtable[4];
extern "C" int igPickMode_GetVTable(void);
extern "C" void igPickMode_EnsureRegistered(void);
extern "C" CallbackArray *igPickMode_Register(void);
extern "C" void igPickMode_GetMetaObjectFunction(void);
extern "C" void igPickMode_InitFields(void);
extern "C" igMetaEnum *FUN_0045c540(void);
struct S_45c5e0 { char p[36]; unsigned f; };
extern "C" void *igRotateMode_GetMetaObject(void);
extern "C" int g_igRotateMode_vtable[4];
union U_45c630 { int vt; char b[160]; };
extern "C" int igRotateMode_GetVTable(void);
extern "C" void igRotateMode_EnsureRegistered(void);
extern "C" CallbackArray *igRotateMode_Register(void);
extern "C" void igRotateMode_GetMetaObjectFunction(void);
extern "C" void igRotateMode_InitFields(void);
extern "C" igMetaObject *igFlyMode_GetMetaObject(void);
struct Obj_45c970 { int *vt; char p4[8]; int sub[4]; char pad[108]; int *ref; char pe[20]; };
extern "C" int g_igFlyMode_vtable[4];
extern "C" int igFlyMode_GetVTable(void);
extern "C" void igFlyMode_EnsureRegistered(void);
extern "C" CallbackArray *igFlyMode_Register(void);
extern "C" void igFlyMode_GetMetaObjectFunction(void);
struct V2 { int x; int y; };
struct V3 { int x; int y; int z; };
extern "C" void igFlyMode_InitFields(void);
extern "C" igMetaObject *igCameraMode_GetMetaObject(void);
extern "C" int g_igCameraMode_vtable[4];
union U_45ccd0 { int vt; int w[21]; char b[84]; };
extern "C" int igCameraMode_GetVTable(void);
extern "C" void igCameraMode_EnsureRegistered(void);
extern "C" CallbackArray *igCameraMode_Register(void);
extern "C" void igCameraMode_GetMetaObjectFunction(void);
#include "dw4/scenegraph/igCamera.h"
extern "C" void igCameraMode_InitFields(void);
extern "C" igMetaObject *igViewMode_GetOrCreateMetaObject(void);
extern "C" void *igViewMode_GetMetaObject(void);
struct W { int *vt; int f[19]; };
extern "C" int igViewMode_GetVTable(void);
extern "C" void igViewMode_GetMetaObjectFunction(void);
extern "C" void igViewMode_InitFields(void);
extern "C" igMetaObject *igViewManager_GetOrCreateMetaObject(void);
extern "C" void *igViewManager_GetMetaObject(void);
extern "C" int g_igViewManager_vtable[4];
extern "C" int DAT_00542680[8];
union U_45d1a0 { int vt; int w[21]; char b[84]; };
extern "C" int igViewManager_GetVTable(void);
extern "C" CallbackArray *igViewManager_Register(void);
extern "C" void igViewManager_GetMetaObjectFunction(void);
extern "C" void igViewManager_InitFields(void);
struct Obj_45d8d0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" void** FUN_00136e10(void**, int);
#include "dw4/attrs/igColorAttr.h"
#include "dw4/attrs/igAttrList.h"
struct SigLogoRenderer_GetMetaObject { char pad[36]; unsigned int flags; int ok() { return (flags & 4) != 0; } };
struct Obj_45dc70 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
struct Obj_45df30 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" void *igActorManager_GetMetaObject(void);
struct Obj_45e2c0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int g_igActorManager_vtable[4];
extern "C" int igActorManager_GetVTable(void);
extern "C" O *FUN_0045e420(O *arg0, short arg1);
extern "C" void igActorManager_EnsureRegistered(void);
extern "C" CallbackArray *igActorManager_Register(void);
extern "C" void igActorManager_GetMetaObjectFunction(void);
#include "dw4/scenegraph/igNodeList.h"
#include "dw4/scenegraph/igAppearanceList.h"
#include "dw4/scenegraph/igActorList.h"
#include "dw4/attrs/igAlphaStateAttr.h"
#include "dw4/attrs/igCullFaceAttr.h"
#include "dw4/attrs/igDisplayListAttr.h"
#include "dw4/attrs/igGeometryAttr.h"
#include "dw4/attrs/igLightAttr.h"
#include "dw4/attrs/igLightList.h"
#include "dw4/attrs/igLightStateAttr.h"
#include "dw4/attrs/igLightStateAttrList.h"
#include "dw4/attrs/igModelViewMatrixAttr.h"
#include "dw4/attrs/igPolygonModeAttr.h"
#include "dw4/attrs/igShadeModelAttr.h"
#include "dw4/attrs/igViewportAttr.h"
#include "dw4/datapump/igDataPumpManager.h"
#include "dw4/gfx/GfxMetaEnums.h"
#include "dw4/gfx/igDisableExt.h"
#include "dw4/scenegraph/igBitMask.h"
#include "dw4/scenegraph/igGraphPathList.h"
#include "dw4/scenegraph/igIntersectTraversal.h"
#include "dw4/scenegraph/igLightSet.h"
#include "dw4/scenegraph/igOverrideAttrSet.h"
#include "dw4/windowinput/igWindow.h"
#include "dw4/viewer/ViewerInlineCopies.h"
extern "C" void igActorManager_InitFields(void);
extern "C" igMetaObject *igViewerLoadingFileMessage_GetMeta(void);
extern "C" igMetaObject *igViewerModeChangeMessage_GetMeta(void);

#endif
