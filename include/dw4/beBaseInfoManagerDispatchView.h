#ifndef DW4_BEBASEINFOMANAGERDISPATCHVIEW_H
#define DW4_BEBASEINFOMANAGERDISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* igInfoManager's virtual functions, as the insight core and the schedulers call them
 * (beBaseInfoManager_<Name>).
 * ABI view only: never instantiated. */
class igInfoManagerDispatchView : public igObjectDispatchView {
public:
    virtual void Activate();                                                /* slot 21 */
    virtual void Deactivate();
    virtual void Start();
    virtual void Stop();
    virtual int AddInfo(beBaseInfo *info);
    virtual void RemoveAllInfo();
    virtual void Update();                                                  /* slot 27 */
};

/* beBaseInfoManager's virtual functions: the per-info and per-ram hooks its start, add, remove and
 * update defaults call, and the two message handlers beMessenger dispatches to (beBaseInfoManager_<Name>,
 * beBkColor_<Name> for slots 30 to 32).
 * ABI view only: never instantiated. */
class beBaseInfoManagerDispatchView : public igInfoManagerDispatchView {
public:
    virtual void OnAddInfo(beBaseInfo *info);                               /* slot 28 */
    virtual void OnAddRam(beBaseInfoRam *ram);
    virtual igMetaObject *GetInfoMeta();
    virtual void UpdateRam(beBaseInfoRam *ram);
    virtual void Prepare();
    virtual int OnMessageText(beBaseInfoRam *ram, const char *message);
    virtual int OnMessage(beBaseInfoRam *ram, beMessengerWork *work);       /* slot 34 */
};

#endif
