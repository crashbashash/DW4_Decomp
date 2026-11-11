#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

struct Rt;
struct Fld;
class VisualContext;
extern "C" int igMetaObject_RunStaticInit(...);
extern "C" unsigned char g_WindowInputLibrary_registered;
extern "C" void WindowInputLibrary_MarkRegistered(void);
extern "C" int igMetaObject_CreateInstance(int, int);
extern "C" void FUN_00145d00(int arg0);
extern "C" int igMetaObject_Create(...);
extern "C" void *Memory_GetAllocatorBySelector(...);
extern "C" int DAT_0055f5d8[4];
extern "C" int DAT_00587040[4];
extern "C" int FUN_00145d40(void);
extern "C" igMetaObject *g_igWindow_metaObject[4];
extern "C" igMetaObject *igWindow_GetMetaObject(void);
extern "C" void FUN_00145de0(void);
extern "C" char igEventProducer_GetPublishedMetaObject[];
extern "C" char igWindow_className[];
extern "C" int igMetaObject_RegisterClass(...);
extern "C" void igWindow_Register(void);
extern "C" void thunk_igWindow_GetMetaObject(void);
extern "C" int DAT_0055f600[4];
extern "C" int FUN_00145e70(void);
extern "C" void FUN_00145e80(void);
extern "C" void thunk_FUN_00146a60(void);
extern "C" int igMetaEnum_Create(...);
extern "C" int DAT_00486dd0[4];
extern "C" int DAT_00486f80[4];
extern "C" int DAT_004d64d8[4];
extern "C" int DAT_0055f5e0[4];
extern "C" int FUN_00145eb0(void);
extern "C" igMetaObject *g_igInterfaceManager_metaObject[4];
extern "C" igMetaObject *igInterfaceManager_GetMetaObject(void);
extern "C" void FUN_00145f60(void);
extern "C" char igObject_GetMetaObject_ParentAccessor[];
extern "C" char igObject_Register[];
extern "C" char g_igInterfaceManager_callbackList[];
extern "C" char igInterfaceManager_className[];
extern "C" void igInterfaceManager_Register(void);
extern "C" void thunk_igInterfaceManager_GetMetaObject(void);
extern "C" int igMetaObject_CreateFields(...);
extern "C" struct Fld *igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int DAT_00487130[4];
extern "C" int DAT_00487138[4];
extern "C" int DAT_00487140[4];
extern "C" int DAT_00487148[4];
extern "C" int DAT_0055f5e8[4];
extern "C" void igInterfaceManager_InitFields(void);
extern "C" void thunk_FUN_00146470(void);
extern "C" int DAT_0055f5f8[4];
extern "C" int FUN_001460b0(void);
extern "C" igMetaObject *g_igEventProducerList_metaObject[4];
extern "C" igMetaObject *igEventProducerList_GetMetaObject(void);
struct Obj { int *vt; char pad[28]; };
extern "C" int igObject_InitHeader(...);
extern "C" int DAT_00525040[4];
extern "C" Rt *DAT_00586dc8[4];
extern "C" int igEventProducerList_GetVTable(void);
extern "C" void FUN_00146190(void);
extern "C" char igObjectList_GetPublishedMetaObject[];
extern "C" char igObjectList_Register[];
extern "C" char g_igEventProducerList_callbackList[];
extern "C" char igEventProducerList_className[];
extern "C" void igEventProducerList_Register(void);
extern "C" void thunk_igEventProducerList_GetMetaObject(void);
extern "C" igMetaObject *g_igEventProducer_metaObject[4];
extern "C" igMetaObject *igEventProducer_GetMetaObject(void);
extern "C" void FUN_00146270(void);
extern "C" char igEventProducer_className[];
extern "C" void igEventProducer_Register(void);
extern "C" void thunk_igEventProducer_GetMetaObject(void);
extern "C" int DAT_00562b78[4];
extern "C" int FUN_001462f0(void);
extern "C" int DAT_0055f608[4];
extern "C" int FUN_00146300(void);
extern "C" igMetaObject *g_igControllerList_metaObject[4];
extern "C" igMetaObject *igControllerList_GetMetaObject(void);
typedef struct { int *vt; int pad[7]; } Obj_1463a0;
extern "C" int DAT_00524f70[4];
extern "C" int igControllerList_GetVTable(void);
extern "C" void FUN_001463e0(void);
extern "C" char g_igControllerList_callbackList[];
extern "C" char igControllerList_className[];
extern "C" void igControllerList_Register(void);
extern "C" void thunk_igControllerList_GetMetaObject(void);
extern "C" igMetaObject *g_igDefaultInterfaceManager_metaObject[4];
extern "C" igMetaObject *FUN_00146470(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
extern "C" int DAT_00524e50[4];
extern "C" int DAT_00524da0[4];
union U { int vt; char b[80]; };
extern "C" int igDefaultInterfaceManager_GetVTable(void);
extern "C" void FUN_00146560(void);
extern "C" char igInterfaceManager_GetPublishedMetaObject[];
extern "C" char igDefaultInterfaceManager_className[];
extern "C" void igDefaultInterfaceManager_Register(void);
extern "C" int FUN_001465e0(void);
extern "C" int DAT_00487160[4];
extern "C" int DAT_004871a0[4];
extern "C" int DAT_004871e0[4];
extern "C" int DAT_00487220[4];
extern "C" int DAT_0055f610[4];
extern "C" void igDefaultInterfaceManager_InitFields(void);
extern "C" int DAT_0055f698[4];
extern "C" int FUN_00146660(void);
extern "C" igMetaObject *g_igControllerManager_metaObject[4];
extern "C" igMetaObject *igControllerManager_GetMetaObject(void);
extern "C" void FUN_00146700(void);
extern "C" char g_igControllerManager_callbackList[];
extern "C" char igControllerManager_className[];
extern "C" void igControllerManager_Register(void);
extern "C" void thunk_igControllerManager_GetMetaObject(void);
extern "C" int DAT_00487268[4];
extern "C" int DAT_00487270[4];
extern "C" int DAT_00487278[4];
extern "C" int DAT_00487280[4];
extern "C" void igControllerManager_InitFields(void);
extern "C" void thunk_igPsx2ControllerManager_GetMetaObject(void);
extern "C" int DAT_00487290[4];
extern "C" int DAT_00487360[4];
extern "C" int DAT_004d6bc8[4];
extern "C" int DAT_0055f6a8[4];
extern "C" int FUN_00146850(void);
extern "C" igMetaObject *g_igController_metaObject[4];
extern "C" igMetaObject *igController_GetMetaObject(void);
extern "C" void FUN_00146900(void);
extern "C" char igController_className[];
extern "C" void igController_Register(void);
extern "C" void thunk_igController_GetMetaObject(void);
extern "C" int igIntMetaField_GetDefaultDescriptor(...);
extern "C" int DAT_00487428[4];
extern "C" int DAT_00487430[4];
extern "C" int DAT_00487438[4];
extern "C" int DAT_00487440[4];
extern "C" int DAT_0055f6b0[4];
extern "C" void igController_InitFields(void);
extern "C" void thunk_igPsx2Controller_GetMetaObject(void);
extern "C" igMetaObject *g_igPsx2Window_metaObject[4];
extern "C" igMetaObject *FUN_00146a60(void);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int DAT_00524be0[4];
union U_146ab0 { int vt; char b[64]; };
extern "C" int igPsx2Window_GetVTable(void);
extern "C" void FUN_00146b80(void);
extern "C" char igWindow_GetPublishedMetaObject[];
extern "C" char g_igPsx2Window_callbackList[];
extern "C" char igPsx2Window_className[];
extern "C" void igPsx2Window_Register(void);
extern "C" int FUN_00146c10(void);
extern "C" int FUN_0014a040(...);
extern "C" int FUN_002d3890(...);
extern "C" int FUN_002ea4b0(...);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" int DAT_00487450[4];
extern "C" int DAT_00487480[4];
extern "C" int DAT_004874b0[4];
extern "C" int DAT_004874e0[4];
extern "C" int DAT_0055f6c8[4];
extern "C" void igPsx2Window_InitFields(void);
extern "C" int DAT_00487510[4];
extern "C" int DAT_00487520[4];
extern "C" int DAT_004d6ce8[4];
extern "C" int DAT_0055f730[4];
extern "C" int FUN_00146d90(void);
extern "C" igMetaObject *g_igPsx2ControllerManager_metaObject[4];
extern "C" igMetaObject *igPsx2ControllerManager_GetMetaObject(void);
extern "C" int DAT_00524c90[4];
extern "C" int DAT_00524f00[4];
union U_146e40 { int vt; int w[5]; char b[20]; };
extern "C" int igPsx2ControllerManager_GetVTable(void);
extern "C" void FUN_00146ee0(void);
extern "C" char igControllerManager_GetPublishedMetaObject[];
extern "C" char igPsx2ControllerManager_className[];
extern "C" void igPsx2ControllerManager_Register(void);
extern "C" int FUN_00146f60(void);
extern "C" int FUN_002dc7a0(...);
extern "C" int DAT_00487530[4];
extern "C" int DAT_00487540[4];
extern "C" int DAT_00487550[4];
extern "C" int DAT_00487560[4];
extern "C" int DAT_00487570[4];
extern "C" int DAT_0055f738[4];
extern "C" void igPsx2ControllerManager_InitFields(void);
extern "C" int DAT_00487580[4];
extern "C" int DAT_004875a0[4];
extern "C" int DAT_004d6e30[4];
extern "C" int DAT_0055f758[4];
extern "C" int FUN_00147030(void);
extern "C" int FUN_00147090(int arg0);
extern "C" igMetaObject *g_igPsx2Controller_metaObject[4];
extern "C" igMetaObject *igPsx2Controller_GetMetaObject(void);
extern "C" int DAT_00524d00[4];
union U_147120 { int vt; int w[28]; void *p[28]; char b[112]; };
extern "C" int igPsx2Controller_GetVTable(void);
extern "C" void FUN_001471b0(void);
extern "C" char igController_GetPublishedMetaObject[];
extern "C" char g_igPsx2Controller_callbackList[];
extern "C" char igPsx2Controller_className[];
extern "C" void igPsx2Controller_Register(void);
extern "C" int FUN_00147240(void);
extern "C" int FUN_0030eda0(...);
struct Fld { char p0[52]; int f52; int f56; };
extern "C" int DAT_004875d0[4];
extern "C" int DAT_00487630[4];
extern "C" int DAT_00487690[4];
extern "C" int DAT_004876f0[4];
extern "C" int DAT_00487750[4];
extern "C" int DAT_00487758[4];
extern "C" int DAT_0055f760[4];
extern "C" int FUN_002d1870(...);
extern "C" void igPsx2Controller_InitFields(void);
extern "C" int FUN_00147430(void *arg0, int arg1);
extern "C" int FUN_00147450(void *arg0, int arg1);
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); };
struct L { char p0[8]; int count; char pc[4]; V **items; };
struct O { char p0[8]; L *list; };
extern "C" void FUN_001474a0(O *arg0, int arg1);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_26(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_27(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_28(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_29(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_30(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
extern "C" void Gap__igDefaultInterfaceManager__vfunc_31(igDefaultInterfaceManager *arg0, void **arg1);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_40(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_41(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_32(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_33(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_34(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_35(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_36(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_37(igDefaultInterfaceManager *arg0, int arg1, int arg2);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_38(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__igDefaultInterfaceManager__vfunc_39(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3);
typedef struct R { int w0; int refs; } R;
typedef struct L_147840 { char pad[8]; int cnt; char pad2[4]; R **arr; } L_147840;
struct A { char pad[8]; L_147840 *list; };
extern "C" int List_Reserve(...);
extern "C" void FUN_00147840(struct A *arg0);
class S;
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(S *); };
struct L_147930 { char pad[8]; int count; char pad2[4]; VC **data; };
class S { public: char pad[8]; L_147930 *list; };
extern "C" void FUN_00147930(S *arg0);
extern "C" void FUN_001479b0(igPsx2Controller *arg0);
extern "C" int Gap__Core__igObject__vfunc_09(...);
extern "C" void Gap__igPsx2Controller__vfunc_11(int arg0);
extern "C" int scePadPortClose(int, int);
extern "C" int Memory_FreeBuffer(...);
extern "C" int Gap__Core__igObject__vfunc_10(void *);
extern "C" void Gap__igPsx2Controller__vfunc_12(void *arg0);
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
extern "C" PadActAlign DAT_00487760;
extern "C" int FUN_00118390(int port, int slot);
extern "C" int FUN_001184a8(int port, int slot);
extern "C" int FUN_00118530(int port, int slot, int actno, int term);
extern "C" int FUN_00118770(int port, int slot, int term, int offs);
extern "C" int FUN_00118c60(int port, int slot);
extern "C" int scePadSetMainMode(int port, int slot, int offs, int lock);
extern "C" int scePadSetActAlign(int port, int slot, const unsigned char *data);
extern "C" int scePadEnterPressMode(int port, int slot);
extern "C" int scePadExitPressMode(int port, int slot);
extern "C" void FUN_00148160(igPsx2Controller *pad, ControllerListener *listener);
extern "C" void Gap__igPsx2Controller__vfunc_23(igPsx2Controller *self, ControllerListener *listener);
extern "C" int FUN_00118960(...);
typedef struct C { char pad[60]; int f60; int f64; char pad68[23]; unsigned char b91[6]; } C;
extern "C" void Gap__igPsx2Controller__vfunc_37(C *arg0, int arg1, float fparg0);
extern "C" int FUN_00147ff0(void *arg0, unsigned int arg1);
struct O_1480a0 { char pad[12]; unsigned char f12; };
extern "C" int FUN_001480a0(struct O_1480a0 *o, int a);
class Al { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
class Pd { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void vX(int); };
class Pe { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void vX(int); };
struct Rt { char pad[56]; int f56; };
extern "C" int DAT_004fb410[4];
struct LoadStatus { int v; bool ok() const { return v == DAT_004fb410[0]; } };
extern "C" int FUN_00117c78(...);
extern "C" int scePadPortOpen(...);
extern "C" int strncmp(...);
extern "C" int FUN_00225300(...);
extern "C" void *FUN_002b9500(...);
extern "C" int FUN_00306770(...);
extern "C" LoadStatus FUN_0032cf50(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" void *igObject_GetAllocator(...);
extern "C" int strcmp(...);
extern "C" int sceMtapPortOpen(...);
extern "C" char *DAT_004c22f0[4];
extern "C" int DAT_004d6cc8[4];
extern "C" int DAT_004d6ce0[4];
extern "C" int DAT_004d7020[4];
extern "C" int DAT_004d7030[4];
extern "C" int DAT_004d7040[4];
extern "C" int DAT_004d7050[4];
extern "C" int DAT_004d7058[4];
extern "C" int DAT_004d7060[4];
extern "C" int DAT_00587060[4];
extern "C" unsigned char GPR_00554b18;
extern "C" unsigned char GPR_00554c14;
struct PropertyText : igObject { char *chars; };
extern "C" void Gap__igPsx2ControllerManager__vfunc_24(igPsx2ControllerManager *arg0, int arg1);
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
extern "C" int FUN_00100610(...);
extern "C" void **FUN_001489a0(void **arg0, short arg1);
extern "C" void Gap__igPsx2Controller__vfunc_36(igPsx2Controller *self, igObject *window);
extern "C" void Gap__igPsx2Controller__vfunc_33(void *arg0, short arg1);
extern "C" int Gap__igPsx2ControllerManager__vfunc_25(igPsx2ControllerManager *arg0);
extern "C" void Gap__igPsx2ControllerManager__vfunc_10(void *arg0);
extern "C" int FUN_002eb010(...);
extern "C" int StringPool_Construct(...);
extern "C" int *StringPool_Intern(...);
extern "C" int DAT_00586f20[4];
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
extern "C" VisualContext *FUN_0014a000(void *allocator);
extern "C" int printf(const char *, ...);
extern "C" char DAT_004d7070[];
extern "C" char DAT_004d7080[];
extern "C" int Gap__igPsx2Window__vfunc_24(igPsx2Window *self, const char *name, int width, int height);
extern "C" void Gap__igPsx2Window__vfunc_27(int *arg0, char *arg1);
extern "C" int Gap__igPsx2Window__vfunc_34(void *arg0, int dummy1, int arg2, int arg3, int arg4);
extern "C" void Gap__igPsx2Window__vfunc_35(void *arg0, char *arg1, int *arg2, int *arg3, int *arg4);
extern "C" int Gap__igPsx2Window__vfunc_22(void);
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
extern "C" int g_allocatorFailureStatus[4];
extern "C" void Gap__igPsx2Window__vfunc_40(int *status_out);
extern "C" int Gap__igPsx2Window__vfunc_41(igPsx2Window *self);
extern "C" void Gap__igPsx2Window__vfunc_23(void);
extern "C" unsigned char Gap__igPsx2Window__vfunc_43(igPsx2Window *self);
extern "C" int Gap__igPsx2ControllerManager__vfunc_22(void);
extern "C" int Gap__igPsx2Controller__vfunc_22(void);
extern "C" int Gap__igPsx2Controller__vfunc_24(void *arg0);
extern "C" void Gap__igPsx2Controller__vfunc_25(void *arg0, int arg1);
extern "C" unsigned short Gap__igPsx2Controller__vfunc_26(void *arg0);
extern "C" void Gap__igPsx2Controller__vfunc_27(void *arg0, short arg1);
extern "C" unsigned short Gap__igPsx2Controller__vfunc_32(void *arg0);
extern "C" int Gap__igPsx2Controller__vfunc_28(void *arg0, int arg1);
class O_149230 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int); };
extern "C" float dptofp(long long);
extern "C" float Gap__igPsx2Controller__vfunc_29(O_149230 *arg0, int arg1);
extern "C" int Gap__igPsx2Controller__vfunc_30(void *arg0);
extern "C" unsigned char Gap__igPsx2Controller__vfunc_34(igPsx2Controller *self);
extern "C" int Gap__igPsx2Controller__vfunc_35(igPsx2Controller *self);
extern "C" int FUN_00149320(void);
extern "C" void FUN_00149330(int a0);
extern "C" int Gap__igDefaultInterfaceManager__vfunc_22(void);
extern "C" int FUN_00149350(void);
extern "C" int Gap__igControllerList__vfunc_22(void);
extern "C" int Gap__igNonRefCountedObjectStack__vfunc_22(void);
extern "C" int Gap__igEventProducerList__vfunc_22(void);
extern "C" int Gap__igControllerList__vfunc_24(void);
extern "C" int Gap__igEventProducerList__vfunc_24(void);
extern "C" void Gap__igNonRefCountedObjectStack__vfunc_18(igDataList *arg0);

void WindowInputLibrary_MarkRegistered(void) {
    if (g_WindowInputLibrary_registered == 0) {
        g_WindowInputLibrary_registered = 1;
    }
}

void FUN_00145d00(int arg0) {
    FUN_00145de0();
    igMetaObject_CreateInstance(*(int *)0x55F5D8, arg0);
}

int FUN_00145d40(void) {
    if (DAT_0055f5d8[0] == 0) {
        DAT_0055f5d8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f5d8[0];
}

igMetaObject *igWindow_GetMetaObject(void)
{
    igMetaObject *g = g_igWindow_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00145de0();
    return g_igWindow_metaObject[0];
}

void FUN_00145de0(void)
{
    igMetaObject_RunStaticInit(igWindow_Register);
}

void igWindow_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igWindow_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igWindow_GetMetaObject,
        igWindow_className,
        8, /* instance size */
        0,
        FUN_00145e80,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igWindow_GetMetaObject(void) {
    igWindow_GetMetaObject();
}

int FUN_00145e70(void) {
    return DAT_0055f600[0];
}

void FUN_00145e80(void) {
    *(int *)((char *)(DAT_0055f5d8[0]) + 60) = (int)(&thunk_FUN_00146a60);
}

void thunk_FUN_00146a60(void) {
    FUN_00146a60();
}

int FUN_00145eb0(void) {
    if (DAT_0055f5e0[0] == 0) {
        DAT_0055f5e0[0] = igMetaEnum_Create(&DAT_004d64d8[0], &DAT_00486dd0[0], &DAT_00486f80[0], 0x69);
    }
    return DAT_0055f5e0[0];
}

igMetaObject *igInterfaceManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInterfaceManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00145f60();
    return g_igInterfaceManager_metaObject[0];
}

void FUN_00145f60(void)
{
    igMetaObject_RunStaticInit(igInterfaceManager_Register);
}

void igInterfaceManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInterfaceManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInterfaceManager_GetMetaObject,
        igInterfaceManager_className,
        0xC, /* instance size */
        0,
        &igInterfaceManager_InitFields,
        0, /* extra callback item */
        g_igInterfaceManager_callbackList /* callback list */
    );
}

void thunk_igInterfaceManager_GetMetaObject(void) {
    igInterfaceManager_GetMetaObject();
}

void igInterfaceManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055f5e8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487130[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001460b0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00487138[0], &DAT_00487140[0], &DAT_00487148[0], temp_s2);
    *(int *)((char *)(DAT_0055f5e8[0]) + 60) = (int)(thunk_FUN_00146470);
}

void thunk_FUN_00146470(void) {
    FUN_00146470();
}

int FUN_001460b0(void) {
    if (DAT_0055f5f8[0] == 0) {
        DAT_0055f5f8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f5f8[0];
}

igMetaObject *igEventProducerList_GetMetaObject(void)
{
    igMetaObject *g = g_igEventProducerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146190();
    return g_igEventProducerList_metaObject[0];
}

int igEventProducerList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00525040[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00146190(void)
{
    igMetaObject_RunStaticInit(igEventProducerList_Register);
}

void igEventProducerList_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventProducerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igEventProducerList_GetMetaObject,
        igEventProducerList_className,
        0x14, /* instance size */
        igEventProducerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igEventProducerList_callbackList /* callback list */
    );
}

void thunk_igEventProducerList_GetMetaObject(void) {
    igEventProducerList_GetMetaObject();
}

igMetaObject *igEventProducer_GetMetaObject(void)
{
    igMetaObject *g = g_igEventProducer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146270();
    return g_igEventProducer_metaObject[0];
}

void FUN_00146270(void)
{
    igMetaObject_RunStaticInit(igEventProducer_Register);
}

void igEventProducer_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igEventProducer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEventProducer_GetMetaObject,
        igEventProducer_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igEventProducer_GetMetaObject(void) {
    igEventProducer_GetMetaObject();
}

int FUN_001462f0(void) {
    return DAT_00562b78[0];
}

int FUN_00146300(void) {
    if (DAT_0055f608[0] == 0) {
        DAT_0055f608[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f608[0];
}

igMetaObject *igControllerList_GetMetaObject(void)
{
    igMetaObject *g = g_igControllerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001463e0();
    return g_igControllerList_metaObject[0];
}

int igControllerList_GetVTable(void) {
    Obj_1463a0 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00524f70[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001463e0(void)
{
    igMetaObject_RunStaticInit(igControllerList_Register);
}

void igControllerList_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igControllerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igControllerList_GetMetaObject,
        igControllerList_className,
        0x14, /* instance size */
        igControllerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igControllerList_callbackList /* callback list */
    );
}

void thunk_igControllerList_GetMetaObject(void) {
    igControllerList_GetMetaObject();
}

igMetaObject *FUN_00146470(void)
{
    unsigned char ready;
    if (g_igDefaultInterfaceManager_metaObject[0] != 0) {
        ready = (g_igDefaultInterfaceManager_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00146560();
done:
    return g_igDefaultInterfaceManager_metaObject[0];
}

int igDefaultInterfaceManager_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00524da0[0];
    u.vt = (int)&DAT_00524e50[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524da0[0];
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

void FUN_00146560(void)
{
    igMetaObject_RunStaticInit(igDefaultInterfaceManager_Register);
}

void igDefaultInterfaceManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultInterfaceManager_metaObject,
        igInterfaceManager_Register,
        igInterfaceManager_GetPublishedMetaObject,
        thunk_FUN_00146470,
        igDefaultInterfaceManager_className,
        0x4C, /* instance size */
        igDefaultInterfaceManager_GetVTable,
        &igDefaultInterfaceManager_InitFields,              /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

int FUN_001465e0(void) {
    return DAT_0055f5e8[0];
}

void igDefaultInterfaceManager_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f610[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487160[0], 0x10);
    igMetaObject_NameFields(temp_s0, &DAT_004871a0[0], &DAT_004871e0[0], &DAT_00487220[0], temp_s1);
}

int FUN_00146660(void) {
    if (DAT_0055f698[0] == 0) {
        DAT_0055f698[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f698[0];
}

igMetaObject *igControllerManager_GetMetaObject(void)
{
    igMetaObject *g = g_igControllerManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146700();
    return g_igControllerManager_metaObject[0];
}

void FUN_00146700(void)
{
    igMetaObject_RunStaticInit(igControllerManager_Register);
}

void igControllerManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igControllerManager_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igControllerManager_GetMetaObject,
        igControllerManager_className,
        0xC, /* instance size */
        0,
        &igControllerManager_InitFields,
        0, /* extra callback item */
        g_igControllerManager_callbackList /* callback list */
    );
}

void thunk_igControllerManager_GetMetaObject(void) {
    igControllerManager_GetMetaObject();
}

void igControllerManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055f698[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487268[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00146300();
    *(char *)((char *)(temp_s1) + 52) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00487270[0], &DAT_00487278[0], &DAT_00487280[0], temp_s2);
    *(int *)((char *)(DAT_0055f698[0]) + 60) = (int)(&thunk_igPsx2ControllerManager_GetMetaObject);
}

void thunk_igPsx2ControllerManager_GetMetaObject(void) {
    igPsx2ControllerManager_GetMetaObject();
}

int FUN_00146850(void) {
    if (DAT_0055f6a8[0] == 0) {
        DAT_0055f6a8[0] = igMetaEnum_Create(&DAT_004d6bc8[0], &DAT_00487290[0], &DAT_00487360[0], 0x31);
    }
    return DAT_0055f6a8[0];
}

igMetaObject *igController_GetMetaObject(void)
{
    igMetaObject *g = g_igController_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146900();
    return g_igController_metaObject[0];
}

void FUN_00146900(void)
{
    igMetaObject_RunStaticInit(igController_Register);
}

void igController_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igController_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igController_GetMetaObject,
        igController_className,
        0x10, /* instance size */
        0,
        &igController_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igController_GetMetaObject(void) {
    igController_GetMetaObject();
}

void igController_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055f6b0[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487428[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 60) = igIntMetaField_GetDefaultDescriptor();
    *(char *)((char *)(temp_s1) + 53) = 1;
    *(char *)((char *)(temp_s1) + 64) = 1;
    *(char *)((char *)(temp_s1) + 65) = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00487430[0], &DAT_00487438[0], &DAT_00487440[0], temp_s2);
    *(int *)((char *)(DAT_0055f6b0[0]) + 60) = (int)thunk_igPsx2Controller_GetMetaObject;
}

void thunk_igPsx2Controller_GetMetaObject(void) {
    igPsx2Controller_GetMetaObject();
}

igMetaObject *FUN_00146a60(void)
{
    igMetaObject *meta = g_igPsx2Window_metaObject[0];
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_00146b80();
end:
    return g_igPsx2Window_metaObject[0];
}

int igPsx2Window_GetVTable(void) {
    union U_146ab0 u;
    int temp_s0;
    char *q0;
    S_ref *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00524be0[0];
    q1 = (S_ref *)&u.b[24];
    *(int *)q1 = 0;
    q0 = &u.b[32];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524be0[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
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
    return temp_s0;
}

void FUN_00146b80(void)
{
    igMetaObject_RunStaticInit(igPsx2Window_Register);
}

void igPsx2Window_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Window_metaObject,
        igWindow_Register,
        igWindow_GetPublishedMetaObject,
        thunk_FUN_00146a60,
        igPsx2Window_className,
        sizeof(igPsx2Window),                     /* Instance size. */
        igPsx2Window_GetVTable,
        &igPsx2Window_InitFields,
        0, /* extra callback item */
        g_igPsx2Window_callbackList /* callback list */
    );
}

int FUN_00146c10(void) {
    return DAT_0055f5d8[0];
}

void igPsx2Window_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055f6c8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487450[0], 0xC);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2), 0x280);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 0x1C0);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1) + 56) = FUN_0014a040();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 0);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9), 0x18);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA), 8);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB), 0x20);
    igMetaObject_NameFields(temp_s0, &DAT_00487480[0], &DAT_004874b0[0], &DAT_004874e0[0], temp_s2);
    *(int *)((char *)(DAT_0055f6c8[0]) + 64) = (int)thunk_igWindow_GetMetaObject;
}

