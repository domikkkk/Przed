create or replace procedure close_exchange(aid number)
as
cursor cr is select distinct(offers_id) from study_groups_offers
             where group_id in (select id from study_groups where activity_id = aid);
ofid number(10,0);
begin
update activity set student_can_trade=0 where id = aid;
open cr;
loop
exit when cr%notfound;
fetch cr into ofid;
delete from exchange_offer where ofid = id;
delete from study_groups_offers where ofid = offers_id;
end loop;
close cr;
end;
