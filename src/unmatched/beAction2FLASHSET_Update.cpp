#include "dw4/reflected.h"
/* The info's _node target: class not recovered, only its list handle at +136 is read. */
extern "C" {
typedef struct Action2NodeList136 { char pad[136]; int list; } Action2NodeList136;
int FUN_003a7e90(beAction2InfoRam *, int *);
int FUN_003a8580(beAction2InfoRam *, int *);
int ObjectList_RemoveFirstRetained(int *, int, int, int);
int igObject_Destroy(igObject *);
extern int DAT_0050dfd0[4];
void beAction2FLASHSET_Update(void *arg0, beAction2InfoRam *arg1);
}

void beAction2FLASHSET_Update(void *arg0, beAction2InfoRam *arg1) {
    int sp4C;
    int sp48;
    int sp44;
    beAction2InfoWork *s1;
    int s0;
    igObject *a0;
    s1 = (beAction2InfoWork *)arg1->_work;
    switch (s1->_flashSt0) {
    case 0:
        break;
    case 1:
        if (FUN_003a7e90(arg1, &DAT_0050dfd0[0]) != 0) {
            s0 = ((Action2NodeList136 *)arg1->_node)->list;
            if (s1->_blendStateAttr == 0) {
                ObjectList_RemoveFirstRetained(&sp4C, s0, s1->_colorAttr, 0);
                a0 = (igObject *)s1->_colorAttr;
                if (a0 != 0) {
                    a0->_refCount = (int)a0->_refCount - 1;
                    if (((unsigned long long)((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(a0);
                    }
                }
                s1->_colorAttr = 0;
                ObjectList_RemoveFirstRetained(&sp48, s0, s1->_lightingStateAttr, 0);
                a0 = (igObject *)s1->_lightingStateAttr;
                if (a0 != 0) {
                    a0->_refCount = (int)a0->_refCount - 1;
                    if (((unsigned long long)((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(a0);
                    }
                }
                s1->_lightingStateAttr = 0;
            }
            ObjectList_RemoveFirstRetained(&sp44, s0, s1->_textureStateAttr, 0);
            a0 = (igObject *)s1->_textureStateAttr;
            if (a0 != 0) {
                a0->_refCount = (int)a0->_refCount - 1;
                if (((unsigned long long)((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(a0);
                }
            }
            s1->_textureStateAttr = 0;
            FUN_003a8580(arg1, &DAT_0050dfd0[0]);
            s1->_flashSt0 = 0;
        }
    }
}
