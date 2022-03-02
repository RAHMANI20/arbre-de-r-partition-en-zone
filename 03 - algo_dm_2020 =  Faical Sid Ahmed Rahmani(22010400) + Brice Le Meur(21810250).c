/*
- Faical Sid Ahmed Rahmani 22010400
- Brice Le Meur 21810250
- num binome : 2447

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int INFINI=30 ;
int compteur = 0;

typedef struct {
	double x;
	double y;
} PointStr;    // sous la forme d'une structure

/*****************  les points ********************************/
typedef  double * Point;  // sous forme d'un  tableau

Point creerPoint(double x, double y){
	double * p =  malloc(2*sizeof(double));
	p[0]=x;
	p[1]=y;
	return  p;
}

/* pour convertir un point sous forme de structure en un point sous forme de tableau */
Point pointStrucToPoint(PointStr ps){
	return creerPoint(ps.x, ps.y);
}

/* pour tester l egalite de deux points  */
int  estEgalPoint(Point p, Point q){
	if((p[0] == q[0]) && (p[1] == q[1])) 	return 1;
	else return 0;
}

void afficherPoint(Point pc){
   printf("(%.0f , %.0f)", pc[0], pc[1]);
}

Point copierPoint(Point p){
	return creerPoint(p[0], p[1]);
}

/* selecteur et initialisation de points */
double get(Point pt, int i){  return pt[i];}
void setCoordonnee(Point pt, int i, double v){  pt[i]=v;}
void setPointParCoordonnee(Point pt, double x, double y){ pt[0]=x; 	pt[1]=y; }
void setPointParPoint(Point pt, Point q){setPointParCoordonnee(pt, q[0], q[1]);}

/*------------------- distance = carre de la distance eucliienne -----------*/
double square(double x){ return x * x;}
double distance(Point a, Point b){
	double xx= (b[0] - a[0]);
	double yy = (b[1] - a[1]);
	return square(xx) + square(yy);
}

	/* ********** les listes de points *************/
typedef struct SNListeP
{
	Point valeur;
	struct SNListeP * suivant;
}  NoeudListePoint;

typedef NoeudListePoint * ListePoint;

ListePoint ajouterDevant(Point p, ListePoint lp){
	ListePoint temp = malloc(sizeof(struct SNListeP));
	temp->valeur = p;
	temp->suivant = lp;
	return temp;
}

ListePoint extend(ListePoint l1, ListePoint l2){
	if(l1==NULL) return l2;
	if(l2==NULL) return l1 ;
	ListePoint temp=l1;
	while(temp != NULL){
		l2=ajouterDevant(temp->valeur,l2);
		temp = temp->suivant;
	}
	return l2;
}

void afficherLPoint(ListePoint lp){
	Point p;
	ListePoint temp = lp;
	while(temp !=NULL){
		p=temp->valeur;
		printf("(%.2f , %.2f), ",p[0], p[1]);
		temp = temp->suivant;
		}
}

 /*---------------- ABRZ arbre de partition en zones  --------------------*/
typedef  struct SNoeud {
	Point valeur;
	int cs;
	struct SNoeud * gauche;
	struct SNoeud * droit;
}  NoeudABRZ;

typedef NoeudABRZ * ABRZ;
/*--------------- ----------- zone  ------------------------------*/
typedef struct{
	Point  infg;
	Point supd;
} Zone;


int estFeuille(ABRZ arb){
	if (arb == NULL) return 0;
	if ((arb->gauche == NULL) && (arb->droit == NULL))
		return 1;
	else return 0;
}
/************** affichage d'un arbre           *************/

int hauteur(ABRZ A){
    // fonction qui calcul la hauteur d'un arbre binaire A
    if (A == NULL){ return -1;}
	int hg = hauteur(A -> gauche);
	int hd = hauteur(A -> droit);
	if (hg < hd){ return 1 + hd;}
	else { return 1 + hg;}
 }

