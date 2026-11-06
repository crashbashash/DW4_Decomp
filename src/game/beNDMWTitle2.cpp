/* beNDMWTitle2, the title-menu controller (0x003f2d50..0x003f540c), one translation unit in retail
 * address order: 0x003f2e00 Gap__Bec__beNDMWTitle2__vfunc_32 resolve the pad manager, release the
 * MC utility 0x003f2ef0 Gap__Bec__beNDMWTitle2__vfunc_31 per-frame update (state machine)
 * 0x003f5310 Gap__Bec__beNDMWTitle2__vfunc_30 info-record class metaObject accessor 0x003f5320
 * Gap__Bec__beNDMWTitle2__vfunc_29 register the TITLE2 message receiver 0x003f5400
 * Gap__Bec__beNDMWTitle2__vfunc_20 class metaObject accessor The retail unit was C++ with
 * exceptions on. vfunc_32, vfunc_30 and vfunc_20 used to live in beNDMWTitle2.c; they now compile
 * here as C++ under that profile, which also reproduces vfunc_32's exception index record. The
 * whole unit keeps C linkage. vfunc_31 (0x003f2ef0) is the per-frame update: a four-level state
 * machine (CTRL._st0.._st3) that drives the logo, the Press START wait, the Game Start / Option
 * menu, the Options window and the hand-off to beNDMWLoadCtrl2. The state values and the pad words
 * it reads are documented in docs/engine/title-menu-controller.md. The string externs are the
 * model-control sequence and message names it sends; the numbers 0xf0001.. 0xf000d passed to the
 * text-order helper are Options text ids (0xf0001 header, 0xf0002/3 camera, 0xf0004/5 light,
 * 0xf0006 country header, 0xf0007..d country). Matching constructs (the pinned compiler is
 * sensitive to all of these): - TitleRef<Tag> reproduces the five reference wrappers and their
 * exception cleanup; the tags only keep otherwise identical destructors apart. - Local declaration
 * order, the bool direction flags and the volatile state-field re-reads (`ctrl->_stN = (*(volatile
 * int *)&ctrl->_stN) + 1`, the advance-to-next-step idiom) fix register allocation and reload
 * points. - The two language locals (Up and Down handlers) are kept separate; merging them changes
 * the register colouring. - Address-named externs only fix the access; their C types are not
 * recovered. vfunc_29 (0x003f5320) registers the controller as the TITLE2 message receiver. */
