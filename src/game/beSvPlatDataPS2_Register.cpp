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
extern igMetaObject *g_beSvPlatDataPS2_metaObject[];
void *beSvPlatBaseData_Register(void);
igMetaObject *beSvPlatBaseData_GetPublishedMetaObject(void);
igMetaObject *beSvPlatDataPS2_GetMetaObject(void);
extern const char beSvPlatDataPS2_className[];
int beSvPlatDataPS2_GetVTable(void);
void beSvPlatDataPS2_InitFields(void);
extern char g_beSvPlatDataPS2_callbackList[];
void *beSvPlatDataPS2_Register(void);
}

void *beSvPlatDataPS2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatDataPS2_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataPS2_GetMetaObject,
        beSvPlatDataPS2_className,
        0xd8, /* instance size */
        beSvPlatDataPS2_GetVTable,
        beSvPlatDataPS2_InitFields,
        0, /* extra callback item */
        g_beSvPlatDataPS2_callbackList /* callback list */
    );
}
