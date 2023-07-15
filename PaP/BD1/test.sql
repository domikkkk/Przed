select distinct s.firstname, s.lastname, a.name from students s
join students_groups g on s.indeks = g.indeks
join study_groups sg on g.id = sg.id
join activity a on a.id = sg.activity_id
where a.id = 103
order by s.lastname;

select distinct s.firstname, s.lastname, sg.name from students s
join students_groups g on s.indeks = g.indeks
join study_groups sg on sg.id = g.id
where sg.activity_id in (select id from activity where name like 'Projekt') and sg.name like 'z2';

select distinct s.firstname, s.lastname, sg.name from students s
join students_groups g on s.indeks = g.indeks
join study_groups sg on sg.id = g.id
where sg.activity_id in (select id from activity where name like 'Laboratoria');

select distinct s.firstname, s.lastname, sg.name from students s
join students_groups g on s.indeks = g.indeks
join study_groups sg on sg.id = g.id
where sg.activity_id in (select id from activity where name like 'Wyk³ad');

select a.name, case when tp.end_date is null then 'Nie ma wymian' else to_char(tp.end_date) end data_zak from activity a
left join trade_period tp on tp.activity_id = a.id
order by data_zak;

select distinct s.indeks, nvl(sum(g.result),0) from students s
left join grade g on g.indeks = s.indeks
group by s.indeks;

select firstname, lastname from students
where indeks in (select ss.indeks from students ss
                inner join grade g on g.indeks = ss.indeks);

select firstname, lastname from students
where indeks not in (select gg.indeks from grade gg);

