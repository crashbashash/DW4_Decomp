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
extern igMetaObject *g_beMessengerArgDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beMessengerArgDataList_GetMetaObject(void);
extern const char beMessengerArgDataList_className[];
int beMessengerArgDataList_GetVTable(void);
extern char g_beMessengerArgDataList_callbackList[];
void *beMessengerArgDataList_Register(void);
}

void *beMessengerArgDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerArgDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerArgDataList_GetMetaObject,
        beMessengerArgDataList_className,
        0x14, /* instance size */
        beMessengerArgDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerArgDataList_callbackList /* callback list */
    );
}
