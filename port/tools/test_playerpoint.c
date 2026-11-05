#include "dw4/playerpoint.h"
#include "dw4/mount.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
    dw4_mount m;assert(!dw4_mount_open(&m,argc>1?argv[1]:"../local/extracted"));
    static const unsigned entries[]={820,824,828},counts[]={5,6,3};
    for(unsigned s=0;s<3;s++) {
        uint32_t size;const void *blob=dw4_mount_entry(&m,0,entries[s],&size,NULL);assert(blob);
        for(unsigned group=0;group<=counts[s];group++)for(unsigned player=0;player<4;player++) {
            int index=group==counts[s]?99:(int)group;float matrix[16];
            assert(!dw4_playerpoint_matrix(blob,size,index,player,matrix));
            printf("%u %d %u",entries[s],index,player);
            for(unsigned k=0;k<16;k++){uint32_t word;memcpy(&word,matrix+k,4);printf(" %08x",word);}puts("");
        }
        float matrix[16],saved[16];memset(matrix,0x5a,sizeof matrix);memcpy(saved,matrix,sizeof saved);
        assert(dw4_playerpoint_matrix(blob,size,-1,0,matrix)==-1 && !memcmp(matrix,saved,sizeof matrix));
        assert(dw4_playerpoint_matrix(blob,size,0,4,matrix)==-1 && !memcmp(matrix,saved,sizeof matrix));
        assert(dw4_playerpoint_matrix(blob,20,0,0,matrix)==-1 && !memcmp(matrix,saved,sizeof matrix));
    }
    dw4_mount_close(&m);return 0;
}
