#!/bin/sh
arq="dados.csv"
rm $arq
g++  -fopenmp calculoPiParalelo.cpp -o arq.exe

# cabeçalho
echo -n 'N NumThreads' >> $arq
for i in 1 2 3 4 5 6 7 8 9 10
  do
    echo -n ' tempo'$i >> $arq
  done
echo '' >> $arq

# Conteúdo
for n in 1000 10000 100000 1000000
  do
    for nthreads in 1 2 4 8
      do
        echo -n $n $nthreads >> $arq
        for i in 1 2 3 4 5 6 7 8 9 10
          do
            ./arq.exe $n $nthreads >> $arq
          done
        echo '' >> $arq
      done
  done
	