#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(...);
void *beBaseInfoDataList_Create(...);
void *FUN_003b2250(...);
void *FUN_003b2560(...);
void *beNDMWLoadIntf2ComMdlCtrl_Create(...);
void *beNDMWLoadIntf2TextOrder_Create(...);
int beNDMWLoadIntf2ComMdlCtrl__Start(...);
int beNDMWLoadIntf2ComMdlCtrl__Play(...);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
int beNDMWLoadIntf2ComMdlCtrl__Close(...);
int beNDMWLoadIntf2ComMdlCtrl__IsRunning(...);
int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(...);
int beNDMWLoadIntf2ComMdlCtrl__Poll(...);
int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
int TextOrder_PublishLineListOnly(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBool(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
int beMessenger_SendGroup(...);
int beMessenger_SendNamed(...);
int beNDMWTitle2Option_InitSettings(...);
void *bePadManager_GetPadForPlayer(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void *igProperty_FindByName(...);
void *igProperty_GetRecord(...);
extern int GAMERAM_3[4];
extern int GETCOMMON_2[4];
extern int CAMERAMODE_2[4];
extern int LIGHTMODE_2[4];
extern int CTRL_2[4];
extern int COMMDLCTRL_2[4];
extern int TEXTORDER_2[4];
extern int j_startlogo[4];
extern int SQ_OPEN_2[4];
extern int j_startmenu01[4];
extern int MODELCTRL_2[4];
extern int SQ_LINESL00_2[4];
extern int ISSEQNAME_2[4];
extern int i_fadewn01[4];
extern int GENERATE_2[4];
extern int SQ_BLOUT30[4];
extern int ISRUN_2[4];
extern int STAGECTL[4];
extern int stagIS09[4];
extern int NEXTSTAGE[4];
extern int SQ_LINEON00_2[4];
extern int j_startmenu02[4];
extern int SQ_LINEUP00_2[4];
extern int SQ_LINEDW01_2[4];
extern int SQ_LINEON01_2[4];
extern int SQ_CANCEL_2[4];
extern int SQ_CLOSE_2[4];
extern int OPTION[4];
extern int j_optionwin02[4];
extern int SQ_BOPEN[4];
extern int SQ_AOPEN[4];
extern int j_optioncursor11[4];
extern int j_optioncursor12[4];
extern int SQ_MOVE[4];
extern int SQ_LINERT00[4];
extern int SQ_LINERT01[4];
extern int SQ_LINERT02[4];
extern int SQ_LINELF00[4];
extern int SQ_LINELF01[4];
extern int SQ_LINELF02[4];
extern int SQ_LINESL01[4];
extern int SQ_LINESL02[4];
extern int SQ_LINESL03[4];
extern int SQ_LINEON02[4];
extern int SQ_LINEON03[4];
extern int SOUND[4];
extern int BGMSTOP[4];
extern int ENVSTOP[4];
extern int SESTOP[4];
extern int stagIS08[4];
extern int SQ_WTOUT60[4];
extern int j_startback[4];
extern int LOADCTRL2_2[4];
extern int GENERATE_TITLE[4];
extern int g_propertyNameField[4];
extern int g_defaultAllocatorSelector[4];
extern int g_beLua_metaObject[4];
/* Byte flag: allocate from the owner's allocator. */
extern unsigned char g_useOwnerAllocator;
/* Set by the GAMESTART path; tells the Options initialiser that GAMERAM's CAMERAMODE/LIGHTMODE are
 * valid. */
extern char g_commonSettingsValid;
extern int g_beNDMWTitle2Info_metaObject[4];
extern int g_beNDMWTitle2_metaObject[4];
extern int g_bePadManager_metaObject[4];
extern int TITLE2[4];
/* igObject_Destroy (0x002ff820): called when a reference count reaches zero.  Declared and
 * called without its argument in vfunc_32: retail's a0 still holds the released object
 * (matching construct). */
int FUN_002ff820();
int beMessenger_RegisterReceiverFromInfo(int, int, int *);

void Gap__Bec__beNDMWTitle2__vfunc_32(beNDMWTitle2 *);
void Gap__Bec__beNDMWTitle2__vfunc_31(beNDMWTitle2 *, beBaseInfoRam *);
int Gap__Bec__beNDMWTitle2__vfunc_30(void);
void Gap__Bec__beNDMWTitle2__vfunc_29(beNDMWTitle2 *, int);
int Gap__Bec__beNDMWTitle2__vfunc_20(void);
}

/* Resolves the pad manager on first use, and releases the cached memory-card utility controller.
 * References are counted in the low 23 bits of _refCount. The `asm { nop }` statements reproduce
 * retail's delay-slot nops after each call and store, and the repeated null test on the held
 * reference reproduces retail's inlined release-then-clear sequence; they are matching constructs,
 * not code. */
void Gap__Bec__beNDMWTitle2__vfunc_32(beNDMWTitle2 *self) {
    igObject *padManager;
    igObject *held;
    if (self->_padManager == 0) {
        padManager = (igObject *)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
        if (padManager != 0) {
            padManager->_refCount = padManager->_refCount + 1;
            asm { nop }
        }
        held = (igObject *)self->_padManager;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if ((held->_refCount & 0x7fffff) == 0) {
                FUN_002ff820();
                asm { nop }
            }
        }
        self->_padManager = (int)padManager;
        asm { nop }
    }
    held = (igObject *)self->_mcUtilCtrl;
    if (held != 0) {
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if ((held->_refCount & 0x7fffff) == 0) {
                FUN_002ff820();
                asm { nop }
            }
        }
        self->_mcUtilCtrl = 0;
        asm { nop }
    }
}
/* Outer state, CTRL._st0. Values and behaviour: docs/engine/title-menu-controller.md. */
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

/* Options window rows, OPTION._ctrlPos. Row 0 edits _comConf, row 1 _lightConf and
 * row 2 the country (only with _selLang != 0); row 3 confirms. See the Options
 * section of docs/engine/title-menu-controller.md. */
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
/* Pick the allocator for a new object: the owner's own allocator when the
 * global flag at 0x00554c14 is set, otherwise the registry's default one. */
