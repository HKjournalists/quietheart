#!/usr/bin/python
import sys
import os

import parser.parser_api as parser_api
from factory_class import FactoryScenario
import lib.log_api as log_api

def run(scenario):



    moduleLog = log_api.initLogger("Apchannel")
    factory = FactoryScenario()
    ap = factory.instance(scenario)

    params = scenario.m_parameters
    moduleLog.debug(params)

    channel= params["channel"]
    ap.setChannel(channel)

if "__main__" == __name__:
    pass


