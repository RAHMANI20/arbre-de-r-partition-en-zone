#Brice Le Meur 21810250
#Faical Sid Ahmed Rahmani 22010400
#numero binome 2447

res2 = None
A = None
compteur = 0
import math

INFINI=200
def creerPoint(x , y):
    return [x,y]

def afficherPoint(point):
    print("(%.0f,%.0f)"%(point[0], point[1]),end="");

def estEgal(point1, point2):
    return point1 == point2

# ========== liste de points
class ListePoint:
    def __init__(self,p):
        self.valeur=p
        self.suivant=None

    def __init__(self,p,lp):
        self.valeur = p
        self.suivant = lp

def ajouterDevant(p, lp):
   temp = ListePoint
   temp.valeur = p
   temp.suivant = lp
   return temp

#----------  extend( [2,3], [4, 7]) = [2, 3, 4, 7]
def extend(l1,  l2):
    if(l1==None):
        return l2;
    if(l2==None):
        return l1
    temp=l1
    while(temp != None):
        l2=ajouterDevant(temp.valeur,l2);
        temp = temp.suivant
    return l2

# ----------- affichage d'une liste de points
def afficherLPoint(lp):
    temp = lp
    while(temp !=None):
        p=temp.valeur;
        print("(%.0f , %.0f)"%(p[0], p[1]), end=",");
        temp = temp.suivant

# une zone est une liste de deux points [infg, supd]
def infg(zone):
    return zone[0]
def supd(zone):
    return zone[1]

# ======================= ABRZ=================
class ABRZ :
    def __init__(self,p):
        self.valeur=p
        self.gauche=None
        self.droit=None
        self.cs=0

    def __init__(self,p,g,d,c):
        self.valeur = p
        self.gauche = g
        self.droit = d
        self.cs = c

    def noeudToString(self):
        """ chaine d'affichage de la valeur et du cs du noeud"""
        return "%s,%s"%(str(self.valeur),str(self.cs))

def estFeuille(arb):
    return  ((arb != None) and (arb.gauche==None) and (arb.droit==None))

#------------ affichage d'un arbre --------------

def hauteur(A):
    """fonction qui calcul la hauteur d'un arbre binaire a"""
    if A == None: return -1
    return 1 + max(hauteur(A.gauche), hauteur(A.droit))

def dessinArbre(A, decalage=1):
    """retourner une chaine d(affichage planaire de l'arbre"""
    if A == None:
        return ""

    def affichageProfondeur(A, profondeur):
        if A == None:
            return " "
        ligne = affichageProfondeur(A.gauche, profondeur - 1)
        if (profondeur == 0):
            #ligne += str(A.valeur) + "," + str(A.cs)
            ligne += A.noeudToString()
        else:
            ligne += " "
        return ligne + affichageProfondeur(A.droit, profondeur - 1)

    chaine = ""
    for p in range(hauteur(A) + 1):
        chaine += affichageProfondeur(A, p) + '\n'

    return chaine

def afficherArbre(A):
    """ affichage de l'arbre"""
    print(dessinArbre(A))

## creation et insertion arbres

def creerArbre(point,gauche,droit,cs):
    return ABRZ(point,gauche,droit,cs)

#=======QUESTION 1 : implementer inserer
def insererAux(arb, p, cs):
    if (arb == None):
        return (creerArbre(p, None, None, cs))
    else:
        ptr = arb.valeur
        if (ptr == p):
            arb.gauche = insererAux(arb.gauche, p, (cs+1)%2)
        elif (cs == 0):
            if (p[0] <= ptr[0]):
                arb.gauche = insererAux(arb.gauche, p, (cs+1)%2)
            else:
                arb.droit = insererAux(arb.droit, p, (cs+1)%2)
        else:
            if (p[1] <= ptr[1]):
                arb.gauche = insererAux(arb.gauche, p, (cs+1)%2)
            else:
                arb.droit = insererAux(arb.droit, p, (cs+1)%2)
    return (arb)

def inserer(arb,  p):
    if (arb == None):
        return insererAux(arb, p, 0)
    else:
        return insererAux(arb, p, arb.cs)

#============== QUESTION  2 : recherche de point
def rechercherPoint(arb, pt):
    global compteur
    if (arb == None):
        return None
    else:
        if (arb.valeur == pt):
            return arb
        else:
            if (arb.cs == 0):
                if (arb.valeur[0] >= pt[0]):
                    compteur += 1
                    return rechercherPoint(arb.gauche, pt)
                else:
                    compteur += 1
                    return rechercherPoint(arb.droit, pt)
            else:
                if (arb.valeur[1] >= pt[1]):
                    compteur += 1
                    return rechercherPoint(arb.gauche, pt)
                else:
                    compteur += 1
                    return rechercherPoint(arb.droit, pt)

