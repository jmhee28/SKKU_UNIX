# Sychronization

## Monte Carlo Method

![image](https://user-images.githubusercontent.com/92200502/173604574-368b10ad-ce3b-4594-a7bc-1051a0b444a4.png)

- The parallel version get two command line arguments.   
 
    1) the number of threads
    2) the number of random points per thread
- Each thread creates random points and counts the number of points that are inside the circle
- Each thread tells the main thread about the number of points it found to be inside the circle using global variable or static variable
- Main thread calculates the value for pi using thevariable after all threads exited
## Running Example
```./e13.out 10000 100```   
```3.142100```
