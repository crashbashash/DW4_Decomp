/* beCopyModelCtrl2_GetVTable: builds a beCopyModelCtrl2 on the stack and returns the word at the
 * runtime vtable-slot offset the meta object publishes (DAT_00586dc8[0] + 916), then destroys it.
 * Reflection accessor. Its exception table (one tag-0xa6 base action: igNode dtor 0x195a90 around
 * the igMatrix44f constructor) is reproduced by the inline constructors of igNode -> igTransform
 * -> beCopyModelCtrl2 views. The leaf's inline destructor is emitted out of line by MWCC and was
 * dead-stripped by the retail linker: the `stripped` entry of this unit's row in
 * config/SLUS-20836/unit-objects.json. */
extern "C" {
extern int DAT_005284f0[4];                 /* igTransform vtable */
extern int DAT_00534bd0[4];                 /* beCopyModelCtrl2 vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beCopyModelCtrl2_GetVTable(void);
}

/* igObject: ctor 0x2fef20 igObject_InitHeader (bound as an external) */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igMatrix44f: ctor 0x190380 igMatrix44f_SetIdentity */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _srcNode (igObjectRefMetaField): dtor 0x34c1b0 */
struct SrcNodeField { int *p; SrcNodeField() { p = 0; } ~SrcNodeField(); };

/* stores a derived vtable before the class's first member constructor runs, as retail does */
struct igTransformVtable { igTransformVtable(int **slot) { *slot = DAT_005284f0; } };
struct CopyModelCtrl2Vtable { CopyModelCtrl2Vtable(int **slot) { *slot = DAT_00534bd0; } };

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
struct CopyModelCtrl2View : igTransformView, CopyModelCtrl2Vtable {
    SrcNodeField srcNode;         /* +108 _srcNode */
    CopyModelCtrl2View() : CopyModelCtrl2Vtable(&vtable) { }
    ~CopyModelCtrl2View() { vtable = DAT_00534bd0; }
};

int beCopyModelCtrl2_GetVTable(void) {
    CopyModelCtrl2View copy;
    return *(int *)((char *)&copy + *(int *)((char *)DAT_00586dc8[0] + 916));
}
