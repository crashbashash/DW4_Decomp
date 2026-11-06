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
extern igMetaObject *g_beModelCtrlData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlData_GetMetaObject(void);
extern const char beModelCtrlData_className[];
int beModelCtrlData_GetVTable(void);
void beModelCtrlData_InitFields(void);
extern char g_beModelCtrlData_callbackList[];
void *beModelCtrlData_Register(void);
}

void *beModelCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlData_GetMetaObject,
        beModelCtrlData_className,
        0x10, /* instance size */
        beModelCtrlData_GetVTable,
        beModelCtrlData_InitFields,
        0, /* extra callback item */
        g_beModelCtrlData_callbackList /* callback list */
    );
}
