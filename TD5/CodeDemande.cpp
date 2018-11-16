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
	// DONE: S'il reste de la place, ajouter l'élément à la fin.
	if (liste.nbElements != liste.capacite)
		liste.elements[liste.nbElements++] = element;
}


void retirerCible(ListeCibles& liste, uint32_t id)
{

	for (int i = 0; i < liste.nbElements; i++) {
		if(liste.elements[i].id == id){
			for(int j = i; j < liste.nbElements; j++)
				liste.elements[j] = liste.elements[j + 1];
			liste.nbElements--;
		}
	}
	//  DONE: Rechercher la cible avec le même ID et le retirer de la liste si
	//       présent. ATTENTION! On parle bien de Cible::id, pas de l'index
	//       dans le tableau.

}


void lireCibles(istream& fichier, ListeCibles& cibles)
{
	int i = 0;
	// DONE: Tant que la fin de fichier n'est pas atteinte :
	while (fichier.peek() != EOF) {

		fichier.seekg(0, ios::cur);
		fichier.read((char*)&cibles.elements[i], sizeof(Cible));
		ajouterCible(cibles, cibles.elements[i]);
		i++;

	}
		// DONE: Lire une 'Cible' à partir du ficher à la position
		//       courante et l'ajouter à la liste.

	//note: utilisr ajouter cible
}


void ecrireCibles(ostream& fichier, const ListeCibles& cibles)
{
	// DONE: Écrire tous les éléments de la liste dans le fichier à partir de la position courante.
	/*Notes pour moi-meme:
	On veut seulement ecrire les elements de la struct ListeCibles (qui contient aussi le nb et la capacite)
	Donc, cibles.elements
	Pour ecrire tous les elements d'un coup, il faut connaitre la longueur du tableau ou ces elements sont stores
	Sachant qu'un element est de type stuct Cible, sizeof(Cible) est la longure de UN element
	Donc, cibles.nbElement * sizeof(Cibles) retourne la longueur de tous les elements Cible
	On ne peut pas utiliser directement sizeof(cibles.elements), puisque c'est un pointeur vers un tableau.
	*/
	fichier.seekp(0, ios::cur);
	fichier.write((char*)cibles.elements, cibles.nbElements * sizeof(Cible));
}


void ecrireJournalDetection(const string& nomFichier, const JournalDetection& journal, bool& ok)
{
	// DONE: Ouvrir un fichier en écriture binaire.
	ofstream ficBin;
	ficBin.open(nomFichier, ios::binary);

	// DONE: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'.
	if (ficBin.fail())
		ok = false;
	else
		ok = true;

	// DONE: Écrire les paramètres de mission dans le fichier.
	//question: quelle position il faut commencer a ecrire?
	ficBin.seekp(0, ios::cur);
	ficBin.write((char*)&journal.parametres, sizeof(journal.parametres));

	// DONE: Écrire les cibles dans le fichier.
	ficBin.seekp(0, ios::cur);
	ficBin.write((char*)&journal.cibles, sizeof(journal.cibles));
}


void ecrireObservation(const string& nomFichier, size_t index, const string& observation)
{
	// DONE: Ouvrir un fichier en lecture/écriture binaire.

	// DONE: Se positionner (têtes de lecture et d'écriture) au début de la cible
	//       à l'index donné. On parle ici de l'index dans le fichier, donc 0 est
	//       la première cible dans le fichier, etc.

	// DONE: Lire cette cible.
	//       ATTENTION! Vous ne devez lire que cette cible isolée, pas tout le
	//       tableau.

	// DONE: Copier l'observation donnée en paramètre dans la cible.
	//       Astuce : strcpy()

	// DONE: Réécrire la cible (et seulement celle-là) dans le fichier.

	fstream ficBin(nomFichier, ios::in | ios::out | ios::binary);


	ficBin.seekg(((index + 1) * sizeof(Cible)), ios::beg); //positionnement au debut de la 3e cible

	Cible cible;
	ficBin.read((char*)&cible, sizeof(cible));

	strcpy_s(cible.observation, observation.c_str());

	ficBin.seekp((-1 * streamoff(sizeof(Cible))), ios::beg); //repositionnement au debut de la 3e cible

	ficBin.write((char*)&cible, sizeof(cible));

}


ListeCibles allouerListe(size_t capacite)
{

	ListeCibles listeDonnee;
	listeDonnee.nbElements = 0;
	listeDonnee.capacite = capacite;
	// TODO: Créer une 'ListeDonnee' vide (nbElements = 0) avec la capacité donnée.

	listeDonnee.elements = new Cible[capacite];
	// TODO: Allouer un tableau de 'Cible' de la taille demandée.
	return listeDonnee;
}


void desallouerListe(ListeCibles& cibles)
{
	delete []cibles.elements;
	// DONE: Désallouer le tableau d'élément.
	
	cibles.elements = 0;
	cibles.nbElements = 0;
	cibles.capacite = 0;

	// DONE: Remettre les membres à zéro.??
}

JournalDetection lireJournalDetection(const string& nomFichier, bool& ok)
{
	ifstream ficBin(nomFichier, ios::binary);
	if (ficBin.fail())
		ok = false;
	else
		ok = true;

	// DONE: Ovrir un fichier en lecture binaire.
	// DONE: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'.
	// DONE: Lire les paramètres de mission
	JournalDetection journal;
	ficBin.seekg(0, ios::beg);
	ficBin.read((char*)&journal.parametres, sizeof(journal.parametres));

	// DONE: Compter le nombre de cibles dans le fichier.
	int nbCibles = 0;
	Cible cibles;
	while (ficBin.peek() != EOF) {
		ficBin.read((char*)&cibles, sizeof(Cible));
		nbCibles++;
	}
	ListeCibles liste;
	allouerListe(nbCibles);
	// DONE: Allouer la liste de cibles avec la bonne capacité.
	lireCibles(ficBin, liste);

	// DONE: Lire les cibles.

	return journal;
}

#pragma endregion //}

#pragma endregion //}
