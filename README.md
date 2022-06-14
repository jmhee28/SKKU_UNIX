# Catching_signals
1. The program gets a number N via argv[1]
2. Terminate the program if SIGINT(Ctrl+c) caught N times
3. When SIGQUIT(Ctrl+\) is caught, print "SIGQUIT caught, will be ignored" and do not terminate.
4. When SIGTSTP(Ctrl+z) is caught, print "SIGTSTP caught. This process will stop" and stop the process.
5. When SIGCONT is caught, print "SIGCONT caught”
6. Exmaple
![image](https://user-images.githubusercontent.com/92200502/173577806-e5d85500-377e-4cd4-87cc-a2fdb1e552b4.png)


