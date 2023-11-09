#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            return buffer;
}


int main(int argc, char** argv){

      char *Dossier = (char*)malloc(TAILLE_MAX);
      Dossier = argv[1];
      char *file = "namesOfFiles";
      PdfToText(Dossier);
      char * path = Dossier;
      char * path2 = (char *)malloc(strlen(Dossier) + 11 );
      char * path4 = (char *)malloc(strlen(Dossier) + 15 );
      sprintf(path2, "%s/resultat/", Dossier);
      sprintf(path4, "%s/resultat_xml/", Dossier);
      char * ch;
      ch = (char *) malloc(TAILLE_MAX);
      snprintf(ch, TAILLE_MAX, "ls %s > %s", path2, file);
      system(ch);
      
      char * ligne;
      ligne  = (char*) malloc(TAILLE_MAX);
      FILE * fichier = fopen(file, "r");
       char * title;
       char * ab;
       char * path3;
     while (fscanf(fichier, " %[^\n] ", ligne) != EOF) {
	    char * l = ligne;
	    char *p = path2;
	    char *chemin = (char *)malloc(strlen(p) + strlen(ligne) + 1);
	    char *chemin2 = (char *)malloc(strlen(p) + strlen(ligne) + 12);
		if (chemin != NULL) {
		    sprintf(chemin, "%s%s", p, ligne);
		    sprintf(chemin2, "%s%s_resume.txt", p, ligne);
		    snprintf(ch, TAILLE_MAX, "touch %s", chemin2);
                    system(ch);
		    title = trouver_titre(chemin);
		    FILE *fichier1 = fopen(chemin2, "w");
		    char *filePdf = strtok(l, ".");
	  	    fprintf(fichier1, "%s.pdf    converti a     %s.txt\n",filePdf, ligne );
		    fprintf(fichier1, "%s\n", title);
		    ab = trouver_abstract(chemin);
		    fprintf(fichier1, "%s\n", ab);
		    free(chemin); 
	            fclose(fichier1);
		}
	   // printf("%s.pdf    converti a     %s.txt \n",filePdf, ligne);
	  //  printf("le titre est : %s \n", title);
	  //  printf("le resume est : %s \n", ab);
     }
      fclose(fichier);
      FILE * fichier2 = fopen(file, "r");
      while (fscanf(fichier, " %[^\n] ", ligne) != EOF){
      
      
      
      }
      fclose(fichier1);
      free(ligne);
      free(ch);
}
      
























