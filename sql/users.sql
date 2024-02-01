CREATE TABLE bank.users (
       -- id INT NOT NULL IDENTITY(1000, 1), -- SQL Server
       id INT NOT NULL AUTO_INCREMENT, -- MariaDB
       username VARCHAR(64) NOT NULL,
       password VARCHAR(64),
       PRIMARY KEY (id)
);
ALTER TABLE bank.users AUTO_INCREMENT = 1000; -- MariaDB

INSERT INTO bank.users
        (username, password)
VALUES
        ('olle',   '0000'),
        ('nils',   '1234'),
        ('ludwig', '9999'),
        ('mariia', '4242'),
        ('faisal', '9898'),
        ('pontus', '1221'),
        ('daniel', '5182');
