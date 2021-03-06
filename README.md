## Author: Emeka Umeozo

## Instructions 
 - Call `make` to compile the files
 - To run the receiver, call `./receiver <port number>`
 - To run the sender, call: `./sender <receiver's hostname> <receiver's port> <window size> <timeout(secs)>`

## How the programs work
**SENDER:**

- The program validates the program arguments and prompts the user if the wrong arguments are given.
- The program receives any input and sends it to the receiver, only when the sending window is not full.
- Each input is sent as a frame, containing a sequence number, the data, the time it was sent, and a *sent* flag.
- The sequence number starts with zero and increments by one for each message. The sequence number does not repeat.
i.e; for a window size of 3 with 5 frames to be sent, the sequence numbers are `0, 1, 2, 3, 4`. Not `0, 1, 2, 0, 1`.
- When an ACK n is received, the sender removes all sent frames with a sequence number less than n.
- A thread watches every frame's sent time, and retransmits a frame if it has been unacknowledged beyond the given timeout
value.

**RECEIVER:**

- The program validates the program arguments and prompts the user if the wrong arguments are given.
- When a frame is received, the program does a corruption simulation test twice by prompting the user for a value.
    - The frame is deemed to not be corrupted or lost only if the user enters 'Y'.
    - The first simulation is done before processing the frame sequence received.
    - The second simulation done before sending the ACK to the sender.
- If the frame received has a sequence number that is larger than the last acknowledged sequence, but is not the next 
  order sequence, the frame is dropped
- If the frame received has a sequence number that is smaller than the last acknowledged sequence.
(caused by a retransmission), an ACK is sent with the last acknowledged sequence as its value.


## THINGS TO NOTE
 - The receiver is built to receive frames from only one sender.
