/* eeloadfile.c - libkernl's client of the IOP loadfile server: loads, starts, stops and finds IOP
 * modules, loads EE ELF files, and reads and writes IOP memory words. Every call binds the server
 * first and sends one 512-byte request, which the reply overwrites. */
#include "dw4/sony/sif.h"

#define LF_SERVER 0x80000006

/* the loadfile server's RPC functions */
#define LF_SET_ADDR 2
#define LF_GET_ADDR 3
#define LF_LOAD_MODULE_BUFFER 6
#define LF_STOP_MODULE 7
#define LF_UNLOAD_MODULE 8
#define LF_SEARCH_MODULE_BY_NAME 9
#define LF_SEARCH_MODULE_BY_ADDRESS 10
#define LF_VERSION 255

/* _sceSifLoadModule's and _sceSifLoadElfPart's command */
#define LF_LOAD_MODULE 0
#define LF_LOAD_ELF 1

#define LF_PATH_MAX 252
#define LF_ARG_MAX 252

#define LF_ERR_BIND 0xFFFF0000
#define LF_ERR_RPC 0xFFFEFFFF
#define LF_ERR_TYPE 0xFFFEFFFE
#define LF_ERR_LOAD 0xFFFEFFFD
#define LF_ERR_VERSION 0xFFFEFFFC

/* The module and ELF requests. On the way out the first two words carry the call's arguments; the
 * reply puts the server's result and the module's own result there. */
typedef struct {
    int result;
    int modres;
    char path[LF_PATH_MAX];
    char args[LF_ARG_MAX];
} LfModuleRequest;

/* A module argument block copied whole when it fills the request. */
typedef struct {
    char bytes[LF_ARG_MAX];
} LfArgs;

/* the server's version, four characters compared with libkernl's own */
typedef struct {
    char text[4];
} LfVersion;

typedef union {
    unsigned char b;
    unsigned short h;
    unsigned int w;
} LfWord;

/* sceSifGetIopAddr/sceSifSetIopAddr: an IOP address and the width of the word at it */
typedef struct {
    LfWord addr;
    int type;
    LfWord value;
    int pad[5];
} LfAddrRequest;

/* the one send buffer every request shares */
typedef union {
    LfModuleRequest module;
    LfAddrRequest addr;
} LfSendData;

int memcmp(const void *a, const void *b, unsigned int size);
void *memcpy(void *dst, const void *src, unsigned int size);
void *memset(void *dst, int value, unsigned int size);
char *strncpy(char *dst, const char *src, unsigned int size);

extern char __ps2_klibinfo__[];
/* negative until the server is bound */
extern int _bind_check;
extern char *_lfwildcard;
extern LfSendData _lf_senddata;
extern sceSifClientData _lf_cd;
extern LfVersion _lfversion;

int _lf_bind(void)
{
    int i;
    if (_bind_check < 0) {
        while (1) {
            if (sceSifBindRpc(&_lf_cd, LF_SERVER, 0) < 0) {
                return -1;
            }
            if (_lf_cd.serve != 0) {
                _bind_check = 0;
                if (sceSifCallRpc(&_lf_cd, LF_VERSION, 0, 0, 0, &_lf_senddata, 4, 0, 0) < 0) {
                    return LF_ERR_RPC;
                }
                _lfversion = *(LfVersion *)&_lf_senddata;
                return 0;
            }
            i = 0x100000;
            while (i--);
        }
    }
    return 0;
}

/* Nonzero when loadfile's version differs from libkernl's and neither is the wildcard. */
int _lf_version(void)
{
    char *expected = &__ps2_klibinfo__[12];
    char *version = _lfversion.text;
    int result = 0;
    if (memcmp(version, expected, 4) != 0 && memcmp(version, _lfwildcard, 4) != 0) {
        result = memcmp(expected, _lfwildcard, 4) != 0;
    }
    return result;
}

int sceSifLoadFileReset(void)
{
    _bind_check = -1;
    memset(&_lfversion, 0, 4);
    return 0;
}

