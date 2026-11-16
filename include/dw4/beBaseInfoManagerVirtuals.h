#ifndef DW4_BEBASEINFOMANAGERVIRTUALS_H
#define DW4_BEBASEINFOMANAGERVIRTUALS_H

#include "dw4/reflected.h"
#include "dw4/igObjectVirtuals.h"

/* igInfoManager's virtuals, as the insight core and the schedulers call them. */
class igInfoManagerVirtuals : public igObjectVirtuals {
public:
    virtual void activate();
    virtual void deactivate();
    virtual void start();
    virtual void stop();
    virtual int addInfo(beBaseInfo *info);
    virtual void removeAllInfo();
    virtual void update();
};

/* beBaseInfoManager's virtuals: the per-info and per-ram hooks its start, add, remove and update
 * defaults call, and the two message handlers beMessenger dispatches to. */
class beBaseInfoManagerVirtuals : public igInfoManagerVirtuals {
public:
    virtual void onAddInfo(beBaseInfo *info);
    virtual void onAddRam(beBaseInfoRam *ram);
    virtual int getInfoMeta();
    virtual void updateRam(beBaseInfoRam *ram);
    virtual void prepare();
    virtual int onMessageText(beBaseInfoRam *ram, const char *message);
    virtual int onMessage(beBaseInfoRam *ram, beMessengerWork *work);
};

#endif
