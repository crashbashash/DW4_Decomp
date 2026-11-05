/* 0x00134e60 igParticleAttr_Register: registers class igParticleAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igParticleAttr_GetVTable[];
extern char thunk_igParticleAttr_GetMetaObject[];
extern char g_igParticleAttr_callbackList_00486150[];
extern char s_igParticleAttr_className_004d52a8[];
extern char g_igParticleAttr_metaObject_0055ef80[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igParticleAttr_InitFields();

void igParticleAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igParticleAttr_metaObject_0055ef80,              /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igParticleAttr_GetMetaObject,                /* own MetaObject accessor (stored at +0x54) */
        s_igParticleAttr_className_004d52a8,               /* class name */
        0x30,                                              /* instance size */
        igParticleAttr_GetVTable,                          /* vtable getter */
        &igParticleAttr_InitFields,                        /* field adder */
        0,                                                 /* extra callback item */
        g_igParticleAttr_callbackList_00486150             /* callback list */
    );
}
