/* CRI ADXT handle thunk: forwards the stream handle stored at +4 to the
 * worker at 0x25db60. */
typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db60(int stm);

void FUN_00267330(Adxt *adxt)
{
    FUN_0025db60(adxt->stm);
}
