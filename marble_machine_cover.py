#!/usr/bin/env python
# coding: utf-8
import time

music_sheet = [[ [1], [8, 1], [4], [8, 1], [5], # phase 1
                 [6], [5], [8, 1], [4], [6], [5, 8, 1], [2]],
               [ [2], [9, 2], [4], [9, 2], #phase 2
                 [5], [6], [5], [9, 2], [7], [6], [5, 9, 2], [2]],
               [ [2], [7, 9], [4], [7, 9], #phase 3
                 [2], [3], [4], [7, 9], [5], [6], [5, 7, 9], [8]],
               [ [8], [1], [8], [4], # phase 4
                 [2], [1], [9], [2], [3], [4], [7, 9], [5], [6], [5], [1]]]

def set_led(num):
    with open('/dev/myled0','w') as f:
        print >> f, num

def reset_led():
    with open('/dev/myled0','w') as f:
        print >> f, "F"


if __name__ == '__main__':
    for phase in music_sheet:
        for notes in phase:
            if len(notes) > 1:
                for n in notes:
                    set_led(n)
                time.sleep(0.11) # wait after multiple notes
            else:
                set_led(notes[0])
                time.sleep(0.307) # wait after one note
            reset_led()
    reset_led() 
