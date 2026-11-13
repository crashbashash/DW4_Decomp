#define D_STADR ((unsigned int *)0x1000E060)

unsigned int sceDmaPutStallAddr(unsigned int addr) {
    unsigned int old = *D_STADR;
    *D_STADR = addr;
    return old;
}