#define ALLOC(dst, obj)                                                                            \
    {                                                                                              \
        int alloc = igObject_GetAllocator(obj);                                                    \
        if (g_useOwnerAllocator != 0) {                                                                   \
            dst = alloc;                                                                           \
        } else {                                                                                   \
            dst = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);                                  \
        }                                                                                          \
    }
/* Store a reference-counted object as infoRam->_dataList, releasing the old list. */
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

/* per-frame title-menu update. Lazily builds the CTRL / COMMDLCTRL / OPTION / TEXTORDER objects in
 * the info record's property list, then runs the CTRL._st0.._st3 state machine. */
#pragma opt_propagation on
void Gap__Bec__beNDMWTitle2__vfunc_31(beNDMWTitle2 *self, beBaseInfoRam *infoRam) {
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
        TitleRef<TitleControl> ctrlRef(FUN_003b2560(allocator));
        ObjectList_AppendRetained(infoRam->_dataList, ctrlRef.p);
        ALLOC(allocator, self);
        {
            TitleRef<TitleModels> modelsRef(beNDMWLoadIntf2ComMdlCtrl_Create(allocator));
            ObjectList_AppendRetained(infoRam->_dataList, modelsRef.p);
            ((beNDMWLoadIntf2ComMdlCtrl *)modelsRef.p)->_messenger = self->_messenger;
        }
        ALLOC(allocator, self);
        {
            TitleRef<TitleOptions> optionRef(FUN_003b2250(allocator));
            beNDMWTitle2Option_InitSettings(optionRef.p, self->_messenger);
            ObjectList_AppendRetained(infoRam->_dataList, optionRef.p);
        }
        ALLOC(allocator, self);
        {
            TitleRef<TitleText> textRef(beNDMWLoadIntf2TextOrder_Create(allocator));
            ((beNDMWLoadIntf2TextOrder *)textRef.p)->_messenger = self->_messenger;
            beNDMWLoadIntf2TextOrder *textOrder = (beNDMWLoadIntf2TextOrder *)textRef.p;
            textOrder->_lua = FUN_00236f80(self->_insight, g_beLua_metaObject[0]);
            ObjectList_AppendRetained(infoRam->_dataList, textRef.p);
        }
    }
    if (infoRam->_dataList == 0) {
        ALLOC(allocator, infoRam);
        TitleRef<TitleWorkList> workListRef(beBaseInfoDataList_Create(allocator));
        SET_DATA(workListRef);
    }
    ctrl = (beNDMWTitle2CtrlData *)(igProperty_FindByName(infoRam->_dataList, g_propertyNameField[0],
                                                          &CTRL_2[0]));
    if (infoRam->_dataList == 0) {
        ALLOC(allocator, infoRam);
        TitleRef<TitleWorkList> workListRef(beBaseInfoDataList_Create(allocator));
        SET_DATA(workListRef);
    }
    models = (beNDMWLoadIntf2ComMdlCtrl *)(igProperty_FindByName(infoRam->_dataList, g_propertyNameField[0], &COMMDLCTRL_2[0]));
    if (infoRam->_dataList == 0) {
        ALLOC(allocator, infoRam);
        TitleRef<TitleWorkList> workListRef(beBaseInfoDataList_Create(allocator));
        SET_DATA(workListRef);
    }
    text = (beNDMWLoadIntf2TextOrder *)(igProperty_FindByName(infoRam->_dataList, g_propertyNameField[0], &TEXTORDER_2[0]));
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
            ctrl->_st1 = (*(volatile int *)&ctrl->_st1) + 1;
            ctrl->_st3 = 0;
            ctrl->_st2 = 0;
            goto done;
        case 1:
            switch (ctrl->_st2) {
            case 0:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, &j_startlogo[0]) & 0xFF) != 1) {
                    beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_startlogo[0], &SQ_OPEN_2[0], 1);
                }
                ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                    ctrl->_st1 = (*(volatile int *)&ctrl->_st1) + 1;
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
                    beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_startmenu01[0], &SQ_OPEN_2[0], 1);
                    ctrl->_st3 = (*(volatile int *)&ctrl->_st3) + 1;
                    goto done;
                case 1:
                    if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                        ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
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
                        ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    }
                    beMessenger_SelectReceivers(self->_messenger, &MODELCTRL_2[0],
                                                &j_startmenu01[0], 0, 1);
                    beMessenger_AppendString(self->_messenger, &SQ_LINESL00_2[0]);
                    beMessenger_DispatchSelected(self->_messenger, &ISSEQNAME_2[0]);
                    if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                        ctrl->_st3 = 0x3E8;
                        goto done;
                    }
                    break;
                case 0x3E8:
                    ctrl->_st3 = 0x3E9;
                    beMessenger_SendNamed(self->_messenger, &MODELCTRL_2[0], &i_fadewn01[0], 0,
                                          &GENERATE_2[0]);
                    beMessenger_SendNamed(self->_messenger, &MODELCTRL_2[0], &i_fadewn01[0], 0,
                                          &SQ_BLOUT30[0]);
                    goto done;
                case 0x3E9:
                    beMessenger_SendNamed(self->_messenger, &MODELCTRL_2[0], &j_startmenu01[0], 0,
                                          &ISRUN_2[0]);
                    if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
                        ctrl->_st3 = 0x3EA;
                        goto done;
                    }
                    break;
                case 0x3EA:
                    beMessenger_SelectGroup(self->_messenger, &STAGECTL[0]);
                    beMessenger_AppendString(self->_messenger, &stagIS09[0]);
                    beMessenger_DispatchSelected(self->_messenger, &NEXTSTAGE[0]);
                    ctrl->_st3 = 0x3EB;
                    goto done;
                case 0x3EB:
                    goto done;
                }
                break;
            case 2:
                switch (ctrl->_st3) {
                case 0:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_startmenu01[0], &SQ_LINEON00_2[0], 1);
                    ctrl->_st3 = (*(volatile int *)&ctrl->_st3) + 1;
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
                beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_startmenu02[0], &SQ_OPEN_2[0], 1);
                ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(models) & 0xFF) == 1) {
                    ctrl->_st1 = (*(volatile int *)&ctrl->_st1) + 1;
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
                ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if (up) {
                    if (ctrl->_gameMenuCnt == 1) {
                        ctrl->_gameMenuCnt = 0;
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_startmenu02[0], &SQ_LINEUP00_2[0], 1);
                    }
                    ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                    ctrl->_st3 = 0;
                    goto done;
                }
                if (down) {
                    if (ctrl->_gameMenuCnt == 0) {
                        ctrl->_gameMenuCnt = 1;
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_startmenu02[0], &SQ_LINEDW01_2[0], 1);
                    }
                    ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                    ctrl->_st3 = 0;
                    goto done;
                }
                if (pressed & ButtonCross) {
                    if (ctrl->_gameMenuCnt == 0) {
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_startmenu02[0], &SQ_LINEON00_2[0], 1);
                        ctrl->_gameMenuNext = 1;
                    } else {
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_startmenu02[0], &SQ_LINEON01_2[0], 1);
                        ctrl->_gameMenuNext = 2;
                    }
                    ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                    ctrl->_st3 = 0;
                    goto done;
                }
                if (pressed & ButtonCircle) {
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_startmenu02[0], &SQ_CANCEL_2[0], 1);
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
                            beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_startlogo[0], &SQ_CLOSE_2[0], 1);
                            ctrl->_st3 = (*(volatile int *)&ctrl->_st3) + 1;
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
                                                              &OPTION[0]));
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
                    beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_optionwin02[0], &SQ_BOPEN[0], 1);
                    break;
                case 1:
                case 2:
                    beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_optionwin02[0], &SQ_AOPEN[0], 1);
                    break;
                }
                beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_optioncursor11[0], &SQ_OPEN_2[0], 1);
                beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_optioncursor12[0], &SQ_OPEN_2[0], 1);
                option->_ctrlPos = 0;
                option->_isOK = 0U;
                ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
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
                    ctrl->_st1 = (*(volatile int *)&ctrl->_st1) + 1;
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
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor11[0], &SQ_MOVE[0], 1);
                            ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                            ctrl->_st3 = 0;
                        } else if (rowUp != 0) {
                            rowUp = 0;
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor11[0], &SQ_MOVE[0], 1);
                            ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                            ctrl->_st3 = 0;
                        }
                        break;
                    case 1:
                    case 2:
                        rowUp -= 1;
                        if (rowUp < 0) {
                            rowUp = 0;
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor11[0], &SQ_MOVE[0], 1);
                            ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
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
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor11[0], &SQ_MOVE[0], 1);
                            ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                            ctrl->_st3 = 0;
                            break;
                        }
                    case 1:
                    case 2:
                        rowDown += 1;
                        if (rowDown > OptionRowOk) {
                            rowDown = OptionRowOk;
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor11[0], &SQ_MOVE[0], 1);
                            ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
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
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor12[0], &SQ_LINERT00[0], 1);
                        nextComConf = option->_dispComConf + 1;
                        if (nextComConf > 1) {
                            nextComConf = 0;
                        }
                        option->_dispComConf = nextComConf;
                        ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowLight:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor12[0], &SQ_LINERT01[0], 1);
                        nextLightConf = option->_dispLightConf + 1;
                        if (nextLightConf > 1) {
                            nextLightConf = 0;
                        }
                        option->_dispLightConf = nextLightConf;
                        ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowCountry:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor12[0], &SQ_LINERT02[0], 1);
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
                        ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowOk:
                        goto done;
                    }
                } else if (left) {
                    switch (option->_ctrlPos) {
                    case OptionRowCamera:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor12[0], &SQ_LINELF00[0], 1);
                        prevComConf = option->_dispComConf - 1;
                        if (prevComConf < 0) {
                            prevComConf = 1;
                        }
                        option->_dispComConf = prevComConf;
                        ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowLight:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor12[0], &SQ_LINELF01[0], 1);
                        prevLightConf = option->_dispLightConf - 1;
                        if (prevLightConf < 0) {
                            prevLightConf = 1;
                        }
                        option->_dispLightConf = prevLightConf;
                        ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                        ctrl->_st3 = 0;
                        goto done;
                    case OptionRowCountry:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor12[0], &SQ_LINELF02[0], 1);
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
                        ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
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
                            ctrl->_st1 = (*(volatile int *)&ctrl->_st1) + 1;
                            ctrl->_st3 = 0;
                            ctrl->_st2 = 0;
                            goto done;
                        }
                        goto done;
                    }
                    if (pressed & ButtonCircle) {
                        option->_isOK = 1U;
                        ctrl->_st1 = (*(volatile int *)&ctrl->_st1) + 1;
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
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor11[0], &SQ_LINESL00_2[0], 0);
                        break;
                    case OptionRowLight:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor11[0], &SQ_LINESL01[0], 0);
                        break;
                    case OptionRowCountry:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor11[0], &SQ_LINESL02[0], 0);
                        break;
                    case OptionRowOk:
                        beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor11[0], &SQ_LINESL03[0], 0);
                        break;
                    }
                    switch (option->_ctrlPos) {
                    case OptionRowCamera:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, &j_optioncursor12[0]) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor12[0], &SQ_LINESL00_2[0], 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_optioncursor12[0], &SQ_LINESL00_2[0], 0);
                        }
                        break;
                    case OptionRowLight:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, &j_optioncursor12[0]) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor12[0], &SQ_LINESL01[0], 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_optioncursor12[0], &SQ_LINESL01[0], 0);
                        }
                        break;
                    case OptionRowCountry:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, &j_optioncursor12[0]) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Play(models, 0, &j_optioncursor12[0], &SQ_LINESL02[0], 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_optioncursor12[0], &SQ_LINESL02[0], 0);
                        }
                        break;
                    case OptionRowOk:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(models, 0, &j_optioncursor12[0]) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_optioncursor12[0], &SQ_CLOSE_2[0], 0);
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
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_optioncursor11[0], &SQ_LINEON00_2[0], 1);
                    break;
                case OptionRowLight:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_optioncursor11[0], &SQ_LINEON01_2[0], 1);
                    break;
                case OptionRowCountry:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_optioncursor11[0], &SQ_LINEON02[0], 1);
                    break;
                case OptionRowOk:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_optioncursor11[0], &SQ_LINEON03[0], 1);
                    break;
                }
                switch (option->_ctrlPos) {
                case OptionRowCamera:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_optioncursor12[0], &SQ_CLOSE_2[0], 1);
                    break;
                case OptionRowLight:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_optioncursor12[0], &SQ_CLOSE_2[0], 1);
                    break;
                case OptionRowCountry:
                    beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_optioncursor12[0], &SQ_CLOSE_2[0], 1);
                    break;
                }
                TextOrder_PublishLineListOnly(text, 0xF0001);
                if (option->_selLang != 0) {
                    TextOrder_PublishLineListOnly(text, 0xF0006);
                    TextOrder_PublishLineListOnly(text, 0xF000D);
                }
                TextOrder_PublishLineListOnly(text, 0xF0002);
                TextOrder_PublishLineListOnly(text, 0xF0005);
                ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                ctrl->_st3 = 0;
                goto done;
            case 1:
                if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(models) & 0xFF) == 1) {
                    ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
                    ctrl->_st3 = 0;
                    goto done;
                }
                break;
            case 2:
                beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_optionwin02[0], &SQ_CLOSE_2[0], 1);
                ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
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
                    ctrl->_st1 = (*(volatile int *)&ctrl->_st1) + 1;
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
                beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &j_startlogo[0], &SQ_OPEN_2[0], 1);
                ctrl->_st2 = (*(volatile int *)&ctrl->_st2) + 1;
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
                beMessenger_SendNamed(self->_messenger, &MODELCTRL_2[0], &i_fadewn01[0], 0,
                                      &GENERATE_2[0]);
                beMessenger_SendNamed(self->_messenger, &MODELCTRL_2[0], &i_fadewn01[0], 0,
                                      &SQ_BLOUT30[0]);
                goto done;
            case 1:
                beMessenger_SendNamed(self->_messenger, &MODELCTRL_2[0], &j_startmenu01[0], 0,
                                      &ISRUN_2[0]);
                if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
                    ctrl->_st2 = 2;
                    ctrl->_st3 = 0;
                    goto done;
                }
                break;
            case 2:
                beMessenger_SendGroup(self->_messenger, &GAMERAM_3[0], &GETCOMMON_2[0]);
                commonSettings = beMessenger_GetObject(self->_messenger, 0);
                savedCameraMode = option->_comConf;
                savedLightMode = option->_lightConf;
                /* Write the saved settings back into the GAMERAM common-settings records
                 * (value word at record +12). */
                *(int *)((char *)(igProperty_GetRecord(commonSettings, &CAMERAMODE_2[0])) + 12) =
                    savedCameraMode;
                *(int *)((char *)(igProperty_GetRecord(commonSettings, &LIGHTMODE_2[0])) + 12) =
                    savedLightMode;
                g_commonSettingsValid = 1;
                beMessenger_SendNamed(self->_messenger, &SOUND[0], 0, -1, &BGMSTOP[0]);
                beMessenger_SendNamed(self->_messenger, &SOUND[0], 0, -1, &ENVSTOP[0]);
                beMessenger_SendNamed(self->_messenger, &SOUND[0], 0, -1, &SESTOP[0]);
                beMessenger_SelectGroup(self->_messenger, &STAGECTL[0]);
                beMessenger_AppendString(self->_messenger, &stagIS08[0]);
                beMessenger_DispatchSelected(self->_messenger, &NEXTSTAGE[0]);
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
            beNDMWLoadIntf2ComMdlCtrl__Start(models, 0, &i_fadewn01[0], &SQ_WTOUT60[0], 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(models, 0, &j_startback[0], &SQ_CLOSE_2[0], 1);
            ctrl->_st1 = (*(volatile int *)&ctrl->_st1) + 1;
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
                                                       &OPTION[0]));
            cameraMode = option->_comConf;
            lightMode = option->_lightConf;
            beMessenger_SelectReceivers(self->_messenger, &LOADCTRL2_2[0], 0, 0);
            beMessenger_AppendInt(self->_messenger, cameraMode);
            beMessenger_AppendInt(self->_messenger, lightMode);
            beMessenger_DispatchSelected(self->_messenger, &GENERATE_TITLE[0]);
            ctrl->_st1 = (*(volatile int *)&ctrl->_st1) + 1;
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

#undef SET_DATA
#undef ALLOC

/* 0x003f5310: slot 30, class metaObject accessor of the title menu's info record */
int Gap__Bec__beNDMWTitle2__vfunc_30(void)
{
    return g_beNDMWTitle2Info_metaObject[0];
}

/* 0x003f5320 — slot 29: register the controller as the TITLE2 message receiver. */
void Gap__Bec__beNDMWTitle2__vfunc_29(beNDMWTitle2 *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, &TITLE2[0]);
}

/* 0x003f5400: slot 20, class metaObject accessor (RTTI handle at 0x0058ab10) */
int Gap__Bec__beNDMWTitle2__vfunc_20(void)
{
    return g_beNDMWTitle2_metaObject[0];
}
