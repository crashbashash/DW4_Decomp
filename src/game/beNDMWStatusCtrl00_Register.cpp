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
extern igMetaObject *g_beNDMWStatusCtrl00_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusCtrl00_GetMetaObject(void);
extern const char beNDMWStatusCtrl00_className[];
int beNDMWStatusCtrl00_GetVTable(void);
void beNDMWStatusCtrl00_InitFields(void);
void *beNDMWStatusCtrl00_Register(void);
}

void *beNDMWStatusCtrl00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrl00_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrl00_GetMetaObject,
        beNDMWStatusCtrl00_className,
        0x58, /* instance size */
        beNDMWStatusCtrl00_GetVTable,
        beNDMWStatusCtrl00_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
