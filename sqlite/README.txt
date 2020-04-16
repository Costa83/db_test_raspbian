INSTALL RASPBIAN SQLITE TEST :
-----------------------------
Copier le dossier "test_sqlite_raspbian" suivant dans /home/pi/

Installation de SQLITE3 : 
---------------------------
$ sudo apt-get install sqlite3
$ sqlite3                         -> pour vérifier que c'est bien installé

Installation de la librairie SQLITE3
-------------------------------------
$ git clone sqlite3 (dans le répertoire au niveau du répertoire des src)
$ cd sqlite3
$ ./configure
$ make
$ ls -l .libs                     -> pour vérifier que c'est bien installé
$ sudo su
$ make install


Compilation des src et installation des fichiers binaires nécessaires au test de sqlite:
----------------------------------------------------------------------------------------
$ cd src 
$ chmod +x install.sh
$ ./install.sh

Les executables sont installés dans /home/pi/test_sqlite_raspbian/bin


Lancement du script de test :
------------------------------

$ cd ../script_test/
$ chmod +x test_X_rows.sh
$ ./test_X_rows 


