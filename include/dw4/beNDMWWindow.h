#ifndef DW4_BENDMWWINDOW_H
#define DW4_BENDMWWINDOW_H

struct beNDMWWindow;
struct igObject;
template <class T> struct igSmartPointer;

extern "C" {
void beNDMWWindow_BindContext(beNDMWWindow *self, igObject *mother, int insight, int playerNo, int entCode);
void beNDMWWindow_ClearQueuedText(beNDMWWindow *self);
void beNDMWWindow_PlayQueuedModelClose(beNDMWWindow *w);
int beNDMWWindow_PollCloseComplete(beNDMWWindow *self);
void beNDMWWindow_PresentModel(beNDMWWindow *self, const char *model, int id, const char *sequence, const char *close, float *position);
void beNDMWWindow_PresentModelAtOrigin(beNDMWWindow *self, const char *model, int id, const char *sequence, const char *close);
void beNDMWWindow_QueueNumberText(beNDMWWindow *self, const char *textType, const char *textName, int number, const char *align);
void beNDMWWindow_QueueObjectText(beNDMWWindow *self, const char *textType, const char *textName, const igSmartPointer<igObject> &textObject, const char *align);
void beNDMWWindow_QueueText(beNDMWWindow *self, const char *textType, const char *textName, const char *text, const char *align);
void beNDMWWindow_RequestChildrenClose(beNDMWWindow *self);
void beNDMWWindow_RunMessageScript(beNDMWWindow *self, const char *chunk, int callNo);
void beNDMWWindow_SendModelSequence(beNDMWWindow *self, const char *model, int id, const char *sequence);
void beNDMWWindow_ShowPaddedDigits(beNDMWWindow *self, int value, unsigned int digits, const char *slotFormat);
void beNDMWWindow_UpdateTree(beNDMWWindow *w);
}

#endif
