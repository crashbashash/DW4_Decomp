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
extern igMetaObject *g_beLayerInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beLayerInfoRam_GetMetaObject(void);
extern const char beLayerInfoRam_className[];
int beLayerInfoRam_GetVTable(void);
void *beLayerInfoRam_Register(void);
}

void *beLayerInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLayerInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beLayerInfoRam_GetMetaObject,
        beLayerInfoRam_className,
        0x2c, /* instance size */
        beLayerInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
