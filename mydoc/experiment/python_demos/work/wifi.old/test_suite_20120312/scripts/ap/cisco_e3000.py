""" 
Cisco E3000 Access point .
"""
import sys
import os

from base import ApBase

from selenium import webdriver
from selenium.webdriver.support.ui import Select

class CiscoE3000(ApBase):
    def __init__(self,mac):
        self.mac = mac
        if 0:
            self.ip="192.168.1.1"
            self.admin="admin"
            self.password="myadmin"
            self.serial="CVQ01k634585"
            self.submask="255.255.255.0"
            self.dhcp="enable"
            self.dns="10.1.10.254"
            self.netMode5g="Mixed"
            self.netMode2g="Mixed"
            self.passphrase5g="password"
            self.passphrase2g="password"
            self.ssid2g="Cisco34585"
            self.ssid5g="Cisco34585"
            self.channelWidth5g="Auto(20MHz or 40MHz)"
            self.channelWidth2g="20MHz only"
            self.channel5g="Auto (DFS)"
            self.channel2g="Auto"
            self.ssidBroadcast5g="enable"
            self.ssidBroadcast2g="enable"

    def turnOn(self):
        ApBase.turnOn(self)
        print 'CiscoE3000 turnOn'

    def turnOff(self):
        ApBase.turnOff(self)
        print 'CiscoE3000 turnOff'

    def openWebDriver(self,params):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(20)
        self.base_url = "http://" + self.admin + ":" + self.password + "@" + self.ip

    def closeWebDriver(self):
        self.driver.quit()

    def reboot(self):
        ApBase.reboot(self)
        print 'CiscoE3000 reboot'

    def setChannelWidth(self,ChannelWidth):       
          dict_ChannelWidth2G={"A":"Auto(20MHz or 40MHz)","20":"20MHz only"}
          dict_ChannelWidth5G={"A":"Auto(20MHz or 40MHz)","20":"20MHz only","40":"40MHz only"}
          driver = self.driver
          driver.get(self.base_url + "/")
          driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()  
          for key in ChannelWidth.keys():
              if key=='5G'and self.netMode5g != "Disabled" and self.netMode5g!='Wireless-A Only': 
                  Select(driver.find_element_by_name("_wl1_nbw")).select_by_visible_text(dict_ChannelWidth5G[ChannelWidth["5G"]])    
              if key=='2G'and self.netMode2g != "Disabled" and self.netMode2g!='Wireless-B/G Only' and  self.netMode2g !='Wireless-B Only' and self.netMode2g!='Wireless-G Only':        
                  Select(driver.find_element_by_name("_wl0_nbw")).select_by_visible_text(dict_ChannelWidth2G[ChannelWidth["2G"]])    
          driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
          driver.find_element_by_name("action").click()
          if key=='5G'and self.netMode5g != "Disabled" and self.netMode5g!='Wireless-A Only':     
              self.channelWidth5g=dict_ChannelWidth5G[ChannelWidth["5G"]]
          if key=='2G'and self.netMode2g != "Disabled" and self.netMode2g!='Wireless-B/G Only' and  self.netMode2g !='Wireless-B Only' and self.netMode2g!='Wireless-G Only':               
              self.channelWidth2g=dict_ChannelWidth2G[ChannelWidth["2G"]]

    def setChannel(self,channel):
          dict_channel5G= {'36':'36 - 5.180GHz', '40':'40 - 5.200GHz', '44':'44 - 5.220GHz', '48':'48 - 5.240GHz', '149':'149 - 5.745GHz', '153':'153 - 5.765GHz', '157':'157 - 5.785GHz', '161':'161 - 5.805GHz',"A":"Auto (DFS)"}
          dict_channel2G= {'1':'1 - 2.412GHZ', '2':'2 - 2.417GHZ', '3':'3 - 2.422GHZ', '4':'4 - 2.427GHZ', '5':'5 - 2.432GHZ', '6':'6 - 2.437GHZ', '7':'7 - 2.442GHZ', '8':'8 - 2.447GHZ','9':'9 - 2.452GHZ', '10':'10 - 2.457GHZ', '11':'11 - 2.462GHZ',"A":"Auto"}
          driver = self.driver
          driver.get(self.base_url + "/")
          driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
          for key in channel.keys():
              if key=='5G'and self.netMode5g != "Disabled": 
                  Select(driver.find_element_by_name("_wl1_channel")).select_by_visible_text(dict_channel5G[channel["5G"]])    
              if key=='2G'and self.netMode2g != "Disabled":        
                  Select(driver.find_element_by_name("_wl0_channel")).select_by_visible_text(dict_channel2G[channel["2G"]])
          driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
          driver.find_element_by_name("action").click()
          if key == '5G' and self.netMode5g != "Disabled":       
              self.channel5g=dict_channel5G[channel["5G"]]
          if key == '2G' and self.netMode2g != "Disabled":         
              self.channel2g=dict_channel2G[channel["2G"]]

    def setSecurityMode(self,security_mode):
        dict_SecurityMode_5G={"WPA2/WPA":"WPA2/WPA mixed Mode","WPA2":"WPA2 Personal","WPA":"WPA Personal","D":"Disabled"}
        dict_SecurityMode_2G={"WPA2/WPA":"WPA2/WPA mixed Mode","WPA2":"WPA2 Personal","WPA":"WPA Personal","D":"Disabled"}
        driver = self.driver     
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_css_selector("td.small > a").click()
        for key in security_mode.keys():
              if key=='5G' and security_mode["5G"]!='D': 
                  Select(driver.find_element_by_name("wl1_security_mode")).select_by_visible_text(dict_SecurityMode_5G[security_mode["5G"]])
                  #driver.find_element_by_name("wl1_wpa_psk").clear()
                  #driver.find_element_by_name("wl1_wpa_psk").send_keys(self.passphrase5g) 
                  #setPassphrase(self.)
                  print "5gif----------",self.passphrase5g 
              elif security_mode["5G"]=='D':
                  Select(driver.find_element_by_name("wl1_security_mode")).select_by_visible_text(dict_SecurityMode_5G[security_mode["5G"]])
                  #  print "5gelse----------",self.passphrase5g 
              if key=='2G' and security_mode["2G"]!='D':        
                  Select(driver.find_element_by_name("wl0_security_mode")).select_by_visible_text(dict_SecurityMode_2G[security_mode["2G"]])
                  #driver.find_element_by_name("wl0_wpa_psk").clear()
                  #driver.find_element_by_name("wl0_wpa_psk").send_keys(self.passphrase2g)
                  #  print "2gif----------",self.passphrase2g
              elif security_mode["2G"]=='D':
                  Select(driver.find_element_by_name("wl0_security_mode")).select_by_visible_text(dict_SecurityMode_2G[security_mode["2G"]])
                  #print "2gelse----------",self.passphrase2g
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        for key in security_mode.keys():
            if key=='5G':
               self.securityMode5g=dict_SecurityMode_5G[security_mode["5G"]]
               # print "5g1----------",self.passphrase5g 
            if key=='2G':
               #print "2g1----------",self.passphrase2g 
               self.securityMode2g=dict_SecurityMode_2G[security_mode["2G"]]

    
    def setRadioOFF(self,netmode):
        dict_wmode = {'D':'Disabled'}
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
#   if mode.find("24G") != -1 :
        for key in netmode.keys():
            if key == '2G':
               netmode2g = netmode["2G"]
               Select(driver.find_element_by_name("wl0_net_mode")).select_by_visible_text(dict_wmode[netmode2g])
