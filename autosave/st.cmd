require autosave

epicsEnvSet("AS_TOP", "$(E3_CMD_TOP)")
epicsEnvSet("IOCNAME", "TESTIOC")
epicsEnvSet("SETTINGS_FILES","settings")
iocshLoad("$(autosave_DIR)/autosave.iocsh")

afterInit("fdbrestore("$(AS_TOP)/$(IOCNAME)/save/$(SETTINGS_FILES).sav")")

dbLoadDatabase("ai.db")
