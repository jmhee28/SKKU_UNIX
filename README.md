# UNIX file I/O
This project searches a keyword in a text file
 
 ## How to execute
 1. ``` $ make ```
 2. After you execute Makefile, the program will be created.
    lorem.txt is the example text file.    
    
      ![image](https://user-images.githubusercontent.com/92200502/173567672-34ffc80f-7f39-4638-bcc4-573a6df5c40d.png)

 3. Execution result is shown as below image.    
   ``` $./proj1.out lorem.txt ```   
    The name of text file must be given as command line argument.
    After you execute the program, ```Enter Keyword(s) :``` wil be shown, then type the word to show the place of the word.
    In the image, I typed "the". The result is ```1:8, 2:5,2:12,4:12 ```. ```1:8```means that ``` the ``` is located in 1st line and it is 8th word in the line.  
    ![image](https://user-images.githubusercontent.com/92200502/173566821-8218aa4e-7326-4aea-b056-ae8ace07b3e9.png)
   
4. You can search multiple words also as below image shows, the program'll print out just the line number,
 
 ![image](https://user-images.githubusercontent.com/92200502/173569121-b99ecab3-57cb-47a3-90d1-b55d9dec695c.png)
