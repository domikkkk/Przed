--dodawanie zaj??
INSERT INTO activity VALUES (101, 'p. 131', 'Wyk?ad', 0);
INSERT INTO activity VALUES (102, '', 'Laboratoria', 1);
INSERT INTO activity VALUES (103, '', 'Projekt', 1);

--dodawanie grup
INSERT INTO study_groups VALUES (101, 150, 12, 'Wyk?adowa', 'Wtorek', 101);

INSERT INTO study_groups VALUES (102, 15, 12, 'G1', 'Poniedzia?ek', 102);
INSERT INTO study_groups VALUES (103, 15, 12, 'G2', 'Poniedzia?ek', 102);

INSERT INTO study_groups VALUES (104, 15, 14, 'G3', 'Wtorek', 102);
INSERT INTO study_groups VALUES (105, 15, 14, 'G4', 'Wtorek', 102);

INSERT INTO study_groups VALUES (106, 15, 12, 'G5', '?roda', 102);
INSERT INTO study_groups VALUES (107, 15, 12, 'G6', '?roda', 102);

INSERT INTO study_groups VALUES (108, 15, 12, 'G7', 'Czwartek', 102);
INSERT INTO study_groups VALUES (109, 15, 12, 'G8', 'Czwartek', 102);

INSERT INTO study_groups VALUES (110, 15, 12, 'G9', 'Pi?tek', 102);
INSERT INTO study_groups VALUES (111, 15, 12, 'G10', 'Pi?tek', 102);

INSERT INTO study_groups VALUES (112, 4, 12, 'z1', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (113, 4, 12, 'z2', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (114, 4, 12, 'z3', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (115, 4, 12, 'z4', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (116, 4, 12, 'z5', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (117, 4, 12, 'z6', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (118, 4, 12, 'z7', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (119, 4, 12, 'z8', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (120, 4, 12, 'z9', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (121, 4, 12, 'z10', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (122, 4, 12, 'z11', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (123, 4, 12, 'z12', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (124, 4, 12, 'z13', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (125, 4, 12, 'z14', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (126, 4, 12, 'z15', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (127, 4, 12, 'z16', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (128, 4, 12, 'z17', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (129, 4, 12, 'z18', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (130, 4, 12, 'z19', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (131, 4, 12, 'z20', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (132, 4, 12, 'z21', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (133, 4, 12, 'z22', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (134, 4, 12, 'z23', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (135, 4, 12, 'z24', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (136, 4, 12, 'z25', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (137, 4, 12, 'z26', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (138, 4, 12, 'z27', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (139, 4, 12, 'z28', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (140, 4, 12, 'z29', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (141, 4, 12, 'z30', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (142, 4, 12, 'z31', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (143, 4, 12, 'z32', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (144, 4, 12, 'z33', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (145, 4, 12, 'z34', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (146, 4, 12, 'z35', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (147, 4, 12, 'z36', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (148, 4, 12, 'z37', 'Poniedzialek', 103);
INSERT INTO study_groups VALUES (149, 4, 12, 'z38', 'Poniedzialek', 103);

ALTER SESSION SET NLS_DATE_FORMAT = "DD/MM/YYYY";

-- dodawanie student?w
INSERT INTO students VALUES (101, '09/09/2004', 'Fedir', 'Tsupin', 'ftsupin');
INSERT INTO students VALUES (102, '12/12/2002', 'Dominik', 'Sidorczuk', 'dsidorcz');
INSERT INTO students VALUES (103, '05/10/2003', 'Krzysztof', 'Stawarski', 'kstawars');
INSERT INTO students VALUES (104, '12/02/2002', 'Tomasz', 'Sroka', 'tsroka');
INSERT INTO students VALUES (105, '01/01/2004', 'Maciej', 'Bie?kowski', 'mbienkow');
INSERT INTO students VALUES (106, '01/01/2004', 'Marta', 'Borek', 'mborek');
INSERT INTO students VALUES (107, '01/01/2004', 'Micha?', 'Ciupak', 'mciupak');
INSERT INTO students VALUES (108, '01/01/2004', 'Piotr', 'Grabowski', 'pgrabows');

--nauczyciele
INSERT INTO TEACHER VALUES (101, 'pmaciag', 'Piotr', 'Maciąg', 'dr inż.');


-- dodawanie grup do student?w
INSERT INTO students_groups VALUES (101, 101);
INSERT INTO students_groups VALUES (102, 101);
INSERT INTO students_groups VALUES (103, 101);
INSERT INTO students_groups VALUES (104, 101);
INSERT INTO students_groups VALUES (105, 101);
INSERT INTO students_groups VALUES (106, 101);
INSERT INTO students_groups VALUES (107, 101);
INSERT INTO students_groups VALUES (108, 101);
-- dodawanie lab
INSERT INTO students_groups VALUES (101, 102);
INSERT INTO students_groups VALUES (102, 103);
INSERT INTO students_groups VALUES (103, 104);
INSERT INTO students_groups VALUES (104, 105);
INSERT INTO students_groups VALUES (105, 106);
INSERT INTO students_groups VALUES (106, 107);
INSERT INTO students_groups VALUES (107, 108);
INSERT INTO students_groups VALUES (108, 109);
-- dodawanie projektu
INSERT INTO students_groups VALUES (101, 112);
INSERT INTO students_groups VALUES (102, 112);
INSERT INTO students_groups VALUES (103, 112);
INSERT INTO students_groups VALUES (104, 112);

INSERT INTO students_groups VALUES (105, 113);
INSERT INTO students_groups VALUES (106, 113);
INSERT INTO students_groups VALUES (107, 113);
INSERT INTO students_groups VALUES (108, 113);

-- dodawanie termin?w
INSERT INTO trade_period VALUES (101, '01/01/2024', '01/01/2023', 102);
INSERT INTO trade_period VALUES (102, '01/01/2024', '01/01/2023', 103);

-- dodawanie test?w
INSERT INTO graded_test VALUES (101, 'Kolos 1', 20, '26/01/2023', 101);
INSERT INTO graded_test VALUES (102, 'Kolos 2', 20, '27/01/2023', 101);
INSERT INTO graded_test VALUES (103, 'Sprawdzian 1', 5, '02/02/2023', 102);

-- dodawanie ocen
INSERT INTO grade VALUES (101, 15, 101, 101,101);
INSERT INTO grade VALUES (102, 10, 101, 102,101);
INSERT INTO grade VALUES (103, 20, 101, 103,101);
INSERT INTO grade VALUES (104, 15, 101, 104,101);
INSERT INTO grade VALUES (105, 5, 102, 101,101);
INSERT INTO grade VALUES (106, 10, 102, 102,101);
INSERT INTO grade VALUES (107, 2, 102, 103,101);
INSERT INTO grade VALUES (108, 13, 102, 104,101);