int _sceSifLoadModuleBuffer(void *addr, int arglen, const char *args, int *modres)
{
    int result;
    if (_lf_bind() < 0) {
        return LF_ERR_BIND;
    }
    if (_lf_version() != 0) {
        return LF_ERR_VERSION;
    }
    _lf_senddata.module.result = (int)addr;
    if (args != 0) {
        if (arglen > LF_ARG_MAX) {
            *(LfArgs *)_lf_senddata.module.args = *(const LfArgs *)args;
            _lf_senddata.module.modres = LF_ARG_MAX;
        } else {
            memcpy(_lf_senddata.module.args, args, arglen);
            _lf_senddata.module.modres = arglen;
        }
    } else {
        _lf_senddata.module.modres = 0;
    }
    if (sceSifCallRpc(&_lf_cd, LF_LOAD_MODULE_BUFFER, 0, &_lf_senddata, sizeof(LfModuleRequest), &_lf_senddata, 8, 0, 0) < 0) {
        return LF_ERR_RPC;
    }
    result = _lf_senddata.module.result;
    *modres = _lf_senddata.module.modres;
    return result;
}

int sceSifStopModule(int modid, int arglen, const char *args, int *modres)
{
    int result;
    if (_lf_bind() < 0) {
        return LF_ERR_BIND;
    }
    if (_lf_version() != 0) {
        return LF_ERR_VERSION;
    }
    _lf_senddata.module.result = modid;
    if (args != 0) {
        if (arglen > LF_ARG_MAX) {
            *(LfArgs *)_lf_senddata.module.args = *(const LfArgs *)args;
            _lf_senddata.module.modres = LF_ARG_MAX;
        } else {
            memcpy(_lf_senddata.module.args, args, arglen);
            _lf_senddata.module.modres = arglen;
        }
    } else {
        _lf_senddata.module.modres = 0;
    }
    if (sceSifCallRpc(&_lf_cd, LF_STOP_MODULE, 0, &_lf_senddata, sizeof(LfModuleRequest), &_lf_senddata, 8, 0, 0) < 0) {
        return LF_ERR_RPC;
    }
    result = _lf_senddata.module.result;
    *modres = _lf_senddata.module.modres;
    return result;
}

int sceSifUnloadModule(int modid)
{
    if (_lf_bind() < 0) {
        return LF_ERR_BIND;
    }
    if (_lf_version() != 0) {
        return LF_ERR_VERSION;
    }
    _lf_senddata.module.result = modid;
    if (sceSifCallRpc(&_lf_cd, LF_UNLOAD_MODULE, 0, &_lf_senddata, 4, &_lf_senddata, 4, 0, 0) < 0) {
        return LF_ERR_RPC;
    }
    return _lf_senddata.module.result;
}

int sceSifSearchModuleByName(const char *name)
{
    if (_lf_bind() < 0) {
        return LF_ERR_BIND;
    }
    if (_lf_version() != 0) {
        return LF_ERR_VERSION;
    }
    strncpy(_lf_senddata.module.path, name, LF_PATH_MAX);
    _lf_senddata.module.path[LF_PATH_MAX - 1] = 0;
    if (sceSifCallRpc(&_lf_cd, LF_SEARCH_MODULE_BY_NAME, 0, &_lf_senddata, sizeof(LfModuleRequest), &_lf_senddata, 4, 0, 0) < 0) {
        return LF_ERR_RPC;
    }
    return _lf_senddata.module.result;
}

int sceSifSearchModuleByAddress(const void *addr)
{
    if (_lf_bind() < 0) {
        return LF_ERR_BIND;
    }
    if (_lf_version() != 0) {
        return LF_ERR_VERSION;
    }
    _lf_senddata.module.result = (int)addr;
    if (sceSifCallRpc(&_lf_cd, LF_SEARCH_MODULE_BY_ADDRESS, 0, &_lf_senddata, 4, &_lf_senddata, 4, 0, 0) < 0) {
        return LF_ERR_RPC;
    }
    return _lf_senddata.module.result;
}

int sceSifLoadModuleBuffer(void *addr, int arglen, const char *args)
{
    int modres;
    return _sceSifLoadModuleBuffer(addr, arglen, args, &modres);
}

int sceSifLoadStartModuleBuffer(void *addr, int arglen, const char *args, int *modres)
{
    return _sceSifLoadModuleBuffer(addr, arglen, args, modres);
}

