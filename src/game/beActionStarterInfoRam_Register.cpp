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
extern igMetaObject *g_beActionStarterInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beActionStarterInfoRam_GetMetaObject(void);
extern const char beActionStarterInfoRam_className[];
int beActionStarterInfoRam_GetVTable(void);
void *beActionStarterInfoRam_Register(void);
}

void *beActionStarterInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarterInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beActionStarterInfoRam_GetMetaObject,
        beActionStarterInfoRam_className,
        0x2c, /* instance size */
        beActionStarterInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
