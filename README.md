# Inter_Process_Communication
## Simple chatting program
1. When the program starts, get sender’s id and receiver’s id from stdin
    - Parent → sender, child → receiver
3. Sender: 
    - Gets the message from stdin and sends the message to the receiver’s id         

3. Receiver:
    - Receives message from othersender   
    - Receives ack message from otherreceiver
    - Print out the message   
    - Send back ack message with read time
4. Quit the program if the user inputs “quit”
    - When quitting, print out “QUIT” to stdout
5. Output   
  - When sender receives ack from other receiver:
    - ```ACK FROM $ID AT$READ_TIME```
  - When receiver receives message from other sender
      - ```RECEIVED: $USER_MSG```
6. Example input/output

![image](https://user-images.githubusercontent.com/92200502/173586097-696e1777-aa8b-4474-a190-e00e52e9858f.png)
