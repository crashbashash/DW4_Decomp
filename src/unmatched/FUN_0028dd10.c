int FUN_0028dc78(char *p);

char *FUN_0028dd10(char *end, int len, int mask)
{
    char c;
    unsigned int state = 0;
    char *p = end;
    char *start = end - len;

    while (start < p) {
        p--;
        c = *p;
        switch (state) {
        case 0:
            state = 1;
            break;
        case 1:
            if (c == 1)
                state = 2;
            break;
        case 2:
            if (c == 0)
                state = 3;
            else if (c != 1)
                state = 1;
            break;
        case 3:
            if (c == 0) {
                if (mask & FUN_0028dc78(p))
                    return p;
                state = 0;
            } else
                state = c != 1 ? 1 : 2;
            break;
        }
    }
    return 0;
}
