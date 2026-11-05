/* CRI ADXT handle thunk: forwards the stream handle stored at +4 to the
 * worker at 0x25d830. */
typedef struct Adxt {
    char used;
    signed char state;
    char pad[2];
    int stm;
} Adxt;

extern void FUN_0025d830(int stm);

void FUN_00267130(Adxt *adxt)
{
    FUN_0025d830(adxt->stm);
}
