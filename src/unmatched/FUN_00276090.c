int FUN_00275ff0();
int FUN_00276010();
int FUN_00276040();
int FUN_00276060();

int FUN_00276090(const char *path, int code)
{
    int result;

    result = 0;
    if (path == 0) {
        return 0;
    }
    switch (code) {
    case 200:
        result = FUN_00275ff0();
        break;
    case 201:
        result = FUN_00276010();
        break;
    case 202:
    case 204:
        result = FUN_00276040();
        break;
    case 203:
    case 205:
        result = FUN_00276060();
        break;
    case 299:
        result = 1;
        break;
    }
    return result;
}
