#ifndef DW4_WINDOW_INPUT_LIBRARY_H
#define DW4_WINDOW_INPUT_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/windowinput/igInterfaceManager.h"
#include "dw4/windowinput/igWindow.h"

struct Rt;
struct Fld;
class VisualContext;
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igFloatArrayMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igMemoryRefMetaField.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igRawRefMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igUnsignedCharArrayMetaField.h"
#include "dw4/core/igUnsignedShortMetaField.h"
class igMemoryPoolView;
#include "dw4/gfx/igVisualContext.h"
extern "C" unsigned char g_WindowInputLibrary_registered;
extern "C" void WindowInputLibrary_MarkRegistered(void);
#include "dw4/core/igMemoryPoolContext.h"
extern "C" igMetaObject *g_igWindow_metaObject;
extern "C" igMetaObject *igWindow_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igWindow_GetMetaObject(void);
extern "C" void igWindow_EnsureRegistered(void);
extern "C" igMetaObject *igEventProducer_GetPublishedMetaObject(void);
extern "C" CallbackArray *igWindow_Register(void);
extern "C" void igWindow_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igEventProducer_metaObject;
extern "C" igMetaObject *igEventProducer_GetPublishedMetaObject(void);
extern "C" void FUN_00145e80(void);
extern "C" void igPsx2Window_GetMetaObjectFunction(void);
extern "C" igMetaEnum *FUN_00145eb0(void);
extern "C" igMetaObject *g_igInterfaceManager_metaObject;
extern "C" igMetaObject *igInterfaceManager_GetMetaObject(void);
extern "C" void igInterfaceManager_EnsureRegistered(void);
#include "dw4/core/igObject.h"
extern "C" void igInterfaceManager_GetMetaObjectFunction(void);
extern "C" void igInterfaceManager_InitFields(void);
extern "C" void igDefaultInterfaceManager_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igEventProducerList_metaObject;
extern "C" igMetaObject *igEventProducerList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igEventProducerList_GetMetaObject(void);
struct Obj { int *vt; char pad[28]; };
extern "C" int g_igEventProducerList_vtable[4];
#include "dw4/core/igObjectSystem.h"
extern "C" int igEventProducerList_GetVTable(void);
extern "C" void igEventProducerList_EnsureRegistered(void);
#include "dw4/core/igObjectList.h"
extern "C" CallbackArray *igEventProducerList_Register(void);
extern "C" void igEventProducerList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igEventProducer_GetMetaObject(void);
extern "C" void igEventProducer_EnsureRegistered(void);
extern "C" CallbackArray *igEventProducer_Register(void);
extern "C" void igEventProducer_GetMetaObjectFunction(void);
#include "dw4/datapump/igNonRefCountedObjectStack.h"
#include "dw4/sony/libpad.h"
extern "C" igMetaObject *igNonRefCountedObjectStack_GetPublishedMetaObject(void);
extern "C" igMetaObject *g_igControllerList_metaObject;
extern "C" igMetaObject *igControllerList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igControllerList_GetMetaObject(void);
typedef struct { int *vt; int pad[7]; } Obj_1463a0;
extern "C" int g_igControllerList_vtable[4];
extern "C" int igControllerList_GetVTable(void);
extern "C" void igControllerList_EnsureRegistered(void);
extern "C" CallbackArray *igControllerList_Register(void);
extern "C" void igControllerList_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igDefaultInterfaceManager_metaObject;
extern "C" igMetaObject *igDefaultInterfaceManager_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
extern "C" int g_igDefaultInterfaceManager_vtable[4];
extern "C" int DAT_00524da0[4];
union U { int vt; char b[80]; };
extern "C" int igDefaultInterfaceManager_GetVTable(void);
extern "C" void igDefaultInterfaceManager_EnsureRegistered(void);
extern "C" CallbackArray *igDefaultInterfaceManager_Register(void);
extern "C" igMetaObject *FUN_001465e0(void);
extern "C" void igDefaultInterfaceManager_InitFields(void);
extern "C" igMetaObject *g_igControllerManager_metaObject;
extern "C" igMetaObject *igControllerManager_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igControllerManager_GetMetaObject(void);
extern "C" void igControllerManager_EnsureRegistered(void);
extern "C" CallbackArray *igControllerManager_Register(void);
extern "C" void igControllerManager_GetMetaObjectFunction(void);
extern "C" void igControllerManager_InitFields(void);
extern "C" void igPsx2ControllerManager_GetMetaObjectFunction(void);
extern "C" igMetaEnum *FUN_00146850(void);
extern "C" igMetaObject *g_igController_metaObject;
extern "C" igMetaObject *igController_GetMetaObject(void);
extern "C" void igController_EnsureRegistered(void);
extern "C" CallbackArray *igController_Register(void);
extern "C" void igController_GetMetaObjectFunction(void);
extern "C" void igController_InitFields(void);
extern "C" void igPsx2Controller_GetMetaObjectFunction(void);
extern "C" igMetaObject *g_igPsx2Window_metaObject;
extern "C" igMetaObject *igPsx2Window_GetMetaObject(void);
#include "dw4/core/StringPool.h"
extern "C" int g_igPsx2Window_vtable[4];
union U_146ab0 { int vt; char b[64]; };
extern "C" int igPsx2Window_GetVTable(void);
extern "C" void igPsx2Window_EnsureRegistered(void);
extern "C" igMetaObject *igWindow_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2Window_Register(void);
extern "C" igMetaObject *igWindow_GetPublishedMetaObject(void);
extern "C" void igPsx2Window_InitFields(void);
extern "C" igMetaEnum *FUN_00146d90(void);
extern "C" igMetaObject *g_igPsx2ControllerManager_metaObject;
extern "C" igMetaObject *igPsx2ControllerManager_GetMetaObject(void);
extern "C" int g_igPsx2ControllerManager_vtable[4];
extern "C" int DAT_00524f00[4];
union U_146e40 { int vt; int w[5]; char b[20]; };
extern "C" int igPsx2ControllerManager_GetVTable(void);
extern "C" void igPsx2ControllerManager_EnsureRegistered(void);
extern "C" igMetaObject *igControllerManager_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2ControllerManager_Register(void);
extern "C" igMetaObject *FUN_00146f60(void);
extern "C" void igPsx2ControllerManager_InitFields(void);
extern "C" igMetaEnum *FUN_00147030(void);
extern "C" int igPsx2Controller_Create(int arg0);
extern "C" igMetaObject *g_igPsx2Controller_metaObject;
extern "C" igMetaObject *igPsx2Controller_GetMetaObject(void);
extern "C" int g_igPsx2Controller_vtable[4];
union U_147120 { int vt; int w[28]; void *p[28]; char b[112]; };
extern "C" int igPsx2Controller_GetVTable(void);
extern "C" void igPsx2Controller_EnsureRegistered(void);
extern "C" igMetaObject *igController_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2Controller_Register(void);
extern "C" igMetaObject *igController_GetPublishedMetaObject(void);
struct Fld { char p0[52]; int f52; int f56; };
extern "C" void igPsx2Controller_InitFields(void);
extern "C" int FUN_00147430(void *arg0, int arg1);
extern "C" int FUN_00147450(void *arg0, int arg1);
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); };
struct L { char p0[8]; int count; char pc[4]; V **items; };
struct O { char p0[8]; L *list; };
extern "C" void FUN_001474a0(O *arg0, int arg1);
extern "C" void igDefaultInterfaceManager_MouseMotion(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void igDefaultInterfaceManager_MouseButtonDown(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void igDefaultInterfaceManager_MouseButtonUp(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void igDefaultInterfaceManager_WindowMove(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void igDefaultInterfaceManager_WindowResize(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
extern "C" void igDefaultInterfaceManager_WindowClose(igDefaultInterfaceManager *arg0, void **arg1);
extern "C" void igDefaultInterfaceManager_KeyDown(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void igDefaultInterfaceManager_KeyUp(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void igDefaultInterfaceManager_ControllerJoystickMotion(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void igDefaultInterfaceManager_ControllerButtonDown(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void igDefaultInterfaceManager_ControllerButtonUp(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void igDefaultInterfaceManager_ControllerButtonPressure(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void igDefaultInterfaceManager_ControllerConnection(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void igDefaultInterfaceManager_ControllerDisconnection(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void igDefaultInterfaceManager_ControllerSlider(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void igDefaultInterfaceManager_ControllerPointOfView(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
typedef struct R { int w0; int refs; } R;
typedef struct L_147840 { char pad[8]; int cnt; char pad2[4]; R **arr; } L_147840;
struct A { char pad[8]; L_147840 *list; };
#include "dw4/core/igDataLists.h"
extern "C" void igInterfaceManager_RemoveAllEventProducers(struct A *arg0);
class S;
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(S *); };
struct L_147930 { char pad[8]; int count; char pad2[4]; VC **data; };
class S { public: char pad[8]; L_147930 *list; };
extern "C" void igInterfaceManager_HandleEvents(S *arg0);
extern "C" void FUN_001479b0(igPsx2Controller *arg0);
extern "C" void igPsx2Controller_InitDefaults(igPsx2Controller *self);
#include "dw4/core/igMemory.h"
extern "C" void igPsx2Controller_ReleaseDefaults(void *arg0);
extern "C" void Gap__igPsx2Controller__vfunc_31(void *arg0, int arg1, float *arg2, float *arg3);
class ControllerListener {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void onConnect(int window, igPsx2Controller *pad); virtual void onReset(int window, igPsx2Controller *pad);
};
struct PadActAlign {
    unsigned char data[6];
};
extern "C" void FUN_00148160(igPsx2Controller *pad, ControllerListener *listener);
extern "C" void Gap__igPsx2Controller__vfunc_23(igPsx2Controller *self, ControllerListener *listener);
typedef struct C { char pad[60]; int f60; int f64; char pad68[23]; unsigned char b91[6]; } C;
extern "C" void Gap__igPsx2Controller__vfunc_37(C *arg0, int arg1, float fparg0);
extern "C" int FUN_00147ff0(void *arg0, unsigned int arg1);
struct O_1480a0 { char pad[12]; unsigned char f12; };
extern "C" int FUN_001480a0(struct O_1480a0 *o, int a);
class Al { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
class Pd { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void vX(int); };
class Pe { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void vX(int); };
struct Rt { char pad[56]; int f56; };
#include "dw4/core/igResult.h"
#include <string.h>
#include "dw4/core/igStringObj.h"
#include "dw4/core/igRegistry.h"
struct PropertyText : igObject { char *chars; };
extern "C" void Gap__igPsx2ControllerManager__vfunc_24(igPsx2ControllerManager *arg0, int arg1);
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
extern "C" void Gap__igPsx2Controller__vfunc_36(igPsx2Controller *self, igObject *window);
extern "C" void Gap__igPsx2Controller__vfunc_33(void *arg0, short arg1);
extern "C" int Gap__igPsx2ControllerManager__vfunc_25(igPsx2ControllerManager *arg0);
extern "C" void igPsx2ControllerManager_userDestruct(void *arg0);
struct R_148b00 { int w0; int rc; };
struct A_148b00 { char pad[24]; struct R_148b00 *f24; char pad2[4]; int *f32; int f36; char f40; };
extern "C" void Gap__igPsx2Window__vfunc_26(struct A_148b00 *arg0);
extern "C" int Gap__igPsx2Window__vfunc_39(igPsx2Window *self, igObject *viewContext);
class igPsx2WindowView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void vfunc_22(const char *name, int width, int height);
    unsigned int _refCount;
    int _width;
    int _height;
    char _pad16[16];
    const char *_winName;
};
extern "C" void Gap__igPsx2Window__vfunc_25(igPsx2WindowView *self);
struct RenderDestinationDesc {
    int kind;
    int width;
    int height;
    int bpp;
    int alpha;
    int bppDepth;
    float clearDepth;
    float scale;
};
struct VisualResult { int value; };
class VisualContext {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual VisualResult beginWindow();
    virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    virtual int createRenderDestination(RenderDestinationDesc *desc);
    virtual void d45(); virtual void d46(); virtual void d47();
    virtual int currentRenderDestination();
    virtual void d49(); virtual void d50();
    virtual void getRenderDestinationSize(int handle, int *width, int *height);
    unsigned int _refCount;
};
#include <stdio.h>
extern "C" int Gap__igPsx2Window__vfunc_24(igPsx2Window *self, const char *name, int width, int height);
extern "C" void Gap__igPsx2Window__vfunc_27(int *arg0, char *arg1);
extern "C" int Gap__igPsx2Window__vfunc_34(void *arg0, int dummy1, int arg2, int arg3, int arg4);
extern "C" void Gap__igPsx2Window__vfunc_35(void *arg0, char *arg1, int *arg2, int *arg3, int *arg4);
extern "C" igMetaObject *igPsx2Window_GetMeta(void);
extern "C" int Gap__igPsx2Window__vfunc_28(void *arg0);
extern "C" void Gap__igPsx2Window__vfunc_29(void);
extern "C" void Gap__igPsx2Window__vfunc_30(void *d0, int *arg1, int *arg2);
extern "C" void Gap__igPsx2Window__vfunc_31(void);
extern "C" void Gap__igPsx2Window__vfunc_32(void *d0, int *arg1, int *arg2);
extern "C" void Gap__igPsx2Window__vfunc_36(void);
extern "C" int Gap__igPsx2Window__vfunc_37(void);
extern "C" int Gap__igPsx2Window__vfunc_38(igPsx2Window *self);
extern "C" int Gap__igPsx2Window__vfunc_42(igPsx2Window *self);
extern "C" void Gap__igPsx2Window__vfunc_33(void *d0, int *arg1, int *arg2);
extern "C" void Gap__igPsx2Window__vfunc_40(int *status_out);
extern "C" int Gap__igPsx2Window__vfunc_41(igPsx2Window *self);
extern "C" void Gap__igPsx2Window__vfunc_23(void);
extern "C" unsigned char Gap__igPsx2Window__vfunc_43(igPsx2Window *self);
extern "C" int igPsx2ControllerManager_GetMeta(void);
extern "C" igMetaObject *igPsx2Controller_GetMeta(void);
extern "C" int Gap__igPsx2Controller__vfunc_24(void *arg0);
extern "C" void Gap__igPsx2Controller__vfunc_25(void *arg0, int arg1);
extern "C" unsigned short Gap__igPsx2Controller__vfunc_26(void *arg0);
extern "C" void Gap__igPsx2Controller__vfunc_27(void *arg0, short arg1);
extern "C" unsigned short Gap__igPsx2Controller__vfunc_32(void *arg0);
extern "C" int Gap__igPsx2Controller__vfunc_28(void *arg0, int arg1);
class O_149230 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int); };
#include "dw4/support/softfloat.h"
#include "dw4/sony/libmtap.h"
#include "dw4/core/igPsx2File.h"
extern "C" float Gap__igPsx2Controller__vfunc_29(O_149230 *arg0, int arg1);
extern "C" int Gap__igPsx2Controller__vfunc_30(void *arg0);
extern "C" unsigned char Gap__igPsx2Controller__vfunc_34(igPsx2Controller *self);
extern "C" int Gap__igPsx2Controller__vfunc_35(igPsx2Controller *self);
extern "C" igMetaObject *FUN_00149320(void);
extern "C" void igInterfaceManager_AddEventProducer(void *a0, igObject *object);
extern "C" int igDefaultInterfaceManager_GetMeta(void);
extern "C" igMetaObject *FUN_00149350(void);
extern "C" int igControllerList_GetMeta(void);
extern "C" igMetaObject *igNonRefCountedObjectStack_GetMeta(void);
extern "C" igMetaObject *igEventProducerList_GetMeta(void);
extern "C" int igControllerList_GetElementMeta(void);
extern "C" igMetaObject *igEventProducerList_GetElementMeta(void);
extern "C" void igNonRefCountedObjectStack_TrimCapacity(igDataList *arg0);

#endif
