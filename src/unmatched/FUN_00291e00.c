typedef struct FrmBufsBufs {
    void *a;
    void *b;
} FrmBufsBufs;

typedef struct FrmBufsCfg {
    int f0;
    int f4;
    int width;
    int height;
} FrmBufsCfg;

extern int mpv_frm_buf_num;
extern int mpv_frm_buf_size;
extern FrmBufsBufs mpv_frm_buf_table;
void *FUN_00293508(int obj, int size);

/* matching construct: two orders tried: the buffer pointers read into locals first */
int FUN_00291e00(int obj, FrmBufsCfg *cfg, FrmBufsBufs *bufs)
{
    int ret = 0;
    int size[2];
    int n;
    void *a;
    void *b;

    size[1] = 0x840D0;
    n = cfg->width * cfg->height;
    size[0] = n * 9 / 2 + 10304;
    if (mpv_frm_buf_num != 0) {
        if (mpv_frm_buf_num < 2 || mpv_frm_buf_size < size[0] || mpv_frm_buf_size < size[1]) {
            bufs->a = 0;
            ret = -1;
            bufs->b = 0;
        } else {
            a = mpv_frm_buf_table.a;
            b = mpv_frm_buf_table.b;
            bufs->b = b;
            bufs->a = a;
        }
    } else {
        bufs->a = FUN_00293508(obj, size[0]);
        bufs->b = FUN_00293508(obj, size[1]);
    }
    if (bufs->a == 0 || bufs->b == 0)
        ret = -1;
    return ret;
}
