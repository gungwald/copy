* Program: Copy file
* Author:  Bill Chatfield

use symbols
use macros

* Get source file name

getSource
                puts    sourcePrompt
    
* Get destination directory

                >>> puts;destPrompt

* Variables

sourcePrompt    asc "File to copy:",00
destPrompt      asc "Directory to copy it to:",00

