# Travail 3 TP OS (INFOB231)

Dans le cadre de l'exercice de groupe nous avons du tester le programme sur un certain nombre de threads.
Vous trouverez la capture d'écran de l'exécution <a href='./test-1.png'>ici</a>

Voici nos conclussion:
--- 
Plus le nombre de threads est grand plus les processus attendent pour passer dans le processeur et etre exécuter. Celà a pour conséquence de ralentir significativement le traitement du merge sort. <br />Il n'est pas nessésaire de faire plusieur threads pour nos besoin quotidient. 

<br /><br />
Méthode de testing
--- 
Nous avons conserver la liste présente dans le code mais avons passé en inline arguments le nombre de threads souhaiter <a href="./test-1.png">(voir image)</a>. Le programme se contente juste d'afficher le temps de traitement