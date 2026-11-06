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
extern igMetaObject *g_beAsTargetModelData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beAsTargetModelData_GetMetaObject(void);
extern const char beAsTargetModelData_className[];
int beAsTargetModelData_GetVTable(void);
void beAsTargetModelData_InitFields(void);
extern char g_beAsTargetModelData_callbackList[];
void *beAsTargetModelData_Register(void);
}

void *beAsTargetModelData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAsTargetModelData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAsTargetModelData_GetMetaObject,
        beAsTargetModelData_className,
        0x10, /* instance size */
        beAsTargetModelData_GetVTable,
        beAsTargetModelData_InitFields,
        0, /* extra callback item */
        g_beAsTargetModelData_callbackList /* callback list */
    );
}
