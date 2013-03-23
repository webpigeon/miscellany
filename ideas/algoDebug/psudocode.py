
import collections

# PsudoCode commands
var_types = {
		'QUEUE': list
	}

def print_keyword(runtime, parts):
	print ("program:", parts[1:])

def begin_keyword(runtime, parts):
	runtime.add_label("BEGIN", runtime.current - 1 )
	print ("STARTED")

def end_keyword(runtime, parts):
	print("TERMINATED")

def goto_keyword(runtime, parts):
	runtime.goto(parts[1])

def debug_keyword(runtime, parts):
	print ("**DEBUG POINT", runtime, parts)

def def_keyword(runtime, parts):
	var_name = parts[1]
	var_type = parts[2]
	var = var_types[var_type]()	
	runtime.memory[var_name] = var

def jwr_psudocode():
	runtime = psudoCode()
	runtime.add_keyword("BEGIN", begin_keyword)
	runtime.add_keyword("PRINT", print_keyword)
	runtime.add_keyword("END", end_keyword)
	runtime.add_keyword("DEF", def_keyword)
	runtime.add_keyword("DEBUG", debug_keyword)
	return runtime

class psudoCode:
	
	def __init__(self):
		self.keywords = {}
		self.memory = {}
		self.labels = {}
		self.lines = []
		self.current = 0

	def add_keyword(self, keyword, callback):
		self.keywords[keyword] = callback

	def add_label(self, name, point):
		self.labels[name] = point

	def goto(self, label):
		point = self.labels[label]
		self.current = point

	def run(self):
		progLen = len(self.lines)
		while (self.current is not progLen):
			self.step()

	def step(self):
		line = self.lines[self.current]
		parts = self.decode(line)	
		self.current = self.current + 1

		keyword = self.keywords[parts[0]]
		keyword(self, parts)


	def decode(self, line):
		return line.split(" ")
