#!/usr/bin/python
# motion-driver-client.py
import serial, sys, time, string, pygame
# Android orientation enums
        if quat_delegate:
        if debug_delegate:
        if data_delegate:
        self.packets = []
    def read(self):
    def write(self,a):
    def close(self):
    def write_log(self,fname):
# ===========  PACKET DELEGATES  ==========
class empty_packet_delegate(packet_delegate):
class cube_packet_viewer (packet_delegate):
    def loop(self,event):
    def dispatch(self,p):
class debug_packet_viewer (packet_delegate):
    def dispatch(self,p):
class data_packet_viewer (packet_delegate):
    def dispatch(self,p):
# =============== PACKETS ================= 
# For 32-bit signed integers.
class debug_packet (object):
            pass
    def display(self):
class quat_packet (object):
    def display(self):
    def to_q(self):
# =============== MAIN ======================
    pygame.init()
    reader = motion_driver_packet_reader(comport, 
    while 1:
        # TODO: If system load is too high, increase this sleep time.
