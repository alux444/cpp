# exceptions

when an exception is thrown:

- the program first looks to se if the exception can be handled immediately inside the current function (try catch block). if it can handle the exception, it does
- if not, the program next checks whether the function's caller (next up on call stack) can handle the exception
- if not, continues up the call stack, until either handler is found or all functions on stack have been checked, and no handler is found
- if a handler is found, execution jumps from the point where exception is thrown to the top of the matching catch block, which requires unwinding the stack until the function handling the exception is at the top of the call stack
- if no handler is found, the stack may or may not be unwound
- when the current function is removed from the call stack, all local variables are destroyed (as usual) but no value is returned
