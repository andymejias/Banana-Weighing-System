/**
 * sql script to create tables or mysql
 */

create table log_type (
	id int not null comment 'pk, log type id',
	description varchar(10) not null comment 'log type description',
	primary key (id),
	unique (description)
)
engine innodb
comment 'log types';

create table log (
	id int not null auto_increment comment 'pk, log id',
	type_id int not null comment 'fk, log_type.id',
	created date not null,
	entry varchar(4000) not null,
	primary key (id),
	foreign key (type_id) references log_type(id)
)
engine innodb
comment 'log entries table';

create table records (
	id int not null auto_increment comment 'pk, record id',
	created date not null,
	machine_id varchar(20) not null,
	record_id int not null,
	farm_id int not null,
	parcel_id int not null,
	lot_id int not null,
	gang_id int not null,
	ribbon_id int not null,
	age int not null,
	weigh_date date not null,
	weight decimal(12,6) not null,
	primary key (id)
)
engine innodb
comment 'records';

create table sampling (
	id int not null auto_increment,
	created date not null,
	machine_id varchar(20) not null,
	record_id int not null,
	bc	decimal(9,3) not null comment 'bunch calibration',
	fl decimal(9,3) not null comment 'finger length',
	nh decimal(9,3) not null comment 'number of hands',
	fc decimal(9,3) not null comment 'number of fingers',
	hc decimal(9,3) not null comment 'harvesting code'
	primary key (id)
)
engine innodb
comment 'sampling';
