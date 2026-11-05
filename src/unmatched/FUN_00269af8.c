/* 0x00269af8 — FUN_00269af8 (148 bytes). Runs the decode pump (FUN_00268960) and accumulates its output count at +44 until +48 reaches +60, then marks the input ended (+3); once ended, FUN_00268a10 drains and a positive result sets the state byte (+1) to 3. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Decoder_269af8 {
    signed char pad0;
    signed char state;      /* 0x01 */
    signed char pad2;
    signed char ended;      /* 0x03 */
    char pad4[40];
    int decoded;            /* 0x2c */
    int position;           /* 0x30 */
    char pad52[8];
    int end;                /* 0x3c */
} Decoder_269af8;

int FUN_00268960(Decoder_269af8 *decoder);
int FUN_00268a10(Decoder_269af8 *decoder);

void FUN_00269af8(Decoder_269af8 *decoder) {
    int count;

    /* matching construct: goto — retail re-tests the ended flag after setting it; structured loops reorder the blocks */
loop:
    if (decoder->ended == 0) {
        while ((count = FUN_00268960(decoder)) != 0) {
            decoder->decoded += count;
            if (decoder->position >= decoder->end) {
                decoder->ended = 1;
                goto loop;
            }
        }
        return;
    }
    if (FUN_00268a10(decoder) > 0) {
        decoder->state = 3;
    }
}

