////////////////////////////////////////////////////////////////////////////////
/// \file    CodeFourni.hpp
/// \author  Charles Hosson et François-R Boyer
/// \version 2018-11-06
///
/// Le code fourni aux élèves est constitué des structures d'enregistrement
/// et de fonctions utilitaires.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <ctime>
#include <string>

using namespace std;

#pragma endregion //}


#pragma region "Déclarations" //{

#pragma region "Constantes" //{

static const size_t TAILLE_NOM_PHOTO = 32;
static const size_t TAILLE_OBSERVATION = 64;
static const size_t TAILLE_NOM_MISSION = 32;
static const size_t TAILLE_NOTES = 256;

static const double PI = 3.14159265358979;

#pragma endregion //}


#pragma region "Structures" //{

/**
 * Coordonnées GPS.
 */
struct PositionGps
{
	double latitude;   ///< En degrés décimaux.
	double longitude;  ///< En degrés décimaux.
};


/**
 * Une cible détectée (format du fichier binaire).
 *
 * Cette structure a le format exact des cibles dans le fichier binaire.
 */
struct Cible
{
	uint32_t      id;                               ///< Numéro d'identification de détection.
	PositionGps   positionGps;                      ///< Où elle a été détectée.
	char          observation[TAILLE_OBSERVATION];  ///< Quelle cible semble avoir été observée.
	char          nomFichier[TAILLE_NOM_PHOTO];     ///< Nom du fichier qui contient la photo.
};


/**
 * Une liste de cibles.
 *
 * Permet de conserver un ensemble de cibles en mémoire, alloué dynamiquement.
 */
struct ListeCibles
{
	Cible* elements;    ///< Pointeur vers un tableau de Cible.
	size_t nbElements;  ///< Nombre de cibles actuellement dans #elements, aux indices 0 à #nbElements-1.
	size_t capacite;    ///< Taille du tableau #elements, donc nombre d'éléments maximum qu'il peut contenir.
};


/**
 * Paramètres de mission (format du fichier binaire).
 *
 * Cette structure a le format exact de l'entête du fichier binaire de cibles.
 */
struct ParametresMission
{
	char   nom[TAILLE_NOM_MISSION];  ///< Son nom.
	char   notes[TAILLE_NOTES];      ///< Quelques notes.
	tm     dateHeure;                ///< Date et heure de début de la mission.
};


/**
 * Journal de détection des cibles.
 *
 * Permet de conserver en mémoire le contenu du fichier de cibles avec des structures manipulables.
 */
struct JournalDetection
{
	ParametresMission parametres;
	ListeCibles       cibles;
};

#pragma endregion //}


#pragma region "Globaux" //{

double enRadians(double);

double enDegres(double);

void afficherParametres(const ParametresMission&);

void afficherCible(const Cible& cible);

void afficherCibles(const ListeCibles& cibles);

void afficherJournal(const JournalDetection& journal);

#pragma endregion //}

#pragma endregion //}

