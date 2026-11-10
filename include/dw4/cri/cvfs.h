/* CRI cvFs: the file-system layer that routes ADX file access to registered devices. */
#ifndef DW4_CRI_CVFS_H
#define DW4_CRI_CVFS_H

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

/* A device's interface table. Each slot holds a function address as an int; a caller casts the
 * slot to the function type it calls. */
typedef struct CvFsVtbl {
    int exec_server;
    int entry_err_func;
    int get_file_size;
    int get_free_size;
    int open;
    int close;
    int seek;
    int tell;
    int req_rd;
    int req_wr;
    int stop_tr;
    int get_stat;
    int get_sct_len;
    int set_sct_len;
    int get_num_tr;
    int change_dir;
    int is_exist_file;
    int get_num_files;
    int load_dir_info;
    int get_max_byte_rate;
    int make_dir;
    int remove_dir;
    int delete_file;
    int get_file_size_ex;
    int opt_fn1;
    int opt_fn2;
} CvFsVtbl;

typedef struct CvFsHandle {
    CvFsVtbl *vtbl;
    int fd;
} CvFsHandle;

typedef struct CvFsDevice {
    CvFsVtbl *vtbl;
    char name[CVFS_DEV_NAME_SIZE];
} CvFsDevice;

/* The block the volume requests pass to opt_fn1. Its fields are ints like the vtbl slots; a caller
 * casts the pointer it stores. */
typedef struct CvFsVolumeArg {
    int image;
    int volume;
    int option;
    int pad12[2];
} CvFsVolumeArg;

typedef void (*CvFsErrFn)(void *obj, const char *msg, int code);

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
void cvFsAddDev(char *devname, CvFsVtbl *(*get_if)(void));
CvFsVtbl *addDevice(char *devname, CvFsVtbl *(*get_if)(void));
CvFsVtbl *getDevice(const char *devname);
void toUpperStr(char *str);
void cvFsDelDev(const char *devname);
void cvFsSetDefDev(char *devname);
int isExistDevName(const char *devname, int len);
char *cvFsGetDefDev(void);
CvFsVtbl *getPathDevice(char *devname, char *fname, const char *path);
CvFsHandle *cvFsOpen(const char *path, void *atr, int rw);
CvFsHandle *allocCvFsHdl(void);
void releaseCvFsHdl(CvFsHandle *hdl);
void splitPath(char *devname, char *fname, const char *path);
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
int isFullPathDev(const char *devname);
void makeFullPath(char *devname, char *fname);
int cvFsIsExistDev(const char *devname);
long long cvFsGetNumTr64(CvFsHandle *hdl);
long long cvFsGetFileSize64(const char *path);
long long cvFsGetFileSizeEx64(const char *path, int arg);
int cvFsGetFsys64Info(CvFsHandle *hdl);

#endif
