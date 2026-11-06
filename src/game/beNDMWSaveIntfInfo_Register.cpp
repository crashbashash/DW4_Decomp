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
extern igMetaObject *g_beNDMWSaveIntfInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWSaveIntfInfo_GetMetaObject(void);
extern const char beNDMWSaveIntfInfo_className[];
int beNDMWSaveIntfInfo_GetVTable(void);
void *beNDMWSaveIntfInfo_Register(void);
}

void *beNDMWSaveIntfInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveIntfInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWSaveIntfInfo_GetMetaObject,
        beNDMWSaveIntfInfo_className,
        0x1c, /* instance size */
        beNDMWSaveIntfInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
