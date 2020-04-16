#ifndef __DB_FONCTIONS_H__
#define __DB_FONCTIONS_H__

struct sttdata;

int db_connect(void **db, const char *dbpath);
int db_init(void *cbarg);
void db_disconnect(void * db);
int db_insert(void *cbarg, struct sttdata *data1);
int db_print_db(void * db);

/*Test function for Sqlite*/
int db_one_row_insert_test(void *cbarg, int count);
int db_one_row_read_all_test(void *cbarg);
int db_one_row_read_test(void *cbarg, int id_row);
int db_one_row_delete_test(void *cbarg, int id_row);
int db_one_row_delete_all_test(void *cbarg);
int db_drop_table_test(void *cbarg);


#endif
