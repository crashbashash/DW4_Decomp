#!/usr/bin/env python3
"""regions.py — config/SLUS-20836/regions.tsv: what each part of the image is."""
import bisect
import collections
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_PATH = os.path.join(ROOT, "config", "SLUS-20836", "regions.tsv")
Region = collections.namedtuple("Region", "lo hi id label group build anchor confidence evidence")
_CACHE = {}


def load(path=DEFAULT_PATH):
    """The rows in address order."""
    if path not in _CACHE:
        rows = []
        for line in open(path):
            if line.startswith("#") or not line.strip():
                continue
            lo, hi, *rest = line.rstrip("\n").split("\t")
            rows.append(Region(int(lo, 16), int(hi, 16), *rest))
        _CACHE[path] = rows
    return _CACHE[path]


def of(va, path=DEFAULT_PATH):
    """The row holding an address, or None outside the image."""
    rows = load(path)
    i = bisect.bisect_right([r.lo for r in rows], va) - 1
    if i >= 0 and va < rows[i].hi:
        return rows[i]
    return None


def named(region_id, path=DEFAULT_PATH):
    """The row with this id."""
    return next(r for r in load(path) if r.id == region_id)
