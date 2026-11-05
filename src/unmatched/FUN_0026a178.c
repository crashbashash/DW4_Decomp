/* 0x0026a178 — FUN_0026a178 (56 bytes). Resets a request: state 3 when it has no sectors, else 2; clears the counters and sets byte 71. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* Request layout shared by FUN_00269ff0 … FUN_0026a300 (offsets from their accesses). */
typedef struct Request_269ff0 {
    char used;          /* 0x00: entries of DAT_004a7f10 with used == 1 are serviced by FUN_0026a908 */
    char state;         /* 0x01: 2 or 3 after FUN_0026a178 (by sectors), polled for 1 by FUN_0026a2a0 */
    char f2;            /* 0x02 */
    char f3;            /* 0x03 */
    char pad4[4];
    int f8;             /* 0x08 */
    int f12;            /* 0x0c */
    int bytes;          /* 0x10: sectors << 11 */
    int sectors;        /* 0x14 */
    char pad24[12];
    int pending;        /* 0x24 */
    int f40;            /* 0x28 */
    char pad44[4];
    int f48;            /* 0x30 */
    int f52;            /* 0x34 */
    char pad56[13];
    char busy;          /* 0x45: set when a request starts, cleared by FUN_0026a0a0 */
    char f70;           /* 0x46 */
    char f71;           /* 0x47 */
    char pad72;
    char f73;           /* 0x49 */
    char pad74[6];
    int f80;            /* 0x50 */
    int f84;            /* 0x54 */
    char pad88[4];
    int f92;            /* 0x5c */
} Request_269ff0;    /* 0x60 bytes: the DAT_004a7f10 entry stride */

void FUN_0026a178(Request_269ff0 *request) {
    request->f52 = 0;
    request->f3 = 0;
    if (request->sectors == 0) {
        request->state = 3;
    } else {
        request->state = 2;
    }
    request->f2 = 0;
    request->pending = 0;
    request->f40 = 0;
    request->f71 = 1;
}
