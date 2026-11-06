struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beWaterPlainInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beWaterPlainInfo_GetMetaObject(void);
extern const char beWaterPlainInfo_className[];
int beWaterPlainInfo_GetVTable(void);
void *beWaterPlainInfo_Register(void);
}

void *beWaterPlainInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterPlainInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beWaterPlainInfo_GetMetaObject,
        beWaterPlainInfo_className,
        0x1c, /* instance size */
        beWaterPlainInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
