# Programming assignment 

For this study, you will complete the programming assignment described here.

This will involve completing the list.c file, which is an implementation of a _linked list_.
This linked list represents a shopping list, where each item in the list has an `item_name`, `price`, and `quantity`.

## Overview

You will be completing the functions in `list.c` only.

You may use any online or class resources available to you (e.g. Google, Stackoverflow, etc.). 
You must use the Visual Studio Code Insiders Build with the extensions provided. 
You must not use any other extensions or plugins, including GitHub Copilot or other programming autocomplete tools.

Note that it is not a hard requirement to complete all functionality, but _all of your code is useful_ - do complete as much as you can, and _even if it does not fully work_ please submit non-functional or incomplete code. Further, you do not need to complete this assignment in 'one go', although you can if you would like to. 

## Instructions

Complete the functions in `list.c` to the best of your ability. You do not need to alter any other files.

Here is a recommended guide:
1. Start by implementing the `list_add_item_at_pos()` function. Then, so that you may test it, implement `list_item_to_string()` and `list_print()` functions.
2. Once those three functions are working reliably, we recommend you write the remaining functions in the following order:
 a. `list_update_item_at_pos()`
 b. `list_remove_item_at_pos()`
 c. `list_swap_item_positions()`
 d. `list_find_highest_price_item_position()`
 e. `list_cost_sum()`
3. The next functions are a little more complex, and we recommend that you complete the above functions before proceeding. Once you are satisfied, we recommend tackling the functions in this order:
 a. `list_save()`
 b. `list_load()`
 c. `list_deduplicate()`

For saving and loading file format, the comments in `list.c` provide detailed instructions and we provide an example `example_load_file.txt`.

For printing, the comments provide the detailed format, and we also present this example:
```
Choice: p
1: 2 * apple @ $0.80 ea
2: 3 * banana @ $0.50 ea
3: 1 * cheese @ $10.49 ea
OK.
```

## How to install the extension
- Download [Visual Studio Code Insiders](https://code.visualstudio.com/insiders/) edition for your OS. 
- clone the current repo: `git clone https://github.com/GusSand/2022_study`
- Type: `cd bin` 

### If you were told to use the language model
- Type: './setup.sh'

### If you were told to NOT use the language model
- Type: './setupnull.sh'

## How to compile and test your code

Depending on your current OS your how to compile might be different, but the idea is that you will need to open a terminal window from VSCode. 
On the `Terminal` menu item, type `New Terminal`
This will get you to your program's currenct directory
Type: `make`

### Windows

- If you don't have LSW, you will need to install [Cygwin](http://www.cygwin.com/install.html) using all the defaults and then follow the instructions above. - Another option is using [MinGW](https://www.mingw-w64.org/) 

