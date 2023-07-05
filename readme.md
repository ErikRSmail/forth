This is just a (mostly complete) FORTH interpreter. 

For Hello, world!:
```
33 100 108 114 111 119 44 111 108 108 101 72 EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT CR
```
or if you are a strict adherent to clean code, minimalism, DRY etc, try:
```
33 100 108 114 111 119 44 111 108 108 101 72 12 0 DO EMIT LOOP CR
```
Clear as day? FORTH is great. 

This supports basic arithmetic and stack manipulation primitives, macros, and do loops