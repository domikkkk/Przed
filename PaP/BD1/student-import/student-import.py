#!/bin/env python
import csv
import sys

import mysql.connector

data_file = sys.argv[1]
db_url = sys.argv[2]

db_connection = mysql.connector.connect(
    host=db_url,
    user="root",
    password="very_secure_password",
    database="db_example"
)

my_cursor = db_connection.cursor()

SQL_INSERT_QUERY = "INSERT INTO students\
             (indeks, birthdate, firstname, lastname, username)\
             VALUES (%s, %s, %s, %s, %s)"

SQL_FIND_IDX_QUERY = "SELECT MAX(indeks) FROM students"

with open(data_file, "r") as f:
    data = csv.reader(f, delimiter=";")
    next(data)  # skip the row with data labels

    my_cursor.execute(SQL_FIND_IDX_QUERY)
    index = my_cursor.fetchall()[0][0]
    index = index if type(index) is int else 0
    print(f"Max index in DB is {index}.")

    data_to_insert = []
    for row in data:
        index += 1
        new_row = [index] + row
        data_to_insert.append(new_row)

    my_cursor.executemany(SQL_INSERT_QUERY, data_to_insert)
    db_connection.commit()

print(f"Inserted {my_cursor.rowcount} rows of data")
