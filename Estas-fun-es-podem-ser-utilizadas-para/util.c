/*
* Estas funções podem ser utilizadas para corrigir alguns problemas
* no processamento de texto no RunCodes.
* 
* A função limpar_cadeia_caracteres deve ser utilizada depois do fgets, assim:
*
* ...
* fgets(aux,501,stdin);
* limpar_cadeia_caracteres(aux);
* ...
*
e a função remover_espaco deve ser utilizada em cada iteração produzida pela strtok, assim:
*
* ...
* while(token!=NULL){
*        remover_espaco(token);
* ...
*/
void remover_espaco(char *aux) {
	int k;
	if(aux[0] == ' ')
		for(k = 1; aux[k] != '\0'; k++)
			aux[k-1] = aux[k];
		aux[k-1] = '\0';
}

void limpar_cadeia_caracteres(char *aux)
{
	int k, t;
	if(aux[0] == ' ')
		for(k = 1; aux[k] != '\0'; k++)
			aux[k-1] = aux[k];
		aux[k-1] = '\0';

	for(t = 0; aux[t] != '\0'; t++) ;		
	while( (aux[t] == '\0' || aux[t] == '\n' || aux[t] == '\r') && t > 0) t--;
	aux[t+1] = '\0';
}
