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
extern igMetaObject *g_beNDMWStatusCtrlSendBit_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusCtrlSendBit_GetMetaObject(void);
extern const char beNDMWStatusCtrlSendBit_className[];
int beNDMWStatusCtrlSendBit_GetVTable(void);
void beNDMWStatusCtrlSendBit_InitFields(void);
extern char g_beNDMWStatusCtrlSendBit_callbackList[];
void *beNDMWStatusCtrlSendBit_Register(void);
}

void *beNDMWStatusCtrlSendBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlSendBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlSendBit_GetMetaObject,
        beNDMWStatusCtrlSendBit_className,
        0x64, /* instance size */
        beNDMWStatusCtrlSendBit_GetVTable,
        beNDMWStatusCtrlSendBit_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlSendBit_callbackList /* callback list */
    );
}
