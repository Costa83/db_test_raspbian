package influxdb

import (
    "github.com/influxdata/influxdb1-client/v2"
    "fmt"
)

func Read_one_row_database_influxdb(id_row string, IpAdress string, PortAddress string) {

  MyDB :=  "test_influxdb_go"
  Addr := "http://" + IpAdress + ":" + PortAddress


	c, err := client.NewHTTPClient(client.HTTPConfig{
		Addr: Addr,
	})
	if err != nil {
		fmt.Println("Error creating InfluxDB Client: ", err.Error())
	}
	defer c.Close()

  query_read := "select * from stt where id=" + id_row

	q := client.NewQuery(query_read, MyDB, "")

  response, err := c.Query(q)
  fmt.Println(response.Results)
}
