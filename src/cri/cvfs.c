#include "dw4/cri/cvfs.h"

unsigned int strlen(const char *s);
int strncmp(const char *a, const char *b, unsigned int n);
char *strcpy(char *dst, const char *src);
void *memcpy(void *dst, const void *src, unsigned int n);
void *memset(void *dst, int value, unsigned int n);
int sprintf(char *dst, const char *format, ...);

extern char cvFsAddDev_1_illegal_device_name[];
extern char cvFsAddDev_2_illegal_I_F_func_name[];
extern char cvFsAddDev_3_failed_added_a_device[];
extern char cvFsDelDev_1_illegal_device_name[];
extern char cvFsSetDefDev_1_illegal_device_name[];
extern char cvFsSetDefDev_2_unknown_device_name[];
extern char cvFsOpen_1_illegal_file_name[];
extern char cvFsOpen_3_failed_handle_alloced[];
extern char cvFsOpen_4_device_not_found[];
extern char cvFsOpen_5_vtbl_error[];
extern char cvFsOpen_6_open_failed[];
extern char cvFsClose_1_handle_error[];
extern char cvFsClose_2_vtbl_error[];
extern char cvFsTell_1_handle_error[];
extern char cvFsTell_2_vtbl_error[];
extern char cvFsSeek_1_handle_error[];
extern char cvFsSeek_2_vtbl_error[];
extern char cvFsReqRd_1_handle_error[];
extern char cvFsReqRd_2_vtbl_error[];
extern char cvFsReqWr_1_handle_error[];
extern char cvFsReqWr_2_vtbl_error[];
extern char cvFsStopTr_1_handle_error[];
extern char cvFsStopTr_2_vtbl_error[];
extern char cvFsGetStat_1_handle_error[];
extern char cvFsGetStat_2_vtbl_error[];
extern char cvFsGetFileSizeByHndl_1_illegal_file_handle[];
extern char cvFsGetSctLen_1_handle_error[];
extern char cvFsGetSctLen_2_vtbl_error[];
extern char cvFsSetSctLen_3_handle_error[];
extern char cvFsSetSctLen_4_vtbl_error[];
extern char cvFsGetNumTr_1_handle_error[];
extern char cvFsGetNumTr_2_vtbl_error[];
extern char cvFsIsExistFile_1_illegal_file_name[];
extern char cvFsIsExistFile_2_illegal_device_name[];
extern char cvFsIsExistFile_3_device_not_found[];
extern char cvFsIsExistFile_4_vtbl_error[];
extern char cvFsGetMaxByteRate_1_handle_error[];
extern char cvFsGetMaxByteRate_2_vtbl_error[];
extern char cvFsGetDevName_1_vtbl_error[];
extern char cvFsOptFn1_1_handle_error[];
extern char cvFsOptFn1_2_vtbl_error[];
extern char cvFsOptFn2_1_handle_error[];
extern char cvFsOptFn2_2_vtbl_error[];
extern char cvFsSetCurVolume_1_illegal_device_name[];
extern char cvFsSetCurVolume_2_illegal_image_handle[];
extern char cvFsSetCurVolume_3_device_not_found[];
extern char cvFsAddVolumeEx_1_illegal_device_name[];
extern char cvFsAddVolumeEx_2_illegal_volume_name[];
extern char cvFsAddVolumeEx_3_illegal_image_handle[];
extern char cvFsAddVolumeEx_3_device_not_found[];
extern char cvFsDelVolume_1_illegal_device_name[];
extern char cvFsDelVolume_2_illegal_volume_name[];
extern char cvFsDelVolume_3_device_not_found[];
extern char cvFsGetVolumeInfo_1_illegal_device_name[];
extern char cvFsGetVolumeInfo_2_illegal_volume_name[];
extern char cvFsGetVolumeInfo_3_device_not_found[];
extern char cvFsSetDefVol_1_illegal_device_name[];
extern char cvFsSetDefVol_2_illegal_volume_name[];
extern char cvFsSetDefVol_3_device_not_found[];
extern char percent_s_colon_percent_s[];
extern char cvFsGetNumTr64_1_handle_error[];
extern char cvFsGetFsys64Info_1_handle_error[];

