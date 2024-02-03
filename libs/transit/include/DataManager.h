#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include <map>
#include <mutex>  // linter says this is unapproved
// but its still used in documentation seen here
// https://en.cppreference.com/w/cpp/thread/mutex
#include <string>

#include "DroneMetaData.h"

/**
 * @class DataManager
 * @brief Manages and logs data related to drone operations.
 */
class DataManager {
 public:
  /**
   * @brief Retrieves the singleton instance of DataManager.
   * @return Pointer to the singleton DataManager instance.
   */
  static DataManager* getInstance();

  /**
   * @brief Logs data for a specific drone.
   * @param droneId The ID of the drone.
   * @param destination The destination of the drone's trip.
   * @param tripLength The length of the trip.
   * @param strategy The navigation strategy used.
   * @param tripType The type of trip, either 'Pickup' or 'DropOff'.
   */
  void logDroneData(int droneId, const std::string& destination,
                    float tripLength, const std::string& strategy,
                    const std::string& tripType);

  /**
   * @brief Exports the collected drone data to a CSV file.
   * @param filename The name of the file to export data to.
   */
  void exportDataToCSV(const std::string& filename) const;

  /**
   * @brief Updates the strategy count for a specific drone.
   * @param droneId The ID of the drone.
   * @param strategy The strategy to update the count for.
   */
  void updateDroneStrategyCount(int droneId, const std::string& strategy);

  /**
   * @brief Destructor for DataManager.
   */
  ~DataManager();

 private:
  /**
   * @brief Constructor for DataManager.
   */
  DataManager();

  // Deleted copy constructor and assignment operator
  DataManager(const DataManager&) = delete;
  DataManager& operator=(const DataManager&) = delete;

  static DataManager* instance;  ///< Singleton instance of DataManager.
  std::map<int, DroneMetaData>
      droneData;  ///< Map of drone IDs to their metadata.

  mutable std::mutex dataMutex;  ///< Mutex for thread safety.
};

#endif  // DATA_MANAGER_H_