void afficherArbre(ABRZ A){
   // un affichage planaire de l'arbre
     void affichageProfondeur(ABRZ A,int profondeur){
	   Point racine;
	   int i=0;
      if (A == NULL){ i++; }
      else{
		  racine=A->valeur;
		  affichageProfondeur(A -> gauche,profondeur-1);
		  if (profondeur == 0)
			printf("(%.1f,%.1f,%d)", racine[0], racine[1], A->cs);
		  else
		    printf("   ");
		    affichageProfondeur(A -> droit,profondeur-1);
		}
	  }

  if (A != NULL){
	    int h = hauteur(A);
	    for( int p = 0 ; p < h + 1 ; p++){
            affichageProfondeur(A,p);
            printf("\n");
        }
   }
}
/*---------------- vreation ----------------------*/
ABRZ creerArbre(Point v, ABRZ g, ABRZ d, int cs){
	ABRZ a = malloc(sizeof(NoeudABRZ));
	a->valeur= v;
	a->cs = cs;
	a->gauche = g;
	a->droit = d;

	return a;
}

/* ============ Question 1: definir inserer ==============   */
ABRZ insererAux(ABRZ a, Point p, int cs){
	Point ptr;
	if(a == NULL) return creerArbre(p,NULL,NULL,cs);

	else {compteur++;
		ptr = a->valeur;
		if(estEgalPoint(ptr,p) == 1) return a;
		if(cs == 0) {
			if(p[0] <= ptr[0]) a->gauche = insererAux(a->gauche,p,1);
			else a->droit = insererAux(a->droit,p,1);
		}

		else {
			if(p[1] <= ptr[1]) a->gauche = insererAux(a->gauche,p,0);
			else a->droit = insererAux(a->droit,p,0);
		}
		return a;
    }
}


ABRZ inserer(ABRZ a, Point p){
	if (a==NULL) return insererAux(a , p, 0);
	else return insererAux(a, p, a->cs);
}
//======================QUESTION 2:  recherche d un point****************************/

ABRZ rechercher(ABRZ arb, Point pt){
	if (arb == NULL) return NULL;
	compteur++;
	if (estEgalPoint(arb->valeur,pt) == 1) return arb;
	Point ptr = arb->valeur;
	if(arb->cs == 0){
		if(pt[0] <= ptr[0]) return rechercher(arb->gauche,pt);
		else return rechercher(arb->droit,pt);
	}
	else{
		if(pt[1] <= ptr[1]) return rechercher(arb->gauche,pt);
		else return rechercher(arb->droit,pt);
	}


} // testée (ça marche bien)

// ================== QUESTION 3 calcul d'un point dont l'abcisse est minimale----------------------------------

// cette fonction compare entre deux points et retourne le point dont l'abscisse est minimum.

Point minAbc(Point a,Point b){
	if(a == NULL && b == NULL) return NULL;
	if(a == NULL && b != NULL) return b;
	if(b == NULL && a != NULL) return a;
	if(a[0] < b[0]) return a;
	return b; // a[0] >= b[0]
}

// on suppose que arb est non vide
Point minX(ABRZ arb){

    compteur++;

	if(arb->gauche == NULL && arb->droit == NULL ) return arb->valeur; // le cas d'une feuille
	if(arb->cs == 0) { // on cherche à gauche
		if(arb->gauche != NULL) return minX(arb->gauche);
		else return arb->valeur;
	}
	else { // si arb->cs = 1 on cherche à gauche et à droite
		Point min1 = NULL,min2 = NULL;
		if(arb->gauche != NULL) min1 = minX(arb->gauche);
		if(arb->droit != NULL) min2 = minX(arb->droit);
		min1 = minAbc(min1,min2);
		// on compare le minimum des deux sous-arbre avec la racine
		if (min1[0] < arb->valeur[0]) return min1;
		else return arb->valeur;
	}
}// testée (ça fonctionne)




