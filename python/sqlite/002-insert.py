# @page SQLite: INSERT

# https://sqlitebrowser.org/
# https://habr.com/ru/articles/754400/

# Insert value of the tag/variable with current time-stamp
# python.exe 002-insert.py <tag-name> <tag-value>

# Example:
# python.exe 002-insert.py A1 1

import sys;
import sqlite3;
import time;

# test input arguments
# arg0 - the script name
# arg1 - tag/variable name
# arg2 - tag/variable value
if len(sys.argv) < 3:
    print("Error! Incompleted input arguments.");
    quit();

# set connection with DB
connection = sqlite3.connect("my_database.db");
cursor     = connection.cursor();

tag = sys.argv[1];
val = sys.argv[2];

# insert row into the table
cursor.execute('INSERT INTO my_table (tag, ts, val) VALUES (?, CURRENT_TIMESTAMP, ?)', (tag, val));

# save changes
connection.commit();

# close connection
connection.close();
