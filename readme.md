This is just a (mostly complete) FORTH interpreter. 

For Hello, world!:
```
33 100 108 114 111 119 44 111 108 108 101 72 EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT CR
```
or if you are a strict adherent to clean code, minimalism, DRY etc, try:
```
33 100 108 114 111 119 44 111 108 108 101 72 12 0 DO EMIT LOOP CR
```
Clear as day? FORTH is great. We can keep going for maximum clarity and c l e a n   c o d e though.

```
: H 72 ; : e 101 ; : l 108 ; : o 111 ; : , 44 ; : SPACE 32 ; : w 119 ; : r 114 ; : d 100 ; : ! 33 ;
: print13chars 13 0 DO EMIT LOOP CR ;
: hello_world ! d l r o w SPACE , o l l e H print13chars ;
hello_world
```
How elegant.

This supports basic arithmetic and stack manipulation primitives, macros, and do loops