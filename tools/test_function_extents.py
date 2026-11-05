"""Regression: disjoint Ghidra body counts must not truncate a reviewed return."""
import json
from pathlib import Path
import tempfile
import unittest

from split import apply_function_extents


class ReviewedSpans(unittest.TestCase):
    functions = [(0x3f5350, 160, "title_message", None),
                 (0x3f5400, 12, "title_meta", None)]

    def apply(self, rows):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "extents.json"
            path.write_text(json.dumps(rows))
            return apply_function_extents(self.functions, path)

    def test_retail_return_and_delay_slot_are_included(self):
        rows = json.loads((Path(__file__).resolve().parents[1] /
                           "data/function-extents.json").read_text())
        rows = [row for row in rows if int(row["address"], 0) == 0x3f5350]
        result = self.apply(rows)
        self.assertEqual(result[0][1], 168)
        self.assertEqual(result[1], self.functions[1])

    def test_material_dispatch_includes_shared_return(self):
        rows = json.loads((Path(__file__).resolve().parents[1] /
                           "data/function-extents.json").read_text())
        rows = [row for row in rows if int(row["address"], 0) == 0x38bdf0]
        self.assertEqual(len(rows), 1)
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "extents.json"
            path.write_text(json.dumps(rows))
            result = apply_function_extents([(0x38bdf0, 212, "material_message", None),
                                            (0x38bed0, 12, "material_meta", None)], path)
        self.assertEqual(result[0][1], 220)
        self.assertLess(0x38bec8, result[0][0] + result[0][1])
        self.assertEqual(result[1][0], 0x38bed0)

    def test_messenger_selector_and_dispatch_include_complete_epilogues(self):
        rows = json.loads((Path(__file__).resolve().parents[1] /
                           "data/function-extents.json").read_text())
        for start, old_size, end, next_start in ((0x38d860, 2028, 0x38e054, 0x38e060),
                                                (0x38e060, 1192, 0x38e52c, 0x38e530)):
            with self.subTest(start=start), tempfile.TemporaryDirectory() as tmp:
                row = [r for r in rows if int(r["address"], 0) == start]
                self.assertEqual(len(row), 1)
                path = Path(tmp) / "extents.json"
                path.write_text(json.dumps(row))
                result = apply_function_extents([(start, old_size, "messenger", None),
                                                (next_start, 128, "next", None)], path)
                self.assertEqual(result[0][1], end - start)
                self.assertLess(end - 4, start + result[0][1])
                self.assertEqual(result[1][0], next_start)

    def test_allocator_wrapper_includes_shared_virtual_jump(self):
        rows=json.loads((Path(__file__).resolve().parents[1]/"data/function-extents.json").read_text())
        row=[r for r in rows if int(r["address"],0)==0x2ed1c0]
        self.assertEqual(len(row),1);self.assertEqual(row[0]["body_bytes"],40)
        with tempfile.TemporaryDirectory() as tmp:
            path=Path(tmp)/"extents.json";path.write_text(json.dumps(row))
            result=apply_function_extents([(0x2ed1c0,40,"allocate",None),
                                          (0x2ed200,56,"default_allocate",None)],path)
        self.assertEqual(result[0][1],52)
        self.assertEqual(result[0][0]+result[0][1],0x2ed1f4)

    def test_subwindow_update_preserves_return_and_three_padding_holes(self):
        rows=json.loads((Path(__file__).resolve().parents[1]/"data/function-extents.json").read_text())
        row=next(r for r in rows if int(r["address"],0)==0x3d59b0)
        self.assertEqual(row["body_bytes"],1820)
        with tempfile.TemporaryDirectory() as tmp:
            path=Path(tmp)/"extents.json";path.write_text(json.dumps([row]))
            result=apply_function_extents([(0x3d59b0,1820,"subwindow_update",None),
                                          (0x3d60e0,9824,"subwindow_message",None)],path)
        self.assertEqual(result[0][1],1832)
        self.assertEqual(result[0][0]+result[0][1],0x3d60d8)
        occupied={p for r in row["body_ranges"] for p in range(int(r["start"],0),int(r["end_exclusive"],0),4)}
        self.assertEqual(len(occupied)*4,1820)
        self.assertEqual(set(range(0x3d59b0,0x3d60d8,4))-occupied,
                         {0x3d59f4,0x3d5a5c,0x3d600c})
        self.assertTrue({0x3d60cc,0x3d60d0,0x3d60d4}<=occupied)

    def test_subwindow_command_span_separates_final_padding(self):
        rows=json.loads((Path(__file__).resolve().parents[1]/'data/function-extents.json').read_text())
        row=next(r for r in rows if int(r['address'],0)==0x3d60e0)
        occupied={p for r in row['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
        self.assertEqual(int(row['end_exclusive'],0),0x3d873c)
        self.assertEqual(row['body_bytes'],9736)
        self.assertEqual(len(occupied),2434)
        self.assertTrue({0x3d8730,0x3d8734,0x3d8738}<=occupied)
        self.assertNotIn(0x3d873c,occupied)
        self.assertEqual(len(set(range(0x3d60e0,0x3d873c,4))-occupied),21)

    def test_shop_root_return_extent_is_not_occupied_byte_sum(self):
        rows=json.loads((Path(__file__).resolve().parents[1]/'data/function-extents.json').read_text())
        row=next(r for r in rows if int(r['address'],0)==0x4267b0)
        self.assertEqual(row['body_bytes'],2004)
        self.assertEqual(int(row['end_exclusive'],0),0x426f94)
        occupied={p for r in row['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
        self.assertTrue(set(range(0x426f80,0x426f94,4))<=occupied)
        self.assertEqual(set(range(0x4267b0,0x426f94,4))-occupied,{0x4267f4,0x426ae4,0x426b04,0x426b8c})

    def test_reviewed_service_controller_spans_preserve_return_and_padding(self):
        rows={int(r['address'],0):r for r in json.loads((Path(__file__).resolve().parents[1]/'data/function-extents.json').read_text())}
        spans={0x424160:208,0x4270a0:5484,0x428790:3608,0x429630:3240,0x42a2e0:5400,0x43cc20:1168,0x42bc70:2844}
        self.assertEqual(sum(spans.values()),21952)
        for address,size in spans.items():
            row=rows[address];self.assertEqual(int(row['end_exclusive'],0)-address,size)
            occupied={p for r in row['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
            self.assertTrue({address+size-8,address+size-4}<=occupied)
        elf=Path(__file__).resolve().parents[1]/'orig/SLUS-20836/SLUS_208.36'
        if elf.exists():
            import verify
            image=verify.read_elf(str(elf))
            for address,size in spans.items():self.assertEqual(verify.va_bytes(image,address+size-8,4),bytes.fromhex('0800e003'))

    def test_shop_selector_initializer_full_return_spans(self):
        rows={int(r['address'],0):r for r in json.loads((Path(__file__).resolve().parents[1]/'data/function-extents.json').read_text())}
        for address,occupied,size in ((0x43d1d0,628,636),(0x43ecc0,3740,3752),(0x43fb70,692,696)):
            row=rows[address];self.assertEqual(row['body_bytes'],occupied)
            self.assertEqual(int(row['end_exclusive'],0)-address,size)
            body={p for r in row['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
            self.assertTrue({address+size-8,address+size-4}<=body)

    def test_selectctrl_handler_preserves_all_saved_register_restores(self):
        rows={int(r['address'],0):r for r in json.loads((Path(__file__).resolve().parents[1]/'data/function-extents.json').read_text())}
        row=rows[0x39d720]
        self.assertEqual(row['body_bytes'],1932)
        self.assertEqual(int(row['end_exclusive'],0),0x39dec8)
        with tempfile.TemporaryDirectory() as tmp:
            path=Path(tmp)/'extents.json';path.write_text(json.dumps([row]))
            result=apply_function_extents([(0x39d720,1932,'handler',None),(0x39ded0,12,'meta',None)],path)
        self.assertEqual(result[0][1],1960)
        self.assertEqual(result[0][0]+result[0][1],0x39dec8)
        occupied={p for r in row['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
        self.assertEqual(len(occupied)*4,1932)
        self.assertTrue(set(range(0x39dea0,0x39dec8,4))<=occupied)
        elf=Path(__file__).resolve().parents[1]/'orig/SLUS-20836/SLUS_208.36'
        if elf.exists():
            import struct,verify
            image=verify.read_elf(str(elf))
            self.assertEqual(struct.unpack('<10I',verify.va_bytes(image,0x39dea0,40)),
                             (0xdfbf0070,0x7bb60060,0x7bb50050,0x7bb40040,0x7bb30030,
                              0x7bb20020,0x7bb10010,0x7bb00000,0x03e00008,0x27bd00a0))
            holes=set(range(0x39d720,0x39dec8,4))-occupied
            self.assertEqual(len(holes),7)
            for address in holes:self.assertEqual(verify.va_bytes(image,address,4),b'\0'*4)
            update=rows[0x39cbf0]
            self.assertEqual(update['body_bytes'],2816)
            self.assertEqual(int(update['end_exclusive'],0),0x39d720)
            body={p for r in update['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
            padding=set(range(0x39cbf0,0x39d720,4))-body
            self.assertEqual(len(padding),12)
            for address in padding:self.assertEqual(verify.va_bytes(image,address,4),b'\0'*4)

    def test_chip_list_text_helper_includes_return_and_delay(self):
        rows={int(r['address'],0):r for r in json.loads((Path(__file__).resolve().parents[1]/'data/function-extents.json').read_text())}
        row=rows[0x43c7f0]
        self.assertEqual(row['body_bytes'],1064)
        self.assertEqual(int(row['end_exclusive'],0),0x43cc20)
        with tempfile.TemporaryDirectory() as tmp:
            path=Path(tmp)/'extents.json';path.write_text(json.dumps([row]))
            result=apply_function_extents([(0x43c7f0,1064,'text',None),(0x43cc20,1168,'device',None)],path)
        self.assertEqual(result[0][1],1072)
        elf=Path(__file__).resolve().parents[1]/'orig/SLUS-20836/SLUS_208.36'
        if elf.exists():
            import struct,verify
            image=verify.read_elf(str(elf))
            self.assertEqual(struct.unpack('<2I',verify.va_bytes(image,0x43cc18,8)),(0x03e00008,0x27bd00a0))

    def test_database_index_finder_preserves_full_return(self):
        rows=json.loads((Path(__file__).resolve().parents[1]/'data/function-extents.json').read_text())
        row=next(r for r in rows if int(r['address'],0)==0x3a93a0)
        self.assertEqual(row['body_bytes'],184)
        self.assertEqual(int(row['end_exclusive'],0),0x3a9460)
        occupied={p for r in row['body_ranges'] for p in range(int(r['start'],0),int(r['end_exclusive'],0),4)}
        self.assertTrue({0x3a9458,0x3a945c}<=occupied)
        self.assertEqual(set(range(0x3a93a0,0x3a9460,4))-occupied,{0x3a93cc,0x3a9424})
        with tempfile.TemporaryDirectory() as tmp:
            path=Path(tmp)/'extents.json';path.write_text(json.dumps([row]))
            result=apply_function_extents([(0x3a93a0,184,'find_index',None),(0x3a9460,216,'get_int',None)],path)
        self.assertEqual(result[0][1],192)
        self.assertEqual(result[1][0],0x3a9460)
        elf=Path(__file__).resolve().parents[1]/'orig/SLUS-20836/SLUS_208.36'
        if elf.exists():
            import struct,verify
            self.assertEqual(struct.unpack('<2I',verify.va_bytes(verify.read_elf(str(elf)),0x3a9458,8)),(0x03e00008,0x27bd0050))

    def test_invalid_spans_fail_before_changing_the_split(self):
        for start, end in ((0x3f5350, 0x3f53ec), (0x3f5350, 0x3f5404),
                           (0x3f5350, 0x3f53f9), (0x3f5354, 0x3f53f8)):
            with self.subTest(start=start, end=end), self.assertRaises(ValueError):
                self.apply([{"address": hex(start), "end_exclusive": hex(end)}])

    def test_duplicate_evidence_fails(self):
        row = {"address": "0x3f5350", "end_exclusive": "0x3f53f8"}
        with self.assertRaises(ValueError):
            self.apply([row, row])

    def test_epilogue_rows_end_on_jr_ra_with_stack_restore(self):
        """Rows added for symbols that stopped before `jr ra; addiu sp` end right after it."""
        import struct
        root = Path(__file__).resolve().parents[1]
        elf = root / "orig/SLUS-20836/SLUS_208.36"
        if not elf.exists():
            self.skipTest("private retail ELF not available")
        img = elf.read_bytes()

        def word(va):
            return struct.unpack_from("<I", img, va - 0x100000 + 0x80)[0]
        rows = json.loads((root / "data/function-extents.json").read_text())
        checked = 0
        for row in rows:
            if row.get("body_bytes") is None or len(row["body_ranges"]) != 1:
                continue
            start, end = int(row["address"], 0), int(row["end_exclusive"], 0)
            if end - start == row["body_bytes"] or word(end - 8) != 0x03E00008:
                continue
            delay = word(end - 4)
            if (delay >> 16) == 0x27BD:           # addiu sp,sp,+N closes the frame
                checked += 1
        self.assertGreater(checked, 200)


if __name__ == "__main__":
    unittest.main()
