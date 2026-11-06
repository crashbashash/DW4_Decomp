/* Reflection accessor: builds a beCopyModelCtrl2 on the stack, returns the word at the runtime
 * vtable-slot offset the meta object publishes (+916), then destroys it. */
extern "C" {
extern int DAT_005284f0[4];                 /* igTransform vtable */
extern int DAT_00534bd0[4];                 /* beCopyModelCtrl2 vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beCopyModelCtrl2_GetVTable(void);
}

/* igObject, constructed by igObject_InitHeader. */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igMatrix44f, constructed by igMatrix44f_SetIdentity. */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _srcNode (igObjectRefMetaField). */
struct SrcNodeField { int *p; SrcNodeField() { p = 0; } ~SrcNodeField(); };

/* Stores a derived vtable before the class's first member constructor runs. */
struct igTransformVtable { igTransformVtable(int **slot) { *slot = DAT_005284f0; } };
struct CopyModelCtrl2Vtable { CopyModelCtrl2Vtable(int **slot) { *slot = DAT_00534bd0; } };

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
struct CopyModelCtrl2View : igTransformView, CopyModelCtrl2Vtable {
    SrcNodeField srcNode;         /* +108 _srcNode */
    CopyModelCtrl2View() : CopyModelCtrl2Vtable(&vtable) { }
    ~CopyModelCtrl2View() { vtable = DAT_00534bd0; }
};

int beCopyModelCtrl2_GetVTable(void) {
    CopyModelCtrl2View copy;
    return *(int *)((char *)&copy + *(int *)((char *)DAT_00586dc8[0] + 916));
}
