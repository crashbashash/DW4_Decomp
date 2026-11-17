/* libmc.h - libmc's EE side (Sony libmc.h): the memory card calls, each an RPC to mcserv, and the
 * directory record sceMcGetDir fills. */
#ifndef DW4_SONY_LIBMC_H
#define DW4_SONY_LIBMC_H

typedef struct sceMcStDateTime {
    unsigned char Resv2;
    unsigned char Sec;
    unsigned char Min;
    unsigned char Hour;
    unsigned char Day;
    unsigned char Month;
    unsigned short Year;
} sceMcStDateTime;

typedef struct sceMcTblGetDir {
    sceMcStDateTime _Create;
    sceMcStDateTime _Modify;
    unsigned int FileSizeByte;
    unsigned short AttrFile;
    unsigned short Reserve1;
    unsigned int Reserve2;
    unsigned int PdaAplNo;
    unsigned char EntryName[32];
} sceMcTblGetDir;

#ifdef __cplusplus
extern "C" {
#endif

int sceMcInit(void);
int sceMcEnd(void);
int sceMcChangeThreadPriority(int priority);
int sceMcGetSlotMax(int port);
int sceMcOpen(int port, int slot, char *name, int mode);
int sceMcMkdir(int port, int slot, char *name);
int sceMcClose(int fd);
int sceMcSeek(int fd, int offset, int origin);
int sceMcRead(int fd, void *buffer, int size);
int sceMcWrite(int fd, void *buffer, int size);
int sceMcSync(int mode, int *cmd, int *result);
int sceMcGetInfo(int port, int slot, int *type, int *free, int *format);
int sceMcUdCheckNewCard(void);
int sceMcGetDir(int port, int slot, char *name, int mode, int maxent, sceMcTblGetDir *table);
int sceMcChdir(int port, int slot, char *name, char *dir);
int sceMcFormat(int port, int slot);
int sceMcDelete(int port, int slot, char *name);
int sceMcFlush(int fd);
int sceMcSetFileInfo(int port, int slot, char *name, sceMcTblGetDir *info, unsigned int flags);
int sceMcRename(int port, int slot, char *name, char *newname);
int sceMcUnformat(int port, int slot);
int sceMcGetEntSpace(int port, int slot, char *name);

#ifdef __cplusplus
}
#endif

#endif
