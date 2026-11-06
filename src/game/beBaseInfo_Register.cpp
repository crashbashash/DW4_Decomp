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
extern igMetaObject *g_beBaseInfo_metaObject[];
void *igInfo_Register(void);
igMetaObject *igInfo_GetPublishedMetaObject(void);
igMetaObject *beBaseInfo_GetMetaObject(void);
extern const char beBaseInfo_className[];
void beBaseInfo_InitFields(void);
extern char g_beBaseInfo_callbackList[];
void *beBaseInfo_Register(void);
}

void *beBaseInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beBaseInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beBaseInfo_GetMetaObject,
        beBaseInfo_className,
        0x1c, /* instance size */
        0,
        beBaseInfo_InitFields,
        0, /* extra callback item */
        g_beBaseInfo_callbackList /* callback list */
    );
}
