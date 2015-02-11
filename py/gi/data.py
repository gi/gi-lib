"""
Module: gi.data
"""

class Attribute(object):

    def __init__(self, name):
        self._name = name

    @property
    def name(self):
        return self._name

    def get(self, obj):
        return getattr(obj, self.name)

    def set(self, obj, value):
        return setattr(obj, self.name, value)

class cachedproperty(property):
    """A lazily evaluated, cached property descriptor.
    
    Setter and deleter cannot be set as their behavior is forced by
    the construction of the cached property. However a boolean set argument
    can be passed to indicate whether it is possible to fill the cache by
    assignment. Besides, cachedproperty implement __delete__, which in this
    particular context empties the cache so that the property can be
    recalculated on the next call.
    """

    def __init__(self, fget=None, fset=None, fdel=None, doc=None):
        super(cachedproperty, self).__init__(fget, fset, fdel, doc)
        self.cache = '_' + fget.__name__

    def __get__(self, obj, cls=None):
        if obj is None:
            return self
        try:
            return getattr(obj, self.cache)
        except AttributeError:
            pass
        if self.fget is None:
            raise AttributeError("unreadable attribute")
        setattr(obj, self.cache, self.fget(obj))
        return getattr(obj, self.cache)

    def __set__(self, obj, value):
        if self.fset is None:
            raise AttributeError("cannot set attribute")
        self.fset(obj, value)
        setattr(obj, self.cache, value)

    def __delete__(self, obj):
        if self.fdel is not None:
            self.fdel(obj)
            return
        try:
            delattr(obj, self.cache)
        except AttributeError:
            pass

    def getter(self, fget):
        return type(self)(fget, self.fset, self.fdel, self.__doc__)

    def setter(self, fset):
        return type(self)(self.fget, fset, self.fdel, self.__doc__)

    def deleter(self, fdel):
        return type(self)(self.fget, self.fset, fdel, self.__doc__)

    @classmethod
    def reset(cls, obj):
        """Resets all cached properties on obj (if declared in its class)."""
        attrs = type(obj).__dict__
        props = [k for k, v in attrs.items() if isinstance(v, cls)]
        for k in props: delattr(obj, k)
