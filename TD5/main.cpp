/**
* Programme qui lit un journal de détection d'une mission à partir d'un fichier binaire,
le modifie et le transcrit dans un autre fichier binaire.
Ce fichier contient le programme ainsi que les tests des fonctions permettant de réaliser ce programme.
* \file   main.cpp
* \author Sofia Alvarez (1894016) et Mihaela Talpos (1894329)
* \date   19 novembre 2018
* Créé le 7 novembre 2018
*/

#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include "CodeDemande.hpp"
#include "CodeFourni.hpp"


using namespace std;

#pragma endregion //}


void tests_partie1()
{
	//afficher un true or false si les tests passent
	//identifier les tests 

	cout << endl << "Debut des tests partie 2." << endl << endl;

	// Dans la partie 1, on déclare une liste de cibles avec un tableau statique, puisque l'allocation dynamique est vue en classe seulement la semaine suivante.
	Cible tableauCibles[3] = {};
	ListeCibles cibles = { tableauCibles, 0, size(tableauCibles) };

	//TODO: Ajouter 3 fois une cible (ajouterCible) à la cibles, chacun avec un ID différent (les autres valeurs ne sont pas importantes);
	//TODO: après chaque ajout vérifier que le nombre de cibles est bon (i.e. 1 après le premier ajout, 2 après le deuxième), et que les données de la cible sont dans la liste (vérifiez uniquement l'ID).
	//TODO: Ajouter une autre cible, le nombre d'éléments devrait être encore 3 puisque c'est la capacité de la liste.

	Cible ciblesTest[4];
	for (int i = 0; i < 4; i++)
		ciblesTest[i] = { (uint32_t)(1 * i), { 1.0, 1.0 }, "observation", "nomFichier" };
	
	for (int i = 0; i < 3; i++) {
		ajouterCible(cibles, ciblesTest[i]);
		cout << "Le nombre d'elements dans la liste est: " << cibles.nbElements << endl;
		cout << "L'ID de la cible a l'indice " << i << " est: " << cibles.elements[i].id << endl;
	}

	ajouterCible(cibles, ciblesTest[4]);
	cout << "Le nombre d'elements dans la liste est: " << cibles.nbElements << endl;
	

	//TODO: Retirer la cible (retirerCible) ayant l'ID que vous avez mis en 2e, vérifier qu'il reste 2 éléments aux indices 0 et 1 dont les ID sont les bons.

	retirerCible(cibles, 1);
	cout << "Le nombre d'elements dans la liste est: " << cibles.nbElements << endl;
	for (int i = 0; i < cibles.nbElements; i++) {
		cout << "L'ID de la cible a l'indice " << i << " est: " << cibles.elements[i].id << endl;
	}

	//note: utliser la ListeCibles cibles

	//TODO: Écrire les cibles (ecrireCibles) dans le fichier fichierTestCibles. Vérifier que la tête d'écriture est rendue au bon endroit.
	
	fstream fichierTestCibles("fichierTestCibles.bin", ios::in | ios::out | ios::trunc | ios::binary);

	ecrireCibles(fichierTestCibles, cibles);
	if (fichierTestCibles.tellp() == (cibles.nbElements * sizeof(Cible)))
		cout << "La tete de lecture est a la bonne place." << endl;
	else
		cout << "La tete de lecture n'est pas a la bonne place." << endl;

	Cible tableauCibles2[3] = {};
	ListeCibles cibles2 = { tableauCibles2, 0, size(tableauCibles) };
	
	//TODO: Remettre la tête de lecture au début du fichier puis lire les cibles (lireCibles) dans cibles2. Vérifier que les 2 bonnes cibles y sont.
	
	fichierTestCibles.seekg(0, ios::beg);
	lireCibles(fichierTestCibles, cibles2);
	for (int i = 0; i < cibles2.nbElements; i++) {
		cout << "L'ID de la cible 2 a l'indice " << i << " est: " << cibles2.elements[i].id << endl;
	}
	
	//TODO: Créer une variable de type JournalDetection avec des valeurs quelconques et une ListeCibles déjà créé ci-dessus.
	//TODO: Écrire ce journal (ecrireJournalDetection) dans un nouveau fichier binaire.
	//TODO: Vérifier que ok est vrai.
	//NOTE: La relecture du fichier pour vérifier qu'il est bon se fera seulement dans 
	//la partie 2.  Vous pouvez pour l'instant vérifier que la taille du fichier est 
	//bonne (propriétés du fichier dans Windows; la "taille" en octets devrait être une 
	//taille d'entête plus le bon nombre de cibles; attention de ne pas regarder la 
	//"taille sur disque" qui peut être différente de la "taille" dans les propriétés du fichier).  
	//Vous pouvez aussi ouvrir le fichier binaire avec un éditeur binaire (par exemple celui de VisualStudio) 
	//pour voir si les ID sont bien dans le fichier.

	time_t t = time(0);
	tm* now = localtime(&t);
	ParametresMission parametres = {"sonnom", "quelquesnotes", *now};
	JournalDetection journalTest = {parametres, cibles};

	bool ok;
	ecrireJournalDetection("fichierTestCibles.bin", journalTest, ok);
	if (ok)
		cout << "L'ouverture a reussie." << endl;
	else
		cout << "L'ouverture a echouee." << endl;
	   	 
	//TODO: Ajouter une observation (ecrireObservation) au fichier créé ci-dessus à l'indice 1 (deuxième cible).
	//NOTE: Même chose que ci-dessus: la taille du fichier ne devrait pas avoir changée
	// et dans l'éditeur binaire vous devriez voir le texte après le deuxième ID.
	
	string observation = "observation";
	ecrireObservation("fichierTestCibles.bin", 1, observation);

}

