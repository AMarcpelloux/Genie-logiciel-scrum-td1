#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define TAILLE_MAX 10000000

void PdfToText(char* nom_dossier){
   
	   char * ch;
	   ch = (char *) malloc(TAILLE_MAX * sizeof(char));
	   
	   char * line; 
	   line = (char *) malloc(TAILLE_MAX * sizeof(char));
	   
	   snprintf(ch, TAILLE_MAX, "ls %s > tst.txt", nom_dossier);
           system(ch); // mettre les non des fichier.pdf dans un fichier "tst.txt"
           
	   snprintf(ch, TAILLE_MAX, "rm -fr %s/resultat", nom_dossier);
           system(ch); // supprimer le dossier resultat s'il existe
      
	   snprintf(ch, TAILLE_MAX, "mkdir %s/resultat", nom_dossier);
           system(ch);  // créer un nouveau dossier resultat qui contient les fichiers.txt de resultat finale
  
        // on ouvre le fichier "tst.txt"
        FILE* fichier = fopen("tst.txt", "r");
        /*
              parcourir le fichier "tst.txt" et à chaque fois on prend le non d'un
              fichier pdf et on le converti à un fichier.txt on gardant leur nom
        */
        while (fgets(line, TAILLE_MAX, fichier) != NULL) 
        {
            snprintf(ch, TAILLE_MAX, "pdftotext %s/%s", nom_dossier, line);
            system(ch);
        }
 
        fclose(fichier);
      snprintf(ch, TAILLE_MAX,"mv %s/*.txt %s/resultat/", nom_dossier,nom_dossier);
        system(ch); // deplacer les fichier.txt dans le dossier resultat
        system("rm tst.txt"); // supprimer le fichier "tst.txt"
       free(ch);
       free(line);
}

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

    int condition = 1;
    while (fgets(ligne, TAILLE_MAX, file) != NULL) {
        char *newLigne;
        newLigne = (char *)malloc(TAILLE_MAX * sizeof(char));

        if ((strstr(ligne, "Introduction") || strstr(ligne, "INTRODUCTION") ||
             strstr(ligne, "introduction") || strstr(ligne, "I NTRODUCTION"))) {
            break;
        }

        if (strstr(ligne, "Bibliography") || strstr(ligne, "BIBLIOGRAPHY") || condition == 0) {
            condition = 0;
            int taille = strlen(ligne);
            strncpy(newLigne, ligne, taille - 1);
            strcat(resultat, newLigne);
            strcat(resultat, " ");
            free(newLigne);
        }
    }
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

    return resultat;
}


int main(int argc, char** argv){

      char *Dossier = (char*)malloc(TAILLE_MAX);
      Dossier = argv[1];
      char *file = "namesOfFiles";
      PdfToText(Dossier);
      char * path = Dossier;
      char * path2 = (char *)malloc(strlen(Dossier) + 11 );
      sprintf(path2, "%s/resultat/", Dossier);
      char * ch;
      ch = (char *) malloc(TAILLE_MAX);
      snprintf(ch, TAILLE_MAX, "ls %s > %s", path2, file); // enregistrer les nom de fichier.txt dans un fichier namesOfFiles
      system(ch);
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
      }
      else if(strcmp(argv[2], "-x") == 0){   //  choisir le type de sortie : xml
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
		    FILE *fichier1 = fopen(chemin2, "w");
	  	    fprintf(fichier1, "<article>\n");
		    fprintf(fichier1, "<preamble> %s.pdf </preamble>\n", filePdf);
		    fprintf(fichier1, "<titre> %s </titre>\n", title);
		    fprintf(fichier1, "<auteur> %s </auteur>\n", auteur);
		    fprintf(fichier1, "<abstract> %s </abstract>\n", ab);
		    fprintf(fichier1, "<biblio> %s </biblio>\n", biblio);
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
      free(ligne);
      free(ch);
      system("rm namesOfFiles");
}
      
