void cvFsCallUsrErrFn(void *obj, const char *msg, int code)
{
    if (cvfs_errfn != 0) {
        cvfs_errfn(cvfs_errobj, msg, code);
    }
}

void cvFsError(const char *msg)
{
    cvFsCallUsrErrFn(&cvfs_errobj, msg, 0);
}

void cvFsFinish(void)
{
    int i;

    if (--cvfs_init_cnt != 0) {
        return;
    }
    for (i = 0; i < CVFS_MAX_HANDLES; i++) {
        if (cvfs_handles[i].vtbl != 0) {
            ((void (*)(int))cvfs_handles[i].vtbl->close)(cvfs_handles[i].fd);
        }
        cvfs_handles[i].vtbl = 0;
        cvfs_handles[i].fd = 0;
    }
    for (i = CVFS_MAX_DEVICES - 1; i >= 0; i--) {
        cvfs_devices[i].name[0] = 0;
    }
    memset(cvfs_defdev, 0, sizeof(cvfs_defdev));
    cvfs_defdev[0] = 0;
}

void cvFsAddDev(char *devname, CvFsVtbl *(*get_if)(void))
{
    extern char *volatile cvfs_build;
    CvFsVtbl *vtbl;

    /* The discarded read keeps the build string in the link. */
    (void)cvfs_build;
    if (devname == 0) {
        cvFsError(cvFsAddDev_1_illegal_device_name);
        return;
    }
    if (get_if == 0) {
        cvFsError(cvFsAddDev_2_illegal_I_F_func_name);
        return;
    }
    vtbl = addDevice(devname, get_if);
    if (vtbl == 0) {
        cvFsError(cvFsAddDev_3_failed_added_a_device);
        return;
    }
    if (vtbl->entry_err_func != 0) {
        ((void (*)(CvFsErrFn, void *))vtbl->entry_err_func)(cvFsCallUsrErrFn, 0);
    }
}

CvFsVtbl *addDevice(char *devname, CvFsVtbl *(*get_if)(void))
{
    CvFsVtbl *vtbl;
    int i;

    toUpperStr(devname);
    vtbl = get_if();
    i = 0;
    if (getDevice(devname) != 0) {
        return vtbl;
    }
    for (; i < CVFS_MAX_DEVICES; i++) {
        if (cvfs_devices[i].name[0] == 0) {
            break;
        }
    }
    if (i == CVFS_MAX_DEVICES) {
        return 0;
    }
    cvfs_devices[i].vtbl = vtbl;
    memcpy(cvfs_devices[i].name, devname, strlen(devname) + 1);
    return vtbl;
}

CvFsVtbl *getDevice(const char *devname)
{
    unsigned int len;
    unsigned int i;

    len = strlen(devname);
    for (i = 0; i < CVFS_MAX_DEVICES; i++) {
        if (strncmp(devname, cvfs_devices[i].name, len) == 0) {
            return cvfs_devices[i].vtbl;
        }
    }
    return 0;
}

void cvFsDelDev(const char *devname)
{
    unsigned int len;
    unsigned int i;

    if (devname == 0) {
        cvFsError(cvFsDelDev_1_illegal_device_name);
        return;
    }
    len = strlen(devname);
    for (i = 0; i < CVFS_MAX_DEVICES; i++) {
        if (strncmp(devname, cvfs_devices[i].name, len) == 0) {
            cvfs_devices[i].name[0] = 0;
            return;
        }
    }
}

void cvFsSetDefDev(char *devname)
{
    int len;

    if (devname == 0) {
        cvFsError(cvFsSetDefDev_1_illegal_device_name);
        return;
    }
    len = strlen(devname);
    if (len == 0) {
        cvfs_defdev[0] = 0;
        return;
    }
    toUpperStr(devname);
    if (isExistDevName(devname, len) == 1) {
        memcpy(cvfs_defdev, devname, len + 1);
        return;
    }
    cvFsError(cvFsSetDefDev_2_unknown_device_name);
}

int isExistDevName(const char *devname, int len)
{
    int i;

    for (i = 0; i < CVFS_MAX_DEVICES; i++) {
        if (strncmp(devname, cvfs_devices[i].name, len) == 0) {
            return 1;
        }
    }
    return 0;
}

