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
extern igMetaObject *g_beBkColorInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beBkColorInfo_GetMetaObject(void);
extern const char beBkColorInfo_className[];
int beBkColorInfo_GetVTable(void);
void beBkColorInfo_InitFields(void);
void *beBkColorInfo_Register(void);
}

void *beBkColorInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBkColorInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beBkColorInfo_GetMetaObject,
        beBkColorInfo_className,
        0x2c, /* instance size */
        beBkColorInfo_GetVTable,
        beBkColorInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
