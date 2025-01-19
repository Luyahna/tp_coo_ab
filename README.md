# Présentation 
Utilisation d'un framework web : Django, avec lequel une application a été créée, à partir d'un modèle UML correspondant à 
une fabrique de crayon.\
La partie Django (python) communique avec une partie en C++ avec des JSON.\
\
Le modèle UML utilisé pour l'implémentation est présenté ci-dessous : 
 ![Alt text](https://gitlab.laas.fr/gsaurel/teach/-/raw/main/media/crayon.png)
 
# Dépendances
## Pré-requis
- Git (version 2.43.0)
- Python (version 3.12.3)
- Pip (version 24.0)
- Venv (version 3.12.3)
## Dépendances Python
- Pip
- Django
- pre-commit [Pas obligatoire]
- ipython
## Dépendances C++
- CMAKE
- Cpr 
- JSON

# Détails du projet
## Python 
Dans cette partie, les modèles, les classes abstraites, l'interface d'administartion ont été implémentés 
dans le fichier 'models.py'.\
\
Pour l'utiliser : 
- créer un environnement virtuelle
- faire les migrations
- lancer l'application (manage.py runserver)

## C++ 
Dans cette partie les données de l'application sont récupérerées grâce à <cpr/cpr.h> , puis celles-ci sont affichées dans le terminal.\
Tout est traité par le fichier 'low_level.cpp'.\
\
Pour l'utiliser 
- configurer le projet avec Cmake
- compiler le projet avec Cmake
- lancer le projet (./ build) \
\
Cela devrait afficher la liste des données nécessaire à l'opération d'une usine à crayon.\
Remarque : Aucun test unitaire dans cette partie (C++)
