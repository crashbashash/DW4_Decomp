/* A page turn happens when the player's pad shows left (previous) or right (next) and no up/down is
 * held; the page index moves by one and the i_stcursorleft / i_stcursorright arrow models on the
 * MODELCTRL receiver are told which sequence to play. */
#include "dw4/reflected.h"
/* Direction bits as the pad object reports them: the stick words (_lTrg, _lRpt, _lStk) use 1 up, 2
 * right, 4 down, 8 left; the button words (_trigger, _repeat) use the PS2 digital layout 0x10 up,
 * 0x20 right, 0x40 down, 0x80 left. */
#define STICK_UP 1
#define STICK_RIGHT 2
#define STICK_DOWN 4
#define STICK_LEFT 8
#define BUTTON_RIGHT 0x20
#define BUTTON_LEFT 0x80
extern "C" {
extern int g_beNDMWListCtrl_metaObject[4];
/* Model names (the list's page-arrow cursors) and the sequences they are driven with: SQ_HIDE
 * keeps an arrow invisible, SQ_SELECT shows it, SQ_CLOSE is queued as the close sequence,
 * SQ_MOVEEND / SQ_MOVENEXT animate a page turn. */
extern char i_stcursorleft[], SQ_HIDE[], SQ_CLOSE_3[],
    i_stcursorright[], SQ_SELECT[], MODELCTRL_3[],
    SQ_MOVEEND[], SQ_MOVENEXT[];
/* beNDMWWindow_PresentModel(window, modelName, ramNo, sequence, closeSequence, position) */
void beNDMWWindow_PresentModel(beNDMWListCtrl *, const char *, int, const char *, const char *, float *);
bePadData *bePadManager_GetPadForPlayer(int, int);
void beMessenger_SendNamed(int, const char *, const char *, int, const char *);
void Gap__Bec__beNDMWListCtrl__vfunc_22(beNDMWListCtrl *, const float *, const float *);
bool Gap__Bec__beNDMWListCtrl__vfunc_23(beNDMWListCtrl *);
bool Gap__Bec__beNDMWListCtrl__vfunc_24(beNDMWListCtrl *);
int Gap__Bec__beNDMWListCtrl__vfunc_20(void);
}

/* Create the previous/next page arrow models. The left arrow starts hidden; the right arrow is
 * shown when the list spans more than one page (_maxPage) and hidden otherwise. */
void Gap__Bec__beNDMWListCtrl__vfunc_22(beNDMWListCtrl *self,const float *leftArrowPos,const float *rightArrowPos){
    float leftPos[4],rightShownPos[4],rightHiddenPos[4];
    leftPos[0]=leftArrowPos[0];leftPos[1]=leftArrowPos[1];leftPos[2]=leftArrowPos[2];
    beNDMWWindow_PresentModel(self,i_stcursorleft,0,SQ_HIDE,SQ_CLOSE_3,leftPos);
    if(self->_maxPage>1){
        rightShownPos[0]=rightArrowPos[0];rightShownPos[1]=rightArrowPos[1];rightShownPos[2]=rightArrowPos[2];
        beNDMWWindow_PresentModel(self,i_stcursorright,0,SQ_SELECT,SQ_CLOSE_3,rightShownPos);
    }else{
        rightHiddenPos[0]=rightArrowPos[0];rightHiddenPos[1]=rightArrowPos[1];rightHiddenPos[2]=rightArrowPos[2];
        beNDMWWindow_PresentModel(self,i_stcursorright,0,SQ_HIDE,SQ_CLOSE_3,rightHiddenPos);
    }
}

/* Previous page. */
bool Gap__Bec__beNDMWListCtrl__vfunc_23(beNDMWListCtrl *self){
    bool changed;
    bool upDownHeld;
    unsigned stickRepeat;
    unsigned stickTrigger;
    unsigned trigger;
    unsigned repeat;
    unsigned stickHeld;
    bool leftPressed;
    bePadData *pad;
    pad=bePadManager_GetPadForPlayer(self->_padManager,self->_playerNo);
    trigger=pad->_trigger;repeat=pad->_repeat;stickHeld=pad->_lStk;stickTrigger=pad->_lTrg;stickRepeat=pad->_lRpt;
    leftPressed=true;
    if(!((stickTrigger|stickRepeat)&STICK_LEFT)){
        if(!((trigger|repeat)&BUTTON_LEFT)){
            leftPressed=false;
        }
    }
    upDownHeld=true;if(!(stickHeld&STICK_UP)&&!(stickHeld&STICK_DOWN)){upDownHeld=false;}
    changed=false;
    if(self->_nowPage>0&&leftPressed&&!upDownHeld){
        self->_nowPage--;changed=true;
        if(self->_nowPage==0){
            beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorleft,0,SQ_MOVEEND);
        }else{
            beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorleft,0,SQ_MOVENEXT);
        }
        beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorright,0,SQ_SELECT);
    }
    return changed;
}

/* Next page. */
bool Gap__Bec__beNDMWListCtrl__vfunc_24(beNDMWListCtrl *self){
    bool changed;
    bool upDownHeld;
    unsigned stickRepeat;
    unsigned stickTrigger;
    unsigned trigger;
    unsigned stickHeld;
    bool rightPressed;
    unsigned repeat;
    int page;
    bePadData *pad;
    pad=bePadManager_GetPadForPlayer(self->_padManager,self->_playerNo);
    trigger=pad->_trigger;repeat=pad->_repeat;stickHeld=pad->_lStk;stickTrigger=pad->_lTrg;stickRepeat=pad->_lRpt;
    rightPressed=true;
    if(!((stickTrigger|stickRepeat)&STICK_RIGHT)){
        if(!((trigger|repeat)&BUTTON_RIGHT)){
            rightPressed=false;
        }
    }
    upDownHeld=true;if(!(stickHeld&STICK_UP)&&!(stickHeld&STICK_DOWN)){upDownHeld=false;}
    changed=false;
    page=self->_nowPage;
    if(page<(self->_maxPage-1)&&rightPressed&&!upDownHeld){
        self->_nowPage=(page+1);changed=true;
        if(self->_nowPage==(self->_maxPage-1)){
            beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorright,0,SQ_MOVEEND);
        }else{
            beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorright,0,SQ_MOVENEXT);
        }
        beMessenger_SendNamed(self->_messenger,MODELCTRL_3,i_stcursorleft,0,SQ_SELECT);
    }
    return changed;
}

int Gap__Bec__beNDMWListCtrl__vfunc_20(void)
{
    return g_beNDMWListCtrl_metaObject[0];
}
