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
extern igMetaObject *g_beFontInfoData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beFontInfoData_GetMetaObject(void);
extern const char beFontInfoData_className[];
int beFontInfoData_GetVTable(void);
void beFontInfoData_InitFields(void);
extern char g_beFontInfoData_callbackList[];
void *beFontInfoData_Register(void);
}

void *beFontInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beFontInfoData_GetMetaObject,
        beFontInfoData_className,
        0x2c, /* instance size */
        beFontInfoData_GetVTable,
        beFontInfoData_InitFields,
        0, /* extra callback item */
        g_beFontInfoData_callbackList /* callback list */
    );
}
