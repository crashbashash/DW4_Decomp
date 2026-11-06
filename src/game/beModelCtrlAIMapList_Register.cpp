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
extern igMetaObject *g_beModelCtrlAIMapList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlAIMapList_GetMetaObject(void);
extern const char beModelCtrlAIMapList_className[];
int beModelCtrlAIMapList_GetVTable(void);
extern char g_beModelCtrlAIMapList_callbackList[];
void *beModelCtrlAIMapList_Register(void);
}

void *beModelCtrlAIMapList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlAIMapList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlAIMapList_GetMetaObject,
        beModelCtrlAIMapList_className,
        0x14, /* instance size */
        beModelCtrlAIMapList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlAIMapList_callbackList /* callback list */
    );
}