/* ================== QUESTION 4:-- affichage des points dans une droite verticale intersection ------------------------*/
void dansDroiteV(ABRZ arb, double x){

	if(arb != NULL){ // si arb = None on fait rien

        compteur++;

		if(arb->valeur[0] == x){// on affiche
	        afficherPoint(arb->valeur);
        }

        if(arb->cs == 0){ // on part soit à droite soit à gauche
            if(arb->valeur[0] < x) dansDroiteV(arb->droit,x);
            else dansDroiteV(arb->gauche,x);
        }
        else{ // arb->cs = 1 // on part à gauche et à droite
            dansDroiteV(arb->gauche,x);
            dansDroiteV(arb->droit,x);
        }

	}

} // testée (ça fonctionne)



/* ================== QUESTION 5: affichage des points d'une zone ------------------------*/

int estDansZone(Point pt, Point infg, Point supd){
	if(((pt[0] > infg[0]) && (pt[0] <= supd[0])) && ((pt[1] > infg[1]) && (pt[1] <= supd[1])))
		return 1;
	else return 0;
}

// cette fonction permet de déterminer si la droite verticale
// passant par p coupe la zone z=[pig,psd]
// sans traiter le cas ou p.x = psd.x (traité dans intersection)

int coupe_vert_zone(Point p,Point pig,Point psd){
	if(p[0] > pig[0] && p[0] < psd[0]) return 1;
	else return 0;
}

// cette fonction permet de déterminer si la droite horizontale
// passant par p coupe la zone z=[pig,psd]
// sans traiter le cas ou p.y = psd.y (traité dans intersection)

int coupe_horz_zone(Point p,Point pig,Point psd){
	if(p[1] > pig[1] && p[1] < psd[1]) return 1;
	else return 0;
}


void intersection(ABRZ arb, Point infg, Point supd){

	if(arb != NULL){

        compteur++;


		if(estDansZone(arb->valeur,infg,supd) == 1){ // le point est dans la zone

			afficherPoint(arb->valeur);
			intersection(arb->gauche,infg,supd);
			intersection(arb->droit,infg,supd);
		}
		else{
			if(arb->cs == 0){
				if(coupe_vert_zone(arb->valeur,infg,supd) == 1){ // on part à gauche et à droite
				    intersection(arb->gauche,infg,supd);
			        intersection(arb->droit,infg,supd);
				}
				else{
					if(arb->valeur[0] >= supd[0])  intersection(arb->gauche,infg,supd); // le point à droite donc on part à gauche
					else intersection(arb->droit,infg,supd); // à gauche
				}
			}
			else{// arb->cs = 1
			    if(coupe_horz_zone(arb->valeur,infg,supd) == 1){
			    	// on part à gauche et à droite
					intersection(arb->gauche,infg,supd);
			        intersection(arb->droit,infg,supd);
				}
				else{
					if(arb->valeur[1] >= supd[1]) intersection(arb->gauche,infg,supd); // le point en haut donc on part à gauche
					else intersection(arb->droit,infg,supd); // en bas
				}
		    }
	    }
	}
} // testée (ça fonctionne )

/* =================== QUESTION 6 =  plus proche point ***************/



// cette fonction teste si la droite passant par p
// verticale si cs = 0 et horizontale si cs = 1
// coupe ou non le cercle de centre cen et de rayon ray.
// retourne 0 si la droite coupe le cercle
// -1 si elle est en bas ou à gauche du cercle et
// 1 si elle est au dessus ou à droite du cercle.

int position_droite_cercle(Point p, int cs, Point cen, double ray){

	if(cs == 0){
		if(cen[0]-ray <= p[0] && p[0] <= cen[0]+ray) return 0;
		if(cen[0]-ray > p[0]) return -1;
		if(cen[0]+ray < p[0]) return 1;
	}
	if(cs == 1){
		if(cen[1]-ray <= p[1] && p[1] <= cen[1]+ray) return 0;
		if(cen[1]-ray > p[1]) return -1;
		if(cen[1]+ray < p[1]) return 1;
	}



}



