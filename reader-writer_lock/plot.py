import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

def plot_lock(filename, image):
    lock_data = pd.read_csv(filename)
    plt.plot(list(range(0, 2000)), lock_data['read'].tolist(), label = 'read')
    plt.plot(list(range(0, 2000)), lock_data['write'].tolist(), label = 'write')
    plt.xlabel('Time')
    plt.ylabel('Count')
    plt.legend()
    plt.savefig(image)
    plt.clf()

def plot_runtime(filename, image):
    runtime = pd.read_csv(filename)
    plt.plot(list(range(0, 100)), runtime['rprefer'].tolist(), label = 'rprefer')
    plt.plot(list(range(0, 100)), runtime['rprefer_cond'].tolist(), label = 'rprefer_cond')
    plt.plot(list(range(0, 100)), runtime['wprefer'].tolist(), label = 'wprefer')
    plt.plot(list(range(0, 100)), runtime['wprefer_cond'].tolist(), label = 'wprefer_cond')
    plt.xlabel('Time')
    plt.ylabel('Runtime')
    plt.legend()
    plt.savefig(image)
    plt.clf()

def main():
    plot_lock('rprefer_lock.csv', 'rprefer.jpg')
    plot_lock('rprefer_cond_lock.csv', 'rprefer_cond.jpg')
    plot_lock('wprefer_lock.csv', 'wprefer.jpg')
    plot_lock('wprefer_cond_lock.csv', 'wprefer_cond.jpg')

    plot_runtime('runtime.csv', 'runtime.jpg')
main()