# Team-010-10-hw4

Team Number:  010-10                           
Member Names & x500s :   Julian Heyman  heyma045                     
		         Faith Sims     sims0140

              3081W HW4 - Drone Delivery Simulation Project 

How to run the simulation?

First we need to download this project from docker. 
Click and follow the link https://hub.docker.com/repository/docker/faith77/drone_sim/general
Either sign into an existing docker account or create an account. 
To run drone_sim we enter the command.... < docker run --rm -it -p 8081:8081 faith77/drone_sim > in the terminal. 
Commands that we should know in order to properly
• -rm - delete the container as soon as it's stopped
• -d - run the container in detached mode
• -p 80:80 - map the host machine's port 80 to the container's port 80, i.e. hostport:containerport 
• docker/getting-started - the name of the image to instantiate a container from When the drone_sim is run the server is started and a drone is instantiated. 
We can now follow the link http://localhost:8081 and http://localhost:8081/schedule.html to view the project that we are running.


• What does the simulation do?

This is a drone delivery simulation that delivers packages around a simulation of University of Minnesota Twin Cities campus. We have two sites that we utilize http://localhost:8081 and http://localhost:8081/schedule.html to view the project that we are running.
We have a drone that will be used to deliver packages and we have a package that will travel with the drone and be delivered to the customer(Both drone and package obtain most of their movement functionality inherited through IEntity). The pick up/drop off destinations for the for the package are placed on the simulation through http://localhost:8081/schedule.html. Such that the drone will fly to the pick up location, obtain the package and bring it to our delivery destination, then it will perform a spin upon delivery. 


• Below I will explain what our most integral files do. 


• IEntity 
An IEntity object has a unique ID, a position, a direction, a destination,
and details. It also has a speed, which determines how fast the entity moves
in the physical system. Subclasses of IEntity can override the `Update`
function to implement their own movement behavior.



•Drone
Represents a drone in a physical system. The drone move using euler
integration that is structured on a specified velocity and direction.


• Package 
Represents a package in a physical system. The packages move using euler
integration that is structured on a specified velocity and direction.


• SimulationModel handles the transit simulation. It can communicate with the controller.


• TransitWebServer is what holds the simulation and updates sessions.


• IControler is an abstract controller class used in the Transit Service which utalizes the Model View controller pattern

• TransiteService communicates with the webpage through the utilization of web sockets. This is what acts as the controller in the model view.  



• Algorithm.h & .c files
The goal of the below algorithm files are for us to implement the movement of our entities(drone and package)through our simulation. On the front end http://localhost:8081/schedule.html we have a dropdown button such that the user is able to select what path traversal algorithm will be used in their delivery.
The algorithms we have to choose from are the following..
-AstarStrategy.h/cc
-BeelineStrategy.h/.cc
-BfsStrategy.h/.cc
-BfsStrategy.h/.cc
-DfsStrategy.h/.cc
-DijkstraStrategy.h/cc



• FACTORY .h/.cc files
-RobotFactory.h /.cc 
-PackageFactory.h/.cc
-IEntityFactory.h /.cc 
-HumanFactory.h/.cc
-HelicopterFactory.h/.cc
-DroneFactory.h/.cc
-CompositeFactory.h/.cc





• Decorator .h/.c files
Below are listed the files that utilize the decorator design pattern. Once the drone delivers its package to its recipient the movement will use the decorator to implement a celebration upon successful delivery. The celebrations implemented below are spinning and or jumping. 
SpinDecorator.h/.cc
JumpDecorator.h/.cc
ICelebrationDecorator.h/.cc

• New Feature
Link to our video demonstration and explanation of our new feature: https://youtu.be/nuMtQ3wzOLw

• What does it do?
Our new feature will utilize the singleton design pattern in order to collect data and analyze the “best” delivery strategy. Data that will subsequently be converted into a CSV file that the user will be able to download.

• Why is it significantly interesting?
It is significantly interesting in that it will offer the user insight into what path algorithm is the best to use for a timely delivery. It allows the customer access to the data on their orders and gives them the opportunity to select a faster path algorithm in the future. 

• How does it add to the existing work? 
 		![For HW](https://media.github.umn.edu/user/27856/files/575c3036-fc23-4b6f-9952-fd33cea9b006)
It adds in that we can analyze things that are already implemented. We already have the drone delivering packages to the robot, but when a customer chooses which algorithm/path for the drone and package to take, we do not know which algorithm they selected will result in the best delivery time. As such, it is an extremely useful addition to our drone simulation in that it can give the customer the insight that they need in order to, for their future orders, for them to select the best delivery path algorithm. 


• Which design pattern did you choose to implement it and why? 

We selected a singleton because it carries a "global" state or global access that allows every entity to interact with the same data manager resource which makes tracking the data easier and but collecting it as well.

• Instruction to use this new feature.

1. Use the directions on page one under “How to run the simulation” to start the simulation.

2. When you have delivered all the packages that you intend to in a given period and would like to view data/ 
analytics on your delivery time given the amount of space traversed as well as the amount of time it took to be delivered. 
You go to the main simulation page and under the “Stop Simulation” there is a button that says “Export CSV File”. 
Click this button and download the attachment in order to view your analytics.
    
    
    
• Sprint Retrospective
What went well: When it came to divvying up the tasks we each took the task that best suited our strengths and were able to complete said tasks.  The stand up also greatly helped us to coordinate finishing the button and as well as keeping us on track. 
What could have been improved: The only snag we ran into was when it came to recording the video for the README. We rented a space to record but ran into the good old full disk quota, and as such had to individually record our portions. This is why we are not both on the screen at the same time. 
What to do better in the future:Book a space to record the video sooner as we ran out of time to book another slot, but the video was able to be worked out in the end, as such was not the biggest deal. 
Overall, the project ran smoothly due to the efficient and evenly divided up tasks that indeed catered to our individual strengths. 
