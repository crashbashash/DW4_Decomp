/* 0x0045e840 igActorManagerParams_Register: registers class igActorManagerParams with the object system, derived from igModel.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igActorManagerParams_GetVTable[];
extern char thunk_igActorManagerParams_GetMetaObject[];
extern char igActorManagerParams_className[];
extern char g_igActorManagerParams_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igActorManagerParams_InitFields();

void igActorManagerParams_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igActorManagerParams_metaObject, /* published MetaObject slot */
        igModel_Register,                           /* base class registrar */
        igModel_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igActorManagerParams_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igActorManagerParams_className,  /* class name */
        0x10,                                       /* instance size */
        igActorManagerParams_GetVTable,             /* vtable getter */
        &igActorManagerParams_InitFields,           /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
