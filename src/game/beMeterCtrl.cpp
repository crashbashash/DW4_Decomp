#include "dw4/support/reflected.h"
#include "dw4/core/igTDataList.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beMeterCtrl.h"
#include "dw4/game/beMeterCtrlInfo.h"
#include "dw4/core/igObject.h"

extern "C" void beMeterCtrl_Prepare(void);
extern "C" void beMeterCtrl_UpdateRam(beMeterCtrl *self, beBaseInfoRam *ram);
extern "C" igMetaObject *beMeterCtrl_GetInfoMeta(void);
extern "C" igMetaObject *beMeterCtrl_GetMeta(void);
extern "C" char METERCTRL_3[];
extern "C" void beMeterCtrl_OnAddRam(beMeterCtrl * p0, int p1, char * p2);
extern "C" char MODELCTRL_11[];
extern "C" char GETHP_2[];
extern "C" int beMeterCtrl_OnMessageText(beMeterCtrl *self, beBaseInfoRam *ram, int message);

void beMeterCtrl_Prepare(void)
{
}

igMetaObject *beMeterCtrl_GetInfoMeta(void)
{
    return g_beMeterCtrlInfo_metaObject;
}

void beMeterCtrl_OnAddRam(beMeterCtrl * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)p0->_messenger, (beBaseInfoRam *)p1, METERCTRL_3);
}

static inline float RatioTime(const float maxValue)
{
    return 2.0e9f / maxValue;
}

static inline float PerFrame(const float value)
{
    return value / 60.0f;
}

void beMeterCtrl_SetupMaxValue(beMeterCtrl *self, beMeterCtrlOneData *data)
{
    int digits = 1;
    int value = (int)data->_maxValueF;

    while (1) {
        value /= 10;
        if (value == 0) {
            break;
        }
        digits++;
    }
    data->_ketaKazu = digits;
    data->_ratioTimeValueF = RatioTime(data->_maxValueF);
    data->_addMaxValueF = PerFrame(data->_maxValueF);
    if (data->_addMaxValueF < 1.0f) {
        data->_addMaxValueF = 1.0f;
    }
    data->_isChange = 1;
}

/* Sets the meter's target value from a percentage of its maximum; any non-zero percentage shows at least 1. */
static inline void SetNowPercent(beMeterCtrlOneData *one, float percent) {
    unsigned char nonZero = (percent != 0.0f);
    float value = (percent * one->_maxValueF) / 100.0f;
    if (value < 1.0f && nonZero) value = 1.0f;
    one->_nowValueF = value;
}

static inline igTDataList<long long> *TimeListOf(beMeterCtrlNode *node) { return (igTDataList<long long> *)node->_timeList; }
static inline void AppendTime(igTDataList<long long> *times, const long long &time) {
    int n = times->_count;
    if (n < times->_capacity) {
        times->_count = n + 1;
    } else {
        ((Gap::Core::igDataList *)times)->resizeAndSetCount(n + 1, sizeof(long long));
    }
    times->_data[n] = time;
}

/* Sets the meter up on its first update, follows the linked HP record, moves the shown value toward the target
 * by at most _addMaxValueF a frame and, when it changed, rewrites the node's time list: one time for a bar meter,
 * one per digit for a number. */
