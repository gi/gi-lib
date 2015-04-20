# -*- coding: utf-8 -*-
"""
Copyright (C) Vehicle Data Science Corporation
"""


def isbreakpoint(obj, *scopes):
    if not scopes:
        return False
    breakpoints = obj
    if hasattr(obj, 'breakpoints'):
        breakpoints = obj.breakpoints
    for scope in scopes:
        try:
            breakpoints = breakpoints[scope]
        except KeyError:
            return False
    if isinstance(breakpoints, bool):
        return breakpoints
    try:
        return breakpoints['*']
    except KeyError:
        return False
