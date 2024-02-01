CREATE TABLE bank.accounts (
       id INT NOT NULL AUTO_INCREMENT,
       userid INT NOT NULL,
       accountname VARCHAR(64),
       currency CHAR(3) NOT NULL DEFAULT 'SEK',
       balance INT DEFAULT 0,
       PRIMARY KEY (id),
       FOREIGN KEY (userid) REFERENCES bank.users(id)
);
ALTER TABLE bank.accounts AUTO_INCREMENT = 1000;
