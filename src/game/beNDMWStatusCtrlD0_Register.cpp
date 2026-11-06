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
extern igMetaObject *g_beNDMWStatusCtrlD0_metaObject[];
void *beNDMWListCtrl_Register(void);
igMetaObject *beNDMWListCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusCtrlD0_GetMetaObject(void);
extern const char beNDMWStatusCtrlD0_className[];
int beNDMWStatusCtrlD0_GetVTable(void);
void beNDMWStatusCtrlD0_InitFields(void);
extern char g_beNDMWStatusCtrlD0_callbackList[];
void *beNDMWStatusCtrlD0_Register(void);
}

void *beNDMWStatusCtrlD0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlD0_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlD0_GetMetaObject,
        beNDMWStatusCtrlD0_className,
        0x74, /* instance size */
        beNDMWStatusCtrlD0_GetVTable,
        beNDMWStatusCtrlD0_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlD0_callbackList /* callback list */
    );
}
