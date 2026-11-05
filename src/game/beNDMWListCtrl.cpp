/* src/game/beNDMWListCtrl.cpp — the beNDMWListCtrl methods, one translation unit in
 * retail address order:
 *   0x0040dae0  Gap__Bec__beNDMWListCtrl__vfunc_22  create the page-arrow models (finding #922)
 *   0x0040dbf0  Gap__Bec__beNDMWListCtrl__vfunc_23  previous page (finding #919)
 *   0x0040dd30  Gap__Bec__beNDMWListCtrl__vfunc_24  next page (findings #917, #919)
 *   0x004233e0  Gap__Bec__beNDMWListCtrl__vfunc_20  class metaObject accessor
 *
 * The retail unit at 0x0040dae0 was C++ with exceptions on (its three functions keep
 * exception index records, config/SLUS-20836/exceptions.txt).  vfunc_22 and vfunc_20 used to live
 * in beNDMWListCtrl.c; they now compile here as C++ under that profile, which also
 * reproduces vfunc_22's record.  vfunc_20 sits in a separate retail unit
 * (beNDMWListCtrl_4233e0 in config/SLUS-20836/units.tsv: the metaObject accessors were placed
 * apart from the method bodies); the build resolves each function's profile by address.
 * The whole unit keeps C linkage.
 *
 * A page turn happens when the player's pad shows left (previous) or right (next) and
 * no up/down is held; the page index moves by one and the i_stcursorleft /
 * i_stcursorright arrow models on the MODELCTRL receiver are told which sequence to
 * play.  All input tests, page arithmetic, vector copies and requests are C++.  Explicit
 * original NOPs, one local unconditional join per method and one address-high word in
 * the arrow initializer preserve branch/alignment layout (matching constructs; there is
 * no claim about the original declaration spelling or an assembly-free source).
 * Next-page return uses the original-width register copy (finding #917).
 */
#include "dw4/reflected.h"
/* Direction bits as the pad object reports them: the stick words (_lTrg, _lRpt,
 * _lStk) use 1 up, 2 right, 4 down, 8 left; the button words (_trigger, _repeat)
 * use the PS2 digital layout 0x10 up, 0x20 right, 0x40 down, 0x80 left.  Cross-checked
 * with the up/down tests in src/unmatched/beNDMWLoadIntf2Diffselect__Update.cpp (0x1/0x4 and 0x10/0x40). */
#define STICK_UP 1
#define STICK_RIGHT 2
#define STICK_DOWN 4
#define STICK_LEFT 8
#define BUTTON_RIGHT 0x20
#define BUTTON_LEFT 0x80
extern "C" {
extern int g_beNDMWListCtrl_metaObject_0058aff0[4];
/* Model names (the list's page-arrow cursors) and the sequences they are driven with:
 * SQ_HIDE keeps an arrow invisible, SQ_SELECT shows it, SQ_CLOSE is queued as the close
 * sequence, SQ_MOVEEND / SQ_MOVENEXT animate a page turn (docs/engine/window-presentation.md;
 * strings read from the ELF). */
extern char s_i_stcursorleft_00519a40[], s_SQ_HIDE_00519a50[], s_SQ_CLOSE_00519a58[],
    s_i_stcursorright_00519a70[], s_SQ_SELECT_00519a80[], s_MODELCTRL_00519a90[],
    s_SQ_MOVEEND_00519aa0[], s_SQ_MOVENEXT_00519ab0[];
/* beNDMWWindow_PresentModel(window, modelName, ramNo, sequence, closeSequence, position) */
void beNDMWWindow_PresentModel(beNDMWListCtrl *, const char *, int, const char *, const char *, float *);
bePadData *bePadManager_GetPadForPlayer(int, int);
void beMessenger_SendNamed(int, const char *, const char *, int, const char *);
void Gap__Bec__beNDMWListCtrl__vfunc_22(beNDMWListCtrl *, const float *, const float *);
bool Gap__Bec__beNDMWListCtrl__vfunc_23(beNDMWListCtrl *);
bool Gap__Bec__beNDMWListCtrl__vfunc_24(beNDMWListCtrl *);
int Gap__Bec__beNDMWListCtrl__vfunc_20(void);
}

/* 0x0040dae0: create the previous/next page arrow models.  The left arrow starts
 * hidden; the right arrow is shown when the list spans more than one page
 * (_maxPage) and hidden otherwise. */
void Gap__Bec__beNDMWListCtrl__vfunc_22(beNDMWListCtrl *self,const float *leftArrowPos,const float *rightArrowPos){
    float rightHiddenPos[4],rightShownPos[4],leftPos[4];
    const char *modelName;
    leftPos[0]=leftArrowPos[0];leftPos[1]=leftArrowPos[1];leftPos[2]=leftArrowPos[2];
    beNDMWWindow_PresentModel(self,s_i_stcursorleft_00519a40,0,s_SQ_HIDE_00519a50,s_SQ_CLOSE_00519a58,leftPos);
    if(self->_maxPage<=1)goto single_page;
    rightShownPos[0]=rightArrowPos[0];rightShownPos[1]=rightArrowPos[1];rightShownPos[2]=rightArrowPos[2];
    beNDMWWindow_PresentModel(self,s_i_stcursorright_00519a70,0,s_SQ_SELECT_00519a80,s_SQ_CLOSE_00519a58,rightShownPos);
    /* Preserve the original join and its delay/alignment NOPs. */
    asm { .set noreorder
        b arrows_done
        nop
        nop
        .set reorder }
single_page:
    /* The single-page block starts with this original address-high word.
     * dmove connects a1 to the C local; it coalesces away (no extra word).
     * 0x520000 - 26000 = 0x519a70, i_stcursorright. */
    asm { lui a1,0x52 }
    asm { dmove modelName,a1 };
    rightHiddenPos[0]=rightArrowPos[0];rightHiddenPos[1]=rightArrowPos[1];rightHiddenPos[2]=rightArrowPos[2];
    beNDMWWindow_PresentModel(self,modelName-26000,0,s_SQ_HIDE_00519a50,s_SQ_CLOSE_00519a58,rightHiddenPos);
arrows_done:;
}

