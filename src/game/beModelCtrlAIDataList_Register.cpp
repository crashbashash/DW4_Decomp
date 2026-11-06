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
extern igMetaObject *g_beModelCtrlAIDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlAIDataList_GetMetaObject(void);
extern const char beModelCtrlAIDataList_className[];
int beModelCtrlAIDataList_GetVTable(void);
extern char g_beModelCtrlAIDataList_callbackList[];
void *beModelCtrlAIDataList_Register(void);
}

void *beModelCtrlAIDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlAIDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlAIDataList_GetMetaObject,
        beModelCtrlAIDataList_className,
        0x14, /* instance size */
        beModelCtrlAIDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlAIDataList_callbackList /* callback list */
    );
}
