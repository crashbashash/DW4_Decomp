#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
extern "C" {
beUnicodeObj *FUN_003614f0(int);
int beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
int sprintf(...);
int TextOrder_ConfigureFont(...);
int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
int FUN_003ec120(...);
int Memory_GetAllocatorBySelector(...);
int *beDataBase_GetRecordString(...);
int beMessenger_GetObject(...);
int beMessenger_SendNamed(...);
int igObject_GetAllocator(...);
int strcmp(...);
typedef struct SlotEnt { int name; int val; int val2; } SlotEnt;
extern SlotEnt DAT_004cec70[16];
extern int DAT_00516c40[4];
extern int DAT_00516c50[4];
extern int DAT_00516c60[4];
extern int DAT_00516c68[4];
extern int DAT_00516c78[4];
extern int DAT_00516c80[4];
extern int DAT_00516c90[4];
extern int DAT_00516c98[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;

}
struct SlotDisplay { char p0[40]; unsigned char used; char p2[7]; int model; char p3[4]; int level; int hp; int maxHp; int mp; int maxMp; };
struct AreaCell { char p[12]; igObjectList *displays; };
struct AreaRow { char p[32]; AreaCell *cell; };
struct SlotBackend { char p[36]; igObjectList *ownDisplays; igObjectList *areas; };
struct SlotPanel { char p0[8]; int messenger; char p1[4]; int textCtrl; SlotBackend *backend; int player; int side; char p2[8]; int source; int index; };
/* Owning stack reference to the slot's text object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */

extern "C" void FUN_003d9ec0(SlotPanel *arg0) {
    SlotBackend *v1 = arg0->backend;
    unsigned short *dA, *dB, *srcA, *srcB; int iA, iB;
    if (arg0->side == 0) {
        SlotDisplay *s0;
        int sp90[8];
        if (arg0->source == 0) {
            s0 = ((SlotDisplay **)((AreaRow **)v1->areas->_data)[arg0->player]->cell->displays->_data)[arg0->index];
        } else {
            s0 = ((SlotDisplay **)v1->ownDisplays->_data)[arg0->player];
        }
        if (s0->used == 1) {
            int a, s5, s4, s3;
            SlotEnt *s2;
            a = igObject_GetAllocator(arg0);
            {
                igSmartPointer<beUnicodeObj> text(FUN_003614f0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0])));
                beUnicodeObj_AllocateBuffer(text.p, 8);
                srcA = (unsigned short *)((char *)s0 + 8);
                iA = 0;
                dA = (unsigned short *)text.p->_buffer;
                for (;;) {
                    dA[iA] = srcA[iA + 1];
                    if (dA[iA] == 0) break;
                    iA += 1;
                    if (iA >= 8) break;
                }
                for (; iA < 8; iA++) {
                    dA[iA] = 0;
                }
                FUN_003ec120(arg0->textCtrl, DAT_00516c40, arg0->player, 0, text.p, 0, 0);
            }
            beMessenger_SendNamed(arg0->messenger, DAT_00516c50, DAT_00516c60, 0, DAT_00516c68);
            s4 = beMessenger_GetObject(arg0->messenger, 0);
            s3 = 0;
            s2 = DAT_004cec70;
        lsA:
            if (strcmp(s2->name, s0->model) == 0) {
                s5 = s3;
            } else {
                s3 += 1;
                s2 += 1;
                if (s3 < 16) goto lsA;
            }
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 10, beDataBase_GetRecordString(s4, s5, DAT_00516c78), 0, 0);
            sprintf(sp90, DAT_00516c90, s0->level);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 0, sp90, 1, 0);
            sprintf(sp90, DAT_00516c90, s0->hp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 0, sp90, 2, 0);
            sprintf(sp90, DAT_00516c90, s0->maxHp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 10, sp90, 2, 0);
            sprintf(sp90, DAT_00516c90, s0->mp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 1, sp90, 2, 0);
            sprintf(sp90, DAT_00516c90, s0->maxMp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 11, sp90, 2, 0);
        } else {
            beNDMWLoadIntf2TextOrder_PublishIdLines(arg0->textCtrl, (arg0->player << 16) | 0x10, 0);
        }
    } else {
        SlotDisplay *s0;
        int sp70[8];
        if (arg0->source == 0) {
            s0 = ((SlotDisplay **)((AreaRow **)v1->areas->_data)[arg0->player]->cell->displays->_data)[arg0->index];
        } else {
            s0 = ((SlotDisplay **)v1->ownDisplays->_data)[arg0->player];
        }
        if (s0->used == 1) {
            int a, s5, s4, s3;
            SlotEnt *s2;
            a = igObject_GetAllocator(arg0);
            {
                igSmartPointer<beUnicodeObj> text(FUN_003614f0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0])));
                beUnicodeObj_AllocateBuffer(text.p, 8);
                srcB = (unsigned short *)((char *)s0 + 8);
                iB = 0;
                dB = (unsigned short *)text.p->_buffer;
                for (;;) {
                    dB[iB] = srcB[iB + 1];
                    if (dB[iB] == 0) break;
                    iB += 1;
                    if (iB >= 8) break;
                }
                for (; iB < 8; iB++) {
                    dB[iB] = 0;
                }
                FUN_003ec120(arg0->textCtrl, DAT_00516c40, arg0->player, 10, text.p, 0, 0);
            }
            beMessenger_SendNamed(arg0->messenger, DAT_00516c50, DAT_00516c60, 0, DAT_00516c68);
            s4 = beMessenger_GetObject(arg0->messenger, 0);
            s3 = 0;
            s2 = DAT_004cec70;
        lsB:
            if (strcmp(s2->name, s0->model) == 0) {
                s5 = s3;
            } else {
                s3 += 1;
                s2 += 1;
                if (s3 < 16) goto lsB;
            }
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 11, beDataBase_GetRecordString(s4, s5, DAT_00516c78), 0, 0);
            sprintf(sp70, DAT_00516c90, s0->level);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c80, arg0->player, 1, sp70, 1, 0);
            sprintf(sp70, DAT_00516c90, s0->hp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 2, sp70, 2, 0);
            sprintf(sp70, DAT_00516c90, s0->maxHp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 12, sp70, 2, 0);
            sprintf(sp70, DAT_00516c90, s0->mp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 3, sp70, 2, 0);
            sprintf(sp70, DAT_00516c90, s0->maxMp);
            TextOrder_ConfigureFont(arg0->textCtrl, DAT_00516c98, arg0->player, 13, sp70, 2, 0);
        } else {
            beNDMWLoadIntf2TextOrder_PublishIdLines(arg0->textCtrl, (arg0->player << 16) | 0x110, 0);
        }
    }
}
