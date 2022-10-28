#include <iostream>

#include <telemetry.h>

#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

krpc::Client conn;

int main() {

    std::cout << "Starting KRPC session..." << std::endl;
    conn = krpc::connect("MBP", "10.0.1.205", 50002U, 50003U);
    krpc::services::KRPC krpc(&conn);
    std::cout << "Connected to kRPC server version " << krpc.get_status().version() << std::endl;

    // Get vessel info from Space Center
    krpc::services::SpaceCenter spaceCenter(&conn);
    auto vessel = spaceCenter.active_vessel();
    auto frame_srf = vessel.orbit().body().reference_frame();
    auto frame_vsl = vessel.surface_reference_frame();
    auto flight_info = vessel.flight(frame_vsl); // FOR EVERYTHING ELSE
    auto flight_info_srf = vessel.flight(frame_srf); // FOR SPEED/VELOCITY

    // Printout snapshot of flight telem
    telemetry_t telem;
    while (1) {
        telemetry_update(vessel, &telem);
        telemetry_display(&telem);
        telemetry_warnings(&telem);
        std::cout <<  "----------" << std::endl;
    }
}
