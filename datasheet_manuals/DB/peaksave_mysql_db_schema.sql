# --------------------------------------------------------
# Host:                         114.207.113.78
# Database:                     PEAKSAVE
# Server version:               5.1.61
# Server OS:                    redhat-linux-gnu
# HeidiSQL version:             5.0.0.3272
# Date/time:                    2012-08-10 22:03:15
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
# Dumping database structure for PEAKSAVE
CREATE DATABASE IF NOT EXISTS `PEAKSAVE` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `PEAKSAVE`;


# Dumping structure for table PEAKSAVE.apiAAN
CREATE TABLE IF NOT EXISTS `apiAAN` (
  `code` int(11) NOT NULL AUTO_INCREMENT,
  `akey` varchar(30) COLLATE utf8_bin DEFAULT NULL,
  `server` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `site` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`code`),
  KEY `key` (`akey`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin ROW_FORMAT=DYNAMIC;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.apiDeviceinfo
CREATE TABLE IF NOT EXISTS `apiDeviceinfo` (
  `uid` varchar(20) COLLATE utf8_bin NOT NULL DEFAULT '0',
  `node` int(10) unsigned DEFAULT NULL,
  `server` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `site` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `type` varchar(20) COLLATE utf8_bin DEFAULT NULL,
  `name` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `en_name` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `state` char(5) COLLATE utf8_bin DEFAULT NULL,
  `memo` text COLLATE utf8_bin,
  `regdate` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.CO2_DAVG
CREATE TABLE IF NOT EXISTS `CO2_DAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` date DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` double DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.CO2_HISTORY
CREATE TABLE IF NOT EXISTS `CO2_HISTORY` (
  `code` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `nodeid` int(10) unsigned DEFAULT '0',
  `seq` int(10) unsigned DEFAULT '0',
  `serialNumber` varchar(50) DEFAULT '0',
  `CO2` float unsigned DEFAULT '0',
  `battery` int(10) unsigned DEFAULT '0',
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`code`),
  KEY `nodeid` (`nodeid`),
  KEY `regdate` (`regdate`),
  KEY `code` (`code`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.CO2_TAVG
CREATE TABLE IF NOT EXISTS `CO2_TAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` datetime DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` double DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.CO2_UPDATE
CREATE TABLE IF NOT EXISTS `CO2_UPDATE` (
  `nodeid` int(10) unsigned NOT NULL DEFAULT '0',
  `seq` int(10) unsigned DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `co2` float unsigned DEFAULT NULL,
  `battery` int(10) unsigned DEFAULT NULL,
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`nodeid`),
  KEY `seq` (`seq`),
  KEY `regdate` (`regdate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.db_connect_history
CREATE TABLE IF NOT EXISTS `db_connect_history` (
  `code` int(10) NOT NULL AUTO_INCREMENT,
  `akey` varchar(30) DEFAULT NULL,
  `app` varchar(20) DEFAULT NULL,
  `info` text,
  `ip` varchar(30) DEFAULT NULL,
  `mac` varchar(30) DEFAULT NULL,
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`code`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.ETYPE_DAVG
CREATE TABLE IF NOT EXISTS `ETYPE_DAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` date DEFAULT NULL COMMENT '날짜',
  `serialNumber` varchar(50) DEFAULT NULL COMMENT '시리얼',
  `data` double DEFAULT NULL COMMENT '평균값',
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.ETYPE_TAVG
CREATE TABLE IF NOT EXISTS `ETYPE_TAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` datetime DEFAULT NULL COMMENT '날짜 시간',
  `serialNumber` varchar(50) DEFAULT NULL COMMENT '시리얼',
  `data` double DEFAULT NULL COMMENT '평균값',
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.ETYPE_UPDATE
CREATE TABLE IF NOT EXISTS `ETYPE_UPDATE` (
  `nodeid` int(10) unsigned NOT NULL DEFAULT '0',
  `seq` int(10) unsigned DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `validCurrent` float unsigned DEFAULT NULL,
  `t_validCurrent` int(10) unsigned DEFAULT NULL,
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`nodeid`),
  KEY `seq` (`seq`),
  KEY `regdate` (`regdate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.HUMIDITY_DAVG
CREATE TABLE IF NOT EXISTS `HUMIDITY_DAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` date DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` float unsigned DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.HUMIDITY_TAVG
CREATE TABLE IF NOT EXISTS `HUMIDITY_TAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` datetime DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` float unsigned DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.HUMIDITY_UPDATE
CREATE TABLE IF NOT EXISTS `HUMIDITY_UPDATE` (
  `nodeid` int(10) unsigned NOT NULL DEFAULT '0',
  `seq` int(10) unsigned DEFAULT '0',
  `serialNumber` varchar(50) DEFAULT '0',
  `humidity` float unsigned DEFAULT '0',
  `battery` int(10) unsigned DEFAULT '0',
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`nodeid`),
  KEY `seq` (`seq`),
  KEY `regdate` (`regdate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.LUX_DAVG
CREATE TABLE IF NOT EXISTS `LUX_DAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` date DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` float unsigned DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.LUX_TAVG
CREATE TABLE IF NOT EXISTS `LUX_TAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` datetime DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` float unsigned DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.LUX_UPDATE
CREATE TABLE IF NOT EXISTS `LUX_UPDATE` (
  `nodeid` int(10) unsigned NOT NULL DEFAULT '0',
  `seq` int(10) unsigned DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `lux` float unsigned DEFAULT NULL,
  `battery` int(10) unsigned DEFAULT NULL,
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`nodeid`),
  KEY `regdate` (`regdate`),
  KEY `seq` (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.PIR_DAVG
CREATE TABLE IF NOT EXISTS `PIR_DAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` date DEFAULT NULL COMMENT '날짜',
  `serialNumber` varchar(50) DEFAULT NULL COMMENT '시리얼',
  `data` int(10) unsigned DEFAULT NULL COMMENT '빈도',
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.PIR_HISTORY
CREATE TABLE IF NOT EXISTS `PIR_HISTORY` (
  `code` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `nodeid` int(10) unsigned DEFAULT NULL,
  `seq` int(10) unsigned DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `pir` int(10) unsigned DEFAULT NULL,
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`code`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.PIR_TAVG
CREATE TABLE IF NOT EXISTS `PIR_TAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` datetime DEFAULT NULL COMMENT '날짜',
  `serialNumber` varchar(50) DEFAULT NULL COMMENT '시리얼',
  `data` int(10) unsigned DEFAULT NULL COMMENT '빈도',
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.PIR_UPDATE
CREATE TABLE IF NOT EXISTS `PIR_UPDATE` (
  `nodeid` int(10) unsigned NOT NULL,
  `seq` int(10) DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `pir` int(10) DEFAULT NULL,
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`nodeid`),
  KEY `seq` (`seq`),
  KEY `regdate` (`regdate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.SENSOR_LIST
CREATE TABLE IF NOT EXISTS `SENSOR_LIST` (
  `serialNumber` varchar(50) NOT NULL DEFAULT '',
  `nodeid` int(10) unsigned DEFAULT NULL,
  `sensorType` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`serialNumber`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.SPLUG_DAVG
CREATE TABLE IF NOT EXISTS `SPLUG_DAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` date DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` float unsigned DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.SPLUG_TAVG
CREATE TABLE IF NOT EXISTS `SPLUG_TAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` datetime DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` float unsigned DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.SPLUG_UPDATE
CREATE TABLE IF NOT EXISTS `SPLUG_UPDATE` (
  `nodeid` int(10) unsigned NOT NULL DEFAULT '0',
  `seq` int(10) unsigned DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `WATT` float unsigned DEFAULT NULL,
  `ACC_WATT` float unsigned DEFAULT NULL,
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`nodeid`),
  KEY `seq` (`seq`),
  KEY `regdate` (`regdate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.TEMPERATURE_DAVG
CREATE TABLE IF NOT EXISTS `TEMPERATURE_DAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` date DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` float unsigned DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.TEMPERATURE_TAVG
CREATE TABLE IF NOT EXISTS `TEMPERATURE_TAVG` (
  `seq` int(10) NOT NULL AUTO_INCREMENT,
  `regdate` datetime DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `data` float unsigned DEFAULT NULL,
  PRIMARY KEY (`seq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.TEMPERATURE_UPDATE
CREATE TABLE IF NOT EXISTS `TEMPERATURE_UPDATE` (
  `nodeid` int(10) unsigned NOT NULL DEFAULT '0',
  `seq` int(10) unsigned DEFAULT NULL,
  `serialNumber` varchar(50) DEFAULT NULL,
  `temperature` float unsigned DEFAULT NULL,
  `battery` int(10) unsigned DEFAULT NULL,
  `regdate` datetime DEFAULT NULL,
  PRIMARY KEY (`nodeid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

# Data exporting was unselected.


# Dumping structure for table PEAKSAVE.viewerDeviceinfo
CREATE TABLE IF NOT EXISTS `viewerDeviceinfo` (
  `uid` varchar(20) COLLATE utf8_bin NOT NULL DEFAULT '0',
  `node` int(10) unsigned DEFAULT NULL,
  `site` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `name` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `en_name` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `type` varchar(20) COLLATE utf8_bin DEFAULT NULL,
  `user` varchar(20) COLLATE utf8_bin DEFAULT NULL,
  `regdate` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

# Data exporting was unselected.
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
