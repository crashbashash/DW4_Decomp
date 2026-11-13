extern char text_all[]; /* "all" */
int _sceSifLoadElfPart(const char *name, const char *section, int *data, int rpc_number);

int sceSifLoadElf(const char *name, int *data) {
    return _sceSifLoadElfPart(name, text_all, data, 1);
}
