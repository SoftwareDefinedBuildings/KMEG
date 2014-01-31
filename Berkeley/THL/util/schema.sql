-- DROP TABLE energy2;
CREATE TABLE `energy2` (
	`mid` INT,
	`eui64` CHAR(24), 
	`seqno` INT, 
	`inserttime` DOUBLE,
	`localtime` INT, 
	`globaltime` INT, 
	`period` INT, 
	`realenergy` BIGINT, 
	`realpower` INT, 
	`apparentpower` INT,
	PRIMARY KEY(mid, globaltime),
	KEY mid (mid),
	KEY index_readings_on_posix_timestamp(globaltime),
	KEY seqno(seqno)
) ENGINE=InnoDB DEFAULT CHARACTER SET utf8;
