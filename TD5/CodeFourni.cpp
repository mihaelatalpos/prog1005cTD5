////////////////////////////////////////////////////////////////////////////////
//  \file    CodeFourni.cpp
/// \author  Charles Hosson et François-R Boyer
/// \version 2018-11-06
///
/// L'implémentation du code fourni aux élèves.
////////////////////////////////////////////////////////////////////////////////

#pragma region "Inclusions" //{

#include "CodeFourni.hpp"

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#pragma endregion //}




#pragma region "Globaux" //{

#pragma region "Fonctions" //{

/// Convertit un angle en degrés vers radians.
/// \return L'angle en radians.
double enRadians(
	double angle  ///< L'angle en degrés.
)
{
	return angle * PI / 180.0;
}


/// Convertit un angle en radians vers degrés.
/// \return L'angle en degrés.
double enDegres(
	double angle  ///< L'angle en radians.
)
{
	return angle * 180.0 / PI;
}


/// Affiche à l'écran les paramètres d'une mission.
void afficherParametres(const ParametresMission& parametres)
{
	cout << "Nom   : " << parametres.nom << "\n"
	     << "Date  : " << put_time(&parametres.dateHeure, "%Y-%m-%d") << "\n" // NOTE: Causera une erreur à l'exécution si la date n'est pas valide.
	     << "Heure : " << put_time(&parametres.dateHeure, "%H:%M:%S") << "\n" // NOTE: Même note ce ci-dessus.
	     << "\n"
	     << "  Notes  " << "\n"
	     << "---------" << "\n"
	     << parametres.notes << endl;
}


/// Affiche à l'écran les données d'une cible.
void afficherCible(const Cible& cible)
{
	cout << fixed << setprecision(7);
	cout << cible.id << ": (" << cible.positionGps.latitude << ", " << cible.positionGps.longitude << ") " << cible.observation << "  <" << cible.nomFichier << ">" << endl;
}


/// Affiche à l'écran une liste de cibles.
void afficherCibles(const ListeCibles& cibles)
{
	for (size_t i = 0; i < cibles.nbElements; ++i)
		afficherCible(cibles.elements[i]);
	cout << endl;
}


/// Affiche à l'écran un journal de détection.
void afficherJournal(const JournalDetection& journal)
{
	afficherParametres(journal.parametres);
	cout << "\n"
	     << "  Cibles  " << "\n"
	     << "----------" << endl;
	afficherCibles(journal.cibles);
}

#pragma endregion //}

#pragma endregion //}

