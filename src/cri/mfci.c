typedef struct MfCiFile {
    signed char used;       /* 0x00 */
    signed char stat;       /* 0x01 */
    char pad2[2];
    int sctsize;            /* 0x04 */
    int size;               /* 0x08 */
    int nsct;               /* 0x0c */
    int pos;                /* 0x10 */
    int nbyte;              /* 0x14 */
    int reqsct;             /* 0x18 */
    char name[20];          /* 0x1c */
    int ofs;                /* 0x30 */
    int len;                /* 0x34 */
} MfCiFile;

extern void (*DAT_004b0374)(void *context, const char *message, void *detail);
extern void *DAT_004b0378;
extern MfCiFile DAT_004b03e8[40];
extern char DAT_004b0ca8[];

extern char DAT_004f0c88[];
extern char DAT_004f0cc8[];
extern char E01100301_fname_is_null_mfCiOpen[];
extern char E01100302_rw_is_illigal_mfCiOpen[];
extern char E01100303_not_enough_handle_resource_mfCiOpen[];
extern char E01100305_handl_is_null[];
extern char E01100306_handl_is_null[];
extern char DAT_004f0dc8[];
extern char DAT_004f0de8[];
extern char DAT_004f0e08[];
extern char E0092912_handl_is_null_2[];
extern char E0040301_handl_is_null[];
extern char E0040302_handl_is_null[];
extern char E1041001_invalid_entry_number_mfCiOpenEntry[];
extern char E1041002_rw_is_illigal_mfCiOpenEntry[];
extern char E1041002_not_enough_handle_resource_mfCiOpenEntry[];

unsigned int strlen(const char *s);
int sprintf(char *dst, const char *format, ...);
char *strcpy(char *dst, const char *src);
void *memcpy(void *dst, const void *src, unsigned int n);
void *memset(void *dst, int value, unsigned int n);
unsigned long strtoul(const char *s, char **end, int base);
void SVM_Lock(void);
void SVM_Unlock(void);

void FUN_00278410(MfCiFile *fh);

void FUN_00277da0(void)
{
    SVM_Lock();
}

void FUN_00277db8(void)
{
    SVM_Unlock();
}

void FUN_00277de8(void *detail, const char *message)
{
    if (DAT_004b0374 != 0) {
        DAT_004b0374(DAT_004b0378, message, detail);
    }
}

unsigned long FUN_00277e18(const char *s, char **end, int base)
{
    return strtoul(s, end, base);
}

char *FUN_00277e30(char *name, int *size)
{
    char *p;
    char *data;

    if (strlen(name) != 17) {
        sprintf(DAT_004b0ca8, DAT_004f0c88, name);
        FUN_00277de8(0, DAT_004b0ca8);
    }
    if (name[8] != '.') {
        sprintf(DAT_004b0ca8, DAT_004f0cc8, name);
        FUN_00277de8(0, DAT_004b0ca8);
    }
    p = name;
    data = (char *)FUN_00277e18(p, &p, 16);
    if (*p != 0) {
        p++;
    }
    if (size != 0) {
        *size = FUN_00277e18(p, &p, 16);
    }
    return data;
}

void FUN_00277f28(MfCiFile *fh)
{
}

void FUN_00277f30(void)
{
    int i;
    MfCiFile *fh;

    fh = DAT_004b03e8;
    i = 0x27;
    do {
        if (fh->used != 0) {
            FUN_00277f28(fh);
        }
        i -= 1;
        fh += 1;
    } while (i >= 0);
}

void FUN_00277f88(void (*func)(void *context, const char *message, void *detail), void *context)
{
    DAT_004b0374 = func;
    DAT_004b0378 = context;
}

int FUN_00277fa0(char *name)
{
    int size;

    FUN_00277e30(name, &size);
    return size;
}

MfCiFile *FUN_00277fc0(void)
{
    MfCiFile *found = 0;
    int i;

    for (i = 0; i < 40; i++) {
        if (DAT_004b03e8[i].used == 0) {
            found = &DAT_004b03e8[i];
            break;
        }
    }
    return found;
}

void FUN_00278018(MfCiFile *fh)
{
    memset(fh, 0, 0x38);
}

void FUN_00278038(MfCiFile *fh)
{
    int size;

    fh->sctsize = 0x800;
    size = FUN_00277fa0(fh->name);
    fh->size = size;
    fh->nsct = (size + fh->sctsize - 1) / fh->sctsize;
    fh->used = 1;
    fh->reqsct = 0;
    fh->nbyte = 0;
    fh->stat = 0;
    fh->pos = 0;
}

MfCiFile *FUN_002780a8(const char *fname, int reserved, int rw)
{
    MfCiFile *fh;

    if (fname == 0) {
        FUN_00277de8(0, E01100301_fname_is_null_mfCiOpen);
        return 0;
    }
    if (rw != 0) {
        FUN_00277de8(0, E01100302_rw_is_illigal_mfCiOpen);
        return 0;
    }
    fh = FUN_00277fc0();
    if (fh == 0) {
        FUN_00277de8(0, E01100303_not_enough_handle_resource_mfCiOpen);
        return 0;
    }
    strcpy(fh->name, fname);
    FUN_00278038(fh);
    return fh;
}

