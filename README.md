# Concurrent_Programming
There are multiple choices for **Conccurrent Programming**. In this program it is implemented by **I/O multiplexing with select()**.
### Making chatting roomusing select()
- The clients insert the nameof itself
- The client is under an infinite loop with conditional exit(“quit”)
- When client A sends a message, server receives it and sends it back to the client A
- When a client joins or leaves the chatting room, server prints a message with the number of current clients.
- FD_ISSET() is used to check if there is input in specific file descriptor
## Running Example
![image](https://user-images.githubusercontent.com/92200502/173601381-9f0c744b-d4c0-4922-b3f9-a6f86a2dd7b7.png)

