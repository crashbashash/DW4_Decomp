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
extern igMetaObject *g_beModelCtrlHITBOX_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlHITBOX_GetMetaObject(void);
extern const char beModelCtrlHITBOX_className[];
int beModelCtrlHITBOX_GetVTable(void);
void beModelCtrlHITBOX_InitFields(void);
void *beModelCtrlHITBOX_Register(void);
}

void *beModelCtrlHITBOX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlHITBOX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlHITBOX_GetMetaObject,
        beModelCtrlHITBOX_className,
        0x30, /* instance size */
        beModelCtrlHITBOX_GetVTable,
        beModelCtrlHITBOX_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
