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
extern igMetaObject *g_beCameraMode_metaObject[];
void *igViewMode_Register(void);
igMetaObject *igViewMode_GetPublishedMetaObject(void);
igMetaObject *beCameraMode_GetMetaObject(void);
extern const char beCameraMode_className[];
int beCameraMode_GetVTable(void);
void beCameraMode_InitFields(void);
extern char g_beCameraMode_callbackList[];
void *beCameraMode_Register(void);
}

void *beCameraMode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        beCameraMode_GetMetaObject,
        beCameraMode_className,
        0x78, /* instance size */
        beCameraMode_GetVTable,
        beCameraMode_InitFields,
        0, /* extra callback item */
        g_beCameraMode_callbackList /* callback list */
    );
}
