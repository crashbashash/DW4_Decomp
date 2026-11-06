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
extern igMetaObject *g_beNDMWStatusCtrlSkill_metaObject[];
void *beNDMWListCtrl_Register(void);
igMetaObject *beNDMWListCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusCtrlSkill_GetMetaObject(void);
extern const char beNDMWStatusCtrlSkill_className[];
int beNDMWStatusCtrlSkill_GetVTable(void);
void beNDMWStatusCtrlSkill_InitFields(void);
extern char g_beNDMWStatusCtrlSkill_callbackList[];
void *beNDMWStatusCtrlSkill_Register(void);
}

void *beNDMWStatusCtrlSkill_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlSkill_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlSkill_GetMetaObject,
        beNDMWStatusCtrlSkill_className,
        0x6c, /* instance size */
        beNDMWStatusCtrlSkill_GetVTable,
        beNDMWStatusCtrlSkill_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlSkill_callbackList /* callback list */
    );
}
