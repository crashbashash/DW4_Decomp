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
extern igMetaObject *g_beNumberCtrlInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beNumberCtrlInfoRam_GetMetaObject(void);
extern const char beNumberCtrlInfoRam_className[];
int beNumberCtrlInfoRam_GetVTable(void);
void beNumberCtrlInfoRam_InitFields(void);
extern char g_beNumberCtrlInfoRam_callbackList[];
void *beNumberCtrlInfoRam_Register(void);
}

void *beNumberCtrlInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumberCtrlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNumberCtrlInfoRam_GetMetaObject,
        beNumberCtrlInfoRam_className,
        0x44, /* instance size */
        beNumberCtrlInfoRam_GetVTable,
        beNumberCtrlInfoRam_InitFields,
        0, /* extra callback item */
        g_beNumberCtrlInfoRam_callbackList /* callback list */
    );
}
