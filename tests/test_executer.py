#!/bin/python

import subprocess
from pylib.config_data import ConfigData, BaseTestConfig, BaseDut

def compile_all(configuration : ConfigData):
    for test_to_compile in [configuration.test_suite + "\\" + test.name for test in configuration.tests]:
        compile(configuration.dut, test_to_compile)
        yield test_to_compile

def compile(dut : BaseDut, test : BaseTestConfig):
    print("Compiling {}...".format(test))
    subprocess.check_call(["arduino-cli.exe", "compile", "--fqbn", dut.fqbn, "--libraries", ".\\libraries", str(test)])

def upload(dut : BaseDut, test : BaseTestConfig):
    print("Uploading {}...".format(test))
    subprocess.check_call(["arduino-cli.exe", "upload", "--fqbn", dut.fqbn, "-p", dut.port, str(test)])

def verify(dut : BaseDut, test : BaseTestConfig):
    import re
    import time
    import serial

    print("Verifying {}...".format(test))
    affirmative = ["SUCCESS", "success", "PASSED", "passed"]
    negative = ["FAILURE", "failure", "FAILED", "failed"]
    test_status_verifier = re.compile(r"(?P<status>{yes}|{no})".format(yes="|".join(affirmative), no="|".join(negative)))
    ser = serial.Serial(
		port = dut.port,
		baudrate = dut.baud_rate,
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

def main():
    import argparse

    parser = argparse.ArgumentParser("test_executer.py", description="Launches the test suite with the given configuration file.")
    parser.add_argument("config", help="The frameworks test configuration file.")
    parser.add_argument("-c", "--compile", action="store_true", help="Only compile the requested tests.")
    args = parser.parse_args()

    testobj = ConfigData.create_from_json(args.config)

    if args.compile:
        for _ in compile_all(testobj): pass
    else:
        for compiled_test in compile_all(testobj):
            upload(testobj.dut, compiled_test)
            verify(testobj.dut, compiled_test)

if __name__ == "__main__":
    main()