int FUN_00146d90(void) {
    if (DAT_0055f730[0] == 0) {
        DAT_0055f730[0] = igMetaEnum_Create(&DAT_004d6ce8[0], &DAT_00487510[0], &DAT_00487520[0], 4);
    }
    return DAT_0055f730[0];
}

igMetaObject *igPsx2ControllerManager_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ControllerManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146ee0();
    return g_igPsx2ControllerManager_metaObject[0];
}

int igPsx2ControllerManager_GetVTable(void) {
    union U_146e40 u;
    int temp_s0;
    S_ref *q1;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00524f00[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_00524c90[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00524f00[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_00146ee0(void)
{
    igMetaObject_RunStaticInit(igPsx2ControllerManager_Register);
}

void igPsx2ControllerManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2ControllerManager_metaObject,
        igControllerManager_Register,
        igControllerManager_GetPublishedMetaObject,
        thunk_igPsx2ControllerManager_GetMetaObject,
        igPsx2ControllerManager_className,
        0x14, /* instance size */
        igPsx2ControllerManager_GetVTable,
        &igPsx2ControllerManager_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

int FUN_00146f60(void) {
    return DAT_0055f698[0];
}

void igPsx2ControllerManager_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f738[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487530[0], 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00487570[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00146d90);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00487540[0], &DAT_00487550[0], &DAT_00487560[0], temp_s2);
}

int FUN_00147030(void) {
    if (DAT_0055f758[0] == 0) {
        DAT_0055f758[0] = igMetaEnum_Create(&DAT_004d6e30[0], &DAT_00487580[0], &DAT_004875a0[0], 8);
    }
    return DAT_0055f758[0];
}

int FUN_00147090(int arg0) {
    FUN_001471b0();
    return igMetaObject_CreateInstance(*(int *)0x55F760, arg0);
}

igMetaObject *igPsx2Controller_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Controller_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001471b0();
    return g_igPsx2Controller_metaObject[0];
}

int igPsx2Controller_GetVTable(void) {
    union U_147120 u;
    void **q8;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader(u.b);
    q8 = &u.p[8];
    u.w[0] = (int)(&DAT_00524d00[0]);
    *q8 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00524d00[0]);
    if (q8 != 0) {
        temp_a0 = *q8;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_001471b0(void)
{
    igMetaObject_RunStaticInit(igPsx2Controller_Register);
}

void igPsx2Controller_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Controller_metaObject,
        igController_Register,
        igController_GetPublishedMetaObject,
        thunk_igPsx2Controller_GetMetaObject,
        igPsx2Controller_className,
        0x70, /* instance size */
        igPsx2Controller_GetVTable,
        &igPsx2Controller_InitFields,
        0, /* extra callback item */
        g_igPsx2Controller_callbackList /* callback list */
    );
}

int FUN_00147240(void) {
    return DAT_0055f6b0[0];
}

void igPsx2Controller_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f760[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004875d0[0], 0x18);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 0x10);
    FUN_0030eda0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 2);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    *(int *)((char *)(temp_s2) + 56) = FUN_00145d40();
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6); q->f52 = 2; }
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7); q->f52 = 2; }
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    FUN_002dc7a0(temp_v0, &DAT_00487750[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_002d1870);
    FUN_0030eda0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC), 0xFFFF);
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE); q->f52 = 2; }
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF); q->f52 = 2; }
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12), 1);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x14));
    FUN_002dc7a0(temp_v0_2, &DAT_00487758[0]);
    *(int *)((char *)(temp_v0_2) + 52) = (int)(&FUN_00147030);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00487630[0], &DAT_00487690[0], &DAT_004876f0[0], temp_s1);
}

