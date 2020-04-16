INSTALL RASPBIAN SQLITE TEST :
-----------------------------

First on Rapbian, connect to github and git clone this repository in your
/home/pi path.

$ cd /home/pi
$ git clone https://github.com/Costa83/db_test_raspbian.git
$ cd db_test_raspbian/sqlite/

Then follow the install.sh script

Or launch it with

$ chmod +x install.sh
$ ./install.sh

Do "CTRL+D" when sqlite prompt appear.


When you are in superuser mode after installation of lib by install.sh 
you have to enter the following commands :


$ make install
$ cd ..
$ chmod +x src/install.sh
$ cd src/
$ ./install.sh
$ cd ..

The executables for the testapp are in /home/pi/sqlite/bin now.

$ chmod +x script_test/test_X_rows.sh
$ cd script_test/
$ ./test_X_rows.sh



