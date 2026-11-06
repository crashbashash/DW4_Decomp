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
extern igMetaObject *g_beNDMWItemImportant_metaObject[];
void *beNDMWItemBase_Register(void);
igMetaObject *beNDMWItemBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWItemImportant_GetMetaObject(void);
extern const char beNDMWItemImportant_className[];
int beNDMWItemImportant_GetVTable(void);
void *beNDMWItemImportant_Register(void);
}

void *beNDMWItemImportant_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemImportant_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemImportant_GetMetaObject,
        beNDMWItemImportant_className,
        0x14, /* instance size */
        beNDMWItemImportant_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
