createdb bankdb

psql bankdb

create table branch (
	branch_no int primary key,
	branch_name varchar(20) not null,
	branch_city varchar(20) not null 
);

create table account (
	account_no int primary key,
	account_type varchar(7) not null check (account_type in ('current', 'savings')),
	branch_no int not null references branch (branch_no),
	balance real not null check (balance >= 0)
);

create table customer (
	cust_id int primary key,
	cust_name varchar(50) not null,
	cust_city varchar(20) not null,
	account_no int not null references account (account_no)
);

copy branch from '/home/tiwari-s/Desktop/LabWork/ADBMS/branchdata.csv' delimiter ',';

copy account from '/home/tiwari-s/Desktop/LabWork/ADBMS/accountdata.csv' delimiter ',';

copy customer from '/home/tiwari-s/Desktop/LabWork/ADBMS/customerdata.csv' delimiter ',';

--Names of customers whose city and branch city is same
select cust_name 
from customer, account, branch 
where customer.account_no = account.account_no and 
	account.branch_no = branch.branch_no and
	customer.cust_city = branch.branch_city;
--or
select cust_name 
from customer natural join (account natural join branch)
where cust_city = branch_city;

--Update the table account; if balance < 1000, make it 1500
update account
set balance = 1500
where balance < 1000;

--Names of customers whose account is of type 'current'
select cust_name
from customer natural join account
where account_type='current';

--Find number of customers for each type of account
select account_type, count(*)
from customer natural join account
group by account_type;

--Name of branch and customer city where balance > 20000
select branch_name, cust_city
from customer natural join (account natural join branch)
where balance>20000;