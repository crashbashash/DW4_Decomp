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
extern igMetaObject *g_beSvPlatDataXbox_metaObject[];
void *beSvPlatBaseData_Register(void);
igMetaObject *beSvPlatBaseData_GetPublishedMetaObject(void);
igMetaObject *beSvPlatDataXbox_GetMetaObject(void);
extern const char beSvPlatDataXbox_className[];
int beSvPlatDataXbox_GetVTable(void);
void beSvPlatDataXbox_InitFields(void);
extern char g_beSvPlatDataXbox_callbackList[];
void *beSvPlatDataXbox_Register(void);
}

void *beSvPlatDataXbox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatDataXbox_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataXbox_GetMetaObject,
        beSvPlatDataXbox_className,
        0x2c, /* instance size */
        beSvPlatDataXbox_GetVTable,
        beSvPlatDataXbox_InitFields,
        0, /* extra callback item */
        g_beSvPlatDataXbox_callbackList /* callback list */
    );
}
