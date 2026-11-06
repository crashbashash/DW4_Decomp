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
extern igMetaObject *g_beModelCtrlMOVEEX_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlMOVEEX_GetMetaObject(void);
extern const char beModelCtrlMOVEEX_className[];
int beModelCtrlMOVEEX_GetVTable(void);
void beModelCtrlMOVEEX_InitFields(void);
void *beModelCtrlMOVEEX_Register(void);
}

void *beModelCtrlMOVEEX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMOVEEX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVEEX_GetMetaObject,
        beModelCtrlMOVEEX_className,
        0x24, /* instance size */
        beModelCtrlMOVEEX_GetVTable,
        beModelCtrlMOVEEX_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
