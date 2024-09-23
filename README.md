<img src="https://github.com/user-attachments/assets/2ad86f70-12b4-4500-997d-9f8c1874a9b5" alt="Dal logo" width="80"/>
<h1>Associated with Dalhousie University</h1>

### CSCI2122
### Text Reassembly
#### Objectives

- Linked list manipulation
- Encapsulation
- Using self-created modules

#### Features
- Compute the maximum overlap between two linked lists using the `ll_overlap` function.
- Splice one linked list into another using the `ll_splice` function.
- Test program (`main.c`) provided to demonstrate usage.

#### Repository Structure
This repository contains two main directories:

- linkedlist: Implementation of linked list functions
- splicer: Application using linked lists to reassemble text segments

#### Problem 1: Match and Splice
Located in the linkedlist directory.

#### Problem 2: The Splicer
Located in the splicer directory.

#### Task:
Developing a program to reassemble pieces of text using linked lists.

#### Sample input and output
```
Input 
2
list 0 new
list 1 new
list 0 build 5 ali ben gem dan eve
list 1 build 5 gem dan eve ali ben
list 0 overlap 1
list 0 splice 1
list 1 print
end

Output
List 0: new list
[ ] (0 items)
List 1: new list
[ ] (0 items)
List 0: build
[ ali ben gem dan eve ] (5 items)
List 1: build
[ gem dan eve ali ben ] (5 items)
List 0: Overlap between lists 0 and 1 is 3
List 0: List 1 spliced to the end of list 0
[ ali ben gem dan eve ali ben ] (7 items)
List 1: print
[ gem dan eve ] (3 items)
```

```
Input 
Lorem ipsum dolor sit amet, consectetur adipiscing elit. EOS
Pellentesque sed dolor non arcu imperdiet placerat. EOS
dolor sit amet, consectetur adipiscing elit. Pellentesque sed dolor non EOS
EOS

Output
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque sed dolor non arcu imperdiet placerat.
```
#### Feel free to contribute.
