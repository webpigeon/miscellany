#! /usr/bin/env python2
##
# Find out who is talking to who in an IRC log.
##
import nltk
import re, os
from collections import defaultdict


class Data(object):

    def __init__(self):
        self.mentions = defaultdict(int)
        self.lines = defaultdict(int)
        self.who = defaultdict(lambda : defaultdict(int))

def process(raw, data):
    line = re.compile("\W+\[([^\]]+)\] <([^>]+)> (.*)")
    result = line.findall(raw)

    # find out how much each person says
    for (time, user, line) in result:
        data.lines[user.lower()] = data.lines[user] + 1

    for (time, user, line) in result:
        words = nltk.word_tokenize(line)
        for word in words:
            word = word.lower()
            if word in data.lines:
                data.who[user.lower()][word] = data.who[user][word] + 1
                data.mentions[word] = data.mentions[word] + 1

data = Data()
for f in os.listdir("irc-docs"):
    raw = open("irc-docs/"+f).read()
    process(raw, data)
    print(f)

print("\n == mentions == ")
print(data.mentions)

print("\n == lines == ")
print(data.lines)

print("\n == who == ")
for user,other in data.who.items():
    print("%s : %s" % (user,other.keys()) )
