#!/usr/bin/env python3
"""Generator freeze primitive: existing Work flag or no-op without Work."""
from verify_scriptservices_retail import World,ROOT,BASE
OWNER,RAM,INFO,LIST,DATA,WORK=range(BASE+0x310000,BASE+0x310600,0x100)
class Retail(World):
    def call(self,e,a):
        if e in (0x38f820,0x360b10):return 0
        if e==0x38d4a0:return self.command
        return super().call(e,a)
def main():
    elf=ROOT.parent.parent/'local/extracted/SLUS_208.36'
    if not elf.exists():print('generator freeze: private ELF unavailable, skipped');return
    w=Retail(elf.read_bytes());total=0
    for present in range(2):
        for command in (6,7):
            for previous in (0,1,128,255):
                w.w(RAM+44,4,WORK if present else 0);w.w(RAM+12,4,INFO);w.w(RAM+8,4,0);w.w(INFO+28,4,LIST);w.list(LIST,[DATA])
                for off in range(64):w.w(WORK+off,1,(off*13)&255)
                w.w(WORK+8,1,previous);before=bytes(w.read(WORK+i,1) for i in range(64))
                w.command=command;w.invoke(0x3853c0,OWNER,RAM,0)
                after=bytes(w.read(WORK+i,1) for i in range(64));expected=bytearray(before)
                if present:expected[8]=int(command==6)
                assert after==expected,(present,command,previous,after,expected);total+=1
    print(f'generator freeze: {total} original3853c0 Work/no-Work cases change only Work+8; no Work is an exact no-op, enum/query decoding controlled')
if __name__=='__main__':main()
