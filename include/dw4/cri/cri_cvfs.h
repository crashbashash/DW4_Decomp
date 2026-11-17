/* CRI cvFs: the file-system layer that routes ADX file access to registered devices. */
#ifndef DW4_CRI_CVFS_H
#define DW4_CRI_CVFS_H

#ifdef __cplusplus
extern "C" {
#endif

#define CVFS_MAX_HANDLES 40
#define CVFS_MAX_DEVICES 32
#define CVFS_DEV_NAME_SIZE 12
#define CVFS_DEF_DEV_SIZE 9
#define CVFS_PATH_SIZE 304

#define CVFS_STAT_ERROR 3

/* Requests a device answers through its opt_fn1 slot. */
enum CvFsOptCode {
    CVFS_OPT_SET_CUR_VOLUME = 1,
    CVFS_OPT_ADD_VOLUME = 2,
    CVFS_OPT_DEL_VOLUME = 3,
    CVFS_OPT_GET_NUM_FILES = 4,
    CVFS_OPT_GET_VOLUME_INFO = 5,
    CVFS_OPT_SET_DEF_VOL = 6,
    CVFS_OPT_IS_FULL_PATH = 100,
    CVFS_OPT_NUM_TR64_HIGH = 200,
    CVFS_OPT_NUM_TR64_LOW = 201,
    CVFS_OPT_FILE_SIZE64_HIGH = 202,
    CVFS_OPT_FILE_SIZE64_LOW = 203,
    CVFS_OPT_FILE_SIZE_EX64_HIGH = 204,
    CVFS_OPT_FILE_SIZE_EX64_LOW = 205,
    CVFS_OPT_FSYS64_INFO = 299,
    CVFS_OPT_FILE_SIZE_BY_HNDL = 300
};

typedef void (*CvFsErrFn)(void *obj, const char *msg, int code);

/* The slot types of a device's interface table. A device file handle travels as an int (CvFsHandle.fd);
 * a device whose functions take its own handle or callback type converts them to these types. */
typedef void (*CvFsEntryErrFuncFn)(CvFsErrFn func, void *obj);
typedef int (*CvFsPathFn)(const char *path);
typedef int (*CvFsGetFreeSizeFn)(void);
typedef int (*CvFsOpenFn)(const char *fname, void *atr, int rw);
typedef void (*CvFsFdFn)(int fd);
typedef int (*CvFsFdIntFn)(int fd);
typedef int (*CvFsSeekFn)(int fd, int offset, int origin);
typedef int (*CvFsXferFn)(int fd, int nsct, void *buf);
typedef void (*CvFsSetSctLenFn)(int fd, int len);
typedef int (*CvFsGetNumFilesFn)(void);
typedef int (*CvFsLoadDirInfoFn)(const char *path, void *work, int nfile);
typedef int (*CvFsGetFileSizeExFn)(const char *path, int arg);
typedef int (*CvFsOptFn2)(int fd, int code, int arg);

/* A device's interface table. */
typedef struct CvFsVtbl {
    void (*exec_server)(void);
    CvFsEntryErrFuncFn entry_err_func;
    CvFsPathFn get_file_size;
    CvFsGetFreeSizeFn get_free_size;
    CvFsOpenFn open;
    CvFsFdFn close;
    CvFsSeekFn seek;
    CvFsFdIntFn tell;
    CvFsXferFn req_rd;
    CvFsXferFn req_wr;
    CvFsFdFn stop_tr;
    CvFsFdIntFn get_stat;
    CvFsFdIntFn get_sct_len;
    CvFsSetSctLenFn set_sct_len;
    CvFsFdIntFn get_num_tr;
    CvFsPathFn change_dir;
    CvFsPathFn is_exist_file;
    CvFsGetNumFilesFn get_num_files;
    CvFsLoadDirInfoFn load_dir_info;
    CvFsFdIntFn get_max_byte_rate;
    CvFsPathFn make_dir;
    CvFsPathFn remove_dir;
    CvFsPathFn delete_file;
    CvFsGetFileSizeExFn get_file_size_ex;
    /* The request entry: its first argument is a handle, a CvFsOptPrm or a path depending on the
     * code, so it has no prototype (as in CRI's SDK). */
    int (*opt_fn1)();
    CvFsOptFn2 opt_fn2;
} CvFsVtbl;

typedef struct CvFsHandle {
    CvFsVtbl *vtbl;
    int fd;
} CvFsHandle;

typedef struct CvFsDevice {
    CvFsVtbl *vtbl;
    char name[CVFS_DEV_NAME_SIZE];
} CvFsDevice;

/* The block the volume requests pass to opt_fn1 (CRI's CVS_FS_OPTPRM): image handle, volume name,
 * option. */
typedef struct CvFsOptPrm {
    void *prm[5];
} CvFsOptPrm;

extern CvFsErrFn cvfs_errfn;
extern void *cvfs_errobj;
extern int cvfs_init_cnt;
extern CvFsHandle cvfs_handles[CVFS_MAX_HANDLES];
extern CvFsDevice cvfs_devices[CVFS_MAX_DEVICES];
extern char cvfs_defdev[CVFS_DEF_DEV_SIZE];
extern char cvfs_path_work[];

void cvFsCallUsrErrFn(void *obj, const char *msg, int code);
void cvFsError(const char *msg);
void cvFsInit(void);
void cvFsFinish(void);
void cvFsAddDev(char *devname, CvFsVtbl *(*get_if)(void), void *prm);
CvFsVtbl *addDevice(char *devname, CvFsVtbl *(*get_if)(void));
CvFsVtbl *getDevice(const char *devname);
void toUpperStr(char *str);
void cvFsDelDev(const char *devname);
void cvFsSetDefDev(char *devname);
int isExistDev(const char *devname, int len);
char *cvFsGetDefDev(void);
CvFsVtbl *variousProc(char *devname, char *fname, const char *path);
CvFsHandle *cvFsOpen(const char *path, void *atr, int rw);
CvFsHandle *allocCvFsHn(void);
void releaseCvFsHn(CvFsHandle *hdl);
void getDevName(char *devname, char *fname, const char *path);
void getDefDev(char *devname);
void cvFsClose(CvFsHandle *hdl);
int cvFsTell(CvFsHandle *hdl);
int cvFsSeek(CvFsHandle *hdl, int offset, int origin);
int cvFsReqRd(CvFsHandle *hdl, int nsct, void *buf);
int cvFsReqWr(CvFsHandle *hdl, int nsct, void *buf);
void cvFsStopTr(CvFsHandle *hdl);
void cvFsExecServer(void);
int cvFsGetStat(CvFsHandle *hdl);
int cvFsGetFileSize(const char *path);
int cvFsGetFileSizeEx(const char *path, int arg);
int cvFsGetFileSizeByHndl(CvFsHandle *hdl);
int cvFsGetFreeSize(const char *devname);
int cvFsGetSctLen(CvFsHandle *hdl);
void cvFsSetSctLen(CvFsHandle *hdl, int len);
int cvFsGetNumTr(CvFsHandle *hdl);
int cvFsChangeDir(const char *path);
int cvFsIsExistFile(const char *path);
int cvFsGetNumFiles(const char *devname);
int cvFsLoadDirInfo(const char *path, void *work, int nfile);
int cvFsGetMaxByteRate(CvFsHandle *hdl);
int cvFsMakeDir(const char *path);
int cvFsRemoveDir(const char *path);
int cvFsDeleteFile(const char *path);
char *cvFsGetDevName(CvFsHandle *hdl);
void cvFsEntryErrFunc(CvFsErrFn func, void *obj);
int cvFsOptFn1(CvFsHandle *hdl, int code, int arg);
int cvFsOptFn2(CvFsHandle *hdl, int code, int arg);
int cvFsSetCurVolume(const char *devname, void *image);
int cvFsAddVolumeEx(const char *devname, const char *volume, void *image, int option);
int cvFsDelVolume(const char *devname, const char *volume);
int cvFsGetVolumeInfo(const char *devname, const char *volume, void *info);
void cvFsSetDefVol(const char *devname, const char *volume);
int isNeedDevName(const char *devname);
void addDevName(char *devname, char *fname);
int cvFsIsExistDevice(const char *devname);
long long cvFsGetNumTr64(CvFsHandle *hdl);
long long cvFsGetFileSize64(const char *path);
long long cvFsGetFileSizeEx64(const char *path, int arg);
int cvFsGetFsys64Info(CvFsHandle *hdl);

#ifdef __cplusplus
}
#endif

#endif
