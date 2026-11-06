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
extern igMetaObject *g_beNDMWTitle2Info_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWTitle2Info_GetMetaObject(void);
extern const char beNDMWTitle2Info_className[];
int beNDMWTitle2Info_GetVTable(void);
void *beNDMWTitle2Info_Register(void);
}

void *beNDMWTitle2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWTitle2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWTitle2Info_GetMetaObject,
        beNDMWTitle2Info_className,
        0x1c, /* instance size */
        beNDMWTitle2Info_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
