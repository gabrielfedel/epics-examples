require essioc

epicsEnvSet("AS_TOP", "$(E3_CMD_TOP)")
epicsEnvSet("IOCNAME", "TESTIOC")
epicsEnvSet("IOCDIR", "TESTIOC")
iocshLoad("$(essioc_DIR)/common_config.iocsh")

dbLoadDatabase("ai.db")
