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
extern igMetaObject *g_beNDMWItemInstant_metaObject[];
void *beNDMWItemBase_Register(void);
igMetaObject *beNDMWItemBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWItemInstant_GetMetaObject(void);
extern const char beNDMWItemInstant_className[];
int beNDMWItemInstant_GetVTable(void);
void beNDMWItemInstant_InitFields(void);
void *beNDMWItemInstant_Register(void);
}

void *beNDMWItemInstant_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemInstant_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemInstant_GetMetaObject,
        beNDMWItemInstant_className,
        0x18, /* instance size */
        beNDMWItemInstant_GetVTable,
        beNDMWItemInstant_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
