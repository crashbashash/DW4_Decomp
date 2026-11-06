"""tools/exceptions.py: recovering the retail exception index records from an image."""
import os
from pathlib import Path
import struct
import tempfile
import unittest

import exceptions as exception_records
import verify

BASE, FILE_BASE = exception_records.VADDR_BASE, exception_records.FILE_BASE


def image_with(records, tables, size=0x4000):
    """A synthetic image: `records` are (fn, size_word, third) triples laid out as one
    index array at BASE+0x3000; `tables` maps table address -> bytes."""
    image = bytearray(FILE_BASE + size)
    for address, data in tables.items():
        image[address - BASE + FILE_BASE:address - BASE + FILE_BASE + len(data)] = data
    at = BASE + 0x3000
    for triple in records:
        struct.pack_into("<III", image, at - BASE + FILE_BASE, *triple)
        at += 12
    return bytes(image)


class Scanner(unittest.TestCase):
    FUNCTIONS = {BASE + 0x100: 0x1c, BASE + 0x120: 0x5c, BASE + 0x180: 0x40, BASE + 0x200: 0x30,
                 BASE + 0x240: 0x10, BASE + 0x260: 0x24}

    def test_runs_of_records_with_tables_sized_by_their_neighbours(self):
        first, second = BASE + 0x2000, BASE + 0x2010
        tables = {first: bytes.fromhex("06051000099c0012"), second: bytes.fromhex("0605100000820510c0e93300")}
        records = [(BASE + 0x100, 0x1c | 1, 0x2000),          # packed
                   (BASE + 0x120, 0x5c, first),
                   (BASE + 0x180, 0x40, second),
                   (BASE + 0x200, 0x30 | 1, 0x406000),
                   (BASE + 0x240, 0x10 | 1, 0x4001),
                   (BASE + 0x260, 0x24 | 1, 0x2000)]
        found = exception_records.scan(image_with(records, tables), self.FUNCTIONS)
        self.assertEqual([r[0] for r in found], [r[0] for r in records])
        self.assertEqual(found[0], (BASE + 0x100, BASE + 0x3000, None, 0))
        self.assertEqual(found[1], (BASE + 0x120, BASE + 0x300c, first, 0x10))
        # the last table ends at the index region, less whole zero words of padding
        self.assertEqual(found[2], (BASE + 0x180, BASE + 0x3018, second, 12))

    def test_a_short_run_of_lookalikes_is_not_a_record_array(self):
        records = [(BASE + 0x100, 0x1c | 1, 0x2000), (BASE + 0x120, 0x5c | 1, 0x2000)]
        self.assertEqual(exception_records.scan(image_with(records, {}), self.FUNCTIONS), [])

    def test_unlisted_functions_inside_a_run_are_kept(self):
        records = [(BASE + 0x100, 0x1c | 1, 0x2000), (BASE + 0x120, 0x5c | 1, 0x2000),
                   (BASE + 0x150, 0x24 | 1, 0x2000),          # a body the map does not list
                   (BASE + 0x180, 0x40 | 1, 0x2000), (BASE + 0x200, 0x30 | 1, 0x2000),
                   (BASE + 0x240, 0x10 | 1, 0x2000)]
        found = exception_records.scan(image_with(records, {}), self.FUNCTIONS)
        self.assertEqual(len(found), 6)
        self.assertIn(BASE + 0x150, [r[0] for r in found])

    def test_table_round_trips_through_the_config_file(self):
        rows = [(BASE + 0x100, BASE + 0x3000, None, 0), (BASE + 0x120, BASE + 0x300c, BASE + 0x2000, 0x10)]
        with tempfile.TemporaryDirectory() as td:
            path = os.path.join(td, "exceptions.txt")
            with open(path, "w") as fh:
                fh.write(exception_records.format_table(rows))
            self.assertEqual(exception_records.load(path),
                             {BASE + 0x100: (BASE + 0x3000, None, 0), BASE + 0x120: (BASE + 0x300c, BASE + 0x2000, 0x10)})
            self.assertTrue(open(path).read().startswith("# fn_va index_record_va table_va table_size — GENERATED"))

    def test_fixture_symbol_maps_have_no_retail_records(self):
        with tempfile.TemporaryDirectory() as td:
            symbols = os.path.join(td, "symbols.txt")
            Path(symbols).write_text("00180000 000010 fixture\n")
            self.assertEqual(exception_records.load(exception_records.config_path(symbols)), {})
        self.assertEqual(exception_records.config_path(exception_records.SYMBOLS_DEFAULT),
                         exception_records.CONFIG_DEFAULT)


@unittest.skipUnless(Path(verify.ELF_DEFAULT).exists() and Path(exception_records.CONFIG_DEFAULT).exists(),
                     "retail image or generated table unavailable")
class RetailTable(unittest.TestCase):
    def test_generated_table_is_current_and_names_the_known_records(self):
        image = Path(verify.ELF_DEFAULT).read_bytes()
        functions = exception_records.read_functions(exception_records.SYMBOLS_DEFAULT)
        text = exception_records.format_table(exception_records.scan(image, functions))
        self.assertEqual(text, Path(exception_records.CONFIG_DEFAULT).read_text())
        table = exception_records.load()
        # the anchors
        self.assertEqual(table[0x3fca10], (0x553b80, 0x544fd4, 0x1a0))
        self.assertEqual(table[0x407120], (0x553bd4, 0x545174, 0x28))
        self.assertEqual(table[0x1005f0], (0x546fd4, None, 0))
        # every declared group row agrees with the recovered table
        import unitobjects
        for group in unitobjects.load():
            if group.exceptions:
                self.assertEqual(table[group.owner], group.exceptions, hex(group.owner))


if __name__ == "__main__":
    unittest.main()
