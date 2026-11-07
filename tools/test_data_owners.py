"""The data ownership table stays in link order, section by section."""
import csv
from pathlib import Path
import unittest

import regions

ROOT = Path(__file__).resolve().parent.parent
TABLE = ROOT / "config/SLUS-20836/data-owners.tsv"


def rows():
    with TABLE.open() as fh:
        return [row for row in csv.reader(fh, delimiter="\t") if row and not row[0].startswith("#")]


class DataOwners(unittest.TestCase):
    def test_rows_do_not_overlap(self):
        spans = [(int(row[0], 16), int(row[1], 16)) for row in rows()]
        self.assertTrue(all(start < end for start, end in spans))
        self.assertTrue(all(a[1] <= b[0] for a, b in zip(spans, spans[1:])))

    def test_owners_keep_link_order_in_a_section(self):
        order = {row.id: index for index, row in enumerate(regions.load())}
        last = {}
        for row in rows():
            position = order[row[3]]
            self.assertGreaterEqual(position, last.get(row[2], -1), row)
            last[row[2]] = position

    def test_each_section_opens_with_the_first_object(self):
        opened = {}
        for row in rows():
            opened.setdefault(row[2], row[3])
        self.assertEqual(set(list(opened.values())[1:]), {"metrowerks-runtime"})


if __name__ == "__main__":
    unittest.main()
