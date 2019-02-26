# -*- coding: utf-8 -*-
"""
Created on Wed Jan 24 17:38:38 2018

@author: ROEE
"""


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

# gI.getAlltagText(tree, 'Location')

t, deg, hum, dateTick = gI.parseXmlData(tree, r'ESHHAR')

#%%
#gI.getAlltagText(tree, 'Location')

iNoon = np.argmin(np.abs(np.fmod(t, 24)-18))
iSunRise = np.argmin(np.abs(np.fmod(t, 24)-6))

firstIndex = np.amin([iNoon,iSunRise])

for i in range(firstIndex, firstIndex + 13):
    print('\t' + dateTick[i] + ', ' + str(deg[i]) + ' [C]')
