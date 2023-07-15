create or replace trigger check_group_size
before insert or update on students_groups
for each ROW
declare
group_size study_groups.group_size%TYPE;
students_amount number;
begin
    select s.group_size
    into group_size
    from study_groups s
    where id = :new.id;
    
    select count(indeks)
    into students_amount
    from students_groups
    where id = :new.id;
    
    if students_amount + 1 > group_size then
        raise_application_error(-20101, 'Bla bla');
    end if;
end;


--INSERT INTO study_groups VALUES (500, 0, 12, 'z38', 'Poniedzialek', 103);
--
--INSERT INTO students_groups VALUES (108, 500);
--
--INSERT INTO study_groups VALUES (600, 1, 12, 'z38', 'Poniedzialek', 103);
--
--INSERT INTO students_groups VALUES (107, 600);
--
--INSERT INTO students_groups VALUES (108, 600);
--
--delete from students_groups where indeks = 108 and id = 200;
