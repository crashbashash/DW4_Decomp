/* beModelCtrlNode2_GetVTable: builds a beModelCtrlNode2 on the stack and returns the word at the
 * runtime vtable-slot offset the meta object publishes (DAT_00586dc8[0] + 916), then destroys it.
 * Reflection accessor. Its exception table (one tag-0xa6 base action: igNode dtor 0x195a90 around
 * the igMatrix44f constructor) is reproduced by the inline constructors of igNode -> igTransform
 * -> beModelCtrlNode2 views. The leaf's inline destructor is emitted out of line by MWCC and was
 * dead-stripped by the retail linker: the `stripped` entry of this unit's row in
 * config/SLUS-20836/unit-objects.json. */
extern "C" {
extern int DAT_005284f0[4];                 /* igTransform vtable */
extern int DAT_00537f40[4];                 /* beModelCtrlNode2 vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beModelCtrlNode2_GetVTable(void);
}

/* igObject: ctor 0x2fef20 igObject_InitHeader (bound as an external) */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igMatrix44f: ctor 0x190380 igMatrix44f_SetIdentity */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _overrideAttrList (igObjectRefMetaField): dtor 0x13bfe0 */
struct OverrideAttrListField { int *p; OverrideAttrListField() { p = 0; } ~OverrideAttrListField(); };

/* stores a derived vtable before the class's first member constructor runs, as retail does */
struct igTransformVtable { igTransformVtable(int **slot) { *slot = DAT_005284f0; } };
struct ModelCtrlNode2Vtable { ModelCtrlNode2Vtable(int **slot) { *slot = DAT_00537f40; } };

/* igNode: inline ctor, out-of-line dtor 0x195a90 */
struct igNodeView : igObjectView {
    int name, bound, parentList, flags, handle, childList;
    igNodeView() { name = 0; bound = 0; parentList = 0; childList = 0; }
    ~igNodeView();
};
/* igTransform: inline ctor, out-of-line dtor 0x1962d0 */
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
