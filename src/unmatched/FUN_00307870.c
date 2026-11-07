extern char DAT_004fb1a8[];
extern char DAT_004fb1b0[];
extern char DAT_004fb200[];
extern char DAT_004fb260[];
int FUN_00129ef8();
int FUN_00306360();
int FUN_00306e50();
int FUN_00307700();
int FUN_00307a50();
int FUN_00307c10();
int FUN_00307fd0();
typedef struct Ini { char pad[20]; unsigned char flag; } Ini;
typedef struct Root { char pad[56]; Ini *cur; } Root;
extern Root *DAT_00586dc8;
void FUN_00307870(Ini *self, int file, int overwrite) {
    char eq;
    unsigned char flag;
    int lineNo;
    char line[4096];
    char key[4096];
    char value[4096];
    int n;
    int section;
    Ini *cur;

    lineNo = 0;
    section = -1;
    while (FUN_00307a50(self, file, line, &lineNo) != 0) {
        if (FUN_00129ef8(line, DAT_004fb1a8, value) <= 0) {
            continue;
        }
        if (value[0] == '#') {
            FUN_00307fd0(self, file, line, lineNo, overwrite);
            continue;
        }
        if (FUN_00129ef8(line, DAT_004fb1b0, value) == 1) {
            section = FUN_00306360(self, value, 1);
            continue;
        }
        n = FUN_00129ef8(line, DAT_004fb200, key, &eq, value);
        if (n <= 0 || n == 1) {
            continue;
        }
if (n > 1 && eq != '=') { continue; }
        if (n == 2) {
            value[0] = 0;
        }
        if (overwrite == 0 && FUN_00307c10(self, section, key, 0) != 0) {
            continue;
        }
        FUN_00307700(self, section, key, value);
    }
    cur = DAT_00586dc8->cur;
    flag = self->flag;
    FUN_00306e50(cur, 2, DAT_004fb260, &flag, flag, 0);
    self->flag = flag;
    if (self->flag != 0 && cur == self) {
        FUN_00306e50(cur, 2, DAT_004fb260, &flag, flag, 0);
    }
}
