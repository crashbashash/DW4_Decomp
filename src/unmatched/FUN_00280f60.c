/* Sends a pair of 32-word tables to FUN_00281a00 (request 0x300) and, if it returns 0, keeps a
 * copy of them in the context. */
int FUN_00281a00();

struct Tables00280f60 {
    int first[32];  /* +0 */
    int second[32]; /* +128 */
};

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx00280f60 {
    char pad0[2728];
    char busy;                       /* +2728: set on entry */
    char pad2729[5028 - 2729];
    struct Tables00280f60 tables;    /* +5028: copy kept after a successful send */
};

extern struct Ctx00280f60 *DAT_004bb114;

int FUN_00280f60(struct Tables00280f60 *tables) {
    struct Tables00280f60 request;
    int result;
    int i;

    DAT_004bb114->busy = 1;
    for (i = 0; i < 32; i++) {
        request.first[i] = tables->first[i];
        request.second[i] = tables->second[i];
    }
    result = FUN_00281a00(0x300, &request, 64, 4);
    if (result == 0) {
        for (i = 0; i < 32; i++) {
            DAT_004bb114->tables.first[i] = tables->first[i];
            DAT_004bb114->tables.second[i] = tables->second[i];
        }
    }
    return result;
}
