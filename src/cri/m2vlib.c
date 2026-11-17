#include "dw4/cri/m2v.h"
#include <string.h>
#include "dw4/cri/mpv.h"

extern char M2VLIB_version_str[];
extern char *volatile m2vlib_version_ptr;
extern unsigned char m2vlib_endian_mark[4];
extern M2vLibWork m2vlib_libwork;
extern M2vObj *m2vlib_m2vobj;

/* A library built for the other byte order stops here. */
#define M2V_CHK_ENDIAN()                      \
    do {                                      \
        if (m2vlib_endian_mark[0] != 4) {     \
            for (;;) {                        \
                ((void (*)(void))-1)();       \
            }                                 \
        }                                     \
    } while (0)

void m2vlib_SetCondAll(int no, M2vCondFn fn);
M2vObj *m2vlib_SearchFreeHn(void);
M2vObj *m2vlib_InitHn(M2vObj *hn);
void m2vlib_InitPicAtr(M2vPicAtr *picatr);
void m2vlib_InitObjTbl(void);
void m2vlib_InitWork(int nobj, char *work, unsigned int size);

char *M2V_GetVersionStr(void)
{
    return M2VLIB_version_str;
}

int M2V_IsConformable(char *buf, int size)
{
    char *p;

    p = MPV_SearchDelim(buf, size, 64);
    if (p == 0) {
        return 0;
    }
    p += 4;
    size -= p - buf;
    if (size <= 0) {
        return 0;
    }
    buf = p;
    p = MPV_SearchDelim(buf, size, -1);
    if (p == 0) {
        return 0;
    }
    if ((MPV_CheckDelim(p) & 0x10) == 0) {
        return 0;
    }
    p += 4;
    size -= p - buf;
    if (size <= 0) {
        return 0;
    }
    return (*(unsigned char *)p >> 4) == 1;
}

/* matching construct: manual — the byte-order check is a do-while(0) macro; as a bare if its load is hoisted into the prologue */
void M2V_Init(int nobj, char *work, unsigned int size)
{
    M2V_CHK_ENDIAN();
    m2vlib_version_ptr = M2VLIB_version_str;
    M2VERR_Init();
    M2VHDEC_Init();
    m2vlib_InitWork(nobj, work, size);
    m2vlib_InitObjTbl();
}

void m2vlib_InitObjTbl(void)
{
    int i;
    int n = m2vlib_libwork.nobj;
    M2vObj *hn = m2vlib_libwork.obj;

    for (i = 0; i < n; i++) {
        hn->stat = 1;
        hn++;
    }
}

void m2vlib_InitWork(int nobj, char *work, unsigned int size)
{
    while (size < nobj * M2V_OBJ_WORK_SIZE + 64) {
        nobj--;
    }
    work = (char *)(((int)work + 63) & ~63);
    memset(work, 0, nobj * M2V_OBJ_WORK_SIZE);
    m2vlib_libwork.nobj = nobj;
    m2vlib_libwork.obj = (M2vObj *)work;
}

void m2vlib_InitPicAtr(M2vPicAtr *picatr)
{
    picatr->horizontal_size = 0;
    picatr->vertical_size = 0;
    picatr->mb_width = 0;
    picatr->mb_height = 0;
    picatr->frame_rate_code = 0;
    picatr->temporal_reference = 0;
    picatr->picture_coding_type = 0;
    picatr->drop_frame_flag = 0;
    picatr->time_code_hours = 0;
    picatr->time_code_minutes = 0;
    picatr->time_code_seconds = 0;
    picatr->time_code_pictures = 0;
    picatr->gsc_count = 0;
    picatr->shc_count = 0;
    picatr->picture_structure = 3;
    picatr->chroma_format = 1;
    picatr->f64 = 0;
    picatr->f68 = 1;
    picatr->bit_rate = 0;
    picatr->vbv_buffer_size = 0;
    picatr->display_horizontal_size = -1;
    picatr->display_vertical_size = -1;
    picatr->field_count = 0;
    picatr->progressive_frame = 1;
    picatr->top_field_first = 0;
    picatr->repeat_first_field = 0;
    picatr->field_964 = 0;
    picatr->aspect_ratio_information = 1;
    picatr->constrained_parameters_flag = 0;
    picatr->frame_rate_extension_n = 0;
    picatr->frame_rate_extension_d = 0;
    picatr->profile_and_level_indication = 255;
    picatr->progressive_sequence = 0;
    picatr->low_delay = 255;
    picatr->video_format = 255;
    picatr->colour_description = 0;
    picatr->colour_primaries = 255;
    picatr->transfer_characteristics = 255;
    picatr->matrix_coefficients = 255;
}

void M2V_Finish(void)
{
}

M2vObj *M2V_Create(void)
{
    M2vObj *hn = m2vlib_SearchFreeHn();

    if (hn != 0) {
        return m2vlib_InitHn(hn);
    }
    return 0;
}

M2vObj *m2vlib_SearchFreeHn(void)
{
    M2vObj *hn = m2vlib_libwork.obj;
    int i;

    for (i = 0; i < m2vlib_libwork.nobj; i++, hn++) {
        if (hn->stat == 1) {
            return hn;
        }
    }
    return 0;
}

typedef struct M2vCondTbl { M2vCondFn fn[16]; } M2vCondTbl;

M2vObj *m2vlib_InitHn(M2vObj *hn)
{
    *(M2vCondTbl *)hn->cond = *(M2vCondTbl *)m2vlib_libwork.cond;
    M2VHDEC_InitHn(hn);
    m2vlib_InitPicAtr(&hn->picatr);
    hn->stat = 2;
    return hn;
}

void M2V_Destroy(M2vObj *hn)
{
    if (M2VLIB_CheckHn(hn) != 0) {
        M2VERR_SetCode(0, 0xFF030201);
        return;
    }
    hn->stat = 1;
}

void M2V_MbCbFn(void)
{
}

void M2V_SetCond(M2vObj *hn, int no, M2vCondFn fn)
{
    M2vCondFn *cond;

    if (no == 8 && fn == 0) {
        fn = mpvhook_MbCbFn;
    }
    if (hn == 0) {
        m2vlib_SetCondAll(no, fn);
        cond = m2vlib_libwork.cond;
    } else {
        if (M2VLIB_CheckHn(hn) != 0) {
            M2VERR_SetCode(0, 0xFF030202);
            return;
        }
        cond = hn->cond;
    }
    cond[no] = fn;
}

void m2vlib_SetCondAll(int no, M2vCondFn fn)
{
    M2vObj *hn;
    int n;

    n = m2vlib_libwork.nobj;
    hn = m2vlib_libwork.obj;
    if (n > 0) {
        do {
            if (hn->stat == 2) {
                hn->cond[no] = fn;
            }
            hn++;
        } while (--n != 0);
    }
}

int M2VLIB_CheckHn(M2vObj *hn)
{
    m2vlib_m2vobj = hn;
    if (hn == 0) {
        return -1;
    }
    return hn->stat == 2 ? 0 : -1;
}
