import sys

import epics
import numpy as np

PVNAME="OCTOPUS:SavedWav"
FILEOUT="/tmp/savePV"

def savePV(pvname=None, value=None, char_value=None, timestamp=None, **kw):
    print("PV saved")
    sys.stdout.flush()
    with open(FILEOUT, "ab") as f:
        np.save(f, timestamp + value)

# need to set auto_monitor to work with large PVs
savPV = epics.PV(PVNAME, auto_monitor=True)
savPV.add_callback(savePV)

while True:
    epics.ca.poll(0.1)
