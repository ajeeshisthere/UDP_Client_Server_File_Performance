
# UDP Client Server File Transfer Systemcall Performance Check

This reposotory is created for evaluation and comparison of performance of file transfer.
in a UDP client server setup. 

**Compile the code**
```
  gcc client.c -o client
  gcc server.c -o server
```
**create a zero file of size 10MB**
```
  dd if=/dev/zero of=file_to_send bs=10M count=1
```
**Run the binary**

First run the server binary in the background, and copy the PID
```
 ./server&
 ```
 Server program have a 20 second sleep before starting any network related system calls.
 before that start the ``trace-cmd`` with the PID of server process.
 ```
 trace-cmd record -P <PID of server> -p function_graph
 ```
 In another console run the client binary after 20 seconds completed.

 ```
 ./client
 ```
 Once the client process is completed, exit from the trace-cmd using Ctrl+C

 Generate trace report using ``trace-cmd``
 ```
 trace-cmd report > report.txt
 ```

**Note**

Adjust the iteration count in client program to increase the timing. Also to increase the file size change the count or block size of ``dd`` command