Point  plusprocheAux(ABRZ A, Point q, Point ppc, double dminc){

	if(A == NULL) return ppc;
	compteur++;
	if(sqrt(distance(A->valeur,q)) < dminc) { // le point courant est plus proche
		dminc = sqrt(distance(A->valeur,q));
		ppc = A->valeur;
	}

	if(position_droite_cercle(A->valeur,A->cs,q,dminc) == 0){
		// la droite (h ou v) coupe le cercle
		Point a,b; // on cherche le plus proche pour chaque sous arbre
		a = plusprocheAux(A->gauche,q,ppc,dminc);
		b = plusprocheAux(A->droit,q,ppc,dminc);
		// on retourne le plus proche entre le plus proche courant
        // et le plus proche de chaque sous arbre

        if(sqrt(distance(a,q)) <= sqrt(distance(b,q))) {
        	if(sqrt(distance(a,q)) <= dminc) return a;
		}
		if(sqrt(distance(b,q)) <= sqrt(distance(a,q))) {
        	if(sqrt(distance(b,q)) <= dminc) return b;
		}
		return ppc;
	}

	if(position_droite_cercle(A->valeur,A->cs,q,dminc) == -1){
		// la droite (h ou v) est (en bas ou à gauche) du cercle
        // il suffit de chercher dans le sous arbre droit
        return plusprocheAux(A->droit,q,ppc,dminc);
	}
	// la droite (h ou v) est (en haut ou à droite) du cercle
    // il suffit de chercher dans le sous arbre gauche
	return plusprocheAux(A->gauche,q,ppc,dminc);


}




Point plusproche(ABRZ A, Point q)
{
	if(A==NULL) return NULL;
	// initialisation : ppc = point racine , dminc = distance entre le point de la racine et q
	return plusprocheAux(A,q,A->valeur,sqrt(distance(A->valeur,q)));
} // testée (ça fonctionne)

int estDans(Point pt, Point v, Point w){
	if (((pt[0] > v[0]) && (pt[0] <= w[0])) && ((pt[1] > v[1]) && (pt[1] <= w[1])))
		return 1;
	else return 0;
}


void afficherPointsAvecNoms(PointStr *tabp , char * tabm, int n){

	for(int i=0 ; i<n ; i++){
		printf("\"%c=(%.0f, %.0f)\",", tabm[i], tabp[i].x, tabp[i].y);
	}
}

/*  ================ Tests des fonctions ***********************************************/
void testRecherche(ABRZ arb, PointStr * tabPoints, int np)
{
	ABRZ res=NULL;
	Point pt;
	for(int i=0 ; i<np ; i++){
		pt=pointStrucToPoint(tabPoints[i]);
		compteur=0;
		res=rechercher(arb,pt);
		printf("\n    - le point (%.2f , %.2f) est racine de : \n",pt[0], pt[1]);
		afficherArbre(res);
	}
}

void testMinX(ABRZ arb){
	//ListePoint res = minX(arb);
	Point res=minX(arb);
	printf("un poit d'abcisse minimum :");
	afficherPoint(res);
}


void testDansDroiteV(ABRZ arb, double tabX[], int nx)
{
	ABRZ res=NULL;
	double  vx;
	for(int i=0 ; i<nx ; i++){
		printf("\n   - les points de la droite (x=%.2f) sont: \n",tabX[i]);
		dansDroiteV(arb, tabX[i]);
		}
}



void testIntersection(ABRZ arb, PointStr tabPointsZones[], int npz){
	Point pinfg, psupd;
	int i=0;
	while(i < npz){
		pinfg=pointStrucToPoint(tabPointsZones[i++]);
		psupd=pointStrucToPoint(tabPointsZones[i++]);
		printf("\n   -l'intersection  avec la zone (%.2f , %.2f) et (%.2f , %.2f) contient: \n",pinfg[0], pinfg[1], psupd[0], psupd[1]);
	    intersection(arb, pinfg, psupd);

	}
}

