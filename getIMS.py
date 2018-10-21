# -*- coding: utf-8 -*-
"""
Get Tahazit data from IMS xmls

Created on Sat Dec 23 13:10:43 2017

@author: ROEE
"""

from urllib.request import Request, urlopen
import numpy as np
#from matplotlib import pyplot as plt
import xml.etree.ElementTree as ET

xmlWebDict = {'sites':'https://ims.data.gov.il/sites/default/files/IMS_001.xml',
              'cities':'https://ims.data.gov.il/sites/default/files/isr_cities.xml',
              }

def reqXmlData(URL):
    '''Request XML from URL and return as element tree.
    '''
    req=Request(URL, headers={'User-Agent': 'Mozilla/5.0'})
    webpage = urlopen(req).read() 
    return ET.fromstring(webpage)

def findInTree_txt(tree,text,pathInds):
    '''
    Find "text" in tree (first appearance) and return path (as list of int).
    tree (input)
    text (input)
    pathInds (empty input)
    '''
    try:
        if tree.text != None and text in tree.text:
            return pathInds
    except TypeError as e:
        print(e)
        print(tree.text)
        pass
    i=0
    for tmp in tree.getchildren():
        pathInds.append(i)
        if findInTree_txt(tmp,text,pathInds):
            return pathInds
        else:
            pathInds.pop()
        i+=1
    return []

def findInTree_tag(tree,tag,pathInds):
    '''
    Find "tag" in tree (first appearance) and return path (as list of int).
    tree (input)
    tag  (input)
    pathInds (empty input)
    '''
    try:
        if tag in str(tree.tag):
            return pathInds
    except TypeError:
        print('Error!')
        pass
    i=0
    for tmp in tree.getchildren():
        pathInds.append(i)
        if findInTree_tag(tmp,tag,pathInds):
            return pathInds
        else:
            pathInds.pop()
        i+=1
    return []

def findInTree_txt_postRef(tree,text,pathInds,refPathInds):
    '''
    XXXXXXX TODO XXXXXXX
    tree (input)
    text (input)
    pathInds (empty input)
    '''
    try:
        if text in tree.text and myPathInds(pathInds)>=myPathInds(refPathInds):
            return pathInds
    except TypeError:
        print('Error!')
        pass
    i=0
    for tmp in tree.getchildren():
        pathInds.append(i)
        if findInTree_txt_postRef(tmp,text,pathInds,refPathInds) and myPathInds(pathInds)>=myPathInds(refPathInds):
            return pathInds
        else:
            pathInds.pop()
        i+=1
    return []

def findInTree_txt_relRef(tree,text,pathInds,refPathInds,relFunc):
    '''
    XXXXXXX TODO XXXXXXX
    tree (input)
    text (input)
    pathInds (empty input)
    '''
    relCond=relFunc(myPathInds(pathInds),myPathInds(refPathInds))
    try:
        if tree.text != None and text in tree.text and relCond:
            return pathInds
    except TypeError as e:
        print('Error!')
        print(e)
        pass

    i=0
    for tmp in tree.getchildren():
        pathInds.append(i)
        relCond=relFunc(myPathInds(pathInds),myPathInds(refPathInds))
        if findInTree_txt_relRef(tmp,text,pathInds,refPathInds,relFunc) and relCond:
            return pathInds
        else:
            pathInds.pop()
        i+=1
    return []
    
def getFieldTag(tree,pathInds,i):
    if i==len(pathInds)-1:
        return str(tree[pathInds[i]].tag)
    else:
        return getFieldTag(tree[pathInds[i]],pathInds,i+1)

def getFieldText(tree,pathInds,i):
    if i==len(pathInds)-1:
        return str(tree[pathInds[i]].text)
    else:
        return getFieldText(tree[pathInds[i]],pathInds,i+1)

def getAlltagText(tree,tag):
    l=list()
    for indx1 in tree.getchildren():#root:
        if indx1.tag == tag:
            print(indx1[0][0].text)
            l.append(indx1[0][0].text)
    return l


def parseXmlData(tree, loc = 'ESHHAR'):
    x=np.array([])
    deg=np.array([])
    hum=np.array([])
    dateTick=[]
    for indx1 in tree.getchildren():#root:
        if 'Location'==indx1.tag:
            if loc in indx1[0][0].text:
                for indx2 in indx1:
                    if indx2.tag=='LocationData':
                        for tg in indx2:
                            dateTick.append(tg[0].text.split()[0].split('/')[0]+', '+tg[0].text.split()[1])
                            x=np.append(x,float(tg[0].text.split()[1].split(':')[0]))
                            deg=np.append(deg,float(tg[1].text.split()[0]))
                            hum=np.append(hum,float(tg[2].text.split()[0]))
                            
    xNew=x
    for i in range(len(x)-1):
        if xNew[i+1]-xNew[i]<0:
            xNew[i+1:]+=24
        
    return xNew, deg, hum, dateTick       

class myPathInds(list):
    def __ge__(self,other):
        tupBoth=zip(self,other)
        for cpl in tupBoth:
            if cpl[0]<cpl[1]:
                return False
        return True
    
    def __le__(self,other):
        tupBoth=zip(self,other)
        for cpl in tupBoth:
            if cpl[0]>cpl[1]:
                return False
        return True
    
    def __gt__(self,other):
        tupBoth=zip(self,other)
        for cpl in tupBoth:
            if cpl[0]<=cpl[1]:
                return False
        return True
    
    def __lt__(self,other):
        tupBoth=zip(self,other)
        for cpl in tupBoth:
            if cpl[0]>=cpl[1]:
                return False
        return True
#%%
'''
import getIMS as gI
from matplotlib import pyplot as plt

tree = gI.reqXmlData(gI.xmlWebDict.get('sites'))
treeCities = gI.reqXmlData(gI.xmlWebDict.get('cities'))
t, deg, hum, dateTick = gI.parseXmlData(tree)

gI.getAlltagText(tree,'Location')

iNoon = np.argmin(np.abs(t-16))

plt.subplot(211).plot(t,deg)
plt.xticks(t, dateTick, color='red', rotation='vertical')
yl_tmp = plt.ylim()
t[0]

plt.subplot(212).plot(t,hum)
plt.xticks(t, dateTick, color='red', rotation='vertical')

'''