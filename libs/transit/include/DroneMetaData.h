#ifndef DRONE_METADATA_H_
#define DRONE_METADATA_H_

#include <map>
#include <string>
#include <vector>

/**
 * @class DroneMetaData
 * @brief Holds metadata about drone trips and strategies.
 */
class DroneMetaData {
 public:
  /**
   * @brief Constructor for DroneMetaData.
   */
  DroneMetaData();

  /**
   * @brief Updates the trip data for a drone.
   * @param destination The destination of the current trip.
   * @param tripLength The length of the current trip.
   * @param strategy The strategy used for the trip.
   * @param tripType The type of trip, e.g., "Pickup" or "DropOff".
   */
  void updateTripData(const std::string& destination, float tripLength,
                      const std::string& strategy, const std::string& tripType);

  /**
   * @brief Gets the total count of trips made by the drone.
   * @return Total number of trips.
   */
  int getTripCount() const;

  /**
   * @brief Calculates the average length of pickup trips.
   * @return Average length of pickup trips.
   */
  float getAveragePickupTripLength() const;

  /**
   * @brief Calculates the average length of drop-off trips.
   * @return Average length of drop-off trips.
   */
  float getAverageDropOffTripLength() const;

  /**
   * @brief Increments the count of a particular strategy used.
   * @param strategy The strategy to increment the count for.
   */
  void incrementStrategyCount(const std::string& strategy);

  /**
   * @brief Gets a formatted string showing the usage count of each strategy.
   * @return A string representing strategy usage counts.
   */
  std::string getStrategyUsageString() const;

  /**
   * @brief Gets the counts of each path type used by the drone.
   * @return Map of path types to their usage counts.
   */
  std::map<std::string, int> getPathCounts() const;

  /**
   * @brief Gets a string representation of all destinations visited.
   * @return A string listing all destinations.
   */
  std::string getDestinationsAsString() const;

 private:
  int pickupTripCount;           ///< Count of pickup trips made.
  int dropOffTripCount;          ///< Count of drop-off trips made.
  int tripCount;                 ///< Total count of all trips.
  float totalPickupTripLength;   ///< Total length of all pickup trips.
  float totalDropOffTripLength;  ///< Total length of all drop-off trips.
  std::map<std::string, int>
      strategyCount;  ///< Map of strategies to their usage counts.
  std::vector<std::string> destinations;  ///< List of all destinations visited.
};

#endif  // DRONE_METADATA_H_
