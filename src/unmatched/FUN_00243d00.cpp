#include "dw4/reflected.h"
class Ctx { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual igMemoryPool *v21(int); };
struct Pad88 { char p[88]; };
class It : public Pad88 { public: virtual int va(); virtual int vb(); };
struct Node { int f0; int (*fn)(); It *f8; Node *next; };
extern "C" {
int FUN_0023e7c0(...);
int FUN_00241930(...);
int FUN_002caa70(...);
void *Memory_AllocateBufferDirect(...);
Ctx *Memory_GetCurrentContextAlias(...);
extern int DAT_004ea6f0[4];
extern int DAT_004ea700[4];
extern int DAT_004ea718[4];
extern int DAT_004ea730[4];
extern int DAT_004ea748[4];
extern int DAT_004ea760[4];
extern int DAT_004ea778[4];
extern int DAT_004ea790[4];
extern int DAT_004ea7a8[4];
extern int DAT_004ea7b8[4];
extern int DAT_004ea7c8[4];
extern int DAT_0052d5a0[4];
extern int DAT_0052d5b0[4];
extern int DAT_0052d5c0[4];
extern int DAT_0052d5d0[4];
extern int DAT_0052d5e0[4];
extern int DAT_0052d5f0[4];
extern int DAT_0052d600[4];
extern int DAT_0052d610[4];
extern int DAT_0052d620[4];
extern int DAT_0052d630[4];
extern int DAT_0052d640[4];
extern igMemoryPool * DAT_0056de30[4];
extern int DAT_0056de38[4];
extern void * DAT_0056de44[4];
extern void * DAT_0056de48[4];
extern void * DAT_0056de4c[4];
extern void * DAT_0056de50[4];
extern void * DAT_0056de54[4];
extern void * DAT_0056de58[4];
extern void * DAT_0056de5c[4];
extern void * DAT_0056de60[4];
extern void * DAT_0056de64[4];
extern void * DAT_0056de68[4];
extern void * DAT_0056de6c[4];
extern void * DAT_0056de70[4];
extern Node * DAT_0056de90[4];
int FUN_00242560(...);
int FUN_00242590(...);
int FUN_00242630(...);
int FUN_00242710(...);
int FUN_00242790(...);
int FUN_002427c0(...);
int FUN_00242860(...);
int FUN_00242940(...);
int FUN_002429c0(...);
int FUN_002429f0(...);
int FUN_00242aa0(...);
int FUN_00242b80(...);
int FUN_00242c00(...);
int FUN_00242c30(...);
int FUN_00242ce0(...);
int FUN_00242dc0(...);
int FUN_00242e40(...);
int FUN_00242e70(...);
int FUN_00242f20(...);
int FUN_00243000(...);
int FUN_00243080(...);
int FUN_002430b0(...);
int FUN_00243160(...);
int FUN_00243240(...);
int FUN_002432c0(...);
int FUN_002432f0(...);
int FUN_002433a0(...);
int FUN_00243480(...);
int FUN_00243500(...);
int FUN_00243530(...);
int FUN_002435e0(...);
int FUN_002436c0(...);
int FUN_00243740(...);
int FUN_00243770(...);
int FUN_00243810(...);
int FUN_00243890(...);
int FUN_002438c0(...);
int FUN_00243970(...);
int FUN_00243a50(...);
int FUN_00243ad0(...);
int FUN_00243b00(...);
int FUN_00243ba0(...);
int FUN_00243c80(...);
int FUN_002442e0(...);

}
extern "C" void FUN_00243d00(void) {
    Ctx *temp_v0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0_10;
    void *temp_v0_11;
    void *temp_v0_12;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;

    if (DAT_0056de30[0] == 0) {
        temp_v0 = Memory_GetCurrentContextAlias();
        DAT_0056de30[0] = temp_v0->v21(0x10);
        DAT_0056de30[0]->_refCount = (int)((int) (DAT_0056de30[0]->_refCount + 1));
        temp_v0_2 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_2 != 0) {
            FUN_00241930(temp_v0_2, &DAT_004ea6f0[0], 0, &FUN_00242560, 0, &FUN_00242590, &FUN_00242630, &FUN_00242710);
            *(int *)((char *)(temp_v0_2) + 88) = (int)(&DAT_0052d640[0]);
        }
        DAT_0056de44[0] = (void *)(temp_v0_2);
        temp_v0_3 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_3 != 0) {
            FUN_00241930(temp_v0_3, &DAT_004ea700[0], 0, &FUN_00242790, 0, &FUN_002427c0, &FUN_00242860, &FUN_00242940);
            *(int *)((char *)(temp_v0_3) + 88) = (int)(&DAT_0052d630[0]);
        }
        DAT_0056de48[0] = (void *)(temp_v0_3);
        temp_v0_4 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_4 != 0) {
            FUN_00241930(temp_v0_4, &DAT_004ea718[0], 0, &FUN_002429c0, 0, &FUN_002429f0, &FUN_00242aa0, &FUN_00242b80);
            *(int *)((char *)(temp_v0_4) + 88) = (int)(&DAT_0052d620[0]);
        }
        DAT_0056de4c[0] = (void *)(temp_v0_4);
        temp_v0_5 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_5 != 0) {
            FUN_00241930(temp_v0_5, &DAT_004ea730[0], 0, &FUN_00242c00, 0, &FUN_00242c30, &FUN_00242ce0, &FUN_00242dc0);
            *(int *)((char *)(temp_v0_5) + 88) = (int)(&DAT_0052d610[0]);
        }
        DAT_0056de50[0] = (void *)(temp_v0_5);
        temp_v0_6 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_6 != 0) {
            FUN_00241930(temp_v0_6, &DAT_004ea748[0], 0, &FUN_00242e40, 0, &FUN_00242e70, &FUN_00242f20, &FUN_00243000);
            *(int *)((char *)(temp_v0_6) + 88) = (int)(&DAT_0052d600[0]);
        }
        DAT_0056de54[0] = (void *)(temp_v0_6);
        temp_v0_7 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_7 != 0) {
            FUN_00241930(temp_v0_7, &DAT_004ea760[0], 0, &FUN_00243080, 0, &FUN_002430b0, &FUN_00243160, &FUN_00243240);
            *(int *)((char *)(temp_v0_7) + 88) = (int)(&DAT_0052d5f0[0]);
        }
        DAT_0056de58[0] = (void *)(temp_v0_7);
        temp_v0_8 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_8 != 0) {
            FUN_00241930(temp_v0_8, &DAT_004ea778[0], 0, &FUN_002432c0, 0, &FUN_002432f0, &FUN_002433a0, &FUN_00243480);
            *(int *)((char *)(temp_v0_8) + 88) = (int)(&DAT_0052d5e0[0]);
        }
        DAT_0056de5c[0] = (void *)(temp_v0_8);
        temp_v0_9 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_9 != 0) {
            FUN_00241930(temp_v0_9, &DAT_004ea790[0], 0, &FUN_00243500, 0, &FUN_00243530, &FUN_002435e0, &FUN_002436c0);
            *(int *)((char *)(temp_v0_9) + 88) = (int)(&DAT_0052d5d0[0]);
        }
        DAT_0056de60[0] = (void *)(temp_v0_9);
        temp_v0_10 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_10 != 0) {
            FUN_00241930(temp_v0_10, &DAT_004ea7a8[0], 0, &FUN_00243740, 0, &FUN_00243770, &FUN_002442e0, &FUN_00243810);
            *(int *)((char *)(temp_v0_10) + 88) = (int)(&DAT_0052d5c0[0]);
        }
        DAT_0056de64[0] = (void *)(temp_v0_10);
        temp_v0_11 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_11 != 0) {
            FUN_00241930(temp_v0_11, &DAT_004ea7b8[0], 0, &FUN_00243890, 0, &FUN_002438c0, &FUN_00243970, &FUN_00243a50);
            *(int *)((char *)(temp_v0_11) + 88) = (int)(&DAT_0052d5b0[0]);
        }
        DAT_0056de6c[0] = (void *)(temp_v0_11);
        temp_v0_12 = (void *)(Memory_AllocateBufferDirect(0x5C, DAT_0056de30[0]));
        if (temp_v0_12 != 0) {
            FUN_00241930(temp_v0_12, &DAT_004ea7c8[0], 0, &FUN_00243ad0, 0, &FUN_00243b00, &FUN_00243ba0, &FUN_00243c80);
            *(int *)((char *)(temp_v0_12) + 88) = (int)(&DAT_0052d5a0[0]);
        }
        DAT_0056de70[0] = (void *)(temp_v0_12);
        DAT_0056de68[0] = (void *)(DAT_0056de54[0]);
        if (DAT_0056de38[0] == 0) {
            DAT_0056de38[0] = FUN_002caa70(DAT_0056de30[0]);
        }
        {
            Node *n = DAT_0056de90[0];
            for (; n != 0; n = n->next) {
                if (n->f0 == 0) n->f8 = (It *)n->fn();
            }
            n = DAT_0056de90[0];
            for (; n != 0; n = n->next) {
                if (n->f0 == 1) n->f8 = (It *)n->fn();
            }
            n = DAT_0056de90[0];
            for (; n != 0; n = n->next) {
                n->f8->va();
                n->f8->vb();
            }
        }
        DAT_0056de90[0] = 0;
        FUN_0023e7c0();
    }
}
