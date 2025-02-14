#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "selec.h"
#define TAILLE_MAX 10000000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define TAILLE_MAX 100000000


char * trouver_titre(char *fichier){

	 char * ch;
	 ch = (char *) malloc(TAILLE_MAX * sizeof(char));
	 
	 char * ligne;
	 ligne  = (char*) malloc(TAILLE_MAX * sizeof(char));
	 FILE * file = fopen(fichier, "r");
	 int i  =0;
	 char * resultat;
	 resultat = (char*) malloc(TAILLE_MAX);
	 while(fgets(ligne, TAILLE_MAX, file) != NULL){
	     i++; 
	         if(strstr(ligne, ",") || i==3 ){
                if(i==1){
                    if(strstr(ligne, "FROM") || strstr(ligne, "from") || strstr(ligne, "From")){
                        fgets(ligne, TAILLE_MAX, file);
                    }
                    strcat(resultat, ligne);
                    break;
                }
                break;
            }
             else {
              char * newLigne;
              newLigne = (char*)malloc(TAILLE_MAX * sizeof(char));
	      int taille = strlen(ligne);
              strncpy(newLigne, ligne, taille-1);
              //newLigne = ligne;
              strcat(resultat, newLigne);
              strcat(resultat, " ");
              free(newLigne);
	  	}
	}
	fclose(file);
	free(ch);
	free(ligne);
	
	return resultat;
}



char * trouver_abstract(char * fichier){

	char * buffer;
     	buffer = (char*)malloc(TAILLE_MAX * sizeof(char));
       	FILE * file = fopen(fichier, "r");
       	char * ligne;
       	ligne = (char *) malloc(TAILLE_MAX * sizeof(char));
        int condition = 1;
       	while(fgets(ligne, TAILLE_MAX, file) != NULL){
        	char * newLigne;
       		newLigne = (char*)malloc(TAILLE_MAX * sizeof(char));
        	if((strstr(ligne, "Introduction") || strstr(ligne, "INTRODUCTION") || strstr(ligne, "introduction")||strstr(ligne, "I NTRODUCTION"))){
                   	break;
           	}
           
           	if(strstr(ligne, "Abstract") || strstr(ligne, "ABSTRACT") || condition ==0 ){
                 	condition = 0;
                	int taille = strlen(ligne);
                	strncpy(newLigne, ligne, taille-1);
                	strcat(buffer, newLigne);
                	strcat(buffer, " ");
                	free(newLigne);
           	}
         
       }
       fclose(file);
       free(ligne);
       buffer = buffer + 15;
       return buffer;
}

char *trouver_bibliographie(char *fichier) {
    FILE *file = fopen(fichier, "r");

    char *ligne;
    ligne = (char *)malloc(TAILLE_MAX * sizeof(char));

    char *resultat;
    resultat = (char *)malloc(TAILLE_MAX);
char *newLigne;
        newLigne = (char *)malloc(TAILLE_MAX * sizeof(char));
    int condition = 1;
    while (fgets(ligne, TAILLE_MAX, file) != NULL) {
       
        if (strstr(ligne, "References\n") || strstr(ligne, "REFERENCES\n") || condition == 0) {
			condition= 0;
            int taille = strlen(ligne);
            strncpy(newLigne, ligne, taille - 1);
        }
    }
     strcat(resultat, newLigne);
    strcat(resultat, " ");
    free(newLigne);
    fclose(file);
    free(ligne);

    return resultat;
}
char *trouver_auteur(char *fichier) {
    FILE *file = fopen(fichier, "r");

    char *ligne;
    ligne = (char *)malloc(TAILLE_MAX * sizeof(char));

    char *resultat;
    resultat = (char *)malloc(TAILLE_MAX);

    int i = 0;
    while (fgets(ligne, TAILLE_MAX, file) != NULL) {
        i++;
        if (i == 3) {
            char *newLigne;
            newLigne = (char *)malloc(TAILLE_MAX * sizeof(char));
            int taille = strlen(ligne);
            strncpy(newLigne, ligne, taille - 1);
            strcat(resultat, newLigne);
            strcat(resultat, " ");
            free(newLigne);
            break;
        }
    }
    fclose(file);
    free(ligne);

    resultat = resultat +6;
    return resultat;
}

