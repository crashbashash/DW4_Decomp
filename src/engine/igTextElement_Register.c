/* 0x0044bfa0 igTextElement_Register: registers class igTextElement with the object system, derived from igGeometryElement.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTextElement_GetVTable[];
extern char thunk_igTextElement_GetMetaObject[];
extern char igGeometryElement_GetPublishedMetaObject[];
extern char igGeometryElement_Register[];
extern char g_igTextElement_callbackList[];
extern char igTextElement_className[];
extern char g_igTextElement_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igTextElement_InitFields();

void igTextElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextElement_metaObject,               /* published MetaObject slot */
        igGeometryElement_Register,                        /* base class registrar */
        igGeometryElement_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTextElement_GetMetaObject,                 /* own MetaObject accessor (stored at +0x54) */
        igTextElement_className,                /* class name */
        0x38,                                              /* instance size */
        igTextElement_GetVTable,                           /* vtable getter */
        &igTextElement_InitFields,                         /* field adder */
        0,                                                 /* extra callback item */
        g_igTextElement_callbackList              /* callback list */
    );
}
