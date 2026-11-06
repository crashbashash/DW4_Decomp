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
extern igMetaObject *g_beUnicodeObjList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beUnicodeObjList_GetMetaObject(void);
extern const char beUnicodeObjList_className[];
int beUnicodeObjList_GetVTable(void);
extern char g_beUnicodeObjList_callbackList[];
void *beUnicodeObjList_Register(void);
}

void *beUnicodeObjList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beUnicodeObjList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beUnicodeObjList_GetMetaObject,
        beUnicodeObjList_className,
        0x14, /* instance size */
        beUnicodeObjList_GetVTable,
        0,
        0, /* extra callback item */
        g_beUnicodeObjList_callbackList /* callback list */
    );
}
