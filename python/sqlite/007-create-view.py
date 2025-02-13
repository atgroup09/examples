# @page SQLite: CREATE VIEW

# https://sqlitebrowser.org/
# https://habr.com/ru/articles/754400/

# How to execute the script:
# python.exe 007-crerate-view.py

import sqlite3;

# set connection with DB
connection = sqlite3.connect("my_database.db");
cursor     = connection.cursor();

# create view (if not exist)

cursor.execute('''
CREATE VIEW IF NOT EXISTS my_table_view 
AS SELECT res_main.tag AS tag, res_sub.val AS val, CURRENT_TIMESTAMP AS ts_curr, res_sub.ts AS ts, ((STRFTIME('%s',CURRENT_TIMESTAMP)-STRFTIME('%s',res_sub.ts))/3600) AS ts_delta_h, (((STRFTIME('%s',CURRENT_TIMESTAMP)-STRFTIME('%s',res_sub.ts))%3600)/60) AS ts_delta_m, (((STRFTIME('%s',CURRENT_TIMESTAMP)-STRFTIME('%s',res_sub.ts))%3600)%60) AS ts_delta_s FROM my_table AS res_main JOIN (SELECT tag, MAX(ts) AS ts, val FROM my_table GROUP BY tag) AS res_sub ON res_main.tag = res_sub.tag AND res_main.ts = res_sub.ts
''');

cursor.execute('''
CREATE VIEW IF NOT EXISTS my_table_view2 
AS SELECT tag, val, ts_curr, ts, CASE WHEN ts_delta_h > 10 THEN ('' || ts_delta_h) ELSE ('0' || ts_delta_h) END AS ts_delta_hf, CASE WHEN ts_delta_m > 10 THEN ('' || ts_delta_m) ELSE ('0' || ts_delta_m) END AS ts_delta_mf, CASE WHEN ts_delta_s > 10 THEN ('' || ts_delta_s) ELSE ('0' || ts_delta_s) END AS ts_delta_sf FROM my_table_view
''');

cursor.execute('''
CREATE VIEW IF NOT EXISTS my_table_view3 
AS SELECT tag, val, ts_curr, ts, ('' || ts_delta_hf || ':' || ts_delta_mf || ':' || ts_delta_sf) AS ts_delta FROM my_table_view2
''');

# save changes and close connection
connection.commit();
connection.close();





