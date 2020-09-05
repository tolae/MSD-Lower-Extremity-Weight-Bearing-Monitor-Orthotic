from .base_test_config import BaseTestConfig
from .base_dut import BaseDut

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
