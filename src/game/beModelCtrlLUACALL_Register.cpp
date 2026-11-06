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
extern igMetaObject *g_beModelCtrlLUACALL_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlLUACALL_GetMetaObject(void);
extern const char beModelCtrlLUACALL_className[];
int beModelCtrlLUACALL_GetVTable(void);
void beModelCtrlLUACALL_InitFields(void);
void *beModelCtrlLUACALL_Register(void);
}

void *beModelCtrlLUACALL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlLUACALL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLUACALL_GetMetaObject,
        beModelCtrlLUACALL_className,
        0x10, /* instance size */
        beModelCtrlLUACALL_GetVTable,
        beModelCtrlLUACALL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
