#ifndef DW4_BEMODELCTRLDISPATCHVIEW_H
#define DW4_BEMODELCTRLDISPATCHVIEW_H
#include "dw4/beBaseInfoManagerDispatchView.h"

/* beModelCtrl's own virtual functions past beBaseInfoManager's, as the model-controller files
 * dispatch them (each named as the same slot is in the class that introduces it).
 * ABI view only: never instantiated. */
class beModelCtrlDispatchView : public beBaseInfoManagerDispatchView {
public:
    virtual unsigned char IsKind(const char *kind);                         /* slot 35 */
    virtual void OnGenerate(beBaseInfoRam *ram);
    virtual void RegisterReceiver(beBaseInfoRam *ram);
    virtual void UpdateControl(beBaseInfoRam *ram);
    virtual void OnWaitCheck(beBaseInfoRam *ram);
    virtual void OnControlOff(beBaseInfoRam *ram);
    virtual void OnFreeze(beBaseInfoRam *ram);
    virtual void OnRemove(beBaseInfoRam *ram);
    virtual void OnErase(beBaseInfoRam *ram);
    virtual void OnSequenceChange(beBaseInfoRam *ram);
    virtual void OnAction1(beBaseInfoRam *ram);
    virtual void OnUpdateRam(beBaseInfoRam *ram);
    virtual unsigned char OnPreMessage(beBaseInfoRam *ram, const char *message); /* slot 47 */
};

#endif
