# @page SQLite: test

# https://sqlitebrowser.org/
# https://habr.com/ru/articles/754400/

import sqlite3;
import time;

# set connection with DB
connection = sqlite3.connect("my_database.db");
cursor     = connection.cursor();

val = 1;

# create table (if not exist)
cursor.execute('INSERT INTO my_table (ts, val) VALUES (?, ?)', (int(time.time()), val));

# save changes and close connection
connection.commit();
connection.close();





