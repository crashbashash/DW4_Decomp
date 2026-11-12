typedef struct AdxfSj AdxfSj;
typedef struct AdxfSjVtbl {
    void (*f0)(AdxfSj *sj);
    void (*f4)(AdxfSj *sj);
    void (*f8)(AdxfSj *sj);
    void (*destroy)(AdxfSj *sj);
} AdxfSjVtbl;
struct AdxfSj {
    const AdxfSjVtbl *vtbl;
};

typedef struct AdxfHandle {
    signed char used;
    signed char stat;
    signed char sjflag;
    signed char stopnw;
    void *stm;
    AdxfSj *sj;
    int fsize_sct;
    int fsize_byte;
    int ofst;
    int rqsct_ofst;
    int rqsct;
    int rdsct;
    void *buf;
    int bsize;
    int rqrdsct;
    int skpsct;
    void *dir;
    const char *fname;
    int stm_ofst;
    int stm_nsct;
} AdxfHandle;

typedef struct AdxfPtInfo AdxfPtInfo;
struct AdxfPtInfo {
    AdxfPtInfo *next;
    int size;
    int nfile;
    unsigned short nfile16;
    signed char f14;
    signed char type;
    char fname[256];
    void *dir;
    int base;
    unsigned int top;
};

typedef struct AdxfLogEntry {
    signed char id;
    signed char kind;
    unsigned short count;
    int arg0;
    int arg1;
    int arg2;
} AdxfLogEntry;

#define ADXF_HANDLE_COUNT 16

extern int DAT_00499de4;
extern AdxfHandle DAT_00499de8[ADXF_HANDLE_COUNT];
extern AdxfPtInfo *DAT_0049a228[256];
extern int DAT_0049a628;
extern AdxfLogEntry DAT_0049a630[16];
extern unsigned short DAT_0049a730[16];
extern int DAT_0049a750;
extern int DAT_0049a754;
extern AdxfHandle *DAT_0049a758;
extern int DAT_0049a75c;
extern int DAT_0049a760;
extern void *DAT_0049a768;
extern int DAT_0049a76c;
extern char DAT_0049a800[];

extern char DAT_004ed900[];
extern char DAT_004ed938[];
extern char DAT_004ed968[];
extern char DAT_004ed9a8[];
extern char DAT_004ed9d8[];
extern char DAT_004eda00[];
extern char DAT_004eda30[];
extern char DAT_004edb58[];
extern char DAT_004edb90[];
extern char DAT_004edbc8[];
extern char DAT_004edc00[];
extern char DAT_004edc28[];
extern char DAT_004edc58[];
extern char DAT_004edc80[];
extern char DAT_004edca8[];
extern char DAT_004edcd8[];
extern char DAT_004edd00[];
extern char DAT_004edd30[];
extern char DAT_004edd68[];
extern char DAT_004edd90[];
extern char DAT_004eddc0[];
extern char DAT_004edde8[];
extern char DAT_004ede18[];
extern char DAT_004ede40[];
extern char DAT_004ede68[];
extern char DAT_004ede90[];
extern char DAT_004edec0[];
extern char DAT_004edef0[];
extern char DAT_004edf20[];
extern char DAT_004edf48[];
extern char DAT_004edf70[];
extern char DAT_004edf98[];

void *memset(void *dst, int value, unsigned int size);
char *strncpy(char *dst, const char *src, unsigned int n);
void FUN_0010b918(void *start, void *last);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_002607e8(const char *message);
void ADXM_ExecMain(void);
void *FUN_00269f50(int a, int size);
void FUN_00269f98(void *stm);
void FUN_0026a068(void *stm, const char *fname, void *dir, int ofst, int nsct);
void FUN_0026a0e0(void *stm);
char FUN_0026a138(void *stm);
void FUN_0026a140(void *stm, int ofst);
int FUN_0026a160(void *stm);
void FUN_0026a1f0(void *stm, int nsct);
void FUN_0026a238(void *stm);
void FUN_0026a2a0(void *stm);
void FUN_0026a300(void *stm, int a);
int FUN_0026a9e8(void *stm, int nsct);
int FUN_0026aa00(void *stm);
int FUN_0026aa08(void *stm);
void FUN_0026aa10(void *stm, int a);
void FUN_0026aae8(void *stm, AdxfSj *sj);
int FUN_0026aba8(void *stm);
void FUN_0026abb0(void *stm);
AdxfSj *FUN_0027bd48(void *buf, int size, int a);
int cvFsGetFileSize();

