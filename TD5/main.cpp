/**
* Programme qui lit un journal de détection d'une mission à partir d'un fichier binaire,
le modifie et le transcrit dans un autre fichier binaire.
Ce fichier contient le programme ainsi que les tests des fonctions permettant de réaliser ce programme.
* \file   main.cpp
* \author Sofia Alvarez (1894016) et Mihaela Talpos (1894329)
* \date   20 novembre 2018
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
	cout << endl << "Debut des tests partie 1." << endl 
		         << "--------------------------" << endl;

	Cible tableauCibles[3] = {};
	ListeCibles cibles = { tableauCibles, 0, size(tableauCibles) };

	//création de 4 cibles ayant un ID différent
	Cible ciblesTest[4];
	for (int i = 0; i < 4; i++)
		ciblesTest[i] = { (uint32_t)(1 * i), { 1.0, 1.0 }, "observation", "nomFichier" };
	
	cout << endl << "Verification ajouterCible: " << endl;
	for (int i = 0; i < 3; i++) {
		ajouterCible(cibles, ciblesTest[i]);
		cout << "Le nombre d'elements dans la liste est " << cibles.nbElements 
			<< " et l'ID de la cible ajoutee est " << cibles.elements[i].id << " -> ";
		if (cibles.nbElements == (i + 1) && cibles.elements[i].id == (1 * i))
			cout << boolalpha << true << endl;
		else
			cout << boolalpha << false << endl;
	}

	ajouterCible(cibles, ciblesTest[4]);
	cout << "Le nombre d'elements dans la liste est: " << cibles.nbElements << " -> ";
	if (cibles.nbElements == 3)
		cout << boolalpha << true << endl;
	else
		cout << boolalpha << false << endl;

	cout << endl << "Verification retirerCible: " << endl;
	retirerCible(cibles, 1);
	cout << "Le nombre d'elements dans la liste est: " << cibles.nbElements << " -> ";
	if (cibles.nbElements == 2)
		cout << boolalpha << true << endl;
	else
		cout << boolalpha << false << endl;
	for (int i = 0; i < cibles.nbElements; i++)
		cout << "L'ID de la cible restante a l'indice " << i << " est: " << cibles.elements[i].id << endl;
	if (cibles.elements[0].id == 0 && cibles.elements[1].id == 2)
		cout << " -> " << boolalpha << true << endl;
	else
		cout << " -> " << boolalpha << false << endl;

	
	fstream fichierTestCibles("fichierTestCibles.bin", ios::in | ios::out | ios::trunc | ios::binary);

	cout << endl << "Verification ecrireCible: " << endl;
	ecrireCibles(fichierTestCibles, cibles);
	if (fichierTestCibles.tellp() == (cibles.nbElements * sizeof(Cible)))
		cout << "La tete de lecture est a la bonne place." << endl;
	else
		cout << "La tete de lecture n'est pas a la bonne place." << endl;

	Cible tableauCibles2[3] = {};
	ListeCibles cibles2 = { tableauCibles2, 0, size(tableauCibles) };
	
	cout << endl << "Verification lireCible: " << endl;
	fichierTestCibles.seekg(0, ios::beg);
	lireCibles(fichierTestCibles, cibles2);
	for (int i = 0; i < cibles2.nbElements; i++)
		cout << "L'ID de la cible 2 a l'indice " << i << " est: " << cibles2.elements[i].id << endl;
	if (cibles2.elements[0].id == 0 && cibles2.elements[1].id == 2)
		cout << " -> " << boolalpha << true << endl;
	else
		cout << " -> " << boolalpha << false << endl;
	
	//création d'un journal de détection avec des paramètres de mission quelconques
	time_t t = time(0);
	tm* now = localtime(&t);
	ParametresMission parametres = {"sonnom", "quelquesnotes", *now};
	JournalDetection journalTest = {parametres, cibles};

	cout << endl << "Verification de l'ouverture du fichier dans ecrireJournalDetection: " << endl;
	bool ok;
	ecrireJournalDetection("fichierTestCibles.bin", journalTest, ok);
	if (ok)
		cout << "L'ouverture a reussie." << endl;
	else
		cout << "L'ouverture a echouee." << endl;

	//ajout d'une observation quelconque à la cible de l'indice 1
	string observation = "observation";
	ecrireObservation("fichierTestCibles.bin", 1, observation);
}

void tests_partie2()
{
	cout << endl << endl << "Debut des tests partie 2." << endl
		<< "--------------------------" << endl;
	
	cout << endl << "Verification allouerListe: " << endl;
	ListeCibles cibles3;
	cibles3 = allouerListe(2);
	cout << "La capacite de la liste cibles3 est " << cibles3.capacite 
		<< " et le nombre d'elements est " << cibles3.nbElements << " -> ";
	if (cibles3.capacite == 2 && cibles3.nbElements == 0)
		cout << boolalpha << true << endl;
	else
		cout << boolalpha << false << endl;
	
	cout << endl << "Verification ajouterCible dans la liste allouee: " << endl;

	//création d'une cible quelconque
	Cible cibleTest = { (uint32_t)(1234), { 1.0, 1.0 }, "observation", "nomFichier" };
	ajouterCible(cibles3, cibleTest);
	cout << "L'id de la cible ajoutee est " << cibles3.elements->id 
		<< " et le nombre d'elements est " << cibles3.nbElements << " -> ";
	if (cibles3.elements->id == 1234 && cibles3.nbElements == 1)
		cout << boolalpha << true << endl;
	else
		cout << boolalpha << false << endl;
	
	cout << endl << "Verification desallouerListe: " << endl;
	desallouerListe(cibles3);
	cout << "La capacite de la liste cibles3 est " << cibles3.capacite
		<< " et le nombre d'elements est " << cibles3.nbElements << " -> ";
	if (cibles3.capacite == 0 && cibles3.nbElements == 0)
		cout << boolalpha << true << endl;
	else
		cout << boolalpha << false << endl;
	cout << "Le pointeur pointe vers : " << cibles3.elements << endl << endl;
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
	verificationErreur(ok, "lireJournalDetection");
	
	afficherJournal(journal);
	retirerCible(journal.cibles, journal.cibles.elements[4].id);
	ajouterCible(journal.cibles, c11);
	afficherJournal(journal);
	
	ecrireJournalDetection(nomFichierCiblesFinal, journal, ok);
	verificationErreur(ok, "ecrireJournalDetection");
	
	ecrireObservation(nomFichierCiblesFinal, 2, observation);
	
	JournalDetection journalFinal = lireJournalDetection(nomFichierCiblesFinal, ok);

	afficherJournal(journalFinal);	
	desallouerListe(journal.cibles);
	desallouerListe(journalFinal.cibles);

	verificationErreur(ok, "journalFinal");
	
	return 0;
}
