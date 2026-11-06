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
extern igMetaObject *g_beFontInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beFontInfo_GetMetaObject(void);
extern const char beFontInfo_className[];
int beFontInfo_GetVTable(void);
void beFontInfo_InitFields(void);
extern char g_beFontInfo_callbackList[];
void *beFontInfo_Register(void);
}

void *beFontInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beFontInfo_GetMetaObject,
        beFontInfo_className,
        0x20, /* instance size */
        beFontInfo_GetVTable,
        beFontInfo_InitFields,
        0, /* extra callback item */
        g_beFontInfo_callbackList /* callback list */
    );
}
