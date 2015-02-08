#!/bin/sh

loopCount=20
var=1

#for var in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
#do 
#	echo $var
#	./program files/dsjc1000.9.col 1
#done


for var in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do 
	echo $var
	echo '\t 1000 \n '
	./program files/dsjc1000.9.col 2
	./program files/dsjc1000.5.col 2
	./program files/dsjc1000.5.col 2
	echo '\t 500 \n '
	./program files/dsjc500.9.col 2
	./program files/dsjc500.5.col 2
	./program files/dsjc500.1.col 2
	./program files/dsjr500.1c.col 2
	./program files/dsjr500.5.col 2
	echo '\t 250 \n '
	./program files/dsjc250.5.col 2

done


exit 0;