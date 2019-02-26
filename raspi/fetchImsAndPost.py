import getIMS as gI
import numpy as np
import datetime


today = datetime.date.today()
todayNum = today.day

tomorrow = datetime.date.today() + datetime.timedelta(days=1)
tomorrowNum = tomorrow.day

currentTime = datetime.datetime.now()

#This part of the code imports the xml data from the ims website
tree = gI.reqXmlData(gI.xmlWebDict.get('sites'))
t, deg, hum, dateTick = gI.parseXmlData(tree, r'ESHHAR')

iNoon = np.argmin(np.abs(np.fmod(t, 24)-18))
iSunRise = np.argmin(np.abs(np.fmod(t, 24)-6))

firstIndex = np.amin([iNoon,iSunRise])

with open('/var/www/html/index.html','w') as outfile:
    outfile.write('<?xml version="1.0" encoding="UTF-8"?>\n')
    outfile.write('<note>\n')

    for i in range(firstIndex, firstIndex + 25):
        #print('\t' + dateTick[i] + ', ' + str(deg[i]) + ' [C]')
        outfile.write("<br><body>{}, {}</body>\n".format(dateTick[i],deg[i]))    
        
    #for dti, degi in zip(dateTick, deg):
    #	outfile.write("<br><body>{}: {}</body>\n".format(dti,degi))
    outfile.write('</note>\n')
