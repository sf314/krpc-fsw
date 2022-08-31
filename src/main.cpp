#include <iostream>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

int main() {
    auto conn = krpc::connect();
    krpc::services::KRPC krpc(&conn);
    std::cout << "Connected to kRPC server version " << krpc.get_status().version() << std::endl;
    // printf("Connected to kRPC server version %s\n", krpc.get_status().version().c_str());

    // Get vessel info from Space Center
    krpc::services::SpaceCenter spaceCenter(&conn);
    auto vessel = spaceCenter.active_vessel();
    auto flight_info = vessel.flight();

    // Printout snapshot of flight telem
    std::cout << "Mean altitude: " << flight_info.mean_altitude() << std::endl;
    std::cout << "G-force: " << flight_info.g_force() << std::endl;
    std::cout << "Lat: " << flight_info.latitude() << std::endl;
    std::cout << "Lon: " << flight_info.longitude() << std::endl;
}