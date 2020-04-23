package main

import (
    "fmt"
    "measuretime"
    "influxdb"
    "flag"
)


func main() {

  var IpAdress string
  var PortAddress string
  var Points string
  var Middle string
  var Last string


  fmt.Println("#########################################################")
  fmt.Println("########## Test INFLUX DB in Go  ########################")
  fmt.Println("--- Enter the IpAdress of rows to insert : --Ip=...")
  fmt.Println("--- Enter the PortAddress of rows to insert : --Port=...")
  fmt.Println("--- Enter the number of rows to insert : --Points=...")
  fmt.Println("--- Enter the Middle of rows to insert : --Middle=...")
  fmt.Println("--- Enter the Last of rows to insert : --Last=...")
  fmt.Println("##########################################################")


  flag.StringVar(&IpAdress, "Ip", "10.18.3.185", "A string var for connecting to ip")
  flag.StringVar(&PortAddress, "Port", "8086", "A string var for connecting to port")
  flag.StringVar(&Points, "Points", "10", "A string var for points to write")
  flag.StringVar(&Middle, "Middle", "5", "A string var for the middle point number")
  flag.StringVar(&Last, "Last", "9", "A string var for the Last point number")

  flag.Parse()

  fmt.Println("--->1/13 Creation de la base de donnee influxDB en Go   ")
  start1 :=  measuretime.Measuretime_start()
  influxdb.Create_database_influxdb(IpAdress, PortAddress)
  measuretime.Measuretime_stop(start1)

  fmt.Println("--->2/13 Ecriture de " + Points + "  rows en BD         ")
  start2 := measuretime.Measuretime_start()
  influxdb.Write_database_influxdb(&Points, &IpAdress, &PortAddress)
  measuretime.Measuretime_stop(start2)

  fmt.Println("--->3/13 Lecture de la première ligne en BD             ")
  start3 := measuretime.Measuretime_start()
  influxdb.Read_one_row_database_influxdb("1", IpAdress, PortAddress)
  measuretime.Measuretime_stop(start3)

  fmt.Println("--->4/13 Lecture de la ligne en milieu de BD            ")
  start4 := measuretime.Measuretime_start()
  influxdb.Read_one_row_database_influxdb(Middle, IpAdress, PortAddress)
  measuretime.Measuretime_stop(start4)

  fmt.Println("--->5/13 Lecture de la ligne dernière ligne en BD       ")
  start5 := measuretime.Measuretime_start()
  influxdb.Read_one_row_database_influxdb(Last, IpAdress, PortAddress)
  measuretime.Measuretime_stop(start5)

  fmt.Println("--->6/13 Lecture de toutes les lignes                   ")
  start6 := measuretime.Measuretime_start()
  influxdb.Read_all_rows_database_influxdb(IpAdress, PortAddress)
  measuretime.Measuretime_stop(start6)

  fmt.Println("--->7/13 Suppression de la dernière ligne numero" +  Last)
  start7 := measuretime.Measuretime_start()
  influxdb.Delete_one_row_database_influxdb(Last, IpAdress, PortAddress)
  measuretime.Measuretime_stop(start7)

  fmt.Println("--->8/13 Suppression de la ligne du milieu, numero : " + Middle)
  start8 := measuretime.Measuretime_start()
  influxdb.Delete_one_row_database_influxdb(Middle, IpAdress, PortAddress)
  measuretime.Measuretime_stop(start8)

  fmt.Println("--->9/13 Lecture de la ligne du milieu, numero : " + Middle)
  start9 := measuretime.Measuretime_start()
  influxdb.Read_one_row_database_influxdb(Middle, IpAdress, PortAddress)
  measuretime.Measuretime_stop(start9)

  fmt.Println("--->10/13 Lecture de toutes les lignes                  ")
  start10 := measuretime.Measuretime_start()
  influxdb.Read_all_rows_database_influxdb(IpAdress, PortAddress)
  measuretime.Measuretime_stop(start10)

  fmt.Println("--->11/13 Suppression de toutes les lignes              ")
  start11 := measuretime.Measuretime_start()
  influxdb.Delete_database_influxdb(IpAdress, PortAddress)
  measuretime.Measuretime_stop(start11)

  fmt.Println("--->12/13 Lecture de toutes les lignes                  ")
  start12 := measuretime.Measuretime_start()
  influxdb.Read_all_rows_database_influxdb(IpAdress, PortAddress)
  measuretime.Measuretime_stop(start12)

  fmt.Println("--->13/13 Suppresion de la database avec drop           ")
  start13 := measuretime.Measuretime_start()
  influxdb.Drop_database_influxdb(IpAdress, PortAddress)
  measuretime.Measuretime_stop(start13)


  fmt.Println("#########################################################")
  fmt.Println("#########################################################")
  fmt.Println("#########################################################")
  fmt.Println("")


}
