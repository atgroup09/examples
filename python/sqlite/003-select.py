# @page SQLite: SELECT

# https://sqlitebrowser.org/
# https://habr.com/ru/articles/754400/

# Select all rows and all fields from the database table
# python.exe 003-select.py

# Example:
# python.exe 003-select.py

import sqlite3;
import time;

# set connection with DB
connection = sqlite3.connect("my_database.db");
cursor     = connection.cursor();

# select data from the database table
cursor.execute('SELECT * FROM my_table');

# copy read rows into result-list
result = cursor.fetchall();

# print the result
for row in result:
    print(row);

# close connection
connection.close();
