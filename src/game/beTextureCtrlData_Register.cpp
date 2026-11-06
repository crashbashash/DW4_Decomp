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
extern igMetaObject *g_beTextureCtrlData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beTextureCtrlData_GetMetaObject(void);
extern const char beTextureCtrlData_className[];
int beTextureCtrlData_GetVTable(void);
void beTextureCtrlData_InitFields(void);
extern char g_beTextureCtrlData_callbackList[];
void *beTextureCtrlData_Register(void);
}

void *beTextureCtrlData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrlData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beTextureCtrlData_GetMetaObject,
        beTextureCtrlData_className,
        0x10, /* instance size */
        beTextureCtrlData_GetVTable,
        beTextureCtrlData_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlData_callbackList /* callback list */
    );
}
