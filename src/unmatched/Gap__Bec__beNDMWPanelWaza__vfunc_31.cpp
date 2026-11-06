/* ram->_st0 is the phase (0 build, 1 run, 2 close request, 3 finished), _st1 the sub-state of the
 * run phase, _st2/_st3 the sub-state timers; work->_page selects the active panel. SetLabel is an
 * inlined static member; the string-pool singleton is created on first use and the new string is
 * interned before the old one is read and released. PanelVt/WorkVt are dummy-virtual classes so
 * the calls go through t9. `ramState = (T *)(int)ram` is a deliberate type-laundering copy:
 * without it the incoming register is propagated into every use and the pre-call loads use s4
 * instead of a1. The `< 2` test of _st3 reads through a volatile lvalue so the increment reloads
 * the field. Local declaration order and the exact condition spellings (blocked == 0 / blocked, if
 * (confirm), if (show)) select the register colouring and the bool tests. Raw offset casts remain
 * only for the player-work chain (+200 -> +8/+16 -> +4 -> +8), which has no reflected field. */
#include "dw4/reflected.h"

extern "C" {
int FUN_002eb010(int);
int FUN_003a7a20(void *, int *, long long);
int FUN_003a7e90(void *, int *);
int FUN_003cc3d0(int, int *);
int FUN_003cc480(void *);
int FUN_003cc540(void *);
int FUN_003ce4c0(void *, int *);
int FUN_003ce500(void *, void *, void *, void *, int);
int FUN_003ce5b0(void *, int, int);
int FUN_003ce700(void *);
int FUN_003ce7e0(void *);
int FUN_003ce890(void *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
bePadData *bePadManager_GetPadForPlayer(int, int);
extern int DAT_004cc680[4];
extern int DAT_004cc6c0[4];
extern int DAT_005159b0[4];
extern int DAT_005159c0[4];
extern int DAT_005159d8[4];
extern int DAT_00515b90[4];
extern int DAT_00515b98[4];
extern int DAT_00515ba8[4];
extern int DAT_00515bb8[4];
extern int DAT_00515bc8[4];
extern int DAT_00586f20[4];
void Gap__Bec__beNDMWPanelWaza__vfunc_31(beNDMWPanelWaza *, beNDMWPanelWazaInfoRam *);
}

/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]). The constructor interns the text and the destructor releases the token on scope exit;
 * both are out of line. */
class StringRef {
public:
    char *p;
    StringRef(const char *text);
    ~StringRef();
};
extern "C" int FUN_003cc490(int, StringRef *);

/* matching construct: dummy-virtual panel object; slot 21 refreshes, slot 22 asks for a fire request */
class PanelVt { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
 virtual void Refresh();
 virtual void GetFireRequest(int *label, long long *result);
};
/* matching construct: dummy-virtual info work; slot 16 is the "finished" notification */
class WorkVt { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
 virtual void Finished();
};

