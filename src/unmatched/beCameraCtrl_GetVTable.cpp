/* beCameraCtrl_GetVTable: builds a beCameraCtrl on the stack and returns the word at the runtime
 * vtable-slot offset the meta object publishes (DAT_00586dc8[0] + 916), then destroys it.
 * Reflection accessor. Its exception table (around the two igMatrix44f constructors: tag-0x27
 * member _cameraMode, dtor 0x3699a0, then the tag-0xa6 base, dtor 0x33f5e0) is reproduced by the
 * inline constructor of a derived view whose base and member have out-of-line destructors. The
 * view's inline destructor is emitted out of line by MWCC and was dead-stripped by the retail
 * linker: the `stripped` entry of this unit's row in config/SLUS-20836/unit-objects.json. */
extern "C" {
extern int DAT_0053a210[4];                 /* beCameraCtrl vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beCameraCtrl_GetVTable(void);
}

/* igObject: ctor 0x2fef20 igObject_InitHeader (bound as an external) */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igMatrix44f: ctor 0x190380 igMatrix44f_SetIdentity */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _cameraMode (igObjectRefMetaField): dtor 0x3699a0 */
struct CameraModeField { int *p; CameraModeField() { p = 0; } ~CameraModeField(); };

/* The unnamed controller base shared by beCameraCtrl, beLayerCtl, beFont, beMovie and the beNDMW controllers
 * (fields _name.._isUpdateRun): inline ctor, out-of-line dtor 0x33f5e0. */
struct ControllerBaseView : igObjectView {
    int name, insight, system, messenger, infoList;
    unsigned char isUpdateRun;
    ControllerBaseView() { name = 0; infoList = 0; }
    ~ControllerBaseView();
};
/* stores the derived vtable before the first member constructor runs, as retail does */
struct CameraCtrlVtable { CameraCtrlVtable(int **slot) { *slot = DAT_0053a210; } };

/* matching construct: hand-written view of beCameraCtrl (see beNDMWMdlPlayerInfoWork_GetVTable) */
struct CameraCtrlView : ControllerBaseView, CameraCtrlVtable {
    int viewerMang, viewerPara;             /* +32 */
    CameraModeField cameraMode;             /* +40 _cameraMode */
    float avgPos[3], savePos[3];            /* +44 */
    unsigned char isPosChange;              /* +68 */
    float cameraNowFrame;                   /* +72 */
    int cameraNow, cameraOld;               /* +76 */
    igMatrix44fView eyeMatrix;              /* +84 _eyeMatrix */
    igMatrix44fView intMatrix;              /* +148 _intMatrix */
    float debugZoom;                        /* +212 */
    unsigned char isFirst;                  /* +216 */
    CameraCtrlView() : CameraCtrlVtable(&vtable) { }
    ~CameraCtrlView() { vtable = DAT_0053a210; }
};

int beCameraCtrl_GetVTable(void) {
    CameraCtrlView camera;
    return *(int *)((char *)&camera + *(int *)((char *)DAT_00586dc8[0] + 916));
}
