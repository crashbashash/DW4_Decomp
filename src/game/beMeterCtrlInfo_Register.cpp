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
extern igMetaObject *g_beMeterCtrlInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beMeterCtrlInfo_GetMetaObject(void);
extern const char beMeterCtrlInfo_className[];
int beMeterCtrlInfo_GetVTable(void);
void beMeterCtrlInfo_InitFields(void);
extern char g_beMeterCtrlInfo_callbackList[];
void *beMeterCtrlInfo_Register(void);
}

void *beMeterCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMeterCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMeterCtrlInfo_GetMetaObject,
        beMeterCtrlInfo_className,
        0x20, /* instance size */
        beMeterCtrlInfo_GetVTable,
        beMeterCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beMeterCtrlInfo_callbackList /* callback list */
    );
}
