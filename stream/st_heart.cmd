require stream

drvAsynIPPortConfigure("TEST",     "127.0.0.1:12222", 0,0,1)

dbLoadRecords("heart.db","P=GSF:,PORT=TEST")
