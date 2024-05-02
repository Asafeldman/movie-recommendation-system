#include "RecommendationSystem.h"
#include <numeric>
#include <limits>
#include <algorithm>
#include <cmath>
#define NEG_INF (-std::numeric_limits<double>::infinity ())

sp_movie
RecommendationSystem::add_movie (const std::string &name, int year,
                                 const std::vector<double> &features)
{
  auto to_add = std::make_shared<Movie> (name, year);
  _rs[to_add] = features;
  return to_add;
}

sp_movie
RecommendationSystem::get_movie (const std::string &name, int year) const
{
  auto to_find = _rs.find
      (std::make_shared<Movie> (name, year));
  if (to_find == _rs.end ())
  { return nullptr; }
  return to_find->first;
}

double RecommendationSystem::get_user_mean (const User &user)
{
  auto rankings = user.get_ranks ();
  double sum = 0;
  for (const auto &ranking: rankings)
  { sum += ranking.second; }
  return sum / (double) rankings.size ();
}

std::vector<double>
RecommendationSystem::get_preferences_vec (const User &user, double user_mean)
{
  std::vector<double> accumulator (_rs.begin ()->second.size (), 0.0);
  std::vector<double> pref_vec (_rs.begin ()->second.size (), 0.0);
  auto rankings = user.get_ranks ();
  for (const auto &ranking: rankings)
  {
    auto cur_vec = _rs.find (ranking.first)->second;
    std::transform (cur_vec.begin (), cur_vec.end (), accumulator.begin (),
                    [&] (double value)
                    { return value * (ranking.second - user_mean); });
    for (int i = 0; i < (int) pref_vec.size (); ++i)
    { pref_vec[i] += accumulator[i]; }
  }
  return pref_vec;
}

sp_movie RecommendationSystem::recommend_by_content (const User &user)
{
  double max_val = NEG_INF;
  sp_movie max_movie = nullptr;
  auto rankings = user.get_ranks ();
  auto pref_vec = get_preferences_vec (user,
                                       get_user_mean (user));
  for (const auto &pair: _rs)
  {
    auto cur_vec = pair.second;
    auto cur_movie = pair.first;
    if (rankings.find (cur_movie) == rankings.end ())
    {
      double cur_similarity = calculate_similarity (cur_vec, pref_vec);
      if (cur_similarity > max_val)
      {
        max_val = cur_similarity;
        max_movie = cur_movie;
      }
    }
  }
  return max_movie;
}

double
RecommendationSystem::calculate_similarity (const std::vector<double> &movie_1,
                                            const std::vector<double> &movie_2)
{
  double movie_1_norm = std::sqrt (std::inner_product (movie_1.begin (),
                                                       movie_1.end (),
                                                       movie_1.begin (), 0.0));
  double movie_2_norm = std::sqrt (std::inner_product (movie_2.begin (),
                                                       movie_2.end (),
                                                       movie_2.begin (), 0.0));
  double prod = std::inner_product (movie_1.begin (), movie_1.end (),
                                    movie_2.begin (), 0.0);
  return prod / (movie_1_norm * movie_2_norm);
}

sp_movie RecommendationSystem::recommend_by_cf (const User &user, int k)
{
  std::map<sp_movie, double, sp_movie_comparator> rating_map;
  auto rankings = user.get_ranks ();
  for (const auto &pair: _rs)
  {
    if (rankings.find (pair.first) == rankings.end ())
    {
      double cur_rating = predict_movie_score (user, pair.first, k);
      rating_map[pair.first] = cur_rating;
    }
  }
  double max_val = NEG_INF;
  sp_movie max_movie = nullptr;
  for (const auto &pair: rating_map)
  {
    if (pair.second > max_val)
    {
      max_movie = pair.first;
      max_val = pair.second;
    }
  }
  return max_movie;
}

double
RecommendationSystem::predict_movie_score (const User &user,
                                           const sp_movie &movie, int k)
{
  std::map<sp_movie, double, sp_movie_comparator> movie_scores;
  auto rankings = user.get_ranks ();
  for (const auto &pair: rankings)
  {
    double cur_similarity = calculate_similarity (
        _rs.find (movie)->second, _rs.find (pair.first)->second);
    movie_scores[pair.first] = cur_similarity;
  }
  std::map<sp_movie, double, sp_movie_comparator> k_movie_scores;

  for (int i = 0; i < k; ++i)
  {
    double max_val = NEG_INF;
    sp_movie max_movie = nullptr;
    for (const auto &pair: movie_scores)
    {
      if (pair.second > max_val)
      {
        max_movie = pair.first;
        max_val = pair.second;
      }
    }
    k_movie_scores[max_movie] = max_val;
    movie_scores.erase (max_movie);
  }
  return calculate_rank (k_movie_scores, user);
}

double
RecommendationSystem::calculate_rank (const std::map<sp_movie, double,
    sp_movie_comparator> &k_map, const User &user)
{
  auto rankings = user.get_ranks ();
  double rank_sum = 0;
  double sim_sum = 0;
  for (const auto &pair: k_map)
  {
    sim_sum += pair.second;
    rank_sum += (pair.second * rankings.find (pair.first)->second);
  }
  return rank_sum / sim_sum;
}

std::ostream &operator<< (std::ostream &os, const RecommendationSystem &sys)
{
  for (const auto &pair: sys._rs)
  {
    os << *pair.first;
  }
  return os;
}

