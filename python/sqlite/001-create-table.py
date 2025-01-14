# @page SQLite: test

# https://sqlitebrowser.org/
# https://habr.com/ru/articles/754400/

import sqlite3;

# set connection with DB
connection = sqlite3.connect("my_database.db");
cursor     = connection.cursor();

# create table (if not exist)
cursor.execute('''
CREATE TABLE IF NOT EXISTS my_table 
(
  id  INTEGER PRIMARY KEY,
  ts  INTEGER,
  val INTEGER
)
''');

# save changes and close connection
connection.commit();
connection.close();





