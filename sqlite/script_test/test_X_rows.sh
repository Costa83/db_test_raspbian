#!/bin/sh

rm -rf sttTest*
cp ../bin/* .

echo "--- Test SQLITE DB  ---"
echo "--- Clean directory: rm test_sqlite.db"
rm test_sqlite.db
echo " "
echo "--- Enter the number of rows to insert :      --- "
read -p "-> " r
middle=$(( r / 2 ))
blast=$(( r - 1 ))
div_ten=$(( r / 10))

echo "--->1/12 Insertion de  $r lignes en BD             ---"
./sttTestInsertRowsSqlite -i $r

echo "--->2/12 Lecture de la premiere ligne en BD        ---"
./sttTestReadRowSqlite -r 1

echo "--->3/12 Lecture de la ligne $middle               ---"
./sttTestReadRowSqlite -r $middle

echo "--->4/12 Lecture de la ligne $blast                ---"
./sttTestReadRowSqlite -r $blast

echo "--->5/12 Lecture de toutes les lignes              ---"
./sttTestReadAllRowsSqlite

echo "--->6/12 Insertion de la ligne numero $div_ten     ---"
./sttTestInsertRowsSqlite -i $div_ten

echo "--->7/12 Suppression de la ligne numero $blast     ---"
./sttTestDeleteRowsSqlite -r $blast

echo "--->8/12 Suppression de la ligne du milieu $middle ---"
./sttTestDeleteRowsSqlite -r $middle

echo "--->9/12 Lecture de la ligne du milieu $middle     ---"
./sttTestReadRowSqlite -r $middle

echo "--->10/12 Lecture de toutes les lignes              ---"
./sttTestReadAllRowsSqlite

echo "--->11/12 Suppression de toutes les lignes          ---"
./sttTestDeleteAllRowsSqlite

echo "--->12/12 Lecture de toutes les lignes              ---"
./sttTestReadAllRowsSqlite