/* matching construct: hand search — int return type with no return value (implicit-int style); a void
   return type lets GCC turn the last call into a sibling call */
int FUN_00278148(MfCiFile *fh)
{
    if (fh != 0) {
        FUN_00278410(fh);
        if (fh->used == 1) {
            fh->used = 0;
            FUN_00278018(fh);
        }
    }
}

int FUN_00278190(MfCiFile *fh, int offset, int origin)
{
    int pos;

    if (fh == 0) {
        FUN_00277de8(fh, E01100305_handl_is_null);
        return 0;
    }
    FUN_00277da0();
    if (origin == 0) {
        fh->pos = offset;
    } else if (origin == 2) {
        fh->pos = fh->nsct + offset;
    } else if (origin == 1) {
        fh->pos += offset;
    }
    pos = fh->pos;
    if (pos >= fh->nsct) {
        pos = fh->nsct;
    }
    if (pos < 0) {
        pos = 0;
    }
    fh->pos = pos;
    FUN_00277db8();
    return fh->pos;
}

int FUN_00278250(MfCiFile *fh)
{
    if (fh == 0) {
        FUN_00277de8(0, E01100306_handl_is_null);
        return 0;
    }
    return fh->pos;
}

int FUN_00278288(MfCiFile *fh, int nsct, char *buf)
{
    char *data;
    int size;
    int n;
    int ofs;
    int len;
    int avail;

    if (fh == 0) {
        FUN_00277de8(fh, DAT_004f0dc8);
        return 0;
    }
    if (nsct < 0) {
        FUN_00277de8(fh, DAT_004f0de8);
        return 0;
    }
    if (buf == 0) {
        FUN_00277de8(fh, DAT_004f0e08);
        return 0;
    }
    if (nsct == 0) {
        fh->stat = 1;
        return 0;
    }
    if (fh->stat == 2) {
        return 0;
    }
    FUN_00277da0();
    fh->nbyte = 0;
    n = fh->nsct - fh->pos;
    if (nsct < n) {
        n = nsct;
    }
    fh->reqsct = n;
    ofs = fh->pos * fh->sctsize;
    len = n * fh->sctsize;
    if (len == 0) {
        fh->stat = 1;
        FUN_00277db8();
        return 0;
    }
    fh->ofs = ofs;
    fh->len = len;
    fh->stat = 2;
    data = FUN_00277e30(fh->name, &size);
    avail = (size - fh->ofs < fh->len) ? size - fh->ofs : fh->len;
    FUN_00277db8();
    memcpy(buf, data + fh->ofs, fh->len);
    memset(buf + avail, 0, fh->len - avail);
    FUN_00277da0();
    fh->stat = 1;
    fh->pos += fh->reqsct;
    fh->nbyte = fh->reqsct * fh->sctsize;
    FUN_00277db8();
    return fh->reqsct;
}

void FUN_00278410(MfCiFile *fh)
{
    if (fh == 0) {
        FUN_00277de8(0, E0092912_handl_is_null_2);
        return;
    }
    FUN_00277da0();
    fh->stat = 0;
    FUN_00277db8();
}

char FUN_00278460(MfCiFile *fh)
{
    if (fh == 0) {
        FUN_00277de8(fh, E0092912_handl_is_null_2);
        return 0;
    }
    return fh->stat;
}

int FUN_00278498(MfCiFile *fh)
{
    if (fh == 0) {
        FUN_00277de8(0, E0040301_handl_is_null);
        return 0;
    }
    return fh->sctsize;
}

void FUN_002784d0(MfCiFile *fh, int sctsize)
{
    int old;
    int pos;

    if (fh == 0) {
        FUN_00277de8(fh, E0040302_handl_is_null);
        return;
    }
    pos = fh->pos;
    old = fh->sctsize;
    fh->sctsize = sctsize;
    fh->nsct = (fh->size + sctsize - 1) / sctsize;
    fh->pos = pos * old / sctsize;
    fh->nbyte = fh->reqsct * sctsize;
}

int FUN_00278550(MfCiFile *fh)
{
    if (fh == 0) {
        FUN_00277de8(0, E0092912_handl_is_null_2);
        return 0;
    }
    return fh->nbyte;
}

MfCiFile *FUN_00278588(int entry, int reserved, int rw)
{
    MfCiFile *fh;

    if (entry <= 0) {
        FUN_00277de8(0, E1041001_invalid_entry_number_mfCiOpenEntry);
        return 0;
    }
    if (rw != 0) {
        FUN_00277de8(0, E1041002_rw_is_illigal_mfCiOpenEntry);
        return 0;
    }
    fh = FUN_00277fc0();
    if (fh == 0) {
        FUN_00277de8(0, E1041002_not_enough_handle_resource_mfCiOpenEntry);
        return 0;
    }
    FUN_00278038(fh);
    return fh;
}
