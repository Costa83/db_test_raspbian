INSTALL RASPBIAN SQLITE TEST :
-----------------------------

First on Rapbian, connect to github and git clone this repository in your
/home/pi path.

Follow all this command in this order from /home/pi path.

$ cd /home/pi
$ git clone https://github.com/Costa83/db_test_raspbian.git
$ cd db_test_raspbian/sqlite/

$ sudo apt-get install sqlite3
$ sqlite3

$ git clone https://github.com/Costa83/libsqlite3.git
$ cd libsqlite3
$ ./configure
$ make
$ ls -l .libs
$ sudo su
$ make install
$ cd ..
$ chmod +x src/install.sh
$ cd src/
$ ./install.sh
$ cd ..

The executable for the testapp are in /home/pi/sqlite/bin

$ chmod +x script_test/test_X_rows.sh
$ cd script_test/
$ ./test_X_rows.sh

$ sudo cp /usr/local/lib/libsqlite3.so.0.8.6 /usr/lib/x86_64-linux-gnu/libsqlite3.so.0.8.6

