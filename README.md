# UNIX file I/O
This project searches a keyword in a text file
 
 ## How to execute
 1. ``` $ make ```
 2. After you execute Makefile, the program will be created.
    lorem.txt is the example text file.    
    
      ![image](https://user-images.githubusercontent.com/92200502/173567672-34ffc80f-7f39-4638-bcc4-573a6df5c40d.png)
      
    ``` $./proj1.out lorem.txt ```   
    The name of text file must be given as command line argument. After you execute the program, ```Enter Keyword(s) :``` wil be shown, then type the word to show the place of the word.

 3. Search a single word.   
       
    After you execute the program, ```Enter Keyword(s) :``` wil be shown, then type the word to show the place of the word.
    In the image, I typed "the". The result is ```1:8, 2:5,2:12,4:12 ```. ```1:8```means that ``` the ``` is located in 1st line and it is 8th word in the line.  
    ![image](https://user-images.githubusercontent.com/92200502/173566821-8218aa4e-7326-4aea-b056-ae8ace07b3e9.png)
   
5. Search multiple words.    
     You can search multiple words also as below image shows, the program'll print out just the line number,
 
   ![image](https://user-images.githubusercontent.com/92200502/173569121-b99ecab3-57cb-47a3-90d1-b55d9dec695c.png)
   
6. Search phrase.
   If you type multi-words inside double quotes, it will find the lines that contain the phrase and print out the index of the first word.
   ```[line number]:[start index of the phrase]```
   
   ![image](https://user-images.githubusercontent.com/92200502/173569455-c1c7932b-30de-4258-9fe3-dffc3db5fc17.png)
7. Searching a keyword using a wild character.   
 ```[word1] * [word2]```
 The program print out the locations of the keyword that contains a single word in between word1
 
   ![image](https://user-images.githubusercontent.com/92200502/173571797-78b41847-6467-4f5a-9726-602737af8be3.png)
## Other descriptions
1. Line number and the word index start from 1, not from 0
2. The program counts an empty line.
3. Word is a string separated by white spaces (tab, space, new line)
4. Case sensitive search:  ‘Hi’ and ‘hi’ are two different words. 
5. Punctuation marks: ‘industry’ and ‘industry’s’ are two different words.
6. This program must be implemented in Linux environment
