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
extern igMetaObject *g_beCopyModelCtrl2_metaObject[];
void *igTransform_Register(void);
igMetaObject *igTransform_GetPublishedMetaObject(void);
igMetaObject *beCopyModelCtrl2_GetMetaObject(void);
extern const char beCopyModelCtrl2_className[];
int beCopyModelCtrl2_GetVTable(void);
void beCopyModelCtrl2_InitFields(void);
void FUN_003682f0(void);
extern char g_beCopyModelCtrl2_callbackList[];
void *beCopyModelCtrl2_Register(void);
}

void *beCopyModelCtrl2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCopyModelCtrl2_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beCopyModelCtrl2_GetMetaObject,
        beCopyModelCtrl2_className,
        0x70, /* instance size */
        beCopyModelCtrl2_GetVTable,
        beCopyModelCtrl2_InitFields,
        FUN_003682f0, /* extra callback item */
        g_beCopyModelCtrl2_callbackList /* callback list */
    );
}
