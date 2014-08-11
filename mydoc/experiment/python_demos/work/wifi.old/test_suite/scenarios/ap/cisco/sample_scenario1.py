#!/usr/bin/python
import sys
import os

import parser.parser_api as parser_api
from factory_class import FactoryScenario
import lib.logtools as logtools

def run(scenario):

    moduleLog = logtools.logger
    factory = FactoryScenario()
    ap = factory.instance(scenario)

    params = scenario.m_parameters
    moduleLog.debug(params)

    ap.test(params)

if "__main__" == __name__:
    sub_dir = "scenarios"
    main_dir = sys.path[0]
    if main_dir.find(sub_dir) != -1:
        while os.path.basename(main_dir) != sub_dir:
            main_dir = os.path.dirname(main_dir)
        main_dir = os.path.dirname(main_dir)
    else:
        print "Path error, not in 'scenarios'."
        exit(1)
    scripts_dir = main_dir+os.sep+"scripts"
    sys.path.insert(1,scripts_dir)
    print "nothing to test!"
