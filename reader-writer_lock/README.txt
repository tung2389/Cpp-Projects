# Reader-Writer Lock in modern C++

## Usage
- Run the main code and produce data:
```c++
g++ -std=c++2a -pthread main.cpp -o main
./main
```

- Then run plot.py to plot the result:
```python
python3 plot.py
```

## Collaboration statement:
- I worked individually on this project.

## References:
- Concurrent Control with 'Readers' and 'Writers', Courtois et al. 1971: https://dl.acm.org/doi/pdf/10.1145/362759.362813
- https://eli.thegreenplace.net/2019/implementing-reader-writer-locks/
