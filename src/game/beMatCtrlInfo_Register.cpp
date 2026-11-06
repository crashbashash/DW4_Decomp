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
extern igMetaObject *g_beMatCtrlInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beMatCtrlInfo_GetMetaObject(void);
extern const char beMatCtrlInfo_className[];
int beMatCtrlInfo_GetVTable(void);
void beMatCtrlInfo_InitFields(void);
extern char g_beMatCtrlInfo_callbackList[];
void *beMatCtrlInfo_Register(void);
}

void *beMatCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMatCtrlInfo_GetMetaObject,
        beMatCtrlInfo_className,
        0x28, /* instance size */
        beMatCtrlInfo_GetVTable,
        beMatCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfo_callbackList /* callback list */
    );
}
