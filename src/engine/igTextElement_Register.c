/* 0x0044bfa0 igTextElement_Register: registers class igTextElement with the object system, derived from igGeometryElement.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTextElement_GetVTable[];
extern char thunk_igTextElement_GetMetaObject[];
extern char igGeometryElement_GetPublishedMetaObject_0044c030[];
extern char igGeometryElement_Register[];
extern char g_igTextElement_callbackList_004cff18[];
extern char s_igTextElement_className_0051dd58[];
extern char g_igTextElement_metaObject_0058c1d0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igTextElement_InitFields();

void igTextElement_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextElement_metaObject_0058c1d0,               /* published MetaObject slot */
        igGeometryElement_Register,                        /* base class registrar */
        igGeometryElement_GetPublishedMetaObject_0044c030, /* base class MetaObject accessor */
        thunk_igTextElement_GetMetaObject,                 /* own MetaObject accessor (stored at +0x54) */
        s_igTextElement_className_0051dd58,                /* class name */
        0x38,                                              /* instance size */
        igTextElement_GetVTable,                           /* vtable getter */
        &igTextElement_InitFields,                         /* field adder */
        0,                                                 /* extra callback item */
        g_igTextElement_callbackList_004cff18              /* callback list */
    );
}
