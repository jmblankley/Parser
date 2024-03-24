# Parser

**Author:** Joshua Blankley

**Date:** February 2024

## Project Description

This project utilizes the Token class to contrusct a simple parser that takes in input and 'beautifies' the code then outputs the beuatified code to the terminal.

## Technologies Used

Linux, Github, C++

## Installation and Usage

In the terminal:
1. Compile the program using `make`.
2. Execute the program using `./beautifier <filename>`.

## Example

ugly.myl:
```
#This really is ugly code.
int a,b,c;void v1,v2;float really;begin while(a+2>b*c-d)begin
calculation=a+b*c;NoParamFuncCall;if(c==b)then begin c=c-b
end else begin doNothing end;a=b+c;print(help) end;print
(awesomeness) end
```

Terminal:
```console
./beautifier ugly.myl
# successful code =========================
int a, b, c;
void v1, v2;
float really;

begin
  while ( a + 2 > b * c - d )
    begin
      calculation = a + b * c;
      NoParamFuncCall;
      if ( c == b ) then
        begin
          c = c - b
        end
      else
        begin
          doNothing
        end;
      a = b + c;
      print( help )
    end;
  print( awesomeness )
end
```

## Dev Log
- Built up declaration, type, and idlist first and tested them independently since they only interact with eachother.
- Built factor, term, expr, simpexpr, and exprlist since they can interact only with eachother.
- Built compound, statement, and statement list.
- Built program function.
- Got all functions reading in the file and outputting into the console by only calling the program function.
- Got the program to create newlines where needed.
- Implemented a function called getIndent() to set the indention of the lines depending on what came before them.
