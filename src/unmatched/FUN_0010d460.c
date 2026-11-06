int FUN_0010ba90();
int RemoveDmacHandler();
extern int DAT_00481e68[4];
extern int DAT_00555fd4[4];
void FUN_0010d460(void) {
    FUN_0010ba90(5);
    RemoveDmacHandler(5, DAT_00555fd4[0]);
    DAT_00481e68[0] = 0;
}
