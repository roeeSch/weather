# This project is intended on bringing weather forecast to your weatherdoc.



###On the raspberry pi (3):

**fetchImsAndPost.py** - fetches the weather forecast using **getIMS.py ** and writes the next 24 hour temperature forecast (6:00 to 6:00 or 18:00 to 18:00) to **index.html** (location /var/www/html/index.html).  

`fetchImsAndPost` is run via crontab (sudo) twice a day (usage `python3 fetchImsAndPost`) at 5:30 and at 17:30.

**index.html** - is used by local web server.

typically looks like:

```
<?xml version="1.0" encoding="UTF-8"?>
<note>
<br><body>21, 18:00, 9.9</body>
<br><body>21, 19:00, 9.5</body>
<br><body>21, 20:00, 8.9</body>
.
.
.
<br><body>22, 16:00, 9.9</body>
<br><body>22, 17:00, 9.3</body>
<br><body>22, 18:00, 9.0</body>
</note>

```



### On the weatherdoc - NodeMCU (arduino with wifii):

**nodeMcu_attempt** - is the main file.
**getHttpData.h** - manages the connection to the host, requests the html page and parses out the needed data.
**pswrd.h** - stores the network name, password and so on.







