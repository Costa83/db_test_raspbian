#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#define HAVE_PWD_H
#ifdef HAVE_PWD_H
# include <pwd.h>
# include <grp.h>
#include <time.h>
#endif

#include "json_fonctions.h"
#include "sttData.h"
#include "db_fonctions.h"
#include "sensor_fonctions.h"
#include "../log.h"


int main(int argc, char *argv[]) {

	dbg("Dossier : src/database - Fichier main.c");

	struct passwd *user = NULL;
	struct group *grp = NULL;
	const char *socket_path = "muxsocketSTT";
	const char *directory = "/var/run/ouistiti";
	const char *dbpath = "test.db";
	const char *username = NULL;
	int c ;
	int fd;
	void *arg = NULL;

	do
	{
		c = getopt(argc, argv, "W:u:f:"); /**We added options to the program with ./myexample -W test1 **/
		switch (c)
		{
			case 'W':
				directory = optarg;
			break;
			case 'u':
				username  = optarg;
			break;
			case 'f':
				dbpath = optarg;
			break;
		}
	} while (c != -1);

	chdir(directory);
#ifdef HAVE_PWD_H
	if (username)
	{
		user = getpwnam(username);
		if (user == NULL)
		{
			fprintf(stderr, "Error: start as root\n");
			return -1;
		}
		grp = getgrgid(user->pw_gid);
		if (grp == NULL)
		{
			fprintf(stderr, "Error: start as root\n");
			return -1;
		}
	}
#endif
	db_connect(&arg, dbpath);
	db_init(arg);
	dbg("Dossier : src/database - Fichier main.c  sensor_connect");
	fd=sensor_connect(socket_path);
	int rc = 0;
	while(rc >= 0)
	{
		dbg("Dossier : src/database - Fichier main.c  while(rc>=1)");
		rc = sensor_recv(fd, db_insert , arg);
	}
	db_print_db(arg);
	dbg("Dossier : src/database - Fichier main.c  sensor_disconnect");
	sensor_disconnect(fd);
	db_disconnect(arg);
	return 0;
}
