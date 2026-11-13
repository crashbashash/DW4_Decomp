#include "dw4/cri/sfdsj.h"

#define PS2RNA_MAX_PSJ 32
#define PS2RNA_DEF_NVOICE 16
#define PS2RNA_DEF_IOP_WKSIZE 0x41000
#define PS2RNA_RMT_WKSIZE 256      /* IOP work per SJRMT */
#define PS2RNA_UNI_WKSIZE 256      /* EE work per SJUNI */
#define PS2RNA_PSJ_BUFSIZE 0x4000  /* IOP buffer per voice */

enum { SJ_LIN_FREE = 0 };

/* One voice's stream path (24 bytes): IOP-side SJ, EE-side SJ and the SJX joining them. */
typedef struct RnaPsj {
    char used;          /* 0x00 */
    void *sjrmt;        /* 0x04 */
    SfdSj *sjuni;       /* 0x08 */
    void *sjx;          /* 0x0c */
    SfdSjChunk ck;      /* 0x10: the IOP buffer, handed to sjuni as free space */
} RnaPsj;

void ADXMSG_PrintErr(const char *format, ...);
void *sceSifAllocIopHeap(int size);
void *memset();
void *SJRMT_Create(int mode, int work, int size);
SfdSj *SJUNI_Create(int mode, char *work, int size);
void *SJX_Create(SfdSj *sjuni, void *sjrmt, int mode);

extern char PS2RNA_E01112903_Failed_sceSifAllocIopHeap_in_ps2rna_init_psj[];
extern char PS2RNA_sceSifAllocIopHeap_d_ret_0x_08x[];
extern char E0110101_ps2rna_init_psj_wk_size_error[];
extern char E0110102_ps2rna_init_psj_can_t_creat_SJUNI_CreaetRmt[];
extern char E0110103_ps2rna_init_psj_wk_size_error[];
extern char E0110104_ps2rna_init_psj_can_t_creat_SJUNI_Creaet[];
extern char E0110105_ps2rna_init_psj_can_t_creat_SJX_Create[];
extern int ps2rna_nvoice;
extern int ps2rna_iop_wksize;
extern int ps2rna_setup_voice;
extern int ps2rna_iop_heap;
extern int ps2rna_iop_work;
extern char ps2rna_iop_alloced;
extern RnaPsj ps2rna_psj[PS2RNA_MAX_PSJ];
extern char ps2rna_psj_buf[PS2RNA_MAX_PSJ][PS2RNA_UNI_WKSIZE];

/* Allocates the IOP work once and builds one SJRMT/SJUNI/SJX path per voice; any failure hangs. */
void ps2rna_init_psj(void)
{
    RnaPsj *psj;
    int work;
    int i;

    if (ps2rna_setup_voice == 0) {
        ps2rna_nvoice = PS2RNA_DEF_NVOICE;
        ps2rna_iop_wksize = PS2RNA_DEF_IOP_WKSIZE;
    }
    if (ps2rna_iop_heap == 0) {
        ps2rna_iop_heap = (int)sceSifAllocIopHeap(ps2rna_iop_wksize + 64);
        if (ps2rna_iop_heap == 0) {
            ADXMSG_PrintErr(PS2RNA_E01112903_Failed_sceSifAllocIopHeap_in_ps2rna_init_psj, ps2rna_iop_wksize + 64);
            for (;;) {
            }
        }
        ADXMSG_PrintErr(PS2RNA_sceSifAllocIopHeap_d_ret_0x_08x, ps2rna_iop_wksize + 64, ps2rna_iop_heap);
        ps2rna_iop_work = (ps2rna_iop_heap + 64) & ~63;
        ps2rna_iop_alloced = 1;
    }
    memset(ps2rna_psj, 0, sizeof(ps2rna_psj));
    work = ps2rna_iop_work;
    for (i = 0; i < ps2rna_nvoice; i++) {
        psj = &ps2rna_psj[i];
        psj->used = 0;
        if (work & 63) {
            ADXMSG_PrintErr(E0110101_ps2rna_init_psj_wk_size_error);
            for (;;) {
            }
        }
        psj->sjrmt = SJRMT_Create(1, work, PS2RNA_RMT_WKSIZE);
        work += PS2RNA_RMT_WKSIZE;
        if (psj->sjrmt == 0) {
            ADXMSG_PrintErr(E0110102_ps2rna_init_psj_can_t_creat_SJUNI_CreaetRmt);
            for (;;) {
            }
        }
        if (work & 63) {
            ADXMSG_PrintErr(E0110103_ps2rna_init_psj_wk_size_error);
            for (;;) {
            }
        }
        psj->sjuni = SJUNI_Create(1, ps2rna_psj_buf[i], PS2RNA_UNI_WKSIZE);
        if (psj->sjuni == 0) {
            ADXMSG_PrintErr(E0110104_ps2rna_init_psj_can_t_creat_SJUNI_Creaet);
            for (;;) {
            }
        }
        psj->ck.len = PS2RNA_PSJ_BUFSIZE;
        psj->ck.data = (char *)work;
        psj->sjuni->vtbl->putChunk(psj->sjuni, SJ_LIN_FREE, &psj->ck);
        work += PS2RNA_PSJ_BUFSIZE;
        psj->sjx = SJX_Create(psj->sjuni, psj->sjrmt, 1);
        if (psj->sjx == 0) {
            ADXMSG_PrintErr(E0110105_ps2rna_init_psj_can_t_creat_SJX_Create);
            for (;;) {
            }
        }
    }
}
