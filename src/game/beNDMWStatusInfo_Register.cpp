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
extern igMetaObject *g_beNDMWStatusInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusInfo_GetMetaObject(void);
extern const char beNDMWStatusInfo_className[];
int beNDMWStatusInfo_GetVTable(void);
void *beNDMWStatusInfo_Register(void);
}

void *beNDMWStatusInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWStatusInfo_GetMetaObject,
        beNDMWStatusInfo_className,
        0x1c, /* instance size */
        beNDMWStatusInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
