Another great thing from HSE's students

So, what is this and how to?
    This is a SQL-lab. Common thing to do: GUI-client for PostgreSQL server.

There are our steps to configure PostgreSQL server:

Short list of terms:
    $ -- bash prompt
    # -- psql prompt

Install some PostgreSQL (in Devuan 3 case it is PostgreSQL 11):
    $ sudo apt install postgresql

Login to psql as postgres (psql role) through postgres (linux user):
    $ sudo -u postgres psql -U postgres
       |    | |         |    |
       |    | |         |    `--------------------------------.
       |    | |         |                                      `.
       |    | |       open PostgreSQL interactive terminal, login there as postgres (psql role)
    execute | |       ```````````````                       ```````````````````````
     'as    |  `-------------------.
     root'  |                       `.
          execute next command as postgres (linux user)
          ```````                 ````````
postgres is an administrator in psql, some kind of root
It is absolutely normal to login as postgres (psql role) through postgres (linux user) with sudo --
  it is save
It is absolutely normal that postgres (both: psql role and linux user) doesn't have a password --
  there are reasons for that
It is not a good practice to do something unclear in config-files, so it is advisable to
  forget about pg_hba.conf, however, if you want you can find this file (so, where is it?).

If you edited your configuration files, you should restart postgresql service or reboot your system

To understand who are you in psql (print using-right-now role name):
    # SELECT current_user;

To understand where are you in psql (print name of current database):
    # SELECT current_database();

By the way, there are users and roles in psql and it makes sense in previous versions (do not know
  exactly in which ones) of PostgreSQL, but then these concepts were merged and now they are almost
  the same thing. So, in the future when I talk about role or user in psql I will mean the same
  thing

To list users (such as postgres):
    # \du

To create new (non-postgres/non-admin/just-dude) loginable psql role with password and ability to
  create databases:
    # CREATE ROLE username
      CREATEDB
      LOGIN
      PASSWORD 'password';

To list databases (there is database named "postgres" -- not so original/various, you know):
    # \l

To create new database with certain owner (by the way, it seems having some "home/default" database
  is nessesary for every psql user):
    # CREATE DATABASE databasename WITH OWNER = username;

To connect to another database using current user:
    # \c databasename

To list tables in current database:
    # \dt

To remove database:
    # DROP DATABASE databasename;

To remove user:
    # DROP USER username;

Actually, you cannot just remove some user -- any dependencies (databases owned by this user) must
  not exist

To find the port number. Default PostgreSQL port number is "5432". There are many ways to get it,
  one of the easiest ones:
    # \conninfo

To exit psql:
    # \q
  or Ctrl+D keyboard shortcut

There are many important and interesting information like the port number in postgresql.conf file
  (in the same directory that pg_hba.conf (common, where is it?))

To login to psql as some psql user from bash (it works without root and editing configuration files
  and it is some kind of the right way):
    $ psql -h hostname -p portnumber -U username -d databasename
               |               |
               |               |
       name of host,     the port number,
      if one computer   PostgreSQL default is
        is used type           5432
        "localhost"

To login to psql as some psql user (simple way) (works on default port number, you will login to
  some "default" database owned by this this user):
    $ psql -h hostname -U username

To create extensions current user usually needs to have superuser priviliges. It is not always
  OK to give some usual user these priviliges. Fortunately, extensions are installed on databases,
  not users/roles, therefore if you need an extension on some database, connect to this one as
  postgres or something and create needed extension.
    # CREATE EXTENSION extensionnameorsmth;

To list installed extensions
    # \dx

To create/drop (delete) stored procedures and functions read docs, manuals or smth.

To list available for current user stored procedures and functions (by the way, SQL standard):
    # SELECT specific_name, routine_definition
        FROM information_schema.routines;

To short the list (do not show pg_catalog procedures and functions, e.g. show "custom" ones):
    # SELECT specific_name, routine_definition
        FROM information_schema.routines
       WHERE specific_schema <> 'pg_catalog';

To check database existence this way might be used:
    # SELECT 1
        FROM pg_database
       WHERE datname='namedb';

Простор открыт -- и ничего святого now.
