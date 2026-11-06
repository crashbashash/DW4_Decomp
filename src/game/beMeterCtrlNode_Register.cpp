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
extern igMetaObject *g_beMeterCtrlNode_metaObject[];
void *igGroup_Register(void);
igMetaObject *igGroup_GetPublishedMetaObject(void);
igMetaObject *beMeterCtrlNode_GetMetaObject(void);
extern const char beMeterCtrlNode_className[];
int beMeterCtrlNode_GetVTable(void);
void beMeterCtrlNode_InitFields(void);
void FUN_00356f40(void);
extern char g_beMeterCtrlNode_callbackList[];
void *beMeterCtrlNode_Register(void);
}

void *beMeterCtrlNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMeterCtrlNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beMeterCtrlNode_GetMetaObject,
        beMeterCtrlNode_className,
        0x34, /* instance size */
        beMeterCtrlNode_GetVTable,
        beMeterCtrlNode_InitFields,
        FUN_00356f40, /* extra callback item */
        g_beMeterCtrlNode_callbackList /* callback list */
    );
}
