/* 0x00367ea0 beCopyTransform_GetVTable: builds a beCopyTransform on the stack and returns the word at the
 * runtime vtable-slot offset the meta object publishes (DAT_00586dc8[0] + 916), then destroys it.
 * Reflection accessor. Its exception table (one tag-0xa6 base action: igNode dtor 0x195a90 around the
 * igMatrix44f constructor) is reproduced by the inline constructors of igNode -> igTransform -> beCopyTransform
 * views (finding #3886). The leaf's inline destructor is emitted out of line by MWCC and was dead-stripped by
 * the retail linker: the `stripped` entry of this unit's row in config/SLUS-20836/unit-objects.json (finding #3888). */
extern "C" {
extern int DAT_005284f0[4];                 /* igTransform vtable */
extern int DAT_00534c70[4];                 /* beCopyTransform vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beCopyTransform_GetVTable(void);
}

/* igObject: ctor 0x2fef20 igObject_InitHeader (bound as an external) */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igMatrix44f: ctor 0x190380 igMatrix44f_SetIdentity */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _srcTransform (igObjectRefMetaField): dtor 0x1a7580 */
struct SrcTransformField { int *p; SrcTransformField() { p = 0; } ~SrcTransformField(); };

/* stores a derived vtable before the class's first member constructor runs, as retail does */
struct igTransformVtable { igTransformVtable(int **slot) { *slot = DAT_005284f0; } };
struct CopyTransformVtable { CopyTransformVtable(int **slot) { *slot = DAT_00534c70; } };

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
struct CopyTransformView : igTransformView, CopyTransformVtable {
    SrcTransformField srcTransform;         /* +108 _srcTransform */
    CopyTransformView() : CopyTransformVtable(&vtable) { }
    ~CopyTransformView() { vtable = DAT_00534c70; }
};

int beCopyTransform_GetVTable(void) {
    CopyTransformView transform;
    return *(int *)((char *)&transform + *(int *)((char *)DAT_00586dc8[0] + 916));
}