#       if mode.find("5G") != -1 :
        for key in netmode.keys():
            if key == "5G":
                netmode5g = netmode["5G"]
                Select(driver.find_element_by_name("wl1_net_mode")).select_by_visible_text(dict_wmode[netmode5g])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        for key in netmode.keys():
            if key == '2G':
               self.netmode_24G=dict_wmode[netmode2g]
        for key in netmode.keys():
            if key == "5G":
                self.netmode_5G=dict_wmode[netmode5g]

    def setWirelessMode(self, param):
        netMode = param["netMode"]
        dictMode5g = {'A':'Wireless-A Only', 'N':'Wireless-N Only', 'M':'Mixed'}
        dictMode2g = {'B/G':'Wireless-B/G Only', 'B':'Wireless-B Only', 'G':'Wireless-G Only', 'M':'Mixed', 'N':'Wireless-N Only'}
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        for key in netMode:
            if "2G" == key:
                Select(driver.find_element_by_name("wl0_net_mode")).select_by_visible_text(dictMode2g[netMode[key]])
            if "5G" == key:
                Select(driver.find_element_by_name("wl1_net_mode")).select_by_visible_text(dictMode5g[netMode[key]])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()

        for key in netMode:
            if "2G" == key:
                self.netMode2g=dictMode2g[netMode[key]]
            if "5G" == key:
                self.netMode5g=dictMode5g[netMode[key]]

    def setDns(self,ipaddr):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_css_selector("a").click()
        driver.find_element_by_id("dns00").clear()
        driver.find_element_by_id("dns00").send_keys(self.dns.split('.')[0])
        driver.find_element_by_id("dns01").clear()
        driver.find_element_by_id("dns01").send_keys(self.dns.split('.')[1])
        driver.find_element_by_id("dns02").clear()
        driver.find_element_by_id("dns02").send_keys(self.dns.split('.')[2])
        driver.find_element_by_id("dns03").clear()
        driver.find_element_by_id("dns03").send_keys(self.dns.split('.')[3])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        self.dns=ipaddr


    def setParkingState(self):
        ApBase.setParkingState(self)
        print 'CiscoE3000 setParkingState'

    def dump(self):
        ApBase.dump(self)

    
    def setSSID(self, ssid):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        for key in ssid.keys():
            if key == '5G' and self.netMode5g != "Disabled":
                driver.find_element_by_name("wl1_ssid").clear()
                driver.find_element_by_name("wl1_ssid").send_keys(ssid['5G'])
            if key == '2G' and self.netMode2g != "Disabled":
                driver.find_element_by_name("wl0_ssid").clear()
                driver.find_element_by_name("wl0_ssid").send_keys(ssid['2G'])
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        for key in ssid.keys():
            if key == '5G' and self.netMode5g != "Disabled":
                self.ssid5g = ssid['5G']
            if key == '2G' and self.netMode2g != "Disabled":
                self.ssid2g = ssid['2G']

    def setSsidBroadcast(self, ssidBroadcast):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        for key in ssidBroadcast.keys():
            if key == '5G' and self.netMode5g != "Disabled":
                if ssidBroadcast['5G'] == 'enable':
                    driver.find_element_by_name("wl1_closed").click()
                elif ssidBroadcast['5G'] == 'disable':
                    driver.find_element_by_xpath("(//input[@name='wl1_closed'])[2]").click()
            if key == '2G' and self.netMode2g != "Disabled":
                if ssidBroadcast['2G'] == 'enable':
                    driver.find_element_by_name("wl0_closed").click()
                elif ssidBroadcast['2G'] == 'disable':
                    driver.find_element_by_xpath("(//input[@name='wl0_closed'])[2]").click()
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        for key in ssidBroadcast.keys():
            if key == '5G' and self.netMode5g != "Disabled":
                self.ssidBroadcast5g = ssidBroadcast['5G']
            if key == '2G' and self.netMode2g != "Disabled":
                self.ssidBroadcast2g = ssidBroadcast['2G']

    def setPassphrase(self,passphrase):
        #dict_SecurityMode_5G={"WPA2/WPA":"WPA2/WPA mixed Mode","WPA2":"WPA2 Personal","WPA":"WPA Personal","D":"Disabled"}
        #dict_SecurityMode_2G={"WPA2/WPA":"WPA2/WPA mixed Mode","WPA2":"WPA2 Personal","WPA":"WPA Personal","D":"Disabled"}

        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[2]/font/a").click()
        driver.find_element_by_css_selector("td.small > a").click()

        for key in passphrase.keys():
            if key == "5G":
               passphrase5g = passphrase["5G"]
               if "WPA2/WPA mixed Mode" ==self.securityMode5g or "WPA2 Personal" == self.securityMode5g or "WPA Personal" == self.securityMode5g: 
                   driver.find_element_by_name("wl1_wpa_psk").clear()
                   driver.find_element_by_name("wl1_wpa_psk").send_keys(passphrase5g)
               elif 'Disabled' ==self.securityMode5g:
                     pass
            if key == "2G":
               passphrase2g = passphrase["2G"]
               if 'WPA2 Personal' == self.securityMode2g :
                   driver.find_element_by_name("wl0_wpa_psk").clear()
                   driver.find_element_by_name("wl0_wpa_psk").send_keys(passphrase2g)
               elif 'Disabled' == self.securityMode2g :
                        pass
        driver.find_element_by_xpath("//table[@id='AutoNumber9']/tbody/tr[2]/td/table/tbody/tr[2]/td[3]/table/tbody/tr/td/font/a").click()
        driver.find_element_by_name("action").click()
        for key in passphrase.keys():
            if key == "5G":
               if 'WPA2/WPA Mixed Mode' ==self.securityMode5g or 'WPA2 Personal' == self.securityMode5g or 'WPA Personal' == self.securityMode5g: 
                   self.passphrase5g = passphrase5g;
        for key in passphrase.keys():
            if key == "2G":
               if 'WPA2 Personal' == self.securityMode2g :
                   self.passphrase2g = passphrase2g;

    def restore_factory_default(self):
        driver = self.driver
        driver.get(self.base_url + "/")
        driver.find_element_by_xpath("//table[@id='table3']/tbody/tr[2]/td[7]/p/font/a").click()
        driver.find_element_by_xpath("//table[@id='AutoNumber1']/tbody/tr[3]/td/table/tbody/tr/td[11]/a").click()
        driver.find_element_by_name("restore_b").click()
        # ERROR: Caught exception [ERROR: Unsupported command [getConfirmation]]

    def test(self,params):
        ''' Test function for develop.
            '''
        print "run test function, param value are:",params
        print "all data attributes are:",self.__dict__


if __name__ == '__main__':
    e3000 = CiscoE3000()
    e3000.setParameters({'name':'E3000', 'ip':'10.1.10.32:8080', 'submask':'255.255.255.0', 'dns':'10.1.10.254', 'admin':'admin', 'password':'myadmin'})
    e3000.openWebDriver()
    e3000.setWirelessMode('A','24G')
    e3000.setRadioOFF('D','24G')
    e3000.setChannelWidth('20','','5G')
    e3000.setChannel('','1','24G')
    e3000.setSecurityMode('WPA2 Personal','WPA2 Personal','5G24G')
    e3000.setSSID('Cisco6300','5G')
    e3000.setSsidBroadcast('enable','5G')
    e3000.closeWebDriver()
    e3000.setWirelessMode_24G('B/G')