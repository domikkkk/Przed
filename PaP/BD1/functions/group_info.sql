create or replace function group_info(gid number)
return varchar
as
sise number(10, 0);
gr_name varchar(255);
name varchar(255);
des varchar(255);
begin
select s.name, s.group_size, a.name, a.description
into gr_name, sise, name, des
from study_groups s
         join activity a on a.id = s.activity_id
where s.id = gid;

return 'grupa: ' || gr_name || '\nrozmiar: ' || sise || '\nnazwa: ' || name || '\nopis: ' || des;
end;
