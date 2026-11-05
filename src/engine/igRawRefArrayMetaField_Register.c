/* 0x002bbed0 igRawRefArrayMetaField_Register: registers class igRawRefArrayMetaField with the object system, derived from igRawRefMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRawRefMetaField_Register[];
extern char igRawRefArrayMetaField_GetVTable[];
extern char thunk_igRawRefArrayMetaField_GetMetaObject[];
extern char igRawRefMetaField_GetPublishedMetaObject_002bbf60[];
extern char g_igRawRefArrayMetaField_callbackList_004bf988[];
extern char s_igRawRefArrayMetaField_className_004f62b0[];
extern char g_igRawRefArrayMetaField_metaObject_00585a90[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igRawRefArrayMetaField_InitFields();

void igRawRefArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRawRefArrayMetaField_metaObject_00585a90,      /* published MetaObject slot */
        igRawRefMetaField_Register,                        /* base class registrar */
        igRawRefMetaField_GetPublishedMetaObject_002bbf60, /* base class MetaObject accessor */
        thunk_igRawRefArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igRawRefArrayMetaField_className_004f62b0,       /* class name */
        0x3C,                                              /* instance size */
        igRawRefArrayMetaField_GetVTable,                  /* vtable getter */
        &igRawRefArrayMetaField_InitFields,                /* field adder */
        0,                                                 /* extra callback item */
        g_igRawRefArrayMetaField_callbackList_004bf988     /* callback list */
    );
}
