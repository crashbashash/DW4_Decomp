/* Reflection accessor: builds a beModelCtrlNode2 on the stack, returns the word at the runtime
 * vtable-slot offset the meta object publishes (+916), then destroys it. */
extern "C" {
extern int DAT_005284f0[4];                 /* igTransform vtable */
extern int DAT_00537f40[4];                 /* beModelCtrlNode2 vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beModelCtrlNode2_GetVTable(void);
}

/* igObject, constructed by igObject_InitHeader. */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igMatrix44f, constructed by igMatrix44f_SetIdentity. */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _overrideAttrList (igObjectRefMetaField). */
struct OverrideAttrListField { int *p; OverrideAttrListField() { p = 0; } ~OverrideAttrListField(); };

/* Stores a derived vtable before the class's first member constructor runs. */
struct igTransformVtable { igTransformVtable(int **slot) { *slot = DAT_005284f0; } };
struct ModelCtrlNode2Vtable { ModelCtrlNode2Vtable(int **slot) { *slot = DAT_00537f40; } };

struct igNodeView : igObjectView {
    int name, bound, parentList, flags, handle, childList;
    igNodeView() { name = 0; bound = 0; parentList = 0; childList = 0; }
    ~igNodeView();
};
struct igTransformView : igNodeView, igTransformVtable {
    igMatrix44fView m;                      /* +32 _m */
    int target, mvm, transformInput;        /* +96 */
    igTransformView() : igTransformVtable(&vtable) { mvm = 0; transformInput = 0; }
    ~igTransformView();
};
struct ModelCtrlNode2View : igTransformView, ModelCtrlNode2Vtable {
    int pad108;
    long long time;                         /* +112 _time */
    float timeScale;                        /* +120 _timeScale */
    long long timeBias;                     /* +128 _timeBias */
    OverrideAttrListField overrideAttrList;  /* +136 _overrideAttrList */
    ModelCtrlNode2View() : ModelCtrlNode2Vtable(&vtable) { }
    ~ModelCtrlNode2View() { vtable = DAT_00537f40; }
};

int beModelCtrlNode2_GetVTable(void) {
    ModelCtrlNode2View node;
    return *(int *)((char *)&node + *(int *)((char *)DAT_00586dc8[0] + 916));
}
