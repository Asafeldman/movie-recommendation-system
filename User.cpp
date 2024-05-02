#include "User.h"
#include "RecommendationSystem.h"
#define NAME "name: "

User::User (const std::string &name, const rank_map &rankings, const
std::shared_ptr<RecommendationSystem> &recsys)
{
  _username = name, _rankings = rankings, _recsys = recsys;
}

void
User::add_movie_to_rs (const std::string &name, int year,
                       const std::vector<double> &features, double rate)
{
  _recsys->add_movie (name, year, features);
  _rankings[_recsys->get_movie (name, year)] = rate;
}

sp_movie User::get_recommendation_by_content () const
{
  return _recsys->recommend_by_content (*this);
}

sp_movie User::get_recommendation_by_cf (int k) const
{
  return _recsys->recommend_by_cf (*this, k);
}

double
User::get_prediction_score_for_movie (const std::string &name, int year,
                                      int k) const
{
  auto movie_p = _recsys->get_movie (name, year);
  return _recsys->predict_movie_score (*this, movie_p, k);
}

std::ostream &operator<< (std::ostream &os, const User &user)
{
  os << NAME << user.get_name () << "\n" << *user._recsys << std::endl;
  return os;
}






