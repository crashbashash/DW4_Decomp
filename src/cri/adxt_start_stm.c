/* Restarts the request of an object: sets its sizes from the halfword sector counts at 62 and 60,
 * applies adxt_stm_eos through ADXSTM_SetEos, resets it (ADXSTM_EntryEosFunc, FUN_0026a140, FUN_0026a238,
 * FUN_0026a0a0), starts it with FUN_00269ff0 and FUN_0026a1b0, then calls FUN_0026b978(object,
 * field 16). */
/* Request layout shared by FUN_00269ff0 through ADXSTM_SetEos. */
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

typedef struct Object_26ba68 {
    char pad0[8];
    Request_269ff0 *request;    /* 0x08 */
    char pad12[4];
    int f16;                    /* 0x10 */
    char pad20[40];
    short f60;                  /* 0x3c: sectors */
    short f62;                  /* 0x3e: sectors */
} Object_26ba68;

extern int adxt_stm_eos;
int FUN_0026a9d8(Request_269ff0 *request, int a, int b);
void ADXSTM_SetEos(Request_269ff0 *request, int value);
void ADXSTM_EntryEosFunc(Request_269ff0 *request, int a, int b);
void FUN_0026a140(Request_269ff0 *request, int value);
void FUN_0026a238(Request_269ff0 *request);
void FUN_0026a0a0(Request_269ff0 *request);
void FUN_00269ff0(Request_269ff0 *request, int f80, int f84, int f12, int sectors);
int FUN_0026a1b0(Request_269ff0 *request);
void FUN_0026b978(Object_26ba68 *object, int value);

void adxt_start_stm(Object_26ba68 *object, int f80, int f84, int f12, int sectors) {
    FUN_0026a9d8(object->request, object->f62 << 11, object->f60 << 11);
    ADXSTM_SetEos(object->request, adxt_stm_eos);
    ADXSTM_EntryEosFunc(object->request, 0, 0);
    FUN_0026a140(object->request, 0);
    FUN_0026a238(object->request);
    FUN_0026a0a0(object->request);
    FUN_00269ff0(object->request, f80, f84, f12, sectors);
    FUN_0026a1b0(object->request);
    FUN_0026b978(object, object->f16);
}
