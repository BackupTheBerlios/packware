#!/usr/bin/env python
"""Simple script for making .pwinfo files from freshmeat"""
#
# Created by StOOdi - stoodi@gazeta.pl
version = "0.0.6"
# 
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 2 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Library General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

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
         
    def writePwinfo(self):
        """Writes description to name.pwinfo"""
        filename = sys.argv[1] + '.pwinfo'
        pwinfo = open(filename, 'w')
        info = self.getText('desc_short')
        desc = self.getText('desc_full')
                
        pwinfo.write("info=" + '"' + info + '"' + "\n")
        pwinfo.write("desc=" + '"' + desc + '"' + "\n")

# The main ugly script.

inf = FreshmeatInfo()
usage = """
Project not found, or argument not given.

usage:

freshinfo projectname
"""
try:
    inf.openXML(sys.argv[1])
    inf.writePwinfo()
except:
    print __doc__
    print "Version ", version
    print usage

