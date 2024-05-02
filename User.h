#ifndef USER_H
#define USER_H
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "Movie.h"

class RecommendationSystem;
typedef std::unordered_map<sp_movie, double, hash_func, equal_func> rank_map;

class User
{
 public:
  /**
   * Constructor for the User class.
   * @param name: Name of the user.
   * @param rankings: Map of movie rankings for the user.
   * @param recsys: Shared pointer to the RecommendationSystem.
   */
  User (const std::string &name, const rank_map &rankings, const
  std::shared_ptr<RecommendationSystem> &recsys);

  /**
   * Getter for the user's name.
   * @return The username.
   */
  const std::string &get_name () const
  { return _username; }

  /**
   * Function for adding a movie to the RecommendationSystem.
   * @param name: Name of the movie.
   * @param year: Year the movie was made.
   * @param features: Vector of the movie's features.
   * @param rate: The user's rate for this movie.
   */
  void add_movie_to_rs (const std::string &name, int year,
                        const std::vector<double> &features,
                        double rate);

  /**
   * Getter for the movie rankings map.
   * @return The rankings map.
   */
  const rank_map &get_ranks () const
  { return _rankings; }

  /**
   * Returns a recommendation according to the movie's content.
   * @return Recommended movie.
   */
  sp_movie get_recommendation_by_content () const;

  /**
   * Returns a recommendation according to the similarity recommendation
   * method.
   * @param k: The number of the most similar movies to calculate by.
   * @return Recommendation movie.
   */
  sp_movie get_recommendation_by_cf (int k) const;

  /**
   * Predicts the score for a given movie.
   * @param name: The name of the movie.
   * @param year: The year the movie was created.
   * @param k: The parameter representing the number of the most similar
   * movies to predict the score by.
   * @return Predicted score for the given movie.
   */
  double
  get_prediction_score_for_movie (const std::string &name,
                                  int year, int k) const;

  /**
   * Output stream operator for printing a User object's recommendation
   * system according to the format given in the pdf.
   * @param os: Output stream to write to.
   * @param user: The user object.
   * @return A reference to the output stream.
   */
  friend std::ostream &operator<< (std::ostream &os, const User &user);

 private:
  std::string _username;
  rank_map _rankings;
  std::shared_ptr<RecommendationSystem> _recsys;
};

#endif //USER_H
