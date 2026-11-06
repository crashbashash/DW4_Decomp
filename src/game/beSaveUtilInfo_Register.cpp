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
extern igMetaObject *g_beSaveUtilInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beSaveUtilInfo_GetMetaObject(void);
extern const char beSaveUtilInfo_className[];
int beSaveUtilInfo_GetVTable(void);
void *beSaveUtilInfo_Register(void);
}

void *beSaveUtilInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveUtilInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSaveUtilInfo_GetMetaObject,
        beSaveUtilInfo_className,
        0x1c, /* instance size */
        beSaveUtilInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