char * trouver_introduction(char * fichier){

	char * buffer;
     	buffer = (char*)malloc(TAILLE_MAX * sizeof(char));
       	FILE * file = fopen(fichier, "r");
       	char * ligne;
       	ligne = (char *) malloc(TAILLE_MAX * sizeof(char));
        int condition = 1;
       	while(fgets(ligne, TAILLE_MAX, file) != NULL){
        	char * newLigne;
       		newLigne = (char*)malloc(TAILLE_MAX * sizeof(char));
        	if((strstr(ligne, "2. ") || strstr(ligne, "II. ") )){
                   	break;
           	}
           
           	if(strstr(ligne, "1. introduction") || strstr(ligne, "1. Introduction") || strstr(ligne, "I. I NTRODUCTION") || strstr(ligne, "1. INTRODUCTION") || strstr(ligne, "I. introduction") || strstr(ligne, "I. Introduction") || strstr(ligne, "1. I NTRODUCTION") || strstr(ligne, "I. INTRODUCTION") || strstr(ligne, "introduction") || strstr(ligne, "Introduction") || strstr(ligne, "I NTRODUCTION") || strstr(ligne, "INTRODUCTION") || condition ==0 ){
                 	condition = 0;
                	int taille = strlen(ligne);
                	strncpy(newLigne, ligne, taille-1);
                	strcat(buffer, newLigne);
                	strcat(buffer, " ");
                	free(newLigne);
           	}
         
       }
       fclose(file);
       free(ligne);
       buffer = buffer + 16;
       return buffer;
}

char * trouver_discussion(char * fichier){

	char * buffer;
     	buffer = (char*)malloc(TAILLE_MAX * sizeof(char));
       	FILE * file = fopen(fichier, "r");
       	char * ligne;
       	ligne = (char *) malloc(TAILLE_MAX * sizeof(char));
        int condition = 1;
       	while(fgets(ligne, TAILLE_MAX, file) != NULL){
        	char * newLigne;
       		newLigne = (char*)malloc(TAILLE_MAX * sizeof(char));
        	if((strstr(ligne, "Conclusion") || strstr(ligne, "Conclusions") || strstr(ligne, "CONCLUSIONS") || strstr(ligne, "CONCLUSION") || strstr(ligne, "C ONCLUSIONS") || strstr(ligne, "C ONCLUSION"))){   	break;
           	}
           
           	if(strstr(ligne, "DISCUSSION") || strstr(ligne, "D ISCUSSION") || strstr(ligne, "Discussion") || condition ==0 ){
                 	condition = 0;
                	int taille = strlen(ligne);
                	strncpy(newLigne, ligne, taille-1);
                	strcat(buffer, newLigne);
                	strcat(buffer, " ");
                	free(newLigne);
           	}
         
       }
       fclose(file);
       free(ligne);
       buffer = buffer + 15;
       return buffer;
}

char * trouver_conclusion(char * fichier){

	char * buffer;
     	buffer = (char*)malloc(TAILLE_MAX * sizeof(char));
       	FILE * file = fopen(fichier, "r");
       	char * ligne;
       	ligne = (char *) malloc(TAILLE_MAX * sizeof(char));
        int condition = 1;
       	while(fgets(ligne, TAILLE_MAX, file) != NULL){
        	char * newLigne;
       		newLigne = (char*)malloc(TAILLE_MAX * sizeof(char));
        	if( strstr(ligne, "Acknowledgements") || strstr(ligne, "ACKNOWLEDGEMENTS") || strstr( ligne,"References")||strstr( ligne,"REFERENCES") ||strstr( ligne,"references") ||       
                       strstr( ligne,"R EFERENCES")){   	break;
           	}
           
           	if((strstr(ligne, "conclusions") || strstr(ligne, "Conclusions") || strstr(ligne, "conclusion") || strstr(ligne, "Conclusion") || strstr(ligne, "CONCLUSIONS")||strstr(ligne, "CONCLUSION") || strstr(ligne, "C ONCLUSIONS")|| condition == 0)){
                 	condition = 0;
                	int taille = strlen(ligne);
                	strncpy(newLigne, ligne, taille-1);
                	strcat(buffer, newLigne);
                	strcat(buffer, " ");
                	free(newLigne);
           	}
         
       }
       fclose(file);
       free(ligne);
       buffer = buffer + 15;
       return buffer;
}


