import matplotlib.pyplot as plt
from scipy.io import wavfile # get the api
from scipy.fftpack import fft
from basic_units import hertz
from pylab import *
import glob
import numpy as np

def f(filename):
    print(f"Parsing {filename}")
    fs, data = wavfile.read(filename)

    plt.clf()
    plt.cla()

    lf = abs(np.fft.rfft(data))

    b = plt.subplot(111)
    #b.set_xscale('log')
    b.set_xlabel('frequency [Hz]')
    b.set_ylabel('|amplitude|')
    plt.plot(lf)
    plt.savefig(filename + '.png')

files = glob.glob("./*.wav")

for i in files:
    f(i)
