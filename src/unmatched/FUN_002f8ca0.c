int strncmp();
int strcmp();
int strlen();
extern char DAT_004fa3c8[];
extern char DAT_004fabb0[];
struct Item { char p[20]; char *name; };
struct List { char p[8]; int count; char p12[4]; struct Item **data; };
struct Own { char p[20]; struct List *list; };
struct Item *FUN_002f8ca0(struct Own *arg0, char *arg1) {
    int i;
    char *s;
    int n;
    struct Item *it;

    n = arg0->list->count;
    if ((arg1 == 0) || (*arg1 == 0)) {
        return 0;
    }
    if (strncmp(arg1, DAT_004fa3c8, 0xD) == 0) {
        arg1 += 0xD;
    }
    if (strncmp(arg1, DAT_004fabb0, 6) == 0) {
        if (strlen(arg1) != 6) {
            arg1 += 6;
        }
    }
    for (i = 0; i < n; i++) {
        it = arg0->list->data[i];
        if (it != 0) {
            s = it->name;
            if ((s != 0) && (*s != 0)) {
                if (strncmp(s, DAT_004fa3c8, 0xD) == 0) {
                    s += 0xD;
                }
                if (strncmp(s, DAT_004fabb0, 6) == 0) {
                    if (strlen(arg1) != 6) {
                        s += 6;
                    }
                }
                if (strcmp(s, arg1) == 0) {
                    return it;
                }
            }
        }
    }
    return 0;
}
