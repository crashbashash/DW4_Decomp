#!/usr/bin/env python3
"""Authored hub spawn matrices: independent pack decoder + real39c1c0 traversal.
Matrix delivery is the sole engine leaf; this does not validate world publication.
"""
import argparse
from pathlib import Path
import struct
import subprocess
import sys
from verify_scriptservices_retail import World,ROOT,BASE
sys.path.insert(0,str(ROOT.parent/'scripts'))
import igb_ids
import igb_inst
OWNER,INFO,LIST,GROUPS,CHILDREN,TRANSFORMS=range(BASE+0x400000,BASE+0x406000,0x1000)
class Retail(World):
    def call(self,entry,a):
        if entry==0x38f5b0:
            self.result=bytes(self.read((a[1]&0xffffffff)+i,1) for i in range(64));return 0
        raise AssertionError(f'unexpected engine leaf {entry:x}')
def matrices(blob,reflection):
    dirs,first,second,_=igb_ids.sections(blob,reflection)
    table,n,ids=igb_ids.find_table(blob,first,second)
    objects={i:second[k] for i,k in enumerate(ids) if k is not None}
    cursor=max(row['end'] for row in second);blocks={}
    for i in range(n):
        row=first[struct.unpack_from('<H',blob,table+8+2*i)[0]]
        if row['class']=='igMemoryDirEntry':
            length=igb_ids.field_map(row)['_memSize'];blocks[i]=(cursor,length);cursor+=(length+3)//4*4
    assert cursor==len(blob)
    def members(i):
        fields=igb_ids.field_map(objects[i]);count=fields['slot2'];offset,length=blocks[fields['slot4']]
        assert count*4<=length
        return struct.unpack_from('<%dI'%count,blob,offset)
    info=next(row for row in second if row['class']=='bePoint01Info')
    out=[]
    for group in members(igb_ids.field_map(info)['_dataList']):
        row=objects[group];assert row['class']=='beGroupKeep'
        group_matrices=[]
        for transform in members(igb_ids.field_map(row)['slot7']):
            row=objects[transform];assert row['class']=='igTransform'
            offset=row['off']+8;found=None
            for kind,ordinal,width in dirs[row['classIndex']]['trips']:
                if ordinal==8:
                    assert kind==40 and width==64;found=blob[offset:offset+64]
                offset+=4+struct.unpack_from('<I',blob,offset)[0] if kind==4 else igb_inst.align4(width)
            assert offset==row['end'] and found is not None
            group_matrices.append(found)
        assert len(group_matrices)==4;out.append(group_matrices)
    return out
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--roms',default=str(ROOT.parent.parent/'local/extracted'));ap.add_argument('--tool',default=str(ROOT/'build/test_playerpoint'));a=ap.parse_args()
    roms=Path(a.roms)
    if not (roms/'NDMW.AFS').exists() or not (roms/'SLUS_208.36').exists():
        raise SystemExit('playerpoint validation requires private USA archives and ELF')
    rows=subprocess.check_output([a.tool,str(roms)],text=True).splitlines()
    reflection=igb_inst.load_reflection(str(ROOT.parent/'data/reflection.json'))
    packs={}
    with (roms/'NDMW.AFS').open('rb') as f:
        for entry in (820,824,828):
            f.seek(8+entry*8);offset,size=struct.unpack('<II',f.read(8));f.seek(offset);packs[entry]=matrices(f.read(size),reflection)
    w=Retail((roms/'SLUS_208.36').read_bytes());w.descend=set();total=0
    for line in rows:
        parts=line.split();entry,group,player=map(int,parts[:3]);native=struct.pack('<16I',*[int(x,16) for x in parts[3:]])
        authored=packs[entry];assert len(native)==64
        w.w(INFO+32,4,LIST);w.list(LIST,[GROUPS+i*0x100 for i in range(len(authored))]);w.w(OWNER+20,4,0)
        for i,players in enumerate(authored):
            children=CHILDREN+i*0x100;w.w(GROUPS+i*0x100+28,4,children)
            transforms=[TRANSFORMS+i*0x400+j*0x100 for j in range(4)];w.list(children,transforms)
            for address,matrix in zip(transforms,players):
                for j,byte in enumerate(matrix):w.w(address+32+j,1,byte)
        w.result=None;w.invoke(0x39c1c0,OWNER,INFO,group,player)
        assert native==w.result==authored[group if group<len(authored) else 0][player],(entry,group,player)
        total+=1
    assert total==68
    print(f'playerpoint: {total} authored matrices and original39c1c0 deliveries match, all hub groups/four player rows/high-index fallback; invalid host inputs preserve output')
if __name__=='__main__':main()
