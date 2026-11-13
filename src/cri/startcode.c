int mpvsc_GetKind(const unsigned char *p) {
    unsigned int code = p[0];
    int type;
    code <<= 8;
    code |= p[1];
    code <<= 8;
    code |= p[2];
    code <<= 8;
    code |= p[3];
    if (code == 0x100) {
        type = 4;
    } else if (code == 0x101) {
        type = 3;
    } else if (code - 0x102 < 0xAE) {
        type = 1;
    } else if (code == 0x1B2) {
        type = 32;
    } else if (code == 0x1B3) {
        type = 64;
    } else if (code == 0x1B5) {
        type = 16;
    } else if (code == 0x1B7) {
        type = 128;
    } else if (code == 0x1B8) {
        type = 8;
    } else {
        type = 0;
    }
    return type;
}

char *mpvsc_SearchBack(char *end, int len, int mask)
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
                if (mask & mpvsc_GetKind((const unsigned char *)p))
                    return p;
                state = 0;
            } else
                state = c != 1 ? 1 : 2;
            break;
        }
    }
    return 0;
}

char *MPV_SearchDelim(char *buf, int len, int mask)
{
    char *p = buf;
    char *end = buf + len;
    unsigned int state = 0;
    char c;
    char *hit;
    while (p < end) {
        c = *p++;
        switch (state) {
        case 0:
            if (c == 0)
                state = 1;
            break;
        case 1:
            state = c != 0 ? 0 : 2;
            break;
        case 2:
            if (c == 1)
                state = 3;
            else if (c != 0)
                state = 0;
            break;
        case 3:
            hit = p - 4;
            if (mask & mpvsc_GetKind((const unsigned char *)hit))
                return hit;
            state = 0;
            break;
        }
    }
    return 0;
}

char *mpvsc_SearchFrom(char *dst, char *src, int len, int mask)
{
    char *p = src;
    char *end = src + len;
    unsigned int state = 0;
    char c;
    while (p < end) {
        c = *p++;
        *dst++ = c;
        switch (state) {
        case 0:
            if (c == 0)
                state = 1;
            break;
        case 1:
            state = c != 0 ? 0 : 2;
            break;
        case 2:
            if (c == 1)
                state = 3;
            else if (c != 0)
                state = 0;
            break;
        case 3:
            if (mask & mpvsc_GetKind((const unsigned char *)(p - 4)))
                return p;
            state = 0;
            break;
        }
    }
    return p;
}

