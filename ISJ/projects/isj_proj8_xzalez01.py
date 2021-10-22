#!/usr/bin/env python3

def first_with_given_key(iterable, key=lambda x: x):

    values = []

    for iter_object in iterable:
        if key(iter_object) not in values:
            values.append(key(iter_object))
            yield iter_object