int FUN_002612d8(int ptid);
void FUN_00261c88(AdxfHandle *adxf);
int FUN_00261f48(AdxfHandle *adxf, int nsct, void *buf);
int FUN_00262118(AdxfHandle *adxf);
int FUN_00262678(AdxfHandle *adxf);
int FUN_00262748(int ptid, int flid, char *fname, void **dir, int *ofst, int *nsct);

void FUN_00260a40(void *base, int length) {
    FUN_0010b918(base, (char *)base + length - 1);
}

void FUN_00260b30(void)
{
    void FUN_00261d40(void);
    if (--DAT_00499de4 != 0) {
        return;
    }
    FUN_00261d40();
    DAT_0049a760 = 1;
    DAT_0049a75c = -1;
    DAT_0049a758 = 0;
    DAT_0049a754 = 0;
    DAT_0049a628 = 0;
    DAT_0049a750 = 0;
    memset(DAT_0049a730, 0, sizeof(DAT_0049a730));
    memset(DAT_0049a630, 0xFF, sizeof(DAT_0049a630));
    memset(DAT_0049a228, 0, sizeof(DAT_0049a228));
    memset(DAT_00499de8, 0, sizeof(DAT_00499de8));
}

int FUN_00260bf8(int bytes) {
    return bytes / 2048 + (bytes % 2048 > 0);
}

/* matching construct: sweep of all 120 orders of the entry stores */
void FUN_00260c20(int id, int kind, int arg0, int arg1, int arg2)
{
    AdxfLogEntry *e;
    DAT_0049a750 = DAT_0049a750 % 16;
    e = &DAT_0049a630[DAT_0049a750];
    if (kind == 0) {
        DAT_0049a730[id]++;
    }
    e->arg2 = arg2;
    e->arg0 = arg0;
    e->arg1 = arg1;
    e->id = id;
    e->kind = kind;
    DAT_0049a750++;
    e->count = DAT_0049a730[id];
}

void FUN_00260cd0(void) {
    int i;
    for (i = 0; i < 50000; i++) {
    }
}

int FUN_00260d00(unsigned int ptid, AdxfPtInfo *ptinfo) {
    if (ptid >= 256) {
        FUN_002607e8(DAT_004ed900);
        return -3;
    }
    if (ptinfo == 0) {
        FUN_002607e8(DAT_004ed938);
        return -3;
    }
    return 0;
}

int FUN_00260d68(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo);

int FUN_00260d48(int ptid, const char *fname, AdxfPtInfo *ptinfo) {
    return FUN_00260d68(ptid, fname, 0, ptinfo);
}

int FUN_00260de8(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo);
int FUN_002612c0(int ptid);

int FUN_00260d68(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo) {
    int result = FUN_00260de8(ptid, fname, dir, ptinfo);
    int status;
    if (result < 0) {
        return result;
    }
    for (;;) {
        status = FUN_002612c0(ptid);
        if (status == 3) {
            result = 0;
            break;
        }
        if (status == 4) {
            result = -1;
            break;
        }
        ADXM_ExecMain();
        FUN_00260cd0();
    }
    return result;
}

int FUN_00260e88(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize);
int FUN_00260ed0(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize);
int FUN_00260f08(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize);
int FUN_00260f50(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize);

