/* Registers caller-owned frame buffers: count and size of each, then copies the buffer
 * pointers into the table FUN_00291e00 hands out instead of allocating. */
extern int mpv_frm_buf_num;      /* frame buffer count (0: allocate per handle) */
extern int mpv_frm_buf_size;      /* frame buffer size */
extern void *mpv_frm_buf_table[];  /* frame buffer pointers */

void MPV_SetFrameBuffers(int num, int size, void **bufs)
{
    int i;

    mpv_frm_buf_num = num;
    mpv_frm_buf_size = size;
    for (i = 0; i < num; i++)
        mpv_frm_buf_table[i] = bufs[i];
}
