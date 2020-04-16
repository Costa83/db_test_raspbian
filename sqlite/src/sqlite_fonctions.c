#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <sqlite3.h>

#include "sttData.h"
#include "db_fonctions.h"
#include "../log.h"

#define NB_TABLE_ANNEXES 3
#define NB_KEY 12
#define NB_UNITS 9
#define TIME_STRING_LENGTH 20

static int _db_insert_source(sqlite3 *db, const char *source);
static int _db_find_source(sqlite3 *db, const char *source);
static int _db_find_key(sqlite3 *db, const char *key);
static int _db_insert_key(sqlite3 *db, const char *key);
static int _db_find_unit(sqlite3 *db, const char *unit);
static int _db_insert_unit(sqlite3 *db, const char *unit);
static int _db_init(void *cbarg);

int callback(void *NotUsed, int argc, char **argv, char **azColName) {

	 dbg("Dossier : src/database - Fichier sqlite_fonctions.c  callback");

	 int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

/**Return -1 if there is a problem, 0 if succeeded**/
int db_connect(void **arg, const char *dbpath)
{
	dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_connect");

	struct timespec gettime_start;
	clock_gettime(CLOCK_REALTIME, &gettime_start);

	sqlite3 **argdb = (sqlite3 **)arg;
	int rc;

	int flags = SQLITE_OPEN_READWRITE;
	rc = sqlite3_open_v2(dbpath, argdb, flags, NULL);

	sqlite3 *db = *argdb;
	if(rc != 0)
	{
		int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
		rc = sqlite3_open_v2(dbpath, argdb, flags, NULL);

		if(rc != 0)
		{
			if (db != NULL)
				err("Can't open database: %s", sqlite3_errmsg(db));
			return -1;
		}
		db = *argdb;
		_db_init(db);
	}

	struct timespec gettime_after;
	clock_gettime(CLOCK_REALTIME, &gettime_after);

	if (gettime_after.tv_nsec > gettime_start.tv_nsec)
		printf("Connect Database :Total time taken by CPU : %u.%u\n",
					gettime_after.tv_sec - gettime_start.tv_sec,
					gettime_after.tv_nsec - gettime_start.tv_nsec);
	else
		printf("Connect Database :Total time taken by CPU : %u.%u\n",
					gettime_after.tv_sec - gettime_start.tv_sec + 1,
					gettime_start.tv_nsec - gettime_after.tv_nsec);


	return rc;
}

static int _db_init(void *cbarg)
{
	dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_init");

	sqlite3 *db = (sqlite3 *)cbarg;

	int rc;
	sqlite3_stmt *stmt;
	char *query = NULL;
	const char *Name_Table[NB_TABLE_ANNEXES];

	/**Create Tables Units, Source and Type**/
	Name_Table[0]="Units";
	Name_Table[1]="Source";
	Name_Table[2]="Key";
	
	int i=0;
	for(i=0; i<NB_TABLE_ANNEXES; i++)
	{
		if(asprintf(&query, "CREATE TABLE IF NOT EXISTS Table_%s(Id_%s INTEGER PRIMARY KEY,%s TEXT, UNIQUE(Id_%s, %s) );", Name_Table[i], Name_Table[i], Name_Table[i], Name_Table[i], Name_Table[i]) < 0)
			printf("error\n");

		sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE)
		{
			err("ERROR inserting data Table_%s: %s\n",Name_Table[i], sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			free(query);
			return -1;
		}
		sqlite3_finalize(stmt);
		free(query);
	}
	/**Create Table STT**/
	sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS STT(Id INTEGER PRIMARY KEY AUTOINCREMENT, Date INTEGER NOT NULL,Value REAL, Id_Source INTEGER, Id_Units INTEGER, Id_Key INTEGER );", -1, &stmt, NULL);
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		err("ERROR inserting data table STT: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return -1;
	}
	sqlite3_finalize(stmt);

	/**Fill the three tables UNITS, KEY and TYPE**/
	dbg("Create tables successfully\n");
	return rc;
}

int db_init(void *cbarg)
{
	int rc = 0;
	return rc;
}

void db_disconnect(void *cbarg) {

	dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_disconnect");
	sqlite3 *db = (sqlite3 *)cbarg;
	sqlite3_close(db);
}



int db_one_row_insert_test(void *cbarg, int count) {

  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_one_row_insert_test");

	sqlite3 *db = (sqlite3 *)cbarg;

	int rc;
	/** create sql request**/
	char *query = "insert into \"STT\" (\"Date\" ,\"Value\", \"Id_Source\", \"Id_Units\", \"Id_Key\") values(@mydate, @myvalue, @mysource, @myunit, @mykey);";
	sqlite3_stmt *stmt = NULL;
	char buffer [TIME_STRING_LENGTH];
	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		err("ERROR preparing data %p : %d\n", db, rc);
		sqlite3_finalize(stmt);
		return -1;
	}

  int	i_source = count % 3;
	int j_value = count % 12;


	double source_value[3][12] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
															 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
															 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} };

	char* unit_string[12] = { "km/h", "bpm", "Watts", "tpm", "km", "°C", "Kcal", "%", "D+", "m/s", "lux"};

  int source_unit[3][12] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
															 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
															 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} };

  char* key_string[12] = { "vitesse", "fréquence cardiaque", "Puissance développée", "Cadence de pédalage", "distance", "Température", "Dépense énergétique", "Pourcentage de pente", "Dénivelé positif", "Vitesse du vent", "Luminosité /panneau solaire"};

	int key_id[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

  int source_key[3][12] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
															 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
															 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} };

  int source_id[3] = { 1, 2, 3};

	char* source_string[3] = { "FAKE0", "FAKE1", "FAKE2"};

	struct timespec getdate;
  clock_gettime(CLOCK_REALTIME, &getdate);

	int date_integer = (int) getdate.tv_sec;

	dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_one_row_insert_test date_integer : %d", date_integer);

	int index;
	index = sqlite3_bind_parameter_index(stmt, "@mydate");
	rc = sqlite3_bind_int(stmt, index, date_integer);
	if (rc != SQLITE_OK)
	{
		err("ERROR binding data 1: %d\n", rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	/** Value **/
	index = sqlite3_bind_parameter_index(stmt, "@myvalue");
	rc=sqlite3_bind_double(stmt, index, source_value[i_source][j_value]);
	if (rc != SQLITE_OK)
	{
			err("ERROR binding data 2: %d\n", rc);
			sqlite3_finalize(stmt);
			return -1;
	}

	/** Source Id **/
	index = sqlite3_bind_parameter_index(stmt, "@mysource");
	rc = sqlite3_bind_int(stmt, index, source_id[i_source]);

	if (rc != SQLITE_OK)
	{
		err("ERROR binding data 3: %d\n", rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	index = sqlite3_bind_parameter_index(stmt, "@myunit");
	rc=sqlite3_bind_int(stmt,index,source_unit[i_source][j_value]);

	if (rc != SQLITE_OK)
	{
		err("ERROR binding data 4: %d\n", rc);
		sqlite3_finalize(stmt);
		return -1;
	}


	index = sqlite3_bind_parameter_index(stmt, "@mykey");
	rc=sqlite3_bind_int(stmt,index,source_key[i_source][j_value]);

	if (rc != SQLITE_OK)
	{
		err("ERROR binding data 5: %d\n", rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	/** Send Data **/
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		err("ERROR inserting data: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return -1;
	}
	sqlite3_reset(stmt);
	sqlite3_clear_bindings(stmt);
	sqlite3_finalize(stmt);

  count+=1;
	dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_one_row_insert_test count+1 : %d", count);
	return count;

}

int db_one_row_read_all_test(void *cbarg) {

  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_one_row_read_all_test");
	sqlite3 *db = (sqlite3 *)cbarg;

	char *query = "select * from STT;";
  char *zErrMsg = 0;
	const char* data = "Callback function called";
	int rc=0;
	rc = sqlite3_exec(db, query, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	else
	{
	  fprintf(stdout, "Operation done successfully\n");
	}

 	sqlite3_close(db);
	return 0;

}

int db_one_row_read_test(void *cbarg, int id_row) {

  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_one_row_read_test");
	sqlite3 *db = (sqlite3 *)cbarg;
	sqlite3_stmt *stmt = NULL;

  const char* data = "Callback function called";
	char *query;
	asprintf(&query, "select * from STT where Id=%d;", id_row);
	char *zErrMsg = 0;
	int rc=0;
	rc = sqlite3_exec(db, query, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
	  fprintf(stdout, "Operation done successfully\n");
	}

  free(query);
 	sqlite3_close(db);
	return 0;

}



int db_one_row_delete_test(void *cbarg, int id_row) {

  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_one_row_delete_test");

	sqlite3 *db = (sqlite3 *)cbarg;
	sqlite3_stmt *stmt = NULL;
  const char* data = "Callback function called";
	char *query;
	asprintf(&query, "delete from STT where Id=%d;", id_row);
	char *zErrMsg = 0;
	int rc=0;

	rc = sqlite3_exec(db, query, callback, (void*)data, &zErrMsg);
	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Operation done successfully\n");
	}

	free(query);
 	sqlite3_close(db);
	return 0;

}

int db_one_row_delete_all_test(void *cbarg) {

  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_one_row_delete_all_test");

	sqlite3 *db = (sqlite3 *)cbarg;
  const char* data = "Callback function called";
	char *query = "delete from STT;";
  char *zErrMsg = 0;
	int rc=0;

	rc = sqlite3_exec(db, query, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
	   fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   sqlite3_free(zErrMsg);
	}
	else
	{
	   fprintf(stdout, "Operation done successfully\n");
	}

 	sqlite3_close(db);
	return 0;
}

int db_drop_table_test(void *cbarg) {

  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_drop_table_test");

	sqlite3 *db = (sqlite3 *)cbarg;
  const char* data = "Callback function called";
	char *query = "drop table STT; drop table Table_Key; drop table Table_Source; drop table Table_Units;";
  char *zErrMsg = 0;
	int rc=0;

	rc = sqlite3_exec(db, query, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
	   fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   sqlite3_free(zErrMsg);
	}
	else
	{
	   fprintf(stdout, "Operation done successfully\n");
	}

 	sqlite3_close(db);
	return 0;
}


int db_insert(void *cbarg, struct sttdata *data1) {

  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_insert");

	struct timespec gettime_start;
  clock_gettime(CLOCK_REALTIME, &gettime_start);

	sqlite3 *db = (sqlite3 *)cbarg;
	const char *key[NB_KEY];
	const char *Names_Units[NB_UNITS];

	if (data1 == NULL) {
		return -1;
	}
	int rc;
	/** create sql request**/
	char *query = "insert into \"STT\" (\"Date\" ,\"Value\", \"Id_Source\", \"Id_Units\", \"Id_Key\") values(@mydate, @myvalue, @mysource, @myunit, @mykey);";
	sqlite3_stmt *stmt = NULL;
	char buffer [TIME_STRING_LENGTH];
	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		err("ERROR preparing data %p : %d\n", db, rc);
		sqlite3_finalize(stmt);
		return -1;
	}
	int index, i, j,k,l;

	for(i = 0; i < 3; i++)
	{

		for(j = 0; j < 12; j++)
		{

			if (data1->sensors[i].data[j].key != NULL)
			{
				/** Date and Time **/
				index = sqlite3_bind_parameter_index(stmt, "@mydate");
				rc = sqlite3_bind_int(stmt, index, data1->Date);
				if (rc != SQLITE_OK)
				{
					err("ERROR binding data 1: %d\n", rc);
					sqlite3_finalize(stmt);
					return -1;
				}

				/** Value **/
				index = sqlite3_bind_parameter_index(stmt, "@myvalue");
				rc=sqlite3_bind_double(stmt, index, data1->sensors[i].data[j].value);
				if (rc != SQLITE_OK)
				{
					err("ERROR binding data 2: %d\n", rc);
					sqlite3_finalize(stmt);
					return -1;
				}

				/** Source Id **/
				int sourceid = _db_find_source(db, data1->sensors[i].Source);
				if (sourceid == -1)
				{
					err("ERROR source unknown\n");
					sqlite3_finalize(stmt);
					return -1;
				}

				index = sqlite3_bind_parameter_index(stmt, "@mysource");
				rc=sqlite3_bind_int(stmt,index,sourceid);

				if (rc != SQLITE_OK)
				{
					err("ERROR binding data 3: %d\n", rc);
					sqlite3_finalize(stmt);
					return -1;
				}

				int unitid = _db_find_unit(db, data1->sensors[i].data[j].unit);
				if (unitid == -1)
				{
					err("ERROR id unit unknown\n");
					sqlite3_finalize(stmt);
					return -1;
				}

				index = sqlite3_bind_parameter_index(stmt, "@myunit");
				rc=sqlite3_bind_int(stmt,index,unitid);

				if (rc != SQLITE_OK)
				{
					err("ERROR binding data 4: %d\n", rc);
					sqlite3_finalize(stmt);
					return -1;
				}

				int keyid = _db_find_key(db, data1->sensors[i].data[j].key);
				if (keyid == -1)
				{
					err("ERROR key id unknown\n");
					sqlite3_finalize(stmt);
					return -1;
				}


				index = sqlite3_bind_parameter_index(stmt, "@mykey");
				rc=sqlite3_bind_int(stmt,index,keyid);

				if (rc != SQLITE_OK)
				{
					err("ERROR binding data 5: %d\n", rc);
					sqlite3_finalize(stmt);
					return -1;
				}

				/** Send Data **/
				rc = sqlite3_step(stmt);
				if (rc != SQLITE_DONE)
				{
					err("ERROR inserting data: %s\n", sqlite3_errmsg(db));
					sqlite3_finalize(stmt);
					return -1;
				}
				sqlite3_reset(stmt);
				sqlite3_clear_bindings(stmt);
			}
		}
	}
	sqlite3_finalize(stmt);
	struct timespec gettime_after;
	clock_gettime(CLOCK_REALTIME, &gettime_after);
	if (gettime_after.tv_nsec > gettime_start.tv_nsec)
		printf("Total time taken by CPU : %u.%u\n",
					gettime_after.tv_sec - gettime_start.tv_sec,
					gettime_after.tv_nsec - gettime_start.tv_nsec);
	else
		printf("Total time taken by CPU : %u.%u\n",
					gettime_after.tv_sec - gettime_start.tv_sec + 1,
					gettime_start.tv_nsec - gettime_after.tv_nsec);
}

static int _db_find_source(sqlite3 *db, const char *source) {


	dbg("*** Dossier : src/database - Fichier sqlite_fonctions.c  _db_find_source ::: %s", source);

	int sourceid = -1;
	if (source == NULL)
	{
		return -1;
	}

	int rc;
	char *query = "select Id_Source from Table_Source where Source=@Source";
	sqlite3_stmt *stmt = NULL;
	char buffer [TIME_STRING_LENGTH];

	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		err("ERROR preparing data %p : %d\n", db, rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	int index = sqlite3_bind_parameter_index(stmt, "@Source");
	rc=sqlite3_bind_text(stmt,index, source, -1 , SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW)
	{
		sourceid = sqlite3_column_int(stmt, 0);
		dbg("Dossier : src/database - Fichier sqlite_fonctions.c _db_find_source -> Already exist ");
	}
	else
	{
		dbg("Dossier : src/database - Fichier sqlite_fonctions.c _db_find_source -> Insert SOURCE ");
		sourceid = _db_insert_source(db, source);
	}
	sqlite3_finalize(stmt);
	return sourceid;
}


static int _db_insert_source(sqlite3 *db, const char *source)
{
	int sourceid = -1;
  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  _db_insert_source");

	if (source == NULL)
	{
		return -1;
	}

	int rc;
	char *query = "insert into \"Table_Source\" (\"Source\") values (@Source)";
	sqlite3_stmt *stmt = NULL;
	char buffer [TIME_STRING_LENGTH];

	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		err("ERROR preparing data %p : %d\n", db, rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	int index = sqlite3_bind_parameter_index(stmt, "@Source");
	rc=sqlite3_bind_text(stmt,index, source, -1 , SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE)
	{
		sourceid = sqlite3_last_insert_rowid(db);
	}
	sqlite3_finalize(stmt);
	return sourceid;
}

static int _db_find_key(sqlite3 *db, const char *key) {

	int keyid = -1;
  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  _db_find_keyid");

	if (key == NULL)
	{
		return -1;
	}

	char *query = "select Id_Key from Table_Key where Key=@Key";
	sqlite3_stmt *stmt = NULL;
	char buffer [TIME_STRING_LENGTH];

	int rc;
	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		err("ERROR preparing data %p : %d\n", db, rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	int index = sqlite3_bind_parameter_index(stmt, "@Key");
	rc=sqlite3_bind_text(stmt,index, key, -1 , SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW)
	{
		dbg("Dossier : src/database - Fichier sqlite_fonctions.c _db_find_key -> Already exist ");
		keyid = sqlite3_column_int(stmt, 0);
	}
	else
	{
		dbg("Dossier : src/database - Fichier sqlite_fonctions.c _db_find_key -> Insert new key ");
		keyid = _db_insert_key(db, key);
	}

	sqlite3_finalize(stmt);
	return keyid;
}


static int _db_insert_key(sqlite3 *db, const char *key)
{
	int keyid = -1;
  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  _db_insert_key");

	if (key == NULL)
	{
		return -1;
	}


	char *query = "insert into \"Table_Key\" (\"Key\") values (@Key)";
	sqlite3_stmt *stmt = NULL;
	char buffer [TIME_STRING_LENGTH];

	int rc;
	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		err("ERROR preparing data %p : %d\n", db, rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	int index = sqlite3_bind_parameter_index(stmt, "@Key");
	rc=sqlite3_bind_text(stmt,index, key, -1 , SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_DONE)
	{
		keyid = sqlite3_last_insert_rowid(db);
	}
	sqlite3_finalize(stmt);
	return keyid;
}


static int _db_find_unit(sqlite3 *db, const char *unit)
{
	int unitid = -1;
  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  _db_find_unit");

	if (unit == NULL)
	{
		return -1;
	}


	char *query = "select Id_Units from Table_Units where Units=@Unit";
	sqlite3_stmt *stmt = NULL;
	char buffer [TIME_STRING_LENGTH];

	int rc;
	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		err("ERROR preparing data %p : %d\n", db, rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	int index = sqlite3_bind_parameter_index(stmt, "@Unit");
	rc=sqlite3_bind_text(stmt,index, unit, -1 , SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW)
	{
		dbg("Dossier : src/database - Fichier sqlite_fonctions.c _db_find_unit -> Already exist ");
		unitid = sqlite3_column_int(stmt, 0);
	}
	else
	{
		dbg("Dossier : src/database - Fichier sqlite_fonctions.c _db_find_unit -> New Unit");
		unitid = _db_insert_unit(db, unit);
	}
	sqlite3_finalize(stmt);
	return unitid;
}


static int _db_insert_unit(sqlite3 *db, const char *unit)
{
	int unitid = -1;
  dbg("Dossier : src/database - Fichier sqlite_fonctions.c  _db_insert_unit");

	if (unit == NULL)
	{
		return -1;
	}

	char *query = "insert into \"Table_Units\" (\"Units\") values (@Unit)";


	sqlite3_stmt *stmt = NULL;
	char buffer [TIME_STRING_LENGTH];

	int rc;
	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		err("ERROR preparing data %p : %d\n", db, rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	int index = sqlite3_bind_parameter_index(stmt, "@Unit");
	rc=sqlite3_bind_text(stmt,index, unit, -1 , SQLITE_STATIC);
	rc = sqlite3_step(stmt);

	if (rc == SQLITE_DONE)
	{
		unitid = sqlite3_last_insert_rowid(db);
	}

	sqlite3_finalize(stmt);
	return unitid;
}


int db_print_db(void *cbarg)
{
	dbg("Dossier : src/database - Fichier sqlite_fonctions.c  db_print_db");

	sqlite3 *db = (sqlite3 *)cbarg;
	sqlite3_stmt *stmt = NULL;
	int rc;
	char * query = NULL;
	char *Name_Table[3];
	Name_Table[0]="Units";
	Name_Table[1]="Source";
	Name_Table[2]="Key";

	if (asprintf(&query, "select STT.Date, STT.Value, Table_%s.%s, Table_%s.%s, Table_%s.%s from STT inner join Table_%s on STT.Id_%s = Table_%s.Id_%s inner join Table_%s on STT.Id_%s = Table_%s.Id_%s"
		" inner join Table_%s on STT.Id_%s = Table_%s.Id_%s",Name_Table[0], Name_Table[0],Name_Table[1], Name_Table[1],Name_Table[2], Name_Table[2], Name_Table[0], Name_Table[0], Name_Table[0],
		Name_Table[0], Name_Table[1], Name_Table[1], Name_Table[1], Name_Table[1], Name_Table[2], Name_Table[2], Name_Table[2], Name_Table[2]) < 0)
		printf("error\n");

	rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		err("ERROR preparing data %p : %d\n", db, rc);
		sqlite3_finalize(stmt);
		return -1;
	}

	while((rc = sqlite3_step(stmt))==SQLITE_ROW)
	{
		time_t mtime = sqlite3_column_int(stmt, 0);
		char buffer[64];
		strftime(buffer, sizeof(buffer), "%d/%m/%Y %T", localtime(&mtime));
		printf("%s Source  %s %s %f %s \n", buffer, sqlite3_column_text(stmt, 3), sqlite3_column_text(stmt, 4), sqlite3_column_double(stmt, 1), sqlite3_column_text(stmt, 2));
	}

	sqlite3_finalize(stmt);
	free(query);
	return rc;
}
