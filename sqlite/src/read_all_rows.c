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

	const char *dbpath = "test_sqlite.db";

	void *arg = NULL;

	db_connect(&arg, dbpath);
	db_init(arg);

	struct timespec gettime_start;
	clock_gettime(CLOCK_REALTIME, &gettime_start);

	int count_insert = 0;
	count_insert = db_one_row_read_all_test(arg);

	struct timespec gettime_after;
	clock_gettime(CLOCK_REALTIME, &gettime_after);
	if (gettime_after.tv_nsec > gettime_start.tv_nsec)
		printf("Read All Rows : Total time taken by CPU : %u.%u\n",
					gettime_after.tv_sec - gettime_start.tv_sec,
					gettime_after.tv_nsec - gettime_start.tv_nsec);
	else
		printf("Read All Rows : Total time taken by CPU : %u.%u\n",
					gettime_after.tv_sec - gettime_start.tv_sec + 1,
					gettime_start.tv_nsec - gettime_after.tv_nsec);

	db_disconnect(arg);
	return 0;
}
