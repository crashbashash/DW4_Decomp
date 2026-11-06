struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
void *igMetaObject_RegisterClass(
        int abstractState,
        igMetaObject **slot,
        void *(*baseRegister)(void),
        igMetaObject *(*baseMetaObject)(void),
        igMetaObject *(*getMetaObject)(void),
        const char *className,
        int instanceSize,
        int (*getVTable)(void),
        void (*initFields)(void),
        void (*callbackItem)(void),
        void *callbackList);
extern igMetaObject *g_beNDMWItemRevisionBase_metaObject[];
void *beNDMWItemBase_Register(void);
igMetaObject *beNDMWItemBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWItemRevisionBase_GetMetaObject(void);
extern const char beNDMWItemRevisionBase_className[];
void beNDMWItemRevisionBase_InitFields(void);
void *beNDMWItemRevisionBase_Register(void);
}

void *beNDMWItemRevisionBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWItemRevisionBase_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemRevisionBase_GetMetaObject,
        beNDMWItemRevisionBase_className,
        0x18, /* instance size */
        0,
        beNDMWItemRevisionBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
