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
extern igMetaObject *g_beCopyTransform_metaObject[];
void *igTransform_Register(void);
igMetaObject *igTransform_GetPublishedMetaObject(void);
igMetaObject *beCopyTransform_GetMetaObject(void);
extern const char beCopyTransform_className[];
int beCopyTransform_GetVTable(void);
void beCopyTransform_InitFields(void);
void FUN_00368090(void);
extern char g_beCopyTransform_callbackList[];
void *beCopyTransform_Register(void);
}

void *beCopyTransform_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCopyTransform_metaObject,
        igTransform_Register,
        igTransform_GetPublishedMetaObject,
        beCopyTransform_GetMetaObject,
        beCopyTransform_className,
        0x70, /* instance size */
        beCopyTransform_GetVTable,
        beCopyTransform_InitFields,
        FUN_00368090, /* extra callback item */
        g_beCopyTransform_callbackList /* callback list */
    );
}
