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
extern igMetaObject *g_beWaterPlain_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beWaterPlain_GetMetaObject(void);
extern const char beWaterPlain_className[];
int beWaterPlain_GetVTable(void);
void *beWaterPlain_Register(void);
}

void *beWaterPlain_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterPlain_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beWaterPlain_GetMetaObject,
        beWaterPlain_className,
        0x20, /* instance size */
        beWaterPlain_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
