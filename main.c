#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <myconio.h>
typedef enum couleur_e couleur_e;
enum couleur_e
{
   COEUR, CARREAU,PIQUE,TREFLE
};
typedef enum valeur_e valeur_e;

/*typedef enum couleur2_e couleur2_e;
enum couleur2_e
{
   COEUR2=3, CARREAU2,PIQUE2,TREFLE2
};*/

typedef enum valeur_e valeur_e;
enum valeur_e
{
    SEPT, HUIT, NEUF, DIX, VALET, DAME, ROI, AS
};

typedef struct carte carte;
struct carte
{
  couleur_e couleur; valeur_e valeur;int len;
};
carte* jeux_de_cartes(void)
{
    carte* tabcartes;
    tabcartes=malloc(sizeof(carte)*32);
    int x =0, i , j ;
    for(i=SEPT ;i<=AS; i++)
    {
        for(j=COEUR ; j<=TREFLE; j++)
        {
            tabcartes[x].couleur = j;
            tabcartes[x].valeur = i;
            x++;
        }


    }
    return tabcartes;

}
void affiche_jeu(int cartes, carte* tab)
{
    int i = 0;
    char* s_couleur[4] = {"COEUR","CARREAUX","PIQUE", "TREFLE"};
    char* s_valeur[8]= {"7", "8", "9", "10", "VALET", "DAME", "ROI", "AS"};
    printf("JEUX DE %d CARTE\n",cartes);
    for(i=0 ; i<cartes ; i++)
    {

        printf("-------------------\n");
        printf("|                  |\n");
        printf("    %s %s",s_valeur[tab[i].valeur], s_couleur[tab[i].couleur]);
        printf("\n");
        printf("|                  |\n");
        printf("-------------------\n");


    }
    printf("\n");

}
void melange_jeux(carte tab[])
{
    int i , index_aleatoir;

    for(i = 0 ;i < 32 ; i++)
    {
        index_aleatoir = rand() % 32;
        carte tampo[1];
        tampo[0] = tab[i];
        tab[i]= tab[index_aleatoir];
        tab[index_aleatoir]= tampo[0];

    }
}

carte** donne (int nbjoueur, int nbcartes, carte *jeu)
{
    int i ;
    carte** jeu2 ;//tableau qui contient des pointeur de struct
    jeu2 = (carte**)malloc(sizeof(carte*)*nbjoueur);
    jeu2[0]=jeu;/*ici on n'a pas besoin de malloc car on initialise le pointeur par un addresse*/
    for(i=1; i< nbjoueur;i++)
    {
         jeu2[i]= &jeu[i*nbcartes] ;/*carte reprente le nombre de carte par joueur*/
    }


    return jeu2;
}


int main(int argc, char* argv[])
{
int a;
  /* printf("LA VALEUR DE COEUR %d, CARREAU %d , PIQUE %d , TREFLE %d \n", COEUR, CARREAU, PIQUE, TREFLE);
   printf("LA VALEUR DE COEUR %d, CARREAU %d , PIQUE %d , TREFLE %d \nOn constate que la valeur des enume commence aprtir de 3 et augment de 1\n\n", COEUR2, CARREAU2, PIQUE2, TREFLE2);*/
   carte* blod = jeux_de_cartes();
   do{
   printf("APPUYER SUR 1 POUR VOIR LES 32 CARTE INITIALE: ");
   scanf("%d",&a);}while(a<=0 || a>1);
   affiche_jeu(32,blod);
   do{
   printf("APPUYER SUR 1 POUR MELANGER LES CARTES : ");
   scanf("%d",&a);}while(a!=1);
   system("cls");
   melange_jeux(blod);
   puts("VOICI LES 32 JEUX DE CARTE MELANGER");
   affiche_jeu(32,blod);
   do{
   printf("APPUYER SUR 1 POUR DONNER LES MAINS : ");
   scanf("%d",&a);}while(a!=1);
   int n ,c=0;
   do{
   printf("CHOISIR UN NOMBRE DE JOUEUR COMPRIT ENTRE 2 et 5 ");
   scanf("%d", &n);
   }while(n <2 || n>5);
   c = 32 / n ;
   carte** distribution= donne(n,c,blod);// on obtient un tableau de 5 joueur et 6 carte pour chacun
printf("DISTRIBUTION EFFECTUER \nAVEC %d JOUEUR ET POUR CHACUN %d CARTE\n",n,c);

   for(int i = 0 ;i < n; i++)
   {

    do{
    printf("APPUYER SUR 1 POUR VOIR LA MAIN NO %d : ",i+1);
    scanf("%d",&a);
    system("cls");}while(a!=1);


    printf("\nMAIN NO %d ",i+1);

        affiche_jeu(c,distribution[i]);//main du joueur 0

   }
free(blod);
free(distribution);

   return 0;
}
