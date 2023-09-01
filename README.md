# Pipex - 42 School Project

## 📋 Résumé

Ce projet est une implémentation simplifiée des mécanismes de gestion de pipes en UNIX. Il simule le fonctionnement de la séquence shell `< file1 cmd1 | cmd2 > file2`.

## 💻 Technologies Utilisées

- Langage de programmation: C
- Système d'exploitation: UNIX
- Outils et bibliothèques: Makefile, Libft

## 📦 Installation

Pour compiler le projet, utilisez les commandes suivantes :

```bash
git clone https://github.com/Jeanmichel7/pipex.git
cd pipex
make
```

## 📜 Règles du Projet

- Le projet doit être écrit en C et conforme à la Norme 42.
- Aucun "segmentation fault", "bus error", "double free" n'est toléré.
- Le Makefile doit compiler le projet avec les flags -Wall, -Wextra et -Werror.
- Toutes les fonctions doivent être prototypées dans des fichiers .h et la librairie Libft doit être utilisée si nécessaire.

## 🛠️ Utilisation

Une fois compilé, le programme peut être utilisé comme suit :

```bash
./pipex file1 "cmd1" "cmd2" file2
```

Exemples

```bash
./pipex infile "cat -e" "grep param" outfile # Équivalent à < infile cat -e | grep param > outfile
./pipex infile "grep bla" "wc -w" outfile # Équivalent à < infile grep bla | wc -w > outfile
```
