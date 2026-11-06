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
extern igMetaObject *g_beNDMWItemRevisionPocketBase_metaObject[];
void *beNDMWItemRevisionBase_Register(void);
igMetaObject *beNDMWItemRevisionBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWItemRevisionPocketBase_GetMetaObject(void);
extern const char beNDMWItemRevisionPocketBase_className[];
void beNDMWItemRevisionPocketBase_InitFields(void);
void *beNDMWItemRevisionPocketBase_Register(void);
}

void *beNDMWItemRevisionPocketBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWItemRevisionPocketBase_metaObject,
        beNDMWItemRevisionBase_Register,
        beNDMWItemRevisionBase_GetPublishedMetaObject,
        beNDMWItemRevisionPocketBase_GetMetaObject,
        beNDMWItemRevisionPocketBase_className,
        0x1c, /* instance size */
        0,
        beNDMWItemRevisionPocketBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
