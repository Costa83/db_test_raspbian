package influxdb

import (
    "github.com/influxdata/influxdb1-client/v2"
    "fmt"
)

func Drop_database_influxdb(IpAdress string, PortAddress string) {

  MyDB :=  "test_influxdb_go"
  Addr := "http://" + IpAdress + ":" + PortAddress

	c, err := client.NewHTTPClient(client.HTTPConfig{
		Addr: Addr,
	})
	if err != nil {
		fmt.Println("Error creating InfluxDB Client: ", err.Error())
	}
	defer c.Close()


  query_drop := "drop database test_influxdb_go"


	q := client.NewQuery(query_drop, MyDB, "")

  response, err := c.Query(q)
  fmt.Println(response.Results)

}
