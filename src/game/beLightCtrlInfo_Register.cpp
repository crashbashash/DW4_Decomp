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
extern igMetaObject *g_beLightCtrlInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beLightCtrlInfo_GetMetaObject(void);
extern const char beLightCtrlInfo_className[];
int beLightCtrlInfo_GetVTable(void);
void beLightCtrlInfo_InitFields(void);
extern char g_beLightCtrlInfo_callbackList[];
void *beLightCtrlInfo_Register(void);
}

void *beLightCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLightCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLightCtrlInfo_GetMetaObject,
        beLightCtrlInfo_className,
        0x20, /* instance size */
        beLightCtrlInfo_GetVTable,
        beLightCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beLightCtrlInfo_callbackList /* callback list */
    );
}
