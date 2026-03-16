# IHM Visualisation température

Cette IHM permet de visualiser les changements de température extérieure et intérieure, en fonction de la température de consigne indiquée.

L'IHM est diponible en plusieurs formats, en fonction de votre système
d'exploitation :

- pour **Windows uniquement** : l'archive `IHM - Windows Bundle` fournit un
    exécutable Windows prêt à l'emploi.
- pour tous les systèmes d'exploitation : l'archive `IHM - Script` fournit
    le code Python de l'interface. L'éxécution de ce code nécéssite l'installation de dépendances tel qu'indiqué dans la section suivante.

## Dépendances

Le code de l'interface nécéssite les dépendances Python suivantes :
- tkinter
- numpy
- matplotlib

### Installation sous Linux

#### Debian

```bash
sudo apt install python3 python3-tk python3-numpy python3-matplotlib
```

#### Arch Linux

```bash
sudo pacman -S python tk python-numpy python-matplotlib
```

### Installation sous Windows

```ps
winget install python
pip install numpy matplotlib
```

### Installation sous macOS

```zsh
pip3 install numpy matplotlib
```