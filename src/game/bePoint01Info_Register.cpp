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
extern igMetaObject *g_bePoint01Info_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *bePoint01Info_GetMetaObject(void);
extern const char bePoint01Info_className[];
int bePoint01Info_GetVTable(void);
void bePoint01Info_InitFields(void);
extern char g_bePoint01Info_callbackList[];
void *bePoint01Info_Register(void);
}

void *bePoint01Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_bePoint01Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        bePoint01Info_GetMetaObject,
        bePoint01Info_className,
        0x24, /* instance size */
        bePoint01Info_GetVTable,
        bePoint01Info_InitFields,
        0, /* extra callback item */
        g_bePoint01Info_callbackList /* callback list */
    );
}
