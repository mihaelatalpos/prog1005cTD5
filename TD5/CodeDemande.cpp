/**
* Programme qui lit un journal de détection d'une mission à partir d'un fichier binaire,
	le modifie et le transcrit dans un autre fichier binaire.
	Ce fichier contient les fonctions permettant de réaliser ce programme.
* \file   CodeDemande.cpp
* \author Sofia Alvarez (1894016) et Mihaela Talpos (1894329)
* \date   19 novembre 2018
* Créé le 7 novembre 2018
*/

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
#include <iostream>

using namespace std;

#pragma endregion //}


#pragma region "Globaux" //{

#pragma region "Fonctions" //{

/**
*  Ajoute une cible dans une liste de cibles.
*  \param [in/out] liste  La liste qui contient toutes les cibles.
*  \param [in]     cible  La cible que l'on veut ajouter à la liste.
*  \return void
*/
void ajouterCible(ListeCibles& liste, const Cible& element)
{
	if (liste.nbElements != liste.capacite)
		liste.elements[liste.nbElements++] = element;
}

/**
*  Retire la cible correspondante au ID donné dans une liste de cibles.
*  \param [in/out] liste  La liste qui contient toutes les cibles.
*  \param [in]     id     Le ID de la cible que l'on veut retirer de la liste.
*  \return void
*/
void retirerCible(ListeCibles& liste, uint32_t id)
{
	for (int i = 0; i < liste.nbElements; i++) {
		if(liste.elements[i].id == id){
			for(int j = i; j < liste.nbElements; j++)
				liste.elements[j] = liste.elements[j + 1];
			liste.nbElements--;
			return;
		}
	}
}

/**
*  Lire les cibles du fichier binaire qui contient le journal de détection
	et les mettre dans une liste de cibles.
*  \param [in/out] fichier  Le fichier binaire qui contient les données.
*  \param [in/out] cibles	La liste de cibles.
*  \return void
*/
void lireCibles(istream& fichier, ListeCibles& cibles)
{
	//se positionner après les paramètres de la mission pour lire les cibles
	fichier.seekg(sizeof(ParametresMission), ios::beg);
	
	int i = 0;
	while (fichier.peek() != EOF) {
		fichier.read((char*)&cibles.elements[i], sizeof(Cible));
		ajouterCible(cibles, cibles.elements[i]);
		i++;
	}
}

/**
*  Écrire les cibles d'une liste de cibles et
	et les mettre dans un fichier binaire.
*  \param [in/out] fichier  Le fichier binaire dans lequel on veut écrire.
*  \param [in]     cibles	La liste de cibles que l'on veut transcrire.
*  \return void
*/
void ecrireCibles(ostream& fichier, const ListeCibles& cibles)
{
	fichier.seekp(0, ios::cur);
	fichier.write((char*)cibles.elements, cibles.nbElements * sizeof(Cible));
}

/**
*  Écrire les paramètres et les cibles d'un journal de détection dans un fichier binaire
	et en vérifier sa réussite.
*  \param [in]  nomFichier  Le nom du fichier binaire dans lequel on veut écrire.
*  \param [in]  journal	    Le journal de détection que l'on veut transcrire.
*  \param [out] ok          Booléen qui vérifie la réussite de l'ouverture du fichier.
*  \return void
*/
void ecrireJournalDetection(const string& nomFichier, const JournalDetection& journal, bool& ok)
{
	ofstream fichierBinaire(nomFichier, ios::binary);

	if (fichierBinaire.fail())
		ok = false;
	else
		ok = true;

	fichierBinaire.seekp(0, ios::beg);
	fichierBinaire.write((char*)&journal.parametres, sizeof(journal.parametres));
	ecrireCibles(fichierBinaire, journal.cibles);
}

/**
*  Écrire une observation dans le fichier binaire
	à côté de la cible correspondante à l'index donné.
*  \param [in] nomFichier   Le nom du fichier binaire dans lequel on veut écrire.
*  \param [in] index        L'index de la cible où l'on veut rajouter l'observation.
*  \param [in] observation  L'obseration qu'on veut écire.
*  \return void
*/
void ecrireObservation(const string& nomFichier, size_t index, const string& observation)
{
	fstream fichierBinaire(nomFichier, ios::in | ios::out | ios::binary);
	
	//positionnement après les paramètres, au debut de la cible voulue
	fichierBinaire.seekg(sizeof(ParametresMission) + ((index - 1) * sizeof(Cible)), ios::beg); 

	Cible cible;
	fichierBinaire.read((char*)&cible, sizeof(cible));

	strcpy_s(cible.observation, observation.c_str());

	//repositionnement au debut de la cible
	fichierBinaire.seekp((-1 * streamoff(sizeof(Cible))), ios::cur); 

	fichierBinaire.write((char*)&cible, sizeof(cible));
}

/**
*  Allouer une certaine capacité à une liste de cibles vide au départ;
	indique le nombre maximal de cibles qui peuvent se trouver dans cette liste.
*  \param [in] capacité  La capacité de cibles que l'on veut allouer à la liste.
*  \return Une liste de cibles vide, ayant une certaine capacité et aucun éléments.
*/
ListeCibles allouerListe(size_t capacite)
{
	return { new Cible[capacite], 0, capacite };
}

/**
*  Désallouer l'espace utilisé pour la liste de cibles
	et remet toutes les paramètres de la liste de cibles à 0.
*  \param [in/out] cibles La liste que l'on veut désallouer.
*  \return void
*/
void desallouerListe(ListeCibles& cibles)
{
	delete[] cibles.elements;
	cibles = {0};
}

/**
*  Lire un fichier binaire qui contient un journal de détection d'une mission.
*  \param [in]  nomFichier Le nom du fichier duquel on veut lire le journal.
*  \param [out] ok         Booléen qui vérifie la réussite de l'ouverture du fichier.
*  \return Un journal de détection qui contient les paramètres et les cibles du fichier binaire.
*/
JournalDetection lireJournalDetection(const string& nomFichier, bool& ok)
{
	ifstream fichierBinaire(nomFichier, ios::binary);
	if (fichierBinaire.fail())
		ok = false;
	else
		ok = true;

	JournalDetection journal;
	fichierBinaire.seekg(0, ios::beg);
	fichierBinaire.read((char*)&journal.parametres, sizeof(journal.parametres));

	
	int nbCibles = 0;
	Cible cibles;
	while (fichierBinaire.peek() != EOF) {
		fichierBinaire.seekg(0, ios::cur);
		fichierBinaire.read((char*)&cibles, sizeof(Cible));
		nbCibles++;
	}

	journal.cibles = allouerListe(nbCibles);	
	lireCibles(fichierBinaire, journal.cibles);

	return journal;
}
// fonction vérification d'erreur
void verificationErreur(bool& ok, string nomFonction) {
	if (ok == false) {
		cout << endl << "Erreur de lecture dans: " << nomFonction << endl;
	
	}
}

#pragma endregion //}

#pragma endregion //}