int FUN_00260de8(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo) {
    return FUN_00260e88(ptid, fname, dir, ptinfo, (void *)((int)DAT_0049a800 & ~0x3F), 0x800);
}

int FUN_00260e10(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo) {
    return FUN_00260ed0(ptid, afsid, flid, ptinfo, (void *)((int)DAT_0049a800 & ~0x3F), 0x800);
}

int FUN_00260e38(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo) {
    return FUN_00260f08(ptid, fname, dir, ptinfo, (void *)((int)DAT_0049a800 & ~0x3F), 0x800);
}

int FUN_00260e60(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo) {
    return FUN_00260f50(ptid, afsid, flid, ptinfo, (void *)((int)DAT_0049a800 & ~0x3F), 0x800);
}

int FUN_00260f88(int ptid, int afsid, int flid, const char *fname, void *dir, AdxfPtInfo *ptinfo,
                 void *tmpbuf, int tbsize, int type);

int FUN_00260e88(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize) {
    return FUN_00260f88(ptid, 0, 0, fname, dir, ptinfo, tmpbuf, tbsize, 0);
}

int FUN_00260ed0(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize) {
    return FUN_00260f88(ptid, afsid, flid, 0, 0, ptinfo, tmpbuf, tbsize, 0);
}

int FUN_00260f08(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize) {
    return FUN_00260f88(ptid, 0, 0, fname, dir, ptinfo, tmpbuf, tbsize, 1);
}

int FUN_00260f50(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize) {
    return FUN_00260f88(ptid, afsid, flid, 0, 0, ptinfo, tmpbuf, tbsize, 1);
}

AdxfHandle *FUN_002618c0(const char *fname, void *dir);
AdxfHandle *FUN_00261b78(int afsid, int flid);
int FUN_002620d8(AdxfHandle *adxf, int nsct, void *buf);

int FUN_00260f88(int ptid, int afsid, int flid, const char *fname, void *dir, AdxfPtInfo *ptinfo,
                 void *tmpbuf, int tbsize, int type)
{
    int ret;
    int ofst;
    int nsct;
    int size;

    if (DAT_0049a760 == 2) {
        FUN_002607e8(DAT_004ed968);
        return -1;
    }
    if (DAT_0049a758 != 0) {
        FUN_00261c88(DAT_0049a758);
        DAT_0049a758 = 0;
    }
    DAT_0049a75c = -1;
    DAT_0049a760 = 1;
    if (tmpbuf == 0) {
        FUN_002607e8(DAT_004ed9a8);
        DAT_0049a760 = 4;
        return -3;
    }
    if (tbsize <= 0) {
        FUN_002607e8(DAT_004ed9d8);
        DAT_0049a760 = 4;
        return -3;
    }
    ret = FUN_00260d00(ptid, ptinfo);
    if (ret < 0) {
        DAT_0049a760 = 4;
        return ret;
    }
    if (DAT_0049a75c >= 0) {
        FUN_002607e8(DAT_004eda00);
        DAT_0049a760 = 4;
        return -1;
    }
    DAT_0049a760 = 2;
    DAT_0049a75c = ptid;
    DAT_0049a754 = 0;
    memset(ptinfo, 0, sizeof(AdxfPtInfo));
    DAT_0049a228[ptid] = ptinfo;
    ptinfo->next = 0;
    if (fname == 0) {
        DAT_0049a758 = FUN_00261b78(afsid, flid);
        if (DAT_0049a758 == 0) {
            FUN_002607e8(DAT_004eda30);
            DAT_0049a760 = 4;
            return -1;
        }
        ret = FUN_00262748(afsid, flid, ptinfo->fname, &dir, &ofst, &size);
        if (ret < 0) {
            DAT_0049a760 = 4;
            return ret;
        }
        ptinfo->base = ofst;
    } else {
        DAT_0049a758 = FUN_002618c0(fname, dir);
        if (DAT_0049a758 == 0) {
            FUN_002607e8(DAT_004eda30);
            DAT_0049a760 = 4;
            return -1;
        }
        strncpy(ptinfo->fname, fname, 256);
    }
    ptinfo->type = type;
    ptinfo->f14 = 0;
    nsct = tbsize / 2048;
    ptinfo->dir = dir;
    DAT_0049a768 = tmpbuf;
    DAT_0049a76c = nsct;
    ret = FUN_002620d8(DAT_0049a758, nsct, tmpbuf);
    if (ret < 0) {
        FUN_00261c88(DAT_0049a758);
        DAT_0049a760 = 4;
        return ret;
    }
    ptinfo->nfile = 0;
    return 0;
}

