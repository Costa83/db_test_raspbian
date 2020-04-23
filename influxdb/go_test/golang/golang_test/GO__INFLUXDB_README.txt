INSTALL TESTS EN GO (INFLUXDB) sur  RASPBIAN HOST :

On est sur une architecture client-serveur où ici le client est la RPI et le serveur le PC Host.



## Prérequis 1 : Installer GRAFANA & INFLUXDB (CLIENT & SERVER) voir DOC ../

## Prérequis 2: Installer la commande go pour construire le package depuis RASPBIAN

Depuis le site officiel de go :

https://golang.org/dl/

Linux, macOS, and FreeBSD tarballs 
Download the archive and extract it into /usr/local, creating a Go tree in /usr/local/go. For example: 

go1.14.2.linux-arm64.tar.gz

$ sudo tar -C /usr/local -xzf go1.14.2.linux-arm64.tar.gz
$ export PATH=$PATH:/usr/local/go/bin
Pour pouvoir utiliser largement la commande go depuis tout le système :
$ gedit .bashrc
Et ajouter à la fin du fichier la ligne suivante:
export PATH=$PATH:/usr/local/go/bin


$ apt-get install golang



Créer un fichier hello.go contenant :
	package main

	import "fmt"

	func main() {
	        fmt.Printf("hello, world\n")
	}
$ go build hello.go
Cela génère un fichier hello executable que l’on peut lancer avec ./hello






Pour installer le package : Se procurer le dossier golang_test/ 
avec influxdb/
avec measuretime/
avec test/


Depuis le git clone :

?/influx_test/
		golang_test/
			influx_db/
			measure_time/
			test/





$ go mod init ../golang_test
$ go mod tidy

génère un go.mod et un go.sum

$ sudo cp -r influxdb /usr/local/go/src
$ sudo cp -r measuretime /usr/local/go/src

$ go build test/main.go 

génère main

On lance l’exécutable avec ./main et les options du programme :

./main --Points=10 --Ip=localhost –Port=8086

########## Test INFLUX DB in Go  ########################
--- Enter the IpAdress of rows to insert : --Ip=...
--- Enter the PortAddress of rows to insert : --Port=...
--- Enter the number of rows to insert : --Points=...
--- Enter the Middle of rows to insert : --Middle=...
--- Enter the Last of rows to insert : --Last=...
##########################################################


Dans un autre terminal on peut lancer:

$ influxdb

> show databases 

Permet de voir que la base de donnée test_inlfuxdb_go est bien crée.



HTTP::/


























Pour BR2 on fait pareil :

	On git clone le réperoire golang_test dans le répertoire qui est appelé par BR2 (APP EXTERNES).

Dans package/influx_db_golang/
	Création d’un Config.in
	Création d’un influx_db_go_test.mk





Pour développer en GO :

$ mkdir myproject
$ cd myproject
$ go mod init 
$ mkdir mypackage
$ créer .go
$ go mod tidy
(ou $ make influxdb_go_test create_database)
$ go build -o bin/ ./package
$ go build -o bin/ create_database/createdatabse_influxdb.go


#SUR BR2 :

Créer un répertoire influxdb_go dans package/

	Créer un .config
	Créer un .mk

#POUR RPI

Puis scp dans /usr/bin/ de la RPI de l’excutable.


Trois niveau : repository = ! modules, module!= direcrory, directory = package!= src files


Install go.1.14

$ go version

Go est un langage compilé qui n’a pas de dépendance une fois compilé pour fonctionner sur la cible.

1- Depuis le répertoire projet :
 
Pour activer la compilation croisée : il faut changer une variable d’environnement :

$ go tool dist list
$ GOOS=linux
$ GOARCH=amd64
$ go build -o ./bin./..

$ go build -o bin ./hello hello.go
 




$ go mod init
$ go mod tidy
$go mod 





## ETAPE 1: Installer InfluxDB en Go:

tar -C /usr/local -xzf go$VERSION.$OS-$ARCH.tar.gz

export PATH=$PATH:/usr/local/go/bin