#=====================QUESTION 3: points d'abcisse minimale
def minAbc(a, b):
    if (a == None and b == None):
        return None
    if (a == None and b != None):
        return (b)
    if (b == None and a != None):
        return (a)
    if (a.valeur[0] < b.valeur[0]):
        return (a)
    return (b)

def minX(arb):
    global compteur
    if (arb.gauche == None and arb.droit == None):
        return (arb)
    if (arb.cs == 0):
        if (arb.gauche != None):
            compteur += 1
            return (minX(arb.gauche))
        else:
            return (arb)
    else:
        min1 = None
        min2 = None
        if (arb.gauche != None):
            compteur += 1
            min1 = minX(arb.gauche)
        if (arb.droit != None):
            compteur += 1
            min2 = minX(arb.droit)
        min1 = minAbc(min1,min2)
        if (min1.valeur[0] < arb.valeur[0]):
            return (min1)
        else:
            return (arb)       

# ==================Question 4: points dans droite verticale
def dansDroiteV(arb, x):
    global compteur
    if (arb == None):
        return None
    else:
        if (arb.valeur[0] == x):
            print(arb.valeur)
        if (arb.cs == 0):
            if (arb.valeur[0] < x):
                compteur += 1
                dansDroiteV(arb.droit,x)
            else:
                compteur += 1
                dansDroiteV(arb.gauche,x)
        else:
            compteur += 1
            dansDroiteV(arb.gauche,x)
            compteur += 1
            dansDroiteV(arb.droit,x)

#  ================ Question 5:  intersection avec une zone
def estDansZone(pt, pinfg, psupd):
    return (((pt[0] > pinfg[0]) and (pt[0] <= psupd[0])) and ((pt[1] > pinfg[1]) and (pt[1] <= psupd[1])))

def intersection(arb, pinfg, psupd):
    global compteur
    if (arb == None):
        return None
    else:
        if (estDansZone(arb.valeur,pinfg,psupd) == True):
            print(arb.valeur)
            compteur += 1
            intersection(arb.gauche,pinfg,psupd)
            compteur += 1
            intersection(arb.droit,pinfg,psupd)
        else:
            compteur += 1
            intersection(arb.gauche,pinfg,psupd)
            compteur += 1
            intersection(arb.droit,pinfg,psupd)

# ================= un point parmil les plus proche ----------
def position_droite_cercle(p, cs, cen, ray):
    if (cs ==0):
        if ((cen[0] - ray) <= p[0] and p[0] <= (cen[0] + ray)):
            return (0)
        if ((cen[0] - ray) > p[0]):
            return (-1)
        if ((cen[0] + ray) < p[0]):
            return (1)
    else:
        if ((cen[1] - ray) <= p[1] and p[1] <= (cen[1] + ray)):
            return (0)
        if ((cen[1] - ray) > p[1]):
            return (-1)
        if ((cen[1] + ray) < p[1]):
            return (1)

def  carre(x):
   return x * x

def distance(a, b):
    xx= (b[0] - a[0])
    yy = (b[1] - a[1])
    return carre(xx) + carre(yy)

def plusprocheAux(A, q, ppc, dminc):
    global compteur
    if (A == None):
        return ppc
    elif (math.sqrt(distance(A.valeur,q)) < dminc):
        dminc = math.sqrt(distance(A.valeur,q))
        ppc = A.valeur
    elif (position_droite_cercle(A.valeur,A.cs,q,dminc) == 0):
        compteur += 1
        a = plusprocheAux(A.gauche, q, ppc, dminc)
        compteur += 1
        b = plusprocheAux(A.droit, q, ppc, dminc)
        if (math.sqrt(distance(a,q)) <= math.sqrt(distance(b,q))):
            if (math.sqrt(distance(a,q)) <= dminc):
                return (a)
        elif (math.sqrt(distance(b,q)) <= math.sqrt(distance(a,q))):
            if (math.sqrt(distance(b,q)) <= dminc):
                return (b)
        return ppc
    elif (position_droite_cercle(A.valeur,A.cs,q,dminc) == -1):
        compteur += 1
        return (plusprocheAux(A.droit, q, ppc, dminc))
    compteur += 1
    return (plusprocheAux(A.gauche,q,ppc,dminc))
    

