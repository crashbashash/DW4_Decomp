#!/usr/bin/env python3
"""XDATA txt_shop.lua bindings and call-number branches from private retail packs.

Proves pack-local named ownership and the actual bytecode comparison prefixes;
not a runtime lookup winner, localized display acceptance or VM execution test.
"""
import os
from pathlib import Path
import re
import struct
import sys
import unittest
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
import lua_tree
import igb_ids,igb_inst,lua_dump

class XdataScriptOwnership(unittest.TestCase):
    def test_central_and_shop_own_matching_call_number_control_flow(self):
        afs=Path(os.environ.get('DW4_NDMW',str(ROOT.parent/'local/extracted/NDMW.AFS')))
        if not afs.exists():self.skipTest('private NDMW.AFS unavailable')
        reflection=igb_inst.load_reflection(str(ROOT/'data/reflection.json'));protos=[]
        expected={824:(3100,9257,120,9561,9562,124,554152,0),828:(6808,3151,57,3119,3120,9657,1634452,57)}
        with afs.open('rb') as f:
            self.assertEqual(f.read(4),b'AFS\0')
            for entry,wanted in expected.items():
                f.seek(8+entry*8);offset,size=struct.unpack('<II',f.read(8));f.seek(offset);blob=f.read(size)
                _,s1,s2,_=igb_ids.sections(blob,reflection);table,count,ids=igb_ids.find_table(blob,s1,s2)
                objects={i:s2[k] for i,k in enumerate(ids) if k is not None};cursor=max(r['end'] for r in s2);blocks={}
                for i in range(count):
                    row=s1[struct.unpack_from('<H',blob,table+8+2*i)[0]]
                    if row['class']=='igMemoryDirEntry':
                        n=igb_ids.field_map(row)['_memSize'];blocks[i]=(cursor,n);cursor+=(n+3)//4*4
                self.assertEqual(cursor,len(blob));bindings=[]
                for infoid,info in objects.items():
                    if info['class']!='beLuaInfo':continue
                    listid=igb_ids.field_map(info)['_dataList'];row=objects[listid]
                    self.assertEqual(row['class'],'beLuaDataList');fields=igb_ids.field_map(row)
                    n=fields.get('_count',fields.get('slot2'));mem=fields.get('_data',fields.get('slot4'));start,length=blocks[mem]
                    self.assertEqual(length,n*4)
                    for position,dataid in enumerate(struct.unpack_from('<%dI'%n,blob,start)):
                        data=objects[dataid]
                        if data.get('name','').split('\0')[0]!='txt_shop.lua':continue
                        self.assertEqual(data['class'],'beLuaData');objectid=igb_ids.field_map(data)['_dataObject']
                        obj=objects[objectid];self.assertEqual(obj['class'],'beLuaDataObject');fields=igb_ids.field_map(obj)
                        memoryid=fields['_data'];start,length=blocks[memoryid];self.assertEqual(fields['_dataSize'],31147)
                        self.assertGreaterEqual(length,31147);chunks=[m.start() for m in re.finditer(b'\x1bLua',blob)]
                        chunk=chunks.index(start);bindings.append((infoid,listid,position,dataid,objectid,memoryid,start,chunk))
                        _,proto,reader=lua_dump.parse_chunk(blob,start);self.assertEqual(reader.pos-start,31147);protos.append(proto)
                        code=proto['code'];strings=proto['kstr'];calls=set()
                        for i in range(len(code)-4):
                            if [w&63 for w in code[i:i+5]]==[12,16,2,6,32] and strings[code[i]>>6]=='be' and strings[code[i+1]>>6]=='TXTgetCallNo':
                                calls.add((code[i+3]>>6)-lua_dump.MAXARG_S)
                                target=i+5+(code[i+4]>>6)-lua_dump.MAXARG_S
                                self.assertTrue(0<=target<=len(code))
                        self.assertTrue({1150,*range(1154,1164),1165,1166,*range(11730,11761,5)}<=calls)
                        text=Path(lua_tree.chunk_path(entry,chunk)).read_text()
                        self.assertIn('be:TXTgetCallNo() == 1154',text);self.assertIn('be:TXTgetCallNo() == 11760',text)
                self.assertEqual(bindings,[wanted])
        def shape(proto):
            return (proto['numparams'],proto['is_vararg'],proto['maxstack'],proto['code'],proto['knum'],[re.sub(r'I<\d+>','I<#>',s) for s in proto['kstr']],[shape(p) for p in proto['kproto']])
        self.assertEqual(shape(protos[0]),shape(protos[1]))
        self.assertNotEqual(protos[0]['kstr'],protos[1]['kstr'])

if __name__=='__main__':unittest.main()
