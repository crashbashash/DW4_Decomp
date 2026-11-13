#define D_CHCR_STR_BIT 8

/* Writes back the channel control word sceDmaPause returned; the result is whether the channel was running. */
unsigned int sceDmaRestart(unsigned int *chcr, unsigned int stat) {
    unsigned int old = *chcr;
    *chcr = stat;
    return (old >> D_CHCR_STR_BIT) & 1;
}
