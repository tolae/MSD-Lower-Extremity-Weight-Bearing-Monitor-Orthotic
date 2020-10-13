from .base_test_config import BaseTestConfig
from .base_dut import BaseDut

class ConfigData(object):
    def __init__(self, **fields):
        self.duts = dict()
        self.tests = []
        self.__dict__.update(fields)
        # Create and add dut objects to dict
        for dut_name in [dut_name for dut_name in fields.keys() if "_dut" in dut_name]:
            self.duts[dut_name] = BaseDut(**fields[dut_name])
        # Create test objects
        temp_tests = self.tests.copy()
        self.tests.clear()
        for dut_name in self.duts.keys():
            dut_name_trimmed = dut_name.replace("_dut", "")
            for test in temp_tests:
                self.tests.append((self.duts[dut_name], BaseTestConfig(dut_name_trimmed, **test)))
    
    @staticmethod
    def create_from_json(json_file : str):
        import json
        with open(json_file, "r") as fp:
            test_config = json.load(fp)
            return ConfigData(**test_config)

    def compile_all(self):
        for test in self.tests:
            test[0].compile(test[1])
            yield test

    def __str__(self):
        return "\n".join([
            "Duts: " + ",".join(["\n{\n" + "{}: {}".format(dut, str(self.duts[dut])) + "\n}" for dut in self.duts.keys()]),
            "Tests: " + ",".join([str(test) for test in self.tests])
        ])
