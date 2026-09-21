# copy.db

An example showing how to copy an `waveform`/`aai` array using a single `aao` record. That is an alternative to copying using `acalcout` (see: `acalcout/cp_array.db`).

That uses a closed loop mechanism (OMSL and DOL).

## How to use:

Run IOC: 
```
iocsh copy.cmd
```

Monitor PVs:

```
$ pvmonitor test::PointsWav test::PointsAai  test::PointsFromWav test::PointsFromAai 
test::PointsWav     2026-09-21 11:06:55.378  [1,2]
test::PointsAai     2026-09-21 11:06:55.378  [3,4]
test::PointsFromWav 2026-09-21 11:06:55.381  [1,2]
test::PointsFromAai 2026-09-21 11:06:55.381  [3,4]
```

Change values of waveform/aai PVs:

```
$ pvput test::PointsAai "[5, 6, 7, 8]"
$ pvput test::PointsWav "[10,11,12,13]"
```

See that the update were done:

```
test::PointsAai     2026-09-21 11:07:32.560  [5,6,7,8]
test::PointsFromAai 2026-09-21 11:07:32.560  [5,6,7,8]
test::PointsWav     2026-09-21 11:08:08.848  [10,11,12,13]
test::PointsFromWav 2026-09-21 11:08:08.848  [10,11,12,13]
```