void FUN_00261218(void) {
    FUN_00261c88(DAT_0049a758);
    DAT_0049a758 = 0;
    DAT_0049a754 = 0;
    DAT_0049a76c = 0;
}

void FUN_00261258(void) {
    if (DAT_0049a758 != 0 && DAT_0049a75c >= 0) {
        if (FUN_00262678(DAT_0049a758) != 1) {
            FUN_00262118(DAT_0049a758);
        }
        FUN_00261218();
    }
}

int FUN_002612c0(int ptid) {
    return FUN_002612d8(ptid);
}

int FUN_00261708(int ptid) {
    return DAT_0049a228[ptid]->size;
}

AdxfHandle *FUN_00261720(void) {
    AdxfHandle *found = 0;
    int i;
    for (i = 0; i < ADXF_HANDLE_COUNT; i++) {
        if (DAT_00499de8[i].used == 0) {
            found = &DAT_00499de8[i];
            break;
        }
    }
    return found;
}

AdxfHandle *FUN_00261778(void) {
    AdxfHandle *adxf;
    void *stm;
    adxf = FUN_00261720();
    if (adxf == 0) {
        FUN_002607e8(DAT_004edb58);
        return 0;
    }
    stm = FUN_00269f50(0, 256);
    adxf->stm = stm;
    if (stm == 0) {
        FUN_002607e8(DAT_004edb90);
        return 0;
    }
    adxf->stat = 1;
    adxf->rqsct_ofst = 0;
    adxf->rqsct = 0;
    adxf->rdsct = 0;
    adxf->sjflag = 0;
    adxf->sj = 0;
    adxf->stopnw = 0;
    adxf->rqrdsct = 512;
    adxf->used = 1;
    return adxf;
}

int FUN_00261810(AdxfHandle *adxf, const char *fname, void *dir) {
    int size;
    if (fname == 0) {
        FUN_002607e8(DAT_004edbc8);
        return -1;
    }
    adxf->dir = dir;
    adxf->fname = fname;
    adxf->ofst = 0;
    FUN_0026a068(adxf->stm, fname, dir, 0, 0xfffff);
    if (FUN_0026a138(adxf->stm) == 4) {
        FUN_0026a0e0(adxf->stm);
        return -1;
    }
    adxf->fsize_byte = FUN_0026aa00(adxf->stm);
    size = FUN_0026aa08(adxf->stm);
    adxf->stm_ofst = 0;
    adxf->fsize_sct = size;
    adxf->stm_nsct = size;
    return 0;
}

AdxfHandle *FUN_002618c0(const char *fname, void *dir) {
    AdxfHandle *temp_a0;
    AdxfHandle *var_s0;
    FUN_00260c20(1, 0, (int)fname, (int)dir, -1);
    var_s0 = FUN_00261778();
    if (var_s0 != 0) {
        if (FUN_00261810(var_s0, fname, dir) < 0) {
            temp_a0 = var_s0;
            var_s0 = 0;
            FUN_00261c88(temp_a0);
        }
    }
    FUN_00260c20(1, 1, (int)fname, (int)dir, -1);
    return var_s0;
}

