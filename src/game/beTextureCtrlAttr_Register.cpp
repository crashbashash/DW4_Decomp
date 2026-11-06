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
extern igMetaObject *g_beTextureCtrlAttr_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beTextureCtrlAttr_GetMetaObject(void);
extern const char beTextureCtrlAttr_className[];
int beTextureCtrlAttr_GetVTable(void);
void beTextureCtrlAttr_InitFields(void);
extern char g_beTextureCtrlAttr_callbackList[];
void *beTextureCtrlAttr_Register(void);
}

void *beTextureCtrlAttr_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrlAttr_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beTextureCtrlAttr_GetMetaObject,
        beTextureCtrlAttr_className,
        0x10, /* instance size */
        beTextureCtrlAttr_GetVTable,
        beTextureCtrlAttr_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlAttr_callbackList /* callback list */
    );
}
