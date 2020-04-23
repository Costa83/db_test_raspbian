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

#measuring the execution time of small code snippits
import timeit

debug = True

start_time = time.time()
dbname="test_influxdb_python"
client = InfluxDBClient("localhost", 8086)


client.drop_database(dbname)
end_time = time.time()

if debug:
    print("Temps testsWritePoints : ")
    print(end_time-start_time)
