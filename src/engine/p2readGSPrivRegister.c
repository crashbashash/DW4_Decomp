/* 0x001f8050 p2readGSPrivRegister: read one of the Graphics Synthesizer privileged
 * registers by register number.  The numbers are the GS register-map indices; the
 * memory-mapped address is 0x12000000 + (index << 4) for the display block and
 * 0x12001000 + ((index - 0x40) << 4) for the status block (public PS2 hardware map).
 * An index the function does not serve is reported through printf using the
 * format string "p2readGSPrivRegister(%d)\n" and reads as 0. */
extern char s_p2readGSPrivRegister_004e5130[];
int printf();

/* Register numbers served by the switch below. */
enum GsPrivRegister {
    GSPRIV_PMODE = 0x0,
    GSPRIV_SMODE2 = 0x2,
    GSPRIV_DISPFB1 = 0x7,
    GSPRIV_DISPLAY1 = 0x8,
    GSPRIV_DISPFB2 = 0x9,
    GSPRIV_DISPLAY2 = 0xA,
    GSPRIV_EXTBUF = 0xB,
    GSPRIV_EXTDATA = 0xC,
    GSPRIV_EXTWRITE = 0xD,
    GSPRIV_BGCOLOR = 0xE,
    GSPRIV_CSR = 0x40,
    GSPRIV_IMR = 0x41,
    GSPRIV_BUSDIR = 0x44,
    GSPRIV_SIGLBLID = 0x48
};

/* Memory-mapped 64-bit registers. */
#define GS_PMODE    (*(long long *)0x12000000)
#define GS_SMODE2   (*(long long *)0x12000020)
#define GS_DISPFB1  (*(long long *)0x12000070)
#define GS_DISPLAY1 (*(long long *)0x12000080)
#define GS_DISPFB2  (*(long long *)0x12000090)
#define GS_DISPLAY2 (*(long long *)0x120000A0)
#define GS_EXTBUF   (*(long long *)0x120000B0)
#define GS_EXTDATA  (*(long long *)0x120000C0)
#define GS_EXTWRITE (*(long long *)0x120000D0)
#define GS_BGCOLOR  (*(long long *)0x120000E0)
#define GS_CSR      (*(long long *)0x12001000)
#define GS_IMR      (*(long long *)0x12001010)
#define GS_BUSDIR   (*(long long *)0x12001040)
#define GS_SIGLBLID (*(long long *)0x12001080)

long long p2readGSPrivRegister(int registerIndex) {
    switch (registerIndex) {
    case GSPRIV_PMODE:
        return GS_PMODE;
    case GSPRIV_SMODE2:
        return GS_SMODE2;
    case GSPRIV_DISPFB1:
        return GS_DISPFB1;
    case GSPRIV_DISPLAY1:
        return GS_DISPLAY1;
    case GSPRIV_DISPFB2:
        return GS_DISPFB2;
    case GSPRIV_DISPLAY2:
        return GS_DISPLAY2;
    case GSPRIV_EXTBUF:
        return GS_EXTBUF;
    case GSPRIV_EXTDATA:
        return GS_EXTDATA;
    case GSPRIV_EXTWRITE:
        return GS_EXTWRITE;
    case GSPRIV_BGCOLOR:
        return GS_BGCOLOR;
    case GSPRIV_CSR:
        return GS_CSR;
    case GSPRIV_IMR:
        return GS_IMR;
    case GSPRIV_BUSDIR:
        return GS_BUSDIR;
    case GSPRIV_SIGLBLID:
        return GS_SIGLBLID;
    default:
        printf(s_p2readGSPrivRegister_004e5130, registerIndex);
        return 0;
    }
}
