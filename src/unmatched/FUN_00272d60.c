/* SRD server step: returns early while any of the 32 request slots of DAT_004a9310 (64-byte
 * entries) in state 1/1 still has its SIF DMA (+44) in flight (sceSifDmaStat >= 0); otherwise runs
 * FUN_002729e8 on every active slot (byte 0 == 1) and finishes with FUN_00273928. */
typedef struct Slot_272d60 {
    signed char used;       /* 0x00 */
    signed char phase;      /* 0x01 */
    signed char transfer;   /* 0x02 */
    char pad3[41];
    int dma_id;             /* 0x2c */
    char pad48[16];
} Slot_272d60;              /* 0x40 bytes */

extern Slot_272d60 DAT_004a9310[32];
int sceSifDmaStat(unsigned int id);
void FUN_002729e8(Slot_272d60 *slot);
void FUN_00273928(void);

void FUN_00272d60(void) {
    int i;

    for (i = 0; i < 32; i++) {
        if (DAT_004a9310[i].phase == 1 && DAT_004a9310[i].transfer == 1) {
            if (sceSifDmaStat(DAT_004a9310[i].dma_id) >= 0) {
                return;
            }
        }
    }
    for (i = 0; i < 32; i++) {
        if (DAT_004a9310[i].used == 1) {
            FUN_002729e8(&DAT_004a9310[i]);
        }
    }
    FUN_00273928();
}

