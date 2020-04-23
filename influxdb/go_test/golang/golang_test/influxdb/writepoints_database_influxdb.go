package influxdb

import (
    "github.com/influxdata/influxdb1-client/v2"
    "fmt"
    "strconv"
    "time"
    "math/rand"
)



func Write_database_influxdb(nb_row *string, IpAdress *string, PortAddress *string){

    source_tags := [3]string{"FAKE0","FAKE1","FAKE2"}
    type_tags := [5]string{"Puissance","Vitesse","Denivele","Calories","Distance"}
    unit_tags := [5]string{"Watts","km_h","m","Kcal","km"}

    MyDB :=  "test_influxdb_go"
    Addr := "http://" + *IpAdress + ":" + *PortAddress

    c, err := client.NewHTTPClient(client.HTTPConfig{
    Addr: Addr,

  })

  if err != nil {
    fmt.Println("Error creating InfluxDB Client: ", err.Error())
  }
  defer c.Close()

  nb_row_int, err := strconv.Atoi(*nb_row)
  for i:=0;i<(nb_row_int);i++ {
      bp, _ := client.NewBatchPoints(client.BatchPointsConfig{
  		Database: MyDB,
  	 })

     tags := map[string]string{"source": source_tags[i%3],"type":type_tags[i%5], "unit":unit_tags[i%5], "idtag":strconv.Itoa(i)}
	   fields := map[string]interface{}{
  	 	"value": rand.Intn(1000),
      "id": i,
	   }

     now :=  time.Now()
     measurement := "stt"
     pt, err := client.NewPoint(measurement, tags, fields, now)
     if err != nil {
         	fmt.Println("Error: ", err.Error())
     }
     bp.AddPoint(pt)
     c.Write(bp)
  }

}
