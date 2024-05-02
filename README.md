
# Movie Recommendation System

## Overview
This C++ project is designed for a university programming course and implements a movie recommendation system using content-based and collaborative filtering techniques. It aims to provide personalized movie suggestions to users based on their preferences and similarities with other users.

## Project Structure
- `Movie.cpp` and `Movie.h`: Defines the `Movie` class with attributes and methods relevant to movie entities.
- `User.cpp` and `User.h`: Defines the `User` class for managing user data and interactions with the recommendation system.
- `RecommendationSystem.cpp` and `RecommendationSystem.h`: Implements the core recommendation logic using both content-based and collaborative filtering methods.
- `RecommendationSystemLoader.cpp` and `RecommendationSystemLoader.h`: Handles loading of movie data into the system.
- `UsersLoader.cpp` and `UsersLoader.h`: Handles loading of user data into the system.

## Features
- **Content-based Filtering**: Recommends movies by comparing the features of movies with the user's stated preferences.
- **Collaborative Filtering**: Suggests movies based on the preferences of similar users.
- **Data Management**: Efficient handling of user and movie data with C++ smart pointers to ensure robust memory management.

## Installation
To run this project, you'll need a C++ compiler supporting C++17 or later. Clone the repository and compile the source files:

```bash
git clone [repository-url]
cd [repository-directory]
g++ -std=c++17 -o recommendation_system *.cpp
./recommendation_system
```

Replace `[repository-url]` and `[repository-directory]` with your repository's URL and local directory name, respectively.

## Usage
Execute the compiled application to start recommending movies. The system will prompt for user inputs to simulate interaction:

```bash
./recommendation_system
```

## Contributing
Contributions are welcome! For major changes, please open an issue first to discuss what you would like to change.

## License
Distributed under the MIT License. See `LICENSE` for more information.

## Contact
[Your Contact Information]

## Acknowledgments
- University programming course team for project guidelines.
- Contributors and developers who have worked on this project.
