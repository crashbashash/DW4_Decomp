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
extern igMetaObject *g_beMessengerGroupList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beMessengerGroupList_GetMetaObject(void);
extern const char beMessengerGroupList_className[];
int beMessengerGroupList_GetVTable(void);
extern char g_beMessengerGroupList_callbackList[];
void *beMessengerGroupList_Register(void);
}

void *beMessengerGroupList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerGroupList_GetMetaObject,
        beMessengerGroupList_className,
        0x14, /* instance size */
        beMessengerGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerGroupList_callbackList /* callback list */
    );
}