def plusproche(A, q):
    global compteur
    if (A == None):
        return None
    compteur += 1
    return  plusprocheAux(A, q, A.valeur, math.sqrt(distance(A.valeur,q)))


# =====================-tests de chaque fonction=============
def testRecherche(arb, tabPoints):
    """ recherche d'un point pt dans un arbre arb """
    for pt in tabPoints:
        res=rechercherPoint(arb,pt)
        if (res==None):
            print("point non trouve")
        else:
            print("\n  - le point %s est racine de \n" %(str(pt)))
            afficherArbre(res)

def testMinX(arb):
   print("\n un point d'abcise minimal, racine de:\n")
   res = minX(arb)
   afficherArbre(res)

def testDansDroiteV(arb, tabX):
    for vx in tabX:
        print("\n   - les points de la droite (x=%.2f) sont:"%(vx))
        dansDroiteV(arb, vx)

def testIntersection(arbEx, tabZones):
    for zone in tabZones:
        pinfg=infg(zone)
        psupd=supd(zone)
        print("\n -la zone [(%.1f , %.1f),(%.1f , %.1f)] contient:"%(pinfg[0], pinfg[1], psupd[0], psupd[1]))
        intersection(arbEx, pinfg, psupd)

def testPlusProche(arbEx, tabPoints):
       for pt in tabPoints:
           print("\n")
           res=plusproche(arbEx, pt)
           print("\n  - un point parmi les plus proches de (%.2f , %.2f) est:"%(pt[0], pt[1]), end="");
           afficherPoint(res)

#=================== test dans main ==========
def mainAvecArbreExemple():
    global compteur
    """ main test avec l arbre exemple  """
    print("\n-------- creation arbre exemple -------\n")
    arbEx = arbreExemple()
    print("\n ------- affichage arbre exemple ----- \n")
    afficherArbre(arbEx)

    print("\n---------test de la recherche de points-----------\n")
    compteur = 0
    tabPoints = [[5, 4], [9, 8]]
    testRecherche(arbEx, tabPoints)  
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))
    

    print("\n-----------test de l'abcisse minimale----  \n")
    compteur = 0
    testMinX(arbEx)
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n -----------test  dans droite verticale ----------------\n");
    compteur = 0
    tabX= [5.0, 6.0]
    testDansDroiteV(arbEx, tabX);
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n -----------test intersection avec zone ----------------\n");
    compteur = 0
    tabZones = [[[1, 2], [6, 7]], [[6, 1], [10, 9]]]
    testIntersection(arbEx, tabZones)
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n-----------test du point le plus proche-----------\n");
    compteur = 0
    tabPoints = [[3, 4], [5, 2], [8, 4], [11, 9]]
    testPlusProche(arbEx, tabPoints)
#Compteur de noeuds parcourus
    print("\n nombre de points parcourus = %s"%(str(compteur)))

def mainListePoints():
    global compteur
    """ main test avec liste points exemple  """
    listePoints = [[7, 6], [2, 10], [11, 3], [10, 9], [4, 4], [5, 8],
                   [6, 1], [8, 7], [1, 5], [9, 2], [8, 4], [9, 5], [5, 9],
                   [6, 3], [7, 8], [2, 3]]

    print("\n-------- creation arbre exemple -------\n")
    arbEx = None
    for pt in listePoints:
        arbEx=inserer(arbEx, pt)
    print("\n ------- affichage arbre exemple ----- \n")
    afficherArbre(arbEx)

    print("\n---------test de la recherche de points-----------\n")
    compteur = 0
    tabPoints = [[5, 4], [9, 8]]
    testRecherche(arbEx, tabPoints)
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n-----------test de l'abcisse minimale----  \n")
    compteur = 0
    testMinX(arbEx)
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n -----------test  dans droite verticale ----------------\n");
    compteur = 0
    tabX= [5.0, 6.0]
    testDansDroiteV(arbEx, tabX);
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n -----------test intersection avec zone ----------------\n");
    compteur = 0
    tabZones = [[[1, 2], [6, 7]], [[6, 1], [10, 9]]];
    testIntersection(arbEx, tabZones)
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n-----------test du point le plus proche-----------\n");
    compteur = 0
    tabPoints = [[3, 4], [5, 2], [8, 4], [11, 9]]
    testPlusProche(arbEx, tabPoints)
