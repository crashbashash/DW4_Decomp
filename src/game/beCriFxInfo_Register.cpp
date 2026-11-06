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
extern igMetaObject *g_beCriFxInfo_metaObject[];
void *igInfo_Register(void);
igMetaObject *igInfo_GetPublishedMetaObject(void);
igMetaObject *beCriFxInfo_GetMetaObject(void);
extern const char beCriFxInfo_className[];
int beCriFxInfo_GetVTable(void);
void beCriFxInfo_InitFields(void);
extern char g_beCriFxInfo_callbackList[];
void *beCriFxInfo_Register(void);
}

void *beCriFxInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriFxInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beCriFxInfo_GetMetaObject,
        beCriFxInfo_className,
        0x24, /* instance size */
        beCriFxInfo_GetVTable,
        beCriFxInfo_InitFields,
        0, /* extra callback item */
        g_beCriFxInfo_callbackList /* callback list */
    );
}
