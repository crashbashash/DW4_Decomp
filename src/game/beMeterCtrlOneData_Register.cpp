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
extern igMetaObject *g_beMeterCtrlOneData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beMeterCtrlOneData_GetMetaObject(void);
extern const char beMeterCtrlOneData_className[];
int beMeterCtrlOneData_GetVTable(void);
void beMeterCtrlOneData_InitFields(void);
extern char g_beMeterCtrlOneData_callbackList[];
void *beMeterCtrlOneData_Register(void);
}

void *beMeterCtrlOneData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMeterCtrlOneData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMeterCtrlOneData_GetMetaObject,
        beMeterCtrlOneData_className,
        0x48, /* instance size */
        beMeterCtrlOneData_GetVTable,
        beMeterCtrlOneData_InitFields,
        0, /* extra callback item */
        g_beMeterCtrlOneData_callbackList /* callback list */
    );
}
