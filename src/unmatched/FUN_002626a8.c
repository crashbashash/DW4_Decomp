/* Checks a partition id (below 256 and loaded in DAT_0049a228) and a file id (0 up to the
 * partition file count); reports the bad one through FUN_002607e8 and returns -3, else 0. */
typedef struct AdxfPartition {
    int f0;
    int f4;
    int fileCount;
} AdxfPartition;

void FUN_002607e8(const char *message);
extern AdxfPartition *DAT_0049a228[256];
extern char DAT_004edf48[]; /* "E9040828:'ptid' is range outside." */
extern char DAT_004edf70[]; /* "E9040828:'flid' is range outside." */

int FUN_002626a8(unsigned int partitionId, int fileId) {
    AdxfPartition *partition;

    if (partitionId >= 256) {
        FUN_002607e8(DAT_004edf48);
        return -3;
    }
    partition = DAT_0049a228[partitionId];
    if (partition == 0) {
        FUN_002607e8(DAT_004edf48);
        return -3;
    }
    if (fileId < 0 || fileId >= partition->fileCount) {
        FUN_002607e8(DAT_004edf70);
        return -3;
    }
    return 0;
}