int FUN_00261960(AdxfHandle *adxf, const char *fname, void *dir, int ofst, int nsct) {
    adxf->dir = dir;
    adxf->fname = fname;
    adxf->skpsct = ofst;
    adxf->stm_ofst = ofst;
    adxf->stm_nsct = nsct;
    adxf->ofst = 0;
    FUN_0026a068(adxf->stm, fname, dir, ofst, nsct);
    if (FUN_0026a138(adxf->stm) == 4) {
        FUN_0026a0e0(adxf->stm);
        return -1;
    }
    adxf->fsize_sct = nsct;
    adxf->fsize_byte = nsct << 11;
    return 0;
}

AdxfHandle *FUN_002619e0(const char *fname, void *dir, int ofst, int nsct) {
    AdxfHandle *temp_a0;
    AdxfHandle *var_s2;
    FUN_00260c20(1, 0, (int)fname, (int)dir, -1);
    var_s2 = FUN_00261778();
    if (var_s2 != 0) {
        if (FUN_00261960(var_s2, fname, dir, ofst, nsct) < 0) {
            temp_a0 = var_s2;
            var_s2 = 0;
            FUN_00261c88(temp_a0);
        }
    }
    FUN_00260c20(1, 1, (int)fname, (int)dir, -1);
    return var_s2;
}

char *FUN_002628a0(int ptid);

int FUN_00261aa0(AdxfHandle *adxf, int afsid, int flid)
{
    char fname[256];
    void *dir;
    int ofst;
    int nsct;
    char *ptname;

    if (FUN_00262748(afsid, flid, fname, &dir, &ofst, &nsct) < 0) {
        return -3;
    }
    adxf->skpsct = ofst;
    adxf->dir = dir;
    ptname = FUN_002628a0(afsid);
    adxf->ofst = 0;
    adxf->fname = ptname;
    adxf->stm_nsct = nsct;
    adxf->stm_ofst = ofst;
    FUN_0026a068(adxf->stm, ptname, adxf->dir, ofst, nsct);
    if (FUN_0026a138(adxf->stm) == 4) {
        FUN_0026a0e0(adxf->stm);
        return -1;
    }
    adxf->fsize_sct = nsct;
    adxf->fsize_byte = nsct << 11;
    return 0;
}

AdxfHandle *FUN_00261b78(int afsid, int flid) {
    AdxfHandle *temp_a0;
    AdxfHandle *var_s0;
    FUN_00260c20(2, 0, afsid, flid, -1);
    var_s0 = FUN_00261778();
    if (var_s0 != 0) {
        if (FUN_00261aa0(var_s0, afsid, flid) < 0) {
            temp_a0 = var_s0;
            var_s0 = 0;
            FUN_00261c88(temp_a0);
        }
    }
    FUN_00260c20(2, 1, afsid, flid, -1);
    return var_s0;
}

void FUN_00261c18(AdxfHandle *adxf) {
    AdxfSj *sj;
    if (adxf->sj != 0 && adxf->sjflag == 0) {
        if (DAT_0049a628 == 1) {
            FUN_00260a40(adxf->buf, adxf->bsize);
        }
        sj = adxf->sj;
        adxf->sj = 0;
        sj->vtbl->destroy(sj);
    }
}

void FUN_00261c88(AdxfHandle *adxf) {
    void *stm;
    FUN_00260c20(3, 0, (int)adxf, -1, -1);
    if (adxf != 0) {
        if (adxf->stat == 2) {
            FUN_00262118(adxf);
        }
        stm = adxf->stm;
        if (stm != 0) {
            adxf->used = 0;
            adxf->stm = 0;
            FUN_0026a0e0(stm);
            FUN_00269f98(stm);
        }
        memset(adxf, 0, sizeof(AdxfHandle));
        FUN_00260c20(3, 1, (int)adxf, -1, -1);
    }
}

void FUN_00261d40(void) {
    int i;
    AdxfHandle *adxf;
    adxf = DAT_00499de8;
    i = 15;
    do {
        if (adxf->used == 1) {
            FUN_00261c88(adxf);
        }
        i -= 1;
        adxf++;
    } while (i >= 0);
}

