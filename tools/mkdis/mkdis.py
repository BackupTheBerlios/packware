#!/usr/bin/python
# This is just prototype for future development :D
# for now, works.
#
# StOOdi's excersizes
# Version 0.4
#
# TODO: 
# - names distribution directory (ex. kde, gnome, xfce)
# - mdsums from .md5sum files
# - maybe versions from distribution files
#

import sys, os, getopt

def make_dist(name = 'NoName', version = 'Version', link='http://nobady.home'):

    shell = "#!/bin/sh"
    pname = "name=" + '"' + name + '"'
    pversion = "version=" + '"' + version + '"'
    build = "build=" + '"' + '1' + '"'
    pwbuilder = "_pwbuilder 0.6.4"
    doc = "_doc -d" 
    source = "_source -g -m md5sum" + " " + link  
    copt1 = "_c_opt --prefix=/usr"
    cmi = "_cmi"
    log = "# $" + "Log" + "$" # Stupid but, cvs ... eh...
    CR = '\n'
    DCR = '\n\n'
    
    lines = [ shell, DCR,
              pname, CR,
              pversion, CR,
              build, DCR,
              pwbuilder, DCR,
              doc, DCR,
              source, DCR,
              copt1, DCR,
              cmi, DCR,
              log, CR ]
    
    # Here what we do.
    cwd = os.getcwd()   # getting current working dir
    os.mkdir(cwd + os.sep + name)      # makes dist dir
    os.chdir(name)  # go to dist dir
    # Make needed files
    buildfile = open(name + ".pwbuild",'w')
    buildfile.writelines(lines)
    buildfile.close()
    # Here we can add freshinfo support :)
    infofile = open(name + ".pwinfo", 'w')
    infofile.close()
    os.chdir('..')
    
def usage():
    print """

    -n --name       name of package
    -v --version    version of pakcage
    -l --link       link to source files
    -f --filelist   file with packages names one in line
                    this parameter should be the last.
    
    mkdis.py -n name -v version -l link

    mkdis.py -v 3.44 -f filelist.txt


    Not given parameter take default value.
    
    """

def main(argv):                         

    pname = 'None'
    pversion = 'None'
    plink = 'http://linktofiles'
                     
    try:                                
        opts, args = getopt.getopt(argv, "n:v:l:f:h", ["name",
                                                      "version",
                                                      "link",
                                                      "filelist",
                                                      "help"]) 
    except getopt.GetoptError:           
        usage()                          
        sys.exit(2)                     

    for opt, arg in opts:                

        if opt in ("-h", "--help"):      
            usage()
            sys.exit(2)
            
        elif opt in ("-n", "--name"): 
            pname = arg

        elif opt in ("-v", "--version"):
            pversion = arg

        elif opt in ("-l", "--link"):
            plink = arg

        elif opt in ("-f", "--filelist"):
            pfname = arg

            file = open(pfname, 'r')
            lines = file.readlines()
                        
            for fname in lines:
                fname = fname.rstrip()
                make_dist(name = fname, version = pversion, link = plink)
            sys.exit(2)
            

    make_dist(name = pname , version = pversion , link = plink)


if __name__ == "__main__":
    main(sys.argv[1:])
