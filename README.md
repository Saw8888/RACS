#RACS
RACS (Random Access Control System) is a simple scripting language made to facilitate memory manipulation. Even though it is still in heavy development (only the lexer works), I plan to add cool functions like an option to return the memory to its previous values after runtime to prevent errors as well as functions, loops, linked lists and several other datatypes. I dont plan to add float functionality anytime soon though. Here is some example code:
```c++
@static //Keeps the memory unchanged after the program's runtime
addr m = 0x981923Ad819
addrArr x = NULL //Array of addresses
arr y = null //Array of ints
mem r = Null //A linked list with two variables per node, the address and the data
str z = null

main("MySuika"){ //Declares the program who's RAM memory we'll read
 m -> 20 //Writes the value 20 to the adress in m
 20 -> x //Finds all the addresses with value 20 in the MySuika.exe memory and stores them in the array x
 y -> read(x) //Reads all the data corresponding to each address in x and stores it in y
 for i in x{
  if(read(x<i>) != y<i>){
   print("DATA CHANGE AT",x<i>)
  }	
 }
}
```
