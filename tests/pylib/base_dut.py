import subprocess
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
    
    def compile(self, test : BaseTestConfig):
        print("Compiling {}...".format(test))
        subprocess.check_call(["arduino-cli.exe", "compile", "--fqbn", self.fqbn, "--libraries", ".\\libraries", str(test)])

    def upload(self, test : BaseTestConfig):
        print("Uploading {}...".format(test))
        subprocess.check_call(["arduino-cli.exe", "upload", "--fqbn", self.fqbn, "-p", self.port, str(test)])

    def verify(self, test : BaseTestConfig):
        import re
        import time
        import serial

        print("Verifying {}...".format(test))
        affirmative = ["SUCCESS", "success", "PASSED", "passed"]
        negative = ["FAILURE", "failure", "FAILED", "failed"]
        test_status_verifier = re.compile(r"(?P<status>{yes}|{no})".format(yes="|".join(affirmative), no="|".join(negative)))
        ser = serial.Serial(
            port = self.port,
            baudrate = self.baud_rate,
            parity = serial.PARITY_NONE,
            stopbits = serial.STOPBITS_ONE,
            bytesize = serial.EIGHTBITS,
            timeout = 0
        )
        print("Connection established. Searching for test status code...")

        timeout = 15
        complete_str = ""
        status = "UNKNOWN"
        for _ in range(1, timeout):
            if ser.in_waiting:
                input_str = ser.read_all().decode('utf-8')
                print(input_str, end="")
                complete_str += input_str
                match = test_status_verifier.search(complete_str)
                if match is not None:
                    status = "SUCCESS" if match.group('status') in affirmative else "FAILURE"
                    break
            time.sleep(1)
        
        ser.close()
        print("Test {} status is was '{}'!".format(test, status))

    def __str__(self):
        return "\n".join([
            "Device Manufacturer: " + self.device_manufacturer,
            "Chip Manufacturer: " + self.chip_manufacturer,
            "Device Name: " + self.device_name,
            "Port: " + self.port,
            "Baud Rate: " + str(self.baud_rate),
            "Extras: " + str(self.extras),
        ])
