#!/usr/bin/env python3
"""Check dependency decoding and known retail MAT edges independently of reports."""
from pathlib import Path
import json
import struct
import sys
import unittest
import warnings

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import lua_engine_dependencies as deps


class Transfers(unittest.TestCase):
    def test_subwindow_receiver_roots_factory_and_reflected_lifecycle(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def word(p):return struct.unpack('<I',deps.verify.va_bytes(image,p,4))[0]
        roots={int(line.split('\t',1)[0],0) for line in
               (ROOT/'config/SLUS-20836/lua-dependency-roots.tsv').read_text().splitlines()
               if line.strip() and not line.startswith('#')}
        slots={124:0x3d5960,132:0x3d59b0,136:0x3d58f0,144:0x3d60e0}
        for slot,target in slots.items():
            self.assertEqual(word(0x53e7c0+slot),target)
            self.assertIn(target,roots)
        self.assertEqual(word(0x3d5988),(3<<26)|(0x38d820>>2))
        self.assertEqual(deps.verify.va_bytes(image,0x516788,7),b'SUBWND\0')
        expected=[0x3d5a60,0x3d5b48,0x3d5bb0]+[0x3d5b48]*7+[0x3d5c18]
        self.assertEqual([word(0x5168e0+i*4) for i in range(11)],expected)
        for site,target in ((0x3d5b38,0x3bb1d0),(0x3d5ba0,0x3b8d90),
                            (0x3d5c08,0x3b7750),(0x3d5c70,0x3b7eb0)):
            self.assertEqual(word(site),(3<<26)|(target>>2))
        self.assertEqual(word(0x3d60d0),0x03e00008)
        self.assertEqual(word(0x3d60d4),0x27bd0050)
        classes=json.loads((ROOT/'data/reflection.json').read_text())['classes']
        fields={f['name']:f['offset'] for f in classes['0x58b028']['fields']}
        parents=dict(line.split('\t')[:2] for line in (ROOT/'data/class-hierarchy.tsv').read_text().splitlines() if line and not line.startswith('#'))
        self.assertEqual(parents['beNDMWStatus'],'beBaseInfoManager')
        base=next(row for row in classes.values() if row['class']=='beBaseInfoManager')
        fields.update({f['name']:f['offset'] for f in base['fields']})
        self.assertEqual({k:fields[k] for k in ('_messenger','_infoList','_windowPro','_whoGenerate','_subWndNo')},
                         {'_messenger':20,'_infoList':24,'_windowPro':32,'_whoGenerate':36,'_subWndNo':40})
    def test_selectctrl_receiver_registration_and_general_dispatch(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def words(p,n):return struct.unpack('<'+'I'*n,deps.verify.va_bytes(image,p,n*4))
        slots={124:0x39cbc0,132:0x39cbf0,136:0x39cb70,140:0x39d720,144:0x378410}
        for offset,target in slots.items():self.assertEqual(words(0x53b290+offset,1)[0],target)
        self.assertEqual(words(0x39cbd0,2),((3<<26)|(0x38d820>>2),0x24c6f7f0))
        self.assertEqual(deps.verify.va_bytes(image,0x50f7f0,24).split(b'\0',1)[0],b'SELECTCTRL')
        self.assertEqual(words(0x378410,2),(0x03e00008,0x0000102d))
        names=tuple(deps.verify.va_bytes(image,p,24).split(b'\0',1)[0].decode('ascii') for p in words(0x4c3b40,7))
        self.assertEqual(names,('GENERATE','ISEND','GETSELECT','ISSELECTNOW','FO2TOP','ISFO2TOP','REMOVE'))
        self.assertEqual(words(0x4c3b60,7),tuple(range(7)))
        targets=words(0x50f8e0,7)
        self.assertEqual(targets[4:6],(0x39dca8,0x39dc60))
        self.assertEqual(words(targets[4],7),(0x8e030018,0x24020001,0x1462006b,0,0x8e02001c,0x14400068,0))
        self.assertEqual(words(targets[5],7),(0x8e030018,0x24020001,0x14620009,0,0x8e02001c,0x14400006,0))
        self.assertEqual(words(targets[5]+28,3),(0x8e240014,(3<<26)|(0x38f150>>2),0x0000282d))

        roots={int(line.split('\t',1)[0],0) for line in (ROOT/'config/SLUS-20836/lua-dependency-roots.tsv').read_text().splitlines() if line.strip() and not line.startswith('#')}
        self.assertTrue(set(slots.values())<=roots)

    def test_shop_initializer_literal_null_paths_and_selector_commands(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def words(p,n):return struct.unpack('<'+'I'*n,deps.verify.va_bytes(image,p,n*4))
        rows=json.loads((ROOT/'data/function-extents.json').read_text());spans={int(r['address'],0):int(r['end_exclusive'],0) for r in rows}
        blocks=[]
        for start in (0x43d1d0,0x43d450,0x43ecc0):
            for p in range(start,spans[start],4):
                code=words(p,6)
                if code[0]==0x3c020052 and code[1]>>16==0x2442 and code[2]>>16==0x1440 and code[4]>>26==4:
                    lo=code[1]&65535;lo=lo-65536 if lo&32768 else lo
                    self.assertNotEqual(0x520000+lo,0)
                    self.assertIn(code[3],(0,0x0000102d))
                    target=p+12+(code[2]&65535)*4
                    self.assertGreaterEqual(target,p+24)
                    self.assertLessEqual(target,p+28)
                    blocks.append(p+16)
        self.assertEqual(len(blocks),32)
        for p,text in ((0x51a918,b'SELECTCTRL'),(0x51a938,b'GENERATE'),(0x51a948,b'GETSELECT'),(0x51a958,b'ISEND'),(0x51a960,b'FO2TOP'),(0x51a968,b'ISFO2TOP')):
            self.assertEqual(deps.verify.va_bytes(image,p,32).split(b'\0',1)[0],text)
        self.assertEqual(words(0x4cfaf0,7),(9999,9999,9999,9999,9999,99999,99999))
        self.assertEqual(words(0x423740,1)[0],0x0002102b)
        self.assertEqual(words(0x423748,1)[0],0x38420001)

    def test_xdata_child_controller_and_script_publication_evidence(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def words(p,n):return struct.unpack('<'+'I'*n,deps.verify.va_bytes(image,p,n*4))
        slots={(0x540220,92):0x4233f0,(0x5400d0,92):0x4233f0,(0x540290,92):0x4233f0,(0x540220,96):0x43d450,(0x5400d0,96):0x43ecc0,(0x540290,96):0x43d1d0,(0x53f870,92):0x43aae0,(0x53f870,96):0x40dae0,(0x53f870,100):0x40dbf0,(0x53f870,104):0x40dd30}
        for (table,slot),target in slots.items():self.assertEqual(words(table+slot,1)[0],target)
        self.assertEqual(words(0x423444,2),(0x8f390060,0x0320f809))
        for address,slot in ((0x43b184,96),(0x43b348,100),(0x43b36c,104)):
            self.assertEqual(words(address,2),(0x8f390000|slot,0x0320f809))
        self.assertEqual(words(0x3747f0,3),(0x3c010059,0x03e00008,0x8c22a220)) # TXTgetCallNo shares the published word.
        self.assertEqual(words(0x4cf970,7),(11730,11735,11740,11745,11750,11755,11760))
        roots={int(line.split('\t',1)[0],0) for line in (ROOT/'config/SLUS-20836/lua-dependency-roots.tsv').read_text().splitlines() if line.strip() and not line.startswith('#')}
        self.assertTrue(set(slots.values())<=roots)

    def test_xdata_literal_null_paths_and_message_script_padding(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def words(p,n):return struct.unpack('<'+'I'*n,deps.verify.va_bytes(image,p,n*4))
        for dead,low in ((0x427758,0xb448),(0x4278a0,0xb448),(0x427940,0xb220),(0x4279e0,0xb448),(0x427a80,0xb248),(0x427b20,0xb470)):
            self.assertEqual(words(dead-16,6),(0x3c020052,0x24420000|low,0x14400003,0,0x10000013,0x0000102d))
            self.assertNotEqual((0x52<<16)+(low-65536),0)
        self.assertEqual(words(0x3f596c,4),(0x10000004,0,0,0x0000802d))
        self.assertEqual(words(0x3f5940,1)[0],0x8c259208)
        self.assertEqual(words(0x3f5994,1)[0],0xac31a220)
        self.assertEqual(words(0x428610,32),words(0x428690,32))
        self.assertEqual(words(0x428690,32),words(0x428710,32))

    def test_model_presentation_redundant_close_sequence_branch(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def word(p):return struct.unpack('<I',deps.verify.va_bytes(image,p,4))[0]
        self.assertEqual(word(0x3f5cb8),0x0100902d) # Capture incoming close sequence in callee-saved s2.
        self.assertEqual(word(0x3f5d78),0x12400057) # Zero skips the complete tracking block.
        self.assertEqual(word(0x3f5e4c),0x16400004) # Same nonzero s2 skips impossible inner null path.
        writes=[]
        for p in range(0x3f5c90,0x3f5efc,4):
            w=word(p);op=w>>26;rt=(w>>16)&31;rd=(w>>11)&31
            if (op==0 and rd==18 and (w&63) not in (8,9)) or (op in (8,9,10,11,12,13,14,15,24,25,30,32,33,35,36,37,39,55) and rt==18):writes.append(p)
        self.assertEqual(writes,[0x3f5cb8,0x3f5ee8]) # Entry move and final saved-register restore only.
        self.assertEqual(tuple(word(p) for p in (0x3f5e54,0x3f5e58)),(0x10000012,0x0000102d))

    def test_shop_root_runtime_factories_modes_and_full_return(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def words(p,n):return struct.unpack('<'+'I'*n,deps.verify.va_bytes(image,p,n*4))
        classes=json.loads((ROOT/'data/reflection.json').read_text())['classes']
        factories={0x3b3370:'beNDMWShopTitle00',0x3b3ac0:'beNDMWStatusTitle01',0x3b3900:'beNDMWStatusTitle02',0x3b36f0:'beNDMWStatusTitle03',0x3b31b0:'beNDMWShopTitle01',0x3b8b60:'beNDMWShopCtrl10',0x3b8630:'beNDMWShopCtrl30',0x3b8400:'beNDMWShopCtrl40',0x3b81d0:'beNDMWShopCtrl50',0x3b6650:'beNDMWShopDevice',0x3b6310:'beNDMWShopJunk'}
        for address,name in factories.items():
            code=words(address,13);lo=code[6]&0xffff;lo=lo-65536 if lo&32768 else lo
            handle=((code[5]&65535)<<16)+lo
            self.assertEqual(code[5]>>16,0x3c01)
            self.assertEqual(code[6]>>16,0x8c24)
            self.assertEqual(code[7],(3<<26)|(0x2fda40>>2))
            self.assertEqual(classes[hex(handle)]['class'],name)
        selected={0x5403e0:0x424160,0x53f6b0:0x424160,0x53f640:0x424160,0x53f5d0:0x424160,0x540370:0x424160,0x53fe50:0x4270a0,0x53fdf0:0x428790,0x53fd90:0x429630,0x53fd30:0x42a2e0,0x53f800:0x43cc20,0x53fcd0:0x42bc70}
        for table,target in selected.items():self.assertEqual(words(table+92,1)[0],target)
        roots={int(line.split('\t',1)[0],0) for line in (ROOT/'config/SLUS-20836/lua-dependency-roots.tsv').read_text().splitlines() if line.strip() and not line.startswith('#')}
        self.assertTrue(set(selected.values())<=roots)
        self.assertEqual(words(0x51b370,10),(0x426e00,0x426b90,0x426e00,0x426bf8,0x426c60,0x426cc8,0x426d30,0x426d30,0x426d30,0x426d98))
        self.assertEqual(words(0x426f80,5),(0xdfbf0020,0x7bb10010,0x7bb00000,0x03e00008,0x27bd0050))
        self.assertEqual(deps.verify.va_bytes(image,0x426fa0,128),deps.verify.va_bytes(image,0x427020,128))
        self.assertEqual(classes['0x588f38']['class'],'beMessenger')
        self.assertEqual(classes['0x588518']['class'],'bePadManager')

    def test_shop_root_metadata_callbacks_and_concrete_update(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def words(p,n):return struct.unpack('<'+'I'*n,deps.verify.va_bytes(image,p,n*4))
        self.assertEqual(words(0x3b65b0,3),(0x3c010059,0x03e00008,0x8c22b010))
        self.assertEqual(words(0x3b8edc,1)[0],0x3c07003b)
        self.assertEqual(words(0x3b8efc,1)[0],0x24e765b0)
        self.assertEqual(words(0x53feb0+92,1)[0],0x4267b0)
        self.assertEqual(words(0x3f64bc,2),(0x8f39005c,0x0320f809))
        self.assertEqual(words(0x3b8e78,1)[0],(3<<26)|(0x3b6430>>2))
        classes=json.loads((ROOT/'data/reflection.json').read_text())['classes']
        self.assertEqual(classes['0x58ae30']['class'],'beNDMWShopCtrl00')
        self.assertEqual(classes['0x58ae30']['fields'],[])
        hierarchy=dict(line.split('\t')[:2] for line in (ROOT/'data/class-hierarchy.tsv').read_text().splitlines() if line and not line.startswith('#'))
        self.assertEqual(hierarchy['beNDMWShopCtrl00'],'beNDMWWindowCtrl')
        roots={int(line.split('\t',1)[0],0) for line in (ROOT/'config/SLUS-20836/lua-dependency-roots.tsv').read_text().splitlines() if line.strip() and not line.startswith('#')}
        self.assertTrue({0x3b65b0,0x3b8e20,0x3b8ec0,0x3b8f30,0x4267b0}<=roots)

    def test_subwindow_command_enums_jump_table_and_return(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def words(p,n):return struct.unpack('<'+'I'*n,deps.verify.va_bytes(image,p,n*4))
        def strings(p,n):
            return tuple(deps.verify.va_bytes(image,v,64).split(b'\0',1)[0].decode('ascii') for v in words(p,n))
        self.assertEqual(strings(0x4ca090,7),('GENERATE','REMOVE','UPDATE','GETSHOPDATA','ONPREVIEW','OFPREVIEW','ISRUN'))
        self.assertEqual(words(0x4ca0b0,7),tuple(range(7)))
        self.assertEqual(strings(0x4c9410,11),('STATUS','XDATA','LABO','BANK','CNOS','DISK','WPU','APU','CHIP','JUNK','CARD'))
        self.assertEqual(words(0x4c9440,11),tuple(range(11)))
        self.assertEqual(words(0x516b30,7),(0x3d6178,0x3d6238,0x3d6298,0x3d8650,0x3d7068,0x3d7e88,0x3d6160))
        for p,target in ((0x3bb75c,0x2fbc70),(0x3b1d9c,0x2fbc70),(0x3d6120,0x3bb730),(0x3d61a0,0x3b1d70)):
            self.assertEqual(words(p,1)[0],(3<<26)|(target>>2))
        self.assertEqual(words(0x3d8734,3),(0x03e00008,0x27bd0190,0))

    def test_reviewed_alias_method_boundaries_and_backend_contract(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def word(p):return struct.unpack('<I',deps.verify.va_bytes(image,p,4))[0]
        rows={int(r['address'],0):r for r in json.loads((ROOT/'data/functions.json').read_text())['functions']}
        expected={0x2d0ae0:(32,220),0x2d0b00:(104,224),0x2d0c00:(16,236),
                  0x2d0c10:(188,260),0x2d0d80:(24,264),0x2d0da0:(140,340),
                  0x2d0e30:(20,336),0x2d0e50:(456,348)}
        for address,(size,slot) in expected.items():
            self.assertEqual(rows[address]['size'],size)
            self.assertEqual(word(0x5313a0+slot),address)
            # Every reviewed body ends with a branch delay slot; return or
            # virtual tail dispatch immediately precedes that final word.
            self.assertIn(word(address+size-8),(0x03e00008,0x03200008))
        roots={int(line.split('\t',1)[0],0) for line in
               (ROOT/'config/SLUS-20836/lua-dependency-roots.tsv').read_text().splitlines()
               if line.strip() and not line.startswith('#')}
        runtime_slots={word(0x5313a0+slot) for slot in range(8,416,4)
                       if 0x2d0560<=word(0x5313a0+slot)<0x2d1640}
        self.assertTrue(runtime_slots<=roots)
        self.assertEqual(word(0x5313a0+412),0x2d1210)
        self.assertEqual(word(0x2d124c),0x3242ffff) # Compare low16 alignment.
        self.assertEqual(word(0x2d1268),0x1662002a) # Compare full64 free sentinel.
        self.assertEqual(word(0x2d131c),0x0070182d) #64-bit wrapped current+signed size.
        self.assertEqual(word(0x2d1478),0x0043082a) # Signed live-count high-water test.
        classes=json.loads((ROOT/'data/reflection.json').read_text())['classes']
        fields={f['name']:f['offset'] for f in classes['0x5869b0']['fields']}
        for name,offset in {'_allocationLock':116,'_poolIndex':120,'_allocedBytes':128,
                            '_nAllocs':136,'_nFrees':140,'_maxSize':144,'_eventTracker':152,
                            '_allocedBytesHigh':160,'_netAllocsHigh':168,'_elementSize':172,
                            '_alignment':176,'_aliasedMemoryPool':180}.items():
            self.assertEqual(fields[name],offset)

    def test_alias_pool_binding_roots_and_factory_sites(self):
        elf=ROOT/'orig/SLUS-20836/SLUS_208.36'
        if not elf.exists():self.skipTest('private retail ELF unavailable')
        image=deps.verify.read_elf(str(elf))
        def word(va):return struct.unpack('<I',deps.verify.va_bytes(image,va,4))[0]
        slots={96:0x2d0690,100:0x2d06a0,104:0x2d0680,116:0x2d06b0,
               120:0x2d0600,124:0x2d0620,128:0x2d0640,132:0x2d0670,400:0x2d0560}
        for slot,target in slots.items():self.assertEqual(word(0x5313a0+slot),target)
        roots={int(line.split('\t',1)[0],0) for line in
               (ROOT/'config/SLUS-20836/lua-dependency-roots.tsv').read_text().splitlines()
               if line.strip() and not line.startswith('#')}
        self.assertTrue({0x2d0560,0x2d0600,0x2d0670}<=roots)
        for site,target in ((0x2f6098,0x2cd170),(0x2cd190,0x2cd3f0),
                            (0x2cd1a0,0x2fda40),(0x2cd1b8,0x2f0040),(0x2cd1cc,0x2d1540)):
            self.assertEqual(word(site),(3<<26)|(target>>2))
        self.assertEqual(word(0x2d05cc),0x8f390178) # Query raw slot376.
        self.assertEqual(word(0x2cd19c),0x8c2469b0) # Read class metadata after registration.

    def test_known_transfer_encodings(self):
        # JAL external, J internal, backward external BEQ, JALR t9,
        # JR t0 (unresolved), JR ra (return), local branch.
        code = struct.pack("<7I", 0x0c0e2b28, 0x08040004, 0x1000fffc,
                           0x0320f809, 0x01000008, 0x03e00008, 0x1000fff9)
        direct, indirect = deps.transfers(code, 0x100000)
        self.assertEqual(direct, [{"site": 0x100000, "target": 0x38aca0},
                                  {"site": 0x100008, "target": 0xffffc}])
        self.assertEqual(indirect, [{"site": 0x10000c, "kind": "jalr", "register": 25},
                                    {"site": 0x100010, "kind": "jr", "register": 8}])

    def test_branch_and_link(self):
        direct, indirect = deps.transfers(struct.pack("<I", 0x0411000f), 0x100000)
        self.assertEqual(direct, [{"site": 0x100000, "target": 0x100040}])
        self.assertFalse(indirect)

    def test_likely_and_coprocessor_branches(self):
        for word in (0x5000000f, 0x4501000f):
            direct, indirect = deps.transfers(struct.pack("<I", word), 0x100000)
            self.assertEqual(direct, [{"site": 0x100000, "target": 0x100040}])
            self.assertFalse(indirect)

    def test_retail_mat_wrapper_edges(self):
        elf = ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():
            self.skipTest("private retail ELF unavailable")
        image = deps.verify.read_elf(str(elf))
        _, symbols = deps.verify.load_symbols(str(ROOT / "config/SLUS-20836/symbols.txt"))
        expected = {0x373160: 0x38aca0, 0x373180: 0x38acd0, 0x3731a0: 0x38ad40,
                    0x3731c0: 0x38add0, 0x3731f0: 0x38ae30, 0x373220: 0x38aea0,
                    0x373250: 0x38ae90}
        for va, target in expected.items():
            direct, indirect = deps.transfers(deps.verify.va_bytes(image, va, symbols[va][1]), va)
            self.assertEqual([edge["target"] for edge in direct], [target])
            self.assertFalse(indirect)

    def test_reference_field_roots_have_retail_vtable_and_descriptor_evidence(self):
        elf = ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():
            self.skipTest("private retail ELF unavailable")
        image = deps.verify.read_elf(str(elf))
        slots = {100: 0x303450, 124: 0x303540, 128: 0x303620,
                 132: 0x305500, 136: 0x303680, 240: 0x305cd0}
        roots = {int(line.split("\t", 1)[0], 0)
                 for line in (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
                 if line.strip() and not line.startswith("#")}
        for slot, target in slots.items():
            pointer, = struct.unpack("<I", deps.verify.va_bytes(image, 0x532c80 + slot, 4))
            self.assertEqual(pointer, target)
            self.assertIn(target, roots)
        reflection = json.loads((ROOT / "data/reflection.json").read_text())
        records = reflection.get("classes", reflection).values()
        classes = {row.get("class"): row for row in records if isinstance(row, dict)}
        for name, minimum in (("beMessengerWork", 2), ("beMessengerArgData", 8)):
            refs = [field for field in classes[name]["fields"]
                    if field.get("type") == "igObjectRefMetaField"]
            self.assertGreaterEqual(len(refs), minimum)

    def test_memory_value_roots_and_instance_teardown_hooks(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        for slot,target in ((124,0x2faa10),(128,0x2faae0),(112,0x2facc0)):
            self.assertEqual(word(0x532a50+slot),target)
        for vt,meta,trim in ((0x531b70,0x331660,0x331d60),(0x534890,0x36efa0,0x13c180),(0x536f10,0x36f600,0x2ff1a0)):
            self.assertEqual(word(vt+88),meta);self.assertEqual(word(vt+72),trim)
        self.assertEqual(word(0x2fab10),(3<<26)|(0x2ed460>>2))
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertTrue({0x2faa10,0x2faae0,0x2facc0,0x13c180,0x331d60}<=roots)

    def test_allocator_builder_and_metadata_lookup_contract(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        self.assertEqual(word(0x52f510+204),0x2f5cd0)
        self.assertEqual(word(0x2f6520),0x27a4008c)
        self.assertEqual(word(0x2f64ac),0xaec30000)
        for site,target in ((0x2f6198,0x2fda40),(0x2f6178,0x2fe460),
                            (0x2f6098,0x2cd170),(0x2d308c,0x2ea780)):
            self.assertEqual(word(site),(3<<26)|(target>>2))
        self.assertEqual(word(0x2fe468),(2<<26)|(0x2d3070>>2))
        self.assertEqual(word(0x2d3088),0x8c255c28)
        classes=json.loads((ROOT / "data/reflection.json").read_text())["classes"]
        fields=classes["0x585be8"]["fields"]
        name=next(field for field in fields if field["name"]=="_name")
        self.assertEqual(name["desc"],0x585c28);self.assertEqual(name["offset"],28)
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertIn(0x2f5cd0,roots)

    def test_context_constructor_destructor_and_special_receiver_evidence(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        for site,instruction in ((0x2f25ec,0x2463f510),(0x2f25f0,0xae030000),
                                 (0x2f25f4,0xae020008),(0x2f2648,0x8f3900b4),
                                 (0x2f26a0,0x240619e0),(0x2f26b0,0x8f3900b4),
                                 (0x2f49e8,0x7fb20020),(0x2f4a38,0xa2400097),
                                 (0x2f6518,0x8f3900cc),(0x2f67cc,0xae000000),
                                 (0x2f6958,0xae230004)):
            self.assertEqual(word(site),instruction)
        for slot,target in ((100,0x2f28d0),(180,0x2f49e0),(208,0x2f64e0),(212,0x2f6780)):
            self.assertEqual(word(0x52f510+slot),target)
        self.assertEqual(word(0x2f270c),(3<<26)|(0x2f8830>>2))
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertTrue({0x2f25d0,0x2f2670,0x2f28d0,0x2f49e0,0x2f64e0,0x2f6780}<=roots)

    def test_registry_bootstrap_and_concrete_context_receivers(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        for site,target in ((0x2f46d8,0x2f2180),(0x2f4770,0x2f2180),
                            (0x2f4978,0x2f2200),(0x2f2190,0x2fa6c0),
                            (0x2f21a0,0x2fa4d0),(0x2f21b4,0x2fa610),
                            (0x2f2218,0x2fa540),(0x2f2228,0x2fa540)):
            self.assertEqual(word(site),(3<<26)|(target>>2))
        self.assertEqual(word(0x2f2234),0xac206f58);self.assertEqual(word(0x2f223c),0xac206f60)
        self.assertEqual(word(0x2f2244),0x8f390188)
        self.assertEqual(word(0x2fa500),0x8f3900d8);self.assertEqual(word(0x2fa658),0x8f3900e8)
        self.assertEqual(word(0x2f868c),0x28410004)
        self.assertEqual(word(0x52f510+92),0x2f2730);self.assertEqual(word(0x52f510+96),0x2f2830)
        self.assertEqual(word(0x2f2694),0x2442f510);self.assertEqual(word(0x2f269c),0xae220000)
        self.assertEqual(word(0x2f2790),0x8f3900d0)
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertTrue({0x2f2180,0x2f2200,0x2f2730,0x2f2830}<=roots)

    def test_owner_registry_and_complete_allocation_wrapper_evidence(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        for site,instruction in ((0x2f0508,0x8c226f60),(0x2f0584,0x8c226f58),
                                 (0x2f0518,0x2452ffff),(0x2f0590,0x2451ffff),
                                 (0x2f053c,0x8f390084),(0x2f0558,0x8f390154),
                                 (0x2f0694,0x8f390074),(0x2ed1e8,0x8f3900d8),
                                 (0x2ed1ec,0x03200008),(0x2ed1f0,0),
                                 (0x2f00d0,(2<<26)|(0x2f88e0>>2)),(0x2f00d4,0x24040002)):
            self.assertEqual(word(site),instruction)
        self.assertEqual(word(0x532a50+84),0x2bf380)
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertIn(0x2bf380,roots)
        self.assertEqual(word(0x2fc0f4),(3<<26)|(0x2fef70>>2))
        self.assertEqual(word(0x2fefec),(3<<26)|(0x2f0670>>2))
        _,symbols=deps.verify.load_symbols(str(ROOT / "config/SLUS-20836/symbols.txt"))
        # the wrapper and its shared tail are two symbols (extent-overrides.tsv cuts them); the
        # span they cover together is still 52 bytes
        self.assertEqual(symbols[0x2ed1c0][1],20)
        self.assertEqual(symbols[0x2ed1e0][1],20)
        self.assertEqual(word(0x2ed1cc),(2<<26)|(0x2ed1e0>>2))
        direct,indirect=deps.transfers(deps.verify.va_bytes(image,0x2ed1c0,52),0x2ed1c0)
        self.assertFalse(direct)
        self.assertEqual(indirect,[{"site":0x2ed1ec,"kind":"jr","register":25}])

    def test_memory_copy_visitor_roots_and_duplicate_buffer_calls(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        for slot,target in ((144,0x2fad50),(152,0x2faf10),(164,0x2fafb0),(168,0x2fb0b0)):
            self.assertEqual(word(0x532a50+slot),target);self.assertIn(target,roots)
        for site,target in ((0x2ed540,0x2ed4e0),(0x2ed54c,0x2ed520),
                            (0x2ed558,0x2ed1c0),(0x2ed564,0x2ed4e0),(0x2ed574,0x127098)):
            self.assertEqual(word(site),(3<<26)|(target>>2))
        self.assertEqual(word(0x2fb148),(3<<26)|(0x300b00>>2))
        self.assertEqual(word(0x300bbc),0x8f3900a8)
        classes=json.loads((ROOT / "data/reflection.json").read_text())["classes"]
        self.assertEqual(classes["0x585d80"]["class"],"igMemoryRefMetaField")

    def test_array_allocation_contract_and_reference_class(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        self.assertEqual(word(0x2faab8),(3<<26)|(0x2fb190>>2))
        # Original virtual query/allocator offsets and reference-class publication.
        for address,instruction in ((0x2fb1c4,0x8f390064),(0x2fb1dc,0x8f39006c),
                                    (0x2fb1f4,0x8f3900dc),(0x2fb21c,0x8c255a60)):
            self.assertEqual(word(address),instruction)
        classes=json.loads((ROOT / "data/reflection.json").read_text())["classes"]
        self.assertEqual(classes["0x585a60"]["class"],"igRefMetaField")
        self.assertEqual(word(0x2fb2b8),0x8c63002c)
        self.assertEqual(word(0x2fb31c),0x8c2422f0)

    def test_list_parent_callbacks_and_raw_element_descriptor_evidence(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        records=json.loads((ROOT / "data/functions.json").read_text())["functions"]
        sizes={int(row["address"],0):row["size"] for row in records}
        for va,load in ((0x130c00,0x8c225b60),(0x143720,0x8c226788)):
            self.assertEqual(sizes[va],12)
            self.assertEqual(tuple(word(va+i*4) for i in range(3)),(0x3c010058,0x03e00008,load))
        classes=json.loads((ROOT / "data/reflection.json").read_text())["classes"]
        self.assertEqual(classes["0x585760"]["class"],"igUnsignedCharMetaField")
        self.assertEqual(word(0x2b766c),0x8c225768)
        self.assertEqual(word(0x2bd2ec),0x8c225b28)
        self.assertEqual(word(0x2c309c),0x8c226100)
        self.assertEqual(word(0x2cabe4),0x24e73720)
        self.assertEqual(word(0x36a1e8),0x24e70c00)
        self.assertEqual(word(0x2c8598),0x24428600)
        self.assertEqual(word(0x2c85a0),0xffa20000)
        self.assertEqual(word(0x2bd7c8),0x2442d830)
        self.assertEqual(word(0x2cabb8),0x2442ac20)
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertTrue({0x130c00,0x143720,0x2c8600,0x2caab0,0x36a0a0}<=roots)

    def test_reviewed_list_specializers_and_memory_clone_slots(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        records=json.loads((ROOT / "data/functions.json").read_text())["functions"]
        sizes={int(row["address"],0):row["size"] for row in records}
        for va in (0x2bd830,0x2cac20):
            self.assertEqual(sizes[va],192)
            self.assertEqual(word(va),0x27bdffc0)
            self.assertEqual(word(va+184),0x03e00008)
            self.assertEqual(word(va+188),0x27bd0040)
        self.assertEqual(word(0x532a50+84),0x2bf380)
        self.assertEqual(word(0x2bf3d8),(3<<26)|(0x2fb9a0>>2))
        self.assertEqual(word(0x2fb9b4),(3<<26)|(0x305c70>>2))
        self.assertEqual(word(0x305c84),(3<<26)|(0x2fc0e0>>2))
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertTrue({0x2bd830,0x2cac20}<=roots)

    def test_list_specialization_uses_a_name_field_selector_and_callback_array(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        classes=json.loads((ROOT / "data/reflection.json").read_text())["classes"]
        fields=classes["0x585cc8"]["fields"]
        name=next(row for row in fields if row["name"]=="_fieldName")
        self.assertEqual(name["desc"],0x585cd8);self.assertEqual(name["offset"],12)
        self.assertEqual(word(0x2fdf28),0x8c255cd8)
        self.assertEqual(word(0x2fdf2c),(2<<26)|(0x2ea780>>2))
        for site in (0x2cac44,0x2bd854):self.assertEqual(word(site),(3<<26)|(0x2fdf20>>2))
        for site in (0x2cac98,0x2bd8a8):self.assertEqual(word(site),(3<<26)|(0x2fdea0>>2))
        self.assertEqual(word(0x2bd7c8),0x2442d830)
        self.assertEqual(word(0x2bd7d0),0xffa20000)
        self.assertEqual(word(0x2cabb8),0x2442ac20)
        self.assertEqual(word(0x2cabc0),0xffa20000)
        self.assertEqual(word(0x2d34d0),0x00431018)
        self.assertEqual(tuple(word(0x4c5cc8+i*4) for i in range(3)),(0x2cab90,0x36a180,0))
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertTrue({0x2fdf20,0x2fdea0}<=roots)

    def test_object_base_callbacks_have_retail_and_classification_evidence(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        records=json.loads((ROOT / "data/functions.json").read_text())["functions"]
        sizes={int(row["address"],0):row["size"] for row in records}
        for va,size in ((0x135530,12),(0x2ff4a0,8),(0x2ff560,12)):self.assertEqual(sizes[va],size)
        self.assertEqual(word(0x2ff4a0),0x03e00008);self.assertEqual(word(0x2ff4a4),0x0000102d)
        for va in (0x135530,0x155b80,0x2ff560):
            self.assertEqual(tuple(word(va+i*4) for i in range(3)),(0x3c010058,0x03e00008,0x8c227198))
        self.assertEqual(word(0x52f148),0x155b80)
        self.assertEqual(word(0x2ff4fc),0x2442f570)
        self.assertEqual(word(0x2ff500),0xffa20000)
        self.assertEqual(word(0x2ff524),0x24a57198)
        self.assertEqual(word(0x2ff528),0x24c6f460)
        self.assertEqual(word(0x2ff52c),0x24e7f4a0)
        self.assertEqual(word(0x2ff530),0x2508f560)
        self.assertEqual(word(0x2ff53c),0x256bf4b0)
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertTrue({0x2ff4f0,0x135530,0x2ff460,0x2ff4a0,0x2ff560,0x2ff4b0,0x2ff570,0x155b80}<=roots)

    def test_internal_list_cleanup_root_uses_original_vtable(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        self.assertEqual(word(0x5327d8),0x2eac30)
        self.assertEqual(word(0x2eac40),(3<<26)|(0x2eac80>>2))
        self.assertEqual(word(0x2eac48),(3<<26)|(0x2ea630>>2))
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertIn(0x2eac30,roots)

    def test_metadata_field_storage_uses_internal_object_list(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        def word(address):return struct.unpack("<I",deps.verify.va_bytes(image,address,4))[0]
        classes=json.loads((ROOT / "data/reflection.json").read_text())["classes"]
        self.assertEqual(classes["0x5860d0"]["class"],"__internalObjectList")
        self.assertEqual(word(0x2c2698),0x3c010058)
        self.assertEqual(word(0x2c269c),0x8c2460d0)
        self.assertEqual(word(0x2eab84),0x3c030053)
        self.assertEqual(word(0x2eab8c),0x246327d0)
        words=struct.unpack("<21I",deps.verify.va_bytes(image,0x2fd7c0,84))
        self.assertIn((3<<26)|(0x2c2670>>2),words)

    def test_work_descriptor_factory_roots_use_original_table(self):
        elf=ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():self.skipTest("private retail ELF unavailable")
        image=deps.verify.read_elf(str(elf))
        factories=struct.unpack("<6I",deps.verify.va_bytes(image,0x4c5ce0,24))
        self.assertEqual(factories,(0x2b9750,0x2b9750,0x2c2cf0,0x2b9750,0x2bce90,0x2bce90))
        roots={int(line.split("\t",1)[0],0) for line in
               (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
               if line.strip() and not line.startswith("#")}
        self.assertTrue(set(factories)<=roots)

    def test_string_field_roots_have_initializer_vtable_and_descriptor_evidence(self):
        elf = ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():
            self.skipTest("private retail ELF unavailable")
        image = deps.verify.read_elf(str(elf))
        def word(address):
            return struct.unpack("<I", deps.verify.va_bytes(image, address, 4))[0]
        call = word(0x2b98cc)
        self.assertEqual(call >> 26, 3)
        self.assertEqual((call & 0x3ffffff) << 2, 0x30b270)
        self.assertEqual(word(0x30b284), 0x3c020053)
        self.assertEqual(word(0x30b28c), 0x24423180)
        self.assertEqual(word(0x30b294), 0xae020000)
        slots = {100: 0x30aa00, 112: 0x30aeb0, 124: 0x30b0b0,
                 128: 0x30b0c0, 136: 0x305540}
        roots = {int(line.split("\t", 1)[0], 0)
                 for line in (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
                 if line.strip() and not line.startswith("#")}
        for slot, target in slots.items():
            self.assertEqual(word(0x533180 + slot), target)
            self.assertIn(target, roots)
        reflection = json.loads((ROOT / "data/reflection.json").read_text())
        classes = {row.get("class"): row for row in reflection.get("classes", reflection).values()
                   if isinstance(row, dict)}
        for name, minimum in (("beMessengerWork", 3), ("beMessengerArgData", 1)):
            strings = [field for field in classes[name]["fields"]
                       if field.get("type") == "igStringMetaField"]
            self.assertGreaterEqual(len(strings), minimum)

    def test_work_registration_roots_have_retail_callback_argument_evidence(self):
        elf = ROOT / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():
            self.skipTest("private retail ELF unavailable")
        image = deps.verify.read_elf(str(elf))
        def word(address):
            return struct.unpack("<I", deps.verify.va_bytes(image, address, 4))[0]
        self.assertEqual(word(0x3581d4), 0x3c040036)
        self.assertEqual(word(0x3581e0), 0x248481f0)
        self.assertEqual((word(0x3581dc) & 0x3ffffff) << 2, 0x2fe940)
        self.assertEqual(word(0x358200), 0x3c030036)
        self.assertEqual(word(0x358208), 0x24638290)
        self.assertEqual(word(0x358210), 0xffa30000)
        self.assertEqual(word(0x358224), 0x3c0b0036)
        self.assertEqual(word(0x358254), 0x256b8100)
        roots = {int(line.split("\t", 1)[0], 0)
                 for line in (ROOT / "config/SLUS-20836/lua-dependency-roots.tsv").read_text().splitlines()
                 if line.strip() and not line.startswith("#")}
        self.assertTrue({0x3581f0, 0x358290, 0x358100} <= roots)

    def test_reviewed_roots_are_in_closure(self):
        if not (ROOT / "orig/SLUS-20836/SLUS_208.36").exists():
            self.skipTest("private retail ELF unavailable")
        # Existing shared source scanners rely on CPython closing temporary
        # file objects. Avoid one ResourceWarning per source file in unittest.
        with warnings.catch_warnings():
            warnings.simplefilter("ignore", ResourceWarning)
            data = deps.inventory(ROOT / "orig/SLUS-20836/SLUS_208.36")
        indexed = {row["address"] for row in data["functions"]}
        for row in data["reviewed_roots"]:
            self.assertIn(row["address"], indexed)
            self.assertTrue(row["evidence"])


if __name__ == "__main__":
    unittest.main()
