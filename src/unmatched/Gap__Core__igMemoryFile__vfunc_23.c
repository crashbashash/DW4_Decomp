int FUN_002efae0();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
struct MemoryFileHead { char p[12]; int f12; char p16[4]; unsigned int f20; int f24; char p28[16]; unsigned char open; char p2[3]; int data; int size; int pos; };
void Gap__Core__igMemoryFile__vfunc_23(int *arg0, struct MemoryFileHead *arg1, unsigned int arg2) {
    int sp3C;
    int sp38;

    if (arg1->open != 0) {
        *arg0 = DAT_004fb410[0];
        return;
    }
    if (arg2 == 8) {
        arg2 = arg1->f20;
    }
    switch (arg2) {
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
        *arg0 = DAT_004fb418[0];
        return;
    default:
        *arg0 = DAT_004fb418[0];
        return;
    case 0:
    case 4:
        FUN_002efae0(arg1->f12, &sp3C, &sp38);
        if (sp3C == 0) {
            *arg0 = DAT_004fb418[0];
            return;
        }
        arg1->pos = 0;
        arg1->data = sp3C;
        arg1->size = sp38;
        arg1->open = 1;
        arg1->f24 = sp3C;
        *arg0 = DAT_004fb410[0];
        return;
    }
}
