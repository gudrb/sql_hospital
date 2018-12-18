create database cheil_hospital;
drop database cheil_hospital;
use cheil_hospital;
SET SQL_SAFE_UPDATES = 0;

create table nulse(
nulse_ID int,
N_name varchar(20),
salary int,
age int,
room_num int,
primary key(nulse_ID));


create table hospital_room(
room_num int,
building varchar(20),
primary key(room_num));


insert into hospital_room values(101, '101동');
insert into hospital_room values(102, '101동');
insert into hospital_room values(201, '102동');
insert into hospital_room values(202, '102동');


create table patient(
patient_ID int,
P_name varchar(20),
sex varchar(5),
disease varchar(20),
age int,
primary key(patient_ID));

insert into patient values (2012112075, '조성재', 'M', 'cold', 25);
insert into patient values (2012112047, '김성현', 'M', 'allergy', 25);
insert into patient values (2012112048, '김호영', 'M', 'chest pain', 25);


create table doctor(
doctor_ID int,
D_name varchar(20),
salary int,
age int,
primary key(doctor_ID));

alter table doctor add dept_name varchar(20);   /*dept_name 속성 추가*/
alter table doctor add foreign key(dept_name) references department(dept_name); 

insert into doctor values (2013112075, 'u syhun', 7000, 28, 'internal medicine');
insert into doctor values (2013112047, 'easyhyun', 7500, 23, 'genral surgery');
insert into doctor values (2013112048, 'kimhyounggyu', 6700, 24, 'dentistry');
insert into doctor values (2013112049, 'kimshyoungguk', 6700, 24, 'dentistry');
insert into doctor values (2013112050, 'kimhyounsu', 6700, 24, 'dentistry');
insert into doctor values (2013112051, '김형관', 6700, 24, 'dentistry');
insert into doctor values (2013112052, '김형뀨', 6700, 24, 'dentistry');
delete from doctor ;
select *from doctor where salary > 6800;

select * from doctor where age = 23 and dept_name = 'genral surgery';
select D_name from doctor where salary > all(select salary from doctor where dept_name = 'dentistry');

select doctor_ID from doctor as D where age = 28 and salary = 7000 and 
exists(select * from treat as S where S.patient_ID = 2012112048 and doctor_ID = 2013112048);

create table department(
dept_name varchar(20),
budget int,
primary key(dept_name));

update department set budget = budget * 1.01 where budget < 110000;

insert into department values ('internal medicine', 100000);
insert into department values ('genral surgery', 120000);
insert into department values ('dentistry', 110000);

select *from department where budget > 105000;
select * from department natural join doctor;

select avg(department.budget) as avg_budget from department;

select dept_name from department where budget > all(select budget from department where dept_name = 'dentistry');

select dept_name, avg(salary) as avg_salary from doctor group by dept_name;

create table treat(
start_time int,
end_time int,
patient_ID int,
doctor_ID int);

insert into treat values(1, 2, 2012112075, 2013112075);
insert into treat values(2, 3, 2012112047, 2013112075);
insert into treat values(1, 2, 2012112048, 2013112048);

select *from treat natural join doctor;

select start_time from treat as START1 where patient_ID = 2012112075 and doctor_ID = 2013112075 and 
exists(select * from treat as END1 where patient_ID = 2012112048 and doctor_ID = 2013112048);


select start_time, end_time from treat where doctor_ID = 2013112075;


(select doctor_ID from doctor where salary = 7000) union (select doctor_ID from doctor where age = 28);

create table assigned_room(
start_date int,
end_date int,
patient_ID int,
room_num int);

insert into assigned_room values(0608, 0708, 2012112075, 101);

select start_date, end_date, room_num from assigned_room where patient_ID = 2012112075;


create table medical_certification(
inspection_bill int,
inspection_result varchar(20),
hospitalization_bills int,
patient_ID int);

insert into medical_certification values(2000, 'need treatment', 1000, 2012112075);

select inspection_result from medical_certification where patient_ID = 2012112075;

select inspection_bill from medical_certification where patient_ID = 2012112075;

select hospitalization_bills from medical_certification where patient_ID = 2012112075;



drop table nulse;    /*널스 테이블 전체 삭제*/
select *from nulse;   /*널스 값들 보기*/
describe nulse;       /*널스 속성 목록 보기*/
alter table nulse add foreign key(room_num) references hospital_room(room_num);

drop table patient;    /*널스 테이블 전체 삭제*/
select *from patient;   /*널스 값들 보기*/
describe patient;       /*널스 속성 목록 보기*/

drop table doctor;    /*널스 테이블 전체 삭제*/
select *from doctor;   /*널스 값들 보기*/
describe doctor;       /*널스 속성 목록 보기*/

drop table hospital_room;
select *from hospital_room;   /*널스 값들 보기*/
describe hospital_room;       /*널스 속성 목록 보기*/

drop table department;    /*널스 테이블 전체 삭제*/
select *from department;   /*널스 값들 보기*/
describe department;       /*널스 속성 목록 보기*/

drop table treat;    /*널스 테이블 전체 삭제*/
select *from treat;   /*널스 값들 보기*/
describe treat;       /*널스 속성 목록 보기*/
alter table treat add foreign key(patient_ID) references patient(patient_ID);
alter table treat add foreign key(doctor_ID) references doctor(doctor_ID);

drop table assigned_room;    /*널스 테이블 전체 삭제*/
select *from assigned_room;   /*널스 값들 보기*/
describe assigned_room;       /*널스 속성 목록 보기*/
alter table assigned_room add foreign key(patient_ID) references patient(patient_ID);
alter table assigned_room add foreign key(room_num) references hospital_room(room_num);

drop table medical_certification;    /*널스 테이블 전체 삭제*/
select *from medical_certification;   /*널스 값들 보기*/
describe medical_certification;       /*널스 속성 목록 보기*/
alter table medical_certification add foreign key(patient_ID) references patient(patient_ID);




drop procedure if exists dept_count_proc ; /*프로시져가 있다면 없앰*/
delimiter // /* 프로시저 만들기 전에 붙여줌*/

create procedure dept_count_proc(in temp varchar(20), out d_count integer) /*프로시져 만듬*/
begin
	select count(*) into d_count
	from doctor
	where doctor.dept_name = temp;
end // /*프로시져 끝 */

delimiter ;
call dept_count_proc('dentistry',@d_count);
select @d_count as result;

drop function if exists showtable;

delimiter $$ /*genral surgery 부서 에 있는 의사 이름 반환*/
create function showtable(doc_name varchar(20)) returns varchar(20) /*함수 만듬*/
begin
     declare copy_name varchar(20);
	select D_name into copy_name
    from doctor
    where dept_name = doc_name;
    return copy_name;
end $$
delimiter ;


select cheil_hospital.showtable('genral surgery'); /*함수 실행*/




/*create function showtable(d_name varchar(20)) returns doctor( 테이블은 만들 수 없음

    doctor_ID int,
	D_name varchar(20),
	salary int,
	age int,
    dept_name varchar(20))
    return table(
    select doctor_ID,D_name,salary,age,dept_name
    from doctor
    where doctor.dept_name = d_name);
    end $$*/
delimiter ;

delimiter &&

