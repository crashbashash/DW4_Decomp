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
extern igMetaObject *g_beGroupKeepList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beGroupKeepList_GetMetaObject(void);
extern const char beGroupKeepList_className[];
int beGroupKeepList_GetVTable(void);
extern char g_beGroupKeepList_callbackList[];
void *beGroupKeepList_Register(void);
}

void *beGroupKeepList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGroupKeepList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGroupKeepList_GetMetaObject,
        beGroupKeepList_className,
        0x14, /* instance size */
        beGroupKeepList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGroupKeepList_callbackList /* callback list */
    );
}
