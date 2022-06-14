# POSIX_threads
## Matrix-vector multiplication using multi-threading
- Multiplication result of M×N matrix and N×1 vector is M×1 vector
- Row size(M), column size(N) of matrix are received by command line arguments
    - ```./e11.out <row_size> <column_size>```
- Elements of matrix and vector are randomly assigned between 0~9 (data type is int)
- Create threads as much as the row size(M)
- Each thread performs a calculation on one row of the matrix
- thread_idand calculation results are delivered through the ```struct thread_data```
- Main function must wait other threads to terminate 
###   Matrix-Vector multiplication
![image](https://user-images.githubusercontent.com/92200502/173595890-f38aa36c-3e44-42ac-91f6-d39afd9e5a1f.png)

## Example
![image](https://user-images.githubusercontent.com/92200502/173596382-3a65c577-7f95-46cb-98fd-1f74fece76f7.png)

