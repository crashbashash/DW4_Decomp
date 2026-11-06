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
extern igMetaObject *g_beGeneraterInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beGeneraterInfoRam_GetMetaObject(void);
extern const char beGeneraterInfoRam_className[];
int beGeneraterInfoRam_GetVTable(void);
void beGeneraterInfoRam_InitFields(void);
extern char g_beGeneraterInfoRam_callbackList[];
void *beGeneraterInfoRam_Register(void);
}

void *beGeneraterInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beGeneraterInfoRam_GetMetaObject,
        beGeneraterInfoRam_className,
        0x30, /* instance size */
        beGeneraterInfoRam_GetVTable,
        beGeneraterInfoRam_InitFields,
        0, /* extra callback item */
        g_beGeneraterInfoRam_callbackList /* callback list */
    );
}
