#!/usr/bin/env python
"""Simple script for taking info from freshmeat.net"""
#
# Created by StOOdi - stoodi@gazeta.pl
#
# I hope this script will be usefull for people who want to
# keep packages up to date. It is more universal version of my
# script freshinfo.
# 
version = "0.0.1"
# 
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 2 of the License.
#
#
import re, sys, urllib2, string
from xml.dom import minidom

class FreshmeatInfo:
    """ Class for getting info about packages from freshmeat """
     
    # Here initiation variables
    
    def __init__(self):
        self.xmldoc = ""        # here is stored XML source 
        
    def openXML(self, name):
        """opens adress and puts XML source to self.xmldoc"""
        url = 'http://freshmeat.net/projects-xml/' + name + '/' + name + '.xml'
        usock = urllib2.urlopen(url)
        self.xmldoc = minidom.parse(usock)
    
    def getText(self, tag):
        """gets only text from XML tag"""
        names = self.xmldoc.getElementsByTagName(tag)
        element = names[0].toxml()
        start_tag = '<' + tag + '>'
        end_tag = '</' + tag + '>'
        result = element.replace(start_tag,"").replace(end_tag,"").replace("\n"," ")
        return result
       
   
# The main ugly script.

inf = FreshmeatInfo()
usage = """
Project not found, or argument not given.

usage: project_name tag

Some usefull tags below:
 
project_id, date_added, date_updated, projectname_short
projectname_full, desc_short, desc_full, vitality_score,
vitality_percent, vitality_rank, rating, url_project_page
url_homepage, url_tgz, url_bz2, latest_release_version


"""
try:
    inf.openXML(sys.argv[1])
    info = inf.getText(sys.argv[2])
    print info
    
except:
    print __doc__
    print "Version ", version
    print usage
