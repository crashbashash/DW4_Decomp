/* CRI ADXT handle thunk: forwards the stream handle stored at +4 to the
 * worker at 0x25db28. */
typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025db28(int stm);

void FUN_002672a0(Adxt *adxt)
{
    FUN_0025db28(adxt->stm);
}
