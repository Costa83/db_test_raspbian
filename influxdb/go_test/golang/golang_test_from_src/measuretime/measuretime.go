package measuretime

import (
    "fmt"
    "strconv"
    "time"
)

func Measuretime_start() time.Time {
  start := time.Now()
  return start
}

func Measuretime_stop(start time.Time) {

  duration := time.Since(start)

  fmt.Println("-------------------- Temps d'Execution -------------------- ")

  nanoseconds := duration.Nanoseconds()%1000;
  microsecondes := (duration.Nanoseconds()/1000)%1000;
  millisecondes := (duration.Nanoseconds()/1000000)%1000;
  secondes := duration.Nanoseconds()/1000000000;

  fmt.Println("@... ")
  fmt.Println("#" + strconv.FormatInt(secondes,10) + "s:" + strconv.FormatInt(millisecondes,10) + "ms:" + strconv.FormatInt(microsecondes,10) + "us:" + strconv.FormatInt(nanoseconds,10) + "ns")
  fmt.Println("-------------------- -------------- -------------------- ")

}
