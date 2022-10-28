#include <telemetry.h>

// KRPC
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

void telemetry_update(krpc::services::SpaceCenter::Vessel vessel, telemetry_t* telem) {
    using namespace std;

    // Reference frames
    auto frame_srf = vessel.orbit().body().reference_frame();
    auto frame_vsl = vessel.surface_reference_frame();

    // Flight information objs
    auto flight_info = vessel.flight(frame_vsl); // FOR EVERYTHING ELSE
    auto flight_info_srf = vessel.flight(frame_srf); // FOR SPEED/VELOCITY

    // Position data
    telem->alt_mean = flight_info.mean_altitude();
    telem->lat = flight_info.latitude();
    telem->lon = flight_info.longitude();

    // Orientation data
    telem->dir_x = std::get<0>(vessel.direction(vessel.surface_reference_frame()));
    telem->dir_y = std::get<1>(vessel.direction(vessel.surface_reference_frame()));
    telem->dir_z = std::get<2>(vessel.direction(vessel.surface_reference_frame()));
    telem->pitch = flight_info.pitch();
    telem->heading = flight_info.heading();
    telem->roll = flight_info.roll();

    // Motion data
    telem->speed = flight_info_srf.speed();
    telem->speed_mach = flight_info_srf.mach();
    telem->speed_h = flight_info_srf.horizontal_speed();
    telem->speed_v = flight_info_srf.vertical_speed();

    // Forces
    telem->g_force = flight_info.g_force();
    telem->thrust = vessel.thrust();
    telem->thrust_avail = vessel.available_thrust();
}

void telemetry_display(telemetry_t* telem) {
    using namespace std;

    // Print data, all at once (so there's not perceptible RPC lag)
    cout << "GPS lat: " << telem->lat << endl;
    cout << "    lon: " << telem->lon << endl;
    cout << "G-force: " << telem->g_force << endl;
    cout << "Thrust currn: " << telem->thrust << endl;
    cout << "       avail: " << telem->thrust_avail << endl;
    cout << "Dir x: " << telem->dir_x << endl;
    cout << "    y: " << telem->dir_y << endl;
    cout << "    z: " << telem->dir_z << endl;

    cout << "Alt mean: " << telem->alt_mean << endl;
    cout << "    surf: " << telem->alt_surf << endl;
    cout << "Speed: " << telem->speed << " (mach " << telem->speed_mach << ")" << endl;
    cout << "    h: " << telem->speed_h << endl;
    cout << "    v: " << telem->speed_v << endl;
    cout << "Pitch: " << telem->pitch << endl;
    cout << "Roll: " << telem->roll << endl;
    cout << "Heading: " << telem->heading << endl;
}

void telemetry_warnings(telemetry_t* telem) {
    using namespace std;

    // Print warnings based on data
    if (telem->speed_v < 0.0 && telem->alt_surf < 1000.0 && telem->speed_h > 150) {
        cout << "WARNING: GROUND PROXIMITY" << "\a" << endl;
    }

    if (telem->g_force > 2.0) {
        cout << "WARNING: HIGH-G" << "\a" << endl;
    }

    if (telem->g_force < 0.5) {
        cout << "WARNING: LOW-G" << "\a" << endl;
    }
}