char *cvFsGetDefDev(void)
{
    return cvfs_defdev;
}

CvFsVtbl *getPathDevice(char *devname, char *fname, const char *path)
{
    CvFsVtbl *vtbl;

    if (devname[0] == 0) {
        getDefDev(devname);
        if (devname[0] == 0) {
            return 0;
        }
    }
    makeFullPath(devname, fname);
    vtbl = getDevice(devname);
    if (vtbl == 0) {
        getDefDev(devname);
        vtbl = getDevice(devname);
        if (vtbl == 0) {
            return 0;
        }
        strcpy(fname, path);
    }
    return vtbl;
}

CvFsHandle *cvFsOpen(const char *path, void *atr, int rw)
{
    char devname[CVFS_PATH_SIZE];
    char fname[CVFS_PATH_SIZE];
    CvFsHandle *hdl;
    CvFsVtbl *vtbl;

    if (path == 0) {
        cvFsError(cvFsOpen_1_illegal_file_name);
        return 0;
    }
    splitPath(devname, fname, path);
    if (fname[0] == 0) {
        cvFsError(cvFsOpen_1_illegal_file_name);
        return 0;
    }
    hdl = allocCvFsHdl();
    if (hdl == 0) {
        cvFsError(cvFsOpen_3_failed_handle_alloced);
        return 0;
    }
    vtbl = getPathDevice(devname, fname, path);
    hdl->vtbl = vtbl;
    if (vtbl == 0) {
        releaseCvFsHdl(hdl);
        cvFsError(cvFsOpen_4_device_not_found);
        return 0;
    }
    if (vtbl->open != 0) {
        hdl->fd = ((int (*)(const char *, void *, int))vtbl->open)(fname, atr, rw);
    } else {
        releaseCvFsHdl(hdl);
        cvFsError(cvFsOpen_5_vtbl_error);
        return 0;
    }
    if (hdl->fd == 0) {
        releaseCvFsHdl(hdl);
        cvFsError(cvFsOpen_6_open_failed);
        return 0;
    }
    return hdl;
}

CvFsHandle *allocCvFsHdl(void)
{
    int i;

    for (i = 0; i < CVFS_MAX_HANDLES; i++) {
        if (cvfs_handles[i].fd == 0) {
            break;
        }
    }
    if (i == CVFS_MAX_HANDLES) {
        return 0;
    }
    return &cvfs_handles[i];
}

void releaseCvFsHdl(CvFsHandle *hdl)
{
    /* matching construct: variant search — fd is cleared before vtbl, the retail store order */
    hdl->fd = 0;
    hdl->vtbl = 0;
}

void getDefDev(char *devname)
{
    unsigned int len = strlen(cvfs_defdev);

    if (cvfs_defdev[0] == 0) {
        devname[0] = 0;
        return;
    }
    memcpy(devname, cvfs_defdev, len + 1);
}

void cvFsClose(CvFsHandle *hdl)
{
    if (hdl == 0) {
        cvFsError(cvFsClose_1_handle_error);
        return;
    }
    if (hdl->vtbl->close != 0) {
        ((void (*)(int))hdl->vtbl->close)(hdl->fd);
        releaseCvFsHdl(hdl);
        return;
    }
    cvFsError(cvFsClose_2_vtbl_error);
}

