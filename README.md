  The costs of Tour Guides at UCLA has reached insane levels! The program aims to create directions that a robot would use to give a tour of the Westwood area. 
Given a list of Points of Interest(POIs) within the city, the program will calculate the shortest possible route between each destination and convert them into 
directions. The application uses a C++ backend to process the points of interest, utilizing a custom-made HashMap class and data parsing to generate a shortest path. 

Before setting up the project, make sure you have the following installed on your system:

  Python 3.x
  Node.js and npm
  A C++ compiler (e.g., g++, clang++)
  Make (optional, for building the C++ project)

Project Setup:

  Setup Instructions
  Backend (Flask + C++)
    1. Make sure you're in the Tour-Guide-Generator directory
    2. Set up Python virtual environment
    python3 -m venv venv
    source venv/bin/activate   # On Windows: venv\Scripts\activate
    3. Install Python dependencies:
    pip install -r requirements.txt
    4. Build the C++ project:
      g++ ".\Tour Guide Generator\main.cpp" ".\Tour Guide Generator\router.cpp" ".\Tour Guide Generator\tour_generator.cpp" ".\Tour Guide Generator\geodb.cpp" -o robot
    5. Run the Flask server
      flask run
  Front End
    1. cd my-app
    2. npm start
    3. Click on the link that pops up to open the site

Input Format

  There are hundreds of locations that exist around Westwood that are stored in the TourGuideGenerator/MapData.txt file (which you can find by doing Ctrl+f with the | character) 
  Here are some of these stops:
    Ackerman Union, Kerckhoff Hall, Student Activities Center, Ami Sushi, Barney's Beanery, Five Guys, Regent, Diddy Riese, Fox Theater, Mr. Noodle, Harvard-Westlake Middle School
  To format your input, put the valid location name followed by a description separated by a "|"
    Example:
    
    Diddy Riese|This is where you get cheap yummy cookies.
    Ami Sushi|Enjoy some raw fish here.
    Fox Theater|Watch a movie premiere here with the big shots.
    Ackerman Union|I want some Jollicup! Who doesn't love boba?
    Five Guys|Fries are great but the prices not so much
    Barney's Beanery|Anyone know what a Beanery is?
      
  After inserting a valid input, the program will output directions that a tour guide robot would follow. This includes how far to go on each road, where to turn, and the ouputting
  of the descriptions you add.

Example Output:

Starting tour...
Welcome to Diddy Riese!
This is where you get cheap yummy cookies.
Proceed 0.015 miles southwest on a path
Take a left turn on Broxton Avenue
Proceed 0.093 miles south on Broxton Avenue
Take a right turn on a path
Proceed 0.014 miles south on a path
Welcome to Ami Sushi!
Enjoy some raw fish here.
Proceed 0.014 miles north on a path
Take a left turn on Broxton Avenue
Proceed 0.093 miles northwest on Broxton Avenue
Take a left turn on a path
Proceed 0.021 miles southwest on a path
Welcome to Fox Theater!
Watch a movie premiere here with the big shots.
Proceed 0.021 miles northeast on a path
Take a left turn on Broxton Avenue
Proceed 0.053 miles north on Broxton Avenue
Take a right turn on Le Conte Avenue
Proceed 0.097 miles east on Le Conte Avenue
Take a left turn on Westwood Plaza
Proceed 0.514 miles northwest on Westwood Plaza
Take a right turn on Bruin Walk
Proceed 0.055 miles east on Bruin Walk
Take a right turn on a path
Proceed 0.028 miles south on a path
Welcome to Ackerman Union!
I want some Jollicup! Who doesn't love boba?
Proceed 0.028 miles north on a path
Take a left turn on Bruin Walk
Proceed 0.055 miles west on Bruin Walk
Take a left turn on Westwood Plaza
Proceed 0.514 miles south on Westwood Plaza
Take a right turn on Le Conte Avenue
Proceed 0.097 miles west on Le Conte Avenue
Take a left turn on Broxton Avenue
Proceed 0.146 miles south on Broxton Avenue
Take a right turn on a path
Proceed 0.021 miles south on a path
Welcome to Five Guys!
Fries are great but the prices not so much
Proceed 0.021 miles north on a path
Proceed 0.014 miles west on a path
Welcome to Barney's Beanery!
Anyone know what a Beanery is?
Your tour has finished!
Total tour distance: 1.914 miles
