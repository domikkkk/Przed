CREATE OR REPLACE PROCEDURE print_study_group_summary AS
BEGIN
  DBMS_OUTPUT.PUT_LINE('ID grupy, Nazwa, dzień tygodnia,rozmiar,procent wypełnienia');
  FOR rec IN (SELECT sg.id, sg.weekday, sg.name, sg.group_size, COUNT(ssg.indeks) AS student_count,
              ROUND(COUNT(ssg.indeks)/sg.group_size*100, 2) AS group_fill_percentage
              FROM study_groups sg
              JOIN students_groups ssg ON sg.id = ssg.id
              GROUP BY sg.weekday, sg.name, sg.group_size, sg.id)
  LOOP
            DBMS_OUTPUT.PUT_LINE(rec.id || '    ' || rec.name || '  ' || rec.weekday || '   ' || rec.group_size || '    ' || rec.student_count || ' ' || rec.group_fill_percentage || '%');
  END LOOP;
END;

--EXEC print_study_group_summary();