#Compteur de noeuds parcourus
    print("\n nombre de points parcourus = %s"%(str(compteur)))


def mainLongueListePoints():
    global compteur
    """ main test avec une liste de 100 points  """
    listePoints = [[22, 37],[9, 26],[35, 4],[15, 9],[8, 10],[27, 8],[34, 30],[31, 28],[5, 27],
                   [3, 27],[13, 13],[12, 37],[2, 12],[17, 32],[1, 28],[2, 21],[32, 7],[23, 25],[37, 31],
                   [24, 21],[2, 12],[23, 35],[35, 36],[25, 17],[10, 39],[24, 7],[36, 14],[27, 19],[12, 1],[38, 20],
                   [37, 9],[17, 27],[7, 0],[3, 26],[9, 13],[12, 1],[23, 20],[29, 20],[32, 35],[1, 33],[5, 9],[37, 36],[5, 31],
                   [10, 0],[27, 26],[20, 37],[27, 9],[32, 11],[8, 14],[3, 20],[1, 32],[31, 1],[25, 8],[6, 22],[1, 39],[7, 21],
                   [6, 23],[22, 39],[20, 7],[11, 15],[8, 10],[25, 24],[2, 6],[31, 25],[22, 1],[21, 2],[4, 21],[19, 22],[31, 5],
                   [8, 38],[9, 13],[24, 6],[32, 4],[37, 26],[27, 3],[31, 22],[25, 18],[6, 19],[14, 30],[19, 30],[18, 21],[2, 39],
                   [27, 39],[22, 27],[39, 11],[2, 3],[24, 38],[32, 28],[4, 5],[1, 6],[2, 26],[14, 11],[12, 36],[23, 9],[17, 35],
                   [22, 30],[38, 5],[36, 6],[17, 15],[29, 33]]



    print("\n-------- creation arbre exemple -------\n")
    arbEx = None
    for pt in listePoints:
        arbEx = inserer(arbEx, pt)
    print("\n ------- affichage arbre exemple ----- \n")
    afficherArbre(arbEx)

    print("\n---------test de la recherche de points-----------\n")
    compteur = 0
    tabPoints = [[24, 7], [6, 19], [0, 5]]
    testRecherche(arbEx, tabPoints)
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n-----------test de l'abcisse minimale----  \n")
    compteur = 0
    testMinX(arbEx)
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n -----------test  dans droite verticale ----------------\n");
    compteur = 0
    tabX = [5.0, 6.0]
    testDansDroiteV(arbEx, tabX);
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n -----------test intersection avec zone ----------------\n");
    compteur = 0
    tabZones = [[[1, 2], [6, 7]], [[6, 1], [10, 9]]];
    testIntersection(arbEx, tabZones)
#Compteur de noeuds parcourus
    print("nombre de points parcourus = %s"%(str(compteur)))

    print("\n-----------test du point le plus proche-----------\n");
    compteur = 0
    tabPoints = [[3, 4], [5, 2], [8, 4], [11, 9]]
    testPlusProche(arbEx, tabPoints)
#Compteur de noeuds parcourus
    print("\n nombre de points parcourus = %s"%(str(compteur)))


def  arbreExemple():
    """ un exemple d arbre de type ABRZ """
    aex = None ;    g = None ;     d = None
    d = creerArbre(creerPoint(3, 5), None, None, 1);
    g = creerArbre(creerPoint(1, 5), None, None, 1);
    aex = creerArbre(creerPoint(2, 4), g, d, 0);
    aex = creerArbre(creerPoint(1, 3), None, aex, 1);

    d = creerArbre(creerPoint(6, 3), None, None, 1);
    d = creerArbre(creerPoint(5, 4), None, d, 0);
    d = creerArbre(creerPoint(6, 2), None, d, 1);
    aex = creerArbre(creerPoint(4, 3), aex, d, 0);

    d = creerArbre(creerPoint(5, 9), None, None, 1);
    d = creerArbre(creerPoint(3, 10), None, d, 0);
    aex = creerArbre(creerPoint(1, 6), aex, d, 1);

    g = creerArbre(creerPoint(9, 8), None, None, 1);
    d = creerArbre(creerPoint(11, 9), g, None, 0);
    d = creerArbre(creerPoint(8, 5), None, d, 1);
    aex = creerArbre(creerPoint(7, 1), aex, d, 0);
    return aex;


# programme principal
def main():
    mainAvecArbreExemple()
    mainListePoints()
    mainLongueListePoints()


main()
