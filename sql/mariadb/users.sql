CREATE TABLE bank.users (
       id INT NOT NULL AUTO_INCREMENT,
       username VARCHAR(64) NOT NULL,
       password VARCHAR(128),
       PRIMARY KEY (id)
);
ALTER TABLE bank.users AUTO_INCREMENT = 1000;
