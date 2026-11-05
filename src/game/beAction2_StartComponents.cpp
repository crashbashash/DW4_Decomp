/* beAction2 component Start driver, 0x00377700 (finding #653,
 * docs/engine/action2-jointset.md).  Each action carries a list of timeline
 * components (MOTIONSET, JOINTSET, FADESET, WAITCHECK, FLASHSET); this walks
 * the list from the saved position and starts them one by one. */
#include "dw4/reflected.h"

extern "C" {
int beAction2FADESET_Start(...);
int beAction2FLASHSET_Start(...);
int beAction2JOINTSET_Start(...);
int beAction2MOTIONSET_Start(...);
int beAction2WAITCHECK_Start(...);
extern int g_beAction2FLASHSET_metaObject_00589f98[4];
extern int g_beAction2WAITCHECK_metaObject_00589fa0[4];
extern int g_beAction2FADESET_metaObject_00589fb0[4];
extern int g_beAction2JOINTSET_metaObject_00589fc8[4];
extern int g_beAction2MOTIONSET_metaObject_00589fe8[4];
void beAction2_StartComponents(int manager, void *info);
}

/* matching construct: igObjectList-shaped component list (docs/engine/action2-jointset.md) with a pointer-typed buffer; reflected igObjectList._data (int) changes retail register allocation */
struct Action2ComponentList {
    char _pad0[8];
    int _count;
    int _capacity;
    struct Action2Component **_data;
};

/* matching construct: dummy-virtual component class; only slot 20 (GetMetaObject) is called */
class Action2Component {
public:
    virtual void vfunc_00();
    virtual void vfunc_01();
    virtual void vfunc_02();
    virtual void vfunc_03();
    virtual void vfunc_04();
    virtual void vfunc_05();
    virtual void vfunc_06();
    virtual void vfunc_07();
    virtual void vfunc_08();
    virtual void vfunc_09();
    virtual void vfunc_10();
    virtual void vfunc_11();
    virtual void vfunc_12();
    virtual void vfunc_13();
    virtual void vfunc_14();
    virtual void vfunc_15();
    virtual void vfunc_16();
    virtual void vfunc_17();
    virtual void vfunc_18();
    virtual void vfunc_19();
    virtual int GetMetaObject();
};


/* 0x00377700: resume at work._comIndex and start components until one handler
 * returns false (finding #653) or the list is exhausted, then save the position back into work._comIndex.  The component
 * kind is identified by comparing its virtual GetMetaObject() result with the
 * published metadata handle of each *_Start handler's class. */
void beAction2_StartComponents(int manager, void *info)
{
    Action2Component *component;
    unsigned char keepGoing;
    int index;
    beAction2Data *data;
    beAction2InfoWork *work;

    work = (beAction2InfoWork *)((beAction2InfoRam *)info)->_work;
    data = (beAction2Data *)work->_comData;
    index = work->_comIndex;
    if (index != ((Action2ComponentList *)data->_comList)->_count) {
next_component:
        keepGoing = true;
        component = (((Action2ComponentList *)data->_comList)->_data)[index];
        if (g_beAction2MOTIONSET_metaObject_00589fe8[0] == component->GetMetaObject()) {
            keepGoing = beAction2MOTIONSET_Start(manager, info, component) & 0xFF;
            index += 1;
        } else if (g_beAction2JOINTSET_metaObject_00589fc8[0] == component->GetMetaObject()) {
            keepGoing = beAction2JOINTSET_Start(manager, info, component) & 0xFF;
            index += 1;
        } else if (g_beAction2FADESET_metaObject_00589fb0[0] == component->GetMetaObject()) {
            keepGoing = beAction2FADESET_Start(manager, info, component) & 0xFF;
            index += 1;
        } else if (g_beAction2WAITCHECK_metaObject_00589fa0[0] == component->GetMetaObject()) {
            keepGoing = beAction2WAITCHECK_Start(manager, info, component) & 0xFF;
            index += 1;
        } else if (g_beAction2FLASHSET_metaObject_00589f98[0] == component->GetMetaObject()) {
            keepGoing = beAction2FLASHSET_Start(manager, info, component) & 0xFF;
            index += 1;
            /* matching construct: preserve the retail scheduler's inner-branch padding. */
            asm { nop }
        }
        if (keepGoing & 0xFF) {
            if (index == ((Action2ComponentList *)data->_comList)->_count) {
                /* matching construct: preserve the retail scheduler's loop-exit padding. */
                asm { nop }
            } else {
                goto next_component;
            }
        }
    }
    work->_comIndex = index;
}
