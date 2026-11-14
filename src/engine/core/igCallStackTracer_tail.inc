int *igCallStackTracer_CaptureCallStack(int *stack) {
    int count;
    if (stack[3] > 0) {
        stack[2] = 1;
    } else {
        List_Resize(stack, 1, 4);
    }
    count = stack[2];
    if (count != 0 && 0 < count) {
        *(int *)stack[4] = g_callStackRootAddress[0];
    }
    return (int *)stack[4];
}

int igCallStackTracer_HasSymbols(void) {
    igSymbolTableView *symbols;
    symbols = (igSymbolTableView *)((ObjectSystemView **)g_objectSystem)[0]->symbolTable;
    if (symbols != 0) {
        if (symbols->getSymbolCount() != 0) {
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
    igResult resolved = self->lookupAddress(addr, buf, 255, &offset, name, 255, &line);
    igResult formatted = self->vfunc_28(addr, buf, offset, name, line, format, output, outputSize);
    result->v = resolved.v;
}

igResult igCallStackTracer_LookupAddress(void *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line) {
    igSymbolTableView *symbols = (igSymbolTableView *)((ObjectSystemView **)g_objectSystem)[0]->symbolTable;
    if (symbols != 0 && symbols->getSymbolCount() != 0) {
        int base = 0;
        int other = 0;
        if (symbols->getSymbolAtAddress(addr, buf, size, &base, &other, name, nameSize, line) == g_resultSuccess) {
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

/* String literals are read-only here, as in the original build: a two-byte literal then lives outside
 * small data and strcpy from it is a fixed-size copy. */
#pragma push
#pragma readonly_strings on
extern "C" const char *g_callStackFormat;
extern "C" char *strrchr(const char *, int);
extern "C" igResult Gap__Core__igCallStackTracer__vfunc_28(igCallStackTracerView *self, int addr, char *function, int offset, char *path, int line,
                                                           const char *format, char *output, int outputSize);

/* Formats one call-stack entry. Each format character is a field, optionally followed by a quoted
 * printf specification: a address, s function, o offset, l line, p source path, f source file name;
 * "..." is literal text and \n \r \t are escapes. */
igResult Gap__Core__igCallStackTracer__vfunc_28(igCallStackTracerView *self, int addr, char *function, int offset, char *path, int line,
                                                const char *format, char *output, int outputSize) {
    igResult result = g_resultSuccess;
    char spec[256];
    char text[256];
    if (format == 0 || *format == 0) {
        format = g_callStackFormat;
    }
    if (format == 0 || *format == 0) {
        format = "s+o'0x%x'";
    }
    if (outputSize != 0) *output = 0;
    while (*format != '\0') {
        char field = *format;
        int c;
        spec[0] = 0;
        format++;
        if (field != '"' && *format == '\'') {
            int n = 0;
            format++;
            while (*format && *format != '\'' && n < 255) {
                if (*format == '\\') {
                    format++;
                    switch (*format) {
                    case 'n': spec[n++] = '\n'; break;
                    case 'r': spec[n++] = '\r'; break;
                    case 't': spec[n++] = '\t'; break;
                    }
                } else {
                    spec[n++] = *format;
                }
                format++;
            }
            spec[n] = 0;
            if (*format == '\'') {
                format++;
            }
        }
        text[0] = 0;
        switch (field) {
        case 'a':
            sprintf(text, spec[0] != 0 ? spec : "0x%08x", addr);
            break;
        case 'f': {
            char *backslash = strrchr(path, '\\');
            char *slash = strrchr(path, '/');
            char *name;
            if (backslash != 0 && slash != 0) {
                name = slash < backslash ? backslash : slash;
            } else {
                name = backslash != 0 ? backslash : slash;
            }
            if (name != 0) {
                name++;
            } else {
                name = path;
            }
            if (name != 0 && *name != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", name);
            }
            break;
        }
        case 'l':
            sprintf(text, spec[0] != 0 ? spec : "%d", line);
            break;
        case 'o':
            sprintf(text, spec[0] != 0 ? spec : "%d", offset);
            break;
        case 'p':
            if (path != 0 && *path != 0) {
                sprintf(text, spec[0] != 0 ? spec : "%s", path);
            }
            break;
        case 's':
            sprintf(text, spec[0] != 0 ? spec : "%s", function);
            break;
        case '\\':
            switch (*format++) {
            case 'n': strcpy(text, "\n"); break;
            case 'r': strcpy(text, "\r"); break;
            case 't': strcpy(text, "\t"); break;
            }
            break;
        case '"':
            while (*format && (c = *format) != '"') {
                if (c == '\\') {
                    format++;
                    switch (*format) {
                    case 'n': strcat(text, "\n"); break;
                    case 'r': strcat(text, "\r"); break;
                    case 't': strcat(text, "\t"); break;
                    }
                } else {
                    sprintf(text + strlen(text), "%c", c);
                }
                format++;
            }
            if (*format == '"') {
                format++;
            }
            break;
        default:
            sprintf(text, "%c", field);
            break;
        }
        strncat(output, text, outputSize);
    }
    if (outputSize > 1) {
        output[outputSize - 1] = 0;
    }
    return result;
}

#pragma pop

void Gap__Core__igCallStackTracer__vfunc_29(void) {

}

void Gap__Core__igCallStackTracer__vfunc_30(void) {

}

