#!/usr/bin/env python3
"""Save Keeper named-script ownership and exact delayed-stage call bytecode.

Uses the private pack's object/id/pool graph. It does not execute the save UI,
resolve the destination's full scene graph, or prove persistence/interchange.
"""
import os
from pathlib import Path
import struct
import sys
import unittest

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
import igb_ids
import igb_inst
import lua_dump
import lua_tree


class SaveKeeperOwnership(unittest.TestCase):
    def test_saveshop_owned_payload_and_delayed_stage_request(self):
        afs=Path(os.environ.get('DW4_NDMW',str(ROOT.parent/'local/extracted/NDMW.AFS')))
        if not afs.exists():self.skipTest('private NDMW.AFS unavailable')
        with afs.open('rb') as f:
            self.assertEqual(f.read(4),b'AFS\0')
            f.seek(8+824*8);offset,size=struct.unpack('<II',f.read(8));f.seek(offset);blob=f.read(size)
        self.assertEqual(len(blob),size)
        reflection=igb_inst.load_reflection(str(ROOT/'data/reflection.json'))
        _,s1,s2,_=igb_ids.sections(blob,reflection)
        table,count,ids=igb_ids.find_table(blob,s1,s2)
        objects={i:s2[k] for i,k in enumerate(ids) if k is not None}
        cursor=max(row['end'] for row in s2);blocks={}
        for i in range(count):
            row=s1[struct.unpack_from('<H',blob,table+8+2*i)[0]]
            if row['class']=='igMemoryDirEntry':
                length=igb_ids.field_map(row)['_memSize'];blocks[i]=(cursor,length);cursor+=(length+3)//4*4
        self.assertEqual(cursor,len(blob))
        info=objects[3100];self.assertEqual(info['class'],'beLuaInfo')
        data_list=igb_ids.field_map(info)['_dataList'];self.assertEqual(data_list,9257)
        row=objects[data_list];self.assertEqual(row['class'],'beLuaDataList')
        fields=igb_ids.field_map(row)
        # This parser labels inherited list members by their serialized slots;
        # the established igObjectList record is count/capacity/data at2/3/4.
        n=fields.get('_count',fields.get('slot2'));block=fields.get('_data',fields.get('slot4'))
        start,length=blocks[block];self.assertEqual(n,123);self.assertEqual(length,n*4)
        members=struct.unpack_from('<%dI'%n,blob,start)
        self.assertTrue(all(objects[p]['class']=='beLuaData' for p in members))
        self.assertEqual(len({objects[p]['name'].split('\0')[0] for p in members}),123)
        self.assertEqual(len({igb_ids.field_map(objects[p])['_dataObject'] for p in members}),114)
        named=[(i,p) for i,p in enumerate(members) if objects[p].get('name','').split('\0')[0]=='saveshop.lua']
        self.assertEqual(named,[(112,9523)])
        script=igb_ids.field_map(objects[9523]);self.assertEqual(script['_dataObject'],9524)
        row=objects[9524];self.assertEqual(row['class'],'beLuaDataObject')
        fields=igb_ids.field_map(row);self.assertEqual(fields['_data'],9546)
        start,length=blocks[fields['_data']];self.assertEqual(fields['_dataSize'],655);self.assertGreaterEqual(length,655)
        self.assertEqual(start,2482480)
        starts=[];p=0
        while True:
            p=blob.find(b'\x1bLua',p)
            if p<0:break
            starts.append(p);p+=1
        self.assertEqual(starts.index(start),108)
        _,proto,reader=lua_dump.parse_chunk(blob,start);self.assertEqual(reader.pos-start,655)
        code=proto['code'];strings=proto['kstr']
        self.assertEqual([w&63 for w in code[53:62]],[12,16,7,4,6,7,7,6,2])
        self.assertEqual([strings[code[i]>>6] for i in (53,54,55,58,59)],
                         ['be','DMsetSD','STAGECTL','NEXTSTAGE','stagIS12'])
        self.assertEqual((code[57]>>6)-lua_dump.MAXARG_S,-1)
        self.assertEqual((code[60]>>6)-lua_dump.MAXARG_S,90)
        self.assertEqual((code[61]>>15,(code[61]>>6)&511),(0,0))
        text=Path(lua_tree.chunk_path(824,73)).read_text()
        self.assertIn('be:DMsetLua("saveshop.lua")',text)


if __name__=='__main__':unittest.main()
