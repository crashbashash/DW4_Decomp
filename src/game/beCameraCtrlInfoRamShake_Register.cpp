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
extern igMetaObject *g_beCameraCtrlInfoRamShake_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beCameraCtrlInfoRamShake_GetMetaObject(void);
extern const char beCameraCtrlInfoRamShake_className[];
int beCameraCtrlInfoRamShake_GetVTable(void);
void beCameraCtrlInfoRamShake_InitFields(void);
void *beCameraCtrlInfoRamShake_Register(void);
}

void *beCameraCtrlInfoRamShake_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraCtrlInfoRamShake_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beCameraCtrlInfoRamShake_GetMetaObject,
        beCameraCtrlInfoRamShake_className,
        0x40, /* instance size */
        beCameraCtrlInfoRamShake_GetVTable,
        beCameraCtrlInfoRamShake_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