int FUN_00261da0(AdxfHandle *adxf, int nsct, AdxfSj *sj) {
    int remaining;
    int count;
    if (FUN_0026a138(adxf->stm) != 1) {
        FUN_0026a2a0(adxf->stm);
    }
    FUN_0025f2d0();
    remaining = adxf->fsize_sct - adxf->ofst;
    adxf->rdsct = 0;
    if (nsct < remaining) {
        remaining = nsct;
    }
    adxf->rqsct_ofst = adxf->skpsct + adxf->ofst;
    adxf->rqsct = remaining;
    if (remaining == 0) {
        adxf->stat = 3;
        count = 0;
    } else {
        FUN_0026a300(adxf->stm, -1);
        FUN_0026aae8(adxf->stm, sj);
        FUN_0026a9e8(adxf->stm, adxf->rqrdsct);
        adxf->stat = 2;
        adxf->stopnw = 0;
        FUN_0026aa10(adxf->stm, 0);
        FUN_0026a140(adxf->stm, adxf->ofst);
        FUN_0026a1f0(adxf->stm, adxf->rqsct);
        count = adxf->rqsct;
    }
    FUN_0025f2e8();
    return count;
}

int FUN_00261ea0(AdxfHandle *adxf, int nsct, AdxfSj *sj) {
    int count;
    if (adxf == 0) {
        FUN_002607e8(DAT_004edc00);
        return -3;
    }
    if (nsct < 0) {
        FUN_002607e8(DAT_004edc28);
        return -3;
    }
    if (sj == 0) {
        FUN_002607e8(DAT_004edc58);
        return -3;
    }
    if (adxf->stat == 2) {
        return 0;
    }
    count = FUN_00261da0(adxf, nsct, sj);
    adxf->sjflag = 1;
    return count;
}

int FUN_00261f30(AdxfHandle *adxf, int nsct, AdxfSj *sj) {
    return FUN_00261ea0(adxf, nsct, sj);
}

int FUN_00261f48(AdxfHandle *adxf, int nsct, void *buf)
{
    AdxfSj *sj;
    int size;
    int ret;
    FUN_00260c20(4, 0, (int)adxf, nsct, (int)buf);
    if (adxf == 0) {
        FUN_002607e8(DAT_004edc80);
        return -3;
    }
    if (nsct < 0) {
        FUN_002607e8(DAT_004edca8);
        return -3;
    }
    if (buf == 0) {
        FUN_002607e8(DAT_004edcd8);
        return -3;
    }
    if (adxf->stat == 2)
        return 0;
    if (adxf->sj != 0) {
        FUN_002607e8(DAT_004edd00);
        return -1;
    }
    size = nsct << 11;
    sj = FUN_0027bd48(buf, size, 0);
    if (sj == 0)
        return -2;
    FUN_0025f2d0();
    adxf->buf = buf;
    adxf->sj = sj;
    adxf->bsize = size;
    if (DAT_0049a628 == 1)
        FUN_00260a40(buf, size);
    FUN_0025f2e8();
    ret = FUN_00261da0(adxf, nsct, adxf->sj);
    if (ret <= 0) {
        FUN_0025f2d0();
        if (adxf->sj != 0) {
            adxf->sj->vtbl->destroy(adxf->sj);
            adxf->sj = 0;
        }
        FUN_0025f2e8();
    }
    adxf->sjflag = 0;
    FUN_00260c20(4, 1, (int)adxf, nsct, (int)buf);
    return ret;
}

int FUN_002620d8(AdxfHandle *adxf, int nsct, void *buf) {
    if ((unsigned int)buf & 0x3F) {
        FUN_002607e8(DAT_004edd30);
        return -3;
    }
    return FUN_00261f48(adxf, nsct, buf);
}

void FUN_00261c18(AdxfHandle *adxf);

