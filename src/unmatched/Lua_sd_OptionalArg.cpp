/* 0x00372cf0 - Lua_sd_OptionalArg. Alternate (combat) compiler, -O3,p -Iinclude (also matches with -Cpp_exceptions off).
   Splits a '/'-separated optional-argument string and appends each part to the messenger as a string, or a typed
   value for 'I<n>' int, 'L<n>' long, 'V<x,y,z>' vec3 and 'F<expr>' float parts. */
#include "dw4/reflected.h"
extern "C" {
unsigned strlen(char *);
int FUN_001e6d30(char *, float *, int *);
int FUN_0030b3c0(void *, char *);
int FUN_0030b630(void *, float *);
int FUN_0030bbf0(void *, int, int);
int beMessenger_AppendFloat(int, float);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendLong(int, long long);
int beMessenger_AppendString(int, char *);
int beMessenger_AppendVec3(int, float *);
extern int DAT_0050dab0[4];
extern beSystem *DAT_0058a1b8[4];
extern int DAT_0058a1c0[4];
}

extern "C" void Lua_sd_OptionalArg(int arg0) {
    char *parts[12];
    char buf[1024];
    float tmp[3];
    float vec[3];
    float fv;
    char *q;
    char *s;
    int c;
    int iv;
    bool sign;
    int k;
    long long lv;
    int n;
    int i;
    igStringObj *seq;
    char **pp;
    char *p;

    if (*(char *)arg0 != 0) {
        p = (char *)arg0;
        if (strlen(p) > 0x400) {
            p[1023] = 0;
        }
        n = 0;
        q = buf;
        parts[n++] = q;
        pp = &parts[0];
        for (;;) {
            c = *p;
            if (c == 0) {
                *q = 0;
                break;
            }
            if (c == 0x2F) {
                *q = 0;
                p++;
                q++;
                parts[n++] = q;
            } else {
                *q = c;
                p++;
                q++;
            }
        }
        {
            for (i = 0; i < n; i++, pp++) {
                s = *pp;
                if (s[1] != 0x3C) {
                    beMessenger_AppendString(DAT_0058a1c0[0], s);
                } else {
                    switch (s[0]) {
                    case 0x49:
                        iv = 0;
                        sign = false;
                        k = 2;
                        if (s[2] == 0x2D) {
                            sign = true;
                            k++;
                        }
                        while (s[k] != 0x3E) {
                            iv = iv * 10;
                            iv += s[k] - 0x30;
                            k++;
                        }
                        if (sign) iv = -iv;
                        beMessenger_AppendInt(DAT_0058a1c0[0], iv);
                        break;
                    case 0x4C:
                        lv = 0;
                        k = 2;
                        while (s[k] != 0x3E) {
                            lv = lv * 10;
                            lv += s[k] - 0x30;
                            k++;
                        }
                        beMessenger_AppendLong(DAT_0058a1c0[0], lv);
                        break;
                    case 0x56:
                        FUN_001e6d30(s + 1, tmp, &DAT_0050dab0[0]);
                        vec[0] = tmp[0];
                        vec[1] = tmp[1];
                        vec[2] = tmp[2];
                        beMessenger_AppendVec3(DAT_0058a1c0[0], vec);
                        break;
                    case 0x46:
                        seq = (igStringObj *)DAT_0058a1b8[0]->_globalStrObj;
                        FUN_0030b3c0(seq, s + 2);
                        FUN_0030bbf0(seq, seq->_length - 1, 1);
                        FUN_0030b630(seq, &fv);
                        beMessenger_AppendFloat(DAT_0058a1c0[0], fv);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}
