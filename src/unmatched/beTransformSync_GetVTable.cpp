/* Reflection accessor: builds a beTransformSync on the stack, returns the word at the runtime
 * vtable-slot offset the meta object publishes (+916), then destroys it. */
extern "C" {
extern int DAT_005284f0[4];                 /* igTransform vtable */
extern int DAT_005397d0[4];                 /* beTransformSync vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beTransformSync_GetVTable(void);
}

/* igObject, constructed by igObject_InitHeader. */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* igMatrix44f, constructed by igMatrix44f_SetIdentity. */
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
/* _syncTransformList (igObjectRefMetaField). */
struct SyncTransformListField { int *p; SyncTransformListField() { p = 0; } ~SyncTransformListField(); };

/* Stores a derived vtable before the class's first member constructor runs. */
struct igTransformVtable { igTransformVtable(int **slot) { *slot = DAT_005284f0; } };
struct TransformSyncVtable { TransformSyncVtable(int **slot) { *slot = DAT_005397d0; } };

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
struct TransformSyncView : igTransformView, TransformSyncVtable {
    SyncTransformListField syncTransformList;         /* +108 _syncTransformList */
    TransformSyncView() : TransformSyncVtable(&vtable) { }
    ~TransformSyncView() { vtable = DAT_005397d0; }
};

int beTransformSync_GetVTable(void) {
    TransformSyncView transform;
    return *(int *)((char *)&transform + *(int *)((char *)DAT_00586dc8[0] + 916));
}
