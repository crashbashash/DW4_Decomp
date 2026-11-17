#ifndef DW4_BENDMWLOADINTF2MESWIN_H
#define DW4_BENDMWLOADINTF2MESWIN_H

struct beNDMWLoadIntf2MesWin;

extern "C" {
beNDMWLoadIntf2MesWin *beNDMWLoadIntf2MesWin_Create(int allocator);
void beNDMWLoadIntf2MesWin__Cancel(beNDMWLoadIntf2MesWin *win);
void beNDMWLoadIntf2MesWin__EndSystemMessage(beNDMWLoadIntf2MesWin *win);
int beNDMWLoadIntf2MesWin__GetCurPoint(beNDMWLoadIntf2MesWin *win);
unsigned char beNDMWLoadIntf2MesWin__GetIsCtrl(beNDMWLoadIntf2MesWin *win);
void beNDMWLoadIntf2MesWin__RequestClose(beNDMWLoadIntf2MesWin *win);
void beNDMWLoadIntf2MesWin__RequestMesErase(beNDMWLoadIntf2MesWin *win);
void beNDMWLoadIntf2MesWin__RequestMessage(beNDMWLoadIntf2MesWin *win, int messageNo);
void beNDMWLoadIntf2MesWin__RequestOpen(beNDMWLoadIntf2MesWin *win);
void beNDMWLoadIntf2MesWin__RequestPrompt(beNDMWLoadIntf2MesWin *win, int messageNo);
void beNDMWLoadIntf2MesWin__RequestQuestion(beNDMWLoadIntf2MesWin *win, int messageNo, int cursor);
void beNDMWLoadIntf2MesWin__RequestSystemMessage(beNDMWLoadIntf2MesWin *win, int messageNo);
void beNDMWLoadIntf2MesWin__Update(beNDMWLoadIntf2MesWin *win);
}

#endif
