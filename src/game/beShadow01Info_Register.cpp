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
extern igMetaObject *g_beShadow01Info_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beShadow01Info_GetMetaObject(void);
extern const char beShadow01Info_className[];
int beShadow01Info_GetVTable(void);
void beShadow01Info_InitFields(void);
extern char g_beShadow01Info_callbackList[];
void *beShadow01Info_Register(void);
}

void *beShadow01Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beShadow01Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beShadow01Info_GetMetaObject,
        beShadow01Info_className,
        0x28, /* instance size */
        beShadow01Info_GetVTable,
        beShadow01Info_InitFields,
        0, /* extra callback item */
        g_beShadow01Info_callbackList /* callback list */
    );
}
