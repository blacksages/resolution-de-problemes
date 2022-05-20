#include "Sketch.h"
#include "DynamicTimeWarping.h"
#include <math.h>
#include <stdlib.h>
/**
 * @brief Calcule la distance entre deux points.
 * 
 * @param p1 1er point
 * @param p2 2è point
 * @return double Distance
 */
static double d(Point *p1, Point *p2);
/**
 * @brief Retourne le minimum de trois valeurs.
 * 
 * @param v1 1ère valeur
 * @param v2 2è valeur
 * @param v3 3è valeur
 * @return double Minimum
 */
static double min(double v1, double v2, double v3);

double dtw(Sketch sketch1, Sketch sketch2, double maxDistance)
{
  // Matrice des coûts
  double *distances = calloc(sketch1.size * sketch2.size, sizeof(double));
  if (distances == NULL) // Echec calloc
    return NAN;
  double min_dist = +INFINITY; // Distance minimale par ligne

  for (size_t i = 0; i < sketch1.size; i++) // Lignes
  {
    min_dist = +INFINITY;
    for (size_t j = 0; j < sketch2.size; j++) // Chaque colonne de la ligne i
    {
      distances[i * sketch2.size + j] = d(sketch1.points + i, sketch2.points + j); // Coût instantané
      if (i == j && i == 0) // Coût initial
        distances[i * sketch2.size + j] += 0.;
      else if (i == 0 && j > 0) // Coût en suivant la première ligne
        distances[i * sketch2.size + j] += distances[i * sketch2.size + (j - 1)];
      else if (i > 0 && j == 0) // Coût en suivant la première colonne
        distances[i * sketch2.size + j] += distances[(i - 1) * sketch2.size + j];
      else // Coût en approchant le coin opposé
        distances[i * sketch2.size + j] += min(distances[(i - 1) * sketch2.size + j],
                                               distances[i * sketch2.size + (j - 1)],
                                               distances[(i - 1) * sketch2.size + (j - 1)]);
      min_dist = min_dist > distances[i * sketch2.size + j] ? distances[i * sketch2.size + j] : min_dist;
    }
    if (i != sketch1.size - 1 && min_dist > maxDistance) // Distance minimale de la ligne i
    {
      free(distances);
      return +INFINITY;
    }
  }
  double best_dist = distances[sketch1.size * sketch2.size - 1];
  free(distances);
  return best_dist;
}

double d(Point *p1, Point *p2)
{
  return 0.5 * (fabs((double)(p1->x - p2->x)) + fabs((double)(p1->y - p2->y)));
}

double min(double v1, double v2, double v3)
{
  if (v1 < v2 && v1 < v3)
    return v1;
  else if (v2 < v3 && v2 < v1)
    return v2;
  else
    return v3;
}