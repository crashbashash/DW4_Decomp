#include "dw4/reflected.h"

extern "C" void Gap__Bec__beActionStarter__vfunc_32(void);
extern "C" int Gap__Bec__beActionStarter__vfunc_30(void);
extern "C" void Gap__Bec__beActionStarter__vfunc_31(void);
extern "C" int Gap__Bec__beActionStarter__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" void beMessenger_AppendBool(int, unsigned char);
extern "C" void beMessenger_AppendFloat(int, float);
extern "C" void beMessenger_AppendString(int, int *);
extern "C" void beMessenger_AppendVec3(int, float *);
extern "C" void beMessenger_DispatchSelected(int, int *);
extern "C" void beMessenger_SelectReceivers(int, int *, int, int);
extern "C" void beMessenger_SetRunCheck(int, unsigned char);
extern "C" int Gap__Core__igObject__vfunc_33(void);
extern "C" int g_beActionStarterInfo_metaObject[4];
extern "C" int g_beActionStarter_metaObject[4];
extern "C" char DAT_0050e110[];
extern "C" void Gap__Bec__beActionStarter__vfunc_29(beActionStarter * p0, int p1, char * p2, int p3, int p4);
extern "C" int emptyString[4];
extern "C" int DAT_0050e128[4];
extern "C" int DAT_0050e138[4];
extern "C" int g_beActionStarterData2_metaObject[4];
/* matching construct: dummy-virtual class (20 slots) so getKind() compiles to the retail jalr; the element data is read through beActionStarterData2 below. */
struct ActionStarterDataVTable {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual int getKind();
 };
extern "C" int Gap__Bec__beActionStarter__vfunc_34(beActionStarter *arg0, beActionStarterInfoRam *arg1, int *arg2);

void Gap__Bec__beActionStarter__vfunc_32(void)
{
}

void Gap__Bec__beActionStarter__vfunc_29(beActionStarter * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, DAT_0050e110, 0, -1);
}

int Gap__Bec__beActionStarter__vfunc_30(void)
{
    return g_beActionStarterInfo_metaObject[0];
}

void Gap__Bec__beActionStarter__vfunc_31(void)
{
}

int Gap__Bec__beActionStarter__vfunc_34(beActionStarter *arg0, beActionStarterInfoRam *arg1, int *arg2) {
    float vA[3];
    float vB[3];
    beActionStarterInfo *s7 = (beActionStarterInfo *)arg1->_parentInfo;
    bool a3 = false;
    int s8 = arg2[5];
    int s4 = arg2[3];
    int spA0 = arg2[4];
    int a1;
    igDataList *a0 = (igDataList *)s7->_modelList;
    a1 = 0;
    if (0 < *(int *)&a0->_count) {
        int **v1 = (int **)a0->_data;
        do {
            int *v0 = (int *)(*v1)[2];
            v0 = v0 != 0 ? v0 : &emptyString[0];
            if (s4 == (int)v0) {
                a3 = true;
                break;
            }
            a1 += 1;
            v1 += 1;
        } while (a1 < a0->_count);
    }
    if (!a3) {
        return 1;
    }
    {
        igDataList *s6 = (igDataList *)((int *)((int *)a0->_data)[a1])[3];
        int s3 = 0;
        if (0 < s6->_count) {
            int s0 = 0;
            do {
                ActionStarterDataVTable *s2 = (ActionStarterDataVTable *)((int *)s6->_data)[s0];
                beActionStarterData2 *d = (beActionStarterData2 *)s2;
                int *v0 = (int *)d->_name;
                v0 = v0 != 0 ? v0 : &emptyString[0];
                if ((int)v0 == s8) {
                    int *n;
                    beMessenger_SelectReceivers(arg0->_messenger, &DAT_0050e128[0], s4, spA0);
                    n = (int *)s7->_name;
                    n = n != 0 ? n : &emptyString[0];
                    beMessenger_AppendString(arg0->_messenger, n);
                    beMessenger_AppendString(arg0->_messenger, (int *)d->_message);
                    beMessenger_AppendFloat(arg0->_messenger, (float)d->_delay);
                    vA[0] = ((float *)d->_offset)[0];
                    vA[1] = ((float *)d->_offset)[1];
                    vA[2] = ((float *)d->_offset)[2];
                    beMessenger_AppendVec3(arg0->_messenger, vA);
                    beMessenger_AppendBool(arg0->_messenger, d->_isSeqDead);
                    beMessenger_AppendBool(arg0->_messenger, d->_isPositionLock);
                    {
                        int s1 = g_beActionStarterData2_metaObject[0];
                        if (s1 == s2->getKind()) {
                            vB[0] = ((float *)&d->_rotation)[0];
                            vB[1] = ((float *)&d->_rotation)[1];
                            vB[2] = ((float *)&d->_rotation)[2];
                            beMessenger_AppendVec3(arg0->_messenger, vB);
                        }
                    }
                    beMessenger_SetRunCheck(arg0->_messenger, 1);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0050e138[0]);
                }
                s3 += 1;
                s0 += 1;
            } while (s3 < s6->_count);
        }
    }
    return 1;
}

int Gap__Bec__beActionStarter__vfunc_20(void)
{
    return g_beActionStarter_metaObject[0];
}

/* Slot 33 default: always 0. */
int Gap__Core__igObject__vfunc_33(void) {
    return 0;
}

