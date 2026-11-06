struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWMdlPlayer2InfoWork_metaObject[];
void *beModelCtrlInfoWork_Register(void);
igMetaObject *beModelCtrlInfoWork_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlPlayer2InfoWork_GetMetaObject(void);
extern const char beNDMWMdlPlayer2InfoWork_className[];
int beNDMWMdlPlayer2InfoWork_GetVTable(void);
void beNDMWMdlPlayer2InfoWork_InitFields(void);
void *beNDMWMdlPlayer2InfoWork_Register(void);
}

void *beNDMWMdlPlayer2InfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPlayer2InfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlPlayer2InfoWork_GetMetaObject,
        beNDMWMdlPlayer2InfoWork_className,
        0xfc, /* instance size */
        beNDMWMdlPlayer2InfoWork_GetVTable,
        beNDMWMdlPlayer2InfoWork_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