int FUN_00262118(AdxfHandle *adxf) {
    FUN_00260c20(5, 0, (int)adxf, -1, -1);
    if (adxf == 0) {
        FUN_002607e8(DAT_004edd68);
        return -3;
    }
    if (adxf->stat != 1) {
        if (adxf->stat == 3) {
            adxf->stat = 1;
        } else {
            if (adxf->stm == 0) {
                FUN_002607e8(DAT_004edd90);
                return -1;
            }
            FUN_0026a2a0(adxf->stm);
            FUN_0025f2d0();
            adxf->rdsct = FUN_0026a160(adxf->stm) - adxf->ofst;
            FUN_00261c18(adxf);
            adxf->stat = 1;
            FUN_0025f2e8();
            FUN_00260c20(5, 1, (int)adxf, -1, -1);
        }
    }
    return adxf->ofst;
}

int FUN_00262208(AdxfHandle *adxf) {
    FUN_00260c20(7, 0, (int)adxf, -1, -1);
    if (adxf == 0) {
        FUN_002607e8(DAT_004eddc0);
        return -3;
    }
    if (adxf->stat != 1) {
        if (adxf->stat == 3) {
            adxf->stat = 1;
        } else {
            if (adxf->stm == 0) {
                FUN_002607e8(DAT_004edde8);
                return -1;
            }
            FUN_0026a238(adxf->stm);
            adxf->stopnw = 1;
            FUN_00260c20(7, 1, (int)adxf, -1, -1);
        }
    }
    return adxf->ofst;
}

void FUN_002622d0(AdxfHandle *adxf)
{
    int req;
    int st;
    int n;

    if (adxf->stat == 2) {
        adxf->stat = FUN_0026a138(adxf->stm);
        n = FUN_0026a160(adxf->stm) - adxf->ofst;
        adxf->rdsct = n;
        if ((unsigned char)adxf->stat == 3 || (unsigned char)adxf->stat == 4) {
            adxf->ofst += n;
            FUN_00261c18(adxf);
        }
    }
    req = adxf->stopnw;
    if (req == 1) {
        st = FUN_0026a138(adxf->stm);
        if (st == req) {
            adxf->rdsct = FUN_0026a160(adxf->stm) - adxf->ofst;
            FUN_00261c18(adxf);
            adxf->stat = st;
            adxf->stopnw = 0;
        }
    }
}

void FUN_00262398(void) {
    AdxfHandle *adxf;
    int remaining;
    remaining = 15;
    FUN_0025f2d0();
    adxf = DAT_00499de8;
    do {
        if (adxf->used == 1) {
            FUN_002622d0(adxf);
        }
        remaining--;
        adxf++;
    } while (remaining >= 0);
    FUN_0025f2e8();
}

int FUN_002623f8(AdxfHandle *adxf, int ofst, int whence)
{
    FUN_00260c20(6, 0, (int)adxf, ofst, whence);
    if (adxf == 0) {
        FUN_002607e8(DAT_004ede18);
        return -3;
    }
    if (adxf->stat == 2) {
        FUN_00262118(adxf);
    }
    if (whence == 0) {
        adxf->ofst = ofst;
    } else if (whence == 1) {
        adxf->ofst = adxf->ofst + ofst;
    } else if (whence == 2) {
        adxf->ofst = adxf->fsize_sct + ofst;
    } else {
        FUN_002607e8(DAT_004ede40);
        return -3;
    }
    if (adxf->ofst < 0) {
        adxf->ofst = 0;
    } else if (adxf->fsize_sct < adxf->ofst) {
        adxf->ofst = adxf->fsize_sct;
    }
    FUN_00260c20(6, 1, (int)adxf, ofst, whence);
    return adxf->ofst;
}

int FUN_00262510(AdxfHandle *adxf) {
    if (adxf == 0) {
        FUN_002607e8(DAT_004ede68);
        return -3;
    }
    return adxf->ofst;
}

