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
extern igMetaObject *g_beTextureCtrlWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beTextureCtrlWork_GetMetaObject(void);
extern const char beTextureCtrlWork_className[];
int beTextureCtrlWork_GetVTable(void);
void beTextureCtrlWork_InitFields(void);
extern char g_beTextureCtrlWork_callbackList[];
void *beTextureCtrlWork_Register(void);
}

void *beTextureCtrlWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrlWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beTextureCtrlWork_GetMetaObject,
        beTextureCtrlWork_className,
        0x10, /* instance size */
        beTextureCtrlWork_GetVTable,
        beTextureCtrlWork_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlWork_callbackList /* callback list */
    );
}
