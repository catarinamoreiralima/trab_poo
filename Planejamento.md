# 1. Comunicação da busca

# todo: refazer essa especificação da comunicação para bater com o modelo de input do trabalho de arquivos
a comunicação do campo será feita na forma de uma string nos moldes de:
"id|idade|nomejogador|nac|nomeclube"
- um delimitador de campo '|'
- um delimitador de registro '$'
- se campo vazio, @ 
TESTE
@|12|marcos|@|palmeiras

# comunicação de programas
programa em java recebe os inputs do campo de busca -> função que transforma os inputs em string -> manda os strings pro servidor python -> função em python que recebe a string e manda pro programa em C fazer a busca no arquivo -> programa em c retorna uma string com os registros  

# definir: como vamos passar o arquivo do programa pro servidor?
- e a definição do arquivo? faz ela no início?

