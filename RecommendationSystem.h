#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H
#include "User.h"
#include <map>

/**
 * Comparator struct for comparing movie shared pointers using the < operator.
 */
struct sp_movie_comparator
{
    bool operator() (const sp_movie &movie_1, const sp_movie &movie_2) const
    {
      return (*movie_1) < (*movie_2);
    }
};

class RecommendationSystem
{
 public:
  explicit RecommendationSystem () = default;
  /**
   * Adds a new movie to the system.
   * @param name: Name of the movie.
   * @param year: Year the movie was made.
   * @param features: Features for the movie.
   * @return Shared pointer to the movie in the system.
   */
  sp_movie add_movie (const std::string &name, int year, const
  std::vector<double> &features);

  /**
   * Calculates the movie with the highest score based on movie features.
   * @param user: User for whom the recommendation is being made.
   * @return Shared pointer to the movie in the system.
   */
  sp_movie recommend_by_content (const User &user);

  /**
   * Calculates the movie with the highest predicted score based on rankings
   * of other movies.
   * @param user: User for whom the recommendation is being made.
   * @param k: Number of similar movies to consider.
   * @return Shared pointer to the movie in the system.
   */
  sp_movie recommend_by_cf (const User &user, int k);

  /**
   * Predicts a user rating for a movie using the item collaborative filtering
   * procedure with the k most similar movies.
   * @param user: User for whom the prediction is being made.
   * @param movie: Movie to predict the rating for.
   * @param k: Number of similar movies to consider.
   * @return Predicted score based on the algorithm described in the PDF.
   */
  double predict_movie_score (const User &user, const sp_movie &movie, int k);

  /**
   * Retrieves a shared pointer to a movie in the system.
   * @param name: Name of the movie.
   * @param year: Year the movie was made.
   * @return Shared pointer to the movie in the system.
   */
  sp_movie get_movie (const std::string &name, int year) const;

  /**
   * Output stream operator for printing a RecommendationSystem object.
   * Prints every movie in the system in an ordered manner according to the
   * Movie < operator.
   * @param os: Output stream to write to.
   * @param sys: RecommendationSystem to be printed.
   * @return A reference to the output stream.
   */
  friend std::ostream &operator<< (std::ostream &os, const
  RecommendationSystem &sys);

 private:
  std::map<sp_movie, std::vector<double>, sp_movie_comparator> _rs;

  /**
   * Calculates the user's mean movie ranking.
   * @param user: User for whom the mean is calculated.
   * @return The user's mean ranking.
   */
  static double get_user_mean (const User &user);

  /**
   * Calculates the user's preferences vector by summing every movie's
   * normalized ranking * the movie's feature vector.
   * @param user: User for whom the preferences vector is calculated.
   * @param user_mean: The user's mean ranking.
   * @return The user's preferences vector.
   */
  std::vector<double> get_preferences_vec (const User &user, double user_mean);

  /**
   * Calculates the similarity between two movies according to the algorithm
   * mentioned in the pdf.
   * @param movie_1: First movie.
   * @param movie_2: Second movie.
   * @return The similarity value for the movies.
   */
  static double calculate_similarity (const std::vector<double> &movie_1,
                                      const std::vector<double> &movie_2);

  /**
   * Calculates a user's ranking for a movie given a map of the user's
   * k-most-similar movies to the one mentioned above.
   * @param k_map: Map of k-most similar movies to some movie in the form of:
   * <shared movie pointer, user's ranking for movie>.
   * @param user: User for whom the ranking is calculated.
   * @return The user's ranking for the movie.
   */
  static double
  calculate_rank (const std::map<sp_movie, double, sp_movie_comparator> &k_map,
                  const User &user);
};

#endif //RECOMMENDATIONSYSTEM_H
