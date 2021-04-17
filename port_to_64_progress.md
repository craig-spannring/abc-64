Currently I'm working on getting the ex/generate.ex test to pass. 

In gud-gdb we can run it from the build64 directory with the gdb command 
    run -w ./generate.ex < generate.ex.in
    
Once I get that figured out it is nearly certain there will be other
problems.

A simpler way of demonstrating the problem is to create a file, lets
call it bug1.abc, with the following content

'''
SET RANDOM 'foo'
'''

Enter GDB

'''shell
$ gdb abc

(gdb) run < bug1.abc
'''

