/* Reflection accessor: builds a beCameraCtrl on the stack, returns the word at the runtime vtable-
 * slot offset the meta object publishes (+916), then destroys it. */
extern "C" {
extern int DAT_0053a210[4];                 /* beCameraCtrl vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beCameraCtrl_GetVTable(void);
}

/* igObject, constructed by igObject_InitHeader. */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igMatrix44f, constructed by igMatrix44f_SetIdentity. */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _cameraMode (igObjectRefMetaField). */
struct CameraModeField { int *p; CameraModeField() { p = 0; } ~CameraModeField(); };

/* The unnamed controller base shared by beCameraCtrl, beLayerCtl, beFont, beMovie and the beNDMW
 * controllers (fields _name.._isUpdateRun). */
struct ControllerBaseView : igObjectView {
    int name, insight, system, messenger, infoList;
    unsigned char isUpdateRun;
    ControllerBaseView() { name = 0; infoList = 0; }
    ~ControllerBaseView();
};
/* Stores the derived vtable before the first member constructor runs. */
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
