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
extern igMetaObject *g_beBkColor_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beBkColor_GetMetaObject(void);
extern const char beBkColor_className[];
int beBkColor_GetVTable(void);
void beBkColor_InitFields(void);
void *beBkColor_Register(void);
}

void *beBkColor_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBkColor_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beBkColor_GetMetaObject,
        beBkColor_className,
        0x24, /* instance size */
        beBkColor_GetVTable,
        beBkColor_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