int main(int argc, char** argv){
	  char *Dossier = (char*)malloc(TAILLE_MAX);
      Dossier = argv[1];
      char * path2 = (char *)malloc(strlen(Dossier) + 11 );
      sprintf(path2, "%sresultat/", Dossier);
      char * ch;
      ch = (char *) malloc(TAILLE_MAX);
	  char* file=(char*)malloc(TAILLE_MAX*sizeof(char));
	  file=selecteur(argv);
      FILE * fichier = fopen(file, "r");
      char * ligne = (char*) malloc(TAILLE_MAX);
      if(strcmp(argv[2], "-t") == 0){    //  choisir le type de sortie :txt
       	char * title;
       	char * ab; 
     	while (fscanf(fichier, " %[^\n] ", ligne) != EOF) {
		char * l = ligne;
	    	char *p = path2;
	    	char *chemin = (char *)malloc(strlen(p) + strlen(ligne) );
		if (chemin != NULL) {
		    sprintf(chemin, "%s%s", p, ligne);
		    snprintf(ch, TAILLE_MAX, "touch %s", chemin); //créer les fichier.txt 
                    system(ch);
		    title = trouver_titre(chemin);
		    char* auteur = trouver_auteur(chemin);
		    char* ab = trouver_abstract(chemin);
		    char* biblio = trouver_bibliographie(chemin);
		    FILE *fichier1 = fopen(chemin, "w"); // ouvrir les fichier pour l'écriture des info
		    char *filePdf = strtok(l, ".");
	  	    fprintf(fichier1, "%s.pdf    converti a     %s.txt\n",filePdf, ligne );
		    fprintf(fichier1, "%s\n", title);
		    fprintf(fichier1, "%s\n", auteur);
		    fprintf(fichier1, "%s\n", ab);
		    fprintf(fichier1, "%s\n", biblio);
		    free(chemin); 
	            fclose(fichier1);
		
    	}
      }
      }else if(strcmp(argv[2], "-x") == 0){   //  choisir le type de sortie : xml
       	char * title;
       	char * ab;
     	while (fscanf(fichier, " %[^\n] ", ligne) != EOF) {
	    	char *l = ligne;
	    	char *p = path2;
	    	char *chemin = (char *)malloc(strlen(p) + strlen(ligne) );
	    	char *chemin2 = (char *)malloc(strlen(p) + strlen(l) + 4);
		if (chemin != NULL || chemin2 != NULL) {
		    char *filePdf = strtok(l, ".");
		    sprintf(chemin, "%s%s.txt", p, ligne);
		    sprintf(chemin2, "%s%s.xml", p, l);
		    snprintf(ch, TAILLE_MAX, "touch %s", chemin2);
                    system(ch);
		    char* title = trouver_titre(chemin);
		    char* auteur = trouver_auteur(chemin);
		    char* ab = trouver_abstract(chemin);
		    char* biblio = trouver_bibliographie(chemin);
		    char* intro = trouver_introduction(chemin);
		    char* conclusion = trouver_conclusion(chemin);
		    char* discussion = trouver_discussion(chemin);
		    FILE *fichier1 = fopen(chemin2, "w");
	  	    fprintf(fichier1, "<article>\n");
		    fprintf(fichier1, "<preamble> %s.pdf </preamble>\n", filePdf);
		    fprintf(fichier1, "<titre> %s </titre>\n", title);
		    fprintf(fichier1, "<auteur> %s </auteur>\n", auteur);
		    fprintf(fichier1, "<abstract> %s </abstract>\n", ab);
		    fprintf(fichier1, "<biblio> %s </biblio>\n", biblio);
		    fprintf(fichier1, "<introduction> %s </introduction>\n", intro);
		    fprintf(fichier1, "<conclusion> %s </conclusion>\n", conclusion);
		    fprintf(fichier1, "<discussion> %s </discussion>\n", discussion);
		    fprintf(fichier1, "</article>\n");
		    char *ch1 = (char*)malloc(TAILLE_MAX) ;
		    sprintf(ch1, "rm %s", chemin);
		    system(ch1);
		    free(chemin); 
	            fclose(fichier1); 
			}
		} 
      } else{
      		printf("pas d'argument");
        }
      fclose(fichier);
      //free(ligne);
      //free(ch);
      //system("rm namesOfFiles"); perror("nv");
       perror(",;,");
}
      
























