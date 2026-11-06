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
extern igMetaObject *g_beDataBaseList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beDataBaseList_GetMetaObject(void);
extern const char beDataBaseList_className[];
int beDataBaseList_GetVTable(void);
extern char g_beDataBaseList_callbackList[];
void *beDataBaseList_Register(void);
}

void *beDataBaseList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataBaseList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataBaseList_GetMetaObject,
        beDataBaseList_className,
        0x14, /* instance size */
        beDataBaseList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDataBaseList_callbackList /* callback list */
    );
}
