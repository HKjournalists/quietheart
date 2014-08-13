""" 
Device base class, it defines device common operations.
"""

class DutBase:
    def loadDriver(self):
        pass

    def unloadDriver(self):
        pass

    def startSupplicant(self):
        pass

    def stopSupplicant(self):
        pass

    def connectAp(self, ssid, key):
        pass