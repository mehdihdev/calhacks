import serial
import simpleaudio as sa
import random


clips = ["clip1.wav", "clip2.wav", "nevergonnagiveup.wav", "clip4.wav"]

def readserial(comport, baudrate):
    ser = serial.Serial(comport, baudrate, timeout=0.1)
    while True:
        data = ser.readline().decode().strip()
        if data:
            print(data)
            if data == "Success":
                wave_obj = sa.WaveObject.from_wave_file(random.choice(clips))
                play_obj = wave_obj.play()
                play_obj.wait_done()
            elif data == "Failure":
                wave_obj = sa.WaveObject.from_wave_file("shrek.wav")
                play_obj = wave_obj.play()
                play_obj.wait_done()
            else:
                pass
            data = "1"



if __name__ == '__main__':
    readserial('/dev/cu.usbserial-1120', 9600)