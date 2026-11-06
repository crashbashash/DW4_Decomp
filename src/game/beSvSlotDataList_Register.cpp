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
extern igMetaObject *g_beSvSlotDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beSvSlotDataList_GetMetaObject(void);
extern const char beSvSlotDataList_className[];
int beSvSlotDataList_GetVTable(void);
extern char g_beSvSlotDataList_callbackList[];
void *beSvSlotDataList_Register(void);
}

void *beSvSlotDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvSlotDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSvSlotDataList_GetMetaObject,
        beSvSlotDataList_className,
        0x14, /* instance size */
        beSvSlotDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSvSlotDataList_callbackList /* callback list */
    );
}
