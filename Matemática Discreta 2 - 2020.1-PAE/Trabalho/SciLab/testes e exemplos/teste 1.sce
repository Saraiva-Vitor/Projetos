clear
clc
matrizAdj = [0 1 2 3 4; 2 5 6 7 8]
function [] = teste(matrizAdj)
    disp(matrizAdj)
    matrizAdj(1,2) = 9;
    disp(matrizAdj)
endfunction
teste(matrizAdj)
