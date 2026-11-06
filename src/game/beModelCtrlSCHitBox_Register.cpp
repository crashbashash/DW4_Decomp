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
extern igMetaObject *g_beModelCtrlSCHitBox_metaObject[];
void *beModelCtrlSubComBase_Register(void);
igMetaObject *beModelCtrlSubComBase_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlSCHitBox_GetMetaObject(void);
extern const char beModelCtrlSCHitBox_className[];
int beModelCtrlSCHitBox_GetVTable(void);
void beModelCtrlSCHitBox_InitFields(void);
void *beModelCtrlSCHitBox_Register(void);
}

void *beModelCtrlSCHitBox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlSCHitBox_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCHitBox_GetMetaObject,
        beModelCtrlSCHitBox_className,
        0x3c, /* instance size */
        beModelCtrlSCHitBox_GetVTable,
        beModelCtrlSCHitBox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
