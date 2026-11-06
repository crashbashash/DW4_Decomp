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
extern igMetaObject *g_beModelCtrlInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfo_GetMetaObject(void);
extern const char beModelCtrlInfo_className[];
int beModelCtrlInfo_GetVTable(void);
void beModelCtrlInfo_InitFields(void);
void *beModelCtrlInfo_Register(void);
}

void *beModelCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beModelCtrlInfo_GetMetaObject,
        beModelCtrlInfo_className,
        0x20, /* instance size */
        beModelCtrlInfo_GetVTable,
        beModelCtrlInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
