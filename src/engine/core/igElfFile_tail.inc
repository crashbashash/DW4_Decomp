static void igElfFile_Swap16(unsigned char *arg0) {
    unsigned short x;
    ((unsigned char *)&x)[0] = arg0[1];
    ((unsigned char *)&x)[1] = arg0[0];
    *(unsigned short *)arg0 = x;
}

static void igElfFile_Swap32(unsigned char *arg0) {
    union { unsigned char b[4]; int w; } u;
    u.b[0] = arg0[3];
    u.b[1] = arg0[2];
    u.b[2] = arg0[1];
    u.b[3] = arg0[0];
    *(int *)arg0 = u.w;
}

void igElfFile_SwapHeader(unsigned char *p) {
    igElfFile_Swap16(p + 16);
    igElfFile_Swap16(p + 18);
    igElfFile_Swap32(p + 20);
    igElfFile_Swap32(p + 24);
    igElfFile_Swap32(p + 28);
    igElfFile_Swap32(p + 32);
    igElfFile_Swap32(p + 36);
    igElfFile_Swap16(p + 40);
    igElfFile_Swap16(p + 42);
    igElfFile_Swap16(p + 44);
    igElfFile_Swap16(p + 46);
    igElfFile_Swap16(p + 48);
    igElfFile_Swap16(p + 50);
}

void igElfFile_SwapSectionHeaders(unsigned char *arg0, int arg1) {
    unsigned char *p = arg0;
    int n = arg1;
    for (; n > 0; n--) {
        igElfFile_Swap32(p);
        igElfFile_Swap32(p + 4);
        igElfFile_Swap32(p + 8);
        igElfFile_Swap32(p + 12);
        igElfFile_Swap32(p + 16);
        igElfFile_Swap32(p + 20);
        igElfFile_Swap32(p + 24);
        igElfFile_Swap32(p + 28);
        igElfFile_Swap32(p + 32);
        igElfFile_Swap32(p + 36);
        p += 40;
    }
}

void igElfFile_SwapSymbols(unsigned char *arg0, int arg1) {
    unsigned char *p = arg0;
    int n = arg1;
    for (; n > 0; n--) {
        igElfFile_Swap32(p);
        igElfFile_Swap32(p + 4);
        igElfFile_Swap32(p + 8);
        igElfFile_Swap16(p + 14);
        p += 16;
    }
}

void igElfFile_Reset(igElfFile *arg0) {
    igProgramFile_Reset((igProgramFile *)arg0);
    memset(arg0->_header, 0, 0x34);
    arg0->_sectionHeaderStringTableSize = 0;
    arg0->_sectionHeaderStringTable = 0;
    arg0->_sectionHeaderCount = 0;
    arg0->_sectionHeaders = 0;
    arg0->_symbolStringTableSize = 0;
    arg0->_symbolStringTable = 0;
    arg0->_symbolCount = 0;
    arg0->_symbols = 0;
}

