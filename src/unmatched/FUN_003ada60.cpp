/* One poll of the memory-card connection check: while a card-info request is in flight its result
 * records the polled slot's type and free space; otherwise the next connected slot is chosen and a
 * new request is issued, or the format results of the pending check are collected. */
struct CardSlot { int port; int slot; };
typedef struct ConnectCheckState {
    char header[64];
    int types[8];            /* +64 */
    int frees[8];            /* +96 */
    int slot;                /* +128 */
    int pad132;
    int type;                /* +136 */
    int free;                /* +140 */
} ConnectCheckState;
extern "C" {
int sceMcSync(int, int *, int *);
int FUN_00119ff0(int, int, int, int *, int *);
int FUN_003ad850(ConnectCheckState *, int);
extern CardSlot DAT_004c91b0[];
extern int DAT_0058a810[8];
extern int DAT_0058a830[];
extern int DAT_0058a890[];
extern unsigned char GPR_00554e60;
extern unsigned char GPR_00554e64;
void FUN_003ada60(ConnectCheckState *check);
}

void FUN_003ada60(ConnectCheckState *check) {
    if (GPR_00554e64 == 1) {
        int result;
        int cmd;
        result = 0;
        cmd = 0;
        int done = sceMcSync(1, &cmd, &result);
        if (done != 0 && done == 1) {
            switch (result) {
            case 0:
            case -2:
            case -1:
                DAT_0058a810[check->slot] = 1;
                check->types[check->slot] = check->type;
                check->frees[check->slot] = check->free;
                break;
            default:
                DAT_0058a810[check->slot] = 0;
                break;
            }
            GPR_00554e64 = 0;
            if (!GPR_00554e60) {
                int count = FUN_003ad850(check, 1);
                bool found = false;
                int tries;
                for (tries = 1; tries < count + 1; tries++) {
                    int s = (check->slot + tries) % count;
                    if (DAT_0058a810[s] == 0) {
                        check->slot = s;
                        found = true;
                        break;
                    }
                }
                if (found == true) {
                    FUN_00119ff0(DAT_004c91b0[check->slot].port, DAT_004c91b0[check->slot].slot, 0, &check->type, &check->free);
                    GPR_00554e64 = 1;
                }
            }
        }
    } else if (GPR_00554e60 == 1) {
        int result;
        int cmd;
        result = 0;
        cmd = 0;
        int done = sceMcSync(1, &cmd, &result);
        if (done != 0 && done == 1) {
            if (cmd > 0 && cmd < 22 && DAT_0058a830[cmd] == 1) {
                DAT_0058a890[cmd] = result;
                DAT_0058a830[cmd] = 2;
            }
        }
    } else {
        int count = FUN_003ad850(check, 0);
        check->slot = 0;
        bool found = false;
        int s;
        for (s = 0; s < count; s++) {
            if (DAT_0058a810[s] == 0) {
                check->slot = s;
                found = true;
                break;
            }
        }
        if (found == true) {
            FUN_00119ff0(DAT_004c91b0[check->slot].port, DAT_004c91b0[check->slot].slot, 0, &check->type, &check->free);
            GPR_00554e64 = 1;
        }
    }
}
