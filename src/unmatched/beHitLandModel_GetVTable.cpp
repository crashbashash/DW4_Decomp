extern "C" {
extern int DAT_0053a810[4];                 /* beHitLandModel vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beHitLandModel_GetVTable(void);
}

struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
struct igMatrix44fView { float m[16]; igMatrix44fView(); };

struct HitLandOrderField { int *p; HitLandOrderField() { p = 0; } ~HitLandOrderField(); };
struct HitTraversalField { int *p; HitTraversalField() { p = 0; } ~HitTraversalField(); };
struct HitLandProbeField { int *p; HitLandProbeField() { p = 0; } ~HitLandProbeField(); };

struct ControllerBaseView : igObjectView {
    int name, insight, system, messenger, infoList;
    unsigned char isUpdateRun;
    ControllerBaseView() { name = 0; infoList = 0; }
    ~ControllerBaseView();
};
struct HitLandModelVtable { HitLandModelVtable(int **slot) { *slot = DAT_0053a810; } };

struct HitLandModelView : ControllerBaseView, HitLandModelVtable {
    HitLandOrderField order;                /* +32 _order */
    HitTraversalField hitTraversal;         /* +36 _hitTraversal */
    HitLandProbeField probe;                /* +40 _probe */
    unsigned char isHitWall;                /* +44 */
    igMatrix44fView mat90;                  /* +48 _mat90 */
    HitLandModelView() : HitLandModelVtable(&vtable) { }
    ~HitLandModelView() { vtable = DAT_0053a810; }
};

int beHitLandModel_GetVTable(void) {
    HitLandModelView model;
    return *(int *)((char *)&model + *(int *)((char *)DAT_00586dc8[0] + 916));
}
