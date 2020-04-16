#!/bin/bash

echo 'Installing SQLITE tests for Raspbian'
echo 'Make sure you are in /home/pi path and your have done '
echo '$ git clone https://github.com/Costa83/db_test_raspbian.git'
#Start the rpi with raspbian pre-installed on it (see RASPBIAN_BUILD install.sh)

echo 'Installation de SQLITE3 sur raspbian'
sudo apt-get install sqlite3
sqlite3

echo 'Installing SQLITE3 library'
git clone https://github.com/LuaDist/libsqlite3
cd libsqlite3
./configure
make
ls -l .libs
sudo su
make install

chmod +x src/install.sh
cd src/
./install.sh
cd ..

echo 'The executable for the testapp are in /home/pi/sqlite/bin'
chmod +x script_test/test_X_rows.sh
cd script_test/
./test_X_rows.sh


