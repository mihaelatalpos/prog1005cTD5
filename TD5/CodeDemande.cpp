////////////////////////////////////////////////////////////////////////////////
/// VOTRE ENTÊTE ICI
////////////////////////////////////////////////////////////////////////////////

#pragma region "Inclusions" //{

#include "CodeFourni.hpp"
#include "CodeDemande.hpp"

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <cmath>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

#pragma endregion //}


#pragma region "Globaux" //{

#pragma region "Fonctions" //{

void ajouterCible(ListeCibles& liste, const Cible& element)
{
	// TODO: S'il reste de la place, ajouter l'élément à la fin.
	if (liste.nbElements != liste.capacite) 
		liste.elements[liste.nbElements++] = element;
}


void retirerCible(ListeCibles& liste, uint32_t id)
{
	
	for (int i = 0; i < liste.nbElements; i++) {
		if(liste.elements[i].id == id){
			liste.elements[i].id = liste.elements[i + 1].id;
		}
	}
	// TODO: Rechercher la cible avec le même ID et le retirer de la liste si
	//       présent. ATTENTION! On parle bien de Cible::id, pas de l'index
	//       dans le tableau.
}


void lireCibles(istream& fichier, ListeCibles& cibles)
{
	// TODO: Tant que la fin de fichier n'est pas atteinte :
		// TODO: Lire une 'Cible' à partir du ficher à la position
		//       courante et l'ajouter à la liste.
}


void ecrireCibles(ostream& fichier, const ListeCibles& cibles)
{
	// TODO: Écrire tous les éléments de la liste dans le fichier à partir de la position courante.
	/*Notes pour moi-meme:
	On veut seulement ecrire les elements de la struct ListeCibles (qui contient aussi le nb et la capacite)
	Donc, cibles.elements
	Pour ecrire tous les elements d'un coup, il faut connaitre la longueur du tableau ou ces elements sont stores
	Sachant qu'un element est de type stuct Cible, sizeof(Cible) est la longure de UN element
	Donc, cibles.nbElement * sizeof(Cibles) retourne la longueur de tous les elements Cible
	*/
	fichier.seekp(0, ios::cur);
	fichier.write((char*)cibles.elements , cibles.nbElements * sizeof(Cible));
}


void ecrireJournalDetection(const string& nomFichier, const JournalDetection& journal, bool& ok)
{
	// TODO: Ouvrir un fichier en écriture binaire.
	ofstream ficBin;
	ficBin.open(nomFichier, ios::binary);

	// TODO: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'.
	if (ficBin.fail())
		ok = false;
	else
		ok = true;
			
	// TODO: Écrire les paramètres de mission dans le fichier.
	//question: quelle position il faut commencer a ecrire?
	ficBin.seekp(0, ios::cur);
	ficBin.write((char*)&journal.parametres, sizeof(journal.parametres));
	
	// TODO: Écrire les cibles dans le fichier.
	ficBin.seekp(0, ios::cur);
	ficBin.write((char*)&journal.cibles, sizeof(journal.cibles));
}


void ecrireObservation(const string& nomFichier, size_t index, const string& observation)
{
	// TODO: Ouvrir un fichier en lecture/écriture binaire.
	
	// TODO: Se positionner (têtes de lecture et d'écriture) au début de la cible 
	//       à l'index donné. On parle ici de l'index dans le fichier, donc 0 est
	//       la première cible dans le fichier, etc.
	
	// TODO: Lire cette cible.
	//       ATTENTION! Vous ne devez lire que cette cible isolée, pas tout le
	//       tableau.
	
	// TODO: Copier l'observation donnée en paramètre dans la cible.
	//       Astuce : strcpy()
	
	// TODO: Réécrire la cible (et seulement celle-là) dans le fichier.
}


ListeCibles allouerListe(size_t capacite)
{
	// TODO: Créer une 'ListeDonnee' vide (nbElements = 0) avec la capacité donnée.
	
	// TODO: Allouer un tableau de 'Cible' de la taille demandée.
	return {};
}


void desallouerListe(ListeCibles& cibles)
{
	// TODO: Désallouer le tableau d'élément.
	// TODO: Remettre les membres à zéro.
}


JournalDetection lireJournalDetection(const string& nomFichier, bool& ok)
{
	// TODO: Ouvrir un fichier en lecture binaire.
	
	// TODO: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'.
	
	// TODO: Lire les paramètres de mission
	
	// TODO: Compter le nombre de cibles dans le fichier.
	
	// TODO: Allouer la liste de cibles avec la bonne capacité.
	
	// TODO: Lire les cibles.
	return {};
}

#pragma endregion //}

#pragma endregion //}

