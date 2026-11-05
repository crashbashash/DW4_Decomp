/* 0x0019ae20 igSegment_Register: registers class igSegment with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igSegment_GetVTable[];
extern char thunk_igSegment_GetMetaObject[];
extern char igGroup_Register[];
extern char s_igSegment_className_004e2008[];
extern char g_igSegment_metaObject_005615d8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igSegment_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSegment_metaObject_005615d8,         /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0, /* base class MetaObject accessor */
        thunk_igSegment_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igSegment_className_004e2008,          /* class name */
        0x20,                                    /* instance size */
        igSegment_GetVTable,                     /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
