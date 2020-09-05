#!/bin/python

from pylib.config_data import ConfigData

def main():
    import argparse

    parser = argparse.ArgumentParser("test_executer.py", description="Launches the test suite with the given configuration file.")
    parser.add_argument("config", help="The frameworks test configuration file.")
    parser.add_argument("-c", "--compile", action="store_true", help="Only compile the requested tests.")
    args = parser.parse_args()

    testobj = ConfigData.create_from_json(args.config)

    for compiled_test in testobj.compile_all():
        if args.compile:
            continue
        compiled_test[0].upload(compiled_test)
        compiled_test[0].verify(compiled_test)

if __name__ == "__main__":
    main()
