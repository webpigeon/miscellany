#! /usr/bin/env python
##
# PsudoCode Interpreater written in python
##

import psudocode

program = "BEGIN\nDEF explored QUEUE\nDEF error STACK\nPRINT hello world\nEND"

# check if we are running this as a program
def prompt():
	print "PsudoCode Interperter"
	print "Written by Joseph Walton-Rivers <joseph@webpigeon.me.uk>"

	print ""
	print program
	print ""
	
	runtime = psudocode.jwr_psudocode()
	runtime.lines = program.split("\n")
	runtime.run()

prompt()
