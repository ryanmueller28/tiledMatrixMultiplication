#!bash runit.sh
#By Ryan Mueller and Peyton Harsin

for i in {1..400}
do
	./TiledMatrixMM 400 $i 200 >> out.csv
done
 