void tests_partie2()
{
	cout << endl << "Debut des tests partie 2." << endl << endl;
	
	//TODO: Allouer une liste de cibles (allouerListe) de capacité 2; vérifier que la capacité est la bonne et que le nombre d'éléments est zéro.
	ListeCibles cibles3;
	cibles3 = allouerListe(2);
	cout << "La capacite de la liste cibles3 est " << cibles3.capacite 
		<< " et le nombre d'elements est " << cibles3.nbElements << endl;
	
	//TODO: Ajouter une cible la liste; ça devrait fonctionner.
	Cible cibleTest = { (uint32_t)(1234), { 1.0, 1.0 }, "observation", "nomFichier" };
	ajouterCible(cibles3, cibleTest);
	cout << "L'id de la cible ajoutee est : " << cibles3.elements->id << endl;
	
	//TODO: Conserver le pointeur vers le tableau de cibles dans une variable.
	Cible* ptrCibles = cibles3.elements;

	//TODO: Désallouer la liste (desallouerListe); vérifier que les valeurs sont à zéro.
	desallouerListe(cibles3);
	cout << "La capacite de la liste cibles3 est " << cibles3.capacite
		<< " et le nombre d'elements est " << cibles3.nbElements << endl;
	cout << "L'id efface est : " << ptrCibles->id << endl;
	cout << "Le pointeur pointe vers : " << cibles3.elements << endl;
	
	/*TODO: Allouer une nouvelle liste de cibles de capacité 2; 
	*/

	ListeCibles cibles4;
	cibles4 = allouerListe(3);
	if (cibles4.elements == ptrCibles) {
		cout << "Les pointeurs sont les memes." << endl;
		cout << cibles4.elements << endl;
		cout << ptrCibles << endl;
	}
	else
		cout << "Les pointeurs ne sont pas les memes." << endl;

	//TODO: Désallouer cette deuxième liste.
	desallouerListe(cibles4);

	//NOTE: lireJournalDetection est directement testé par ce qu'il y a à faire dans le main.
}

int main ( )
{
	tests_partie1();
	tests_partie2();

	const string nomFichierCibles = "Cibles.data";
	const string nomFichierCiblesFinal = "Cibles_final.data";
	
	string observation = "Cercle noir, E rouge";
	
	Cible c11 = {11, {38.140728, -76.426494}, "Triangle gris, O orange", "cible_11.jpg"};
	
	bool ok;
	JournalDetection journal = lireJournalDetection(nomFichierCibles, ok);

	if (ok == false) {
		cout << endl << "Erreur de lecture!" << endl;
		return -1;
	}
	
	afficherJournal(journal);
	retirerCible(journal.cibles, journal.cibles.elements[4].id);
	ajouterCible(journal.cibles, c11);
	afficherJournal(journal);
	
	ecrireJournalDetection(nomFichierCiblesFinal, journal, ok);
	verificationErreur(ok);
	
	ecrireObservation(nomFichierCiblesFinal, 2, observation);
	
	JournalDetection journalFinal = lireJournalDetection(nomFichierCiblesFinal, ok);

	afficherJournal(journalFinal);	
	desallouerListe(journal.cibles);
	desallouerListe(journalFinal.cibles);

	verificationErreur(ok);

	return 0;
}
