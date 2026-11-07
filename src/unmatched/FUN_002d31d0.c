int strncpy();
struct N { char pad[0x90]; char name[128]; };
extern char *DAT_004c1eb8[4];
void FUN_002d31d0(struct N *arg0, char *arg1) {
    if (arg1 != 0) {
        strncpy(arg0->name, arg1, 0x7F);
        arg0->name[127] = 0;
    } else {
        arg0->name[0] = 0;
    }
    if ((arg1 != 0) && (*arg1 != 0)) {
        DAT_004c1eb8[0] = arg0->name;
    }
}
