#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
"""

#==============================================================================
# Imports
#==============================================================================

import collections
import itertools

#==============================================================================
# Dictionary
#==============================================================================

class Dictionary(dict):
    
    __keyfn = lambda obj: obj
    
    def __init__(self, key=__keyfn):
        self._keyfn = key

    def __getitem__(self, obj):
        return super(Dictionary, self).__getitem__(self._keyfn(obj))

#==============================================================================
# Stack
#==============================================================================

def stack(iterable=[]):
    s = Stack()
    for obj in iterable:
        s.push(obj)
    return Stack()

class Stack(collections.Sequence):
    
    def __init__(self):
        self._container = []

    def __getitem__(self, index):
        return self._container[index]

    def __len__(self):
        return len(self._container)

    @property
    def top(self):
        return self._container[-1]

    def push(self, obj):
        self._container.append(obj)

    append = push

    def pushall(self, iterable):
        self._container.extend(iterable)

    extend = pushall

    def pop(self):
        return self._container.pop()

    def popall(self):
        elems = list(reversed(self._container))
        self._container.clear()
        return elems

    def clear(self):
        self._container.clear()

#==============================================================================
# Deque
#==============================================================================

def deque(**kwargs):
    return Deque(**kwargs)

class Deque(collections.deque):

    def __init__(self, iterable=None, maxlen=None):
        super(Deque, self).__init__(iterable, maxlen)

    @property
    def front(self):
        return self[0]

    @property
    def back(self):
        return self[-1]

    def pop_front(self):
        return super(Deque, self).popleft()

    def pop_back(self):
        return super(Deque, self).pop()

    def push_front(self, obj):
        if len(self) == self.maxlen > 0:
            rv = self.back
        elif self.maxlen == 0:
            rv = obj
        else:
            rv = None
        super(Deque, self).appendleft(obj)
        return rv

    appendleft = push_front

    def push_back(self, obj):
        if len(self) == self.maxlen > 0:
            rv = self.front
        elif self.maxlen == 0:
            rv = obj
        else:
            rv = None
        super(Deque, self).append(obj)
        return rv

    append = push_back

#==============================================================================
# Queue
#==============================================================================

def queue(**kwargs):
    return Queue(**kwargs)

class Queue(collections.Sequence):

    __container = Deque

    def __init__(self, iterable=None, maxlen=None, container=__container):
        self._container = container(iterable, maxlen)

    def __getitem__(self, index):
        return self._container[index]

    @property
    def front(self):
        return self._container[0]

    @property
    def back(self):
        return self._container[-1]

    @property
    def maxlen(self):
        return self._container.maxlen

    def pop(self):
        return self._container.pop_front()

    def push(self, obj):
        if len(self) == self.maxlen > 0:
            rv = self.front
        elif self.maxlen == 0:
            rv = obj
        else:
            rv = None
        self._container.push_back()
        return rv

#==============================================================================
# LookaheadBuffer
#==============================================================================


def lookahead(func):
    """Returns a lookahead buffer enabling peeking into an iterator."""
    @itertools.wraps(func)
    def wrapper(*args, **kwargs):
        return LookaheadBuffer(func(*args, **kwargs))
    return wrapper


class LookaheadBuffer(collections.Iterable):
    """Buffers an iterator or generator object, allowing peek capabilities."""

    def __init__(self, iterator):
        self._iterator = iterator
        self._last = None

    def __iter__(self):
        return self

    def next(self):
        if self._last is None:
            obj = self._iterator.next()
        else:
            obj = self._last
            self._last = None
        return obj

    def peek(self):
        if self._last is None:
            self._last = self._iterator.next()
        return self._last


