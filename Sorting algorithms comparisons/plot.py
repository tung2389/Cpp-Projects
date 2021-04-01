import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

def main():
    data = pd.read_csv(os.path.dirname(__file__) + '/data.csv')
    plt.plot(data['length'].tolist(), data['selectionSort'].tolist(), label = 'Selection Sort')
    plt.plot(data['length'].tolist(), data['insertionSort'].tolist(), label = 'Insertion Sort')
    plt.plot(data['length'].tolist(), data['mergeSort'].tolist(), label = 'Merge Sort')
    plt.plot(data['length'].tolist(), data['quickSort'].tolist(), label = 'Quick Sort')
    plt.xlabel('Length of list')
    plt.ylabel('Run time (in second)')
    plt.yticks(np.arange(0, 27, step = 1.5), np.arange(0, 27, step = 1.5))
    plt.legend()
    plt.show()

main()