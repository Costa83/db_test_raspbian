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

debug = False

def testDroptInfluxDB():

    dbname = 'test_influxdb_python'
    client = InfluxDBClient('localhost', 8086, 'admin', 'admin', dbname)

    if (debug) :
        print("Create database: " + dbname)

    client.create_database(dbname)

    if (debug) :
        print("Drop database: " + dbname)

    client.drop_database(dbname)

def main():
    if __name__ == '__main__':
        testDroptInfluxDB()

print("Time to drop empty InfluxDB database : " )
print(timeit.timeit(testDroptInfluxDB, number=100)/100)
