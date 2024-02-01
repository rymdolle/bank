CREATE TABLE bank.users (
       id INT NOT NULL IDENTITY(1000, 1),
       username VARCHAR(64) NOT NULL,
       password VARCHAR(128),
       PRIMARY KEY (id)
);
