#! /usr/bin/env python

import string
from datetime import date

def birthday(data):
    d = date.today()
    data = data.replace("cats ", "happy") 
    data = data.replace("today ", "birthday")
    data = data.replace("on facebook", "ben!")
    print(data[0:5], data[5:d.month+6], data[d.day+2:d.day+d.month])

if __name__ == "__main__": 
    birthday("cats today on facebook")
