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
extern igMetaObject *g_beSwitchCtrlInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beSwitchCtrlInfo_GetMetaObject(void);
extern const char beSwitchCtrlInfo_className[];
int beSwitchCtrlInfo_GetVTable(void);
void beSwitchCtrlInfo_InitFields(void);
extern char g_beSwitchCtrlInfo_callbackList[];
void *beSwitchCtrlInfo_Register(void);
}

void *beSwitchCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSwitchCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSwitchCtrlInfo_GetMetaObject,
        beSwitchCtrlInfo_className,
        0x20, /* instance size */
        beSwitchCtrlInfo_GetVTable,
        beSwitchCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beSwitchCtrlInfo_callbackList /* callback list */
    );
}
