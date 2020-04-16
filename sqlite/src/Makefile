CC = gcc
CFLAGS  = 
RM = rm
lIBPATH = -L/../libsqlite3
LIB = -lsqlite3
EXECUTABLES = sttTestInsertRowsSqlite sttTestReadRowSqlite sttTestReadAllRowsSqlite sttTestDeleteAllRowsSqlite sttTestDeleteRowsSqlite

all : sttTestInsertRowsSqlite sttTestReadRowSqlite sttTestReadAllRowsSqlite sttTestDeleteRowsSqlite sttTestDeleteAllRowsSqlite

sttTestInsertRowsSqlite: insert_rows.o sqlite_fonctions.o 
	$(CC) $(lIBPATH) -o sttTestInsertRowsSqlite insert_rows.o sqlite_fonctions.o $(LIB)

sttTestReadRowSqlite: read_rows.o sqlite_fonctions.o
	$(CC) $(lIBPATH) -o sttTestReadRowSqlite read_rows.o sqlite_fonctions.o $(LIB)

sttTestReadAllRowsSqlite: read_all_rows.o sqlite_fonctions.o
	$(CC) $(lIBPATH) -o sttTestReadAllRowsSqlite read_all_rows.o sqlite_fonctions.o $(LIB)

sttTestDeleteRowsSqlite: delete_rows.o sqlite_fonctions.o
	$(CC) $(lIBPATH) -o sttTestDeleteRowsSqlite delete_rows.o sqlite_fonctions.o $(LIB)

sttTestDeleteAllRowsSqlite: delete_all_rows.o sqlite_fonctions.o
	$(CC) $(lIBPATH) -o sttTestDeleteAllRowsSqlite delete_all_rows.o sqlite_fonctions.o $(LIB)

read_rows.o : read_rows.c db_fonctions.h
	$(CC) -o read_rows.o -c read_rows.c $(CFLAGS)

read_all_rows.o : read_all_rows.c db_fonctions.h
	$(CC) -o read_all_rows.o -c read_all_rows.c $(CFLAGS)

delete_rows.o : delete_rows.c db_fonctions.h
	$(CC) -o delete_rows.o -c delete_rows.c $(CFLAGS)

delete_all_rows.o : insert_rows.c db_fonctions.h
	$(CC) -o delete_all_rows.o -c delete_all_rows.c $(CFLAGS)

insert_rows.o : insert_rows.c db_fonctions.h
	$(CC) -o insert_rows.o -c insert_rows.c $(CFLAGS)

sqlite_fonctions.o : sqlite_fonctions.c db_fonctions.h
	$(CC) -o sqlite_fonctions.o -c sqlite_fonctions.c $(CFLAGS)
 
clean: 
	$(RM) $(EXECUTABLES) *.o 