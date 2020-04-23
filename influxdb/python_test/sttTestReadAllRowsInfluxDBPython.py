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

query_read = "select * from stt"

if debug :
    print("Create database: " + dbname)
    print("Querying data: " + query_read)


result = client.query(query_read)
print("Result: {0}".format(result))
end_time = time.time()

if debug:
    print("Temps testsReadAllRows : ")
    print(end_time-start_time)
