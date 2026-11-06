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
extern igMetaObject *g_beStaticInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beStaticInfo_GetMetaObject(void);
extern const char beStaticInfo_className[];
int beStaticInfo_GetVTable(void);
void *beStaticInfo_Register(void);
}

void *beStaticInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beStaticInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beStaticInfo_GetMetaObject,
        beStaticInfo_className,
        0x1c, /* instance size */
        beStaticInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
