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
extern igMetaObject *g_beSaveUtilInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beSaveUtilInfoRam_GetMetaObject(void);
extern const char beSaveUtilInfoRam_className[];
int beSaveUtilInfoRam_GetVTable(void);
void beSaveUtilInfoRam_InitFields(void);
extern char g_beSaveUtilInfoRam_callbackList[];
void *beSaveUtilInfoRam_Register(void);
}

void *beSaveUtilInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveUtilInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beSaveUtilInfoRam_GetMetaObject,
        beSaveUtilInfoRam_className,
        0x34, /* instance size */
        beSaveUtilInfoRam_GetVTable,
        beSaveUtilInfoRam_InitFields,
        0, /* extra callback item */
        g_beSaveUtilInfoRam_callbackList /* callback list */
    );
}