int cvFsTell(CvFsHandle *hdl)
{
    int pos;

    if (hdl == 0) {
        cvFsError(cvFsTell_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->tell != 0) {
        pos = ((int (*)(int))hdl->vtbl->tell)(hdl->fd);
    } else {
        pos = 0;
        cvFsError(cvFsTell_2_vtbl_error);
    }
    return pos;
}

int cvFsSeek(CvFsHandle *hdl, int offset, int origin)
{
    int pos;

    if (hdl == 0) {
        cvFsError(cvFsSeek_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->seek != 0) {
        pos = ((int (*)(int, int, int))hdl->vtbl->seek)(hdl->fd, offset, origin);
    } else {
        pos = 0;
        cvFsError(cvFsSeek_2_vtbl_error);
    }
    return pos;
}

int cvFsReqRd(CvFsHandle *hdl, int nsct, void *buf)
{
    int nreq;

    if (hdl == 0) {
        cvFsError(cvFsReqRd_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->req_rd != 0) {
        nreq = ((int (*)(int, int, void *))hdl->vtbl->req_rd)(hdl->fd, nsct, buf);
    } else {
        nreq = 0;
        cvFsError(cvFsReqRd_2_vtbl_error);
    }
    return nreq;
}

int cvFsReqWr(CvFsHandle *hdl, int nsct, void *buf)
{
    int nreq = 0;

    if (hdl == 0) {
        cvFsError(cvFsReqWr_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->req_wr != 0) {
        nreq = ((int (*)(int, int, void *))hdl->vtbl->req_wr)(hdl->fd, nsct, buf);
    } else {
        cvFsError(cvFsReqWr_2_vtbl_error);
    }
    return nreq;
}

void cvFsStopTr(CvFsHandle *hdl)
{
    if (hdl == 0) {
        cvFsError(cvFsStopTr_1_handle_error);
        return;
    }
    if (hdl->vtbl->stop_tr != 0) {
        ((void (*)(int))hdl->vtbl->stop_tr)(hdl->fd);
        return;
    }
    cvFsError(cvFsStopTr_2_vtbl_error);
}

void cvFsExecServer(void)
{
    int i;

    for (i = 0; i < CVFS_MAX_DEVICES; i++) {
        if (cvfs_devices[i].vtbl != 0 && cvfs_devices[i].vtbl->exec_server != 0) {
            ((void (*)(void))cvfs_devices[i].vtbl->exec_server)();
        }
    }
}

int cvFsGetStat(CvFsHandle *hdl)
{
    int stat = CVFS_STAT_ERROR;

    if (hdl == 0) {
        cvFsError(cvFsGetStat_1_handle_error);
        return CVFS_STAT_ERROR;
    }
    if (hdl->vtbl->get_stat != 0) {
        stat = ((int (*)(int))hdl->vtbl->get_stat)(hdl->fd);
    } else {
        cvFsError(cvFsGetStat_2_vtbl_error);
    }
    return stat;
}

int cvFsGetFileSizeByHndl(CvFsHandle *hdl)
{
    int size;

    if (hdl == 0) {
        cvFsError(cvFsGetFileSizeByHndl_1_illegal_file_handle);
        return -1;
    }
    size = 0x7FFFFFFF;
    if (hdl->vtbl->opt_fn1 != 0) {
        size = ((int (*)(int, int, int, int))hdl->vtbl->opt_fn1)(hdl->fd, CVFS_OPT_FILE_SIZE_BY_HNDL, 0, 0);
    }
    return size;
}

int cvFsGetSctLen(CvFsHandle *hdl)
{
    int len = 0;

    if (hdl == 0) {
        cvFsError(cvFsGetSctLen_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->get_sct_len != 0) {
        len = ((int (*)(int))hdl->vtbl->get_sct_len)(hdl->fd);
    } else {
        cvFsError(cvFsGetSctLen_2_vtbl_error);
    }
    return len;
}

void cvFsSetSctLen(CvFsHandle *hdl, int len)
{
    if (hdl == 0) {
        cvFsError(cvFsSetSctLen_3_handle_error);
        return;
    }
    if (hdl->vtbl->set_sct_len != 0) {
        ((void (*)(int, int))hdl->vtbl->set_sct_len)(hdl->fd, len);
        return;
    }
    cvFsError(cvFsSetSctLen_4_vtbl_error);
}

int cvFsGetNumTr(CvFsHandle *hdl)
{
    int ntr = 0;

    if (hdl == 0) {
        cvFsError(cvFsGetNumTr_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->get_num_tr != 0) {
        ntr = ((int (*)(int))hdl->vtbl->get_num_tr)(hdl->fd);
    } else {
        cvFsError(cvFsGetNumTr_2_vtbl_error);
    }
    return ntr;
}

int cvFsIsExistFile(const char *path)
{
    char devname[CVFS_PATH_SIZE];
    char fname[CVFS_PATH_SIZE];
    CvFsVtbl *vtbl;

    splitPath(devname, fname, path);
    if (fname[0] == 0) {
        cvFsError(cvFsIsExistFile_1_illegal_file_name);
        return 0;
    }
    vtbl = getPathDevice(devname, fname, path);
    if (vtbl == 0) {
        /* Retail reports the miss and still reads the table. */
        cvFsError(cvFsIsExistFile_3_device_not_found);
    }
    if (vtbl->is_exist_file != 0) {
        return ((int (*)(const char *))vtbl->is_exist_file)(fname);
    }
    cvFsError(cvFsIsExistFile_4_vtbl_error);
    return 0;
}

int cvFsGetNumFiles(const char *devname)
{
    CvFsVolumeArg arg;
    CvFsVtbl *vtbl;
    unsigned int len;
    int nfile;
    int i;

    nfile = 0;
    len = strlen(devname);
    for (i = 0; i < CVFS_MAX_DEVICES; i++) {
        if (strncmp(devname, cvfs_devices[i].name, len) != 0) {
            continue;
        }
        vtbl = cvfs_devices[i].vtbl;
        if (isFullPathDev(devname) != 0) {
            if (vtbl != 0 && vtbl->opt_fn1 != 0) {
                arg.volume = (int)devname;
                nfile = ((int (*)(CvFsVolumeArg *, int, int, int))vtbl->opt_fn1)(&arg, CVFS_OPT_GET_NUM_FILES, 0, 0);
                break;
            }
        } else {
            if (vtbl != 0 && vtbl->get_num_files != 0) {
                nfile = ((int (*)(void))vtbl->get_num_files)();
                break;
            }
        }
    }
    return nfile;
}

int cvFsLoadDirInfo(const char *path, void *work, int nfile)
{
    char devname[CVFS_PATH_SIZE];
    char fname[CVFS_PATH_SIZE];
    CvFsVtbl *vtbl;
    int nload;

    splitPath(devname, fname, path);
    nload = 0;
    if (devname[0] == 0) {
        getDefDev(devname);
        if (devname[0] == 0) {
            cvFsError(cvFsIsExistFile_2_illegal_device_name);
            return 0;
        }
    }
    makeFullPath(devname, fname);
    vtbl = getDevice(devname);
    if (vtbl != 0 && vtbl->load_dir_info != 0) {
        nload = ((int (*)(const char *, void *, int))vtbl->load_dir_info)(path, work, nfile);
    }
    return nload;
}

int cvFsGetMaxByteRate(CvFsHandle *hdl)
{
    if (hdl == 0) {
        cvFsError(cvFsGetMaxByteRate_1_handle_error);
    } else if (hdl->vtbl->get_max_byte_rate != 0) {
        return ((int (*)(int))hdl->vtbl->get_max_byte_rate)(hdl->fd);
    } else {
        cvFsError(cvFsGetMaxByteRate_2_vtbl_error);
    }
    return 0;
}

char *cvFsGetDevName(CvFsHandle *hdl)
{
    int i;

    if (hdl == 0) {
        cvFsError(cvFsGetDevName_1_vtbl_error);
        return 0;
    }
    for (i = 0; i < CVFS_MAX_DEVICES; i++) {
        if (cvfs_devices[i].vtbl == hdl->vtbl) {
            break;
        }
    }
    /* Retail does not check for a miss: it returns the name past the table. */
    return cvfs_devices[i].name;
}

void cvFsEntryErrFunc(CvFsErrFn func, void *obj)
{
    if (func == 0) {
        cvfs_errfn = 0;
        cvfs_errobj = 0;
        return;
    }
    cvfs_errfn = func;
    cvfs_errobj = obj;
}

int cvFsOptFn1(CvFsHandle *hdl, int code, int arg)
{
    int result = 0;

    if (hdl == 0) {
        cvFsError(cvFsOptFn1_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->opt_fn1 != 0) {
        result = ((int (*)(int, int, int))hdl->vtbl->opt_fn1)(hdl->fd, code, arg);
    } else {
        cvFsError(cvFsOptFn1_2_vtbl_error);
    }
    return result;
}

int cvFsOptFn2(CvFsHandle *hdl, int code, int arg)
{
    int result = 0;

    if (hdl == 0) {
        cvFsError(cvFsOptFn2_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->opt_fn2 != 0) {
        result = ((int (*)(int, int, int))hdl->vtbl->opt_fn2)(hdl->fd, code, arg);
    } else {
        cvFsError(cvFsOptFn2_2_vtbl_error);
    }
    return result;
}

int cvFsSetCurVolume(const char *devname, void *image)
{
    CvFsVolumeArg arg;
    CvFsVtbl *vtbl;

    if (devname == 0) {
        cvFsError(cvFsSetCurVolume_1_illegal_device_name);
        return -1;
    }
    if (image == 0) {
        cvFsError(cvFsSetCurVolume_2_illegal_image_handle);
        return -1;
    }
    vtbl = getDevice(devname);
    if (vtbl == 0) {
        cvFsError(cvFsSetCurVolume_3_device_not_found);
        return -1;
    }
    memset(&arg, 0, sizeof(arg));
    arg.image = (int)image;
    if (vtbl->opt_fn1 != 0) {
        return ((int (*)(CvFsVolumeArg *, int, int, int))vtbl->opt_fn1)(&arg, CVFS_OPT_SET_CUR_VOLUME, 0, 0);
    }
    return -1;
}

int cvFsAddVolumeEx(const char *devname, const char *volume, void *image, int option)
{
    CvFsVolumeArg arg;
    CvFsVtbl *vtbl;

    if (devname == 0) {
        cvFsError(cvFsAddVolumeEx_1_illegal_device_name);
        return -1;
    }
    if (volume == 0) {
        cvFsError(cvFsAddVolumeEx_2_illegal_volume_name);
        return -1;
    }
    if (image == 0) {
        cvFsError(cvFsAddVolumeEx_3_illegal_image_handle);
        return -1;
    }
    vtbl = getDevice(devname);
    if (vtbl == 0) {
        cvFsError(cvFsAddVolumeEx_3_device_not_found);
        return -1;
    }
    memset(&arg, 0, sizeof(arg));
    arg.image = (int)image;
    arg.volume = (int)volume;
    arg.option = option;
    if (vtbl->opt_fn1 != 0) {
        return ((int (*)(CvFsVolumeArg *, int, int, int))vtbl->opt_fn1)(&arg, CVFS_OPT_ADD_VOLUME, 0, 0);
    }
    return -1;
}

int cvFsDelVolume(const char *devname, const char *volume)
{
    CvFsVolumeArg arg;
    CvFsVtbl *vtbl;

    if (devname == 0) {
        cvFsError(cvFsDelVolume_1_illegal_device_name);
        return -1;
    }
    if (volume == 0) {
        cvFsError(cvFsDelVolume_2_illegal_volume_name);
        return -1;
    }
    vtbl = getDevice(devname);
    if (vtbl == 0) {
        cvFsError(cvFsDelVolume_3_device_not_found);
        return -1;
    }
    memset(&arg, 0, sizeof(arg));
    arg.volume = (int)volume;
    if (vtbl->opt_fn1 != 0) {
        return ((int (*)(CvFsVolumeArg *, int, int, int))vtbl->opt_fn1)(&arg, CVFS_OPT_DEL_VOLUME, 0, 0);
    }
    return -1;
}

int cvFsGetVolumeInfo(const char *devname, const char *volume, void *info)
{
    CvFsVolumeArg arg;
    CvFsVtbl *vtbl;

    if (devname == 0) {
        cvFsError(cvFsGetVolumeInfo_1_illegal_device_name);
        return -1;
    }
    if (volume == 0) {
        cvFsError(cvFsGetVolumeInfo_2_illegal_volume_name);
        return -1;
    }
    vtbl = getDevice(devname);
    if (vtbl == 0) {
        cvFsError(cvFsGetVolumeInfo_3_device_not_found);
        return -1;
    }
    memset(&arg, 0, sizeof(arg));
    arg.volume = (int)volume;
    arg.option = (int)info;
    if (vtbl->opt_fn1 != 0) {
        return ((int (*)(CvFsVolumeArg *, int, int, int))vtbl->opt_fn1)(&arg, CVFS_OPT_GET_VOLUME_INFO, 0, 0);
    }
    return -1;
}

void cvFsSetDefVol(const char *devname, const char *volume)
{
    CvFsVolumeArg arg;
    CvFsVtbl *vtbl;

    if (devname == 0) {
        cvFsError(cvFsSetDefVol_1_illegal_device_name);
        return;
    }
    if (volume == 0) {
        cvFsError(cvFsSetDefVol_2_illegal_volume_name);
        return;
    }
    vtbl = getDevice(devname);
    if (vtbl == 0) {
        cvFsError(cvFsSetDefVol_3_device_not_found);
        return;
    }
    memset(&arg, 0, sizeof(arg));
    arg.volume = (int)volume;
    if (vtbl->opt_fn1 != 0) {
        ((int (*)(CvFsVolumeArg *, int, int, int))vtbl->opt_fn1)(&arg, CVFS_OPT_SET_DEF_VOL, 0, 0);
    }
}

int isFullPathDev(const char *devname)
{
    CvFsVtbl *vtbl;

    vtbl = getDevice(devname);
    if (vtbl == 0) {
        return 0;
    }
    if (vtbl->opt_fn1 != 0) {
        return ((int (*)(int, int, int, int))vtbl->opt_fn1)(0, CVFS_OPT_IS_FULL_PATH, 0, 0);
    }
    return 0;
}

void makeFullPath(char *devname, char *fname)
{
    if (devname == 0) {
        devname = cvFsGetDefDev();
    }
    if (isFullPathDev(devname) == 1) {
        strcpy(cvfs_path_work, fname);
        sprintf(fname, percent_s_colon_percent_s, devname, cvfs_path_work);
    }
}

int cvFsIsExistDev(const char *devname)
{
    return getDevice(devname) != 0;
}

long long cvFsGetNumTr64(CvFsHandle *hdl)
{
    long long ntr = 0;

    if (hdl == 0) {
        cvFsError(cvFsGetNumTr64_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->opt_fn1 != 0) {
        ntr = ((long long)((int (*)(int, int, int, int))hdl->vtbl->opt_fn1)(hdl->fd, CVFS_OPT_NUM_TR64_HIGH, 0, 0) << 32)
            + (unsigned int)((int (*)(int, int, int, int))hdl->vtbl->opt_fn1)(hdl->fd, CVFS_OPT_NUM_TR64_LOW, 0, 0);
    }
    return ntr;
}

long long cvFsGetFileSize64(const char *path)
{
    char devname[CVFS_PATH_SIZE];
    char fname[CVFS_PATH_SIZE];
    CvFsVtbl *vtbl;
    long long size = 0;
    int high;

    splitPath(devname, fname, path);
    vtbl = getPathDevice(devname, fname, path);
    if (vtbl->opt_fn1 != 0) {
        high = ((int (*)(const char *, int, char *, int))vtbl->opt_fn1)(path, CVFS_OPT_FILE_SIZE64_HIGH, fname, 0);
        size = ((long long)high << 32)
             + (unsigned int)((int (*)(const char *, int, char *, int))vtbl->opt_fn1)(path, CVFS_OPT_FILE_SIZE64_LOW, fname, 0);
    }
    return size;
}

long long cvFsGetFileSizeEx64(const char *path, int arg)
{
    char devname[CVFS_PATH_SIZE];
    char fname[CVFS_PATH_SIZE];
    CvFsVtbl *vtbl;
    long long size;
    int high;

    /* Retail looks the device up before the path is split into devname. */
    vtbl = getDevice(devname);
    if (vtbl == 0) {
        return 0;
    }
    splitPath(devname, fname, path);
    size = 0;
    if (vtbl->opt_fn1 != 0) {
        high = ((int (*)(const char *, int, char *, int))vtbl->opt_fn1)(path, CVFS_OPT_FILE_SIZE_EX64_HIGH, fname, arg);
        size = ((long long)high << 32)
             + (unsigned int)((int (*)(const char *, int, char *, int))vtbl->opt_fn1)(path, CVFS_OPT_FILE_SIZE_EX64_LOW, fname, arg);
    }
    return size;
}

int cvFsGetFsys64Info(CvFsHandle *hdl)
{
    int result = 0;

    if (hdl == 0) {
        cvFsError(cvFsGetFsys64Info_1_handle_error);
        return 0;
    }
    if (hdl->vtbl->opt_fn1 != 0) {
        result = ((int (*)(int, int, int, int))hdl->vtbl->opt_fn1)(hdl->fd, CVFS_OPT_FSYS64_INFO, 0, 0);
    }
    return result;
}
