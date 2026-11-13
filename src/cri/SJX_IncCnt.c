/* CRI SJX: joins an EE-side SJ to an IOP-side SJ, 20 bytes. */
typedef struct SjxObj {
    signed char used;       /* 0x00 */
    char pad1;
    unsigned short cnt;     /* 0x02 */
    void *sjuni;            /* 0x04 */
    void *sjrmt;            /* 0x08 */
    int mode;               /* 0x0c */
    int iopid;              /* 0x10 */
} SjxObj;

void SJX_IncCnt(SjxObj *sjx)
{
    sjx->cnt = sjx->cnt + 1;
}
