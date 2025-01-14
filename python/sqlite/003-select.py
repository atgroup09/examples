# @page SQLite: test

# https://sqlitebrowser.org/
# https://habr.com/ru/articles/754400/

import sqlite3;
import time;

# set connection with DB
connection = sqlite3.connect("my_database.db");
cursor     = connection.cursor();

# select all data
cursor.execute('SELECT * FROM my_table');

# get result of SELECT as a list
result_list = cursor.fetchall();

# print result-list
for row in result_list:
  print(row);

# close connection
connection.close();
