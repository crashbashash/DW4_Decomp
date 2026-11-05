/* Warning: missing "jr $ra" in last block of FUN_003ad950 (.L003ADA50). */

extern "C" {
int sceMtapGetConnection(int);
extern int DAT_0058a800[4];
extern int DAT_0058a8f0[4];
extern char GPR_005549dc;
extern char GPR_00554e5c;
void FUN_003ad950(int arg0, void *arg1);
}

void FUN_003ad950(int arg0, void *arg1) {
    if (DAT_0058a8f0[0] != 0) {
        if (DAT_0058a800[0] > 0) {
            goto block_3;
        }
    } else {
block_3:
        if (sceMtapGetConnection(2) == 1) {
            if (GPR_005549dc == 1) {
                GPR_00554e5c = 0;
                DAT_0058a800[0] = 0;
            } else {
                DAT_0058a800[0] += 1;
                if (DAT_0058a800[0] >= 3) {
                    DAT_0058a800[0] = 0;
                    GPR_00554e5c = 1;
                    GPR_005549dc = 1;
                }
            }
        } else if (GPR_005549dc == -1) {
            GPR_00554e5c = 0;
            DAT_0058a800[0] = 0;
        } else {
            DAT_0058a800[0] += 1;
            if (DAT_0058a800[0] >= 3) {
                DAT_0058a800[0] = 0;
                GPR_00554e5c = -1;
                GPR_005549dc = -1;
            }
        }
        *(char *)((char *)(arg1) + 40) = (char) GPR_005549dc;
        *(char *)((char *)(arg1) + 41) = (char) GPR_00554e5c;
    }
}
