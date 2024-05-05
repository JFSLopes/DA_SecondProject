#include "../header/Coordinates.h"
#include <cmath>

Coordinates::Coordinates(double lat, double lon) : lat(lat), lon(lon) {}

double haversine(const Coordinates& c1, const Coordinates& c2){
    double dLat = (c2.lat - c1.lat) * M_PI / 180.0;
    double dLon = (c2.lon - c1.lon) * M_PI / 180.0;

    /// convert to radians
    double lat1 = (c1.lat) * M_PI / 180.0;
    double lat2 = (c2.lat) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}