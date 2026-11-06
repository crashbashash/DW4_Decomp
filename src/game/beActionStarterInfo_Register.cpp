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
extern igMetaObject *g_beActionStarterInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beActionStarterInfo_GetMetaObject(void);
extern const char beActionStarterInfo_className[];
int beActionStarterInfo_GetVTable(void);
void beActionStarterInfo_InitFields(void);
extern char g_beActionStarterInfo_callbackList[];
void *beActionStarterInfo_Register(void);
}

void *beActionStarterInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beActionStarterInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beActionStarterInfo_GetMetaObject,
        beActionStarterInfo_className,
        0x20, /* instance size */
        beActionStarterInfo_GetVTable,
        beActionStarterInfo_InitFields,
        0, /* extra callback item */
        g_beActionStarterInfo_callbackList /* callback list */
    );
}
