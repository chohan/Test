#!/usr/bin/python3
"""
regex examples
"""
import re

text_to_search = '''
abcdefghijklmnopqrstuvwxyz
abcdefghijklmnopqrstuvwxyz
1234567890

Ha HaHa

MetaCharacters (Need to be escaped):
. ^ $ * + ? { } [ ] \ | ( )

google.com

321-555-4321
123.555.1234

Mr. Chohan
Mr. Amir
Mr. Ammar
Mrs. Shamim
i'''

sentnece = 'Start a sentence and the bring it to an end'

print('\tTAB')
print(r'\tTAB')

pattern = re.compile(r'abc')    # pattern to search
matches = pattern.finditer(text_to_search)
for match in matches:
    print(match)

print(re.match('[a-zA-Z0-9]+$', 'asdfg134454'))
print(re.match('[a-zA-Z0-9]+$', 'asdfg13445@4'))