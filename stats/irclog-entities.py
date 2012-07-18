#! /usr/bin/env python2
from urllib import urlopen
#url = "http://www.guardian.co.uk/technology/2011/jun/24/lulzsec-irc-leak-the-full-record"
url = "http://irclogs.ubuntu.com/2012/05/05/%23ubuntu-uk.html"
raw = urlopen(url).read()

import nltk, re
from collections import defaultdict
raw = nltk.clean_html(raw)

sentences = nltk.sent_tokenize(raw)
sentences = [nltk.word_tokenize(sent) for sent in sentences]
sentences = [nltk.pos_tag(sent) for sent in sentences]
sentences = nltk.batch_ne_chunk(sentences)

def extract_entity_names(t):
    entity_names = []
    
    if hasattr(t, 'node') and t.node:
        if t.node == 'PERSON':
            entity_names.append(' '.join([child[0] for child in t]))
        else:
            for child in t:
                entity_names.extend(extract_entity_names(child))
                
    return entity_names

def list2hist(my_list):
    h = defaultdict(int)
    for my in my_list:
        h[my] = h[my] + 1
    return h

entity_names = []
IN = re.compile(r'.*\bin\b(?!\b.+ing)')
for sent in sentences:
    entity_names.extend(extract_entity_names(sent))

print list2hist(entity_names)
