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
extern igMetaObject *g_beModelCtrlMSGBOX_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlMSGBOX_GetMetaObject(void);
extern const char beModelCtrlMSGBOX_className[];
int beModelCtrlMSGBOX_GetVTable(void);
void *beModelCtrlMSGBOX_Register(void);
}

void *beModelCtrlMSGBOX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMSGBOX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMSGBOX_GetMetaObject,
        beModelCtrlMSGBOX_className,
        0xc, /* instance size */
        beModelCtrlMSGBOX_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
