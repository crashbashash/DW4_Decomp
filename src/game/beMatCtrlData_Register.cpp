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
extern igMetaObject *g_beMatCtrlData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beMatCtrlData_GetMetaObject(void);
extern const char beMatCtrlData_className[];
int beMatCtrlData_GetVTable(void);
void beMatCtrlData_InitFields(void);
extern char g_beMatCtrlData_callbackList[];
void *beMatCtrlData_Register(void);
}

void *beMatCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrlData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMatCtrlData_GetMetaObject,
        beMatCtrlData_className,
        0x10, /* instance size */
        beMatCtrlData_GetVTable,
        beMatCtrlData_InitFields,
        0, /* extra callback item */
        g_beMatCtrlData_callbackList /* callback list */
    );
}
