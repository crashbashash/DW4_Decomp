#!/usr/bin/env python3
"""Check the imported behavioral reference and, when present, its source tree."""
import hashlib
import json
from pathlib import Path

root = Path(__file__).resolve().parents[1]
manifest = json.loads((root / 'recovered/frontend/provenance.json').read_text())
for name, expected in manifest['sha256'].items():
    imported = (root / 'recovered/frontend' / name).read_bytes()
    assert hashlib.sha256(imported).hexdigest() == expected, f'{name}: imported reference changed'
    source = root.parent / 'recovered/frontend' / name
    if source.exists():
        assert source.read_bytes() == imported, f'{name}: differs from current decomp reference; review and re-import'
print('title reference: imported source hashes and available canonical source agree')
