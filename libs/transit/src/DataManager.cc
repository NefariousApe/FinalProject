#include "DataManager.h"

#include <fstream>
#include <iostream>

#include "DroneMetaData.h"

DataManager* DataManager::instance = nullptr;

DataManager* DataManager::getInstance() {
  if (instance == nullptr) {
    instance = new DataManager();
  }
  return instance;
}

DataManager::DataManager() {}

DataManager::~DataManager() { delete instance; }

void DataManager::logDroneData(int droneId, const std::string& destination,
                               float tripLength, const std::string& strategy,
                               const std::string& tripType) {
  std::lock_guard<std::mutex> lock(dataMutex);
  droneData[droneId].updateTripData(destination, tripLength, strategy,
                                    tripType);
}

void DataManager::exportDataToCSV(const std::string& filename) const {
  std::lock_guard<std::mutex> lock(dataMutex);
  std::ofstream file(filename);
  file << "DroneID,TripCount,AveragePickupTripLength,AverageDeliveryTripLength,"
          "Strategy,AllDestinations\n";
  for (const auto& pair : droneData) {
    const auto& metaData = pair.second;
    file << pair.first << "," << metaData.getTripCount() << ","
         << metaData.getAveragePickupTripLength() << ","
         << metaData.getAverageDropOffTripLength() << ","
         << "\"" << metaData.getStrategyUsageString() << "\","
         << metaData.getDestinationsAsString() << "\n";
  }
  file.close();
}

void DataManager::updateDroneStrategyCount(int droneId,
                                           const std::string& strategy) {
  std::lock_guard<std::mutex> lock(dataMutex);
  droneData[droneId].incrementStrategyCount(strategy);
}
