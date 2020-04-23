#!/usr/bin/env python3

from influxdb import InfluxDBClient

from datetime import datetime
import uuid
import random
import time
import argparse


from influxdb import InfluxDBClient

from datetime import datetime
import uuid
import random
import time
import argparse

debug = True

start_time = time.time()

dbname = 'test_influxdb_python'
client = InfluxDBClient('localhost', 8086, 'admin', 'admin', dbname)

query_read = "delete from stt"

if debug :
    print("Delete data in database: " + dbname)

end_time = time.time()

if debug:
    print("Temps testDeleteAllRows : ")
    print(end_time-start_time)
