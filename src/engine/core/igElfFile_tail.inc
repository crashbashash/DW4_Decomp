static void FUN_00320930(unsigned char *arg0) {
    unsigned short x;
    ((unsigned char *)&x)[0] = arg0[1];
    ((unsigned char *)&x)[1] = arg0[0];
    *(unsigned short *)arg0 = x;
}

static void FUN_00320960(unsigned char *arg0) {
    union { unsigned char b[4]; int w; } u;
    u.b[0] = arg0[3];
    u.b[1] = arg0[2];
    u.b[2] = arg0[1];
    u.b[3] = arg0[0];
    *(int *)arg0 = u.w;
}

void FUN_003209a0(unsigned char *p) {
    FUN_00320930(p + 16);
    FUN_00320930(p + 18);
    FUN_00320960(p + 20);
    FUN_00320960(p + 24);
    FUN_00320960(p + 28);
    FUN_00320960(p + 32);
    FUN_00320960(p + 36);
    FUN_00320930(p + 40);
    FUN_00320930(p + 42);
    FUN_00320930(p + 44);
    FUN_00320930(p + 46);
    FUN_00320930(p + 48);
    FUN_00320930(p + 50);
}

void FUN_00320a20(unsigned char *arg0, int arg1) {
    unsigned char *p = arg0;
    int n = arg1;
    for (; n > 0; n--) {
        FUN_00320960(p);
        FUN_00320960(p + 4);
        FUN_00320960(p + 8);
        FUN_00320960(p + 12);
        FUN_00320960(p + 16);
        FUN_00320960(p + 20);
        FUN_00320960(p + 24);
        FUN_00320960(p + 28);
        FUN_00320960(p + 32);
        FUN_00320960(p + 36);
        p += 40;
    }
}

void FUN_00320aa0(unsigned char *arg0, int arg1) {
    unsigned char *p = arg0;
    int n = arg1;
    for (; n > 0; n--) {
        FUN_00320960(p);
        FUN_00320960(p + 4);
        FUN_00320960(p + 8);
        FUN_00320930(p + 14);
        p += 16;
    }
}

