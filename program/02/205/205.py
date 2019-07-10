#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import threading

class recursive_mutex_thread():
    def __init__(self):
        self.shared_resource = 1000000
        self.mutex = threading.RLock()

    def deposit(self, n: int):
        with self.mutex:
            self.shared_resource += n

    def add_interest(self):
        with self.mutex:
            i = self.shared_resource * 0.05
            self.deposit( i )

    def thread_A(self):
        print("thread_A(): deposit( 10000 ) ... ")
        self.deposit( 10000 )
        print("thread_A(): deposit( 10000 ) done. ")

    def thread_B(self):
        print("thread_B(): add_interest() ... ")
        self.add_interest()
        print("thread_B(): add_interest() done.")

def main():
    b = recursive_mutex_thread()
    t1 = threading.Thread(target=b.thread_A)
    t1.start()
    t2 = threading.Thread(target=b.thread_B)
    t2.start()
    t1.join()
    t2.join()
    print(f"main(): shared_resource == {b.shared_resource}")

main()