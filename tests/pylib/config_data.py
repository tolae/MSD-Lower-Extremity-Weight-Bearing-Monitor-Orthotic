class ConfigData(object):
    def __init__(self, **fields):
        self.dut = dict()
        self.test_suite = ""
        self.tests = []
        self.__dict__.update(fields)
        temp_tests = self.tests.copy()
        self.tests.clear()
        for test in temp_tests:
            self.tests.append(BaseTestConfig(**test))
        self.dut = BaseDut(**self.dut)
    
    @staticmethod
    def create_from_json(json_file : str):
        import json
        with open(json_file, "r") as fp:
            test_config = json.load(fp)
            return ConfigData(**test_config)

    def __str__(self):
        return "\n".join([
            "Dut: {\n" + str(self.dut) + "\n}",
            "Test Suite: " + self.test_suite,
            "Tests: " + ",".join([str(test) for test in self.tests])
        ])

class BaseTestConfig(object):
    def __init__(self, **fields):
        self.name = ""
        self.__dict__.update(fields)
        self.name += "_test"

    def __str__(self):
        return self.name

class BaseDut(object):
    def __init__(self, **fields):
        self.port = ""
        self.baud_rate = 0
        self.device_manufacturer = ""
        self.chip_manufacturer = ""
        self.device_name = ""
        self.extras = dict()
        self.__dict__.update(fields)

    @property
    def fqbn(self):
        base = [self.device_manufacturer, self.chip_manufacturer, self.device_name]
        for key, value in zip(self.extras.keys(), self.extras.values()):
            base.append(key + "=" + value)
        return ":".join(base)
    
    def __str__(self):
        return "\n".join([
            "Device Manufacturer: " + self.device_manufacturer,
            "Chip Manufacturer: " + self.chip_manufacturer,
            "Device Name: " + self.device_name,
            "Port: " + self.port,
            "Baud Rate: " + self.baud_rate,
            "Extras: " + str(self.extras),
        ])
