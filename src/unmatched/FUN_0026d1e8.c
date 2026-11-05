/* CRI ADXT_GetDecDtLen: null handle reports "E04041901 ADXT_GetDecDtLen:
 * parameter error" (string at 0x4eec20) and yields -1, otherwise the call is
 * forwarded to the stream-handle routine with the stream stored at +4. */
typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern char D_004eec20[];
extern void FUN_002607e8(char *msg);
extern int FUN_002670b8(int stm);

int FUN_0026d1e8(Adxt *adxt)
{
    if (adxt == 0) {
        FUN_002607e8(D_004eec20);
        return -1;
    }
    return FUN_002670b8(adxt->stm);
}
