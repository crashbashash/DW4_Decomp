/* 0x002724b0 — FUN_002724b0 (204 bytes). Prints the SRD debug summary: the enter flag (DAT_004a92c4), the last error (DAT_004a92dc), the SRD object's state and device type (1 DVD, 2 HOST) and the read status from FUN_00272460; returns 0. Its messages name the fields (srd_enter_fg, srd_debug_geterror, srd_obj.stat, srd_obj.devtype). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Srd_2724b0 {
    signed char used;       /* 0x00 */
    signed char devtype;    /* 0x01: 1 DVD, 2 host */
    signed char stat;       /* 0x02 */
} Srd_2724b0;

extern Srd_2724b0 DAT_004a9288;
extern int DAT_004a92c4;
extern volatile int DAT_004a92dc;
extern char SRD_SRD_Info[];                   /* 'SRD: SRD Info.\n' */
extern char srd_enter_fg_d[];                 /* ' srd_enter_fg       = %d\n' */
extern char srd_debug_geterror_d[];           /* ' srd_debug_geterror = %d\n' */
extern char srd_obj_stat_d[];                 /* ' srd_obj.stat       = %d\n' */
extern char srd_obj_devtype_DVD[];            /* ' srd_obj.devtype    = DVD\n' */
extern char srd_obj_devtype_HOST[];           /* ' srd_obj.devtype    = HOST\n' */
extern char Read_Status_DVD_2_HST_1_d[];      /* ' Read Status(DVD=2/HST=1) = %d\n' */
void FUN_0010d108(const char *format, ...);
int FUN_00272460(void);

int FUN_002724b0(void) {
    FUN_0010d108(SRD_SRD_Info);
    FUN_0010d108(srd_enter_fg_d, DAT_004a92c4);
    FUN_0010d108(srd_debug_geterror_d, DAT_004a92dc);
    FUN_0010d108(srd_obj_stat_d, DAT_004a9288.stat);
    if (DAT_004a9288.devtype == 1) {
        FUN_0010d108(srd_obj_devtype_DVD);
    }
    if (DAT_004a9288.devtype == 2) {
        FUN_0010d108(srd_obj_devtype_HOST);
    }
    FUN_0010d108(Read_Status_DVD_2_HST_1_d, FUN_00272460());
    return 0;
}