struct H {
static void SetLabel(beNDMWPanelWazaInfoWork *w, int str)
{
    int pool;
    int fresh;
    int old;
    int *hd;
    int rc;

    if (DAT_00586f20[0] == 0) {
        pool = FUN_002eb010(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        DAT_00586f20[0] = pool;
    }
    fresh = StringPool_Intern(DAT_00586f20[0], str);
    old = w->_retWazaLabel;
    if (old != 0) {
        hd = (int *)(old - 8);
        rc = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = rc;
        if (rc == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    w->_retWazaLabel = fresh;
}
};

void Gap__Bec__beNDMWPanelWaza__vfunc_31(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram)
{
    unsigned char show;
    beNDMWPanelWazaInfoRam *ramState;
    int sel;
    int both;
    beNDMWPanelObject *panel;
    int prevKazu;
    int vec[4];
    long long ret;
    int *obj;
    unsigned char emg;
    bePadData *pad;
    unsigned char decide;
    int idx;
    int refStr;
    unsigned char blocked;
    beNDMWPanelWazaInfoWork *work;
    int rep;
    unsigned char cancel;
    int prevCursor;
    int trig;

    if (ram->_isRun == 1) {
        work = (beNDMWPanelWazaInfoWork *)ram->_work;
        ramState = (beNDMWPanelWazaInfoRam *)(int)ram;
        pad = (bePadData *)bePadManager_GetPadForPlayer(self->_padManager, ramState->_ramNo);
        trig = pad->_trigger;
        decide = 1;
        both = pad->_rTrg | pad->_rRpt;
        rep = pad->_repeat;
        if (!(both & 1) && !((trig | rep) & 0x10)) {
            decide = 0;
        }
        cancel = 1;
        if (!(both & 4) && !((trig | rep) & 0x40)) {
            cancel = 0;
        }
        switch (work->_page) {
        case 0:
            panel = (beNDMWPanelObject *)work->_panelWaza;
            break;
        case 1:
            panel = (beNDMWPanelObject *)work->_panelItem;
            break;
        case 2:
            panel = (beNDMWPanelObject *)work->_panelStat;
            break;
        }
        prevCursor = panel->_cursor;
        prevKazu = panel->_listKazu;
        idx = prevCursor + panel->_lineMode;
        obj = (int *)*(int *)(work->_playerWork + 200);
        blocked = 0;
        if (obj[2] != 0 && *(unsigned char *)(*(int *)(obj[4] + 4) + 8) != 0) {
            blocked = 1;
        }
        switch (ramState->_st0) {
        case 0:
            {
                StringRef empty(0);
                FUN_003cc490(FUN_003cc540(work), &empty);
            }
            FUN_003cc3d0(FUN_003cc480(work), &DAT_004cc680[0]);
            prevKazu = idx = -1;
            ramState->_st0 = ramState->_st0 + 1;
            ramState->_st3 = 0;
            ramState->_st2 = 0;
            ramState->_st1 = 0;
        case 1:
            emg = 1;
            switch (ramState->_st1) {
            case 0:
                if ((unsigned char)FUN_003a7e90(ramState, &DAT_00515b90[0])) {
                    emg = 0;
                    if (panel->_isEmg != 0 ||
                        (blocked == 0 && (trig & 0x4000) && panel->_listKazu != 0 && work->_page != 2)) {
                        if (ramState->_st3 >= 2) {
                            ((PanelVt *)panel)->GetFireRequest(&refStr, &ret);
                            if (0 < ret) {
                                H::SetLabel(work, refStr);
                                work->_retIsFire = 1;
                                FUN_003a7a20(ramState, &DAT_00515b90[0], ret);
                                ramState->_st1 = ramState->_st1 + 1;
                                ramState->_st3 = 0;
                                ramState->_st2 = 0;
                                panel->_isEmg = 0;
                            } else if (ret < 0) {
                                ramState->_st0 = 2;
                                ramState->_st3 = 0;
                                ramState->_st2 = 0;
                                ramState->_st1 = 0;
                            } else {
                                FUN_003a7a20(ramState, &DAT_00515b90[0], 0x0FE502AA);
                                ramState->_st1 = ramState->_st1 + 1;
                                ramState->_st3 = 0;
                                ramState->_st2 = 0;
                            }
                        }
                    } else if (decide) {
                        FUN_003ce7e0(panel);
                    } else if (cancel) {
                        FUN_003ce890(panel);
                    } else if (trig & 0x800) {
                        if (work->_page != 0) {
                            work->_page = 0;
                            ramState->_st0 = 0;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                        } else {
                            H::SetLabel(work, 0);
                            ramState->_st0 = 2;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                            beMessenger_SelectGroup(self->_messenger, &DAT_005159c0[0]);
                            beMessenger_AppendString(self->_messenger, &DAT_00515b98[0]);
                            beMessenger_DispatchSelected(self->_messenger, &DAT_005159d8[0]);
                        }
                    } else if (trig & 0x400) {
                        if (work->_page != 1) {
                            work->_page = 1;
                            ramState->_st0 = 0;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                        } else {
                            H::SetLabel(work, 0);
                            ramState->_st0 = 2;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                            beMessenger_SelectGroup(self->_messenger, &DAT_005159c0[0]);
                            beMessenger_AppendString(self->_messenger, &DAT_00515b98[0]);
                            beMessenger_DispatchSelected(self->_messenger, &DAT_005159d8[0]);
                        }
                    } else if (trig & 0x200) {
                        if (work->_page != 2) {
                            work->_page = 2;
                            ramState->_st0 = 0;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                        } else {
                            H::SetLabel(work, 0);
                            ramState->_st0 = 2;
                            ramState->_st3 = 0;
                            ramState->_st2 = 0;
                            ramState->_st1 = 0;
                            beMessenger_SelectGroup(self->_messenger, &DAT_005159c0[0]);
                            beMessenger_AppendString(self->_messenger, &DAT_00515b98[0]);
                            beMessenger_DispatchSelected(self->_messenger, &DAT_005159d8[0]);
                        }
                    }
                    if (*(volatile int *)&ramState->_st3 < 2) {
                        ramState->_st3 = ramState->_st3 + 1;
                    }
                }
                break;
            case 1:
                if (FUN_003a7e90(ramState, &DAT_00515b90[0]) != 0) {
                    ramState->_st1 = 0;
                    ramState->_st3 = 0;
                    ramState->_st2 = 0;
                }
                break;
            }
            ((PanelVt *)panel)->Refresh();
            if (prevKazu != panel->_listKazu) {
                if (panel->_isEmg != 0 && emg) {
                    FUN_003ce5b0(panel, work->_isWindowGenerate, 1);
                } else {
                    FUN_003ce5b0(panel, work->_isWindowGenerate, 0);
                }
                work->_isWindowGenerate = 0;
            }
            show = 1;
            if (ramState->_st0 == 1 && ramState->_st1 == 1) {
                show = 0;
            } else if (panel->_listKazu == 0) {
                show = 0;
            } else if (blocked) {
                show = 0;
            }
            if (show) {
                sel = panel->_cursor + panel->_lineMode;
                if (work->_isCursorGenerate == 0) {
                    FUN_003ce4c0(panel, vec);
                    FUN_003ce500(panel, &DAT_00515ba8[0], &DAT_005159b0[0], vec, DAT_004cc6c0[sel]);
                    work->_isCursorGenerate = 1;
                    return;
                }
                if (idx != sel) {
                    FUN_003ce500(panel, &DAT_00515ba8[0], (void *)DAT_004cc6c0[sel], 0, 0);
                    return;
                }
            } else if (work->_isCursorGenerate != 0) {
                FUN_003ce500(panel, &DAT_00515ba8[0], &DAT_00515bb8[0], 0, 0);
                work->_isCursorGenerate = 0;
                return;
            }
            break;
        case 2:
            beMessenger_SelectGroup(self->_messenger, &DAT_005159c0[0]);
            beMessenger_AppendString(self->_messenger, &DAT_00515bc8[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_005159d8[0]);
            FUN_003ce700(panel);
            if (work->_isCursorGenerate != 0) {
                FUN_003ce500(panel, &DAT_00515ba8[0], &DAT_00515bb8[0], 0, 0);
            }
            ramState->_st0 = 3;
            ramState->_st3 = 0;
            ramState->_st2 = 0;
            ramState->_st1 = 0;
            return;
        case 3:
            ramState->_isRun = 0;
            ((WorkVt *)work)->Finished();
            break;
        }
    }
}
