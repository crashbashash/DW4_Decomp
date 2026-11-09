int FUN_002744a8();
int FUN_002744b8();
int FUN_002744d8();
int FUN_002744e0();

int FUN_002744f8(const char *path, int code)
{
    int result;

    result = 0;
    if (path == 0) {
        return 0;
    }
    switch (code) {
    case 200:
        result = FUN_002744a8();
        break;
    case 201:
        result = FUN_002744b8();
        break;
    case 202:
    case 204:
        result = FUN_002744d8();
        break;
    case 203:
    case 205:
        result = FUN_002744e0();
        break;
    case 299:
        result = 1;
        break;
    }
    return result;
}
