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
extern igMetaObject *g_beNDMWStatusCtrlFlag_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusCtrlFlag_GetMetaObject(void);
extern const char beNDMWStatusCtrlFlag_className[];
int beNDMWStatusCtrlFlag_GetVTable(void);
void beNDMWStatusCtrlFlag_InitFields(void);
extern char g_beNDMWStatusCtrlFlag_callbackList[];
void *beNDMWStatusCtrlFlag_Register(void);
}

void *beNDMWStatusCtrlFlag_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlFlag_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlFlag_GetMetaObject,
        beNDMWStatusCtrlFlag_className,
        0x58, /* instance size */
        beNDMWStatusCtrlFlag_GetVTable,
        beNDMWStatusCtrlFlag_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlFlag_callbackList /* callback list */
    );
}
