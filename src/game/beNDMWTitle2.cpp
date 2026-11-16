#include "dw4/reflected.h"
#include "dw4/beNDMWTitle2.h"
#define ALLOC(dst, obj)                                                                            \
    {                                                                                              \
        int alloc = igObject_GetAllocator(obj);                                                    \
        if (g_useOwnerAllocator != 0) {                                                                   \
            dst = alloc;                                                                           \
        } else {                                                                                   \
            dst = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);                                  \
        }                                                                                          \
    }
#define SET_DATA(ref)                                                                              \
    {                                                                                              \
        igObject *n = (igObject *)(ref).p;                                                         \
        if (n != 0)                                                                                \
            n->_refCount = n->_refCount + 1;                                                       \
        igObject *old = (igObject *)infoRam->_dataList;                                            \
        if (old != 0) {                                                                            \
            old->_refCount = old->_refCount - 1;                                                   \
            if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0)       \
                igObject_Destroy(old);                                                             \
        }                                                                                          \
        infoRam->_dataList = (int)n;                                                               \
    }

extern "C" int beMessenger_SendGroup(...);
extern "C" int beMessenger_GetObject(...);
extern "C" void * igProperty_GetRecord(...);
extern "C" int igInsightCore_FindManager(...);
extern "C" void *beBaseInfoDataList_Create(...);
extern "C" void *beNDMWTitle2Option_Create(...);
extern "C" void *beNDMWTitle2CtrlData_Create(...);
extern "C" void *beNDMWLoadIntf2ComMdlCtrl_Create(...);
extern "C" void *beNDMWLoadIntf2TextOrder_Create(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Start(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Play(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Close(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsRunning(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Poll(...);
extern "C" int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
extern "C" int TextOrder_PublishLineListOnly(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBool(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" void *bePadManager_GetPadForPlayer(...);
extern "C" int igObject_Destroy(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void *igProperty_FindByName(...);
extern "C" int beMessenger_RegisterReceiverFromInfo(int, int, const void *);
extern "C" int beNDMWTitle2_GetInfoMeta(void);
extern "C" int beNDMWTitle2_GetMeta(void);
extern "C" int beNDMWTitle2CtrlData_GetMessageEnum(...);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" void beNDMWTitle2Option_InitSettings(beNDMWTitle2Option *self, int messenger);
extern "C" int g_propertyNameField[4];
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" int g_beLua_metaObject[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" { unsigned char g_commonSettingsValid; }
extern "C" int g_beNDMWTitle2Info_metaObject[4];
extern "C" int g_bePadManager_metaObject[4];
extern "C" void beNDMWTitle2_Prepare(beNDMWTitle2 *self);
/* Outer state, CTRL._st0. */
enum TitleState {
    TitleStateWaitRun = 0,
    TitleStateLogo = 1,
    TitleStateMenu = 2,
    TitleStateOptions = 4,
    TitleStateFadeOut = 7,
    TitleStateLoadHandoff = 8
};
/* Direction bits of the pad's left-stick words (_lTrg, _lRpt). */
enum PadStickDirection { DirUp = 0x01, DirRight = 0x02, DirDown = 0x04, DirLeft = 0x08 };
/* Button bits of the pad's pressed (_trigger) and repeat (_repeat) words. */
enum PadButton {
    ButtonStart = 0x0008,
    ButtonUp = 0x0010,
    ButtonRight = 0x0020,
    ButtonDown = 0x0040,
    ButtonLeft = 0x0080,
    ButtonCircle = 0x2000,
    ButtonCross = 0x4000
};
/* Options window rows, "OPTION"._ctrlPos. Row 0 edits _comConf, row 1 _lightConf and row 2 the
 * country (only with _selLang != 0); row 3 confirms. */
enum OptionRow { OptionRowCamera = 0, OptionRowLight = 1, OptionRowCountry = 2, OptionRowOk = 3 };
enum TitleReferenceRole {
    TitleWorkList = 0,
    TitleControl = 1,
    TitleModels = 2,
    TitleOptions = 3,
    TitleText = 4
};
template <int Tag> struct TitleRef {
    void *p;
    TitleRef(void *v) : p(v) {}
    ~TitleRef() {
        igObject *o = (igObject *)p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)(long long)(int)o->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
    }
};
extern "C" void beNDMWTitle2_UpdateRam(beNDMWTitle2 *self, beBaseInfoRam *infoRam);
extern "C" void beNDMWTitle2_OnAddRam(beNDMWTitle2 *self, int info);
extern "C" int beNDMWTitle2_OnMessage(beNDMWTitle2 *self, beBaseInfoRam *ram, beMessengerWork *message);

/* Bind the messenger and load the Options settings. Once the title settings are valid, the saved
 * camera and light modes are read back from the GAMERAM GETCOMMON property group (property record
 * value at +12); otherwise the defaults are camera 0 and light 1. The language selector always
 * starts at 0. */
#pragma push
#pragma readonly_strings on

void beNDMWTitle2Option_InitSettings(beNDMWTitle2Option *self, int messenger) {
    int commonSettings;

    self->_messenger = messenger;
    if (g_commonSettingsValid == 1) {
        beMessenger_SendGroup(self->_messenger, "GAMERAM", "GETCOMMON");
        commonSettings = beMessenger_GetObject(self->_messenger, 0);
        self->_comConf = (int)((int) *(int *)((char *)(igProperty_GetRecord(commonSettings, "CAMERAMODE")) + 12));
        self->_lightConf = (int)((int) *(int *)((char *)(igProperty_GetRecord(commonSettings, "LIGHTMODE")) + 12));
        self->_selLang = 0;
        return;
    }
    self->_comConf = 0;
    self->_lightConf = 1;
    self->_selLang = 0;
}

/* The title-menu controller. vfunc_31 is the per-frame update: a four-level state machine
 * (CTRL._st0.._st3) that drives the logo, the Press START wait, the Game Start / Option menu, the
 * Options window and the hand-off to beNDMWLoadCtrl2. The numbers 0xf0001..0xf000d passed to the
 * text-order helper are Options text ids (0xf0001 header, 0xf0002/3 camera, 0xf0004/5 light,
 * 0xf0006 country header, 0xf0007..d country).
 * Matching constructs:
 *  - TitleRef<Tag> reproduces the five reference wrappers and their exception cleanup; the tags only
 *    keep otherwise identical destructors apart.
 *  - Local declaration order, the bool direction flags and the const state-field re-reads
 *    (`ctrl->_stN = stN(ctrl) + 1`) fix register allocation and reload points.
 *  - The two language locals (Up and Down handlers) are kept separate; merging them changes the
 *    register colouring. */

static inline int st1(const beNDMWTitle2CtrlData *data) { return data->_st1; }

static inline int st2(const beNDMWTitle2CtrlData *data) { return data->_st2; }

void beNDMWTitle2_Prepare(beNDMWTitle2 *self) {
    igObject *padManager;
    igObject *held;
    if (self->_padManager == 0) {
        padManager = (igObject *)igInsightCore_FindManager(self->_insight, g_bePadManager_metaObject[0]);
        if (padManager != 0) {
            padManager->_refCount = padManager->_refCount + 1;
        }
        held = (igObject *)self->_padManager;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if ((held->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(held);
            }
        }
        self->_padManager = (int)padManager;
    }
    held = (igObject *)self->_mcUtilCtrl;
    if (held != 0) {
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if ((held->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(held);
            }
        }
        self->_mcUtilCtrl = 0;
    }
}

/* Pick the allocator for a new object: the owner's own allocator when the
 * global flag at 0x00554c14 is set, otherwise the registry's default one. */

/* Store a reference-counted object as infoRam->_dataList, releasing the old list. */


/* per-frame title-menu update. Lazily builds the CTRL / COMMDLCTRL / "OPTION" / TEXTORDER objects in
 * the info record's property list, then runs the CTRL._st0.._st3 state machine. */
void beNDMWTitle2_UpdateRam(beNDMWTitle2 *self, beBaseInfoRam *infoRam) {
    int allocator;
    bool left;
    bool right;
    int stickDirs;
    int languageUp;
    int languageDown;
    int savedLightMode;
    int cameraMode;
    int commonSettings;
    int lightMode;
    int pressed;
    int savedCameraMode;
    int repeat;
    int rowUp;
    int rowDown;
    bool up;
    bool down;
    int nextComConf;
    int nextLightConf;
    int nextCountryLang1;
    int nextCountryLang2;
    int prevComConf;
    int prevLightConf;
    int prevCountryLang1;
    int prevCountryLang2;
    beNDMWTitle2CtrlData *ctrl;
    beNDMWLoadIntf2ComMdlCtrl *models;
    beNDMWLoadIntf2TextOrder *text;
    beNDMWTitle2Option *option;
    bePadData *pad;

    if (infoRam->_dataList == 0) {
        ALLOC(allocator, self);
        TitleRef<TitleWorkList> workListRef(beBaseInfoDataList_Create(allocator));
        SET_DATA(workListRef);
        ALLOC(allocator, self);
        TitleRef<TitleControl> ctrlRef(beNDMWTitle2CtrlData_Create(allocator));
        ObjectList_AppendRetained(infoRam->_dataList, ctrlRef.p);
        ALLOC(allocator, self);
        {
            TitleRef<TitleModels> modelsRef(beNDMWLoadIntf2ComMdlCtrl_Create(allocator));
            ObjectList_AppendRetained(infoRam->_dataList, modelsRef.p);
            ((beNDMWLoadIntf2ComMdlCtrl *)modelsRef.p)->_messenger = self->_messenger;
        }
        ALLOC(allocator, self);
        {
            TitleRef<TitleOptions> optionRef(beNDMWTitle2Option_Create(allocator));
            beNDMWTitle2Option_InitSettings((beNDMWTitle2Option *)optionRef.p, (int)self->_messenger);
            ObjectList_AppendRetained(infoRam->_dataList, optionRef.p);
        }
        ALLOC(allocator, self);
        {
            TitleRef<TitleText> textRef(beNDMWLoadIntf2TextOrder_Create(allocator));
            ((beNDMWLoadIntf2TextOrder *)textRef.p)->_messenger = self->_messenger;
            beNDMWLoadIntf2TextOrder *textOrder = (beNDMWLoadIntf2TextOrder *)textRef.p;
            textOrder->_lua = igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]);
            ObjectList_AppendRetained(infoRam->_dataList, textRef.p);
        }
    }
    if (infoRam->_dataList == 0) {
        ALLOC(allocator, infoRam);
        TitleRef<TitleWorkList> workListRef(beBaseInfoDataList_Create(allocator));
        SET_DATA(workListRef);
    }
    ctrl = (beNDMWTitle2CtrlData *)(igProperty_FindByName(infoRam->_dataList, g_propertyNameField[0],
                                                          "CTRL"));
    if (infoRam->_dataList == 0) {
        ALLOC(allocator, infoRam);
        TitleRef<TitleWorkList> workListRef(beBaseInfoDataList_Create(allocator));
        SET_DATA(workListRef);
    }
    models = (beNDMWLoadIntf2ComMdlCtrl *)(igProperty_FindByName(infoRam->_dataList, g_propertyNameField[0], "COMMDLCTRL"));
    if (infoRam->_dataList == 0) {
        ALLOC(allocator, infoRam);
        TitleRef<TitleWorkList> workListRef(beBaseInfoDataList_Create(allocator));
        SET_DATA(workListRef);
    }
    text = (beNDMWLoadIntf2TextOrder *)(igProperty_FindByName(infoRam->_dataList, g_propertyNameField[0], "TEXTORDER"));
    beNDMWLoadIntf2ComMdlCtrl__Poll(models);
    pad = (bePadData *)(bePadManager_GetPadForPlayer(self->_padManager, 0));
    pressed = pad->_trigger;
    left = 1;
    stickDirs = pad->_lTrg | pad->_lRpt;
    repeat = pad->_repeat;
    if (!(stickDirs & DirLeft) && !((pressed | repeat) & ButtonLeft)) {
        left = 0;
    }
    right = 1;
    if (!(stickDirs & DirRight) && !((pressed | repeat) & ButtonRight)) {
        right = 0;
    }
    up = 1;
    if (!(stickDirs & DirUp) && !((pressed | repeat) & ButtonUp)) {
        up = 0;
    }
    down = 1;
    if (!(stickDirs & DirDown) && !((pressed | repeat) & ButtonDown)) {
        down = 0;
    }
    switch (ctrl->_st0) {
    case TitleStateWaitRun: /* Wait for TITLE2 RUN. */
        if (infoRam->_st0 == 1) {
            ctrl->_st0 = TitleStateLogo;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            ctrl->_st1 = 0;
            goto done;
        }
        break;
    case TitleStateLogo: /* Logo, Press START and the attract-loop handoff. */
        switch (ctrl->_st1) {
        case 0:
            ctrl->_st1 = st1(ctrl) + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            goto done;
        case 1:
            switch (ctrl->_st2) {
            case 0:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, "j_startlogo") & 0xFF) != 1) {
                    beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_startlogo", "SQ_OPEN", 1);
                }
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    goto done;
                }
                break;
            }
            break;
        case 2:
            switch (ctrl->_st2) {
            case 0:
                switch (ctrl->_st3) {
                case 0:
                    beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_startmenu01", "SQ_OPEN", 1);
                    ctrl->_st3 = ctrl->_st3 + 1;
                    goto done;
                case 1:
                    if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    }
                    break;
                }
                break;
            case 1:
                switch (ctrl->_st3) {
                case 0x0:
                    if (pressed & ButtonStart) {
                        ctrl->_st2 = st2(ctrl) + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    }
                    beMessenger_SelectReceivers(self->_messenger, "MODELCTRL",
                                                "j_startmenu01", 0, 1);
                    beMessenger_AppendString(self->_messenger, "SQ_LINESL00");
                    beMessenger_DispatchSelected(self->_messenger, "ISSEQNAME");
                    if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                        ctrl->_st3 = 0x3E8;
                        goto done;
                    }
                    break;
                case 0x3E8:
                    ctrl->_st3 = 0x3E9;
                    beMessenger_SendNamed(self->_messenger, "MODELCTRL", "i_fadewn01", 0,
                                          "GENERATE");
                    beMessenger_SendNamed(self->_messenger, "MODELCTRL", "i_fadewn01", 0,
                                          "SQ_BLOUT30");
                    goto done;
                case 0x3E9:
                    beMessenger_SendNamed(self->_messenger, "MODELCTRL", "j_startmenu01", 0,
                                          "ISRUN");
                    if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
                        ctrl->_st3 = 0x3EA;
                        goto done;
                    }
                    break;
                case 0x3EA:
                    beMessenger_SelectGroup(self->_messenger, "STAGECTL");
                    beMessenger_AppendString(self->_messenger, "stagIS09");
                    beMessenger_DispatchSelected(self->_messenger, "NEXTSTAGE");
                    ctrl->_st3 = 0x3EB;
                    goto done;
                case 0x3EB:
                    goto done;
                }
                break;
            case 2:
                switch (ctrl->_st3) {
                case 0:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_startmenu01", "SQ_LINEON00", 1);
                    ctrl->_st3 = ctrl->_st3 + 1;
                    goto done;
                case 1:
                    if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                        ctrl->_st0 = TitleStateMenu;
                        ctrl->_st3 = 0;
                        ctrl->_st2 = 0;
                        ctrl->_st1 = 0;
                        goto done;
                    }
                    break;
                }
                break;
            }
            break;
        case 3:
        case 4:
            goto done;
        }
        break;
    case TitleStateMenu: /* Game Start / Option menu. */
        switch (ctrl->_st1) {
        case 0:
            switch (ctrl->_st2) {
            case 0:
                beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_startmenu02", "SQ_OPEN", 1);
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    goto done;
                }
                break;
            }
            break;
        case 1:
            switch (ctrl->_st2) {
            case 0:
                ctrl->_gameMenuCnt = 0;
                ctrl->_gameMenuNext = 0;
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if (up) {
                    if (ctrl->_gameMenuCnt == 1) {
                        ctrl->_gameMenuCnt = 0;
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_startmenu02", "SQ_LINEUP00", 1);
                    }
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    goto done;
                }
                if (down) {
                    if (ctrl->_gameMenuCnt == 0) {
                        ctrl->_gameMenuCnt = 1;
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_startmenu02", "SQ_LINEDW01", 1);
                    }
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    goto done;
                }
                if (pressed & ButtonCross) {
                    if (ctrl->_gameMenuCnt == 0) {
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_startmenu02", "SQ_LINEON00", 1);
                        ctrl->_gameMenuNext = 1;
                    } else {
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_startmenu02", "SQ_LINEON01", 1);
                        ctrl->_gameMenuNext = 2;
                    }
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    goto done;
                }
                if (pressed & ButtonCircle) {
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_startmenu02", "SQ_CANCEL", 1);
                    ctrl->_st2 = 3;
                    ctrl->_st3 = 0;
                    goto done;
                }
                break;
            case 2:
                switch (ctrl->_st3) {
                case 0:
                    if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                        switch (ctrl->_gameMenuNext) {
                        case 0:
                            ctrl->_st2 = 1;
                            ctrl->_st3 = 0;
                            goto done;
                        case 1:
                        case 2:
                            beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_startlogo", "SQ_CLOSE", 1);
                            ctrl->_st3 = ctrl->_st3 + 1;
                            goto done;
                        case 3:
                            ctrl->_st0 = TitleStateLogo;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                            ctrl->_st1 = 0;
                            goto done;
                        }
                    }
                    break;
                case 1:
                    if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                        switch (ctrl->_gameMenuNext) {
                        case 1:
                            ctrl->_st0 = TitleStateFadeOut;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                            ctrl->_st1 = 0;
                            goto done;
                        case 2:
                            ctrl->_st0 = TitleStateOptions;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                            ctrl->_st1 = 0;
                            goto done;
                        }
                    }
                    break;
                }
                break;
            case 3:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                    ctrl->_st0 = TitleStateLogo;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                    goto done;
                }
                break;
            }
            break;
        }
        break;
    case TitleStateOptions: /* Options and saved-setting publication. */
        if (infoRam->_dataList == 0) {
            ALLOC(allocator, infoRam);
            TitleRef<TitleWorkList> workListRef(beBaseInfoDataList_Create(allocator));
            SET_DATA(workListRef);
        }
        option = (beNDMWTitle2Option *)(igProperty_FindByName(infoRam->_dataList, g_propertyNameField[0],
                                                              "OPTION"));
        switch (ctrl->_st1) {
        case 0:
            switch (ctrl->_st2) {
            case 0:
                if (option->_comConf == 0) {
                    option->_dispComConf = 0;
                } else {
                    option->_dispComConf = 1;
                }
                if (option->_lightConf == 0) {
                    option->_dispLightConf = 0;
                } else {
                    option->_dispLightConf = 1;
                }
                option->_oldCountry = 1;
                option->_dispCountryConf = 1U;
                switch (option->_selLang) {
                case 0:
                    beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_optionwin02", "SQ_BOPEN", 1);
                    break;
                case 1:
                case 2:
                    beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_optionwin02", "SQ_AOPEN", 1);
                    break;
                }
                beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_optioncursor11", "SQ_OPEN", 1);
                beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_optioncursor12", "SQ_OPEN", 1);
                option->_ctrlPos = 0;
                option->_isOK = 0U;
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                    beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0001, 0);
                    if (option->_selLang != 0) {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0006, 0);
                        switch (option->_dispCountryConf) {
                        default:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0007, 0);
                            break;
                        case 1:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0008, 0);
                            break;
                        case 2:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0009, 0);
                            break;
                        case 3:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF000A, 0);
                            break;
                        case 4:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF000C, 0);
                            break;
                        case 5:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF000B, 0);
                            break;
                        case 6:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF000D, 0);
                            break;
                        }
                    }
                    if (option->_dispComConf == 0) {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0002, 0);
                    } else {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0003, 0);
                    }
                    if (option->_dispLightConf == 0) {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0004, 0);
                    } else {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0005, 0);
                    }
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    goto done;
                }
                break;
            }
            break;
        case 1:
            switch (ctrl->_st2) {
            case 0:
                if (up) {
                    languageUp = option->_selLang;
                    rowUp = option->_ctrlPos;
                    switch (languageUp) {
                    case 0:
                        if (rowUp == OptionRowOk) {
                            rowUp = OptionRowLight;
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor11", "SQ_MOVE", 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
                            ctrl->_st3 = 0;
                        } else if (rowUp != 0) {
                            rowUp = 0;
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor11", "SQ_MOVE", 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
                            ctrl->_st3 = 0;
                        }
                        break;
                    case 1:
                    case 2:
                        rowUp -= 1;
                        if (rowUp < 0) {
                            rowUp = 0;
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor11", "SQ_MOVE", 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
                            ctrl->_st3 = 0;
                        }
                        break;
                    }
                    option->_ctrlPos = rowUp;
                    goto done;
                }
                if (down) {
                    languageDown = option->_selLang;
                    rowDown = option->_ctrlPos;
                    switch (languageDown) {
                    case 0:
                        if ((rowDown + 1) == 2) {
                            rowDown = OptionRowOk;
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor11", "SQ_MOVE", 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
                            ctrl->_st3 = 0;
                            break;
                        }
                    case 1:
                    case 2:
                        rowDown += 1;
                        if (rowDown > OptionRowOk) {
                            rowDown = OptionRowOk;
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor11", "SQ_MOVE", 1);
                            ctrl->_st2 = ctrl->_st2 + 1;
                            ctrl->_st3 = 0;
                        }
                        break;
                    }
                    option->_ctrlPos = rowDown;
                    goto done;
                }
                if (right) {
                    switch (option->_ctrlPos) {
                    case OptionRowCamera:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor12", "SQ_LINERT00", 1);
                        nextComConf = option->_dispComConf + 1;
                        if (nextComConf > 1) {
                            nextComConf = 0;
                        }
                        option->_dispComConf = nextComConf;
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowLight:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor12", "SQ_LINERT01", 1);
                        nextLightConf = option->_dispLightConf + 1;
                        if (nextLightConf > 1) {
                            nextLightConf = 0;
                        }
                        option->_dispLightConf = nextLightConf;
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowCountry:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor12", "SQ_LINERT02", 1);
                        switch (option->_selLang) {
                        case 1:
                            nextCountryLang1 = option->_dispCountryConf + 1;
                            if (nextCountryLang1 > 6) {
                                nextCountryLang1 = 2;
                            }
                            option->_dispCountryConf = (int)((unsigned int)nextCountryLang1);
                            break;
                        case 2:
                            nextCountryLang2 = option->_dispCountryConf + 1;
                            if (nextCountryLang2 > 6) {
                                nextCountryLang2 = 0;
                            }
                            option->_dispCountryConf = (int)((unsigned int)nextCountryLang2);
                            break;
                        }
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowOk:
                        goto done;
                    }
                } else if (left) {
                    switch (option->_ctrlPos) {
                    case OptionRowCamera:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor12", "SQ_LINELF00", 1);
                        prevComConf = option->_dispComConf - 1;
                        if (prevComConf < 0) {
                            prevComConf = 1;
                        }
                        option->_dispComConf = prevComConf;
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowLight:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor12", "SQ_LINELF01", 1);
                        prevLightConf = option->_dispLightConf - 1;
                        if (prevLightConf < 0) {
                            prevLightConf = 1;
                        }
                        option->_dispLightConf = prevLightConf;
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowCountry:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor12", "SQ_LINELF02", 1);
                        switch (option->_selLang) {
                        case 1:
                            prevCountryLang1 = option->_dispCountryConf - 1;
                            if (prevCountryLang1 < 2) {
                                prevCountryLang1 = 6;
                            }
                            option->_dispCountryConf = (int)((unsigned int)prevCountryLang1);
                            break;
                        case 2:
                            prevCountryLang2 = option->_dispCountryConf - 1;
                            if (prevCountryLang2 < 0) {
                                prevCountryLang2 = 6;
                            }
                            option->_dispCountryConf = (int)((unsigned int)prevCountryLang2);
                            break;
                        }
                        ctrl->_st2 = ctrl->_st2 + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowOk:
                        goto done;
                    }
                } else {
                    if (pressed & ButtonCross) {
                        switch (option->_ctrlPos) {
                        case OptionRowOk:
                            option->_isOK = 1U;
                            ctrl->_st1 = ctrl->_st1 + 1;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                            goto done;
                        }
                        goto done;
                    }
                    if (pressed & ButtonCircle) {
                        option->_isOK = 1U;
                        ctrl->_st1 = ctrl->_st1 + 1;
                        ctrl->_st3 = 0;
                        ctrl->_st2 = 0;
                        goto done;
                    }
                }
                break;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                    switch (option->_ctrlPos) {
                    case OptionRowCamera:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor11", "SQ_LINESL00", 0);
                        break;
                    case OptionRowLight:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor11", "SQ_LINESL01", 0);
                        break;
                    case OptionRowCountry:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor11", "SQ_LINESL02", 0);
                        break;
                    case OptionRowOk:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor11", "SQ_LINESL03", 0);
                        break;
                    }
                    switch (option->_ctrlPos) {
                    case OptionRowCamera:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, "j_optioncursor12") & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor12", "SQ_LINESL00", 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_optioncursor12", "SQ_LINESL00", 0);
                        }
                        break;
                    case OptionRowLight:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, "j_optioncursor12") & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor12", "SQ_LINESL01", 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_optioncursor12", "SQ_LINESL01", 0);
                        }
                        break;
                    case OptionRowCountry:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, "j_optioncursor12") & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, "j_optioncursor12", "SQ_LINESL02", 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_optioncursor12", "SQ_LINESL02", 0);
                        }
                        break;
                    case OptionRowOk:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, "j_optioncursor12") & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_optioncursor12", "SQ_CLOSE", 0);
                        }
                        break;
                    }
                    if (option->_selLang != 0) {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0006, 0);
                        switch (option->_dispCountryConf) {
                        default:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0007, 0);
                            break;
                        case 1:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0008, 0);
                            break;
                        case 2:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0009, 0);
                            break;
                        case 3:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF000A, 0);
                            break;
                        case 4:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF000C, 0);
                            break;
                        case 5:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF000B, 0);
                            break;
                        case 6:
                            beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF000D, 0);
                            break;
                        }
                    }
                    if (option->_dispComConf == 0) {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0002, 0);
                    } else {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0003, 0);
                    }
                    if (option->_dispLightConf == 0) {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0004, 0);
                    } else {
                        beNDMWLoadIntf2TextOrder_PublishIdLines(text, 0xF0005, 0);
                    }
                    ctrl->_st2 = 0;
                    ctrl->_st3 = 0;
                    goto done;
                }
                break;
            }
            break;
        case 2:
            switch (ctrl->_st2) {
            case 0:
                switch (option->_ctrlPos) {
                case OptionRowCamera:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_optioncursor11", "SQ_LINEON00", 1);
                    break;
                case OptionRowLight:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_optioncursor11", "SQ_LINEON01", 1);
                    break;
                case OptionRowCountry:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_optioncursor11", "SQ_LINEON02", 1);
                    break;
                case OptionRowOk:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_optioncursor11", "SQ_LINEON03", 1);
                    break;
                }
                switch (option->_ctrlPos) {
                case OptionRowCamera:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_optioncursor12", "SQ_CLOSE", 1);
                    break;
                case OptionRowLight:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_optioncursor12", "SQ_CLOSE", 1);
                    break;
                case OptionRowCountry:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_optioncursor12", "SQ_CLOSE", 1);
                    break;
                }
                TextOrder_PublishLineListOnly(text, 0xF0001);
                if (option->_selLang != 0) {
                    TextOrder_PublishLineListOnly(text, 0xF0006);
                    TextOrder_PublishLineListOnly(text, 0xF000D);
                }
                TextOrder_PublishLineListOnly(text, 0xF0002);
                TextOrder_PublishLineListOnly(text, 0xF0005);
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                    ctrl->_st2 = ctrl->_st2 + 1;
                    ctrl->_st3 = 0;
                    goto done;
                }
                break;
            case 2:
                beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_optionwin02", "SQ_CLOSE", 1);
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                goto done;
            case 3:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                    if (option->_isOK == 1) {
                        option->_comConf = (int)((int)option->_dispComConf);
                        option->_lightConf = (int)((int)option->_dispLightConf);
                    }
                    if (option->_oldCountry != 1) {
                        ctrl->_st1 = 0x32;
                        ctrl->_st3 = 0;
                        ctrl->_st2 = 0;
                        goto done;
                    }
                    ctrl->_st1 = ctrl->_st1 + 1;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    goto done;
                }
                break;
            }
            break;
        case 3:
            switch (ctrl->_st2) {
            case 0:
                beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "j_startlogo", "SQ_OPEN", 1);
                ctrl->_st2 = ctrl->_st2 + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                    ctrl->_st0 = TitleStateMenu;
                    ctrl->_st3 = 0;
                    ctrl->_st2 = 0;
                    ctrl->_st1 = 0;
                    goto done;
                }
                break;
            }
            break;
        case 50:
            switch (ctrl->_st2) {
            case 0:
                ctrl->_st2 = 1;
                ctrl->_st3 = 0;
                beMessenger_SendNamed(self->_messenger, "MODELCTRL", "i_fadewn01", 0,
                                      "GENERATE");
                beMessenger_SendNamed(self->_messenger, "MODELCTRL", "i_fadewn01", 0,
                                      "SQ_BLOUT30");
                goto done;
            case 1:
                beMessenger_SendNamed(self->_messenger, "MODELCTRL", "j_startmenu01", 0,
                                      "ISRUN");
                if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
                    ctrl->_st2 = 2;
                    ctrl->_st3 = 0;
                    goto done;
                }
                break;
            case 2:
                beMessenger_SendGroup(self->_messenger, "GAMERAM", "GETCOMMON");
                commonSettings = beMessenger_GetObject(self->_messenger, 0);
                savedCameraMode = option->_comConf;
                savedLightMode = option->_lightConf;
                /* Write the saved settings back into the GAMERAM common-settings records
                 * (value word at record +12). */
                *(int *)((char *)(igProperty_GetRecord(commonSettings, "CAMERAMODE")) + 12) =
                    savedCameraMode;
                *(int *)((char *)(igProperty_GetRecord(commonSettings, "LIGHTMODE")) + 12) =
                    savedLightMode;
                g_commonSettingsValid = 1;
                beMessenger_SendNamed(self->_messenger, "SOUND", 0, -1, "BGMSTOP");
                beMessenger_SendNamed(self->_messenger, "SOUND", 0, -1, "ENVSTOP");
                beMessenger_SendNamed(self->_messenger, "SOUND", 0, -1, "SESTOP");
                beMessenger_SelectGroup(self->_messenger, "STAGECTL");
                beMessenger_AppendString(self->_messenger, "stagIS08");
                beMessenger_DispatchSelected(self->_messenger, "NEXTSTAGE");
                ctrl->_st2 = 3;
                ctrl->_st3 = 0;
                goto done;
            case 3:
                goto done;
            }
            break;
        }
        break;
    case TitleStateFadeOut: /* Fade out for Game Start. */
        switch (ctrl->_st1) {
        case 0:
            beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, "i_fadewn01", "SQ_WTOUT60", 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, "j_startback", "SQ_CLOSE", 1);
            ctrl->_st1 = ctrl->_st1 + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            goto done;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                ctrl->_st0 = TitleStateLoadHandoff;
                ctrl->_st3 = 0;
                ctrl->_st2 = 0;
                ctrl->_st1 = 0;
                goto done;
            }
            break;
        }
        break;
    case TitleStateLoadHandoff: /* LOADCTRL2 GENERATE_TITLE handoff. */
        switch (ctrl->_st1) {
        case 0:
            if (infoRam->_dataList == 0) {
                ALLOC(allocator, infoRam);
                TitleRef<TitleWorkList> workListRef(beBaseInfoDataList_Create(allocator));
                SET_DATA(workListRef);
            }
            option = (beNDMWTitle2Option *)(igProperty_FindByName(infoRam->_dataList, g_propertyNameField[0],
                                                       "OPTION"));
            cameraMode = option->_comConf;
            lightMode = option->_lightConf;
            beMessenger_SelectReceivers(self->_messenger, "LOADCTRL2", 0, 0);
            beMessenger_AppendInt(self->_messenger, cameraMode);
            beMessenger_AppendInt(self->_messenger, lightMode);
            beMessenger_DispatchSelected(self->_messenger, "GENERATE_TITLE");
            ctrl->_st1 = ctrl->_st1 + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            break;
        case 1:
            goto done;
        }
        break;
    /* Jump-table entries 3, 5, 6 and 9 are inert. */
    case 3:
    case 5:
    case 6:
    case 9:
    default:
        goto done;
    }
done:
    return;
}

int beNDMWTitle2_GetInfoMeta(void)
{
    return g_beNDMWTitle2Info_metaObject[0];
}

/* Slot 29: register the controller as the TITLE2 message receiver. */
void beNDMWTitle2_OnAddRam(beNDMWTitle2 *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, "TITLE2");
}

int beNDMWTitle2_OnMessage(beNDMWTitle2 *self, beBaseInfoRam *ram, beMessengerWork *message) {
    int command;

    if (ram->_dataList == 0) {
        return 1;
    }
    command = beMessenger_ResolveEnumValue(self->_messenger, beNDMWTitle2CtrlData_GetMessageEnum(), message->_message);
    switch (command) {
    case 0:
        ram->_st0 = 1;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        break;
    case 1:
        g_commonSettingsValid = 1;
        break;
    }
    return 1;
}

int beNDMWTitle2_GetMeta(void)
{
    return (int)g_beNDMWTitle2_metaObject;
}

#pragma pop
