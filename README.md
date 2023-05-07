# DatingApp

  This project began as a difficult class project, which I later continued and finished independently. The goal was to build a dating app, with a number of constraints. Given a file of members and their attributes (members.txt), and a file of attributes and their compatible attributes (translator.txt). I was to write a program that given the input of a member's email and a desired minimum number of compatible attributes, would output the emails of compatible members and their shared attributes. 

  However, this was to be done with a number of constraints, specifically on structures I could not use, including maps and sets. Instead, I had to write code for a Radix Tree data structure to store and search through the various datasets needed for this project. During the class, I was unable to successfully create this, but after coming back to it a few times, I got this difficult (but very space-efficient) structure to work, and this project is now complete. The goal of this project was to work with finnicky structures, where I had to be very careful about pointers, memory allocation and deallocation.
  
  If anyone wishes to run this themselves, they must change lines 13 and 14 of main.cpp to the directories where they save members.txt and translator.txt.
  
  The following picture is an example of the app in action:
  
  <img width="493" alt="Screen Shot 2023-05-06 at 7 34 53 PM" src="https://user-images.githubusercontent.com/97066772/236654980-ba01226e-d023-4383-8097-69d866591fdb.png">
