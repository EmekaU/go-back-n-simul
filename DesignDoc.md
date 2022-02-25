Author: Emeka V Umeozo [11249945/cvu302]

Call **make** before you attempt to run the programs

Instructions: 
 - Run the sender and receiver on different versions of tux.
 - *** This program can only run on tux ***

**SENDER:**

Run Command: sender [receiver's hostname name] [receiver's port #] [window size] [timeout value]
Validation: 
 - The number of arguments are validated
 - The supplied port is inspected to validate that it falls within the correct range
 - The window size and timeout value are ***not*** inspected

What works:

 - The sender sends data once, but can't receive
 - When the sender attempts to send data the second time, a seg fault occurs.


**RECEIVER:**

Run Command: receiver [port number] [receiver's window size]

Validation: 
 - The number of arguments are validated
 - The supplied port is inspected to validate that it falls within the correct range
 - The window size is ***not*** inspected

What works:

 - The receiver can both send and receive data


Additions:

Receiver is built to receive frames from only one sender.
