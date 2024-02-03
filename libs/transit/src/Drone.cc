#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DataManager.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  tripCount = 0;
  totalTripLength = 0.0f;
  available = true;
  currentStrategy = "";
  previousPosition = getPosition();
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      DataManager::getInstance()->updateDroneStrategyCount(this->getId(),
                                                           strat);
      if (strat == "astar") {
        toFinalDestination = new JumpDecorator(new AstarStrategy(
            packagePosition, finalDestination, model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
            new SpinDecorator(new JumpDecorator(new DfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
            new SpinDecorator(new SpinDecorator(new BfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
            new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
    }
  }
}

void Drone::update(double dt) {
  if (available) getNextDelivery();

  if (toPackage) {
    toPackage->move(this, dt);
    float tripLength = calculateTripLength();
    totalTripLength += tripLength;

    if (toPackage->isCompleted()) {
      lengthToPickup = totalTripLength;
      DataManager::getInstance()->logDroneData(
          this->getId(), package->getDestination().toString(), totalTripLength,
          currentStrategy, "Pickup");
      currentStrategy = "";
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    float tripLength = calculateTripLength();
    totalTripLength += tripLength;

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      DataManager::getInstance()->logDroneData(
          this->getId(), package->getDestination().toString(),
          totalTripLength - lengthToPickup, currentStrategy, "DropOff");
      delete toFinalDestination;
      totalTripLength = 0;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}

float Drone::calculateTripLength() {
  Vector3 currentPosition = getPosition();
  float distance = 0;

  distance = std::sqrt(std::pow(currentPosition.x - previousPosition.x, 2) +
                       std::pow(currentPosition.y - previousPosition.y, 2));
  previousPosition = currentPosition;
  return distance * 10.56;  // 10.56 is a rough approximation to convert 1 unit
                            // to 1 foot, using the
  // max coords of bottom right being (1000, 600) and google maps giving a rough
  // estimate that shape of map is 1.5 by .9 miles this is likely off by quiet a
  // bit
}
