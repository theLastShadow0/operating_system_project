# Team Members: Andres Lopez & Jair Acosta
Operating Systems Project Description:

Throughout the course the team will be working on developing a functional Operating System.

Assignment 1:
For this first part of your project and assignment you are responsible to set up a repository on GitHub together with your teammate. You will start working on your OS simulator. At this point, your program should simulate the following:

    Booting the system
    Login authentication
    Process creation and termination

Assignment 2:
Using Pthreads
In this assignment you will get familiarized with the POSIX threads library (Pthreads). You will implement your programming solution, using NO threads, using ONE thread, and using MANY threads.
Your program will read in from a file where each line will represent a student, and will have a field to store whether this student has passed the successfully passed the course or not. 
Your input file will look like this:

25478 1
14525 1
15423 0
.
.
.
You will create a structure (array, fixed size) that holds one entry per student(per line in the file). Your program should have a function that can be called and will return the percentage of students that have passed the course.
Now, do the same with one thread, and then with many thread. For the many threads implementation, the first argument passed in the command line will specify how many threads to use. i.e.,
./manythreads 10
