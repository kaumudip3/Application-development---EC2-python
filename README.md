# Programming_assignment

For UserRegistration EC2 project: Refer :
- https://www.datasciencebytes.com/bytes/2015/02/24/running-a-flask-app-on-aws-ec2/
- https://pythonprogramming.net/flask-registration-tutorial/?completed=/flask-user-registration-form-tutorial/
- https://www.youtube.com/watch?v=6L3HNyXEais
- https://www.google.com/search?q=create+web+page+using+ec2+instance&oq=create+web+page+using+ec2+&aqs=chrome.1.69i57j33.7732j1j7&sourceid=chrome&ie=UTF-8#kpvalbx=_ifQ1XoWsKO2N_QaP-IGACQ31
- https://pythonhow.com/html-templates-in-flask/

Mysql password change : 
Note: For MySQL 5.7+ please see answer from @Lahiru to this question. That contains more current information.

For MySQL < 5.7:

The default root password is blank (i.e. empty string) not root. So you can just login as:

mysql -u root
You should obviously change your root password after installation

mysqladmin -u root password [newpassword]
In most cases you should also set up individual user accounts before working extensively with the DB as well.


MySQL install:
https://support.rackspace.com/how-to/install-mysql-server-on-the-ubuntu-operating-system/