int _sceSifLoadModule(const char *path, int arglen, const char *args, int *modres, int cmd)
{
    int result;
    if (_lf_bind() < 0) {
        return LF_ERR_BIND;
    }
    if (_lf_version() != 0) {
        return LF_ERR_VERSION;
    }
    strncpy(_lf_senddata.module.path, path, LF_PATH_MAX);
    _lf_senddata.module.path[LF_PATH_MAX - 1] = 0;
    if (args != 0) {
        if (arglen > LF_ARG_MAX) {
            *(LfArgs *)_lf_senddata.module.args = *(const LfArgs *)args;
            _lf_senddata.module.result = LF_ARG_MAX;
        } else {
            memcpy(_lf_senddata.module.args, args, arglen);
            _lf_senddata.module.result = arglen;
        }
    } else {
        _lf_senddata.module.args[0] = 0;
        _lf_senddata.module.result = 0;
    }
    if (sceSifCallRpc(&_lf_cd, cmd, 0, &_lf_senddata, sizeof(LfModuleRequest), &_lf_senddata, 8, 0, 0) < 0) {
        return LF_ERR_RPC;
    }
    result = _lf_senddata.module.result;
    *modres = _lf_senddata.module.modres;
    return result;
}

int sceSifLoadModule(const char *path, int arglen, const char *args)
{
    int modres;
    return _sceSifLoadModule(path, arglen, args, &modres, LF_LOAD_MODULE);
}

int sceSifLoadStartModule(const char *path, int arglen, const char *args, int *modres)
{
    return _sceSifLoadModule(path, arglen, args, modres, LF_LOAD_MODULE);
}

/* the ELF's entry point and gp */
typedef struct {
    int epc;
    int gp;
} LfElfData;

int _sceSifLoadElfPart(const char *path, const char *section, LfElfData *data, int cmd)
{
    if (_lf_bind() < 0) {
        return LF_ERR_BIND;
    }
    if (_lf_version() != 0) {
        return LF_ERR_VERSION;
    }
    strncpy(_lf_senddata.module.path, path, LF_PATH_MAX);
    _lf_senddata.module.path[LF_PATH_MAX - 1] = 0;
    strncpy(_lf_senddata.module.args, section, LF_ARG_MAX);
    _lf_senddata.module.args[LF_ARG_MAX - 1] = 0;
    if (sceSifCallRpc(&_lf_cd, cmd, 0, &_lf_senddata, sizeof(LfModuleRequest), &_lf_senddata, 16, 0, 0) < 0) {
        return LF_ERR_RPC;
    }
    if (_lf_senddata.module.result == 0) {
        return LF_ERR_LOAD;
    }
    data->epc = _lf_senddata.module.result;
    data->gp = _lf_senddata.module.modres;
    return 0;
}

int sceSifLoadElfPart(const char *path, const char *section, LfElfData *data)
{
    return _sceSifLoadElfPart(path, section, data, LF_LOAD_ELF);
}

int sceSifLoadElf(const char *path, LfElfData *data)
{
    return _sceSifLoadElfPart(path, "all", data, LF_LOAD_ELF);
}

int sceSifGetIopAddr(unsigned int addr, void *value, unsigned int type)
{
    if (_lf_bind() < 0) {
        return LF_ERR_BIND;
    }
    if (type >= 3) {
        return LF_ERR_TYPE;
    }
    _lf_senddata.addr.addr.w = addr;
    _lf_senddata.addr.type = type;
    if (sceSifCallRpc(&_lf_cd, LF_GET_ADDR, 0, &_lf_senddata, sizeof(LfAddrRequest), &_lf_senddata, sizeof(LfAddrRequest), 0, 0) < 0) {
        return LF_ERR_RPC;
    }
    if (type == 0) {
        *(unsigned char *)value = _lf_senddata.addr.addr.b;
    } else if (type == 1) {
        *(unsigned short *)value = _lf_senddata.addr.addr.h;
    } else if (type == 2) {
        *(unsigned int *)value = _lf_senddata.addr.addr.w;
    } else {
        return LF_ERR_TYPE;
    }
    return 0;
}

int sceSifSetIopAddr(unsigned int addr, void *value, int type)
{
    if (_lf_bind() < 0) {
        return LF_ERR_BIND;
    }
    _lf_senddata.addr.addr.w = addr;
    _lf_senddata.addr.type = type;
    if (type == 0) {
        _lf_senddata.addr.value.b = *(unsigned char *)value;
    } else if (type == 1) {
        _lf_senddata.addr.value.h = *(unsigned short *)value;
    } else if (type == 2) {
        _lf_senddata.addr.value.w = *(unsigned int *)value;
    } else {
        return LF_ERR_TYPE;
    }
    if (sceSifCallRpc(&_lf_cd, LF_SET_ADDR, 0, &_lf_senddata, sizeof(LfAddrRequest), &_lf_senddata, 16, 0, 0) < 0) {
        return LF_ERR_RPC;
    }
    return 0;
}
