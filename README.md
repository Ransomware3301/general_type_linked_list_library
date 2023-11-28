# general_type_linked_list_library
General-Type Linked List Library written in C 

<br>

## How To Use:

In order to integrate this library in your code, you must perform the following steps:

1.  Copy the library into the folder where your project will live.

2.  At the top of your <code>main.c</code> file, **BEFORE** the <code>#include "full_general_type_list_lib.c"</code> preprocessor directive, you must specify these two <code>#define</code> directives: 

<center><code>#define TYPE [your chosen type goes here]</code></center>
<center><code>#define FORMAT [the printf and scanf format]</code></center>

<br>

3.  After you wrote these two directives, you can now put <code>#include "full_general_type_list_lib.c"</code> and take full advantage of all the functions inside of it.

<br>

### For Example:
- Suppose we want to operate with an _integer_ list. First, we write the two <code>#define</code> directives, which in this case look like this: 

<center><code>#define TYPE int</code></center>
<center><code>#define FORMAT "%d"</code></center>

<br>

- Now the library will behave like it was written natively for _integer_ lists.
- To further clarify, the <code>#define FORMAT "%d"</code> directive is needed so that the <code>printf</code> and <code>scanf</code> functions behave correctly when either writing or reading a value, since both need a _format specifier_ that tells the compiler that the value will be of that specific type.

<br>

## Supported Data Types:

Currently, the library is unable to work with structured data types but only with primitives, so the supported ones are:

- char
- short int
- int
- long int
- float
- double
- long double

(NOTE: I've written the library in C89 ANSI, thus <code>bool</code> and others aren't included but should still work at the time of writing, as long as those data types aren't defined through a <code>struct</code>)

<br>

## Future Development:

- I'm planning to extend the flexibility of this library, firstly by making it capable of working with structured data types, then I was also planning on adding _dynamic_ types (such as <code>string</code>), so that you could have dynamic lists that hold dynamic size values.
- Any suggestion or contribution will be taken into consideration, regardless of its relevance.
