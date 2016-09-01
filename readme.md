# Particle Swarm Optimization

Dans un terminal à partir du dossier "pso"
		make clean	: nettoie le dossier source
		make		: compile le programme
		./pso		: lance le programme


Actuellement, l'optimisation se fait sur un exemple simple (calcul du maximum
d'une fonction qui additionne ses trois paramètres allant de -1000 à 1000).

Pour optimiser une fonction :
	
La fonction objectif doit avoir la signature suivante :

		double f(int n_param, double * param)

		n_param est le nombre de paramètres que prend la fonction
		param est un tableau contenant les paramètres (tous de type double)

Pour chaque paramètre de type double, instancier un objet de classe Domain :

		Domain(double min, double max, int precision)

		min est le minimum du domaine
		max est le maximum du domaine
		precision est le nombre de valeurs que peut prendre le paramètre

Instancier un objet de classe Optimizable :

		Optimizable(double (*f)(int, double *), int n_param, Domain * d, ProblemType pt);

		f est un pointeur qui pointe sur la fonction objectif
		n_param est le nombre de paramètres que prend la fonction
		d est un tableau contenant les domaines de chaque paramètre
		pt décrit l'objectif (min ou max) donné par l'énumération
			enum class ProblemType { MIN, MAX }

Une fois instancié, l'objet Optimizable peut appeler ses deux méthodes

		void optimize(int n_particles, int n_moves);
		void optimize_omp(int n_particles, int n_moves);

		n_particles est le nombre de particules qui recherchent l'optimum
		n_moves est le nombre de mouvements autorisés par particule
		optimize() est la version séquentielle
		optimize_omp() est la version parallélisée

L'optimum trouvé est alors enregistré dans l'attribut optimum de la classe Optimizable

Si un optimum potentiel a été trouvé alors l'attribut optimized est égal à true, sinon l'attribut optimized est égal à false.