void beMeterCtrl_UpdateRam(beMeterCtrl *self, beBaseInfoRam *ram) {
    beMeterCtrlOneData *one = ((beMeterCtrlOneData **)((igObjectList *)((beMeterCtrlInfo *)ram->_parentInfo)->_oneDataList)->_data)[ram->_ramNo];
    switch (ram->_st0) {
    case 0:
        beMeterCtrl_SetupMaxValue(self, one);
        /* matching construct: the state steps by a reload-and-add and the other three counters clear in retail's order (st3, st2, st1) */
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        break;
    }
    if (one->_hp != 0) {
        SetNowPercent(one, ((beDataObjInt *)one->_hp)->_data * 100 / ((beDataObjInt *)one->_mHp)->_data);
    }
    float diff = one->_nowValueF - one->_dspValueF;
    float shown;
    if (diff != 0.0f) {
        /* matching construct: the direction is a byte flag set before the sign test, so the compare-and-negate branch shares one path */
        unsigned char rising;
        one->_isChange = 1;
        rising = 1;
        if (diff < 0.0f) {
            diff = -diff;
            rising = 0;
        }
        if (diff > one->_addMaxValueF) diff = one->_addMaxValueF;
        if (rising) shown = diff + one->_dspValueF; else shown = one->_dspValueF - diff;
        if (shown < 0.0f) shown = 0.0f; else if (shown > one->_maxValueF) shown = one->_maxValueF;
        if (one->_isNotchMode) {
            unsigned char nonZero = (shown != 0.0f);
            shown = (float)(int)shown;
            if (shown == 0.0f && nonZero) shown = 1.0f;
        }
        one->_dspValueF = shown;
    }
    if (one->_isChange) {
        igTDataList<long long> *times;
        one->_isChange = 0;
        times = TimeListOf((beMeterCtrlNode *)one->_node);
        times->_count = 0;
        if (((beMeterCtrlNode *)one->_node)->_isMeter) {
            shown = one->_dspValueF;
            if (shown <= 0.0f) {
                AppendTime(times, 1000000000LL);
                one->_dspValueF = 0;
            } else {
                float max = one->_maxValueF;
                if (shown >= max) {
                    AppendTime(times, 3000000000LL);
                    one->_dspValueF = one->_maxValueF;
                } else {
                    long long time = (long long)(shown * one->_ratioTimeValueF);
                    if (shown > 0.0f && time < one->_nonZeroTimeL) time = one->_nonZeroTimeL;
                    else if (shown < max && time > one->_nonMaxTimeL) time = one->_nonMaxTimeL;
                    AppendTime(times, time + 1000000000LL);
                }
            }
        } else {
            int rest = (int)one->_dspValueF;
            int i;
            for (i = 0; i < one->_ketaKazu; i++) {
                AppendTime(times, (long long)(rest % 10) * 1000000000LL + 1000000000LL);
                rest = rest / 10;
                if (one->_isZeroSupp && rest == 0) break;
            }
        }
    }
}

int beMeterCtrl_OnMessageText(beMeterCtrl *self, beBaseInfoRam *ram, int message) {
    beMeterCtrlOneData *s1;
    igObjectList *l;
    float f0, f2, f3, v;
    const char *s3;
    int s0;
    igObject *o;
    l = (igObjectList *)((beMeterCtrlInfo *)ram->_parentInfo)->_oneDataList;
    s1 = ((beMeterCtrlOneData **)l->_data)[ram->_ramNo];
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beMeterCtrl_GetMsgActionEnum(), (const char *)message)) {
    case 0:
        beMessenger_AppendFloat((beMessenger *)self->_messenger, s1->_nowValueF);
        return 1;
    case 1:
        f0 = beMessenger_GetFloat((beMessenger *)self->_messenger, 0);
        s1->_nowValueF = f0;
        s1->_dspValueF = f0;
        s1->_isChange = 1;
        return 1;
    case 2:
        v = beMessenger_GetFloat((beMessenger *)self->_messenger, 0);
        v += s1->_nowValueF;
        if (v > s1->_maxValueF) v = s1->_maxValueF; else if (v < 0.0f) v = 0.0f;
        s1->_nowValueF = v;
        return 1;
    case 3:
        beMessenger_AppendFloat((beMessenger *)self->_messenger, s1->_nowValueF / s1->_maxValueF);
        return 1;
    case 4:
        if (s1->_hp == 0) {
            SetNowPercent(s1, beMessenger_GetFloat((beMessenger *)self->_messenger, 0));
        }
        return 1;
    case 5:
        f2 = s1->_maxValueF;
        v = beMessenger_GetFloat((beMessenger *)self->_messenger, 0); v = (v * f2) / 100.0f;
        v += s1->_nowValueF;
        if (v > s1->_maxValueF) v = s1->_maxValueF; else if (v < 0.0f) v = 0.0f;
        s1->_nowValueF = v;
        return 1;
    case 6:
        s1->_maxValueF = beMessenger_GetFloat((beMessenger *)self->_messenger, 0);
        beMeterCtrl_SetupMaxValue(self, s1);
        return 1;
    case 7:
        s3 = beMessenger_GetString((beMessenger *)self->_messenger, 0);
        s0 = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        beMessenger_PushArgContext((beMessenger *)self->_messenger);
        beMessenger_SendNamed((beMessenger *)self->_messenger, (const char *)MODELCTRL_11, s3, s0, (const char *)GETHP_2);
        o = beMessenger_GetObject((beMessenger *)self->_messenger, 0);
        if (o != 0) o->_refCount = o->_refCount + 1;
        {
            igObject *old = (igObject *)s1->_hp;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        s1->_hp = (int)o;
        o = beMessenger_GetObject((beMessenger *)self->_messenger, 1);
        if (o != 0) o->_refCount = o->_refCount + 1;
        {
            igObject *old = (igObject *)s1->_mHp;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
            }
        }
        s1->_mHp = (int)o;
        beMessenger_PopArgContext((beMessenger *)self->_messenger);
        return 1;
    default:
        return 0;
    }
}

igMetaObject *beMeterCtrl_GetMeta(void)
{
    return g_beMeterCtrl_metaObject;
}
