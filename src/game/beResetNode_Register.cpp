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
extern igMetaObject *g_beResetNode_metaObject[];
void *igGroup_Register(void);
igMetaObject *igGroup_GetPublishedMetaObject(void);
igMetaObject *beResetNode_GetMetaObject(void);
extern const char beResetNode_className[];
int beResetNode_GetVTable(void);
void beResetNode_InitFields(void);
void FUN_0034b690(void);
void *beResetNode_Register(void);
}

void *beResetNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beResetNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beResetNode_GetMetaObject,
        beResetNode_className,
        0x24, /* instance size */
        beResetNode_GetVTable,
        beResetNode_InitFields,
        FUN_0034b690, /* extra callback item */
        0 /* callback list */
    );
}
