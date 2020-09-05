class BaseTestConfig(object):
    def __init__(self, **fields):
        self.name = ""
        self.__dict__.update(fields)
        self.name += "_test"

    def __str__(self):
        return self.name