int FUN_00262580(AdxfHandle *adxf);

int FUN_00262540(AdxfHandle *adxf) {
    return adxf->fsize_sct = (FUN_00262580(adxf) + 2047) / 2048;
}

int FUN_00262580(AdxfHandle *adxf) {
    if (adxf == 0) {
        FUN_002607e8(DAT_004ede90);
        return -3;
    }
    if (adxf->fsize_byte > 0x7ffff7ff) {
        FUN_0026abb0(adxf->stm);
        if (FUN_0026a138(adxf->stm) == 4) {
            return -5;
        }
    }
    adxf->fsize_byte = FUN_0026aa00(adxf->stm);
    return adxf->fsize_byte;
}

int FUN_002625f8(AdxfHandle *adxf, int *ofst) {
    if (adxf == 0) {
        FUN_002607e8(DAT_004edec0);
        *ofst = 0;
        return -3;
    }
    *ofst = adxf->rqsct_ofst;
    return adxf->rqsct;
}

int FUN_00262648(AdxfHandle *adxf) {
    if (adxf == 0) {
        FUN_002607e8(DAT_004edef0);
        return -3;
    }
    return adxf->rdsct;
}

int FUN_00262678(AdxfHandle *adxf) {
    if (adxf == 0) {
        FUN_002607e8(DAT_004edf20);
        return -3;
    }
    return adxf->stat;
}

int FUN_002626a8(unsigned int ptid, int flid) {
    AdxfPtInfo *ptinfo;

    if (ptid >= 256) {
        FUN_002607e8(DAT_004edf48);
        return -3;
    }
    ptinfo = DAT_0049a228[ptid];
    if (ptinfo == 0) {
        FUN_002607e8(DAT_004edf48);
        return -3;
    }
    if (flid < 0 || flid >= ptinfo->nfile) {
        FUN_002607e8(DAT_004edf70);
        return -3;
    }
    return 0;
}

int FUN_00262720(int ptid, int flid, char *fname, int *ofst, int *nsct) {
    void *dir[4];

    return FUN_00262748(ptid, flid, fname, dir, ofst, nsct);
}

int FUN_00262748(int ptid, int flid, char *fname, void **dir, int *ofst, int *nsct)
{
    AdxfPtInfo *ptinfo;
    int ret;
    int off;
    int i;

    ret = FUN_002626a8(ptid, flid);
    if (ret < 0) {
        *dir = 0;
        *ofst = -1;
        *nsct = -1;
        return ret;
    }
    ptinfo = DAT_0049a228[ptid];
    if (ptinfo->type == 1) {
        unsigned int *tbl = &ptinfo->top;

        off = *tbl++;
        for (i = 0; i < flid; i++) {
            off += tbl[i];
        }
        *nsct = tbl[flid];
    } else {
        unsigned short *tbl = (unsigned short *)&ptinfo->top;

        off = *tbl++;
        for (i = 0; i < flid; i++) {
            off += tbl[i];
        }
        *nsct = tbl[flid];
    }
    strncpy(fname, ptinfo->fname, 256);
    *dir = ptinfo->dir;
    *ofst = ptinfo->base + off;
    return ret;
}

char *FUN_002628a0(int ptid) {
    return DAT_0049a228[ptid]->fname;
}

void FUN_002628b8(int sw) {
    DAT_0049a628 = sw;
}

void FUN_002628c8(AdxfHandle *adxf, int rqrdsct) {
    if (adxf->stat == 2) {
        FUN_002607e8(DAT_004edf98);
        return;
    }
    adxf->rqrdsct = rqrdsct;
}

int FUN_00262900(AdxfHandle *adxf)
{
    if (adxf == 0)
        return 0;
    if (adxf->stm == 0)
        return 0;
    return FUN_0026aba8(adxf->stm);
}

int FUN_00262938(void *a0) {
    return cvFsGetFileSize(a0);
}