void testPlusProche(ABRZ arb, PointStr * tabPoints, int np)
{
	Point res;
	Point pt;
	for(int i=0 ; i<np ; i++){
		pt=pointStrucToPoint(tabPoints[i]);
		res=plusproche(arb,pt);
		printf("\n   -les point les plus proches de (%.2f , %.2f) sont : \n",pt[0], pt[1]);
		afficherPoint(res);
	}
}

ABRZ arbreExemple(){
	ABRZ aex = NULL ; ABRZ g = NULL; ABRZ d = NULL ;
	d = creerArbre(creerPoint(3,5),NULL, NULL,1);
	g = creerArbre(creerPoint(1,5),NULL, NULL,1);
	aex= creerArbre(creerPoint(2,4), g, d,0);
	aex= creerArbre(creerPoint(1,3), NULL, aex,1);

	d=creerArbre(creerPoint(6,3),NULL, NULL,1);
	d=creerArbre(creerPoint(5,4),NULL, d,0);
	d=creerArbre(creerPoint(6,2),NULL, d,1);
	aex=creerArbre(creerPoint(4,3),aex, d,0);

	d=creerArbre(creerPoint(5,9),NULL, NULL,1);
	d=creerArbre(creerPoint(3,10),NULL, d,0);
	aex=creerArbre(creerPoint(1,6), aex,d ,1);

	g=creerArbre(creerPoint(9,8),NULL, NULL,1);
	d=creerArbre(creerPoint(11,9),g, NULL,0);
	d=creerArbre(creerPoint(8,5),NULL,d,1);
	aex=creerArbre(creerPoint(7,1),aex,d,0);
	return aex;
}

/* =====================TESTs dans main ==================================*/
int mainArbreExemple(){
	printf("\n-------- creation arbre exemple -------\n");
	ABRZ   arbEx =arbreExemple();
	printf("\n ------- affichage arbre exemple ----- \n");
	afficherArbre(arbEx);

	printf("\n---------test de la recherche de points-----------\n");
	PointStr tabPoints[]={{2,4}, {9,8}};
	testRecherche(arbEx, tabPoints,2);

	printf("\n------------test de l'abcisse minimale  \n");
	testMinX(arbEx);

	printf("\n -----------test  dans droite verticale ----------------\n");
	double tabX[]={1.0, 6.0 ,2.0,3.0,4.0,6.0,7.0,8.0,9.0,11.0,10.0};
	testDansDroiteV(arbEx, tabX,11);

	printf("\n -----------test intersection avec zone ----------------\n");
	PointStr  tabPointZones[]={{1,2},{6,7},{6,1},{10,9}} ;
	testIntersection(arbEx, tabPointZones, 4);


	printf("\n-----------test du point le plus proche-----------\n");
	PointStr tabPointsPP[]={{3,4}, {5,2}, {8,4}, {11,9},{5.3,2.6}};
	testPlusProche(arbEx, tabPointsPP,5);

	return 0 ;
}

int mainListePoints(){
	/* liste constante de 16 points de type PointStr, exemple de la partie theorique  */
	PointStr lpStr[]={{7,6},{2,10},{11,3},{10,9},{4,4}, {5, 8},
		 {6, 1}, {8, 7}, {1, 5}, {9,2}, {8,4},{9,5},{5,9}, {6, 3}, {7,8}, {2, 3}};

	printf("\n affichage des points avec leur noms \n");
	char* nomsDesPoints="ABCDEFGHIJKLMNOPQRSTUVW";
	afficherPointsAvecNoms(lpStr, nomsDesPoints, 16);

    printf("\n-------- creation de l'arbre Ã  arbre exemple -------\n");
	ABRZ   arbEx = NULL ;
	for(int i=0 ; i < 16; i++)
	     arbEx=inserer(arbEx, pointStrucToPoint(lpStr[i])) ;
	printf("\n ------- affichage arbre exemple ----- \n");
	afficherArbre(arbEx);

	printf("\n---------test de la recherche de points-----------\n");
	PointStr tabPoints[]={{5,4}, {9,8}};
	testRecherche(arbEx, tabPoints,2);

	printf("\n------------test de l'abcisse minimale  \n");
	testMinX(arbEx);

	printf("\n -----------test  dans droite verticale ----------------\n");
	double tabX[]={5.0, 6.0};
	testDansDroiteV(arbEx, tabX,2);

	printf("\n -----------test intersection avec zone ----------------\n");
	PointStr  tabPointZones[]={{1,2},{6,7},{6,1},{10,9}} ;
	testIntersection(arbEx, tabPointZones, 4);

	printf("\n-----------test du point le plus proche-----------\n");
	PointStr tabPointsPP[]={{3,4}, {5,2}, {8,4}, {11,9}};
	testPlusProche(arbEx, tabPointsPP,4);

	return 0 ;
	}

