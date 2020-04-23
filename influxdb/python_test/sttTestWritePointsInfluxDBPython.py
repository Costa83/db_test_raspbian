#!/usr/bin/env python3

from influxdb import InfluxDBClient

from datetime import datetime
import uuid
import random
import time
import argparse
import timeit


debug = True

def write_point(points) :

    database_name="test_influxdb_python"
    start_time = time.time()
    client = InfluxDBClient("localhost", 8086)
    client.create_database(database_name)

    measurement_name = "stt"

    number_of_points = points

    source_tags = [ "FAKE0",
    "FAKE1",
    "FAKE2"]

    type_tags = [ "Puissance",
    "Vitesse",
    "Denivele",
    "Calories",
    "Distance"]

    unit_tags = [ "Watts",
    "km_h",
    "m",
    "Kcal",
    "km"]

    id_tags = []
    for i in range(0,number_of_points,1):
        id_tags.append(i)

    data = []
    for i in range(number_of_points):

        data_end_time = int(time.time() * 1000000 + i)
        if i%5 == 0:
            value=random.randint(90,400)
        elif (i%5 == 1) :
            value=random.randint(9,40)
        elif (i%5 == 2) :
            value=random.randint(0,2880)
        elif (i%5 == 3) :
            value=random.randint(0,7100)
        elif (i%5 == 4) :
            value=random.randint(0,300)


        data.append("{measurement},source={source},type={type},unit={unit} id={id},value={value} {timestamp}"
                    .format(measurement=measurement_name,
                            source=source_tags[i%3],
                            type=type_tags[i%5],
                            unit=unit_tags[i%5],
                            id=i,
                            value=value,
                            timestamp=data_end_time))

    client.write_points(data, database=database_name, time_precision='n', batch_size=10000, protocol='line')

    end_time = time.time()

    if debug:
        print("Temps testsWritePoints : ")
        print(end_time-start_time)


def parse_args():
        """Parse the args."""
        parser = argparse.ArgumentParser(
            description='InfluxDB Pyhton Test')

        parser.add_argument('--points', type=int, required=False, default=10,
                            help='points of InfluxDB ')

        return parser.parse_args()

if __name__ =="__main__":
    args=parse_args()
    write_point(args.points)