int FUN_00147430(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)arg0 + 8) + (arg1 * 4));
}

int FUN_00147450(void *arg0, int arg1) {
    int i;
    int *list;

    for (i = 0; i < 0x20; i++) {
        if (arg1 == *(int *)(*(int *)((char *)(arg0) + 8) + (i * 4))) {
            return i;
        }
    }
    return -1;
}

void FUN_001474a0(O *arg0, int arg1) {
    int n;
    int i;
    n = arg0->list->count;
    for (i = 0; i < n; i++) {
        arg0->list->items[i]->vX(arg1);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_26(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_mouseMotionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_27(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_mouseButtonDownFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_28(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_mouseButtonUpFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_29(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_windowMoveFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_30(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_windowResizeFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_31(igDefaultInterfaceManager *arg0, void **arg1) {
    bool var_a0;
    bool (*temp_v1)(void **);
    var_a0 = true;
    temp_v1 = (bool (*)(void **))(arg0->_windowCloseFunction);
    if (temp_v1 != 0) {
        var_a0 = temp_v1(arg1);
    }
    if (var_a0) {
        ((DW4VC_104_0 *)(arg1))->vX();
    }
}

void Gap__igDefaultInterfaceManager__vfunc_40(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_keyDownFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_41(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_keyUpFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_32(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerJoystickMotionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_33(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerButtonDownFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_34(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerButtonUpFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_35(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerButtonPressureFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_36(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_controllerConnectionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_37(igDefaultInterfaceManager *arg0, int arg1, int arg2) {
    int (*temp_v1)(int, int);

    temp_v1 = (int (*)(int, int))(arg0->_controllerDisconnectionFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_38(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerSliderFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void Gap__igDefaultInterfaceManager__vfunc_39(igDefaultInterfaceManager *arg0, int arg1, int arg2, int arg3) {
    int (*temp_v1)(int, int, int);

    temp_v1 = (int (*)(int, int, int))(arg0->_controllerPointOfViewFunction);
    if (temp_v1 != 0) {
        temp_v1(arg1, arg2, arg3);
    }
}

void FUN_00147840(struct A *arg0) {
    int n2; int j; L_147840 *l; int n1; int i; R *p;
    l = arg0->list;
    n1 = l->cnt;
    for (i = 0; i < n1; i++) {
        p = l->arr[i];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->cnt;
    for (j = 0; j < n2; j++) {
        l->arr[j] = 0;
    }
    l->cnt = 0;
    if (0 >= arg0->list->cnt) {
        List_Reserve(arg0->list, 0, 4);
    }
}

void FUN_00147930(S *arg0) {
    int n = arg0->list->count;
    int i;
    for (i = 0; i < n; i++) {
        arg0->list->data[i]->vX(arg0);
    }
}

void FUN_001479b0(igPsx2Controller *arg0) {
    int i;
    char *p = (char *)arg0;
    for (i = 0; i < 6; i++) {
        *(p + i + 91) = 0;
    }
    for (i = 0; i < 12; i++) {
        *(p + i + 97) = 0;
    }
    for (i = 0; i < 2; i++) {
        arg0->_x[i] = 0;
        arg0->_y[i] = 0;
        *(p + i + 76) = 0;
        *(p + i + 78) = 0;
    }
    arg0->_connected = 0;
    arg0->_buttonState = 0xFFFF;
    arg0->_hasPressure = 0;
    arg0->_phase = 0;
    arg0->_term_id = 0;
    arg0->_lockState = 1;
    arg0->_analogState = 1;
}

void Gap__igPsx2Controller__vfunc_11(int arg0) {
    Gap__Core__igObject__vfunc_09();
    FUN_001479b0((igPsx2Controller *)arg0);
}

void Gap__igPsx2Controller__vfunc_12(void *arg0) {
    int temp_a0;

    scePadPortClose(*(int *)((char *)arg0 + 64), *(int *)((char *)arg0 + 60));
    temp_a0 = *(int *)((char *)arg0 + 72);
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    Gap__Core__igObject__vfunc_10(arg0);
}

void Gap__igPsx2Controller__vfunc_31(void *arg0, int arg1, float *arg2, float *arg3) {
    int temp_a1;
    int idx;
    int temp_v1;
    temp_a1 = arg1 & 0xFFFF;
    if (temp_a1 < (int) *(unsigned short *)((char *)(arg0) + 28)) {
        idx = temp_a1 * 4;
        temp_v1 = idx + (int)arg0;
        *arg2 = *(float *)(temp_v1 + 36);
        *arg3 = *(float *)(temp_v1 + 44);
    }
}

/* matching construct: a small sweep of spellings */
extern "C" void Gap__igPsx2Controller__vfunc_23(igPsx2Controller *self, ControllerListener *listener) {
    int state;
    unsigned char analog;
    unsigned char lock;
    bool firstConnect;
    int id;

    state = FUN_00118390(self->_port, self->_slot);
    if (state == 0 || self->_userReset) {
        if (self->_connected || self->_userReset) {
            analog = self->_analogState;
            lock = self->_lockState;
            FUN_001479b0(self);
            self->_analogState = analog;
            self->_lockState = lock;
            if (listener) {
                listener->onReset(self->_attachedWindow, self);
            }
            self->_userReset = 0;
        }
        return;
    }
    switch (self->_phase) {
    case 0:
        if (state == 6 || state == 2) {
            self->_curr_id = FUN_00118770(self->_port, self->_slot, 1, 0);
            if (self->_curr_id) {
                id = FUN_00118770(self->_port, self->_slot, 2, 0);
                if (id > 0) {
                    self->_curr_id = id;
                }
                firstConnect = !self->_connected;
                self->_connected = 1;
                if (firstConnect && listener) {
                    listener->onConnect(self->_attachedWindow, self);
                    self->_reseting = 1;
                }
                if (self->_curr_id == 4 || self->_curr_id == 7) {
                    if (self->_reseting) {
                        self->_type = 1;
                        self->_phase = 1;
                    } else if (self->_curr_id == 4) {
                        self->_phase = 7;
                    } else if (self->_userResetAnalogOnly) {
                        self->_type = 6;
                        self->_phase = 7;
                    } else {
                        self->_type = 6;
                        self->_phase = 3;
                    }
                } else {
                    self->_reseting = 0;
                    self->_type = 7;
                    self->_phase = 7;
                }
            }
        }
        break;
    case 1:
        self->_reseting = 0;
        if (FUN_00118770(self->_port, self->_slot, 2, 0) == 0) {
            self->_analogState = 0;
        } else {
            scePadSetMainMode(self->_port, self->_slot, 1, self->_lockState ? 3 : 2);
            self->_analogState = 1;
        }
        self->_phase = 2;
        break;
    case 2:
        if (FUN_001184a8(self->_port, self->_slot) == 1) {
            self->_phase = 1;
        }
        if (FUN_001184a8(self->_port, self->_slot) == 0) {
            self->_phase = 0;
        }
        break;
    case 3:
        if (FUN_00118530(self->_port, self->_slot, -1, 0) == 0) {
            self->_phase = 7;
        } else {
            PadActAlign align = DAT_00487760;
            scePadSetActAlign(self->_port, self->_slot, align.data);
            self->_phase = 4;
        }
        break;
    case 4:
        if (FUN_001184a8(self->_port, self->_slot) == 1) {
            self->_phase = 3;
        }
        if (FUN_001184a8(self->_port, self->_slot) == 0) {
            self->_phase = 5;
        }
        break;
    case 5:
        if (FUN_00118c60(self->_port, self->_slot) == 0) {
            self->_hasPressure = 0;
            self->_phase = 7;
        } else {
            self->_hasPressure = 1;
            if (self->_usePressure) {
                scePadEnterPressMode(self->_port, self->_slot);
            } else {
                scePadExitPressMode(self->_port, self->_slot);
            }
            self->_phase = 6;
        }
        break;
    case 6:
        if (FUN_001184a8(self->_port, self->_slot) == 1) {
            self->_phase = 5;
        }
        if (FUN_001184a8(self->_port, self->_slot) == 0) {
            self->_phase = 7;
        }
        break;
    default:
        if (state == 6 || state == 2) {
            FUN_00148160(self, listener);
            if (self->_term_id != self->_curr_id) {
                if (self->_term_id == 7) {
                    self->_analogState = 1;
                    self->_phase = 0;
                } else if (self->_term_id == 4) {
                    self->_curr_id = self->_term_id;
                    self->_analogState = 0;
                }
                self->_phase = 0;
            }
        }
        break;
    }
}

void Gap__igPsx2Controller__vfunc_37(C *arg0, int arg1, float fparg0) {
    if ((arg1 >= 0) && (arg1 < 6)) {
        arg0->b91[arg1] = (unsigned char)(255.0f * fparg0);
        FUN_00118960(arg0->f64, arg0->f60, &arg0->b91[0]);
    }
}

int FUN_00147ff0(void *arg0, unsigned int arg1) {
    int var_a1;

    switch (arg1) {
    case 0:
        var_a1 = 5;
        break;
    case 1:
        var_a1 = 7;
        break;
    case 2:
        var_a1 = 4;
        break;
    case 3:
        var_a1 = 6;
        break;
    case 4:
        var_a1 = 0xC;
        break;
    case 5:
        var_a1 = 0xD;
        break;
    case 6:
        var_a1 = 0xE;
        break;
    case 7:
        var_a1 = 0xF;
        break;
    case 8:
        var_a1 = 0xA;
        break;
    case 9:
        var_a1 = 0xB;
        break;
    case 10:
        var_a1 = 8;
        break;
    default:
        var_a1 = 9;
        break;
    }
    if (*(unsigned char *)((char *)(arg0) + 12) != 0) {
        return FUN_00147430(arg0, var_a1);
    }
    return var_a1;
}

int FUN_001480a0(struct O_1480a0 *o, int a) {
    int v = o->f12 != 0 ? FUN_00147450(o, a) : a;
    unsigned t = v - 4;
    switch (t) {
    case 1: return 0;
    case 3: return 1;
    case 0: return 2;
    case 2: return 3;
    case 8: return 4;
    case 9: return 5;
    case 10: return 6;
    case 11: return 7;
    case 6: return 8;
    case 7: return 9;
    case 4: return 10;
    case 5: return 11;
    default: return -1;
    }
}

void Gap__igPsx2ControllerManager__vfunc_24(igPsx2ControllerManager *arg0, int arg1) {
    PropertyText *sp8C;
    void *al;
    char *s0;
    int s3;
    int s2;
    Al *al2;
    int s1;
    int v1;
    void *base;
    int mem;
    igObject *q;
    if (GPR_00554b18 == 0) {
        GPR_00554b18 = 1;
        arg0->_validControllerManager = 1;
        if (arg0->_loadIRXs != 0) {
            FUN_0032cf50(&DAT_004d7020[0], 1, 0, 0);
            FUN_0032cf50(&DAT_004d7030[0], 1, 0, 0);
        }
        FUN_00117c78(0);
        base = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            al = base;
        } else {
            al = Memory_GetAllocatorBySelector(DAT_00587060[0]);
        }
        sp8C = (PropertyText *)FUN_002b9500(al);
        if (FUN_00306770(DAT_00586dc8[0]->f56, 3, &DAT_004d7040[0], &sp8C, &DAT_004d7050[0], 0) != 0) {
            s0 = sp8C->chars;
            s0 = (s0 == 0) ? DAT_004c22f0[0] : s0;
            if (strcmp(s0, &DAT_004d6ce0[0]) == 0) {
                v1 = 0xFFFF;
                arg0->_multitap = v1;
            } else if (strcmp(s0, &DAT_004d6cc8[0]) == 0) {
                arg0->_multitap = 0;
            } else if (strncmp(s0, &DAT_004d7058[0], 4) == 0) {
                v1 = 2;
                if (s0[4] == 0x30) { v1 = 1; arg0->_multitap = v1; } else { arg0->_multitap = v1; }
            }
        }
        q = sp8C;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
        sp8C = 0;
        s3 = 0;
        if (arg0->_multitap != 0) {
            if (arg0->_loadIRXs != 0) {
                if (FUN_0032cf50(&DAT_004d7060[0], 1, 0, 0).ok()) {
                    FUN_00225300();
                    if (arg0->_multitap & 1) sceMtapPortOpen(0);
                    if (arg0->_multitap & 2) sceMtapPortOpen(1);
                }
            }
            s3 = 0;
        }
        s3 = 0;
        do {
            s1 = 0;
            { unsigned m = arg0->_multitap; s2 = !(m & (1u << s3)) ? 1 : 4; }
            for (; s1 < s2; s1++) {
                base = igObject_GetAllocator(arg0);
                if (GPR_00554c14 != 0) {
                    al2 = (Al *)base;
                } else {
                    al2 = (Al *)Memory_GetAllocatorBySelector(DAT_00587060[0]);
                }
                mem = al2->vX(0x100, 0x40);
                if (scePadPortOpen(s3, s1, mem) != 1) {
                    Memory_FreeBuffer(mem);
                } else {
                    igSmartPointer<igPsx2Controller> controller((igPsx2Controller *)FUN_00147090((int)igObject_GetAllocator(arg0)));
                    controller.get()->_port = s3;
                    controller.get()->_slot = s1;
                    ((Pd *)controller.get())->vX((s3 | (s1 * 2)) & 0xFFFF);
                    controller.get()->_dmaBuffer = mem;
                    ((Pe *)controller.get())->vX(arg1);
                    ObjectList_AppendRetained((int)(igObject *)arg0->_controllers, (int)controller.get());
                }
            }
            s3 += 1;
        } while (s3 < 2);
        q = sp8C;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
    }
}

void **FUN_001489a0(void **arg0, short arg1) {
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

/* slot 36 of igPsx2Controller: set the _attachedWindow reference (+32). Reference-counted
 * assignment: retain the new object, release the old one (destroying it when its 23-bit count
 * reaches zero), then store the new one. */
void Gap__igPsx2Controller__vfunc_36(igPsx2Controller *self, igObject *window) {
    igObject *previousWindow;
    if (window != 0) {
        window->_refCount = window->_refCount + 1;
    }
    previousWindow = (igObject *)(self->_attachedWindow);
    if (previousWindow != 0) {
        previousWindow->_refCount = previousWindow->_refCount - 1;
        if ((previousWindow->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousWindow);
        }
    }
    self->_attachedWindow = (int)window;
}

void Gap__igPsx2Controller__vfunc_33(void *arg0, short arg1) {
    *(short *)((char *)arg0 + 16) = arg1;
}

int Gap__igPsx2ControllerManager__vfunc_25(igPsx2ControllerManager *arg0) {
    int r;
    switch (arg0->_multitap) {
    case 0: r = 2; break;
    case 0xFFFF: r = 8; break;
    default: r = 5; break;
    }
    return r;
}

void Gap__igPsx2ControllerManager__vfunc_10(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 16) != 0) {
        GPR_00554b18 = 0;
    }
}

void Gap__igPsx2Window__vfunc_26(struct A_148b00 *arg0) {
    int *a1;
    int v1;
    int var_v0;
    struct R_148b00 *p;
    int *old;
    int *s1;

    arg0->f36 = -1;
    p = arg0->f24;
    if (p != 0) {
        p->rc = p->rc - 1;
        if ((p->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(p);
        }
    }
    arg0->f24 = 0;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    s1 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
    old = arg0->f32;
    if (old != 0) {
        a1 = old - 2;
        v1 = old[-1] - 1;
        old[-1] = v1;
        if (v1 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->f32 = s1;
    arg0->f40 = 0;
}

int Gap__igPsx2Window__vfunc_39(igPsx2Window *self, igObject *viewContext) {
    igObject *previous;
    if (viewContext != 0) {
        /* The NULL test is repeated around the retain; dropping it changes the bytes. */
        if (viewContext != 0) {
            viewContext->_refCount = viewContext->_refCount + 1;
        }
        previous = (igObject *)(self->_vc);
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(previous);
            }
        }
        self->_vc = (int)(viewContext);
        return 1;
    }
    return 0;
}

void Gap__igPsx2Window__vfunc_25(igPsx2WindowView *self)
{
    self->vfunc_22(self->_winName, self->_width, self->_height);
}

static inline void setWindowName(igPsx2Window *self, const char *name) {
    if (DAT_00586f20[0] == 0) {
        void *pool = (void *)FUN_002eb010(16);
        if (pool != 0) pool = (void *)StringPool_Construct(pool);
        DAT_00586f20[0] = (int)pool;
    }
    const char *interned = (const char *)StringPool_Intern(DAT_00586f20[0], name);
    int *old = (int *)self->_winName;
    if (old != 0) {
        int *header = old - 2;
        int refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) StringChunk_ReleaseHeader(*header, header);
    }
    self->_winName = (int)interned;
}

int Gap__igPsx2Window__vfunc_24(igPsx2Window *self, const char *name, int width, int height) {
    if (name == 0) {
        setWindowName(self, DAT_004d7070);
    } else {
        setWindowName(self, name);
    }
    self->_width = width;
    self->_height = height;
    if (self->_vc != 0) {
        self->_renderDestinationHandle = ((VisualContext *)self->_vc)->currentRenderDestination();
        if (self->_renderDestinationHandle == -1) {
            RenderDestinationDesc desc;
            desc.kind = 1;
            desc.width = width;
            desc.height = height;
            desc.bpp = self->_bpp;
            desc.alpha = self->_alpha;
            desc.bppDepth = self->_bppDepth;
            desc.clearDepth = 0.0f;
            desc.scale = 1.0f;
            self->_renderDestinationHandle = ((VisualContext *)self->_vc)->createRenderDestination(&desc);
        }
        int w;
        int h;
        ((VisualContext *)self->_vc)->getRenderDestinationSize(self->_renderDestinationHandle, &w, &h);
        self->_width = w;
        self->_height = h;
    } else {
        VisualContext *created = FUN_0014a000(igObject_GetAllocator(self));
        if (created != 0) created->_refCount = created->_refCount + 1;
        igRelease((igObject *)self->_vc);
        self->_vc = (int)created;
        VisualContext *vc = (VisualContext *)self->_vc;
        if (vc == 0) {
            printf(DAT_004d7080);
            return 0;
        }
        vc->_refCount = vc->_refCount - 1;
        if ((vc->_refCount & 0x7FFFFF) == 0) igObject_Destroy(vc);
        RenderDestinationDesc desc;
        desc.kind = 1;
        desc.width = width;
        desc.height = height;
        desc.bpp = self->_bpp;
        desc.alpha = self->_alpha;
        desc.bppDepth = self->_bppDepth;
        desc.clearDepth = 0.0f;
        desc.scale = 1.0f;
        self->_renderDestinationHandle = ((VisualContext *)self->_vc)->createRenderDestination(&desc);
    }
    ((VisualContext *)self->_vc)->beginWindow();
    self->_open = 1;
    return 1;
}

void Gap__igPsx2Window__vfunc_27(int *arg0, char *arg1) {
    int *old;
    int *hdr;
    int *s;
    int v;
    if ((arg1 != 0) && (*arg1 != 0)) {
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(0x10);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        s = StringPool_Intern(DAT_00586f20[0], arg1);
        old = (int *)arg0[8];
        if (old != 0) {
            hdr = old - 2;
            v = old[-1] - 1;
            old[-1] = v;
            if (v == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
        arg0[8] = (int)s;
    }
}

int Gap__igPsx2Window__vfunc_34(void *arg0, int dummy1, int arg2, int arg3, int arg4) {
    *(int *)((char *)(arg0) + 8) = arg2;
    *(int *)((char *)(arg0) + 12) = arg3;
    *(int *)((char *)(arg0) + 44) = arg4;
    return 1;
}

void Gap__igPsx2Window__vfunc_35(void *arg0, char *arg1, int *arg2, int *arg3, int *arg4) {
    *arg1 = 1;
    if (arg2 != 0) {
        *arg2 = *(int *)((char *)(arg0) + 8);
    }
    if (arg3 != 0) {
        *arg3 = *(int *)((char *)(arg0) + 12);
    }
    if (arg4 != 0) {
        *arg4 = *(int *)((char *)(arg0) + 44);
    }
}

int Gap__igPsx2Window__vfunc_22(void) {
    return DAT_0055f6c8[0];
}

int Gap__igPsx2Window__vfunc_28(void *arg0) {
    return *(int *)((char *)(arg0) + 32);
}

void Gap__igPsx2Window__vfunc_29(void) {

}

void Gap__igPsx2Window__vfunc_30(void *d0, int *arg1, int *arg2) {
    *arg1 = 0;
    *arg2 = 0;
}

void Gap__igPsx2Window__vfunc_31(void) {

}

void Gap__igPsx2Window__vfunc_32(void *d0, int *arg1, int *arg2) {
    *arg1 = 0x280;
    *arg2 = 0x1C0;
}

void Gap__igPsx2Window__vfunc_36(void) {

}

int Gap__igPsx2Window__vfunc_37(void) {
    return 1;
}

/* IgPsx2Window vtable slot 38, a plain getter that returns the reflected field _vc (the window's
 * visual context reference, igPsx2Window +24). */

int Gap__igPsx2Window__vfunc_38(igPsx2Window *self) {
    return self->_vc;
}

/* igPsx2Window vtable slot 42 (+0xa8): leaf that returns 0 and ignores the window, the PS2
 * backend's "nothing to report" answer for an igWindow virtual (igWindow serialises no fields). */
int Gap__igPsx2Window__vfunc_42(igPsx2Window *self) {
    return 0;
}

void Gap__igPsx2Window__vfunc_33(void *d0, int *arg1, int *arg2) {
    *arg1 = 0x280;
    *arg2 = 0x1C0;
}

void Gap__igPsx2Window__vfunc_40(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}

/* igPsx2Window vtable slot 41 (+0xa4): leaf that returns 0 and ignores the window, the PS2
 * backend's "nothing to report" answer for an igWindow virtual (igWindow serialises no fields). */
int Gap__igPsx2Window__vfunc_41(igPsx2Window *self) {
    return 0;
}

void Gap__igPsx2Window__vfunc_23(void) {

}

/* Reports whether the window is open: returns _open (+40). */

unsigned char Gap__igPsx2Window__vfunc_43(igPsx2Window *self) {
    return self->_open;
}

int Gap__igPsx2ControllerManager__vfunc_22(void)
{
    return (int)g_igPsx2ControllerManager_metaObject[0];
}

int Gap__igPsx2Controller__vfunc_22(void) {
    return DAT_0055f760[0];
}

int Gap__igPsx2Controller__vfunc_24(void *arg0) {
    return *(int *)((char *)(arg0) + 24);
}

void Gap__igPsx2Controller__vfunc_25(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 24) = arg1;
}

unsigned short Gap__igPsx2Controller__vfunc_26(void *arg0) {
    return *(int *)((char *)(arg0) + 28);
}

void Gap__igPsx2Controller__vfunc_27(void *arg0, short arg1) {
    *(short *)((char *)arg0 + 28) = arg1;
}

unsigned short Gap__igPsx2Controller__vfunc_32(void *arg0) {
    return *(int *)((char *)(arg0) + 16);
}

/* The field must be shifted as unsigned (srlv); (unsigned short) promotes to signed int, so the
 * (unsigned int) cast is needed or the compiler emits srav. */
int Gap__igPsx2Controller__vfunc_28(void *arg0, int arg1) {
    return (((unsigned int) * (unsigned short *)((char *)(arg0) + 68) >> arg1) & 1) == 0;
}

float Gap__igPsx2Controller__vfunc_29(O_149230 *arg0, int arg1) {
    int i;
    int t;
    unsigned v;
    long long d;
    unsigned char *p;
    float r;
    i = FUN_001480a0((O_1480a0 *)arg0, arg1);
    if (i >= 0) {
        p = (unsigned char *)(i + (int)arg0);
        v = p[97];
        r = (float)v / 255.0f;
    } else {
    t = arg0->vX(arg1);
    d = 0;
    if (t != 0) {
        d = (long long)0x3FF00000 << 0x20;
    }
    r = dptofp(d);
    }
    return r;
}

int Gap__igPsx2Controller__vfunc_30(void *arg0) {
    return ~*(unsigned short *)((char *)(arg0) + 68) & 0xFFFF;
}

/* Reports whether the controller is connected: returns _connected (+52). */

unsigned char Gap__igPsx2Controller__vfunc_34(igPsx2Controller *self) {
    return self->_connected;
}

/* IgPsx2Controller vtable slot 35, a plain getter that returns the reflected field _attachedWindow
 * (the window the controller is attached to, igPsx2Controller +32). */

int Gap__igPsx2Controller__vfunc_35(igPsx2Controller *self) {
    return self->_attachedWindow;
}

int FUN_00149320(void) {
    return DAT_0055f5e8[0];
}

void FUN_00149330(int a0) {
    ObjectList_AppendRetained(*(int *)((char *)a0 + 8));
}

int Gap__igDefaultInterfaceManager__vfunc_22(void) {
    return (int)g_igDefaultInterfaceManager_metaObject[0];
}

int FUN_00149350(void) {
    return DAT_0055f698[0];
}

int Gap__igControllerList__vfunc_22(void) {
    return (int)g_igControllerList_metaObject[0];
}

int Gap__igNonRefCountedObjectStack__vfunc_22(void) {
    return DAT_00562b78[0];
}

int Gap__igEventProducerList__vfunc_22(void) {
    return DAT_0055f5f8[0];
}

int Gap__igControllerList__vfunc_24(void) {
    return (int)g_igController_metaObject[0];
}

int Gap__igEventProducerList__vfunc_24(void) {
    return DAT_0055f600[0];
}

void Gap__igNonRefCountedObjectStack__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

