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
extern igMetaObject *g_beNDMWItemWaza_metaObject[];
void *beNDMWItemBase_Register(void);
igMetaObject *beNDMWItemBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWItemWaza_GetMetaObject(void);
extern const char beNDMWItemWaza_className[];
int beNDMWItemWaza_GetVTable(void);
void beNDMWItemWaza_InitFields(void);
void *beNDMWItemWaza_Register(void);
}

void *beNDMWItemWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemWaza_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemWaza_GetMetaObject,
        beNDMWItemWaza_className,
        0x18, /* instance size */
        beNDMWItemWaza_GetVTable,
        beNDMWItemWaza_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
