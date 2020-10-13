class BaseTestConfig(object):
    def __init__(self, target_dut_name, **fields):
        self.name = ""
        self.__dict__.update(fields)
        self.name = "{suite}_tests\\{name}_test".format(
            suite=target_dut_name,
            name=self.name
        )

    def __str__(self):
        return self.name
