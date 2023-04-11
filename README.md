# UDP_Client_Server_File_Perofrmance


**Compile the code**

  gcc client.c -o client
  
  gcc server.c -o server

**create a zero file of size 1GB**

  dd if=/dev/zero of=file_to_send bs=1G count=1

**Run the binary**

 ./server
 ./client
 
 **execute the perf analysis at thi time**
 
**Note**

Adjust the iteration count in client program to increase the timing
