/* Server step of an ADX stream-file object (its error string names it adxstmf_stat_exec, a name
 * hypothesis): handles pending stop (+72), close (+70) and open (+69) requests. An open request
 * opens the file (FUN_0026fc60 on the name +80 and offset +84), measures it in sectors (seek to
 * end, FUN_00270028) or bytes (FUN_002702e8 when +84 is 0), clamps the start (+12) and length (+20
 * sectors, +16 bytes) to it and rewinds (FUN_0026a140); a failed open is reported through
 * FUN_00260840 and sets state 4. Finally a running (state 2) and open (+73) stream is serviced
 * with FUN_0026a330. */
typedef struct Stmf_26a728 {
    signed char pad0;
    signed char state;          /* 0x01 */
    signed char stopped;        /* 0x02 */
    char pad3[5];
    void *file;                 /* 0x08 */
    int start;                  /* 0x0c: sectors */
    int bytes;                  /* 0x10 */
    int sectors;                /* 0x14 */
    char pad24[45];
    signed char open_request;   /* 0x45 */
    signed char close_request;  /* 0x46 */
    signed char f71;         /* 0x47 */
    signed char stop_request;   /* 0x48 */
    signed char opened;         /* 0x49 */
    char pad74[6];
    char *name;                 /* 0x50 */
    int offset;                 /* 0x54 */
} Stmf_26a728;

extern char E02110501_adxstmf_stat_exec_can_t_open[]; /* "E02110501 adxstmf_stat_exec: can't open " */
void FUN_0026ffb0(void *file);
void FUN_0027e1c0(void);
void FUN_0027e1d8(void);
void *FUN_0026fc60(char *name, int offset, int mode);
void FUN_00260840(const char *message, char *name);
int FUN_00270090(void *file, int offset, int origin);
int FUN_00270028(void *file);
int FUN_002702e8(char *name);
void FUN_0026a140(Stmf_26a728 *stmf, int position);
void FUN_0026a330(Stmf_26a728 *stmf);

void FUN_0026a728(Stmf_26a728 *stmf) {
    void *file;
    int sectors;
    int bytes;

    if (stmf->stopped == 0) {
        if (stmf->stop_request == 1) {
            stmf->stop_request = 0;
            if (stmf->f71 == 0) {
                stmf->state = 1;
            }
        }
        if (stmf->close_request == 1) {
            file = stmf->file;
            if (file != 0) {
                stmf->file = 0;
                FUN_0026ffb0(file);
            }
            stmf->close_request = 0;
            stmf->opened = 0;
        }
        FUN_0027e1c0();
        if (stmf->open_request == 1) {
            stmf->opened = 1;
            FUN_0027e1d8();
            if (stmf->file == 0) {
                stmf->file = FUN_0026fc60(stmf->name, stmf->offset, 0);
                if (stmf->file == 0) {
                    FUN_00260840(E02110501_adxstmf_stat_exec_can_t_open, stmf->name);
                    stmf->state = 4;
                    stmf->opened = 0;
                    stmf->open_request = 0;
                    return;
                }
                FUN_00270090(stmf->file, 0, 2);
                sectors = FUN_00270028(stmf->file);
                bytes = sectors << 11;
                if (stmf->offset == 0) {
                    bytes = FUN_002702e8(stmf->name);
                }
                FUN_00270090(stmf->file, 0, 0);
                if (stmf->bytes == 0x7ffff800) {
                    stmf->bytes = bytes;
                    stmf->sectors = sectors;
                }
                if (sectors < stmf->start) {
                    stmf->start = sectors;
                }
                if (sectors < stmf->sectors + stmf->start) {
                    stmf->sectors = sectors - stmf->start;
                    stmf->bytes = stmf->sectors << 11;
                }
                FUN_0026a140(stmf, 0);
                stmf->open_request = 0;
            }
        } else {
            FUN_0027e1d8();
        }
        if (stmf->f71 == 1) {
            stmf->f71 = 0;
        }
    }
    if (stmf->state == 2 && stmf->opened == 1) {
        FUN_0026a330(stmf);
    }
}

