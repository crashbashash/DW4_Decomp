/* Reports DAT_004ee8e0 for a null object; otherwise sets the sector count at 62 to 85% of the one
 * at 60 and, when a request is attached, passes both as byte counts to FUN_0026a9d8. */
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

typedef struct Object_26ba68 {
    char pad0[8];
    Request_269ff0 *request;    /* 0x08 */
    char pad12[4];
    int f16;                    /* 0x10 */
    char pad20[40];
    short f60;                  /* 0x3c: sectors */
    short f62;                  /* 0x3e: sectors */
} Object_26ba68;

extern char DAT_004ee8e0[];
void FUN_002607e8(const char *message);
int FUN_0026a9d8(Request_269ff0 *request, int a, int b);

void FUN_0026c898(Object_26ba68 *object) {
    short total;
    Request_269ff0 *request;

    if (object == 0) {
        FUN_002607e8(DAT_004ee8e0);
        return;
    }
    total = object->f60;
    request = object->request;
    /* The constant is 0x3F599999, one ulp below 0.85f: it is folded from 1.0f - 0.15f. */
    object->f62 = total * (1.0f - 0.15f);
    if (request != 0) {
        FUN_0026a9d8(request, object->f62 << 11, total << 11);
    }
}
