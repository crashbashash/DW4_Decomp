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
extern igMetaObject *g_beLoadingNode_metaObject[];
void *beNodeAnim_Register(void);
igMetaObject *beNodeAnim_GetPublishedMetaObject(void);
igMetaObject *beLoadingNode_GetMetaObject(void);
extern const char beLoadingNode_className[];
int beLoadingNode_GetVTable(void);
void beLoadingNode_InitFields(void);
void FUN_0034e850(void);
void *beLoadingNode_Register(void);
}

void *beLoadingNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLoadingNode_metaObject,
        beNodeAnim_Register,
        beNodeAnim_GetPublishedMetaObject,
        beLoadingNode_GetMetaObject,
        beLoadingNode_className,
        0x80, /* instance size */
        beLoadingNode_GetVTable,
        beLoadingNode_InitFields,
        FUN_0034e850, /* extra callback item */
        0 /* callback list */
    );
}
