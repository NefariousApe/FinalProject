#include "DroneMetaData.h"

#include <sstream>

DroneMetaData::DroneMetaData()
    : tripCount(0), totalPickupTripLength(0.0f), totalDropOffTripLength(0.0f) {
  strategyCount["astar"] = 0;
  strategyCount["dfs"] = 0;
  strategyCount["bfs"] = 0;
  strategyCount["dijkstra"] = 0;
  strategyCount["beeline"] = 0;
}

void DroneMetaData::updateTripData(const std::string& destination,
                                   float tripLength,
                                   const std::string& strategy,
                                   const std::string& tripType) {
  std::string detailedDestination =
      tripType + ": " + destination + ", length: " + std::to_string(tripLength);
  destinations.push_back(detailedDestination);
  if (tripType == "Pickup") {
    pickupTripCount++;
    totalPickupTripLength += tripLength;
  } else if (tripType == "DropOff") {
    dropOffTripCount++;
    totalDropOffTripLength += tripLength;
  }
  tripCount++;
  incrementStrategyCount(strategy);
}

int DroneMetaData::getTripCount() const { return tripCount; }

float DroneMetaData::getAveragePickupTripLength() const {
  return pickupTripCount > 0 ? totalPickupTripLength / pickupTripCount : 0.0f;
}

float DroneMetaData::getAverageDropOffTripLength() const {
  return dropOffTripCount > 0 ? totalDropOffTripLength / dropOffTripCount
                              : 0.0f;
}

void DroneMetaData::incrementStrategyCount(const std::string& strategy) {
  // probably better way to do this, all strategies that arent the 4 listed will
  // be counted as beeline
  if (strategy == "astar" || strategy == "dfs" || strategy == "bfs" ||
      strategy == "dijkstra") {
    strategyCount[strategy]++;
  } else {
    strategyCount["beeline"]++;
  }
}

std::map<std::string, int> DroneMetaData::getPathCounts() const {
  return strategyCount;
}

std::string DroneMetaData::getDestinationsAsString() const {
  std::ostringstream oss;
  oss << "[";
  for (size_t i = 0; i < destinations.size(); ++i) {
    oss << "(";
    if (i != 0) {
      oss << ", ";
    }
    oss << destinations[i];
    oss << ")";
  }
  oss << "]";
  return oss.str();
}

std::string DroneMetaData::getStrategyUsageString() const {
  std::ostringstream ss;
  ss << "[";
  for (const auto& pair : strategyCount) {
    if (&pair != &*strategyCount.begin()) {
      ss << ", ";
    }
    ss << pair.first << ": " << pair.second;
  }
  ss << "]";
  return ss.str();
}
