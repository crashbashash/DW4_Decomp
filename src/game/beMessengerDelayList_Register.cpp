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
extern igMetaObject *g_beMessengerDelayList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beMessengerDelayList_GetMetaObject(void);
extern const char beMessengerDelayList_className[];
int beMessengerDelayList_GetVTable(void);
extern char g_beMessengerDelayList_callbackList[];
void *beMessengerDelayList_Register(void);
}

void *beMessengerDelayList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerDelayList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerDelayList_GetMetaObject,
        beMessengerDelayList_className,
        0x14, /* instance size */
        beMessengerDelayList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerDelayList_callbackList /* callback list */
    );
}
