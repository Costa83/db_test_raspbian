#!/usr/bin/env python3

from influxdb import InfluxDBClient

from datetime import datetime
import uuid
import random
import time
import argparse

#measuring the execution time of small code snippits
import timeit

debug = False
def testCreateInfluxDB(address='localhost'):

    dbname = 'test_influxdb_python'
    client = InfluxDBClient(address, 8086, 'admin', 'admin', dbname)

    if (debug) :
        print("Create database: " + dbname)

    client.create_database(dbname)

if __name__ == '__main__':
    address = 'localhost'
    print("Time to create_database: ")
    #print(timeit.timeit('testCreateInfluxDB(\"'.address.'\")', number=100)/100)
    print(timeit.timeit(setup="from __main__ import testCreateInfluxDB",stmt="testCreateInfluxDB('{}')".format(address), number=100)/100)
