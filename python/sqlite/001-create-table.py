# @page SQLite: CREATE DATABASE AND TABLE

# https://sqlitebrowser.org/
# https://habr.com/ru/articles/754400/

# How to execute the script:
# python.exe 001-crerate-table.py

import sqlite3;

# set connection with DB
connection = sqlite3.connect("my_database.db");
cursor     = connection.cursor();

# create table (if not exist)
cursor.execute('''
CREATE TABLE IF NOT EXISTS my_table 
(
  tag TEXT,
  ts  INTEGER,
  val INTEGER
)
''');

# the table fields:
# - tag - tag/variable name
# - ts  - timestamp
# - val - tag/variable value

# save changes and close connection
connection.commit();
connection.close();





