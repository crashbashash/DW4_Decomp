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
extern igMetaObject *g_beModelCtrlDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlDataList_GetMetaObject(void);
extern const char beModelCtrlDataList_className[];
int beModelCtrlDataList_GetVTable(void);
extern char Pi5[];
void *beModelCtrlDataList_Register(void);
}

void *beModelCtrlDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlDataList_GetMetaObject,
        beModelCtrlDataList_className,
        0x14, /* instance size */
        beModelCtrlDataList_GetVTable,
        0,
        0, /* extra callback item */
        Pi5 /* callback list */
    );
}
