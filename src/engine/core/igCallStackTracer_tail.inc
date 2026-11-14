int *igCallStackTracer_CaptureCallStack(int *arg0) {
    int t;
    if (arg0[3] > 0) {
        arg0[2] = 1;
    } else {
        List_Resize(arg0, 1, 4);
    }
    t = arg0[2];
    if (t != 0 && 0 < t) {
        *(int *)arg0[4] = DAT_004c1ea0[0];
    }
    return (int *)arg0[4];
}

int igCallStackTracer_HasSymbols(void) {
    igSymbolTableView *symbols;
    symbols = (igSymbolTableView *)((ObjectSystemView **)g_objectSystem)[0]->symbolTable;
    if (symbols != 0) {
        if (symbols->vfunc_23() != 0) {
            return 1;
        }
    }
    return 0;
}

void igCallStackTracer_FormatAddress(igResult *result, igCallStackTracerView *self, int addr, int format, long long output, long long outputSize) {
    char buf[256];
    char name[256];
    int offset;
    int line;
    igResult resolved = self->vfunc_27(addr, buf, 255, &offset, name, 255, &line);
    igResult formatted = self->vfunc_28(addr, buf, offset, name, line, format, output, outputSize);
    result->v = resolved.v;
}

igResult igCallStackTracer_LookupAddress(void *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line) {
    igSymbolTableView *symbols = (igSymbolTableView *)((ObjectSystemView **)g_objectSystem)[0]->symbolTable;
    if (symbols != 0 && symbols->vfunc_23() != 0) {
        int base = 0;
        int other = 0;
        if (symbols->vfunc_27(addr, buf, size, &base, &other, name, nameSize, line) == g_resultSuccess) {
            *offset = addr - base;
            return g_resultSuccess;
        }
    }
    if (buf != 0) {
        char tmp[20];
        sprintf(tmp, ((char *)text_0x_08x), addr);
        strncpy(buf, tmp, size);
    }
    *offset = 0;
    if (name != 0) {
        *name = 0;
    }
    *line = 0;
    return g_resultFailure;
}

void Gap__Core__igCallStackTracer__vfunc_29(void) {

}

void Gap__Core__igCallStackTracer__vfunc_30(void) {

}

