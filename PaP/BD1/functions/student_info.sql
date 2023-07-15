create or replace function student_info(sid number, grid number)
return VARCHAR
as
imie varchar(255);
nazwisko varchar(255);
result float;
ocena float;
gr3 float;
gr35 float;
gr4 float;
gr45 float;
gr5 float;
begin

select sum(g.result)
into result
from students s
join grade g on g.indeks = s.indeks
where g.indeks = sid
group by s.indeks;

select s.firstname, s.lastname
into imie, nazwisko
from students s
where s.indeks = sid;

select grade3, grade35, grade4, grade45, grade5
into gr3, gr35, gr4, gr45, gr5
from COURSE_SETTINGS
where id = grid;

if result < gr3 then
    ocena := 2;
elsif result < gr35 then
    ocena := 3;
elsif result < gr4 then
    ocena := 3.5;
elsif result < gr45 then
    ocena := 4;
elsif result < gr5 then
    ocena := 4.5;
else
    ocena := 5;
end if;

return imie || ' ' || nazwisko || ', ocena: ' || ocena || ', punkty: ' || result;
end;
