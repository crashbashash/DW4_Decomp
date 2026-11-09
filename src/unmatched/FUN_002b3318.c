typedef struct CnvTblCnv {
    char pad[60];
    unsigned int compo;
} CnvTblCnv;

extern char DAT_004f53e0[];
int FUN_002b3490(CnvTblCnv *cnv, unsigned int compo);
void FUN_002b3510(CnvTblCnv *cnv, int arg);
void FUN_002b3530(CnvTblCnv *cnv, int arg);
void FUN_002b3600(CnvTblCnv *cnv, int arg);
void FUN_002b3620(CnvTblCnv *cnv, int arg);
void FUN_002b3640(CnvTblCnv *cnv, int arg);
void FUN_002b3660(CnvTblCnv *cnv, int arg);
void FUN_002b3678(CnvTblCnv *cnv, int arg);
void FUN_002b3b38(CnvTblCnv *cnv, int arg, const char *msg);

void FUN_002b3318(CnvTblCnv *cnv, int arg, unsigned int compo)
{
    if (FUN_002b3490(cnv, compo) != 1)
        return;
    cnv->compo = compo;
    switch (compo) {
    case 11:
    case 13:
        FUN_002b3510(cnv, arg);
        return;
    case 2:
        FUN_002b3600(cnv, arg);
        return;
    case 4:
        FUN_002b3620(cnv, arg);
        return;
    case 5:
        FUN_002b3640(cnv, arg);
        return;
    case 21:
        FUN_002b3660(cnv, arg);
        return;
    case 22:
        FUN_002b3678(cnv, arg);
        return;
    case 1:
        FUN_002b3530(cnv, arg);
        return;
    case 0:
    case 100:
    default:
        FUN_002b3b38(cnv, arg, DAT_004f53e0);
        return;
    }
}
