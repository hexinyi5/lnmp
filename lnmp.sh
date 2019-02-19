#!/bin/bash
wget -O /etc/yum.repos.d/epel.repo http://mirrors.aliyun.com/repo/epel-6.repo 
for n in `cat deps.txt`;do yum install -y $n;done >/dev/null
groupadd -g 800 nginx
useradd nginx -u 800  -g nginx -s /bin/nologin -M
groupadd -g 900 mysql
useradd -u 900 mysql -g mysql -s /bin/nologin -M

mkdir -p /application
cd /usr/local/src
tar xf mysql-5.6.10.tar.gz
cd mysql-5.6.10
cmake . -DCMAKE_INSTALL_PREFIX=/application/mysql-5.6.10 \
-DMYSQL_DATADIR=/application/mysql-5.6.10/data \
-DSYSCONFDIR=/etc \
-DWITH_INNOBASE_STORAGE_ENGINE=1 \
-DWITH_BLACKHOLE_STORAGE_ENGINE=1 \
-DWITH_ARCHIVE_STORAGE_ENGINE=1 \
-DWITH_PERFSCHEMA_STORAGE_ENGINE=1 \
-DWITHOUT_EXAMPLE_STORAGE_ENGINE=1 \
-DWITH_FEDERATED_STORAGE_ENGINE=1 \
-DDEFAULT_CHARSET=utf8 \
-DDEFAULT_COLLATION=utf8_general_ci \
-DWITH_EXTRA_CHARSETS=all \
-DWITH_ZLIB=bundled \
-DENABLED_LOCAL_INFILE=1 \
-DWITH_READLINE=1 \
-DMYSQL_UNIX_ADDR=/tmp/mysql.sock \
-DMYSQL_TCP_PORT=3306 \
-DWITH_EMBEDDED_SERVER=1 \
-DWITH_DEBUG=0

make && make install
ln -s /application/mysql-5.6.10 /application/mysql
echo 'export PATH=/application/mysql/bin:$PATH' >>/etc/profile
source /etc/profile
chown -R mysql.mysql /application/mysql/data
chmod -R 1777 /tmp/
\cp -pr /tmp/my.cnf /etc/
rm -fr /usr/local/src/mysql-5.6.10
cd /application/mysql
 ./scripts/mysql_install_db --user=mysql --basedir=/application/mysql --datadir=/application/mysql/data
/application/mysql/bin/mysqld_safe &


cd /usr/local/src
wget https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.15.tar.gz
tar xf libiconv-1.15.tar.gz
cd  libiconv-1.15
./configure
make
make install
libtool --finish /usr/local/lib

cd /usr/local/src
tar xf php-5.6.37.tar.gz
cd php-5.6.37
./configure --prefix=/application/php-5.6.37 --with-iconv-dir=/usr/local/libiconv --with-freetype-dir --with-jpeg-dir --with-png-dir --with-zlib --with-libxml-dir=/usr --enable-xml --disable-rpath --enable-bcmath --enable-shmop --enable-sysvsem --enable-inline-optimization --with-curl --enable-mbregex --enable-fpm --enable-mbstring --with-mcrypt --with-gd --enable-gd-native-ttf --with-openssl --with-mhash --enable-pcntl --enable-sockets --with-xmlrpc --enable-zip --enable-soap --enable-short-tags --enable-static --with-xsl --with-fpm-user=nginx --with-fpm-group=nginx --enable-ftp --without-pear  --disable-phar  --with-mysql=mysqlnd --enable-mysqlnd --with-gd --enable-gd-native-ttf  --enable-gd-jis-conv 

sed  -i '/^EXTRA_LIBS/s#$#\ -liconv#' Makefile
make
make install
ln -s /application/php-5.6.37/ /application/php
cp php.ini-production /application/php/lib/php.ini;ls /application/php/lib
cp /application/php/etc/php-fpm.conf.default /application/php/etc/php-fpm.conf
echo '/usr/local/lib' >> /etc/ld.so.conf && /sbin/ldconfig
/application/php/sbin/php-fpm

mkdir -p /app/logs/nginx/
cd /usr/local/src
tar xf nginx-1.14.2.tar.gz
cd nginx-1.14.2
./configure \
--prefix=/application/nginx-1.14.2 \
--user=nginx \
--group=nginx \
--with-http_ssl_module \
--with-http_stub_status_module \
--without-http_gzip_module \
--with-zlib=/usr

make
make install
ln -s /application/nginx-1.14.2/ /application/nginx
\cp /tmp/nginx.conf /application/nginx/conf/nginx.conf
cp /tmp/phpinfo.php /application/nginx/html/phpinfo.php
mkdir -p /application/nginx/html/ecshop
cp -R -pr /tmp/ecshop  /application/nginx/html/
chown -R nginx.nginx /application/nginx/html/ecshop
/application/nginx/sbin/nginx -t
/application/nginx/sbin/nginx

ss -ln|egrep "33|90|80"

