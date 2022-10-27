#include <iostream>

#include <signal.h>

#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

krpc::Client conn;

int main() {

    std::cout << "Starting KRPC session..." << std::endl;
    conn = krpc::connect("MBP", "10.0.1.205", 50002U, 50003U);
    krpc::services::KRPC krpc(&conn);
    std::cout << "Connected to kRPC server version " << krpc.get_status().version() << std::endl;
    // printf("Connected to kRPC server version %s\n", krpc.get_status().version().c_str());

    // Get vessel info from Space Center
    krpc::services::SpaceCenter spaceCenter(&conn);
    auto vessel = spaceCenter.active_vessel();
    auto frame_srf = vessel.orbit().body().reference_frame();
    auto frame_vsl = vessel.surface_reference_frame();
    auto flight_info = vessel.flight(frame_vsl); // FOR EVERYTHING ELSE
    auto flight_info_srf = vessel.flight(frame_srf); // FOR SPEED/VELOCITY

    // Printout snapshot of flight telem
    while (1) {
        // Gather data
        double alt_mean = flight_info.mean_altitude();
        double alt_surf = flight_info.surface_altitude();

        double lat = flight_info.latitude();
        double lon = flight_info.longitude();

        float g_force = flight_info.g_force();

        float thrust = vessel.thrust();
        float thrust_avail = vessel.available_thrust();

        double dir_x = std::get<0>(vessel.direction(vessel.surface_reference_frame()));
        double dir_y = std::get<1>(vessel.direction(vessel.surface_reference_frame()));
        double dir_z = std::get<2>(vessel.direction(vessel.surface_reference_frame()));

        double speed = flight_info_srf.speed();
        double speed_mach = flight_info_srf.mach();
        double speed_h = flight_info_srf.horizontal_speed();
        double speed_v = flight_info_srf.vertical_speed();

        float pitch = flight_info.pitch();
        float heading = flight_info.heading();
        float roll = flight_info.roll();

        // Print data, all at once (so there's not perceptible RPC lag)
        
        std::cout << "GPS lat: " << lat << std::endl;
        std::cout << "    lon: " << lon << std::endl;
        std::cout << "G-force: " << g_force << std::endl;
        std::cout << "Thrust currn: " << thrust << std::endl;
        std::cout << "       avail: " << thrust_avail << std::endl;
        std::cout << "Dir x: " << dir_x << std::endl;
        std::cout << "    y: " << dir_y << std::endl;
        std::cout << "    z: " << dir_z << std::endl;

        std::cout << "Alt mean: " << alt_mean << std::endl;
        std::cout << "    surf: " << alt_surf << std::endl;
        std::cout << "Speed: " << speed << " (mach " << speed_mach << ")" << std::endl;
        std::cout << "    h: " << speed_h << std::endl;
        std::cout << "    v: " << speed_v << std::endl;
        std::cout << "Pitch: " << pitch << std::endl;
        std::cout << "Roll: " << roll << std::endl;
        std::cout << "Heading: " << heading << std::endl;


        // Print warnings based on data
        if (speed_v < 0.0 && alt_surf < 1000.0 && speed_h > 150) {
            std::cout << "WARNING: GROUND PROXIMITY" << "\a" << std::endl;
        }

        if (g_force > 2.0) {
            std::cout << "WARNING: HIGH-G" << "\a" << std::endl;
        }

        if (g_force < 0.5) {
            std::cout << "WARNING: LOW-G" << "\a" << std::endl;
        }

        std::cout <<  "----------" << std::endl;
    }
}
