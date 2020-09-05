from .base_test_config import BaseTestConfig

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
