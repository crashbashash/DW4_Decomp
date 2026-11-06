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
extern igMetaObject *g_beSoundData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beSoundData_GetMetaObject(void);
extern const char beSoundData_className[];
int beSoundData_GetVTable(void);
void beSoundData_InitFields(void);
void *beSoundData_Register(void);
}

void *beSoundData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSoundData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSoundData_GetMetaObject,
        beSoundData_className,
        0x20, /* instance size */
        beSoundData_GetVTable,
        beSoundData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
