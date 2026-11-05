/* CRI ADXT handle accessor: reports the ADXT_GetHdrLen parameter error for a
 * null handle ("E02080822 ADXT_GetHdrLen: parameter error", string at 0x4ee6d0),
 * returns 0 until the handle reaches state 2, else forwards the stream
 * handle stored at +4. */
typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern char D_004ee6d0[];
extern void FUN_002607e8(char *msg);
extern int FUN_00267490(int stm);

int FUN_0026c3c8(Adxt *adxt)
{
    if (adxt == 0) {
        FUN_002607e8(D_004ee6d0);
        return -1;
    }
    if (adxt->state >= 2)
        return FUN_00267490(adxt->stm);
    return 0;
}
