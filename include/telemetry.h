#ifndef _TELEMETRY_H

#define _TELEMETRY_H

// KRPC
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

typedef struct {
    // Position data
    double alt_mean; // ASL
    double alt_surf; // AGL
    double lat; // GPS N<->S, (-90,90)
    double lon; // GPS E<->W, (-180, 180)

    // Orientation data
    double dir_x; // Note: take from vessel in surface reference frame
    double dir_y;
    double dir_z;
    double pitch; // Note: take from vessel in vessel reference frame
    double heading;
    double roll;

    // Motion data
    double speed;
    double speed_mach;
    double speed_h;
    double speed_v;

    // Forces
    float g_force;
    float thrust;
    float thrust_avail;

    // TODO:
    // Thrust per engine
    // Gear status (up/down)
    // Light status
    // Aileron pitch
    // Elevator pitch
    // Rudder angle
    // Flaps status
    // Indicated airspeed
    // Ambient pressure
    // Mass
    // Drag (vector?)

} telemetry_t;

/**
 * @brief Update the provided telemetry struct based on the current data from
 * the provided vessel.
 * 
 * @param vessel KRPC Vessel
 * @param telem Telemetry struct
 */
void telemetry_update(krpc::services::SpaceCenter::Vessel vessel, telemetry_t* telem);

/**
 * @brief Print the provided telemetry all at once
 * 
 * @param telem Telemetry struct
 */
void telemetry_display(telemetry_t* telem);

/**
 * @brief Based on the provided telemetry, print any potential warnings, i.e.
 * GPWS, G-Force, TCAS, etc.
 * 
 * @param telem Telemetry struct
 */
void telemetry_warnings(telemetry_t* telem);

#endif