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

#include "sttData.h"
#include "db_fonctions.h"
#include "../log.h"

int main(int argc, char *argv[]) {

	dbg("Dossier : src/database - Fichier insert_rows.c");

	const char *dbpath = "test_sqlite.db";
	int c ;
	int nb_rows;

	do
	{
		c = getopt(argc, argv, "i:");
		switch (c)
		{
			case 'i':
				nb_rows = optarg;
			break;
	 }

 int index;
 for ( index = optind; index < argc; index++ )
	 printf ("Non-option argument %s\n", argv[index]);

	} while (c != -1);

	void *arg = NULL;
	db_connect(&arg, dbpath);
	db_init(arg);

	int max_row = atoi(nb_rows);
	dbg("Dossier : src/database - Fichier main.c  max_row : %d", max_row);


	struct timespec gettime_start;
  clock_gettime(CLOCK_REALTIME, &gettime_start);

	int count_insert = 0;
	while ( count_insert < max_row )
	{
		count_insert = db_one_row_insert_test(arg, count_insert);
	}

	struct timespec gettime_after;
	clock_gettime(CLOCK_REALTIME, &gettime_after);
	if (gettime_after.tv_nsec > gettime_start.tv_nsec)
		printf("Insert Rows :Total time taken by CPU : %u.%u\n",
					gettime_after.tv_sec - gettime_start.tv_sec,
					gettime_after.tv_nsec - gettime_start.tv_nsec);
	else
		printf("Insert Rows :Total time taken by CPU : %u.%u\n",
					gettime_after.tv_sec - gettime_start.tv_sec + 1,
					gettime_start.tv_nsec - gettime_after.tv_nsec);

	db_disconnect(arg);
	return 0;
}
