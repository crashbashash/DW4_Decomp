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
extern igMetaObject *g_beWaterPlainInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beWaterPlainInfoRam_GetMetaObject(void);
extern const char beWaterPlainInfoRam_className[];
int beWaterPlainInfoRam_GetVTable(void);
void beWaterPlainInfoRam_InitFields(void);
extern char g_beWaterPlainInfoRam_callbackList[];
void *beWaterPlainInfoRam_Register(void);
}

void *beWaterPlainInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWaterPlainInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beWaterPlainInfoRam_GetMetaObject,
        beWaterPlainInfoRam_className,
        0xb8, /* instance size */
        beWaterPlainInfoRam_GetVTable,
        beWaterPlainInfoRam_InitFields,
        0, /* extra callback item */
        g_beWaterPlainInfoRam_callbackList /* callback list */
    );
}
