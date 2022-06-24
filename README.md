The project is not complete, while there are several functionalities I wanna add - to complete the file handeling for structured data. Base functions like SplitAll are still useful for academic management software using Files for data instead of SQL. In a more advance form, the structured data should be like Pandas dataframe or xlsx files. Vector can also be used for this, but I wanted to develop it using dynamic memory objects for more flexibility in operations. 

# C++ File Manipulation
The program files attached handle files as a database, to perform operations like reading with multiple 'where' condition, joining, filtering (like excel), reading and deleting.

Dynamically allocated double pointer change the delimeted file content into a matrix and we can access the content with applied conditions on that. This matrix structure is then used to develop features like join, filter and search. Every pointer of that array points to another pointer, with dynamic allocation size. I have written it with basic dynamic allocation structure through pointers but can be updated to a proper structure like linked list. This is the start and maybe helpful to students to some degree; but I'm planning to add more into this. 

![image](https://user-images.githubusercontent.com/38018683/147359925-4414c47b-cd63-48a4-8066-d2fcc4111e6f.png)

# Additions
1. Partial Search
2. Converting string pointers to relevant data types
3. Operators for mathematical operations
4. File operations -> Unique, Aggregate, LookUp
