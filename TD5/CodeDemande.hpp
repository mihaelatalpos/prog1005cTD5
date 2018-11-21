/**
* Programme qui lit un journal de détection d'une mission à partir d'un fichier binaire,
	le modifie et le transcrit dans un autre fichier binaire.
	Ce fichier contient l'entête des fonctions permettant de réaliser ce programme.
* \file   CodeDemande.hpp
* \author Sofia Alvarez (1894016) et Mihaela Talpos (1894329)
* \date   20 novembre 2018
* Créé le 7 novembre 2018
*/

#pragma once

#pragma region "Inclusions" //{

#include "CodeFourni.hpp"

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <ctime>
#include <fstream>
#include <string>

using namespace std;

#pragma endregion //}


#pragma region "Déclarations" //{

#pragma region "Globaux" //{

void ajouterCible(ListeCibles&, const Cible&);

void retirerCible(ListeCibles&, uint32_t);

void lireCibles(istream&, ListeCibles&);

void ecrireCibles(ostream&, const ListeCibles&);

void ecrireJournalDetection(const string&, const JournalDetection&, bool&);

void ecrireObservation(const string&, size_t, const string&);

ListeCibles allouerListe(size_t);

void desallouerListe(ListeCibles&);

JournalDetection lireJournalDetection(const string&, bool&);

void verificationErreur(fstream&, bool&, const string&);

#pragma endregion //}

#pragma endregion //}

