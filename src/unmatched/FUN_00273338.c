/* 0x00273338 — FUN_00273338 (408 bytes). Creates DTX object id (0..15) in DAT_004a9b30: checks the work-area alignment (EE 64, IOP 32, length 64*N), creates the server side with FUN_002731a8, records the work areas (the EE one also through its uncached 0x20000000 alias), clears and writes back the EE work area (FUN_0010b7d8, FUN_0010b918), installs the FUN_00273268/FUN_00273280 callbacks and marks the object used. Returns it, or 0 with a message on failure. Its messages name it DTX_Create (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Dtx_273338 {
    signed char used;       /* 0x00 */
    signed char state;      /* 0x01 */
    signed char flag;       /* 0x02 */
    char pad3;
    int server;             /* 0x04 */
    int f8;             /* 0x08 */
    char *eewk;             /* 0x0c */
    int size;               /* 0x10: wklen - 64 */
    int eewk_uncached;      /* 0x14 */
    int iopwk;              /* 0x18 */
    int wklen;              /* 0x1c */
    void (*callback32)();   /* 0x20 */
    int f36;            /* 0x24 */
    void (*callback40)();   /* 0x28 */
    int f44;            /* 0x2c */
    char pad48[20];
} Dtx_273338;               /* 0x44 bytes */

extern Dtx_273338 DAT_004a9b30[16];
extern char eewk_is_not_alignment_64_byte[];          /* 'eewk is not alignment 64 byte\n' */
extern char iopwk_is_not_alignment_32_byte[];         /* 'iopwk is not alignment 32 byte\n' */
extern char wklen_d_is_not_64_N[];                    /* 'wklen=%d is not 64*N\n' */
extern char illeagal_ID_d[];                          /* 'illeagal ID (%d) \n' */
extern char DTX_Create_can_t_create_DTX_of_server[];  /* "DTX_Create: can't create DTX of server\n" */
void FUN_002659a0(const char *format, ...);
int FUN_002731a8(unsigned int id, char *eewk, int iopwk, int wklen);
void *memset(void *dst, int value, unsigned int n);
void FUN_0010b7d8(void *start, void *end);
void FUN_0010b918(void *start, void *end);
void FUN_00273268();
void FUN_00273280();

Dtx_273338 *FUN_00273338(unsigned int id, char *eewk, int iopwk, int wklen) {
    Dtx_273338 *dtx;
    int size;

    if ((int)eewk & 63) {
        FUN_002659a0(eewk_is_not_alignment_64_byte);
        return 0;
    }
    if (iopwk & 31) {
        FUN_002659a0(iopwk_is_not_alignment_32_byte);
        return 0;
    }
    if (wklen & 63) {
        FUN_002659a0(wklen_d_is_not_64_N, wklen);
        return 0;
    }
    if (id >= 16) {
        FUN_002659a0(illeagal_ID_d, id);
        return 0;
    }
    dtx = &DAT_004a9b30[id];
    if (dtx->used != 0) {
        return 0;
    }
    dtx->server = FUN_002731a8(id, eewk, iopwk, wklen);
    if (dtx->server == 0) {
        FUN_002659a0(DTX_Create_can_t_create_DTX_of_server);
        return 0;
    }
    size = wklen - 64;
    dtx->size = size;
    dtx->wklen = wklen;
    dtx->iopwk = iopwk;
    dtx->eewk_uncached = (int)(eewk + size) | 0x20000000;
    dtx->f8 = 0;
    dtx->eewk = eewk;
    dtx->state = 0;
    memset(eewk, 0, size);
    FUN_0010b7d8(dtx->eewk, dtx->eewk + dtx->size + 63);
    FUN_0010b918(dtx->eewk, dtx->eewk + dtx->size + 63);
    /* matching construct: statement-order sweep — order of the final field stores */
    dtx->callback32 = FUN_00273268;
    dtx->callback40 = FUN_00273280;
    dtx->f36 = 0;
    dtx->f44 = 0;
    dtx->flag = 1;
    dtx->used = 1;
    return dtx;
}

