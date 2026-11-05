/* Developer aid: print every sequence command of a stage pack model controller. */
#include "dw4/modelctrl.h"
#include "dw4/igfile.h"
#include "dw4/mount.h"
#include <stdio.h>
#include <assert.h>
int main(int argc,char **argv){
    dw4_mount m;assert(!dw4_mount_open(&m,"../../local/extracted"));
    dw4_igfile f={0};if(argv[1][0]=='n')assert(!dw4_igfile_open_named(&f,&m,argv[3]));else assert(!dw4_igfile_open_stage_pack(&f,&m,argv[1],0,0));
    dw4_modelctrl *c=dw4_modelctrl_open(f.data,f.len,argv[2]);if(!c){fprintf(stderr,"open failed\n");return 1;}
    dw4_modelctrl_census(c,stdout);return 0;}