/* 0x0040dbf0: previous page. */
bool Gap__Bec__beNDMWListCtrl__vfunc_23(beNDMWListCtrl *self){
    bePadData *pad;
    bool leftPressed;
    unsigned stickHeld,repeat,trigger,stickTrigger,stickRepeat;
    bool upDownHeld,changed;
    pad=bePadManager_GetPadForPlayer(self->_padManager,self->_playerNo);
    trigger=pad->_trigger;repeat=pad->_repeat;stickHeld=pad->_lStk;stickTrigger=pad->_lTrg;stickRepeat=pad->_lRpt;
    leftPressed=true;
    if(!((stickTrigger|stickRepeat)&STICK_LEFT)){
        /* Keep the second input branch's original delay NOP. */
        asm { .set noreorder }
        if(!((trigger|repeat)&BUTTON_LEFT)){
            asm { nop
                .set reorder }
            leftPressed=false;
        }
    }
    upDownHeld=true;if(!(stickHeld&STICK_UP)&&!(stickHeld&STICK_DOWN)){upDownHeld=false;asm { nop }}
    changed=false;
    if(self->_nowPage>0&&leftPressed&&!upDownHeld){
        self->_nowPage--;changed=true;
        if(self->_nowPage)goto previous_notFirst;
        beMessenger_SendNamed(self->_messenger,s_MODELCTRL_00519a90,s_i_stcursorleft_00519a40,0,s_SQ_MOVEEND_00519aa0);/* Join the opposite-arrow request, retaining unreachable padding. */
        asm { .set noreorder
            b previous_selectNext
            nop
            nop
            .set reorder }
previous_notFirst:
        beMessenger_SendNamed(self->_messenger,s_MODELCTRL_00519a90,s_i_stcursorleft_00519a40,0,s_SQ_MOVENEXT_00519ab0);asm { nop }
previous_selectNext:;
        beMessenger_SendNamed(self->_messenger,s_MODELCTRL_00519a90,s_i_stcursorright_00519a70,0,s_SQ_SELECT_00519a80);asm { nop }
    }
    return changed;
}

/* 0x0040dd30: next page. */
bool Gap__Bec__beNDMWListCtrl__vfunc_24(beNDMWListCtrl *self){
    bePadData *pad;
    int page;
    unsigned repeat;
    bool rightPressed;
    unsigned stickHeld,trigger,stickTrigger,stickRepeat;
    bool upDownHeld,changed;
    pad=bePadManager_GetPadForPlayer(self->_padManager,self->_playerNo);
    trigger=pad->_trigger;repeat=pad->_repeat;stickHeld=pad->_lStk;stickTrigger=pad->_lTrg;stickRepeat=pad->_lRpt;
    rightPressed=true;
    if(!((stickTrigger|stickRepeat)&STICK_RIGHT)){
        /* Keep the second input branch's original delay NOP. */
        asm { .set noreorder }
        if(!((trigger|repeat)&BUTTON_RIGHT)){
            asm { nop
                .set reorder }
            rightPressed=false;
        }
    }
    upDownHeld=true;if(!(stickHeld&STICK_UP)&&!(stickHeld&STICK_DOWN)){upDownHeld=false;asm { nop }}
    changed=false;
    page=self->_nowPage;
    if(page<(self->_maxPage-1)&&rightPressed&&!upDownHeld){
        self->_nowPage=(page+1);changed=true;
        if(self->_nowPage!=(self->_maxPage-1))goto next_notLast;
        beMessenger_SendNamed(self->_messenger,s_MODELCTRL_00519a90,s_i_stcursorright_00519a70,0,s_SQ_MOVEEND_00519aa0);
        /* Same original join/padding sequence as previous-page. */
        asm { .set noreorder
            b next_selectPrevious
            nop
            nop
            .set reorder }
next_notLast:
        beMessenger_SendNamed(self->_messenger,s_MODELCTRL_00519a90,s_i_stcursorright_00519a70,0,s_SQ_MOVENEXT_00519ab0);asm { nop }
next_selectPrevious:;
        beMessenger_SendNamed(self->_messenger,s_MODELCTRL_00519a90,s_i_stcursorleft_00519a40,0,s_SQ_SELECT_00519a80);asm { nop }
    }
    asm { dmove v0,changed }
    return changed;
}

/* 0x004233e0: metadata (igMetaObject) getter of the beNDMWListCtrl class. */
int Gap__Bec__beNDMWListCtrl__vfunc_20(void)
{
    return g_beNDMWListCtrl_metaObject_0058aff0[0];
}