void Gap__Core__igElfFile__vfunc_23(igElfFile *arg0) {
    Gap__Core__igProgramFile__vfunc_23((igProgramFile *)arg0);
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

void Gap__Core__igElfFile__vfunc_25(int arg0, void *arg1) {
    int temp_a1;
    int temp_a1_2;
    int temp_a1_3;
    int temp_a1_4;

    temp_a1 = *(int *)((char *)arg1 + 80);
    if (temp_a1 != 0) {
        FUN_00300f50((int)arg1, temp_a1);
    }
    temp_a1_2 = *(int *)((char *)arg1 + 72);
    if (temp_a1_2 != 0) {
        FUN_00300f50((int)arg1, temp_a1_2);
    }
    temp_a1_3 = *(int *)((char *)arg1 + 88);
    if (temp_a1_3 != 0) {
        FUN_00300f50((int)arg1, temp_a1_3);
    }
    temp_a1_4 = *(int *)((char *)arg1 + 96);
    if (temp_a1_4 != 0) {
        FUN_00300f50((int)arg1, temp_a1_4);
    }
    Gap__Core__igProgramFile__vfunc_25((int *)arg0, arg1);
}

int FUN_00320ea0(struct S_320ea0 *arg0, int arg1) {
    int base = arg0->f80;
    if (base != 0 && arg1 >= 0 && arg1 <= arg0->f76) {
        return base + arg1 * arg0->f62;
    }
    return 0;
}

int FUN_00320ee0(struct S_320ee0 *arg0, int arg1, int arg2) {
    int i;
    int t;
    for (i = 0; i < arg0->n; i++) {
        t = ((struct E_320ee0 *)FUN_00320ea0((S_320ea0 *)arg0, i))->f4;
        if (t == arg1) {
            if (arg2-- == 0) {
                return i;
            }
        }
    }
    return -1;
}

int FUN_00320f70(void *arg0, int arg1) {
    char *base = *(char **)((char *)arg0 + 96);
    if (base != 0 && arg1 >= 0 && arg1 <= *(int *)((char *)arg0 + 92)) return (int)(base + arg1*16); return 0;
}

static inline void prepareSink(ElfSymbolSink *sink, int count, unsigned low, unsigned top) {
    FUN_0030da00((int)sink, count);
    FUN_0030da10((int)sink, count * 4);
    FUN_0030da20((S_30da20 *)sink, low & ~1023, top);
    FUN_0030daa0((int *)sink);
}

void FUN_00321530(const char *in, char *out, int size) {
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
                        FUN_00321530(inner, out, size);
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

void Gap__Core__igElfFile__vfunc_29(int *result, void *self, char *mangled, char *out, int size) {
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
                    FUN_00321530(inner, out, size);
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

int *FUN_00321c10(int arg0, int *arg1) {
    int *v;
    while ((v = (int *)arg1[1]) != 0) {
        if (arg1[0] == arg0) return v;
        arg1 += 2;
    }
    return &DAT_004f7910[0];
}

char *FUN_00321c50(int arg0, int arg1, char *arg2) {
    int a;
    int i;
    char *s;
    char *sep;
    i = 0;
    *arg2 = 0;
    do {
        a = arg0 & (1 << i);
        if (a != 0) {
            s = ((char *)FUN_00321c10(a, (int *)arg1));
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

void Gap__Core__igElfFile__vfunc_30(O_321d30 *o) {
    FUN_00304430(DAT_004fe090);
    FUN_00304680();
    FUN_00304430(DAT_004fe0b0);
    FUN_00304680();
    FUN_00304430(DAT_004fe0d0, o->b16);
    FUN_00304680();
    FUN_00304430(DAT_004fe0f0, o->b17);
    FUN_00304680();
    FUN_00304430(DAT_004fe110, o->b18);
    FUN_00304680();
    FUN_00304430(DAT_004fe130, o->b19);
    FUN_00304680();
    FUN_00304430(DAT_004fe150, ((int)FUN_00321c10(o->b20, &DAT_004c23f0[0])));
    FUN_00304680();
    FUN_00304430(DAT_004fe170, ((int)FUN_00321c10(o->b21, &DAT_004c2410[0])));
    FUN_00304680();
    FUN_00304430(DAT_004fe190, o->b22);
    FUN_00304680();
    FUN_00304430(DAT_004fe1b0);
    FUN_00304680();
    FUN_00304430(DAT_004fe1d0, ((int)FUN_00321c10(o->h32, &DAT_004c2430[0])));
    FUN_00304680();
    FUN_00304430(DAT_004fe1f0, ((int)FUN_00321c10(o->h34, &DAT_004c2470[0])));
    FUN_00304680();
    FUN_00304430(DAT_004fe210, o->w36);
    FUN_00304680();
    FUN_00304430(DAT_004fe230, o->w40);
    FUN_00304680();
    FUN_00304430(DAT_004fe250, o->w44);
    FUN_00304680();
    FUN_00304430(DAT_004fe270, o->w48);
    FUN_00304680();
    FUN_00304430(DAT_004fe290, o->w52);
    FUN_00304680();
    FUN_00304430(DAT_004fe2b0, o->h56);
    FUN_00304680();
    FUN_00304430(DAT_004fe2d0, o->h58);
    FUN_00304680();
    FUN_00304430(DAT_004fe2f0, o->h60);
    FUN_00304680();
    FUN_00304430(DAT_004fe310, o->h62);
    FUN_00304680();
    FUN_00304430(DAT_004fe330, o->h64);
    FUN_00304680();
    FUN_00304430(DAT_004fe350, o->h66);
    FUN_00304680();
    FUN_00304430(DAT_004f95c8);
    FUN_00304680();
}

void Gap__Core__igElfFile__vfunc_31(int *arg0) {
    int temp_a1;
    int var_s0;
    temp_a1 = arg0[19];
    FUN_00304430(DAT_004fe370, temp_a1, temp_a1);
    FUN_00304680();
    for (var_s0 = 0; var_s0 < arg0[19]; var_s0++) {
        FUN_00322040((A_322040 *)arg0, var_s0, (B_322040 *)(FUN_00320ea0((S_320ea0 *)arg0, var_s0)));
    }
}

void FUN_00322040(struct A_322040 *arg0, int arg1, struct B_322040 *arg2) {
    char sp30[128];

    FUN_00304430(DAT_004fe4d0);
    FUN_00304680();
    FUN_00304430(DAT_004fe4f0, arg2->f0, arg0->f72 + arg2->f0);
    FUN_00304680();
    FUN_00304430(DAT_004fe520, ((int)FUN_00321c10(arg2->f4, &DAT_004c24c0[0])));
    FUN_00304680();
    FUN_00304430(DAT_004fe540, arg2->f8, ((int)FUN_00321c50(arg2->f8, (int)&DAT_004c2550[0], (char *)sp30)));
    FUN_00304680();
    FUN_00304430(DAT_004fe570, arg2->f12);
    FUN_00304680();
    FUN_00304430(DAT_004fe5a0, arg2->f16);
    FUN_00304680();
    FUN_00304430(DAT_004fe5d0, arg2->f20);
    FUN_00304680();
    FUN_00304430(DAT_004fe600, arg2->f24);
    FUN_00304680();
    FUN_00304430(DAT_004fe630, arg2->f28);
    FUN_00304680();
    FUN_00304430(DAT_004fe660, arg2->f32);
    FUN_00304680();
    FUN_00304430(DAT_004fe690, arg2->f36);
    FUN_00304680();
    FUN_00304430(DAT_004f95c8);
    FUN_00304680();
}

void Gap__Core__igElfFile__vfunc_32(struct E_3221c0 *arg0) {
    int temp_a1;
    int i;

    temp_a1 = arg0->n;
    FUN_00304430(DAT_004fe6c0, temp_a1, temp_a1);
    FUN_00304680();
    for (i = 0; i < arg0->n; i++) {
        FUN_00322240((igElfFile *)arg0, i, (unsigned char *)(FUN_00320f70(arg0, i)));
    }
}

void FUN_00322240(igElfFile *arg0, int arg1, unsigned char *arg2) {
    int *temp_v0;
    char *var_s0;

    temp_v0 = ((int *)FUN_00320ea0((S_320ea0 *)arg0, *(unsigned short *)(arg2 + 14)));
    if (temp_v0 != 0) {
        var_s0 = (char *)(arg0->_sectionHeaderStringTable + *temp_v0);
    } else {
        var_s0 = ((char *)DAT_004f7910);
    }
    FUN_00304430(DAT_004fe7a0, arg1);
    FUN_00304680();
    FUN_00304430(DAT_004fe7c0, *(int *)(arg2 + 0), arg0->_symbolStringTable + *(int *)(arg2 + 0));
    FUN_00304680();
    FUN_00304430(DAT_004fe7f0, *(int *)(arg2 + 4));
    FUN_00304680();
    FUN_00304430(DAT_004fe820, *(int *)(arg2 + 8));
    FUN_00304680();
    FUN_00304430(DAT_004fe850, arg2[12]);
    FUN_00304680();
    FUN_00304430(DAT_004fe880, ((int)FUN_00321c10(arg2[12] >> 4, (int *)DAT_004c2580)));
    FUN_00304680();
    FUN_00304430(DAT_004fe8b0, ((int)FUN_00321c10(arg2[12] & 0xF, (int *)DAT_004c25b0)));
    FUN_00304680();
    FUN_00304430(DAT_004fe8e0, arg2[13]);
    FUN_00304680();
    FUN_00304430(DAT_004fe910, *(unsigned short *)(arg2 + 14), var_s0);
    FUN_00304680();
    FUN_00304430(DAT_004f95c8);
    FUN_00304680();
}

