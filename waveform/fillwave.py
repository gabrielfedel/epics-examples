import epics

# values
vals=[1,2,3,4,5,6]

# set values
epics.caput("WAVE", vals)

#read values
print(epics.caget("WAVE"))
