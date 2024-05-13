#ifndef DA_SECONDPROJECT_COORDINATES_H
#define DA_SECONDPROJECT_COORDINATES_H

/**
 * @class Coordinates
 * @brief stores the information related to a coordinate
 *
 * This class stores the latitude (lat) and longitude (lon) of a coordinate and calculates the distance between 2 coordinates
 */
class Coordinates{
private:
    double lat; ///< stores the latitude of a coordinate
    double lon; ///< stores the longitude of a coordinate
public:
    Coordinates (double , double );
    /**
     * @brief Returns the latitude
     */
    double getLat() const;
    /**
     * @brief Calculates the distance between two given coordinates
     *
     * This method uses the haversine formula to calculate the geographical distance between two given coordinates on earth
     *
     * @param c1 First coordinate
     * @param c2 Second coordinate
     * @return Returns the distance between the coordinates
     */
    friend double haversine(const Coordinates& c1, const Coordinates& c2);
};
/**
 * @brief Calculates the distance between 2 geographic coordinates
 * @param c1 Geographical coordinate
 * @param c2 Geographical coordinate
 * @return Returns the distance between c1 and c2
 */
double haversine(const Coordinates& c1, const Coordinates& c2);

#endif //DA_SECONDPROJECT_COORDINATES_H
