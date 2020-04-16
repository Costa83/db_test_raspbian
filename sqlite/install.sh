#!/bin/bash

echo 'Installing SQLITE tests for Raspbian'
echo 'Make sure you are in /home/pi path'
#Start the rpi with raspbian pre-installed on it (see RASPBIAN_BUILD install.sh)

echo 'Installation de SQLITE3 sur raspbian'
sudo apt-get install sqlite3
sqlite3

echo 'Installing SQLITE3 library'
git clone https://github.com/sqlite/sqlite.git
cd sqlite
./configure
make
ls -l .libs
sudo su
make install

echo 'Download des sources de test de sqlite'
git clone https://github.com/Costa83/db_test_raspbian.git
chmod +x src/install.sh
./src/install.sh

echo 'The executable for the testapp are in /home/pi/sqlite/bin'
chmod +x /script_test/test_X_rows.sh
./script_test/test_X_rows.sh


