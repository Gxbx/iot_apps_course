--mongodb--
apt-get update
apt-get upgrade
apt-get dist-upgrade
reboot

apt-get install mongodb
service mongodb start
--Redis--
sudo apt update
sudo apt full-upgrade
sudo apt install redis-server

redis-cli ping
redis-cli ping

--ThingsBoard--
sudo apt update
sudo apt install openjdk-8-jdk
sudo update-alternatives --config java
java -version
wget https://github.com/thingsboard/thingsboard/releases/download/v2.4/thingsboard-2.4.deb
sudo dpkg -i thingsboard-2.4.deb

--postgresql--
sudo apt-get update
sudo apt-get install postgresql postgresql-contrib
sudo service postgresql start
sudo su - postgres
psql
\password
\q
psql -U postgres -d postgres -h 127.0.0.1 -W
CREATE DATABASE thingsboard;
\q

sudo nano /etc/thingsboard/conf/thingsboard.conf

# DB Configuration 
export DATABASE_ENTITIES_TYPE=sql
export DATABASE_TS_TYPE=sql
export SPRING_JPA_DATABASE_PLATFORM=org.hibernate.dialect.PostgreSQLDialect
export SPRING_DRIVER_CLASS_NAME=org.postgresql.Driver
export SPRING_DATASOURCE_URL=jdbc:postgresql://localhost:5432/thingsboard
export SPRING_DATASOURCE_USERNAME=postgres
export SPRING_DATASOURCE_PASSWORD=PUT_YOUR_POSTGRESQL_PASSWORD_HERE

sudo nano /etc/thingsboard/conf/thingsboard.conf

export JAVA_OPTS="$JAVA_OPTS -Xms256M -Xmx256M"

sudo /usr/share/thingsboard/bin/install/install.sh --loadDemo
sudo service thingsboard start