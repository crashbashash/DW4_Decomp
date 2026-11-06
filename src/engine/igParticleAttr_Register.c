extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igParticleAttr_GetVTable[];
extern char thunk_igParticleAttr_GetMetaObject[];
extern char g_igParticleAttr_callbackList[];
extern char igParticleAttr_className[];
extern char g_igParticleAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igParticleAttr_InitFields();

void igParticleAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igParticleAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igParticleAttr_GetMetaObject,
        igParticleAttr_className,
        0x30, /* instance size */
        igParticleAttr_GetVTable,
        &igParticleAttr_InitFields,
        0, /* extra callback item */
        g_igParticleAttr_callbackList /* callback list */
    );
}
