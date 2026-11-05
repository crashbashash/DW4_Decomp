#!/usr/bin/env python3
"""Compare bank waveforms with the user's 2026-10-10 06-35-25 PCSX2 capture.
Requires ffmpeg, numpy and scipy. Keeps all extracted game audio in a temp directory.
This verifies cue identity/rate in the recording, not native event scheduling/gain.
"""
import argparse
from pathlib import Path
import subprocess
import tempfile

import numpy as np
from scipy import signal
from scipy.io import wavfile

PORT = Path(__file__).resolve().parent.parent
CUES = (
    ('CURSOR_START', 805, 1, 2, (2.0524, 4.1075, 16.1024)),
    ('CURSOR_DECIDE', 897, 0, 29, (9.1275, 10.7475, 12.0975, 12.7625, 13.4675, 14.2175)),
    ('WINDOW_OPEN', 897, 0, 24, (7.6275, 11.2976, 12.9475, 14.8175)),
    ('WINDOW_CLOSE', 897, 0, 25, (11.1475, 14.7175)),
)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('capture', type=Path)
    ap.add_argument('--roms', type=Path, default=PORT.parent.parent / 'local/extracted')
    opts = ap.parse_args()
    rate = 24000
    sos = signal.butter(3, 700, fs=rate, btype='highpass', output='sos')
    with tempfile.TemporaryDirectory(prefix='dw4-menu-capture-') as directory:
        temp = Path(directory)
        raw = temp / 'capture.pcm'
        subprocess.run(['ffmpeg', '-v', 'error', '-i', str(opts.capture), '-map', '0:a:0',
                        '-ac', '1', '-ar', str(rate), '-f', 's16le', str(raw)], check=True)
        y = signal.sosfilt(sos, np.fromfile(raw, dtype='<i2').astype(float))
        for name, entry, bank, wave, times in CUES:
            wav = temp / 'cue.wav'
            subprocess.run([str(PORT / 'build/dw4asset'), 'sfp', '--afs',
                            str(opts.roms / 'NDMW.AFS'), '--entry', str(entry),
                            '--bank', str(bank), '--sound', str(wave), '--wav', str(wav)],
                           check=True, capture_output=True)
            sr, x = wavfile.read(wav)
            assert sr == rate
            z = signal.sosfilt(sos, x.astype(float))[:rate // 10]
            z -= z.mean()
            c = signal.correlate(y, z, mode='valid', method='fft')
            energy = signal.convolve(y*y, np.ones(len(z)), mode='valid', method='fft')
            correlation = c / np.sqrt(np.maximum(energy, 1) * np.dot(z, z))
            scores = []
            for time in times:
                lo, hi = int((time - .015)*rate), int((time + .015)*rate)
                score = correlation[lo:hi].max()
                assert score > .8, f'{name} at {time}: {score:.3f}'
                scores.append(score)
            print(f'{name}: {len(times)} occurrences, minimum correlation {min(scores):.3f}')
    print('PCSX2 capture: 15 authored cues match bank waveforms at their stored 24 kHz rate')


if __name__ == '__main__':
    main()
