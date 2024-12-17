# @page DateTime sync over HTTP
# @date 2024-08-02, atgroup09@yandex.ru

import sys;
import urllib.request;
import email.utils, datetime;
import timesetter;

Proxy = "192.168.2.1:8080";
Url   = "https://miass.ru";
Hours = 5;

Request = urllib.request.Request(Url);
Request.set_proxy(Proxy, "http");

Response = urllib.request.urlopen(Request);

Date    = Response.headers["Date"];
DateObj = email.utils.parsedate(Date);
#print(Date);
DateTimeObj = datetime.datetime(DateObj[0], DateObj[1], DateObj[2], DateObj[3]+Hours, DateObj[4], DateObj[5], DateObj[6]);
timesetter.set(DateTimeObj);



