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
extern igMetaObject *g_beMatCtrlInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beMatCtrlInfoRam_GetMetaObject(void);
extern const char beMatCtrlInfoRam_className[];
int beMatCtrlInfoRam_GetVTable(void);
void beMatCtrlInfoRam_InitFields(void);
extern char g_beMatCtrlInfoRam_callbackList[];
void *beMatCtrlInfoRam_Register(void);
}

void *beMatCtrlInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beMatCtrlInfoRam_GetMetaObject,
        beMatCtrlInfoRam_className,
        0x30, /* instance size */
        beMatCtrlInfoRam_GetVTable,
        beMatCtrlInfoRam_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfoRam_callbackList /* callback list */
    );
}
