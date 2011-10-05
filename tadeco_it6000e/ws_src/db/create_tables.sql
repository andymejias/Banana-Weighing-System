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
	entry varchar(1000) not null,
	primary key (id),
	foreign key (type_id) references log_type(id)
)
engine innodb
comment 'log entries table';

create table records (
	id int not null auto_increment comment 'pk, record id',
	created date not null,
	farm_id int not null,
	parcel_id int not null,
	lot_id int not null,
	gang_id int not null,
	ribbon_id int not null,
	weigh_date date not null,
	weigh_time timestamp not null,
	weight int not null,
	primary key (id)
)
engine innodb
comment 'records'