CREATE TABLE bank.accounts (
       id INT NOT NULL IDENTITY(1000, 1),
       userid INT NOT NULL,
       accountname VARCHAR(64),
       currency CHAR(3) NOT NULL DEFAULT 'SEK',
       balance INT DEFAULT 0,
       PRIMARY KEY (id),
       FOREIGN KEY (userid) REFERENCES bank.users(id)
);
