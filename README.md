# Cálculo da série de Leibniz em C++

Este repositório contém dois códigos C++ que calculam uma quantidade de termos (passada por input) da série de Leibniz, para aproximação de pi.

Existem dois scripts: o primeiro ('sequencial.cpp', no diretório 'ex1') faz o cálculo de forma simples, em um processo único; o segundo ('threads.cpp', no diretório 'ex2') divide o cálculo dos termos em diferentes threads, para execução paralela.

No script 'threads.cpp' a quantidade de termos calculados e a quantidade de threads utilizadas devem ser passadas como argumentos na execução do código compilado.
O formato de execução fica (em Linux): ./threads <numero_de_termos> <numero_de_threads>
