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

def dictionary(*args, **kwargs):
    """Creates a new Dictionary."""
    return Dictionary(*args, **kwargs)


class Dictionary(dict):
    """A dictionary object that does not throw a key error
    and allows for dot operator dereferencing instead of square brackets.
    """

    def __init__(self, *args, **kwargs):
        """Constructor.
        Args:
            kwargs - key/value pairs to populate this Dictionary.
        """
        super(Dictionary, self).__init__(*args, **kwargs)
        # for arg in args:
        #     if isinstance(arg, dict):
        #         kwargs.update(arg)
        self.update(self)

    @staticmethod
    def convert(x):
        if isinstance(x, dict):
            return Dictionary(x)
        if isinstance(x, (list, tuple)):
            return map(Dictionary.convert, x)
        return x

    def update(self, other=None, **kwargs):
        """Update the dictionary with the key/value pairs from `other`,
        overwriting existing keys.

        Accepts another dictionary object or an iterable of key/value pairs
        (as tuples or other iterables of length two).
        If keyword arguments are specified, the dictionary is then updated with
        those key/value pairs.
        """
        other = dict(other) if other is not None else {}
        other.update(kwargs)
        items = ((k, Dictionary.convert(v)) for k, v in other.iteritems())
        super(Dictionary, self).update(items)

    def __setitem__(self, key, value):
        """Sets the key/value pair, converting any nested dictionaries.
        Args:
            key - Key to set.
            value - Value to set for the provided key.
        """
        value = Dictionary.convert(value)
        super(Dictionary, self).__setitem__(key, value)

    __getitem__ = dict.get
    __getattr__ = __getitem__
    __setattr__ = __setitem__
    __delattr__ = dict.__delitem__


#==============================================================================
# Stack
#==============================================================================

def stack(iterable=[]):
    s = Stack()
    for obj in iterable:
        s.push(obj)
    return s


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

def deque(*args, **kwargs):
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

    pop_front = collections.deque.popleft
    pop_back = collections.deque.pop

    def push_front(self, obj):
        if self.maxlen == 0:
            return obj
        rv = self.back if len(self) == self.maxlen else None
        super(Deque, self).appendleft(obj)
        return rv

    appendleft = push_front

    def push_back(self, obj):
        if self.maxlen == 0:
            return obj
        rv = self.front if len(self) == self.maxlen else None
        super(Deque, self).append(obj)
        return rv

    append = push_back


#==============================================================================
# Queue
#==============================================================================

def queue(*args, **kwargs):
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
        return self._container.push_back(obj)


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

