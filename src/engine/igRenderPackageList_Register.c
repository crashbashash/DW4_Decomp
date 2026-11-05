/* 0x001978b0 igRenderPackageList_Register: registers class igRenderPackageList with the object system, derived from igNonRefCountedObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectList_GetPublishedMetaObject_0013aeb0[];
extern char igRenderPackageList_GetVTable[];
extern char thunk_igRenderPackageList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igRenderPackageList_callbackList_0048b4b0[];
extern char s_igRenderPackageList_className_004e19a0[];
extern char g_igRenderPackageList_metaObject_00561440[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igRenderPackageList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRenderPackageList_metaObject_00561440,                 /* published MetaObject slot */
        igNonRefCountedObjectList_Register,                        /* base class registrar */
        igNonRefCountedObjectList_GetPublishedMetaObject_0013aeb0, /* base class MetaObject accessor */
        thunk_igRenderPackageList_GetMetaObject,                   /* own MetaObject accessor (stored at +0x54) */
        s_igRenderPackageList_className_004e19a0,                  /* class name */
        0x14,                                                      /* instance size */
        igRenderPackageList_GetVTable,                             /* vtable getter */
        0,                                                         /* field adder */
        0,                                                         /* extra callback item */
        g_igRenderPackageList_callbackList_0048b4b0                /* callback list */
    );
}
