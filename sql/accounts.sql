CREATE TABLE bank.accounts (
       -- id INT NOT NULL IDENTITY(1000, 1), -- SQL Server
       id INT NOT NULL AUTO_INCREMENT, -- MariaDB
       userid INT NOT NULL,
       accountname TEXT,
       currency CHAR(3) NOT NULL DEFAULT 'SEK',
       balance INT DEFAULT 0,
       PRIMARY KEY (id),
       FOREIGN KEY (userid) REFERENCES bank.users(id)
);
ALTER TABLE bank.accounts AUTO_INCREMENT = 1000; -- MariaDB

INSERT INTO bank.accounts
        (userid, accountname,       balance)
VALUES
        (1000,   'Savings account', 1617500),
        (1001,   'Salary account',  443400),
        (1002,   'Savings account', 3193300),
        (1003,   'Salary account',  74000),
        (1004,   'Regular account', 343100),
        (1005,   'Savings account', 36500),
        (1006,   'Salary account',  787900);
