import csv
import glob
from epics import caput

def decomment(csvfile):
    for row in csvfile:
        raw = row.split('#')[0].strip()
        if raw: yield raw

prefix="TEST:"
file_names = glob.glob('*.csv')
for file_name in file_names:
    with open(file_name) as csvfile:
        reader = csv.reader(decomment(csvfile))
        rows1 = []
        rows2 = []
        for row in reader:
            rows1.append(float(row[0]))
            rows2.append(float(row[1]))

    caput(prefix + "Y", rows1)
    caput(prefix + "X", rows2)
