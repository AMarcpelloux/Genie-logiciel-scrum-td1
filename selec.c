#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>
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
char* selecteur(char** argv){
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
      char * result=strdup(file);
      char * lect="";
      size_t len=0;
      ssize_t rrrr=0;
      FILE* fp;
      fp=fopen(result,"r");
      int i=1;
      int k=0;
      char tab[25][500];
      while((rrrr = getline(&lect, &len, fp)) != -1){
		  printf("%d %s",i,lect);i++;
		  strcpy(tab[k],lect);k++;
	  }
	  i=0;
	  fclose(fp);
	  fopen(result,"w+");
	  std::cout<<"Sélecteur\n-1 pour sortir\n";
	  while(i!=-1){
		  std::cout<<"choissez un article\n";
		  std::cin>>i;
		  if(i<=k&&i>=0)fprintf(fp,tab[i-1]);
	  }
      fclose(fp);
	return  strdup(result);
}
