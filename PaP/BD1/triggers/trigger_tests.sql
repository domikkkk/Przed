INSERT INTO study_groups VALUES (500, 0, 12, 'z38', 'Poniedzialek', 103);

INSERT INTO students_groups VALUES (108, 500);

INSERT INTO study_groups VALUES (600, 1, 12, 'z38', 'Poniedzialek', 103);

INSERT INTO students_groups VALUES (107, 600);

INSERT INTO students_groups VALUES (108, 600);

delete from students_groups where indeks = 108 and id = 200;
