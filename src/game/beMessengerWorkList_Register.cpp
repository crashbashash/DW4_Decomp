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
extern igMetaObject *g_beMessengerWorkList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beMessengerWorkList_GetMetaObject(void);
extern const char beMessengerWorkList_className[];
int beMessengerWorkList_GetVTable(void);
extern char g_beMessengerWorkList_callbackList[];
void *beMessengerWorkList_Register(void);
}

void *beMessengerWorkList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerWorkList_GetMetaObject,
        beMessengerWorkList_className,
        0x14, /* instance size */
        beMessengerWorkList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerWorkList_callbackList /* callback list */
    );
}
