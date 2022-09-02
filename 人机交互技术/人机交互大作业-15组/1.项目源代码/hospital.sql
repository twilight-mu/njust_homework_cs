/*
Navicat MySQL Data Transfer

Source Server         : MySQL
Source Server Version : 50017
Source Host           : localhost:3306
Source Database       : hospital

Target Server Type    : MYSQL
Target Server Version : 50017
File Encoding         : 65001

Date: 2021-12-19 10:36:11
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for admin
-- ----------------------------
DROP TABLE IF EXISTS `admin`;
CREATE TABLE `admin` (
  `id` int(11) NOT NULL auto_increment,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of admin
-- ----------------------------
INSERT INTO `admin` VALUES ('1', 'admin', 'admin');

-- ----------------------------
-- Table structure for doctor
-- ----------------------------
DROP TABLE IF EXISTS `doctor`;
CREATE TABLE `doctor` (
  `id` int(11) NOT NULL auto_increment,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `name` varchar(255) default NULL,
  `sex` varchar(255) default NULL,
  `age` varchar(255) default NULL,
  `picture` varchar(255) default NULL,
  `phone` varchar(255) default NULL,
  `detail` varchar(255) default NULL,
  `islocked` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of doctor
-- ----------------------------
INSERT INTO `doctor` VALUES ('1', 'doctor1', 'root', '刀客塔', '男', '24', 'picture2.png', '12345', '内科主治医师', '0');
INSERT INTO `doctor` VALUES ('2', 'doctor2', 'root', '华强', '男', '33', 'picture2.png', '12345', '内科主治医师', '0');
INSERT INTO `doctor` VALUES ('3', 'doctor3', 'root', '好家伙', '男', '23', 'picture2.png', '12345', '内科主治医师', '0');
INSERT INTO `doctor` VALUES ('4', 'doctor4', 'root', '好家伙', '女', '33', 'picture2.png', '12345', '内科主治医师', '0');
INSERT INTO `doctor` VALUES ('5', 'testnew', 'testnew', null, null, null, 'moren.jpg', '1234', null, '0');

-- ----------------------------
-- Table structure for message
-- ----------------------------
DROP TABLE IF EXISTS `message`;
CREATE TABLE `message` (
  `id` int(11) NOT NULL auto_increment,
  `content` varchar(255) NOT NULL,
  `publisher` varchar(255) NOT NULL,
  `receiver` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of message
-- ----------------------------
INSERT INTO `message` VALUES ('1', '你好', 'root', 'sax');
INSERT INTO `message` VALUES ('3', '你好', 'doctor1', 'doctor3');
INSERT INTO `message` VALUES ('5', '666', 'doctor1', 'root');
INSERT INTO `message` VALUES ('6', '2222', 'root', 'doctor2');

-- ----------------------------
-- Table structure for patient
-- ----------------------------
DROP TABLE IF EXISTS `patient`;
CREATE TABLE `patient` (
  `id` int(11) NOT NULL auto_increment,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `name` varchar(255) default NULL,
  `sex` varchar(255) default NULL,
  `age` varchar(255) default NULL,
  `picture` varchar(255) default NULL,
  `phone` varchar(255) default NULL,
  `detail` varchar(255) default NULL,
  `islocked` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of patient
-- ----------------------------
INSERT INTO `patient` VALUES ('1', 'root', 'root', '张三', '男', '22', 'picture1.png', '110', '123', '0');
INSERT INTO `patient` VALUES ('2', 'sax', 'sax', '孙傲歆', '男', '21', 'moren.jpg', '15855772938', '无', '0');
INSERT INTO `patient` VALUES ('3', 'test', 'test', null, null, null, 'moren.jpg', '1111', null, '0');
INSERT INTO `patient` VALUES ('4', 'testnew', 'testnew', null, null, null, 'moren.jpg', '1222', null, '0');
INSERT INTO `patient` VALUES ('6', 'test1', 'test1', 'sax', '男', '12', 'picture3.png', '123', '你好', '1');

-- ----------------------------
-- Table structure for question
-- ----------------------------
DROP TABLE IF EXISTS `question`;
CREATE TABLE `question` (
  `id` int(11) NOT NULL auto_increment,
  `title` varchar(255) NOT NULL,
  `content` varchar(255) NOT NULL,
  `publisher` varchar(255) NOT NULL,
  `replynum` int(11) NOT NULL,
  `major` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of question
-- ----------------------------
INSERT INTO `question` VALUES ('1', '孩子咳嗽老不好', '如题', 'sax', '3', '儿科');
INSERT INTO `question` VALUES ('2', '大小便不畅', '如题', 'sax', '2', '内科');
INSERT INTO `question` VALUES ('3', '控制不住大小便', '帮米国总统问的', 'sax', '3', '内科');
INSERT INTO `question` VALUES ('4', '嗯哼', '嗯哼', 'sax', '1', '外科');
INSERT INTO `question` VALUES ('5', '骨头断了', '哼哼哼啊啊啊啊', 'root', '2', '骨科');
INSERT INTO `question` VALUES ('6', '你好', 'hello world', 'root', '0', '儿科');

-- ----------------------------
-- Table structure for reply
-- ----------------------------
DROP TABLE IF EXISTS `reply`;
CREATE TABLE `reply` (
  `id` int(11) NOT NULL auto_increment,
  `content` varchar(255) NOT NULL,
  `replier` varchar(255) NOT NULL,
  `qid` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of reply
-- ----------------------------
INSERT INTO `reply` VALUES ('1', '不造啊', 'doctor1', '1');
INSERT INTO `reply` VALUES ('4', '建议remake', 'doctor1', '3');
INSERT INTO `reply` VALUES ('5', '发出很大的声音掩盖过去吧', 'doctor3', '3');
INSERT INTO `reply` VALUES ('6', '太巨了', 'doctor4', '3');
INSERT INTO `reply` VALUES ('7', '嗯哼', 'doctor3', '4');
INSERT INTO `reply` VALUES ('8', '还有这种事？', 'doctor3', '2');
INSERT INTO `reply` VALUES ('9', '太艹了', 'doctor3', '2');
INSERT INTO `reply` VALUES ('10', '唐突恶臭不可取', 'doctor3', '5');