void igElfFile_Open(int *result, ElfFileView *self, const char *path) {
    if (igProgramFile_Open((igProgramFile *)self, path) == g_resultFailure) {
        *result = g_resultFailure.v;
        return;
    }
    if (self->stream->Read(self->magic, 0x34, 1) != 1) {
        igReport_Printf(DAT_004fdda0, self->path);
        igReport_Flush();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    int hostEndian = 1;
    int fileEndian = self->endian;
    if (GPR_005549b4 == 0x12) {
        hostEndian = 2;
    }
    if (fileEndian != hostEndian) {
        igElfFile_SwapHeader(self->magic);
    }
    if (self->magic[0] != 0x7F || self->magic[1] != 'E' || self->magic[2] != 'L' || self->magic[3] != 'F') {
        igReport_Printf((const char *)DAT_004fddc0, self->path);
        igReport_Flush();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    int sectionOffset = self->sectionHeaderOffset;
    if (sectionOffset == 0) {
        igReport_Printf((const char *)DAT_004fdde0, self->path, sectionOffset);
        igReport_Flush();
        self->Close();
        *result = g_resultFailure.v;
        return;
    }
    if (self->Load(sectionOffset, self->sectionHeaderCount * self->sectionHeaderEntrySize, &self->sectionHeaders) == g_resultFailure) {
        *result = g_resultFailure.v;
        return;
    }
    if (GPR_005549b4 == 0x12) {
        hostEndian = 2;
    } else {
        hostEndian = 1;
    }
    if (self->endian != hostEndian) {
        igElfFile_SwapSectionHeaders((unsigned char *)self->sectionHeaders, self->sectionHeaderCount);
    }
    self->sectionCount = self->sectionHeaderCount;
    if (self->sectionNameIndex != 0) {
        ElfSection *section = igElfFile_GetSectionHeader(self, self->sectionNameIndex);
        if (section != 0 && section->type == 3) {
            self->sectionNamesSize = section->size;
            if (self->Load(section->offset, section->size, &self->sectionNames) == g_resultFailure) {
                *result = g_resultFailure.v;
                return;
            }
        }
    }
    *result = g_resultSuccess.v;
}

void igElfFile_Close(int *result, ElfFileView *self) {
    if (self->sectionHeaders != 0) {
        igObject_FreeMemory((int)self, (int)self->sectionHeaders);
    }
    if (self->sectionNames != 0) {
        igObject_FreeMemory((int)self, (int)self->sectionNames);
    }
    if (self->strings != 0) {
        igObject_FreeMemory((int)self, (int)self->strings);
    }
    if (self->symbols != 0) {
        igObject_FreeMemory((int)self, (int)self->symbols);
    }
    igProgramFile_Close(result, self);
}

ElfSection *igElfFile_GetSectionHeader(ElfFileView *self, int index) {
    char *base = (char *)self->sectionHeaders;
    if (base != 0 && index >= 0 && index <= self->sectionCount) {
        return (ElfSection *)(base + index * self->sectionHeaderEntrySize);
    }
    return 0;
}

int igElfFile_FindSectionByType(ElfFileView *self, int type, int nth) {
    int i;
    int t;
    for (i = 0; i < self->sectionCount; i++) {
        t = igElfFile_GetSectionHeader(self, i)->type;
        if (t == type) {
            if (nth-- == 0) {
                return i;
            }
        }
    }
    return -1;
}

int igElfFile_GetSymbol(void *arg0, int arg1) {
    char *base = *(char **)((char *)arg0 + 96);
    if (base != 0 && arg1 >= 0 && arg1 <= *(int *)((char *)arg0 + 92)) return (int)(base + arg1*16); return 0;
}

static inline void prepareSink(igSymbolTableView *table, int count, unsigned low, unsigned top) {
    igSymbolTable_SetCapacity((int)table, count);
    igSymbolTable_SetHashCapacity((int)table, count * 4);
    igSymbolTable_SetAddressRange(table, low & ~1023, top);
    igSymbolTable_ReserveStorage(table);
}

void igElfFile_DemangleName(const char *in, char *out, int size) {
    char *cursor = (char *)in;
    char inner[256];
    int pointers = 0;
    int copy;
    int parts;
    int length;
    int advance;
    int limit;
    int c;
    char *open;
    while ((c = *cursor) != 0) {
        char kind = c;
        if (kind == 'P') {
            cursor++;
            pointers++;
        } else if (kind == 'Q') {
            cursor++;
            parts = *cursor - '0';
            if (parts > 0 && parts < 10) {
                cursor++;
                while (parts-- != 0) {
                    length = 0;
                    while ((c = *cursor) >= '0' && c <= 57) {
                        length = c - '0' + length * 10;
                        cursor++;
                    }
                    limit = size - 1;
                    copy = length;
                    if (copy > limit) {
                        copy = limit;
                    }
                    strncpy(out, cursor, copy);
                    out[copy] = 0;
                    open = strchr(out, '<');
                    if (open != 0) {
                        length = open - out;
                        memcpy(inner, open + 1, copy + 1 - length);
                        advance = length + 1;
                        if (advance > 254) {
                            advance = 254;
                        }
                        if (advance > size) {
                            advance = size;
                        }
                        out += advance;
                        size -= advance;
                        *out = 0;
                        igElfFile_DemangleName(inner, out, size);
                        advance = strlen(out);
                        size -= advance;
                        out += advance;
                        if (size > 1) {
                            *out = '>';
                            size--;
                            out++;
                        }
                        if (size > 1) {
                            *out = 0;
                            size--;
                            out++;
                        }
                    } else {
                        cursor += length;
                        out += copy;
                        size -= copy;
                    }
                    if (parts != 0 && size > 2) {
                        size -= 2;
                        out[0] = ':';
                        out[1] = ':';
                        out += 2;
                    }
                }
            }
            while (((pointers != 0) ^ 1) == 0 && size > 1) {
                *out = '*';
                size--;
                pointers--;
                out++;
                *out = 0;
            }
            continue;
        } else {
            cursor++;
        }
    }
    *out = 0;
}

void igElfFile_Demangle(int *result, void *self, char *mangled, char *out, int size) {
    char inner[256];
    char *start;
    char *sep;
    char *open;
    int parts;
    int c;
    int length;
    int copy;
    int limit;
    int advance;
    int nameLength;
    char *scan;
    int i;
    char *tail;
    sep = strstr(*mangled != 0 ? mangled + 1 : mangled, DAT_004fdf80);
    start = out;
    if (sep != 0) {
        nameLength = sep - mangled;
    } else {
        nameLength = strlen(mangled);
        if (nameLength > size - 1) {
            nameLength = size - 1;
        }
        strncpy(out, mangled, nameLength);
        out[nameLength] = 0;
        *result = g_resultSuccess.v;
        return;
    }
    if (sep[2] == 'Q') {
        sep += 2;
        sep++;
        parts = *sep - '0';
        if (parts > 0 && parts < 10) {
            sep++;
            while (parts-- != 0) {
                length = 0;
                while ((c = *sep) >= '0' && c <= 57) {
                    length = c - '0' + length * 10;
                    sep++;
                }
                limit = size - 1;
                copy = length;
                if (copy > limit) {
                    copy = limit;
                }
                strncpy(out, sep, copy);
                out[copy] = 0;
                open = strchr(out, '<');
                if (open != 0) {
                    length = open - out;
                    memcpy(inner, open + 1, copy + 1 - length);
                    advance = length + 1;
                    if (advance > 254) {
                        advance = 254;
                    }
                    if (advance > size) {
                        advance = size;
                    }
                    out += advance;
                    size -= advance;
                    *out = 0;
                    igElfFile_DemangleName(inner, out, size);
                    advance = strlen(out);
                    size -= advance;
                    out += advance;
                    if (size > 1) {
                        *out = '>';
                        size--;
                        out++;
                    }
                    if (size > 1) {
                        *out = 0;
                        size--;
                        out++;
                    }
                } else {
                    sep += length;
                    out += copy;
                    size -= copy;
                }
                if (size > 2) {
                    size -= 2;
                    out[0] = ':';
                    out[1] = ':';
                    out += 2;
                }
            }
        }
    }
    *out = 0;
    tail = out - 1;
    if (strncmp(mangled, DAT_004fdf80, 2) == 0) {
        while (((start < tail) ^ 1) == 0 && *tail == ':') {
            tail--;
        }
        scan = tail;
        if (*tail != 0) {
            tail++;
        }
        while (((start < scan) ^ 1) == 0 && *scan != ':') {
            scan--;
        }
        if (*scan == ':') {
            scan++;
        }
        if (strncmp(mangled, DAT_004fde68, nameLength) == 0) {
            nameLength = tail - scan;
            if (nameLength > size - 1) {
                nameLength = size - 1;
            }
            strncpy(out, scan, nameLength);
            out[nameLength] = 0;
            *result = g_resultSuccess.v;
            return;
        }
        if (strncmp(mangled, DAT_004fde70, nameLength) == 0) {
            nameLength = tail - scan;
            if (size > 0) {
                *out = '~';
                size--;
                out++;
            }
            if (nameLength > size - 1) {
                nameLength = size - 1;
            }
            strncpy(out, scan, nameLength);
            out[nameLength] = 0;
            *result = g_resultSuccess.v;
            return;
        }
        for (i = 0; DAT_004c2380[i].mangled != 0; i++) {
            if (strncmp(DAT_004c2380[i].mangled, mangled, nameLength) == 0 && DAT_004c2380[i].name != 0) {
                nameLength = strlen(DAT_004c2380[i].name);
                if (nameLength > size - 1) {
                    nameLength = size - 1;
                }
                strncpy(out, DAT_004c2380[i].name, nameLength);
                out[nameLength] = 0;
                *result = g_resultSuccess.v;
                return;
            }
        }
    }
    if (nameLength > size - 1) {
        nameLength = size - 1;
    }
    strncpy(out, mangled, nameLength);
    out[nameLength] = 0;
    *result = g_resultSuccess.v;
}

int *igElfFile_LookupValueName(int arg0, int *arg1) {
    int *v;
    while ((v = (int *)arg1[1]) != 0) {
        if (arg1[0] == arg0) return v;
        arg1 += 2;
    }
    return &DAT_004f7910[0];
}

char *igElfFile_FormatFlags(int arg0, int arg1, char *arg2) {
    int a;
    int i;
    char *s;
    char *sep;
    i = 0;
    *arg2 = 0;
    do {
        a = arg0 & (1 << i);
        if (a != 0) {
            s = ((char *)igElfFile_LookupValueName(a, (int *)arg1));
            if (*s != 0) {
                if (*arg2 != 0) {
                    sep = ((char *)DAT_004f7910);
                } else {
                    sep = DAT_004fe080;
                }
                sprintf(&arg2[strlen(arg2)], DAT_004fe088, sep, s);
            }
        }
        i++;
    } while (i < 32);
    return arg2;
}

void igElfFile_PrintHeader(ElfFileView *o) {
    igReport_Printf(DAT_004fe090);
    igReport_Flush();
    igReport_Printf(DAT_004fe0b0);
    igReport_Flush();
    igReport_Printf(DAT_004fe0d0, o->magic[0]);
    igReport_Flush();
    igReport_Printf(DAT_004fe0f0, o->magic[1]);
    igReport_Flush();
    igReport_Printf(DAT_004fe110, o->magic[2]);
    igReport_Flush();
    igReport_Printf(DAT_004fe130, o->magic[3]);
    igReport_Flush();
    igReport_Printf(DAT_004fe150, ((int)igElfFile_LookupValueName(o->elfClass, &DAT_004c23f0[0])));
    igReport_Flush();
    igReport_Printf(DAT_004fe170, ((int)igElfFile_LookupValueName(o->endian, &DAT_004c2410[0])));
    igReport_Flush();
    igReport_Printf(DAT_004fe190, o->identVersion);
    igReport_Flush();
    igReport_Printf(DAT_004fe1b0);
    igReport_Flush();
    igReport_Printf(DAT_004fe1d0, ((int)igElfFile_LookupValueName(o->type, &DAT_004c2430[0])));
    igReport_Flush();
    igReport_Printf(DAT_004fe1f0, ((int)igElfFile_LookupValueName(o->machine, &DAT_004c2470[0])));
    igReport_Flush();
    igReport_Printf(DAT_004fe210, o->version);
    igReport_Flush();
    igReport_Printf(DAT_004fe230, o->entry);
    igReport_Flush();
    igReport_Printf(DAT_004fe250, o->programHeaderOffset);
    igReport_Flush();
    igReport_Printf(DAT_004fe270, o->sectionHeaderOffset);
    igReport_Flush();
    igReport_Printf(DAT_004fe290, o->flags);
    igReport_Flush();
    igReport_Printf(DAT_004fe2b0, o->headerSize);
    igReport_Flush();
    igReport_Printf(DAT_004fe2d0, o->programHeaderEntrySize);
    igReport_Flush();
    igReport_Printf(DAT_004fe2f0, o->programHeaderCount);
    igReport_Flush();
    igReport_Printf(DAT_004fe310, o->sectionHeaderEntrySize);
    igReport_Flush();
    igReport_Printf(DAT_004fe330, o->sectionHeaderCount);
    igReport_Flush();
    igReport_Printf(DAT_004fe350, o->sectionNameIndex);
    igReport_Flush();
    igReport_Printf(DAT_004f95c8);
    igReport_Flush();
}

void igElfFile_PrintSectionHeaders(int *arg0) {
    int temp_a1;
    int var_s0;
    temp_a1 = arg0[19];
    igReport_Printf(DAT_004fe370, temp_a1, temp_a1);
    igReport_Flush();
    for (var_s0 = 0; var_s0 < arg0[19]; var_s0++) {
        igElfFile_PrintSectionHeader((ElfFileView *)arg0, var_s0, igElfFile_GetSectionHeader((ElfFileView *)arg0, var_s0));
    }
}

void igElfFile_PrintSectionHeader(ElfFileView *arg0, int arg1, ElfSection *arg2) {
    char sp30[128];

    igReport_Printf(DAT_004fe4d0);
    igReport_Flush();
    igReport_Printf(DAT_004fe4f0, arg2->name, (int)arg0->sectionNames + arg2->name);
    igReport_Flush();
    igReport_Printf(DAT_004fe520, ((int)igElfFile_LookupValueName(arg2->type, &DAT_004c24c0[0])));
    igReport_Flush();
    igReport_Printf(DAT_004fe540, arg2->flags, ((int)igElfFile_FormatFlags(arg2->flags, (int)&DAT_004c2550[0], (char *)sp30)));
    igReport_Flush();
    igReport_Printf(DAT_004fe570, arg2->addr);
    igReport_Flush();
    igReport_Printf(DAT_004fe5a0, arg2->offset);
    igReport_Flush();
    igReport_Printf(DAT_004fe5d0, arg2->size);
    igReport_Flush();
    igReport_Printf(DAT_004fe600, arg2->link);
    igReport_Flush();
    igReport_Printf(DAT_004fe630, arg2->info);
    igReport_Flush();
    igReport_Printf(DAT_004fe660, arg2->addressAlign);
    igReport_Flush();
    igReport_Printf(DAT_004fe690, arg2->entrySize);
    igReport_Flush();
    igReport_Printf(DAT_004f95c8);
    igReport_Flush();
}

void igElfFile_PrintSymbols(ElfFileView *arg0) {
    int temp_a1;
    int i;

    temp_a1 = arg0->symbolCount;
    igReport_Printf(DAT_004fe6c0, temp_a1, temp_a1);
    igReport_Flush();
    for (i = 0; i < arg0->symbolCount; i++) {
        igElfFile_PrintSymbol((igElfFile *)arg0, i, (unsigned char *)(igElfFile_GetSymbol(arg0, i)));
    }
}

void igElfFile_PrintSymbol(igElfFile *arg0, int arg1, unsigned char *arg2) {
    int *temp_v0;
    char *var_s0;

    temp_v0 = ((int *)igElfFile_GetSectionHeader((ElfFileView *)arg0, *(unsigned short *)(arg2 + 14)));
    if (temp_v0 != 0) {
        var_s0 = (char *)(arg0->_sectionHeaderStringTable + *temp_v0);
    } else {
        var_s0 = ((char *)DAT_004f7910);
    }
    igReport_Printf(DAT_004fe7a0, arg1);
    igReport_Flush();
    igReport_Printf(DAT_004fe7c0, *(int *)(arg2 + 0), arg0->_symbolStringTable + *(int *)(arg2 + 0));
    igReport_Flush();
    igReport_Printf(DAT_004fe7f0, *(int *)(arg2 + 4));
    igReport_Flush();
    igReport_Printf(DAT_004fe820, *(int *)(arg2 + 8));
    igReport_Flush();
    igReport_Printf(DAT_004fe850, arg2[12]);
    igReport_Flush();
    igReport_Printf(DAT_004fe880, ((int)igElfFile_LookupValueName(arg2[12] >> 4, (int *)DAT_004c2580)));
    igReport_Flush();
    igReport_Printf(DAT_004fe8b0, ((int)igElfFile_LookupValueName(arg2[12] & 0xF, (int *)DAT_004c25b0)));
    igReport_Flush();
    igReport_Printf(DAT_004fe8e0, arg2[13]);
    igReport_Flush();
    igReport_Printf(DAT_004fe910, *(unsigned short *)(arg2 + 14), var_s0);
    igReport_Flush();
    igReport_Printf(DAT_004f95c8);
    igReport_Flush();
}

