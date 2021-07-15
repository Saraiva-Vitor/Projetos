#!/bin/bash

echo " Gerando conda env create -f ambiente.yml "
echo "criando ambiente"

conda env create -f ambiente.yml

eval "$(conda shell.bash hook)"

conda activate redesneurais

SPTH='/Users/roberto/Desktop/neuralnet'
 
echo "Trocando diretório ( vc precisa mudar este diretoria para o seu ):"$SPTH

mkdir $SPTH
 
cp redesMLPsimples.ipynb $SPTH/redes.ipynb

cd  $SPTH

echo "Rodando Jupyter Notebook - pode dar errado se for root"

jupyter notebook redes.ipynb
