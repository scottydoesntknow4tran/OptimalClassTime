# OptimalClassTime
Program that sorts through text files containing available class times and finds the times that match up for everyone

The idea behind this program is to find the optimal meeting time for a group of people to meet. The user can dicide how many people need to attend and this program can find the optimal meeting times for the group.
This program asks the user to input the files and it reads them using multiple linked lists to store the name of the person (name of the file), the day of the week, and the time of the day
After storing the data for all the files the user inputs the minimum number of matches they want for a meeting time
The program then prints the days and times that have at least the number of matches and the names of those people and the meeting times with more matches
There are example files attached with the names of people. These contain the days and times that the people can meet.
The program does not need the days of the week to be in order or the times to be in order and it gives an error messeage if it is not a number

The format of the files iare:

tue:18,8,8.5,9,9.5,10,10.5,16,16.5,17,17.5
mon:8,8.5,9.5,10,10.5,16,16.5,17,17.5,18,9
thu:16,16.5,17,18,17.5
fri:16.5,17,16,17.5,18
wed:8,17,8.5,9,9.5,10,10.5,16,16.5,17.5,18
