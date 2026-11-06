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
extern igMetaObject *g_beDBManagerInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beDBManagerInfo_GetMetaObject(void);
extern const char beDBManagerInfo_className[];
int beDBManagerInfo_GetVTable(void);
void beDBManagerInfo_InitFields(void);
extern char g_beDBManagerInfo_callbackList[];
void *beDBManagerInfo_Register(void);
}

void *beDBManagerInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDBManagerInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beDBManagerInfo_GetMetaObject,
        beDBManagerInfo_className,
        0x20, /* instance size */
        beDBManagerInfo_GetVTable,
        beDBManagerInfo_InitFields,
        0, /* extra callback item */
        g_beDBManagerInfo_callbackList /* callback list */
    );
}