int mainLongueListePoints(){
	/* liste constante de 100 points de type PointStr, exemple de la partie theorique  */
	PointStr lpStr[]={{22, 37},{9, 26},{35, 4},{15, 9},{8, 10},{27, 8},{34, 30},{31, 28},{5, 27},
		{3, 27},{13, 13},{12, 37},{2, 12},{17, 32},{1, 28},{2, 21},{32, 7},{23, 25},{37, 31},
		{24, 21},{2, 12},{23, 35},{35, 36},{25, 17},{10, 39},{24, 7},{36, 14},{27, 19},{12, 1},{38, 20},
		{37, 9},{17, 27},{7, 0},{3, 26},{9, 13},{12, 1},{23, 20},{29, 20},{32, 35},{1, 33},{5, 9},{37, 36},{5, 31},
		{10, 0},{27, 26},{20, 37},{27, 9},{32, 11},{8, 14},{3, 20},{1, 32},{31, 1},{25, 8},{6, 22},{1, 39},{7, 21},
		{6, 23},{22, 39},{20, 7},{11, 15},{8, 10},{25, 24},{2, 6},{31, 25},{22, 1},{21, 2},{4, 21},{19, 22},{31, 5},
		{8, 38},{9, 13},{24, 6},{32, 4},{37, 26},{27, 3},{31, 22},{25, 18},{6, 19},{14, 30},{19, 30},{18, 21},{2, 39},
		{27, 39},{22, 27},{39, 11},{2, 3},{24, 38},{32, 28},{4, 5},{1, 6},{2, 26},{14, 11},{12, 36},{23, 9},{17, 35},
		{22, 30},{38, 5},{36, 6},{17, 15},{29, 33}};

       ABRZ arbEx = NULL;
       for(int i=0 ; i < 100 ; i++){
		   arbEx=inserer(arbEx,pointStrucToPoint(lpStr[i])) ;
	   }
	   afficherArbre(arbEx);


	printf("\n---------test de la recherche de points-----------\n");
	PointStr tabPoints[]={{24,7}, {6,19}, {0,5}};
	testRecherche(arbEx, tabPoints,2);

	printf("\n------------test de l'abcisse minimale  \n");
	testMinX(arbEx);

	printf("\n -----------test  dans droite verticale ----------------\n");
	double tabX[]={5.0, 6.0};
	testDansDroiteV(arbEx, tabX,2);

	printf("\n -----------test intersection avec zone ----------------\n");
	PointStr  tabPointZones[]={{1,2},{6,7},{6,1},{10,9}} ;
	testIntersection(arbEx, tabPointZones, 4);


	printf("\n-----------test du point le plus proche-----------\n");
	PointStr tabPointsPP[]={{3,4}, {5,2}, {8,4}, {11,9}};
	testPlusProche(arbEx, tabPointsPP,4);

	return 0 ;
}



void main(){
	mainArbreExemple();
	//mainListePoints();
    //mainLongueListePoints();

    /*compteur=0; // avant chaque appel
    ABRZ   arb = arbreExemple();
    ABRZ res=rechercher(arb,creerPoint(2,7));
    printf("nombre de points parcourus =%d", compteur) ;
*/

}
