# open_source

This is a branch for open source software.

How this was setup

1. follow this https://help.github.com/articles/set-up-git/
2. make a repository on github
3. add a collaborator to the project 
4. clone the repo to your local machine using git clone {url for repo}
5. make changes to file or add new ones using git add {filename}
6. need to make a commit for each pus hand do this using git commit -m 'First commit'
7. push your changes to the repo using git push origin {branch}
 
this is a thing


How to run this

Prerequisites
* mysqlclient
* octave
* gcc compiler

1. set up a database named process_control 
2. make a table in it called mixer_temp
3. compile both c programs using the seperate make files
4. run them the producer first to add in the entries
5. make a csv file using the csv file
6. start octave
7. run these two command in octave  b=csvread("{csv file}"); 
and plot(b(:,1),b(:,3)) or plot(b(:,2),b(:,3))

Problems that will arise
The credentials for mysql will be different
line 39 in producer.c and line 44 in reader.c need to be changed to the right configuration 


