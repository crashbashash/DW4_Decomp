extern int DAT_00490c70[4];
extern int DAT_00490c78[4];
extern int DAT_00490c80[4];
extern int DAT_0056ba48[4];
extern int DAT_0056ba50[4];
extern int DAT_0056ba58[4];
extern int DAT_0056ba60[4];
extern int DAT_0056ba68[4];
extern int DAT_0056ba70[4];
extern int DAT_0056ba78[4];
extern int DAT_0056ba80[4];
extern int DAT_0056ba90[];
int FUN_00204840(unsigned arg0){ switch(arg0){
    case 11: return DAT_0056ba70[0];
    case 13: return DAT_0056ba80[0];
    case 12: return DAT_0056ba78[0];
    case 3: return DAT_0056ba48[0];
    case 10: return DAT_0056ba50[0];
    case 9: return DAT_0056ba58[0];
    case 7: return DAT_0056ba60[0];
    case 8: return DAT_0056ba68[0];
    case 0: case 1: case 2: return DAT_0056ba90[arg0];
    case 4: return DAT_00490c70[0];
    case 5: return DAT_00490c78[0];
    case 6: return DAT_00490c80[0];
    default: return 0; } }
