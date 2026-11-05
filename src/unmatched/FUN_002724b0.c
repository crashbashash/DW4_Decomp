/* 0x002724b0 — FUN_002724b0 (204 bytes). Prints the SRD debug summary: the enter flag (DAT_004a92c4), the last error (DAT_004a92dc), the SRD object's state and device type (1 DVD, 2 HOST) and the read status from FUN_00272460; returns 0. Its messages name the fields (srd_enter_fg, srd_debug_geterror, srd_obj.stat, srd_obj.devtype). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Srd_2724b0 {
    signed char used;       /* 0x00 */
    signed char devtype;    /* 0x01: 1 DVD, 2 host */
    signed char stat;       /* 0x02 */
} Srd_2724b0;

extern Srd_2724b0 DAT_004a9288;
extern int DAT_004a92c4;
extern volatile int DAT_004a92dc;
extern char s_SRD_SRD_Info_004efd58[];                   /* 'SRD: SRD Info.\n' */
extern char s_srd_enter_fg_d_004efd68[];                 /* ' srd_enter_fg       = %d\n' */
extern char s_srd_debug_geterror_d_004efd88[];           /* ' srd_debug_geterror = %d\n' */
extern char s_srd_obj_stat_d_004efda8[];                 /* ' srd_obj.stat       = %d\n' */
extern char s_srd_obj_devtype_DVD_004efdc8[];            /* ' srd_obj.devtype    = DVD\n' */
extern char s_srd_obj_devtype_HOST_004efde8[];           /* ' srd_obj.devtype    = HOST\n' */
extern char s_Read_Status_DVD_2_HST_1_d_004efe08[];      /* ' Read Status(DVD=2/HST=1) = %d\n' */
void FUN_0010d108(const char *format, ...);
int FUN_00272460(void);

int FUN_002724b0(void) {
    FUN_0010d108(s_SRD_SRD_Info_004efd58);
    FUN_0010d108(s_srd_enter_fg_d_004efd68, DAT_004a92c4);
    FUN_0010d108(s_srd_debug_geterror_d_004efd88, DAT_004a92dc);
    FUN_0010d108(s_srd_obj_stat_d_004efda8, DAT_004a9288.stat);
    if (DAT_004a9288.devtype == 1) {
        FUN_0010d108(s_srd_obj_devtype_DVD_004efdc8);
    }
    if (DAT_004a9288.devtype == 2) {
        FUN_0010d108(s_srd_obj_devtype_HOST_004efde8);
    }
    FUN_0010d108(s_Read_Status_DVD_2_HST_1_d_004efe08, FUN_00272460());
    return 0;
}

