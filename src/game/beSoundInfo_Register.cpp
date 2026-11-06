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
extern igMetaObject *g_beSoundInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beSoundInfo_GetMetaObject(void);
extern const char beSoundInfo_className[];
int beSoundInfo_GetVTable(void);
void beSoundInfo_InitFields(void);
extern char g_beSoundInfo_callbackList[];
void *beSoundInfo_Register(void);
}

void *beSoundInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSoundInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSoundInfo_GetMetaObject,
        beSoundInfo_className,
        0x28, /* instance size */
        beSoundInfo_GetVTable,
        beSoundInfo_InitFields,
        0, /* extra callback item */
        g_beSoundInfo_callbackList /* callback list */
    );
}
