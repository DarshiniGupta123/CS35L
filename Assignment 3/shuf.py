#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, isRange, repitition, filename):
        if filename == "-":
          self.lines = sys.stdin.readlines()
        elif filename == "":
          self.lines = sys.stdin.readlines()
        #if len(self.lines) <= 0:
          #return 
        elif isRange == True:
          self.lines = filename
        else:
          f = open(filename, 'r')
          self.lines = f.readlines()
          f.close()
        self.repeats = repitition
    def chooseline(self):
        if self.repeats is False:
          line =  random.choice(self.lines)
          self.lines.remove(line)
          return line
        else:
          return random.choice(self.lines) 

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--head-count=COUNT",
                      action="store", dest="numlines", 
                      help="output at most COUNT lines")
    parser.add_option("-i", "--input-range=LO-HI", 
                      action="store", dest="count",
                      help="treat each number LO through HI as an input line")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="repeat", default=False, 
                      help="output lines can be repeated")
    options, args = parser.parse_args(sys.argv[1:])

    
    #flag = bool(options.count)
    flag = False
    if options.count != None:
        flag = True

    #repeat = bool(options.repeat)

    exists = False

    Nums = []

    if flag is True:
        try:
            small, big = options.count.split("-")
        except:
            parser.error("shuf: invalid input range  '" + options.count + "'")
        for index in range(int(small), (int(big))+1):
            Nums.append(index)

    if options.numlines != None: 
        try:
            numlines = int(options.numlines)
            exists = True
        except:
            parser.error("invalid line count '{0}'".
                     format(options.numlines))
        if numlines < 0:
            parser.error("invalid line count {0}".
                     format(numlines))

    if (len(args) != 1) and (len(args) != 0):
        parser.error("wrong number of operands")

    if flag is True:
        input_file = Nums
    elif len(args) < 1:
        input_file = ""
    else:
        input_file = args[0]

    try:
        generator = randline(flag, options.repeat, input_file)
        if exists is True:
            for index in range(numlines):
                if flag is False:
                    sys.stdout.write(str(generator.chooseline()))
                else: 
                    sys.stdout.write(str(generator.chooseline())+ '\n')
        elif options.repeat is False:
            for index in range(len(generator.lines)):
                if flag is False:
                    sys.stdout.write(str(generator.chooseline()))
                else:
                    sys.stdout.write(str(generator.chooseline())+ '\n')
        else:
            while True:
                sys.stdout.write(str(generator.chooseline())+ '\n')
    except IOError:
        parser.error("shuf: " + input_file +": No such file or directory")

if __name__ == "__main__":
    main()
